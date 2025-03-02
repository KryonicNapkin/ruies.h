#include "rlui_elems.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* custom variable that stores current error */
int __rlui_error = 0;

int __current_elem_idx = 0;

/* STYLE DEFINITIONS OF THE ELEMENTS */
struct GlobalStyle __style = {
    .elem_styles = {
        /* Button */
        {
            BORDER_COLOR_NORMAL,  BASE_COLOR_NORMAL,   TEXT_COLOR_NORMAL,  // state: NORMAL  
            BORDER_COLOR_FOCUSED, BASE_COLOR_FOCUSED,  TEXT_COLOR_FOCUSED, // state: FOCUSED
            BORDER_COLOR_CLICKED, BASE_COLOR_CLICKED,  TEXT_COLOR_CLICKED, // state: CLICKED
            __BORDER_WIDTH, ALIGN_CENTER, 
            0, 0, 0, 0,       0, 0, 0, 0
        }, 
        /* Button Grid */
        { 
            BORDER_COLOR_NORMAL, BASE_COLOR_NORMAL, TEXT_COLOR_NORMAL,     // state: NORMAL  
            BORDER_COLOR_FOCUSED, BASE_COLOR_FOCUSED, TEXT_COLOR_FOCUSED,  // state: FOCUSED
            BORDER_COLOR_CLICKED, BASE_COLOR_CLICKED, TEXT_COLOR_CLICKED,  // state: CLICKED
            __BORDER_WIDTH, ALIGN_CENTER, 
            0, 0, 0, 0,       0, 0, 0, 0
        }, 
        /* Titlebar */
        { 
            BORDER_COLOR_NORMAL, BASE_COLOR_NORMAL, TEXT_COLOR_NORMAL,     // state: NORMAL  
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                // state: FOCUSED
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                // state: CLICKED
            __BORDER_WIDTH, ALIGN_LEFT, 
            10, 0, 0, 0,      0, 0, 0, 0
        },
        /* TOGGLE */
        { 
            BORDER_COLOR_NORMAL, BASE_COLOR_NORMAL, TEXT_COLOR_NORMAL,      // state: NORMAL
            BORDER_COLOR_FOCUSED, BASE_COLOR_FOCUSED, TEXT_COLOR_FOCUSED,   // state: FOCUSED
            BORDER_COLOR_CLICKED, BASE_COLOR_CLICKED, TEXT_COLOR_CLICKED,   // state: CLICKED
            __BORDER_WIDTH, ALIGN_CENTER, 
            0, 0, 0, 0,      0, 0, 0, 0
        },
        /* LABEL */
        { 
            NO_COLOR_VALUE, BASE_COLOR_NORMAL, TEXT_COLOR_NORMAL,           // state: NORMAL
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                 // state: FOCUSED
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                 // state: CLICKED
            0, ALIGN_LEFT, 
            10, 0, 0, 0,      0, 0, 0, 0
        },
        /* CellBox */
        { 
            BORDER_COLOR_NORMAL, BASE_COLOR_NORMAL, NO_COLOR_VALUE,         // state: NORMAL
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                 // state: FOCUSED
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                 // state: CLICKED
            __BORDER_WIDTH, 0, 
            0, 0, 0, 0,      0, 0, 0, 0
        },
    }, 
    .fontloader = {DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER},
    .font_sizes = {__FONT_SIZE, __FONT_SIZE, __FONT_SIZE, __FONT_SIZE, __FONT_SIZE, __FONT_SIZE},
};

/* NOTE: fontloader function should be generated using raylib's ExportFontAsCode() function
 *       and you should remove the check for IsGpuReady in the .h file for this function to 
 *       correctly load your desired font 
 */
void set_font_loader_function(enum Elements elem, Font (*fontloader)(void)) {
    if (elem == ALL_ELEMENTS) {
        for (int i = 0; i < MAX_ELEMENTS_COUNT; ++i) {
            __style.fontloader[i] = fontloader;
        }
    } else { 
        __style.fontloader[elem] = fontloader;
    }
    __rlui_error = 0;
}

