#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raylib.h"
#include "rlui_elems.h"

int _current_elem_idx = 0;

/* 
 * TODO: make loading font efficient by loading font just once DONE
 *       make more ui elements like (TitleBar, Selection window list)
 *       support for icons
 *       maybe support for rounded corners
 */

/* Function for creation of a button */
button_t make_button(int32_t posx, int32_t posy, int32_t width, int32_t height, const char* text, bool highlight_on_hover) {
    button_t btn = {0};
    /* Assaign to every button a unique id for pressing function */
    btn.idx = (!_current_elem_idx ? 0 : _current_elem_idx+1);
    btn.posx = posx;
    btn.posy = posy;
    btn.width = width;
    btn.height = height;

    /* Check if user didn't provided any title to the function */
    if (text == NULL) {
        btn.text = rl_ui_strdup("");
    } else {
        btn.text = rl_ui_strdup(text);
    }

    btn.text_font = LoadFontEx(DEF_FONT_PATH, DEF_BUTTON_FONT_SZ, NULL, 0);
    btn.font_sz = DEF_BUTTON_FONT_SZ;
    btn.border_width_px = DEF_BUTTON_BORDER_WIDTH;
    btn.border_fg = DEF_BUTTON_BORDER_FG_COLOR;
    btn.button_bg = DEF_BUTTON_BG_COLOR;
    btn.text_fg = DEF_BUTTON_TEXT_FG_COLOR;
    btn.highlighting = highlight_on_hover;
    return btn;
}

/* Function to create a titlebar */
titlebar_t make_titlebar(int32_t posx, int32_t posy, int32_t width, int32_t height, const char* text, text_align_t text_alignment, hpadding_t text_padding) {
    titlebar_t titlebar = {0};
    /* Assaign an unique id to every created titlebar */
    titlebar.idx = (!_current_elem_idx ? 0 : _current_elem_idx+1);
    titlebar.posx = posx;
    titlebar.posy = posy;
    titlebar.width = width;
    titlebar.height = height;
    /* Check if no title was provided */
    if (text == NULL) {
        titlebar.text = rl_ui_strdup("");
    } else {
        titlebar.text = rl_ui_strdup(text);
    }
    titlebar.text_font = GetFontDefault();
    titlebar.font_sz = 15;
    titlebar.text_padding = text_padding;
    titlebar.text_alignment = text_alignment;
    titlebar.bg_color = WHITE;
    titlebar.text_fg = BLACK;
    return titlebar;
}

button_array_t make_button_array(int32_t origin_posx, int32_t origin_posy, uint32_t rows, uint32_t cols, button_t orig_button, const char* text[], int32_t horizontal_spacing, int32_t vertical_spacing) {
    uint32_t num_of_buttons = rows*cols;
    button_array_t button_arr;
    button_arr.buttons = malloc(sizeof(button_t) * (rows*cols));

    /* Count the number of texts assaigned to every button in an array */
    int count = 0;
    char* fallback_name;
    bool is_text_null = false;
    if (text == NULL) {
        is_text_null = true;
    } else {
        while (text[count] != NULL) {
            count++;
        }
    }
    /* Checks if the number of texts is equal to the number of desired buttons to be created */
    /* If not every button outside the number of texts provided will be assaigned a fallback_name of text[count-1] */
    if (count != num_of_buttons && !is_text_null) {
        fallback_name = rl_ui_strdup(text[count-1]);
    }
    /* Replicate the properties of the original button to every button desired to be created and assaign a specific id to it */
    for (int i = 0; i < num_of_buttons; ++i) {
        memmove(&button_arr.buttons[i], &orig_button, sizeof(button_t));
        button_arr.buttons[i].idx = _current_elem_idx + 1;
        _current_elem_idx += 1;
    }
    /* Calculate the position of every button relative to the provided horizontal and vertical spacing */
    int32_t vertical_step = 0;
    int32_t horizontal_step = 0;
    for (int n = 0; n < num_of_buttons; ++n) {
        button_attr(&button_arr.buttons[n], BUTTON_POS, &(Vector2){orig_button.posx+horizontal_step, orig_button.posy+vertical_step});
        horizontal_step += (orig_button.width+horizontal_spacing);
        if ((n+1) % cols == 0) {
            vertical_step += (orig_button.height+vertical_spacing);
            horizontal_step = 0;
        }
    }
    /* Assaign text to every button */
    for (int x = 0; x < num_of_buttons; ++x) {
        if (x >= count || is_text_null) {
            button_arr.buttons[x].text = rl_ui_strdup(fallback_name);
        } else {
            button_arr.buttons[x].text = rl_ui_strdup(text[x]);
        }
    }
    /* Set other properties of a button array */
    button_arr.origin_posx = origin_posx;
    button_arr.origin_posy = origin_posy;
    button_arr.horizontal_spacing = horizontal_spacing;
    button_arr.vertical_spacing = vertical_spacing;
    button_arr.rows = rows;
    button_arr.cols = cols;
    /* Free the fallback name */
    free(fallback_name);
    return button_arr;
}

