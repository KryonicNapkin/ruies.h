/* 
 * RlUI_elems.h is a simple header-only library that adds some ui elements to 
 * be used in raylib applications
 *                                                      GITHUB
 *     Created by: KryonicNapkin        - https://www.github.com/KryonicNapkin/rlui_elems
 *     Credit: raysan5's raygui library - https://www.github.com/raysan5/raygui
 */

/*  TODO: make more ui elements like (CheckBox, OptionList, Label) */

#ifndef RLUI_ELEMS_H_
#define RLUI_ELEMS_H_

/* #define USE_CUSTOM_FONT
#define RLUI_ELEMS_IMPLEMENTATION
#include "raylib.h" */

#include <stdint.h>                    /* For type compatibility */

typedef int64_t elem_idx;

typedef struct ElemBounds {
    int x;
    int y;
    int width;
    int height;
} elem_bounds_t;

enum Elements {
    BUTTON = 0,
    BUTTON_GRID,
    TITLEBAR,
    TOGGLE,
    ALL_ELEMENTS,
};

enum ElemState {
    NORMAL = 0,
    FOCUSED,
    CLICKED,
    ALL_STATES,
};
/* alignment of text */
enum TextAlignment {
    ALIGN_LEFT = 0,
    ALIGN_CENTER,
    ALIGN_RIGHT,
};

#define MAX_ELEMENTS_COUNT     4
#define MAX_ELEMENT_ATTRIBUTES 20
struct GlobalStyle {
    uint32_t elem_styles[MAX_ELEMENTS_COUNT][MAX_ELEMENT_ATTRIBUTES];
    Font (*fontloader[MAX_ELEMENTS_COUNT])(void);
};

/* Button attributes for the button_grid function */
enum ElemAttr {
    ATTR_BORDER_COLOR_NORMAL = 0,
    ATTR_BASE_COLOR_NORMAL,
    ATTR_TEXT_COLOR_NORMAL,

    ATTR_BORDER_COLOR_FOCUSED,
    ATTR_BASE_COLOR_FOCUSED,
    ATTR_TEXT_COLOR_FOCUSED,

    ATTR_BORDER_COLOR_CLICKED,
    ATTR_BASE_COLOR_CLICKED,
    ATTR_TEXT_COLOR_CLICKED,

    ATTR_FONT_SIZE,
    ATTR_BORDER_WIDTH,
    ATTR_TEXT_ALIGNMENT,

    ATTR_LEFT_PADDING,
    ATTR_RIGHT_PADDING,
    ATTR_TOP_PADDING,
    ATTR_BOTTOM_PADDING,

    ATTR_TITLEBAR_TOP_BORDER_WIDTH,
    ATTR_TITLEBAR_BOTTOM_BORDER_WIDTH,
    ATTR_TITLEBAR_LEFT_BORDER_WIDTH,
    ATTR_TITLEBAR_RIGHT_BORDER_WIDTH,
};

/*------------------------------------------------------------*/
/*----------------------    ELEMENTS    ----------------------*/
/*------------------------------------------------------------*/

/* Button structure */
struct Button {
    elem_idx idx;
    elem_bounds_t bounds;
    char* text;
    Font font;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
    enum ElemState state;
};

/* ButtonGrid structure */
struct ButtonGrid {
    struct Button* buttons;
    Font font;
    uint32_t rows;
    uint32_t cols;
    int32_t origin_posx, origin_posy;
    uint32_t horizontal_spacing;
    uint32_t vertical_spacing;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
};

/* Titlebar structure */
struct TitleBar {
    elem_idx idx;
    elem_bounds_t bounds;
    char* text;
    Font font;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
    enum ElemState state;
};

/* Toggle structure */
struct Toggle {
    elem_idx idx;
    elem_bounds_t bounds;
    char* text;
    Font font;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
    enum ElemState state;
};

/*------------------------------------------------------------*/
/*----------------------    TYPEDEFS    ----------------------*/
/*------------------------------------------------------------*/