void set_elem_font_size(enum Elements elem, float font_size) {
    if (elem == ALL_ELEMENTS) {
        for (int i = 0; i < MAX_ELEMENTS_COUNT; ++i) {
            __style.font_sizes[i] = font_size;
        }
    } else { 
        __style.font_sizes[elem] = font_size;
    }
    __rlui_error = 0;
}

int check_rlui_error(void) {
    return __rlui_error;
}

/* Function for creation of a button */
button_t make_button(Rectangle bounds, const char* text) {
    button_t btn = {0};
    /* Assaign a unique id to a button */
    btn.idx = (!__current_elem_idx ? 0 : __current_elem_idx+1);
    btn.bounds = bounds;

    /* Check if user didn't provided any title to the function */
    if (text != NULL) {
        btn.text = rlui_strdup(text);
    } else {
        __rlui_error = 1;
        return btn;
    }

    memcpy(&btn.style, &__style.elem_styles[BUTTON], sizeof(uint32_t)*MAX_ELEMENT_ATTRIBUTES);
    btn.font = __style.fontloader[BUTTON]();
    btn.font_size = __style.font_sizes[BUTTON];
    btn.state = NORMAL;
    __current_elem_idx += 1;
    __rlui_error = 0;
    return btn;
}

/* Function to create a titlebar */
titlebar_t make_titlebar(Rectangle bounds, const char* text) {
    titlebar_t titlebar = {0};
    /* Assaign an unique id to every created titlebar */
    titlebar.idx = (!__current_elem_idx ? 0 : __current_elem_idx+1);
    titlebar.bounds = bounds;
    /* Check if no title was provided */
    if (text != NULL) {
        titlebar.text = rlui_strdup(text);
    } else {
        __rlui_error = 1;
        return titlebar;
    }

    memcpy(&titlebar.style, &__style.elem_styles[TITLEBAR], sizeof(uint32_t)*MAX_ELEMENT_ATTRIBUTES);
    titlebar.font = __style.fontloader[TITLEBAR]();
    titlebar.font_size = __style.font_sizes[TITLEBAR];
    __current_elem_idx += 1;
    __rlui_error = 0;
    return titlebar;
}

button_grid_t make_button_grid(uint32_t posx, uint32_t posy, uint32_t rows, uint32_t cols, Rectangle sample_bounds, const char* text[], uint32_t horizontal_spacing, uint32_t vertical_spacing) {
    uint32_t num_of_buttons = rows*cols;
    button_grid_t button_grid = {0};
    button_grid.buttons = (struct Button*)malloc(sizeof(button_t) * (rows*cols));

    /* Count the number of strings provided in text[] */
    uint32_t count = 0;
    while (text[count] != NULL) {
        count++;
    }
    /* If not it will free the buttons and return zeroed struct */
    /* Checks if the number of texts is equal to the number of desired buttons to be created */
    if (text == NULL || count != num_of_buttons || text[num_of_buttons] != NULL) {
        free(button_grid.buttons);
        __rlui_error = 1;
        return button_grid;
    }

    /* Replicate the properties of the original button to every button desired to be created and assaign a specific id to it */
    button_grid.font = __style.fontloader[BUTTON_GRID]();
    button_grid.font_size = __style.font_sizes[BUTTON_GRID];
    memcpy(&button_grid.style, &__style.elem_styles[BUTTON_GRID], sizeof(uint32_t)*MAX_ELEMENT_ATTRIBUTES);
    for (uint32_t i = 0; i < num_of_buttons; ++i) {
        button_grid.buttons[i].font_size = button_grid.font_size;
        button_grid.buttons[i].font = button_grid.font;
        button_grid.buttons[i].bounds = sample_bounds;
        memcpy(&button_grid.buttons[i].style, &button_grid.style, sizeof(uint32_t)*MAX_ELEMENT_ATTRIBUTES);
        button_grid.buttons[i].idx = __current_elem_idx + 1;
        __current_elem_idx += 1;
    }
    /* Calculate the position of every button relative to the provided horizontal and vertical spacing */
    uint32_t vertical_step = 0;
    uint32_t horizontal_step = 0;
    for (uint32_t n = 0; n < num_of_buttons; ++n) {
        button_grid.buttons[n].bounds.x = posx+horizontal_step;
        button_grid.buttons[n].bounds.y = posy+vertical_step;
        horizontal_step += (sample_bounds.width+horizontal_spacing);
        if ((n+1) % cols == 0) {
            vertical_step += (sample_bounds.height+vertical_spacing);
            horizontal_step = 0;
        }
    }
    /* Assaign text to every button */
    for (uint32_t x = 0; x < num_of_buttons; ++x) {
        button_grid.buttons[x].text = rlui_strdup(text[x]);
    }
    /* Set other properties of a button array */
    button_grid.origin_posx = posx;
    button_grid.origin_posy = posy;
    button_grid.horizontal_spacing = horizontal_spacing;
    button_grid.vertical_spacing = vertical_spacing;
    button_grid.rows = rows;
    button_grid.cols = cols;
    __rlui_error = 0;
    return button_grid;
}

