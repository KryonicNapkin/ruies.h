/* 
 * RlUI_elems.h is a simple header-only library that adds some ui elements to 
 * be used in raylib applications
 *                                                      GITHUB
 *     Created by: KryonicNapkin        - https://www.github.com/KryonicNapkin/rlui_elems
 *     Credit: raysan5's raygui library - https://www.github.com/raysan5/raygui
 */
/*  TODO: make more ui elements like (CheckBox, OptionList) */

/* ELEMENTS include: Button, Button grid, Titlebar, Toggle, Label */

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
    LABEL,
    ALL_ELEMENTS,
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

enum ElemAttachment {
    LEFT_SIDE = 0,
    ON_TOP,
    RIGHT_SIDE,
    TO_BOTTOM
};

#define MAX_ELEMENTS_COUNT     5
#define MAX_ELEMENT_ATTRIBUTES 19
struct GlobalStyle {
    uint32_t elem_styles[MAX_ELEMENTS_COUNT][MAX_ELEMENT_ATTRIBUTES];
    Font (*fontloader[MAX_ELEMENTS_COUNT])(void);
    float font_sizes[MAX_ELEMENTS_COUNT];
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
    float font_size;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
    enum ElemState state;
};

/* ButtonGrid structure */
struct ButtonGrid {
    struct Button* buttons;
    Font font;
    float font_size;
    uint32_t rows;
    uint32_t cols;
    uint32_t origin_posx, origin_posy;
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
    float font_size;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
};

/* Toggle structure */
struct Toggle {
    elem_idx idx;
    elem_bounds_t bounds;
    char* text;
    Font font;
    float font_size;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
    enum ElemState state;
};

struct Label {
    elem_idx idx;
    elem_bounds_t bounds;
    char* text;
    Font font;
    float font_size;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
    bool is_attached;
    enum ElemAttachment attach_to;
};

/*------------------------------------------------------------*/
/*----------------------    TYPEDEFS    ----------------------*/
/*------------------------------------------------------------*/

typedef struct Button        button_t;
typedef struct ButtonGrid    button_grid_t;
typedef struct TitleBar      titlebar_t;
typedef struct Toggle        toggle_t;
typedef struct Label         label_t;
typedef enum TextAlignment   text_align_t;
typedef enum ElemAttr        elem_attr_t; 
typedef enum ElemState       elem_state_t; 
typedef enum ElemAttachment  elem_attach_t;

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

#define NO_COLOR_VALUE       0x00000000
#define UNDEFINED_COLOR(hex) (!(hex) ? 1 : 0)     

#define __BORDER_WIDTH       1

/* NOTE: For custom font loading you must initialize a new fontloader with you custom font loading function */
#define DEFAULT_FONTLOADER   &GetFontDefault
#define __FONT_SIZE          10                      /* Set font size */

/*
 NOTE: If it's 0 than that means no error 
 *     If it's other than 0 that means error 
 *     You can check the value of using function check_rlui_error()
 * 
*/
/* custom variable that stores current error */
int __rlui_error;

/* variable to keep track of current element id */
int __current_elem_idx;

/* Default style for the elements */
struct GlobalStyle __style;

/*-------------------------------------------------------------*/
/*-----------------   FUNCTION DECLARATIONS   -----------------*/
/*-------------------------------------------------------------*/

#ifdef USE_CUSTOM_FONT
    void set_font_loader_function(enum Elements elem, Font (*fontloader)(void));
    void set_elem_font_size(enum Elements elem, float font_size);
#endif /* USE_CUSTOM_FONT */

/* Error handling functions */
int check_rlui_error(void);

/* Element making functions */
button_t make_button(elem_bounds_t bounds, const char* text);
titlebar_t make_titlebar(elem_bounds_t bounds, const char* text);
/* NOTE: This function allocates memory for the buttons on the heap! 
 * You should call free_button_grid() after CloseWindow() */
button_grid_t make_button_grid(uint32_t posx, uint32_t posy, uint32_t rows, uint32_t cols,
                               elem_bounds_t sample_bounds, const char* text[],
                               uint32_t horizontal_spacing, uint32_t vertical_spacing);
toggle_t make_toggle(elem_bounds_t bounds, const char* text);
label_t make_label(elem_bounds_t bounds, const char* text, uint32_t left_padding, uint32_t right_padding);

/* Additional ways of creating elements */
button_t make_button_from_button(button_t button, elem_bounds_t bounds, const char* text);
toggle_t make_toggle_from_toggle(toggle_t toggle, elem_bounds_t bounds, const char* text);

