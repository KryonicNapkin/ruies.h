#include "rlui_elems.h"

#include <raylib.h>
#include <raymath.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* custom variable that stores current error */
int __rlui_error = 0;

int __current_elem_idx = 0;

/* STYLE DEFINITIONS OF THE ELEMENTS */
GlobalStyle_t __style = {
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
            NO_COLOR_VALUE, NO_COLOR_VALUE, TEXT_COLOR_NORMAL,              // state: NORMAL
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                 // state: FOCUSED
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                 // state: CLICKED
            0, ALIGN_LEFT, 
            10, 0, 0, 0,      0, 0, 0, 0
        },
        /* CellBox */
        { 
            NO_COLOR_VALUE, BASE_COLOR_NORMAL, NO_COLOR_VALUE,              // state: NORMAL
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                 // state: FOCUSED
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                 // state: CLICKED
            0, 0, 
            0, 0, 0, 0,      0, 0, 0, 0
        },
        /* CellBox */
        { 
            BORDER_COLOR_NORMAL, BASE_COLOR_NORMAL, NO_COLOR_VALUE,         // state: NORMAL
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                 // state: FOCUSED
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                 // state: CLICKED
            0, 0, 
            0, 0, 0, 0,      0, 0, 0, 0
        },
    }, 
    .fontloader = {DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER},
    .font_sizes = {__FONT_SIZE, __FONT_SIZE, __FONT_SIZE, __FONT_SIZE, __FONT_SIZE, __FONT_SIZE, __FONT_SIZE},
};

/* NOTE: fontloader function should be generated using raylib's ExportFontAsCode() function
 *       and you should remove the check for IsGpuReady in the .h file for this function to 
 *       correctly load your desired font 
 */
void set_font_loader_function(ElementTypes_t elem, Font (*fontloader)(void)) {
    if (elem == ALL_ELEMENTS) {
        for (int i = 0; i < MAX_ELEMENTS_COUNT; ++i) {
            __style.fontloader[i] = fontloader;
        }
    } else { 
        __style.fontloader[elem] = fontloader;
    }
    __rlui_error = 0;
}