toggle_t make_toggle(Rectangle bounds, const char* text) {
    toggle_t toggle = {0};
    toggle.idx = (!__current_elem_idx ? 0 : __current_elem_idx+1);
    toggle.bounds = bounds;

    if (text != NULL) {
        toggle.text = rlui_strdup(text);
    } else {
        __rlui_error = 1;
        return toggle;
    }

    memcpy(&toggle.style, &__style.elem_styles[TOGGLE], sizeof(uint32_t)*MAX_ELEMENT_ATTRIBUTES);
    toggle.font = __style.fontloader[TOGGLE]();
    toggle.font_size = __style.font_sizes[TOGGLE];
    toggle.state = NORMAL;
    __current_elem_idx += 1;
    __rlui_error = 0;
    return toggle;
}

label_t make_label(Rectangle bounds, const char* text, uint32_t left_padding, uint32_t right_padding) {
    label_t label = {0};
    label.idx = (!__current_elem_idx ? 0 : __current_elem_idx+1);
    label.bounds = bounds;

    if (text != NULL) {
        label.text = rlui_strdup(text);
    } else {
        __rlui_error = 1;
        return label;
    }

    memcpy(&label.style, &__style.elem_styles[LABEL], sizeof(uint32_t)*MAX_ELEMENT_ATTRIBUTES);
    label.style[ATTR_LEFT_PADDING] = left_padding;
    label.style[ATTR_RIGHT_PADDING] = right_padding;
    label.font = __style.fontloader[LABEL]();
    label.font_size = __style.font_sizes[LABEL];
    __current_elem_idx += 1;
    __rlui_error = 0;
    return label;
}

cellbox_t make_cellbox(Rectangle bounds, uint32_t rows, uint32_t cols) {
    cellbox_t cellbox = {0};
    if (rows == 0 || cols == 0) {
        __rlui_error = 1;
        return cellbox;
    }
    cellbox.idx = (!__current_elem_idx ? 0 : __current_elem_idx+1);
    __current_elem_idx += 1;
    cellbox.bounds = bounds;

    uint32_t size = rows*cols;
    cellbox.cell_bounds = (Rectangle*)malloc(size * sizeof(Rectangle));
    cellbox.cell_idxs = (int*)malloc(size * sizeof(int));
    float horizontal_step = 0.0f;
    float vertical_step = 0.0f;
    float horiz_div = (cellbox.bounds.width/(float)cols);
    float verti_div = (cellbox.bounds.height/(float)rows);

    for (uint32_t i = 0; i < size; ++i) {
        cellbox.cell_bounds[i].x = cellbox.bounds.x+horizontal_step;
        cellbox.cell_bounds[i].y = cellbox.bounds.y+vertical_step;
        cellbox.cell_bounds[i].width = horiz_div;
        cellbox.cell_bounds[i].height = verti_div;
        horizontal_step += horiz_div;
        if ((i+1) % cols == 0) {
            vertical_step += verti_div;
            horizontal_step = 0;
        }
        cellbox.cell_idxs[i] = i;
    }

    cellbox.number_of_inscribed_elems = 0;
    cellbox.border_color = GetColor(__style.elem_styles[CELLBOX][ATTR_BORDER_COLOR_NORMAL]);
    cellbox.border_width = __style.elem_styles[CELLBOX][ATTR_BORDER_WIDTH];
    cellbox.cell_cols = cols;
    cellbox.cell_rows = rows;
    __rlui_error = 0;
    return cellbox;
}

