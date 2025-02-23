/* 
 * RlUI_elems.h is a simple header-only library that adds some ui elements to 
 * be used in raylib applications
 *                                                      GITHUB
 *     Created by: KryonicNapkin        - https://www.github.com/KryonicNapkin/rlui_elems
 *     Credit: raysan5's raygui library - https://www.github.com/raysan5/raygui
 */

/* 
 * TODO: make loading font efficient by loading font just once DONE
 *       make more ui elements like (Toggle, CheckBox, OptionList, Label)
 */

#ifndef RLUI_ELEMS_H_
#define RLUI_ELEMS_H_

#include <stdint.h>                    /* For type compatibility */

#ifdef INCLUDE_RAYLIB                  /* if you want to include raylib */
    #include "raylib.h"
#endif

typedef int64_t elem_idx;

typedef struct RluiRectangle {
    int x;
    int y;
    int width;
    int height;
} rlui_rect_t;

enum Elements {
    BUTTON = 0,
    BUTTON_GRID,
    TITLEBAR,
};

enum ElemState {
    NORMAL = 0,
    FOCUSED,
    CLICKED,
};
/* alignment of text */
enum TextAlignment {
    ALIGN_LEFT = 0,
    ALIGN_CENTER,
    ALIGN_RIGHT,
};
/* Padding */
struct PaddingH {
    uint32_t from_left;
    uint32_t from_right;
};

struct PaddingV {
    uint32_t from_top;
    uint32_t from_down;
};

struct ElemStyle {
    Color border_color_normal;
    Color base_color_normal;
    Color text_color_normal;
    Color border_color_focused;
    Color base_color_focused;
    Color text_color_focused;
    Color border_color_clicked;
    Color base_color_clicked;
    Color text_color_clicked;

    float font_size;

    int32_t border_width;
    Font (*fontloader)(void);

    enum TextAlignment text_alignment;
    struct PaddingH horizontal_padding;
    struct PaddingV vertical_padding;
};

/* Button attributes for the button_grid function */
enum ElemAttr {
    ATTR_BORDER_COLOR_NORMAL,
    ATTR_BASE_COLOR_NORMAL,
    ATTR_TEXT_COLOR_NORMAL,
    ATTR_BORDER_COLOR_FOCUSED,
    ATTR_BASE_COLOR_FOCUSED,
    ATTR_TEXT_COLOR_FOCUSED,
    ATTR_BORDER_COLOR_CLICKED,
    ATTR_BASE_COLOR_CLICKED,
    ATTR_TEXT_COLOR_CLICKED,
    ATTR_BORDER_WIDTH,
    ATTR_TEXT_ALIGNMENT,
    ATTR_HORIZ_PADDING,
    ATTR_VERTI_PADDING,
    ATTR_FONT,
};

/*------------------------------------------------------------*/
/*----------------------    ELEMENTS    ----------------------*/
/*------------------------------------------------------------*/

/* Button structure */
struct Button {
    elem_idx idx;
    rlui_rect_t bounds;
    char* text;
    Font font;
    struct ElemStyle style;
    enum ElemState state;
};

/* ButtonGrid structure */
struct ButtonGrid {
    struct Button* buttons;
    uint32_t rows;
    uint32_t cols;
    int32_t origin_posx, origin_posy;
    uint32_t horizontal_spacing;
    uint32_t vertical_spacing;
};

/* Titlebar structure */
struct TitleBar {
    elem_idx idx;
    rlui_rect_t bounds;
    char* text;
    Font font;
    struct ElemStyle style;
    enum ElemState state;
};

/* Typedefs */
typedef struct PaddingH      hpadding_t;
typedef struct PaddingV      vpadding_t;
typedef struct TitleBar      titlebar_t;
typedef struct ButtonGrid    button_grid_t;
typedef struct Button        button_t;
typedef enum TextAlignment   text_align_t;
typedef struct ElemStyle     style_t; 
typedef enum ElemAttr        elem_attr_t; 
typedef enum ElemState       elem_state_t; 