/* Label releated functions */
void attach_label_to_elem(const void* elem, enum Elements type, label_t* label, enum ElemAttachment attach_to);

/* Style functions */
uint32_t* get_style(enum Elements elem, int* size);
uint32_t get_style_value(enum Elements elem, enum ElemAttr attr);
void get_style_colors(enum ElemState state, uint32_t* style, Color* border, Color* base, Color* text);

/* Attributes changing functions */
void set_button_style(button_t* button, enum ElemAttr attr, uint32_t value);
void set_titlebar_style(titlebar_t* titlebar, enum ElemAttr attr, uint32_t value);
void button_grid_attr(button_grid_t* grid, enum ElemAttr attr, uint32_t value);
void set_toggle_style(toggle_t* toggle, enum ElemAttr attr, uint32_t value);
void set_label_style(label_t* label, enum ElemAttr attr, uint32_t value);
void set_allstyle(enum Elements elem, enum ElemAttr attr, uint32_t value);

/* ButtonGrid alignment functions */
void stretch_button_grid_horiz(button_grid_t* button_grid, uint32_t horizontal_spacing, uint32_t until_x);
void stretch_button_grid_verti(button_grid_t* button_grid, uint32_t vertical_spacing, uint32_t until_y);

/* Rendering functions */
void render_button(button_t* button);
void vrender_button(int count, ...);
void render_button_grid(button_grid_t* buttons);
void render_titlebar(titlebar_t titlebar);
void render_toggle(toggle_t* toggle);
void render_label(label_t* label);

/* Internal functions for rendering */
Vector2 __get_elem_with_border_pos(elem_bounds_t bounds, uint32_t border_width);
Vector2 __get_elem_with_border_dims(elem_bounds_t bounds, uint32_t border_width);
Vector2 __get_elem_text_pos(elem_bounds_t bounds, Font font, const char* text);
Vector2 __get_text_pos_align(elem_bounds_t bounds, uint32_t left_padding, uint32_t right_padding, 
                             enum TextAlignment text_align, Font font, float font_size, const char* text);

/* Functions for getting elements states */
elem_state_t get_button_state(button_t button, bool* active);
elem_state_t get_toggle_state(toggle_t toggle, bool* active);

/* Functions for changing element states */
void __detect_button_state_change(button_t* button);
void __detect_toggle_state_change(toggle_t* toggle);

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

/* custom variable that stores current error */
int __rlui_error = 0;

int __current_elem_idx = 0;

/* STYLE DEFINITIONS OF THE ELEMENTS */
struct GlobalStyle __style = {
    .elem_styles = {
        /* Button */
        {
            BORDER_COLOR_NORMAL,  BASE_COLOR_NORMAL,   TEXT_COLOR_NORMAL, 
            BORDER_COLOR_FOCUSED, BASE_COLOR_FOCUSED,  TEXT_COLOR_FOCUSED,
            BORDER_COLOR_CLICKED, BASE_COLOR_CLICKED,  TEXT_COLOR_CLICKED,
            __BORDER_WIDTH, ALIGN_CENTER, 
            0, 0, 0, 0,       0, 0, 0, 0
        }, 
        /* Button Grid */
        { 
            BORDER_COLOR_NORMAL, BASE_COLOR_NORMAL, TEXT_COLOR_NORMAL, 
            BORDER_COLOR_FOCUSED, BASE_COLOR_FOCUSED, TEXT_COLOR_FOCUSED,
            BORDER_COLOR_CLICKED, BASE_COLOR_CLICKED, TEXT_COLOR_CLICKED,
            __BORDER_WIDTH, ALIGN_CENTER, 
            0, 0, 0, 0,       0, 0, 0, 0
        }, 
        /* Titlebar */
        { 
            BORDER_COLOR_NORMAL, BASE_COLOR_NORMAL, TEXT_COLOR_NORMAL, 
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,
            __BORDER_WIDTH, ALIGN_LEFT, 
            10, 0, 0, 0,      0, 0, 0, 0
        },
        /* TOGGLE */
        { 
            BORDER_COLOR_NORMAL, BASE_COLOR_NORMAL, TEXT_COLOR_NORMAL, 
            BORDER_COLOR_FOCUSED, BASE_COLOR_FOCUSED, TEXT_COLOR_FOCUSED,
            BORDER_COLOR_CLICKED, BASE_COLOR_CLICKED, TEXT_COLOR_CLICKED,
            __BORDER_WIDTH, ALIGN_CENTER, 
            0, 0, 0, 0,      0, 0, 0, 0
        },
        /* LABEL */
        { 
            NO_COLOR_VALUE, BASE_COLOR_NORMAL, TEXT_COLOR_NORMAL,           // state: normal
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                 // state: focused
            NO_COLOR_VALUE, NO_COLOR_VALUE, NO_COLOR_VALUE,                 // state: clicked
            0, ALIGN_LEFT, 
            10, 0, 0, 0,      0, 0, 0, 0
        },
    }, 
    .fontloader = {DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER, DEFAULT_FONTLOADER},
    .font_sizes = {__FONT_SIZE, __FONT_SIZE, __FONT_SIZE, __FONT_SIZE, __FONT_SIZE},
};