void merge_neighbouring_cells(cellbox_t* cellbox, cellbox_sides_t side, int idx1);
void split_cell_horizontaly(cellbox_t* cellbox, int idx);
void split_cell_verticaly(cellbox_t* cellbox, int idx);

void inscribe_elem_into_cell(const void* elem, enum Elements type, cellbox_t* cellbox, int cell_idx) {
    Rectangle elem_bounds;
    bool found = false;
    for (uint32_t i = 0; i < cellbox->cell_cols*cellbox->cell_rows; ++i) {
        if (cellbox->cell_idxs[i] == cell_idx) {
            elem_bounds = cellbox->cell_bounds[cell_idx];
            found = true;
            break;
        }
    }
    if (!found) __rlui_error = 1;
    else {
        switch (type) {
            case BUTTON:
                ((button_t*)elem)->bounds = elem_bounds;
                break;
            case TOGGLE:
                ((toggle_t*)elem)->bounds = elem_bounds;
                break;
            case TITLEBAR:
                ((titlebar_t*)elem)->bounds = elem_bounds;
                break;
            case LABEL:
                ((label_t*)elem)->bounds = elem_bounds;
                break;
            default:
                __rlui_error = 1;
                break;
        }
        cellbox->number_of_inscribed_elems++;
        __rlui_error = 0;
    }
}

button_t make_button_from_button(button_t button, Rectangle bounds, const char* text) {
    button_t new_button;
    memcpy(&new_button, &button, sizeof(button_t));
    new_button.bounds = bounds;
    new_button.text = rlui_strdup(text);
    new_button.idx = button.idx + 1;
    __current_elem_idx += 1;
    __rlui_error = 0;
    return new_button;
}

toggle_t make_toggle_from_toggle(toggle_t toggle, Rectangle bounds, const char* text) {
    toggle_t new_toggle;
    memcpy(&new_toggle, &toggle, sizeof(button_t));
    new_toggle.bounds = bounds;
    new_toggle.text = rlui_strdup(text);
    new_toggle.idx = toggle.idx + 1;
    __current_elem_idx += 1;
    __rlui_error = 0;
    return new_toggle;
}
/* Label releated functions */
void attach_label_to_elem(const void* elem, enum Elements type, label_t* label, enum ElemAttachment attach_to) {
    Rectangle elem_bounds = {0};
    switch (type) {
        case BUTTON:
            elem_bounds = (*(button_t*)elem).bounds;
            break;
        case TOGGLE:
            elem_bounds = (*(toggle_t*)elem).bounds;
            break;
        case TITLEBAR:
            elem_bounds = (*(titlebar_t*)elem).bounds;
            break;
        case LABEL:
            elem_bounds = (*(label_t*)elem).bounds;
            break;
        default:
            __rlui_error = 1;
            break;
    }
    switch (attach_to) {
        case TO_THE_LEFT:
            label->bounds.x = elem_bounds.x-label->bounds.width;
            label->bounds.y = elem_bounds.y;
            break;
        case ON_TOP:
            label->bounds.x = elem_bounds.x;
            label->bounds.y = elem_bounds.y-label->bounds.height;
            break;
        case TO_THE_RIGHT:
            label->bounds.x = elem_bounds.x+elem_bounds.width;
            label->bounds.y = elem_bounds.y;
            break;
        case TO_BOTTOM:
            label->bounds.x = elem_bounds.x;
            label->bounds.y = elem_bounds.y+elem_bounds.height;
            break;
        default:
            __rlui_error = 1;
            break;
    }
    label->is_attached = true;
}