#define NO_HPADDING          (hpadding_t){0, 0}
#define NO_VPADDING          (vpadding_t){0, 0}

/* Default values for the global style */
#define BORDER_COLOR_NORMAL  (Color){0x28, 0x2C, 0x34, 0xFF}
#define BASE_COLOR_NORMAL    (Color){0x98, 0xC3, 0x79, 0xFF}
#define TEXT_COLOR_NORMAL    (Color){0x28, 0x2C, 0x34, 0xFF} 
#define BORDER_COLOR_FOCUSED (Color){0x28, 0x2C, 0x34, 0xFF} 
#define BASE_COLOR_FOCUSED   (Color){0x61, 0xAF, 0xEF, 0xFF}
#define TEXT_COLOR_FOCUSED   (Color){0x28, 0x2C, 0x34, 0xFF} 
#define BORDER_COLOR_CLICKED (Color){0x28, 0x2C, 0x34, 0xFF} 
#define BASE_COLOR_CLICKED   (Color){0xE5, 0xC0, 0x7B, 0xFF}
#define TEXT_COLOR_CLICKED   (Color){0x28, 0x2C, 0x34, 0xFF} 

#define BORDER_WIDTH         1

/* NOTE: For custom font loading you must initialize a new fontloader with you custom font loading function */
#define FONT_SIZE           10.0f                    /* Set font size */

/* variable to keep track of current element id */
int __current_elem_idx;

/* Default style for the elements */
#ifdef USE_ELEM_SPECIFIC_STYLES
    struct ElemStyle __button_style;
    struct ElemStyle __titlebar_style;
#else
    struct ElemStyle __global_style;
#endif

/*-------------------------------------------------------------*/
/*-----------------   Function declarations   -----------------*/
/*-------------------------------------------------------------*/

#ifdef USE_CUSTOM_FONT
    void set_font_loader_function(style_t* style, Font (*fontloader)(void));
#endif /* USE_CUSTOM_FONT */

/* Global style manipulation functions */
/* NOTE: These functions should be called before making of any element */
void set_new_global_style(style_t new_style);
void update_style(style_t* style, style_t new_style);

/* Element making functions */
button_t make_button(rlui_rect_t bounds, const char* text);
titlebar_t make_titlebar(rlui_rect_t bounds, const char* text);
/* NOTE: This function allocates memory for the buttons on the heap! 
 * You should call free_button_grid() after CloseWindow() */
button_grid_t make_button_grid(int32_t origin_posx, int32_t origin_posy, uint32_t rows, 
                               uint32_t cols, button_t orig_button, const char* text[], 
                               int32_t horizontal_spacing, int32_t vertical_spacing);

/* Attributes changing functions */
void set_button_style(button_t* button, enum ElemAttr attr, int32_t value);
void set_titlebar_style(titlebar_t* titlebar, enum ElemAttr attr, int32_t value);
void button_grid_attr(button_grid_t* grid, enum ElemAttr attr, int32_t value);
/* void set_button_font(button_t* button, Font (*fontloader)(void)); */

/* Button releated functions */
button_t copy_button(button_t button);

/* ButtonGrid alignment functions */
void stretch_button_grid_horiz(button_grid_t* button_grid, uint32_t horizontal_spacing, uint32_t until_x);
void stretch_button_grid_verti(button_grid_t* button_grid, uint32_t vertical_spacing, uint32_t until_y);

/* Rendering functions */
void render_button(button_t button);
void vrender_button(int count, ...);
void render_button_grid(button_grid_t buttons);
void render_titlebar(titlebar_t titlebar);

/* Internal functions for rendering */
Vector2 _get_button_with_border_pos(button_t button);
Vector2 _get_button_with_border_dims(button_t button);
Vector2 _get_button_text_pos(button_t button);

