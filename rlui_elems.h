/* 
 * RlUI_elems.h is a simple header-only library that adds some ui elements to 
 * be used in raylib applications
 *                                                      GITHUB
 *     Created by: KryonicNapkin        - https://www.github.com/KryonicNapkin/rlui_elems
 *     Credit: raysan5's raygui library - https://www.github.com/raysan5/raygui
 */
/* TODO: make more ui elements like (CheckBox, OptionList) */
/* NOTE: To use this library you NEED to have raylib.h included prior */

/* 
 * TODO: 1. Make more elements (
 *              CheckBox, 
 *              OptionList, 
 *              Slider, 
 *              ProgressBar, 
 *              WindowBox, 
 *              TabPane, 
 *              TitlebarButtons, 
 *              HeaderBar,
 *              ...
 *          )
 *       2. Rework the style system (
 *              Loading a custom style for different Elements,
 *              Do something with fonts,
 *              
 *          )
 *
 *
 */

/* ELEMENTS include: Button, Button grid, Titlebar, Toggle, Label */

#ifndef RLUI_ELEMS_H_
#define RLUI_ELEMS_H_

/* #define USE_CUSTOM_FONT
#include "raylib.h" */

#include <stdint.h>                    /* For type compatibility */

typedef int64_t elem_idx;

enum Elements {
    BUTTON = 0,
    BUTTON_GRID,
    TITLEBAR,
    TOGGLE,
    LABEL,
    CELLBOX,
    ALL_ELEMENTS,
};

enum ElemState {
    NORMAL = 0,
    FOCUSED,
    CLICKED,
};
/* Text alignment */
enum TextAlignment {
    ALIGN_LEFT = 0,
    ALIGN_CENTER,
    ALIGN_RIGHT,
};

enum ElemAttachment {
    TO_THE_LEFT = 0,
    TO_THE_RIGHT,
    ON_TOP,
    TO_BOTTOM
};

enum CellBoxSides {
    LEFT_SIDE = 0,
    RIGHT_SIDE,
    TOP,
    BOTTOM,
};

#define MAX_ELEMENTS_COUNT     6
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
    Rectangle bounds;
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
    Rectangle bounds;
    char* text;
    Font font;
    float font_size;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
};

/* Toggle structure */
struct Toggle {
    elem_idx idx;
    Rectangle bounds;
    char* text;
    Font font;
    float font_size;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
    enum ElemState state;
};

struct Label {
    elem_idx idx;
    Rectangle bounds;
    char* text;
    Font font;
    float font_size;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
    bool is_attached;
    enum ElemAttachment attach_to;
};

struct CellBox {
    elem_idx idx;
    Rectangle bounds;
    uint32_t cell_rows;
    uint32_t cell_cols;
    Rectangle* cell_bounds;
    int* cell_idxs;
    Color border_color;
    uint32_t border_width;
    int number_of_inscribed_elems;
};

/*------------------------------------------------------------*/
/*----------------------    TYPEDEFS    ----------------------*/
/*------------------------------------------------------------*/

/* Elements */
typedef struct Button        button_t;
typedef struct ButtonGrid    button_grid_t;
typedef struct TitleBar      titlebar_t;
typedef struct Toggle        toggle_t;
typedef struct Label         label_t;
typedef struct CellBox       cellbox_t;

/* Elements attributes */
typedef enum TextAlignment   text_align_t;
typedef enum ElemAttr        elem_attr_t; 
typedef enum ElemState       elem_state_t; 
typedef enum ElemAttachment  elem_attach_t;
typedef enum CellBoxSides    cellbox_sides_t;

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
button_t make_button(Rectangle bounds, const char* text);
titlebar_t make_titlebar(Rectangle bounds, const char* text);
/* NOTE: This function allocates memory for the buttons on the heap! 
 * You should call free_button_grid() after CloseWindow() */
button_grid_t make_button_grid(uint32_t posx, uint32_t posy, uint32_t rows, uint32_t cols,
                                Rectangle sample_bounds, const char* text[],
                                uint32_t horizontal_spacing, uint32_t vertical_spacing);
toggle_t make_toggle(Rectangle bounds, const char* text);
label_t make_label(Rectangle bounds, const char* text, uint32_t left_padding, uint32_t right_padding);
cellbox_t make_cellbox(Rectangle bounds, uint32_t rows, uint32_t cols);
 
/* Cellbox releated functions */
void merge_neighbouring_cells(cellbox_t* cellbox, cellbox_sides_t side, int idx1);
void split_cell_horizontaly(cellbox_t* cellbox, int idx);
void split_cell_verticaly(cellbox_t* cellbox, int idx);
void inscribe_elem_into_cell(const void* elem, enum Elements type, cellbox_t* cellbox, int cell_idx);
/* void inscribe_elem_into_cell_relative_side(const void* elem, enum Elements type, cellbox_t* cellbox, cellbox_sides_t from, int how_much, int vertical_pos); */

/* Additional ways of creating elements */
button_t make_button_from_button(button_t button, Rectangle bounds, const char* text);
toggle_t make_toggle_from_toggle(toggle_t toggle, Rectangle bounds, const char* text);

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
void set_cellbox_style(cellbox_t* cellbox, enum ElemAttr attr, uint32_t value);
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
Vector2 __get_elem_with_border_pos(Rectangle bounds, uint32_t border_width);
Vector2 __get_elem_with_border_dims(Rectangle bounds, uint32_t border_width);
Vector2 __get_elem_text_pos(Rectangle bounds, Font font, const char* text);
Vector2 __get_text_pos_align(Rectangle bounds, uint32_t left_padding, uint32_t right_padding, 
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
void free_cellbox(cellbox_t cellbox);

/* Miscellaneous functions */
char* rlui_strdup(const char* str);

#ifdef RLUI_ELEMS_IMPLEMENTATION


#endif /* RLUI_ELEMS_IMPLEMENTATION */
#endif /* RLUI_ELEMS_H_ */