uint32_t* get_style(enum Elements elem, int* size) {
    if (elem == ALL_ELEMENTS) {
        if (size != NULL) *size = 0;
        __rlui_error = 1;
        return NULL;
    }
    *size = sizeof(__style.elem_styles[elem])/sizeof(__style.elem_styles[elem][0]);
    __rlui_error = 0;
    return __style.elem_styles[elem];
}

uint32_t get_style_value(enum Elements elem, enum ElemAttr attr) {
    if (elem == ALL_ELEMENTS) {
        __rlui_error = 1;
        return 0;
    }
    return __style.elem_styles[elem][attr];
}

void get_style_colors(enum ElemState state, uint32_t* style, Color* border, Color* base, Color* text) {
    if (border != NULL) *border = GetColor(style[state*3]);
    if (base != NULL) *base = GetColor(style[(state*3)+1]);
    if (text != NULL) *text = GetColor(style[(state*3)+2]);
    __rlui_error = 0;
}

/* Function to change attributes of button */
void set_button_style(button_t* button, enum ElemAttr attr, uint32_t value) {
    if (UNDEFINED_COLOR(button->style[attr])) {
        __rlui_error = 1;
    } else {
        button->style[attr] = value;
        __rlui_error = 0;
    }
}

/* Function to change attributes of the titlebar */
void set_titlebar_style(titlebar_t* titlebar, enum ElemAttr attr, uint32_t value) {
    if (UNDEFINED_COLOR(titlebar->style[attr])) {
        __rlui_error = 1;
    } else {
        titlebar->style[attr] = value;
        __rlui_error = 0;
    }
}

/* Function to change the attribute of every button in a button grid */
void button_grid_attr(button_grid_t* button_grid, enum ElemAttr attr, uint32_t value) {
    for (int i = 0; i < (button_grid->rows*button_grid->cols); ++i) {
        set_button_style(&button_grid->buttons[i], attr, value);
        if (check_rlui_error()) break;
        else __rlui_error = 0;
    }
}

void set_toggle_style(toggle_t* toggle, enum ElemAttr attr, uint32_t value) {
    if (UNDEFINED_COLOR(toggle->style[attr])) {
        __rlui_error = 1;
    } else {
        toggle->style[attr] = value;
        __rlui_error = 0;
    }
}

void set_label_style(label_t* label, enum ElemAttr attr, uint32_t value) {
    if (UNDEFINED_COLOR(label->style[attr])) {
        __rlui_error = 1;
    } else {
        label->style[attr] = value;
        __rlui_error = 0;
    }
}

void set_allstyle(enum Elements elem, enum ElemAttr attr, uint32_t value) {
    if (elem == ALL_ELEMENTS) {
        for (int i = 0; i < MAX_ELEMENTS_COUNT; ++i) {
            __style.elem_styles[i][attr] = value;
        }
    } else {
        __style.elem_styles[elem][attr] = value;
    }
    __rlui_error = 0;
}

/* Function to adjuct positions and dimensions of every button in button array so that they will stretch horizotaly to the until_x value 
 * keeping spacing the same between buttons */
void stretch_button_grid_horiz(button_grid_t* button_grid, uint32_t horizontal_spacing, uint32_t until_x) {
    uint32_t arr_sz = button_grid->rows*button_grid->cols;
    uint32_t horiz_sz = button_grid->cols;
    /* Calculates the new button width */
    uint32_t new_button_width = (((until_x-button_grid->origin_posx)-((horiz_sz-1)*horizontal_spacing))/horiz_sz);
    for (int i = 0; i < arr_sz; ++i) {
        /* Updates the position of every button that is not the first in a row and that it refrences the previous positions to change 
         * the current button position to make the distance between buttons the same */
        if (i % horiz_sz != 0) {
            button_grid->buttons[i].bounds.x = button_grid->buttons[i-1].bounds.x+new_button_width+horizontal_spacing;
        } 
        /* Set the width of every button to the new width */
        button_grid->buttons[i].bounds.width = new_button_width;
    }
    button_grid->horizontal_spacing = horizontal_spacing;
    __rlui_error = 0;
}