typedef struct Button        button_t;
typedef struct ButtonGrid    button_grid_t;
typedef struct TitleBar      titlebar_t;
typedef struct Toggle        toggle_t;
typedef enum TextAlignment   text_align_t;
typedef enum ElemAttr        elem_attr_t; 
typedef enum ElemState       elem_state_t; 

/* Default values for the global style */
#define BORDER_COLOR_NORMAL  0x282C34FF
#define BASE_COLOR_NORMAL    0x98C379FF
#define TEXT_COLOR_NORMAL    0x282C34FF 
#define BORDER_COLOR_FOCUSED 0x282C34FF 
#define BASE_COLOR_FOCUSED   0x61AFEFFF
#define TEXT_COLOR_FOCUSED   0x282C34FF 
#define BORDER_COLOR_CLICKED 0x282C34FF 
#define BASE_COLOR_CLICKED   0xE5C07BFF
#define TEXT_COLOR_CLICKED   0x282C34FF 

#define __BORDER_WIDTH       1

/* NOTE: For custom font loading you must initialize a new fontloader with you custom font loading function */
#define DEFAULT_FONTLOADER   &GetFontDefault
#define __FONT_SIZE          10                      /* Set font size */

/* variable to keep track of current element id */
int __current_elem_idx;

/* Default style for the elements */
struct GlobalStyle __style;

/*-------------------------------------------------------------*/
/*-----------------   FUNCTION DECLARATIONS   -----------------*/
/*-------------------------------------------------------------*/

#ifdef USE_CUSTOM_FONT
    void set_font_loader_function(enum Elements elem, Font (*fontloader)(void));
#endif /* USE_CUSTOM_FONT */

/* Element making functions */
button_t make_button(elem_bounds_t bounds, const char* text);
titlebar_t make_titlebar(elem_bounds_t bounds, const char* text);
/* NOTE: This function allocates memory for the buttons on the heap! 
 * You should call free_button_grid() after CloseWindow() */
button_grid_t make_button_grid(uint32_t posx, uint32_t posy, uint32_t rows, uint32_t cols,
                               elem_bounds_t sample_bounds, const char* text[],
                               uint32_t horizontal_spacing, uint32_t vertical_spacing);
toggle_t make_toggle(elem_bounds_t bounds, const char* text);

/* Style functions */
uint32_t* get_style(enum Elements elem, int* size);
uint32_t get_style_value(enum Elements elem, enum ElemAttr attr);

/* Attributes changing functions */
void set_button_style(button_t* button, enum ElemAttr attr, uint32_t value);
void set_titlebar_style(titlebar_t* titlebar, enum ElemAttr attr, uint32_t value);
void button_grid_attr(button_grid_t* grid, enum ElemAttr attr, uint32_t value);
void set_toggle_style(toggle_t* toggle, enum ElemAttr attr, uint32_t value);
void set_allstyle(enum Elements elem, enum ElemAttr attr, uint32_t value);
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
void render_toggle(toggle_t toggle);

/* Internal functions for rendering */
Vector2 __get_elem_with_border_pos(elem_bounds_t bounds, uint32_t border_width);
Vector2 __get_elem_with_border_dims(elem_bounds_t bounds, uint32_t border_width);
Vector2 __get_elem_text_pos(elem_bounds_t bounds, Font font, const char* text);

/* Element state handling getting functions */
void watch_button_state(button_t* button, elem_state_t active_on, bool* active);
void watch_button_grid_state(button_grid_t* button_grid, elem_idx* changed_button_idx, elem_state_t active_on, bool* active);
void watch_titlebar_state(titlebar_t* titlebar, elem_state_t active_on, bool* active);
void watch_toggle_state(toggle_t* toggle, bool* active);

void watch_many_buttons_state(int count, elem_state_t active_on, bool* active, elem_idx* changed_button_idx, ...);

int get_button_index_in_grid_by_its_idx(button_grid_t button_grid, elem_idx idx);

/* Memory management functions */
void free_button_grid(button_grid_t button_grid);

/* Miscellaneous functions */
char* rlui_strdup(const char* str);
Color __int2color(uint32_t color);

#ifdef RLUI_ELEMS_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int __current_elem_idx = 0;