void set_elem_font_size(ElementTypes_t elem, float font_size) {
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
Button_t make_button(Rectangle bounds, const char* text) {
    Button_t btn = {0};
    /* Assaign a unique id to a button */
    btn.id = (!__current_elem_idx ? 0 : __current_elem_idx+1);
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
TitleBar_t make_titlebar(Rectangle bounds, const char* text) {
    TitleBar_t titlebar = {0};
    /* Assaign an unique id to every created titlebar */
    titlebar.id = (!__current_elem_idx ? 0 : __current_elem_idx+1);
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

ButtonGrid_t make_button_grid(uint32_t posx, uint32_t posy, uint32_t rows, uint32_t cols, Rectangle sample_bounds, const char* text[], uint32_t horizontal_spacing, uint32_t vertical_spacing) {
    uint32_t num_of_buttons = rows*cols;
    ButtonGrid_t button_grid = {0};
    button_grid.buttons = malloc(sizeof(Button_t) * (rows*cols));

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
        button_grid.buttons[i].id = __current_elem_idx + 1;
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

Toggle_t make_toggle(Rectangle bounds, const char* text) {
    Toggle_t toggle = {0};
    toggle.id = (!__current_elem_idx ? 0 : __current_elem_idx+1);
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

Label_t make_label(Rectangle bounds, const char* text, uint32_t left_padding, uint32_t right_padding) {
    Label_t label = {0};
    label.id = (!__current_elem_idx ? 0 : __current_elem_idx+1);
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

CellBox_t make_cellbox(Rectangle bounds, uint32_t rows, uint32_t cols, uint32_t cell_margin) {
    CellBox_t cellbox = {0};
    if (rows == 0 || cols == 0) {
        __rlui_error = 1;
        return cellbox;
    }
    cellbox.id = (!__current_elem_idx ? 0 : __current_elem_idx+1);
    __current_elem_idx += 1;
    cellbox.bounds = bounds;

    uint32_t size = rows*cols;
    cellbox.cell_bounds = malloc(size * sizeof(Rectangle));
    cellbox.cell_ids = malloc(size * sizeof(int));
    cellbox.cell_margin = cell_margin;
    cellbox.cell_cols = cols;
    cellbox.cell_rows = rows;

    for (uint32_t i = 0; i < size; ++i) {
        cellbox.cell_ids[i] = i;
    }
    calculate_cells(&cellbox);

    cellbox.number_of_inscribed_elems = 0;
    __rlui_error = 0;
    return cellbox;
}

WindowBox_t make_window_box(Rectangle bounds, WindowBoxStyles_t border_style, uint32_t border_width, uint32_t border_gap) {
    WindowBox_t winbox = {0};
    winbox.id = (!__current_elem_idx ? 0 : __current_elem_idx+1);
    __current_elem_idx += 1;
    winbox.bounds = bounds;

    winbox.border_width = border_width;
    set_global_style(WINBOX, ATTR_BORDER_WIDTH, border_width);
    winbox.border_color = GetColor(get_style_value(WINBOX, ATTR_BORDER_COLOR_NORMAL));
    winbox.base_color = GetColor(get_style_value(WINBOX, ATTR_BASE_COLOR_NORMAL));
    winbox.border_gap = 0;
    if (border_style == DOUBLE_BORDER) {
        winbox.border_gap = border_gap;
    }
    winbox.state = NORMAL;
    winbox.border_style = border_style;
    __rlui_error = 0;
    return winbox;
}

void merge_neighbouring_cells(CellBox_t* cellbox, CellBoxSides_t side, int idx1);
void split_cell_horizontaly(CellBox_t* cellbox, int idx);
void split_cell_verticaly(CellBox_t* cellbox, int idx);

void inscribe_elem_into_cell(const void* elem, ElementTypes_t type, CellBox_t* cellbox, int cell_idx) {
    Rectangle elem_bounds;
    bool found = false;
    for (uint32_t i = 0; i < cellbox->cell_cols*cellbox->cell_rows; ++i) {
        if (cellbox->cell_ids[i] == cell_idx) {
            elem_bounds = cellbox->cell_bounds[cell_idx];
            found = true;
            break;
        }
    }
    if (!found) __rlui_error = 1;
    else {
        switch (type) {
            case BUTTON:
                ((Button_t*)elem)->bounds = elem_bounds;
                break;
            case TOGGLE:
                ((Toggle_t*)elem)->bounds = elem_bounds;
                break;
            case TITLEBAR:
                ((TitleBar_t*)elem)->bounds = elem_bounds;
                break;
            case LABEL:
                ((Label_t*)elem)->bounds = elem_bounds;
                break;
            default:
                __rlui_error = 1;
                break;
        }
        cellbox->number_of_inscribed_elems++;
        __rlui_error = 0;
    }
}

void insert_cellbox_into_window_box(CellBox_t* cellbox, WindowBox_t winbox) {
    Rectangle bounds;
    if (winbox.border_style == NORMAL_BORDER) {
        bounds = (Rectangle){
            .x = winbox.bounds.x+winbox.border_width,
            .y = winbox.bounds.y+winbox.border_width,
            .width = winbox.bounds.width-(2.0f*winbox.border_width),
            .height = winbox.bounds.height-(2.0f*winbox.border_width),
        };
    } else {
        bounds = (Rectangle){
            .x = winbox.bounds.x+winbox.border_gap+(2.0f*winbox.border_width),
            .y = winbox.bounds.y+winbox.border_gap+(2.0f*winbox.border_width),
            .width = winbox.bounds.width-((4.0f*winbox.border_width)+(2.0f*winbox.border_gap)),
            .height = winbox.bounds.height-((4.0f*winbox.border_width)+(2.0f*winbox.border_gap)),
        };
    }
    cellbox->bounds = bounds;
    calculate_cells(cellbox);
    __rlui_error = 0;
}

void set_cellbox_cell_margin(CellBox_t* cellbox, uint32_t cell_margin) {
    cellbox->cell_margin = cell_margin;
    calculate_cells(cellbox);
    __rlui_error = 0;
}

void calculate_cells(CellBox_t* cellbox) {
    float horizontal_step = cellbox->cell_margin;
    float vertical_step = cellbox->cell_margin;
    float horiz_div = ((cellbox->bounds.width-((cellbox->cell_cols+1)*cellbox->cell_margin))/(float)cellbox->cell_cols);
    float verti_div = ((cellbox->bounds.height-((cellbox->cell_rows+1)*cellbox->cell_margin))/(float)cellbox->cell_rows);

    for (uint32_t i = 0; i < cellbox->cell_rows*cellbox->cell_cols; ++i) {
        cellbox->cell_bounds[i].x = cellbox->bounds.x+horizontal_step;
        cellbox->cell_bounds[i].y = cellbox->bounds.y+vertical_step;
        cellbox->cell_bounds[i].width = horiz_div;
        cellbox->cell_bounds[i].height = verti_div;
        horizontal_step += (horiz_div+cellbox->cell_margin);
        if ((i+1) % cellbox->cell_cols == 0) {
            vertical_step += (verti_div+cellbox->cell_margin);
            horizontal_step = cellbox->cell_margin;
        }
    }
    __rlui_error = 0;
}

int relative_cellbox_id(int cols, int x, int y) {
    return (y*cols)+x;
}

Button_t make_button_from_button(Button_t button, Rectangle bounds, const char* text) {
    Button_t new_button;
    memcpy(&new_button, &button, sizeof(Button_t));
    new_button.bounds = bounds;
    new_button.text = rlui_strdup(text);
    new_button.id = button.id + 1;
    __current_elem_idx += 1;
    __rlui_error = 0;
    return new_button;
}

Toggle_t make_toggle_from_toggle(Toggle_t toggle, Rectangle bounds, const char* text) {
    Toggle_t new_toggle;
    memcpy(&new_toggle, &toggle, sizeof(Button_t));
    new_toggle.bounds = bounds;
    new_toggle.text = rlui_strdup(text);
    new_toggle.id = toggle.id + 1;
    __current_elem_idx += 1;
    __rlui_error = 0;
    return new_toggle;
}
/* Label releated functions */
void attach_label_to_elem(const void* elem, ElementTypes_t type, Label_t* label, ElemAttachment_t attach_to) {
    Rectangle elem_bounds = {0};
    switch (type) {
        case BUTTON:
            elem_bounds = (*(Button_t*)elem).bounds;
            break;
        case TOGGLE:
            elem_bounds = (*(Toggle_t*)elem).bounds;
            break;
        case TITLEBAR:
            elem_bounds = (*(TitleBar_t*)elem).bounds;
            break;
        case LABEL:
            elem_bounds = (*(Label_t*)elem).bounds;
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

void set_global_style(ElementTypes_t elem_type, ElemAttr_t attr, uint32_t value) {
    if (elem_type == ALL_ELEMENTS) {
        for (int i = 0; i < MAX_ELEMENTS_COUNT; ++i) {
            if (UNDEFINED_COLOR(__style.elem_styles[i][attr])) {
                __rlui_error = 1;
                break;
            }
            __style.elem_styles[i][attr] = value;
            __rlui_error = 0;
        }
    } else {
        if (UNDEFINED_COLOR(__style.elem_styles[elem_type][attr])) {
            __rlui_error = 1;
        } else {
            __style.elem_styles[elem_type][attr] = value;
            __rlui_error = 0;
        }
    }
}

uint32_t* get_style(ElementTypes_t elem, int* size) {
    if (elem == ALL_ELEMENTS) {
        if (size != NULL) *size = 0;
        __rlui_error = 1;
        return NULL;
    }
    *size = sizeof(__style.elem_styles[elem])/sizeof(__style.elem_styles[elem][0]);
    __rlui_error = 0;
    return __style.elem_styles[elem];
}

uint32_t get_style_value(ElementTypes_t elem, ElemAttr_t attr) {
    if (elem == ALL_ELEMENTS) {
        __rlui_error = 1;
        return 0;
    }
    return __style.elem_styles[elem][attr];
}

void get_style_colors(ElemState_t state, uint32_t* style, Color* border, Color* base, Color* text) {
    if (border != NULL) *border = GetColor(style[state*3]);
    if (base != NULL) *base = GetColor(style[(state*3)+1]);
    if (text != NULL) *text = GetColor(style[(state*3)+2]);
    __rlui_error = 0;
}

/* Function to change attributes of button */
void set_button_style(Button_t* button, ElemAttr_t attr, uint32_t value) {
    if (UNDEFINED_COLOR(button->style[attr])) {
        __rlui_error = 1;
    } else {
        button->style[attr] = value;
        __rlui_error = 0;
    }
}

/* Function to change attributes of the titlebar */
void set_titlebar_style(TitleBar_t* titlebar, ElemAttr_t attr, uint32_t value) {
    if (UNDEFINED_COLOR(titlebar->style[attr])) {
        __rlui_error = 1;
    } else {
        titlebar->style[attr] = value;
        __rlui_error = 0;
    }
}

/* Function to change the attribute of every button in a button grid */
void button_grid_attr(ButtonGrid_t* button_grid, ElemAttr_t attr, uint32_t value) {
    for (int i = 0; i < (button_grid->rows*button_grid->cols); ++i) {
        set_button_style(&button_grid->buttons[i], attr, value);
        if (check_rlui_error()) break;
        else __rlui_error = 0;
    }
}

void set_toggle_style(Toggle_t* toggle, ElemAttr_t attr, uint32_t value) {
    if (UNDEFINED_COLOR(toggle->style[attr])) {
        __rlui_error = 1;
    } else {
        toggle->style[attr] = value;
        __rlui_error = 0;
    }
}

void set_label_style(Label_t* label, ElemAttr_t attr, uint32_t value) {
    if (UNDEFINED_COLOR(label->style[attr])) {
        __rlui_error = 1;
    } else {
        label->style[attr] = value;
        __rlui_error = 0;
    }
}

/* Function to adjuct positions and dimensions of every button in button array so that they will stretch horizotaly to the until_x value 
 * keeping spacing the same between buttons */
void stretch_button_grid_horiz(ButtonGrid_t* button_grid, uint32_t horizontal_spacing, uint32_t until_x) {
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
void stretch_button_grid_verti(ButtonGrid_t* button_grid, uint32_t vertical_spacing, uint32_t until_y) {
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
void render_button(Button_t* button) {
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
        render_button(va_arg(ap, Button_t*));
    }
    va_end(ap);
    __rlui_error = 0;
}

/* Function to render a button array */
void render_button_grid(ButtonGrid_t* buttons) {
    for (int i = 0; i < (buttons->cols*buttons->rows); ++i) {
        render_button(&buttons->buttons[i]);
    }
    __rlui_error = 0;
}

/* Function to render a titlebar */
void render_titlebar(TitleBar_t titlebar) {
    Vector2 text_pos = __get_text_pos_align(titlebar.bounds, titlebar.style[ATTR_LEFT_PADDING], titlebar.style[ATTR_RIGHT_PADDING], 
                                            (TextAlignment_t)titlebar.style[ATTR_TEXT_ALIGNMENT], titlebar.font, titlebar.font_size, 
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

void render_toggle(Toggle_t* toggle) {
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

void render_label(Label_t* label) {
    Vector2 text_pos = __get_text_pos_align(label->bounds, label->style[ATTR_LEFT_PADDING], 
                                            label->style[ATTR_RIGHT_PADDING], (TextAlignment_t)label->style[ATTR_TEXT_ALIGNMENT],
                                            label->font, label->font_size, label->text);
    Color text_color = GetColor(label->style[ATTR_TEXT_COLOR_NORMAL]);
    /* Drawing */
    DrawTextEx(label->font, label->text, text_pos, label->font_size, 0, text_color);
    __rlui_error = 0;
}

void render_winbox(WindowBox_t* winbox) {
    __detect_winbox_state_change(winbox);
    Vector2 border_pos[2] = {
        __get_elem_with_border_pos(winbox->bounds, winbox->border_width),
        __get_elem_with_border_dims(winbox->bounds, winbox->border_width),
    };
    DrawRectangleRec(winbox->bounds, winbox->border_color);
    DrawRectangleV(border_pos[0], border_pos[1], winbox->base_color);
    if (winbox->border_style == DOUBLE_BORDER) {
        DrawRectangleV(Vector2AddValue(border_pos[0], winbox->border_gap), Vector2SubtractValue(border_pos[1], 2.0f*winbox->border_gap), 
                      winbox->border_color);
        DrawRectangleV(Vector2AddValue(border_pos[0], winbox->border_gap+winbox->border_width),
                       Vector2SubtractValue(border_pos[1], 2.0f*(winbox->border_width+winbox->border_gap)), winbox->base_color);
    }
    __rlui_error = 0;
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
                             TextAlignment_t text_align, Font font, float font_size, const char* text) {
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

ElemState_t get_button_state(Button_t button, bool* active) {
    if (button.state == CLICKED) {
        if (active != NULL) *active = true;
    } else {
        if (active != NULL) *active = false;
    }
    __rlui_error = 0;
    return button.state;
}

ElemState_t get_toggle_state(Toggle_t toggle, bool* active) {
    if (toggle.state == CLICKED) { 
        if (active != NULL) *active = true;
    } else {
        if (active != NULL) *active = false;
    }
    __rlui_error = 0;
    return toggle.state;
}

ElemState_t get_winbox_state(WindowBox_t winbox) {
    return winbox.state;
}

/* Functions for changing element states */
void __detect_button_state_change(Button_t* button) {
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

void __detect_toggle_state_change(Toggle_t* toggle) {
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

extern void __detect_winbox_state_change(WindowBox_t* winbox) {
    bool hover = CheckCollisionPointRec(GetMousePosition(), winbox->bounds);
    bool clicked = IsMouseButtonDown(0);
    if (!hover && !clicked) {
        winbox->state = NORMAL;
    } else if (hover && !clicked) {
        winbox->state = FOCUSED;
    } else if (hover && clicked) {
        winbox->state = CLICKED;
    }
    __rlui_error = 0;
}

int get_button_index_in_grid_by_its_idx(ButtonGrid_t button_grid, ElemID_t idx) {
    for (uint32_t i = 0; i < button_grid.cols*button_grid.rows; ++i) {
        if (button_grid.buttons[i].id == idx) {
            __rlui_error = 0;
            return i;
        } 
    }
    __rlui_error = 1;
    return -1;
}
/* */
void free_button_grid(ButtonGrid_t button_grid) {
    free(button_grid.buttons);
    __rlui_error = 0;
}

void free_cellbox(CellBox_t cellbox) {
    free(cellbox.cell_ids);
    free(cellbox.cell_bounds);
    __rlui_error = 0;
}

/* Custom strdup function */
char* rlui_strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* n_str = malloc(len);
    if (str) {
        memcpy(n_str, str, len);
    }
    return n_str;
}