/* Function to adjuct positions and dimensions of every button in button array so that they will stretch vertiacaly to the until_y value 
 * keeping spacing the same between buttons */
void stretch_button_grid_verti(button_grid_t* button_grid, uint32_t vertical_spacing, uint32_t until_y) {
    uint32_t arr_sz = button_grid->rows*button_grid->cols;
    uint32_t verti_sz = button_grid->rows;
    /* Calculate the new height of every button */
    uint32_t new_button_height = (((until_y-button_grid->origin_posy)-((verti_sz-1)*vertical_spacing))/verti_sz);
    uint32_t refrence_point = 0;
    /* Set the new verical position to the array original position */
    uint32_t new_pos_y = button_grid->origin_posy;
    for (int i = 0; i < arr_sz; ++i) {
        /* Update the refrence_point */
        if (i % button_grid->cols == 0 && i != 0) {
            refrence_point += new_button_height+vertical_spacing;
            new_pos_y = button_grid->origin_posy+refrence_point;
        } 
        button_grid->buttons[i].bounds.y = new_pos_y;
        button_grid->buttons[i].bounds.height = new_button_height;
    }
    button_grid->vertical_spacing = vertical_spacing;
    __rlui_error = 0;
}

/* Function for rendering a button */
void render_button(button_t* button) {
    __detect_button_state_change(button);
    Color border_color, base_color, text_color;
    Vector2 border_bounds[2] = {
        /* Position */
        __get_elem_with_border_pos(button->bounds, button->style[ATTR_BORDER_WIDTH]),
        /* Dimension */
        __get_elem_with_border_dims(button->bounds, button->style[ATTR_BORDER_WIDTH]),
    };
    Vector2 text_pos = __get_elem_text_pos(button->bounds, button->font, button->text);
    get_style_colors(button->state, button->style, &border_color, &base_color, &text_color);
    /* Drawing */
    DrawRectangleRec(button->bounds, border_color);
    DrawRectangleV(border_bounds[0], border_bounds[1], base_color);
    DrawTextEx(button->font, button->text, text_pos, button->font_size, 0, text_color);
    __rlui_error = 0;
}

/* Function to render a variadic number of buttons */
void vrender_button(int count, ...) {
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; ++i) {
        render_button(va_arg(ap, button_t*));
    }
    va_end(ap);
    __rlui_error = 0;
}

/* Function to render a button array */
void render_button_grid(button_grid_t* buttons) {
    for (int i = 0; i < (buttons->cols*buttons->rows); ++i) {
        render_button(&buttons->buttons[i]);
    }
    __rlui_error = 0;
}