/* Element information getting functions */
elem_state_t get_button_state(button_t button);
elem_state_t get_button_grid_state(button_grid_t grid, elem_idx* changed_button_idx);
elem_state_t get_buttons_state(int count, elem_idx* changed_button_idx, ...);

/* Memory management functions */
void free_button_grid(button_grid_t button_grid);

/* Miscellaneous functions */
char* rlui_strdup(const char* str);
Color __int2color(int32_t color);

#ifdef RLUI_ELEMS_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int __current_elem_idx = 0;

/* STYLE DEFINITIONS OF THE ELEMENTS */
#ifndef USE_ELEM_SPECIFIC_STYLES
    struct ElemStyle __global_style = {
        .border_color_normal  = BORDER_COLOR_NORMAL,
        .base_color_normal    = BASE_COLOR_NORMAL,
        .text_color_normal    = TEXT_COLOR_NORMAL,
        .border_color_focused = BORDER_COLOR_FOCUSED,
        .base_color_focused   = BASE_COLOR_FOCUSED,
        .text_color_focused   = TEXT_COLOR_FOCUSED,
        .border_color_clicked = BORDER_COLOR_CLICKED,
        .base_color_clicked   = BASE_COLOR_CLICKED,
        .text_color_clicked   = TEXT_COLOR_CLICKED,
        .font_size            = FONT_SIZE,
        .border_width         = BORDER_WIDTH,
        .fontloader           = &GetFontDefault,
        .text_alignment       = ALIGN_CENTER,
        .horizontal_padding   = NO_HPADDING,
        .vertical_padding     = NO_VPADDING,
    };
#else
    struct ElemStyle __button_style = {
        .border_color_normal  = BORDER_COLOR_NORMAL,
        .base_color_normal    = BASE_COLOR_NORMAL,
        .text_color_normal    = TEXT_COLOR_NORMAL,
        .border_color_focused = BORDER_COLOR_FOCUSED,
        .base_color_focused   = BASE_COLOR_FOCUSED,
        .text_color_focused   = TEXT_COLOR_FOCUSED,
        .border_color_clicked = BORDER_COLOR_CLICKED,
        .base_color_clicked   = BASE_COLOR_CLICKED,
        .text_color_clicked   = TEXT_COLOR_CLICKED,
        .font_size            = FONT_SIZE,
        .border_width         = BORDER_WIDTH,
        .fontloader           = &GetFontDefault,
        .text_alignment       = ALIGN_CENTER,
        .horizontal_padding   = NO_HPADDING,
        .vertical_padding     = NO_VPADDING,
    };
    struct ElemStyle __titlebar_style = {
        .border_color_normal  = BORDER_COLOR_NORMAL,
        .base_color_normal    = BASE_COLOR_NORMAL,
        .text_color_normal    = TEXT_COLOR_NORMAL,
        .border_color_focused = BORDER_COLOR_FOCUSED,
        .base_color_focused   = BASE_COLOR_FOCUSED,
        .text_color_focused   = TEXT_COLOR_FOCUSED,
        .border_color_clicked = BORDER_COLOR_CLICKED,
        .base_color_clicked   = BASE_COLOR_CLICKED,
        .text_color_clicked   = TEXT_COLOR_CLICKED,
        .font_size            = FONT_SIZE,
        .border_width         = BORDER_WIDTH,
        .fontloader           = &GetFontDefault,
        .text_alignment       = ALIGN_CENTER,
        .horizontal_padding   = NO_HPADDING,
        .vertical_padding     = NO_VPADDING,
    };
#endif

#ifdef USE_ELEM_SPECIFIC_STYLES
    #define DEFAULT_BUTTON_STYLE   &__button_style
    #define DEFAULT_TITLEBAR_STYLE &__titlebar_style
#endif

#define DEFAULT_STYLE              &__global_style


/* NOTE: fontloader function should be generated using raylib's ExportFontAsCode() function
 *       and you should remove the check for IsGpuReady in the .h file for this function to 
 *       correctly load your desired font 
 */