/* STYLE DEFINITIONS OF THE ELEMENTS */
struct GlobalStyle __style = {
    .elem_styles = {
        /* Button */
        {
            BORDER_COLOR_NORMAL,  BASE_COLOR_NORMAL,   TEXT_COLOR_NORMAL, 
            BORDER_COLOR_FOCUSED, BASE_COLOR_FOCUSED,  TEXT_COLOR_FOCUSED,
            BORDER_COLOR_CLICKED, BASE_COLOR_CLICKED,  TEXT_COLOR_CLICKED,
            __FONT_SIZE, __BORDER_WIDTH, ALIGN_CENTER, 
            0, 0, 0, 0
        }, 
        /* Button Grid */
        { 
            BORDER_COLOR_NORMAL, BASE_COLOR_NORMAL, TEXT_COLOR_NORMAL, 
            BORDER_COLOR_FOCUSED, BASE_COLOR_FOCUSED, TEXT_COLOR_FOCUSED,
            BORDER_COLOR_CLICKED, BASE_COLOR_CLICKED, TEXT_COLOR_CLICKED,
            __FONT_SIZE, __BORDER_WIDTH, ALIGN_CENTER, 
            0, 0, 0, 0
        }, 
        /* Titlebar */
        { 
            BORDER_COLOR_NORMAL, BASE_COLOR_NORMAL, TEXT_COLOR_NORMAL, 
            BORDER_COLOR_FOCUSED, BASE_COLOR_FOCUSED, TEXT_COLOR_FOCUSED,
            BORDER_COLOR_CLICKED, BASE_COLOR_CLICKED, TEXT_COLOR_CLICKED,
            __FONT_SIZE, __BORDER_WIDTH, ALIGN_LEFT, 
            10, 0, 0, 0,      0, 0, 0, 0
        },
        /* TOGGLE */
        { 
            BORDER_COLOR_NORMAL, BASE_COLOR_NORMAL, TEXT_COLOR_NORMAL, 
            BORDER_COLOR_FOCUSED, BASE_COLOR_FOCUSED, TEXT_COLOR_FOCUSED,
            BORDER_COLOR_CLICKED, BASE_COLOR_CLICKED, TEXT_COLOR_CLICKED,
            __FONT_SIZE, __BORDER_WIDTH, ALIGN_CENTER, 
            10, 0, 0, 0
        },
    }, 
    .fontloader = {DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER},
};

/* NOTE: fontloader function should be generated using raylib's ExportFontAsCode() function
 *       and you should remove the check for IsGpuReady in the .h file for this function to 
 *       correctly load your desired font 
 */
#ifdef USE_CUSTOM_FONT
    void set_font_loader_function(enum Elements elem, Font (*fontloader)(void)) {
        Font font = fontloader();
        if (elem == ALL_ELEMENTS) {
            for (int i = 0; i < MAX_ELEMENTS_COUNT; ++i) {
                __style.fontloader[i] = fontloader;
                __style.elem_styles[i][ATTR_FONT_SIZE] = font.baseSize;
            }
        } else { 
            __style.fontloader[elem] = fontloader;
            __style.elem_styles[elem][ATTR_FONT_SIZE] = font.baseSize;
        }
    }
#endif /* USE_CUSTOM_FONT */

/* Function for creation of a button */
button_t make_button(elem_bounds_t bounds, const char* text) {
    button_t btn = {0};
    /* Assaign a unique id to a button */
    btn.idx = (!__current_elem_idx ? 0 : __current_elem_idx+1);
    __current_elem_idx += 1;
    btn.bounds = bounds;

    /* Check if user didn't provided any title to the function */
    if (text == NULL) {
        btn.text = rlui_strdup("");
    } else {
        btn.text = rlui_strdup(text);
    }

    memcpy(&btn.style, &__style.elem_styles[BUTTON], sizeof(uint32_t)*MAX_ELEMENT_ATTRIBUTES);
    btn.font = __style.fontloader[BUTTON]();
    btn.state = NORMAL;
    return btn;
}