/* Function to render a titlebar */
void render_titlebar(titlebar_t titlebar) {
    Vector2 text_pos = __get_text_pos_align(titlebar.bounds, titlebar.style[ATTR_LEFT_PADDING], titlebar.style[ATTR_RIGHT_PADDING], 
                                            (enum TextAlignment)titlebar.style[ATTR_TEXT_ALIGNMENT], titlebar.font, titlebar.font_size, 
                                            titlebar.text);
    int64_t left_border_width = titlebar.style[ATTR_TITLEBAR_LEFT_BORDER_WIDTH];
    int64_t right_border_width = titlebar.style[ATTR_TITLEBAR_RIGHT_BORDER_WIDTH];
    int64_t top_border_width = titlebar.style[ATTR_TITLEBAR_TOP_BORDER_WIDTH];
    int64_t bottom_border_width = titlebar.style[ATTR_TITLEBAR_BOTTOM_BORDER_WIDTH];

    Color border_color_normal = GetColor(titlebar.style[ATTR_BORDER_COLOR_NORMAL]);

    DrawRectangleRec(titlebar.bounds, GetColor(titlebar.style[ATTR_BASE_COLOR_NORMAL]));
    if (left_border_width > 0) {
        DrawRectangle(titlebar.bounds.x, titlebar.bounds.y, left_border_width, 
                      titlebar.bounds.height, border_color_normal);
    }
    if (right_border_width > 0) {
        DrawRectangle(titlebar.bounds.x+(titlebar.bounds.width-right_border_width), titlebar.bounds.y, left_border_width, 
                      titlebar.bounds.height, border_color_normal);
    }
    if (top_border_width > 0) {
        DrawRectangle(titlebar.bounds.x, titlebar.bounds.y, titlebar.bounds.width, 
                      top_border_width, border_color_normal);
    }
    if (bottom_border_width > 0) {
        DrawRectangle(titlebar.bounds.x, titlebar.bounds.y+(titlebar.bounds.height-bottom_border_width), titlebar.bounds.width, 
                      bottom_border_width, border_color_normal);
    }
    DrawTextEx(titlebar.font, titlebar.text, text_pos, titlebar.font_size, 0, GetColor(titlebar.style[ATTR_TEXT_COLOR_NORMAL]));
    __rlui_error = 0;
}

void render_toggle(toggle_t* toggle) {
    __detect_toggle_state_change(toggle);
    Color border_color, base_color, text_color;
    Vector2 border_bounds[2] = {
        /* Position */
        __get_elem_with_border_pos(toggle->bounds, toggle->style[ATTR_BORDER_WIDTH]),
        /* Dimension */
        __get_elem_with_border_dims(toggle->bounds, toggle->style[ATTR_BORDER_WIDTH]),
    };
    Vector2 text_pos = __get_elem_text_pos(toggle->bounds, toggle->font, toggle->text);
    get_style_colors(toggle->state, toggle->style, &border_color, &base_color, &text_color);
    /* Drawing */
    DrawRectangleRec(toggle->bounds, border_color);
    DrawRectangleV(border_bounds[0], border_bounds[1], base_color);
    DrawTextEx(toggle->font, toggle->text, text_pos, toggle->font_size, 0, text_color);
    __rlui_error = 0;
}

void render_label(label_t* label) {
    Vector2 text_pos = __get_text_pos_align(label->bounds, label->style[ATTR_LEFT_PADDING], 
                                            label->style[ATTR_RIGHT_PADDING], (enum TextAlignment)label->style[ATTR_TEXT_ALIGNMENT],
                                            label->font, label->font_size, label->text);
    Color base_color = GetColor(label->style[ATTR_BASE_COLOR_NORMAL]);
    Color text_color = GetColor(label->style[ATTR_TEXT_COLOR_NORMAL]);
    /* Drawing */
    DrawRectangleRec(label->bounds, base_color);
    DrawTextEx(label->font, label->text, text_pos, label->font_size, 0, text_color);
}

/* Internal function to calculate the position of the boundsagle relative to border width */
Vector2 __get_elem_with_border_pos(Rectangle bounds, uint32_t border_width) {
    Vector2 border_pos = {0};
    border_pos.x = bounds.x+(float)border_width;
    border_pos.y = bounds.y+(float)border_width;
    __rlui_error = 0;
    return border_pos;
}

/* Internal functin to calculate the dimensions of the boundsagle relative to border width */
Vector2 __get_elem_with_border_dims(Rectangle bounds, uint32_t border_width) {
    Vector2 border_dims = {0};
    border_dims.x = bounds.width-(2.0f*(float)border_width);
    border_dims.y = bounds.height-(2.0f*(float)border_width);
    __rlui_error = 0;
    return border_dims;
}