#ifdef USE_CUSTOM_FONT
    void set_font_loader_function(style_t* style, Font (*fontloader)(void)) {
        style->fontloader = fontloader;
        style->font_size = fontloader().baseSize;
    }
#endif /* USE_CUSTOM_FONT */
/* Function for creation of a button */
button_t make_button(rlui_rect_t bounds, const char* text) {
    button_t btn = {0};
    /* Assaign to every button a unique id for pressing function */
    btn.idx = (!__current_elem_idx ? 0 : __current_elem_idx+1);
    btn.bounds.x = bounds.x;
    btn.bounds.y = bounds.y;
    btn.bounds.width = bounds.width;
    btn.bounds.height = bounds.height;

    /* Check if user didn't provided any title to the function */
    if (text == NULL) {
        btn.text = rlui_strdup("");
    } else {
        btn.text = rlui_strdup(text);
    }

    #ifdef USE_ELEM_SPECIFIC_STYLES
        btn.style = __button_style;
    #else 
        btn.style = __global_style;
    #endif /* BUTTON SPECIFIC STYLE */
    btn.font = btn.style.fontloader();
    btn.state = NORMAL;
    return btn;
}

/* Function to create a titlebar */
titlebar_t make_titlebar(rlui_rect_t bounds, const char* text) {
    titlebar_t titlebar = {0};
    /* Assaign an unique id to every created titlebar */
    titlebar.idx = (!__current_elem_idx ? 0 : __current_elem_idx+1);
    titlebar.bounds.x = bounds.x;
    titlebar.bounds.y = bounds.y;
    titlebar.bounds.width = bounds.width;
    titlebar.bounds.height = bounds.height;
    /* Check if no title was provided */
    if (text == NULL) {
        titlebar.text = rlui_strdup("");
    } else {
        titlebar.text = rlui_strdup(text);
    }

    #ifdef USE_ELEM_SPECIFIC_STYLES
        titlebar.style = __titlebar_style;
    #else 
        titlebar.style = __global_style;
    #endif /* TITLEBAR SPECIFIC STYLE */

    titlebar.font = titlebar.style.fontloader();
    titlebar.state = NORMAL;
    return titlebar;
}

button_grid_t make_button_grid(int32_t origin_posx, int32_t origin_posy, uint32_t rows, uint32_t cols, button_t orig_button, const char* text[], int32_t horizontal_spacing, int32_t vertical_spacing) {
    uint32_t num_of_buttons = rows*cols;
    button_grid_t button_grid;
    button_grid.buttons = (struct Button*)malloc(sizeof(button_t) * (rows*cols));

    /* Count the number of texts assaigned to every button in an array */
    int count = 0;
    char* fallback_name = NULL;
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
        fallback_name = rlui_strdup(text[count-1]);
    }
    /* Replicate the properties of the original button to every button desired to be created and assaign a specific id to it */
    for (int i = 0; i < num_of_buttons; ++i) {
        memmove(&button_grid.buttons[i], &orig_button, sizeof(button_t));
        button_grid.buttons[i].idx = __current_elem_idx + 1;
        __current_elem_idx += 1;
    }
    /* Calculate the position of every button relative to the provided horizontal and vertical spacing */
    int32_t vertical_step = 0;
    int32_t horizontal_step = 0;
    for (int n = 0; n < num_of_buttons; ++n) {
        button_grid.buttons[n].bounds.x = origin_posx+horizontal_step;
        button_grid.buttons[n].bounds.y = origin_posy+vertical_step;
        horizontal_step += (orig_button.bounds.width+horizontal_spacing);
        if ((n+1) % cols == 0) {
            vertical_step += (orig_button.bounds.height+vertical_spacing);
            horizontal_step = 0;
        }
    }
    /* Assaign text to every button */
    for (int x = 0; x < num_of_buttons; ++x) {
        if (x >= count || is_text_null) {
            button_grid.buttons[x].text = rlui_strdup(fallback_name);
        } else {
            button_grid.buttons[x].text = rlui_strdup(text[x]);
        }
    }
    /* Set other properties of a button array */
    button_grid.origin_posx = origin_posx;
    button_grid.origin_posy = origin_posy;
    button_grid.horizontal_spacing = horizontal_spacing;
    button_grid.vertical_spacing = vertical_spacing;
    button_grid.rows = rows;
    button_grid.cols = cols;
    /* Free the fallback name */
    if (fallback_name != NULL) {
        free(fallback_name);
    }
    return button_grid;
}