/* Function to create a titlebar */
titlebar_t make_titlebar(elem_bounds_t bounds, const char* text) {
    titlebar_t titlebar = {0};
    /* Assaign an unique id to every created titlebar */
    titlebar.idx = (!__current_elem_idx ? 0 : __current_elem_idx+1);
    __current_elem_idx += 1;
    titlebar.bounds = bounds;
    /* Check if no title was provided */
    if (text == NULL) {
        titlebar.text = rlui_strdup("");
    } else {
        titlebar.text = rlui_strdup(text);
    }

    memcpy(&titlebar.style, &__style.elem_styles[TITLEBAR], sizeof(uint32_t)*MAX_ELEMENT_ATTRIBUTES);
    titlebar.font = __style.fontloader[TITLEBAR]();
    titlebar.state = NORMAL;
    return titlebar;
}

button_grid_t make_button_grid(uint32_t posx, uint32_t posy, uint32_t rows, uint32_t cols, elem_bounds_t sample_bounds, const char* text[], uint32_t horizontal_spacing, uint32_t vertical_spacing) {
    uint32_t num_of_buttons = rows*cols;
    button_grid_t button_grid;
    button_grid.buttons = (struct Button*)malloc(sizeof(button_t) * (rows*cols));

    /* Count the number of texts assaigned to every button in an array */
    uint32_t count = 0;
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
    button_grid.font = __style.fontloader[BUTTON_GRID]();
    memcpy(&button_grid.style, &__style.elem_styles[BUTTON_GRID], sizeof(uint32_t)*MAX_ELEMENT_ATTRIBUTES);
    for (uint32_t i = 0; i < num_of_buttons; ++i) {
        button_grid.buttons[i].font = button_grid.font;
        button_grid.buttons[i].bounds = sample_bounds;
        memcpy(&button_grid.buttons[i].style, &button_grid.style, sizeof(uint32_t)*MAX_ELEMENT_ATTRIBUTES);
        button_grid.buttons[i].idx = __current_elem_idx + 1;
        __current_elem_idx += 1;
    }
    /* Calculate the position of every button relative to the provided horizontal and vertical spacing */
    int32_t vertical_step = 0;
    int32_t horizontal_step = 0;
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
        if (x >= count || is_text_null) {
            button_grid.buttons[x].text = rlui_strdup(fallback_name);
        } else {
            button_grid.buttons[x].text = rlui_strdup(text[x]);
        }
    }
    /* Set other properties of a button array */
    button_grid.origin_posx = posx;
    button_grid.origin_posy = posy;
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

toggle_t make_toggle(elem_bounds_t bounds, const char* text) {
    toggle_t toggle = {0};
    toggle.idx = (!__current_elem_idx ? 0 : __current_elem_idx+1);
    __current_elem_idx += 1;
    toggle.bounds = bounds;

    if (text == NULL) {
        toggle.text = rlui_strdup("");
    } else {
        toggle.text = rlui_strdup(text);
    }

    memcpy(&toggle.style, &__style.elem_styles[TOGGLE], sizeof(uint32_t)*MAX_ELEMENT_ATTRIBUTES);
    toggle.font = __style.fontloader[TOGGLE]();
    toggle.state = NORMAL;
    return toggle;
}

uint32_t* get_style(enum Elements elem, int* size) {
    if (elem == ALL_ELEMENTS) {
        *size = -1;
        return NULL;
    }
    *size = sizeof(__style.elem_styles[elem])/sizeof(__style.elem_styles[elem][0]);
    return __style.elem_styles[elem];
}

uint32_t get_style_value(enum Elements elem, enum ElemAttr attr) {
    if (elem == ALL_ELEMENTS) return -1;
    return __style.elem_styles[elem][attr];
}
/* Function to change attributes of button */
void set_button_style(button_t* button, enum ElemAttr attr, uint32_t value) {
    button->style[attr] = value;
}

/* Function to change attributes of the titlebar */
void set_titlebar_style(titlebar_t* titlebar, enum ElemAttr attr, uint32_t value) {
    titlebar->style[attr] = value;
}