/* Function to copy the attributes of a button to newly created button but updating it's id */
button_t copy_button(button_t button) {
    button_t new_button;
    memcpy(&new_button, &button, sizeof(button));
    new_button.idx = _current_elem_idx+1;
    _current_elem_idx += 1;
    return new_button;
}

/* Function to change attributes of button using an enum with void* typecasting */
void button_attr(button_t* button, button_attr_t attr, const void* value) {
    switch (attr) {
        case BUTTON_POS:
            button->posx = (int32_t)(*(Vector2*)value).x;
            button->posy = (int32_t)(*(Vector2*)value).y;
            break;
        case BUTTON_DIMS:
            button->width = (int32_t)(*(Vector2*)value).x;
            button->height = (int32_t)(*(Vector2*)value).y;
            break;
        case BUTTON_TEXT:
            button->text = rl_ui_strdup((char*)value);
            break;
        case BUTTON_TEXT_FONT:
            button->text_font = *(Font*)value;
            break;
        case BUTTON_FONT_SZ:
            button->font_sz = *(uint32_t*)value;
            break;
        case BUTTON_BORDER_WIDTH:
            button->border_width_px = *(uint32_t*)value;
            break;
        case BUTTON_BORDER_FG:
            button->border_fg = *(Color*)value;
            break;
        case BUTTON_BG:
            button->button_bg = *(Color*)value;
            break;
        case BUTTON_TEXT_FG:
            button->text_fg = *(Color*)value;
            break;
        case BUTTON_IS_HIGHLIGHTING:
            button->highlighting = *(bool*)value;
            break;
        case BUTTON_TEXT_FG_HIGHLIGHT:
            button->text_fg_highlight = *(Color*)value;
            break;
        case BUTTON_BUTTON_BG_HIGHLIGHT:
            button->button_bg_highlight = *(Color*)value;
            break;
        case BUTTON_BORDER_FG_HIGHLIGHT:
            button->border_fg_highlight = *(Color*)value;
            break;
        default:
            break;
    }
}

/* Function to change the same attribute, but to variadic amount of buttons */
void vbutton_attr(int count, button_attr_t attr, const void* value, ...) {
    va_list ap;
    va_start(ap, value);
    for (int i = 0; i < count; ++i) {
        button_t* current_button = va_arg(ap, button_t*);
        button_attr(current_button, attr, value);
    }
    va_end(ap);
}

/* Function to change the attribute of every button in a button array */
void lbutton_attr(button_array_t* button_array, button_attr_t attr, const void* value) {
    for (int i = 0; i < (button_array->rows*button_array->cols); ++i) {
        button_attr(&button_array->buttons[i], attr, value);
    }
}

/* Function to change the attributes of a titlebar */
void titlebar_attr(titlebar_t* titlebar, titlebar_attr_t attr, const void* value) {
    switch (attr) {
        case TITLEBAR_POS:
            titlebar->posx = (int32_t)(*(Vector2*)value).x;
            titlebar->posy = (int32_t)(*(Vector2*)value).y;
            break;
        case TITLEBAR_DIMS:
            titlebar->width = (int32_t)(*(Vector2*)value).x;
            titlebar->height = (int32_t)(*(Vector2*)value).y;
            break;
        case TITLEBAR_TEXT:
            titlebar->text = rl_ui_strdup((char*)value);
            break;
        case TITLEBAR_TEXT_FONT:
            titlebar->text_font = *(Font*)value;
            break;
        case TITLEBAR_TEXT_ALIGN:
            titlebar->text_alignment = *(text_align_t*)value;
            break;
        case TITLEBAR_TEXT_PADDING:
            titlebar->text_padding = *(hpadding_t*)value;
            break;
        case TITLEBAR_FONT_SZ:
            titlebar->font_sz = *(uint32_t*)value;
            break;
        case TITLEBAR_BG_COLOR:
            titlebar->bg_color = *(Color*)value;
            break;
        case TITLEBAR_TEXT_FG:
            titlebar->text_fg = *(Color*)value;
            break;
        default:
            break;
    }
}