/* Function to change attributes of button */
void set_button_style(button_t* button, enum ElemAttr attr, int32_t value) {
    switch (attr) {
        case ATTR_BORDER_COLOR_NORMAL:
            button->style.border_color_normal = __int2color(value);
            break;
        case ATTR_BASE_COLOR_NORMAL:
            button->style.base_color_normal = __int2color(value);
            break;
        case ATTR_TEXT_COLOR_NORMAL:
            button->style.text_color_normal = __int2color(value);
            break;
        case ATTR_BORDER_COLOR_FOCUSED:
            button->style.border_color_focused = __int2color(value);
            break;
        case ATTR_BASE_COLOR_FOCUSED:
            button->style.base_color_focused = __int2color(value);
            break;
        case ATTR_TEXT_COLOR_FOCUSED:
            button->style.text_color_focused = __int2color(value);
            break;
        case ATTR_BORDER_COLOR_CLICKED:
            button->style.border_color_clicked = __int2color(value);
            break;
        case ATTR_BASE_COLOR_CLICKED:
            button->style.base_color_clicked = __int2color(value);
            break;
        case ATTR_TEXT_COLOR_CLICKED:
            button->style.text_color_clicked = __int2color(value);
            break;
        case ATTR_BORDER_WIDTH:
            button->style.border_width = value;
            break;
        case ATTR_TEXT_ALIGNMENT:
            button->style.text_alignment = (enum TextAlignment)value;
            break;
        case ATTR_HORIZ_PADDING:
            button->style.horizontal_padding.from_left = value;
            button->style.horizontal_padding.from_right = value;
            break;
        default:
            break;
    }
}

/* Function to change attributes of the titlebar */
void set_titlebar_style(titlebar_t* titlebar, enum ElemAttr attr, int32_t value) {
    switch (attr) {
        case ATTR_BORDER_COLOR_NORMAL:
            titlebar->style.border_color_normal = __int2color(value);
            break;
        case ATTR_BASE_COLOR_NORMAL:
            titlebar->style.base_color_normal = __int2color(value);
            break;
        case ATTR_TEXT_COLOR_NORMAL:
            titlebar->style.text_color_normal = __int2color(value);
            break;
        case ATTR_BORDER_COLOR_FOCUSED:
            titlebar->style.border_color_focused = __int2color(value);
            break;
        case ATTR_BASE_COLOR_FOCUSED:
            titlebar->style.base_color_focused = __int2color(value);
            break;
        case ATTR_TEXT_COLOR_FOCUSED:
            titlebar->style.text_color_focused = __int2color(value);
            break;
        case ATTR_BORDER_COLOR_CLICKED:
            titlebar->style.border_color_clicked = __int2color(value);
            break;
        case ATTR_BASE_COLOR_CLICKED:
            titlebar->style.base_color_clicked = __int2color(value);
            break;
        case ATTR_TEXT_COLOR_CLICKED:
            titlebar->style.text_color_clicked = __int2color(value);
            break;
        case ATTR_BORDER_WIDTH:
            titlebar->style.border_width = value;
            break;
        case ATTR_TEXT_ALIGNMENT:
            titlebar->style.text_alignment = (enum TextAlignment)value;
            break;
        case ATTR_HORIZ_PADDING:
            titlebar->style.horizontal_padding.from_left = value;
            titlebar->style.horizontal_padding.from_right = value;
            break;
        default:
            break;
    }
}