/* Internal function to calculate the text position of a button */
Vector2 __get_elem_text_pos(Rectangle bounds, Font font, const char* text) {
    Vector2 text_pos = {0};
    text_pos.x = bounds.x+((bounds.width-MeasureTextEx(font, text, font.baseSize, 0).x)/2.0f);
    text_pos.y = bounds.y+((bounds.height-MeasureTextEx(font, text, font.baseSize, 0).y)/2.0f);
    __rlui_error = 0;
    return text_pos;
}

Vector2 __get_text_pos_align(Rectangle bounds, uint32_t left_padding, uint32_t right_padding, 
                             enum TextAlignment text_align, Font font, float font_size, const char* text) {
    Vector2 text_pos = {0};
    Vector2 text_dims = MeasureTextEx(font, text, font_size, 0);
    /* Calculates the distance from the sides */
    switch (text_align) {
        case ALIGN_LEFT:
            text_pos.x = (bounds.x+(float)left_padding);
            text_pos.y = (bounds.y+((bounds.height-text_dims.y)/2.0f));
            break;
        case ALIGN_CENTER:
            text_pos.x = (bounds.x+((bounds.width-text_dims.x)/2.0f));
            text_pos.y = (bounds.y+((bounds.height-text_dims.y)/2.0f));
            break;
        case ALIGN_RIGHT:
            text_pos.x = (bounds.width-text_dims.x-(float)right_padding);
            text_pos.y = (bounds.y+((bounds.height-text_dims.y)/2.0f));
            break;
        default:
            __rlui_error = 1;
            break;
    }
    __rlui_error = 0;
    return text_pos;
}

elem_state_t get_button_state(button_t button, bool* active) {
    if (button.state == CLICKED) {
        if (active != NULL) *active = true;
    } else {
        if (active != NULL) *active = false;
    }
    __rlui_error = 0;
    return button.state;
}

elem_state_t get_toggle_state(toggle_t toggle, bool* active) {
    if (toggle.state == CLICKED) { 
        if (active != NULL) *active = true;
    } else {
        if (active != NULL) *active = false;
    }
    __rlui_error = 0;
    return toggle.state;
}

/* Functions for changing element states */
void __detect_button_state_change(button_t* button) {
    bool hover = CheckCollisionPointRec(GetMousePosition(), button->bounds);
    bool clicked = IsMouseButtonDown(0);
    if (!hover && !clicked) {
        button->state = NORMAL;
    } else if (hover && !clicked) {
        button->state = FOCUSED;
    } else if (hover && clicked) {
        button->state = CLICKED;
    }
    __rlui_error = 0;
}

void __detect_toggle_state_change(toggle_t* toggle) {
    bool hover = CheckCollisionPointRec(GetMousePosition(), toggle->bounds);
    bool clicked = IsMouseButtonPressed(0);
    if (!hover && !clicked && toggle->state != CLICKED) {
        toggle->state = NORMAL;
    } else if (hover && !clicked && toggle->state != CLICKED) {
        toggle->state = FOCUSED;
    } else if (hover && clicked && toggle->state != CLICKED) {
        toggle->state = CLICKED;
    } else if (hover && clicked && toggle->state == CLICKED) {
        toggle->state = NORMAL;
    }
    __rlui_error = 0;
}

int get_button_index_in_grid_by_its_idx(button_grid_t button_grid, elem_idx idx) {
    for (uint32_t i = 0; i < button_grid.cols*button_grid.rows; ++i) {
        if (button_grid.buttons[i].idx == idx) {
            __rlui_error = 0;
            return i;
        } 
    }
    __rlui_error = 1;
    return -1;
}
/* */
void free_button_grid(button_grid_t button_grid) {
    free(button_grid.buttons);
    __rlui_error = 0;
}

void free_cellbox(cellbox_t cellbox) {
    free(cellbox.cell_idxs);
    free(cellbox.cell_bounds);
    __rlui_error = 0;
}

/* Custom strdup function */
char* rlui_strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* n_str = (char*)malloc(len);
    if (str) {
        memcpy(n_str, str, len);
    }
    return n_str;
}