/* Function to change the attribute of every button in a button grid */
void button_grid_attr(button_grid_t* button_grid, enum ElemAttr attr, uint32_t value) {
    for (int i = 0; i < (button_grid->rows*button_grid->cols); ++i) {
        set_button_style(&button_grid->buttons[i], attr, value);
    }
}

void set_toggle_style(toggle_t* toggle, enum ElemAttr attr, uint32_t value) {
    toggle->style[attr] = value;
}

void set_allstyle(enum Elements elem, enum ElemAttr attr, uint32_t value) {
    if (elem == ALL_ELEMENTS) {
        for (int i = 0; i < MAX_ELEMENTS_COUNT; ++i) {
            __style.elem_styles[i][attr] = value;
        }
    } else {
        __style.elem_styles[elem][attr] = value;
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
    watch_button_state(&button, ALL_STATES, NULL);
    Color border_color, base_color, text_color;
    Vector2 border_bounds[2] = {
        /* Position */
        __get_elem_with_border_pos(button.bounds, button.style[ATTR_BORDER_WIDTH]),
        /* Dimension */
        __get_elem_with_border_dims(button.bounds, button.style[ATTR_BORDER_WIDTH]),
    };
    Vector2 text_pos = __get_elem_text_pos(button.bounds, button.font, button.text);
    if (button.state == NORMAL) {
        border_color = __int2color(button.style[ATTR_BORDER_COLOR_NORMAL]);
        base_color = __int2color(button.style[ATTR_BASE_COLOR_NORMAL]);
        text_color = __int2color(button.style[ATTR_TEXT_COLOR_NORMAL]);
    } else if (button.state == FOCUSED) {
        border_color = __int2color(button.style[ATTR_BORDER_COLOR_FOCUSED]);
        base_color = __int2color(button.style[ATTR_BASE_COLOR_FOCUSED]);
        text_color = __int2color(button.style[ATTR_TEXT_COLOR_FOCUSED]);
    } else if (button.state == CLICKED) {
        border_color = __int2color(button.style[ATTR_BORDER_COLOR_CLICKED]);
        base_color = __int2color(button.style[ATTR_BASE_COLOR_CLICKED]);
        text_color = __int2color(button.style[ATTR_TEXT_COLOR_CLICKED]);
    }
    /* Drawing */
    DrawRectangle(button.bounds.x, button.bounds.y, button.bounds.width, button.bounds.height, border_color);
    DrawRectangleV(border_bounds[0], border_bounds[1], base_color);
    DrawTextEx(button.font, button.text, text_pos, (float)button.style[ATTR_FONT_SIZE], 0, text_color);
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
    Vector2 text_dims = MeasureTextEx(titlebar.font, titlebar.text, (float)titlebar.style[ATTR_FONT_SIZE], 0);
    /* Calculates the distance from the sides */
    switch (titlebar.style[ATTR_TEXT_ALIGNMENT]) {
        case ALIGN_LEFT:
            text_pos.x = (float)(titlebar.bounds.x+titlebar.style[ATTR_LEFT_PADDING]);
            text_pos.y = (float)(titlebar.bounds.y+((titlebar.bounds.height-text_dims.y)/2.0f));
            break;
        case ALIGN_CENTER:
            text_pos.x = (float)(titlebar.bounds.x+((titlebar.bounds.width-text_dims.x)/2.0f));
            text_pos.y = (float)(titlebar.bounds.y+((titlebar.bounds.height-text_dims.y)/2.0f));
            break;
        case ALIGN_RIGHT:
            text_pos.x = (float)(titlebar.bounds.width-text_dims.x-titlebar.style[ATTR_RIGHT_PADDING]);
            text_pos.y = (float)(titlebar.bounds.y+((titlebar.bounds.height-text_dims.y)/2.0f));
            break;
        default:
            break;
    }
    int64_t left_border_width = titlebar.style[ATTR_TITLEBAR_LEFT_BORDER_WIDTH];
    int64_t right_border_width = titlebar.style[ATTR_TITLEBAR_RIGHT_BORDER_WIDTH];
    int64_t top_border_width = titlebar.style[ATTR_TITLEBAR_TOP_BORDER_WIDTH];
    int64_t bottom_border_width = titlebar.style[ATTR_TITLEBAR_BOTTOM_BORDER_WIDTH];

    Color border_color_normal = __int2color(titlebar.style[ATTR_BORDER_COLOR_NORMAL]);

    DrawRectangle(titlebar.bounds.x, titlebar.bounds.y, titlebar.bounds.width, titlebar.bounds.height, __int2color(titlebar.style[ATTR_BASE_COLOR_NORMAL]));
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
    DrawTextEx(titlebar.font, titlebar.text, text_pos, (float)titlebar.style[ATTR_FONT_SIZE], 0, __int2color(titlebar.style[ATTR_TEXT_COLOR_NORMAL]));
}

void render_toggle(toggle_t toggle) {
    watch_toggle_state(&toggle, NULL);
    Color border_color, base_color, text_color;
    Vector2 border_bounds[2] = {
        /* Position */
        __get_elem_with_border_pos(toggle.bounds, toggle.style[ATTR_BORDER_WIDTH]),
        /* Dimension */
        __get_elem_with_border_dims(toggle.bounds, toggle.style[ATTR_BORDER_WIDTH]),
    };
    Vector2 text_pos = __get_elem_text_pos(toggle.bounds, toggle.font, toggle.text);
    if (toggle.state == NORMAL) {
        border_color = __int2color(toggle.style[ATTR_BORDER_COLOR_NORMAL]);
        base_color = __int2color(toggle.style[ATTR_BASE_COLOR_NORMAL]);
        text_color = __int2color(toggle.style[ATTR_TEXT_COLOR_NORMAL]);
    } else if (toggle.state == FOCUSED) {
        border_color = __int2color(toggle.style[ATTR_BORDER_COLOR_FOCUSED]);
        base_color = __int2color(toggle.style[ATTR_BASE_COLOR_FOCUSED]);
        text_color = __int2color(toggle.style[ATTR_TEXT_COLOR_FOCUSED]);
    } else if (toggle.state == CLICKED) {
        border_color = __int2color(toggle.style[ATTR_BORDER_COLOR_CLICKED]);
        base_color = __int2color(toggle.style[ATTR_BASE_COLOR_CLICKED]);
        text_color = __int2color(toggle.style[ATTR_TEXT_COLOR_CLICKED]);
    }
    /* Drawing */
    DrawRectangle(toggle.bounds.x, toggle.bounds.y, toggle.bounds.width, toggle.bounds.height, border_color);
    DrawRectangleV(border_bounds[0], border_bounds[1], base_color);
    DrawTextEx(toggle.font, toggle.text, text_pos, (float)toggle.style[ATTR_FONT_SIZE], 0, text_color);
}

/* Internal function to calculate the position of the boundsagle relative to border width */
Vector2 __get_elem_with_border_pos(elem_bounds_t bounds, uint32_t border_width) {
    Vector2 border_pos = {0};
    border_pos.x = bounds.x+border_width;
    border_pos.y = bounds.y+border_width;
    return border_pos;
}

/* Internal functin to calculate the dimensions of the boundsagle relative to border width */
Vector2 __get_elem_with_border_dims(elem_bounds_t bounds, uint32_t border_width) {
    Vector2 border_dims = {0};
    border_dims.x = bounds.width-(2*border_width);
    border_dims.y = bounds.height-(2*border_width);
    return border_dims;
}

/* Internal function to calculate the text position of a button */
Vector2 __get_elem_text_pos(elem_bounds_t bounds, Font font, const char* text) {
    Vector2 text_pos = {0};
    text_pos.x = bounds.x+((bounds.width-MeasureTextEx(font, text, font.baseSize, 0).x)/2);
    text_pos.y = bounds.y+((bounds.height-MeasureTextEx(font, text, font.baseSize, 0).y)/2);
    return text_pos;
}

void watch_button_state(button_t* button, elem_state_t active_on, bool* active) {
    Rectangle button_bounds = {
        .x = (float)button->bounds.x,
        .y = (float)button->bounds.y,
        .width = (float)button->bounds.width,
        .height = (float)button->bounds.height,
    };
    bool hover = CheckCollisionPointRec(GetMousePosition(), button_bounds);
    bool clicked = IsMouseButtonDown(0);
    if (active_on == ALL_STATES || active == NULL) {
        if (!hover && !clicked) button->state = NORMAL;
        else if (hover && !clicked) button->state = FOCUSED;
        else if (hover && clicked) button->state = CLICKED;
    } else if (!hover && !clicked) {
        if (button->state != NORMAL) *active = false;
        else if (active_on == NORMAL) *active = true;
        button->state = NORMAL;
    } else if (hover && !clicked) {
        if (button->state != FOCUSED) *active = false;
        else if (active_on == FOCUSED) *active = true;
        button->state = FOCUSED;
    } else if (hover && clicked) {
        if (button->state != CLICKED) *active = false;
        else if (active_on == CLICKED) *active = true;
        button->state = CLICKED;
    }
}

void watch_button_grid_state(button_grid_t* button_grid, elem_idx* changed_button_idx, elem_state_t active_on, bool* active) {
    for (uint32_t i = 0; i < button_grid->rows*button_grid->cols; ++i) {
        watch_button_state(&button_grid->buttons[i], active_on, NULL);
        if (button_grid->buttons[i].state == active_on) {
            *changed_button_idx = button_grid->buttons[i].idx;
            *active = true;
            break;
        } else {
            *changed_button_idx = -1;
            *active = false;
        }
    }
}

void watch_toggle_state(toggle_t* toggle, bool* active) {
    Rectangle toggle_bounds = {
        .x = (float)toggle->bounds.x,
        .y = (float)toggle->bounds.y,
        .width = (float)toggle->bounds.width,
        .height = (float)toggle->bounds.height,
    };
    bool hover = CheckCollisionPointRec(GetMousePosition(), toggle_bounds);
    bool clicked = IsMouseButtonPressed(0);
    if (active != NULL) {
        if (!hover && !clicked && toggle->state != CLICKED) {
            toggle->state = NORMAL;
            *active = false;
        } else if (hover && !clicked && toggle->state != CLICKED) {
            toggle->state = FOCUSED;
            *active = false;
        } else if (hover && clicked && toggle->state != CLICKED) {
            toggle->state = CLICKED;
            *active = true;
        } else if (hover && clicked && toggle->state == CLICKED) {
            toggle->state = NORMAL;
            *active = false;
        }
    } else {
        if (!hover && !clicked && toggle->state != CLICKED) toggle->state = NORMAL;
        else if (hover && !clicked && toggle->state != CLICKED) toggle->state = FOCUSED;
        else if (hover && clicked && toggle->state != CLICKED) toggle->state = CLICKED;
    }
}

void watch_many_buttons_state(int count, elem_state_t active_on, bool* active, elem_idx* changed_button_idx, ...) {
    va_list ap;
    va_start(ap, changed_button_idx);
    for (int i = 0; i < count; ++i) {
        button_t button = va_arg(ap, button_t);
        watch_button_state(&button, active_on, NULL);
        if (button.state == active_on) {
            *changed_button_idx = button.idx;
            *active = true;
            break;
        } else {
            *changed_button_idx = -1;
            *active = false;
        }
    }
    va_end(ap);
}

int get_button_index_in_grid_by_its_idx(button_grid_t button_grid, elem_idx idx) {
    for (uint32_t i = 0; i < button_grid.cols*button_grid.rows; ++i) {
        if (button_grid.buttons[i].idx == idx) return i;
    }
    return -1;
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

Color __int2color(uint32_t color) {
    return (Color) {
        .r = (unsigned char)((color >> 24) & 0xFF),
        .g = (unsigned char)((color >> 16) & 0xFF),
        .b = (unsigned char)((color >> 8) & 0xFF),
        .a = (unsigned char)(color & 0xFF),
    };
}
#endif /* RLUI_ELEMS_IMPLEMENTATION */
#endif /* RLUI_ELEMS_H_ */