/* NOTE: fontloader function should be generated using raylib's ExportFontAsCode() function
 *       and you should remove the check for IsGpuReady in the .h file for this function to 
 *       correctly load your desired font 
 */
#ifdef USE_CUSTOM_FONT
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
#endif /* USE_CUSTOM_FONT */

int check_rlui_error(void) {
    return __rlui_error;
}

/* Function for creation of a button */
button_t make_button(elem_bounds_t bounds, const char* text) {
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
titlebar_t make_titlebar(elem_bounds_t bounds, const char* text) {
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

button_grid_t make_button_grid(uint32_t posx, uint32_t posy, uint32_t rows, uint32_t cols, elem_bounds_t sample_bounds, const char* text[], uint32_t horizontal_spacing, uint32_t vertical_spacing) {
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

toggle_t make_toggle(elem_bounds_t bounds, const char* text) {
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

label_t make_label(elem_bounds_t bounds, const char* text, uint32_t left_padding, uint32_t right_padding) {
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

button_t make_button_from_button(button_t button, elem_bounds_t bounds, const char* text) {
    button_t new_button;
    memcpy(&new_button, &button, sizeof(button_t));
    new_button.bounds = bounds;
    new_button.text = rlui_strdup(text);
    new_button.idx = button.idx + 1;
    __current_elem_idx += 1;
    __rlui_error = 0;
    return new_button;
}

toggle_t make_toggle_from_toggle(toggle_t toggle, elem_bounds_t bounds, const char* text) {
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
    elem_bounds_t new_bounds = {0};
    elem_bounds_t elem_bounds;
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
        case LEFT_SIDE:
            label->bounds.x = elem_bounds.x-label->bounds.width;
            label->bounds.y = elem_bounds.y;
            break;
        case ON_TOP:
            label->bounds.x = elem_bounds.x;
            label->bounds.y = elem_bounds.y-label->bounds.height;
            break;
        case RIGHT_SIDE:
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
    switch (state) {
        case NORMAL:
            if (border != NULL) *border = __int2color(style[ATTR_BORDER_COLOR_NORMAL]);
            if (base != NULL) *base = __int2color(style[ATTR_BASE_COLOR_NORMAL]);
            if (text != NULL) *text = __int2color(style[ATTR_TEXT_COLOR_NORMAL]);
            __rlui_error = 0;
            break;
        case FOCUSED:
            if (border != NULL) *border = __int2color(style[ATTR_BORDER_COLOR_FOCUSED]);
            if (base != NULL) *base = __int2color(style[ATTR_BASE_COLOR_FOCUSED]);
            if (text != NULL) *text = __int2color(style[ATTR_TEXT_COLOR_FOCUSED]);
            __rlui_error = 0;
            break;
        case CLICKED:
            if (border != NULL) *border = __int2color(style[ATTR_BORDER_COLOR_CLICKED]);
            if (base != NULL) *base = __int2color(style[ATTR_BASE_COLOR_CLICKED]);
            if (text != NULL) *text = __int2color(style[ATTR_TEXT_COLOR_CLICKED]);
            __rlui_error = 0;
            break;
        default:
            __rlui_error = 1;
            break;
    }
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
    DrawRectangle(button->bounds.x, button->bounds.y, button->bounds.width, button->bounds.height, border_color);
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
    DrawTextEx(titlebar.font, titlebar.text, text_pos, titlebar.font_size, 0, __int2color(titlebar.style[ATTR_TEXT_COLOR_NORMAL]));
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
    DrawRectangle(toggle->bounds.x, toggle->bounds.y, toggle->bounds.width, toggle->bounds.height, border_color);
    DrawRectangleV(border_bounds[0], border_bounds[1], base_color);
    DrawTextEx(toggle->font, toggle->text, text_pos, toggle->font_size, 0, text_color);
    __rlui_error = 0;
}

void render_label(label_t* label) {
    Vector2 text_pos = __get_text_pos_align(label->bounds, label->style[ATTR_LEFT_PADDING], 
                                            label->style[ATTR_RIGHT_PADDING], (enum TextAlignment)label->style[ATTR_TEXT_ALIGNMENT],
                                            label->font, label->font_size, label->text);
    Color base_color = __int2color(label->style[ATTR_BASE_COLOR_NORMAL]);
    Color text_color = __int2color(label->style[ATTR_TEXT_COLOR_NORMAL]);
    /* Drawing */
    DrawRectangle(label->bounds.x, label->bounds.y, label->bounds.width, label->bounds.height, base_color);
    DrawTextEx(label->font, label->text, text_pos, label->font_size, 0, text_color);
}

/* Internal function to calculate the position of the boundsagle relative to border width */
Vector2 __get_elem_with_border_pos(elem_bounds_t bounds, uint32_t border_width) {
    Vector2 border_pos = {0};
    border_pos.x = bounds.x+border_width;
    border_pos.y = bounds.y+border_width;
    __rlui_error = 0;
    return border_pos;
}

/* Internal functin to calculate the dimensions of the boundsagle relative to border width */
Vector2 __get_elem_with_border_dims(elem_bounds_t bounds, uint32_t border_width) {
    Vector2 border_dims = {0};
    border_dims.x = bounds.width-(2*border_width);
    border_dims.y = bounds.height-(2*border_width);
    __rlui_error = 0;
    return border_dims;
}

/* Internal function to calculate the text position of a button */
Vector2 __get_elem_text_pos(elem_bounds_t bounds, Font font, const char* text) {
    Vector2 text_pos = {0};
    text_pos.x = bounds.x+((float)(bounds.width-(float)MeasureTextEx(font, text, font.baseSize, 0).x)/2.0f);
    text_pos.y = bounds.y+((float)(bounds.height-(float)MeasureTextEx(font, text, font.baseSize, 0).y)/2.0f);
    __rlui_error = 0;
    return text_pos;
}

Vector2 __get_text_pos_align(elem_bounds_t bounds, uint32_t left_padding, uint32_t right_padding, 
                             enum TextAlignment text_align, Font font, float font_size, const char* text) {
    Vector2 text_pos = {0};
    Vector2 text_dims = MeasureTextEx(font, text, font_size, 0);
    /* Calculates the distance from the sides */
    switch (text_align) {
        case ALIGN_LEFT:
            text_pos.x = (float)(bounds.x+left_padding);
            text_pos.y = (float)(bounds.y+((bounds.height-text_dims.y)/2.0f));
            break;
        case ALIGN_CENTER:
            text_pos.x = (float)(bounds.x+((bounds.width-text_dims.x)/2.0f));
            text_pos.y = (float)(bounds.y+((bounds.height-text_dims.y)/2.0f));
            break;
        case ALIGN_RIGHT:
            text_pos.x = (float)(bounds.width-text_dims.x-right_padding);
            text_pos.y = (float)(bounds.y+((bounds.height-text_dims.y)/2.0f));
            break;
        default:
            __rlui_error = 1;
            break;
    }
    __rlui_error = 0;
    return text_pos;
}

elem_state_t get_button_state(button_t button, bool* active) {
    if (button.state == CLICKED) *active = true;
    else *active = false;
    __rlui_error = 0;
    return button.state;
}

elem_state_t get_toggle_state(toggle_t toggle, bool* active) {
    if (toggle.state == CLICKED) *active = true;
    else *active = false;
    __rlui_error = 0;
    return toggle.state;
}

/* Functions for changing element states */
void __detect_button_state_change(button_t* button) {
    Rectangle bounds = {
        .x = (float)button->bounds.x,
        .y = (float)button->bounds.y,
        .width = (float)button->bounds.width,
        .height = (float)button->bounds.height,
    };
    bool hover = CheckCollisionPointRec(GetMousePosition(), bounds);
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
    Rectangle bounds = {
        .x = (float)toggle->bounds.x,
        .y = (float)toggle->bounds.y,
        .width = (float)toggle->bounds.width,
        .height = (float)toggle->bounds.height,
    };
    bool hover = CheckCollisionPointRec(GetMousePosition(), bounds);
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
    __rlui_error = 0;
}

#endif /* RLUI_ELEMS_IMPLEMENTATION */
#endif /* RLUI_ELEMS_H_ */