/* Function to change the attribute of every button in a button grid */
void button_grid_attr(button_grid_t* button_grid, enum ElemAttr attr, int32_t value) {
    for (int i = 0; i < (button_grid->rows*button_grid->cols); ++i) {
        set_button_style(&button_grid->buttons[i], attr, value);
    }
}

/* set button font */
/* void set_button_font(button_t* button, Font (*fontloader)(void)) {
    UnloadFont(button->font);
    button->font = fontloader();
    button->style.font_size = button->font.baseSize;
} */

/* Function to copy the attributes of a button to newly created button but updating it's id */
button_t copy_button(button_t button) {
    button_t new_button;
    memcpy(&new_button, &button, sizeof(button));
    new_button.idx = __current_elem_idx+1;
    __current_elem_idx += 1;
    return new_button;
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
            button_grid->buttons[i].bounds.y = button_grid->buttons[i].bounds.y;
        } 
        /* Set the width of every button to the new width */
        button_grid->buttons[i].bounds.width = new_button_width;
        button_grid->buttons[i].bounds.height = button_grid->buttons[i].bounds.height;
    }
    button_grid->horizontal_spacing = horizontal_spacing;
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
        button_grid->buttons[i].bounds.x = button_grid->buttons[i].bounds.x;
        button_grid->buttons[i].bounds.y = new_pos_y;
        button_grid->buttons[i].bounds.width = button_grid->buttons[i].bounds.width;
        button_grid->buttons[i].bounds.height = new_button_height;
    }
    button_grid->vertical_spacing = vertical_spacing;
}