/* Function for rendering a button */
void render_button(button_t button) {
    bool button_hover = button_cursor_hover(button);
    /* Checks whether highlighting is enabled */
    if (button_hover && button.highlighting) {
        DrawRectangle(button.posx, button.posy, button.width, button.height, button.border_fg_highlight);
        DrawRectangleV(_get_button_with_border_pos(button), _get_button_with_border_dims(button), button.button_bg_highlight);
        DrawTextEx(button.text_font, button.text, _get_button_text_pos(button), button.font_sz, 0, button.text_fg_highlight);
    } else {
        DrawRectangle(button.posx, button.posy, button.width, button.height, button.border_fg);
        DrawRectangleV(_get_button_with_border_pos(button), _get_button_with_border_dims(button), button.button_bg);
        DrawTextEx(button.text_font, button.text, _get_button_text_pos(button), button.font_sz, 0, button.text_fg);
    }
}

/* Function to render a variadic number of buttons */
void vrender_button(int count, ...) {
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; ++i) {
        render_button(va_arg(ap, button_t));
    }
    va_end(ap);
}

/* Function to render a button array */
void lrender_button(button_array_t buttons) {
    for (int i = 0; i < (buttons.cols*buttons.rows); ++i) {
        render_button(buttons.buttons[i]);
    }
}

/* Function to render a titlebar */
void render_titlebar(titlebar_t titlebar) {
    Vector2 text_pos = {0};
    Vector2 text_dims = MeasureTextEx(titlebar.text_font, titlebar.text, titlebar.font_sz, 0);
    /* Calculates the distance from the sides */
    switch (titlebar.text_alignment) {
        case ALIGN_LEFT:
            text_pos.x = titlebar.posx+titlebar.text_padding.from_left;
            text_pos.y = titlebar.posy+((titlebar.height-text_dims.y)/2);
            break;
        case ALIGN_CENTER:
            text_pos.x = titlebar.posx+((titlebar.width-text_dims.x)/2);
            text_pos.y = titlebar.posy+((titlebar.height-text_dims.y)/2);
            break;
        case ALIGN_RIGHT:
            text_pos.x = titlebar.width-text_dims.x-titlebar.text_padding.from_right;
            text_pos.y = titlebar.posy+((titlebar.height-text_dims.y)/2);
            break;
        default:
            break;
    }
    DrawRectangle(titlebar.posx, titlebar.posy, titlebar.width, titlebar.height, titlebar.bg_color);
    DrawTextEx(titlebar.text_font, titlebar.text, text_pos, titlebar.font_sz, 0, titlebar.text_fg);
}

/* Internal function to calculate the position of the rectagle relative to border width */
Vector2 _get_button_with_border_pos(button_t button) {
    Vector2 button_border_pos = {0};
    button_border_pos.x = button.posx+button.border_width_px;
    button_border_pos.y = button.posy+button.border_width_px;
    return button_border_pos;
}

/* Internal functin to calculate the dimensions of the rectagle relative to border width */
Vector2 _get_button_with_border_dims(button_t button) {
    Vector2 button_border_dims = {0};
    button_border_dims.x = button.width-(2*button.border_width_px);
    button_border_dims.y = button.height-(2*button.border_width_px);
    return button_border_dims;
}

/* Internal function to calculate the text position of a button */
Vector2 _get_button_text_pos(button_t button) {
    Vector2 button_text_pos = {0};
    button_text_pos.x = button.posx+((button.width-MeasureTextEx(button.text_font, button.text, button.font_sz, 0).x)/2);
    button_text_pos.y = button.posy+((button.height-MeasureTextEx(button.text_font, button.text, button.font_sz, 0).y)/2);
    return button_text_pos;
}

/* Checks if mouse cursor is on the button */
bool button_cursor_hover(button_t button) {
    Vector2 mouse_pos = GetMousePosition();
    if (mouse_pos.x > button.posx && mouse_pos.x < button.posx+button.width &&
        mouse_pos.y > button.posy && mouse_pos.y < button.posy+button.height) {
        return 1;
    }
    return 0;
}

/* Checks if mouse cursor is on cursor and returns an id of button it's currently 
 * on or -1 if mouse cursor is not on any buttons */
int32_t vbutton_cursor_hover(int count, ...) {
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; ++i) {
        button_t current_button = va_arg(ap, button_t);
        if (button_cursor_hover(current_button)) {
            return current_button.idx;
        }
    }
    va_end(ap);
    return -1;
}

/* Checks if mouse cursor is on cursor and returns an id of button it's currently 
 * on or -1 if mouse cursor is not on any buttons */
int32_t lbutton_cursor_hover(button_array_t buttons) {
    int32_t ret_val = -1;
    for (int i = 0; i < (buttons.rows*buttons.cols); ++i) {
        if (button_cursor_hover(buttons.buttons[i])) {
            ret_val = buttons.buttons[i].idx;
            break;
        }
    }
    return ret_val;
}

/* Function to adjuct positions and dimensions of every button in button array so that they will stretch horizotaly to the until_x value 
 * keeping spacing the same between buttons */
void stretch_button_array_horiz(button_array_t* button_array, uint32_t horizontal_spacing, uint32_t until_x) {
    uint32_t arr_sz = button_array->rows*button_array->cols;
    uint32_t horiz_sz = button_array->cols;
    /* Calculates the new button width */
    uint32_t new_button_width = (((until_x-button_array->origin_posx)-((horiz_sz-1)*horizontal_spacing))/horiz_sz);
    for (int i = 0; i < arr_sz; ++i) {
        /* Updates the position of every button that is not the first in a row and that it refrences the previous positions to change 
         * the current button position to make the distance between buttons the same */
        if (i % horiz_sz != 0) {
            button_array->buttons[i].posx = button_array->buttons[i-1].posx+new_button_width+horizontal_spacing;
            button_array->buttons[i].posy = button_array->buttons[i].posy;
        } 
        /* Set the width of every button to the new width */
        button_array->buttons[i].width = new_button_width;
        button_array->buttons[i].height = button_array->buttons[i].height;
    }
    button_array->horizontal_spacing = horizontal_spacing;
}

/* Function to adjuct positions and dimensions of every button in button array so that they will stretch vertiacaly to the until_y value 
 * keeping spacing the same between buttons */
void stretch_button_array_verti(button_array_t* button_array, uint32_t vertical_spacing, uint32_t until_y) {
    uint32_t arr_sz = button_array->rows*button_array->cols;
    uint32_t verti_sz = button_array->rows;
    /* Calculate the new height of every button */
    uint32_t new_button_height = (((until_y-button_array->origin_posy)-((verti_sz-1)*vertical_spacing))/verti_sz);
    uint32_t refrence_point = 0;
    /* Set the new verical position to the array original position */
    uint32_t new_pos_y = button_array->origin_posy;
    for (int i = 0; i < arr_sz; ++i) {
        /* Update the refrence_point */
        if (i % button_array->cols == 0 && i != 0) {
            refrence_point += new_button_height+vertical_spacing;
            new_pos_y = button_array->origin_posy+refrence_point;
        } 
        button_array->buttons[i].posx = button_array->buttons[i].posx;
        button_array->buttons[i].posy = new_pos_y;
        button_array->buttons[i].width = button_array->buttons[i].width;
        button_array->buttons[i].height = new_button_height;
    }
    button_array->vertical_spacing = vertical_spacing;
}

/* Function to check if button is pressed */
bool button_pressed(button_t button) {
    if (button_cursor_hover(button) && IsMouseButtonPressed(0)) {
        return 1;
    }
    return 0;
}

/* Function to checks if one of the buttons was pressed and if so it will return the id 
 * of the pressed button otherwise it will return -1 */
int32_t vbutton_pressed(int count, ...) {
    va_list ap;
    va_start(ap, count);
    for (int i = 0; i < count; ++i) {
        button_t current_button = va_arg(ap, button_t);
        if (button_pressed(current_button)) {
            return current_button.idx;
        }
    }
    va_end(ap);
    return -1;
}

/* Checks if a button in an button array was pressed and returns it's id otherwise -1 */
int32_t lbutton_pressed(button_array_t buttons) {
    int32_t ret_val = -1;
    for (int i = 0; i < (buttons.rows*buttons.cols); ++i) {
        if (button_pressed(buttons.buttons[i])) {
            ret_val = buttons.buttons[i].idx;
            break;
        }
    }
    return ret_val;
}

/* Free the buttons ONLY FOR BUTTON ARRAY normal buttons are not allocated on the heap */
void free_buttons(button_t* buttons) {
    free(buttons);
}

/* Custom strdup function */
char* rl_ui_strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* n_str = malloc(len);
    if (str) {
        memcpy(n_str, str, len);
    }
    return n_str;
}