/* Function for rendering a button */
void render_button(button_t button) {
    enum ElemState state = get_button_state(button);
    if (state == NORMAL) {
        DrawRectangle(button.bounds.x, button.bounds.y, button.bounds.width, button.bounds.height, button.style.border_color_normal);
        DrawRectangleV(_get_button_with_border_pos(button), _get_button_with_border_dims(button), button.style.base_color_normal);
        DrawTextEx(button.font, button.text, _get_button_text_pos(button), (float)button.style.font_size, 0, button.style.text_color_normal);
    } else if (state == CLICKED) {
        DrawRectangle(button.bounds.x, button.bounds.y, button.bounds.width, button.bounds.height, button.style.border_color_clicked);
        DrawRectangleV(_get_button_with_border_pos(button), _get_button_with_border_dims(button), button.style.base_color_clicked);
        DrawTextEx(button.font, button.text, _get_button_text_pos(button), (float)button.style.font_size, 0, button.style.text_color_clicked);
    } else if (state == FOCUSED) {
        DrawRectangle(button.bounds.x, button.bounds.y, button.bounds.width, button.bounds.height, button.style.border_color_focused);
        DrawRectangleV(_get_button_with_border_pos(button), _get_button_with_border_dims(button), button.style.base_color_focused);
        DrawTextEx(button.font, button.text, _get_button_text_pos(button), (float)button.style.font_size, 0, button.style.text_color_focused);
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
void render_button_grid(button_grid_t buttons) {
    for (int i = 0; i < (buttons.cols*buttons.rows); ++i) {
        render_button(buttons.buttons[i]);
    }
}

/* Function to render a titlebar */
void render_titlebar(titlebar_t titlebar) {
    Vector2 text_pos = {0};
    Vector2 text_dims = MeasureTextEx(titlebar.font, titlebar.text, titlebar.style.font_size, 0);
    /* Calculates the distance from the sides */
    switch (titlebar.style.text_alignment) {
        case ALIGN_LEFT:
            text_pos.x = titlebar.bounds.x+titlebar.style.horizontal_padding.from_left;
            text_pos.y = titlebar.bounds.y+((titlebar.bounds.height-text_dims.y)/2);
            break;
        case ALIGN_CENTER:
            text_pos.x = titlebar.bounds.x+((titlebar.bounds.width-text_dims.x)/2);
            text_pos.y = titlebar.bounds.y+((titlebar.bounds.height-text_dims.y)/2);
            break;
        case ALIGN_RIGHT:
            text_pos.x = titlebar.bounds.width-text_dims.x-titlebar.style.horizontal_padding.from_right;
            text_pos.y = titlebar.bounds.y+((titlebar.bounds.height-text_dims.y)/2);
            break;
        default:
            break;
    }
    DrawRectangle(titlebar.bounds.x, titlebar.bounds.y, titlebar.bounds.width, titlebar.bounds.height, titlebar.style.border_color_normal);
    DrawTextEx(titlebar.font, titlebar.text, text_pos, titlebar.style.font_size, 0, titlebar.style.text_color_normal);
}

/* Internal function to calculate the position of the boundsagle relative to border width */
Vector2 _get_button_with_border_pos(button_t button) {
    Vector2 button_border_pos = {0};
    button_border_pos.x = button.bounds.x+button.style.border_width;
    button_border_pos.y = button.bounds.y+button.style.border_width;
    return button_border_pos;
}

/* Internal functin to calculate the dimensions of the boundsagle relative to border width */
Vector2 _get_button_with_border_dims(button_t button) {
    Vector2 button_border_dims = {0};
    button_border_dims.x = button.bounds.width-(2*button.style.border_width);
    button_border_dims.y = button.bounds.height-(2*button.style.border_width);
    return button_border_dims;
}

/* Internal function to calculate the text position of a button */
Vector2 _get_button_text_pos(button_t button) {
    Vector2 button_text_pos = {0};
    button_text_pos.x = button.bounds.x+((button.bounds.width-MeasureTextEx(button.font, button.text, button.style.font_size, 0).x)/2);
    button_text_pos.y = button.bounds.y+((button.bounds.height-MeasureTextEx(button.font, button.text, button.style.font_size, 0).y)/2);
    return button_text_pos;
}

elem_state_t get_button_state(button_t button) {
    elem_state_t state;
    Rectangle button_bounds = {
        .x = (float)button.bounds.x,
        .y = (float)button.bounds.y,
        .width = (float)button.bounds.width,
        .height = (float)button.bounds.height,
    };
    bool hover = CheckCollisionPointRec(GetMousePosition(), button_bounds);
    state = NORMAL;
    if (hover) state = FOCUSED;
    if (hover && IsMouseButtonDown(0) && IsMouseButtonPressed(0)) state = CLICKED;
    return state;
}

elem_state_t get_button_grid_state(button_grid_t button_grid, elem_idx* changed_button_idx) {
    elem_state_t state;
    for (uint32_t i = 0; i < button_grid.rows*button_grid.cols; ++i) {
        state = get_button_state(button_grid.buttons[i]);
        if (state != NORMAL) {
            *changed_button_idx = button_grid.buttons[i].idx;
            return state;
        }
    }
}

elem_state_t get_buttons_state(int count, elem_idx* changed_button_idx, ...) {
    elem_state_t state;
    va_list ap;
    va_start(ap, changed_button_idx);
    for (int i = 0; i < count; ++i) {
        button_t button = va_arg(ap, button_t);
        state = get_button_state(button);
        if (state != NORMAL) {
            *changed_button_idx = button.idx;
            return state;
        }
    }
    va_end(ap);
}

/* */
void free_button_grid(button_grid_t button_grid) {
    free(button_grid.buttons);
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

Color __int2color(int32_t color) {
    return (Color) {
        .r = (unsigned char)((color >> 24) & 0xFF),
        .g = (unsigned char)((color >> 16) & 0xFF),
        .b = (unsigned char)((color >> 8) & 0xFF),
        .a = (unsigned char)(color & 0xFF),
    };
}
#endif /* RLUI_ELEMS_IMPLEMENTATION */
#endif /* RLUI_ELEMS_H_ */
