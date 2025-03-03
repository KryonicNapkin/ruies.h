/* 
 * RlUI_elems.h is a simple header-only library that adds some ui elements to 
 * be used in raylib applications
 *                                                      GITHUB
 *     Created by: KryonicNapkin        - https://www.github.com/KryonicNapkin/rlui_elems
 *     Credit: raysan5's raygui library - https://www.github.com/raysan5/raygui
 */
/* NOTE: To use this library you NEED to have raylib.h included prior */

/* 
 * TODO: 1. Make more elements (
 *              CheckBox, 
 *              OptionList, 
 *              Slider, 
 *              ProgressBar, 
 *              WindowBox,  -- In progress
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

#include "raylib.h"
#include "raymath.h"

#include <stdint.h>                    /* For type compatibility */

typedef int64_t ElemID_t;

typedef enum {
    NORMAL_BORDER = 0,
    DOUBLE_BORDER,
} WindowBoxStyles_t;

typedef enum {
    BUTTON = 0,
    BUTTON_GRID,
    TITLEBAR,
    TOGGLE,
    LABEL,
    CELLBOX,
    WINBOX,
    ALL_ELEMENTS,
} ElementTypes_t;

typedef enum {
    NORMAL = 0,
    FOCUSED,
    CLICKED,
} ElemState_t;
/* Text alignment */
typedef enum {
    ALIGN_LEFT = 0,
    ALIGN_CENTER,
    ALIGN_RIGHT,
} TextAlignment_t;

typedef enum {
    TO_THE_LEFT = 0,
    TO_THE_RIGHT,
    ON_TOP,
    TO_BOTTOM
} ElemAttachment_t;

typedef enum {
    LEFT_SIDE = 0,
    RIGHT_SIDE,
    TOP,
    BOTTOM,
} CellBoxSides_t;

#define MAX_ELEMENTS_COUNT     7
#define MAX_ELEMENT_ATTRIBUTES 19

typedef struct {
    uint32_t elem_styles[MAX_ELEMENTS_COUNT][MAX_ELEMENT_ATTRIBUTES];
    Font (*fontloader[MAX_ELEMENTS_COUNT])(void);
    float font_sizes[MAX_ELEMENTS_COUNT];
} GlobalStyle_t;

/* Button attributes for the button_grid function */
typedef enum {
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
} ElemAttr_t;

/*------------------------------------------------------------*/
/*----------------------    ELEMENTS    ----------------------*/
/*------------------------------------------------------------*/

/* Button structure */
typedef struct {
    ElemID_t id;
    Rectangle bounds;
    char* text;
    Font font;
    float font_size;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
    ElemState_t state;
} Button_t;

/* ButtonGrid structure */
typedef struct {
    Button_t* buttons;
    Font font;
    float font_size;
    uint32_t rows;
    uint32_t cols;
    uint32_t origin_posx, origin_posy;
    uint32_t horizontal_spacing;
    uint32_t vertical_spacing;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
} ButtonGrid_t;

/* Titlebar structure */
typedef struct {
    ElemID_t id;
    Rectangle bounds;
    char* text;
    Font font;
    float font_size;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
} TitleBar_t;

/* Toggle structure */
typedef struct {
    ElemID_t id;
    Rectangle bounds;
    char* text;
    Font font;
    float font_size;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
    ElemState_t state;
} Toggle_t;

typedef struct {
    ElemID_t id;
    Rectangle bounds;
    char* text;
    Font font;
    float font_size;
    uint32_t style[MAX_ELEMENT_ATTRIBUTES];
    bool is_attached;
    ElemAttachment_t attach_to;
} Label_t;

typedef struct {
    ElemID_t id;
    Rectangle bounds;
    uint32_t cell_rows;
    uint32_t cell_cols;
    uint32_t cell_margin;
    Rectangle* cell_bounds;
    int* cell_ids;
    int number_of_inscribed_elems;
} CellBox_t;

typedef struct {
    ElemID_t id;
    Rectangle bounds;
    Color border_color;
    Color base_color;
    uint32_t border_width;
    ElemState_t state;
    WindowBoxStyles_t border_style;
    uint32_t border_gap;
} WindowBox_t;

/*------------------------------------------------------------*/
/*----------------------    TYPEDEFS    ----------------------*/
/*------------------------------------------------------------*/

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
extern int __rlui_error;

/* variable to keep track of current element id */
extern int __current_ElemID_t;

/* Default style for the elements */
extern GlobalStyle_t __style;

/*-------------------------------------------------------------*/
/*-----------------   FUNCTION DECLARATIONS   -----------------*/
/*-------------------------------------------------------------*/

extern void set_font_loader_function(ElementTypes_t elem, Font (*fontloader)(void));
extern void set_elem_font_size(ElementTypes_t elem, float font_size);

/* Error handling functions */
extern int check_rlui_error(void);
 
/* Element making functions */
extern Button_t make_button(Rectangle bounds, const char* text);
extern TitleBar_t make_titlebar(Rectangle bounds, const char* text);
/* NOTE: This function allocates memory for the buttons on the heap! 
 * You should call free_button_grid() after CloseWindow() */
extern ButtonGrid_t make_button_grid(uint32_t posx, uint32_t posy, uint32_t rows, uint32_t cols,
                                Rectangle sample_bounds, const char* text[],
                                uint32_t horizontal_spacing, uint32_t vertical_spacing);
extern Toggle_t make_toggle(Rectangle bounds, const char* text);
extern Label_t make_label(Rectangle bounds, const char* text, uint32_t left_padding, uint32_t right_padding);
extern CellBox_t make_cellbox(Rectangle bounds, uint32_t rows, uint32_t cols, uint32_t cell_margin);
extern WindowBox_t make_window_box(Rectangle bounds, WindowBoxStyles_t border_style, 
                                   uint32_t border_width, uint32_t border_gap);
 
/* Cellbox releated functions */
extern void merge_neighbouring_cells(CellBox_t* cellbox, CellBoxSides_t side, int idx1);
extern void split_cell_horizontaly(CellBox_t* cellbox, int idx);
extern void split_cell_verticaly(CellBox_t* cellbox, int idx);
extern void inscribe_elem_into_cell(const void* elem, ElementTypes_t type, CellBox_t* cellbox, int cell_id);
/* void inscribe_elem_into_cell_relative_side(const void* elem, ElementTypes_t type, CellBox_t* cellbox, cellbox_sides_t from, int how_much, int vertical_pos); */
extern void insert_cellbox_into_window_box(CellBox_t* cellbox, WindowBox_t winbox);
extern void set_cellbox_cell_margin(CellBox_t* cellbox, uint32_t cell_margin);
extern void calculate_cells(CellBox_t* cellbox);
extern int relative_cellbox_id(int cols, int x, int y);

/* Additional ways of creating elements */
extern Button_t make_button_from_button(Button_t button, Rectangle bounds, const char* text);
extern Toggle_t make_toggle_from_toggle(Toggle_t toggle, Rectangle bounds, const char* text);

/* Label releated functions */
extern void attach_label_to_elem(const void* elem, ElementTypes_t type, Label_t* label, ElemAttachment_t attach_to);

/* Style functions */
extern void set_global_style(ElementTypes_t elem_type, ElemAttr_t attr, uint32_t value);
extern uint32_t* get_style(ElementTypes_t elem, int* size);
extern uint32_t get_style_value(ElementTypes_t elem, ElemAttr_t attr);
extern void get_style_colors(ElemState_t state, uint32_t* style, Color* border, Color* base, Color* text);

/* Attributes changing functions */
extern void set_button_style(Button_t* button, ElemAttr_t attr, uint32_t value);
extern void set_titlebar_style(TitleBar_t* titlebar, ElemAttr_t attr, uint32_t value);
extern void button_grid_attr(ButtonGrid_t* grid, ElemAttr_t attr, uint32_t value);
extern void set_toggle_style(Toggle_t* toggle, ElemAttr_t attr, uint32_t value);
extern void set_label_style(Label_t* label, ElemAttr_t attr, uint32_t value);
extern void set_cellbox_style(CellBox_t* cellbox, ElemAttr_t attr, uint32_t value);

/* ButtonGrid alignment functions */
extern void stretch_button_grid_horiz(ButtonGrid_t* button_grid, uint32_t horizontal_spacing, uint32_t until_x);
extern void stretch_button_grid_verti(ButtonGrid_t* button_grid, uint32_t vertical_spacing, uint32_t until_y);

/* Rendering functions */
extern void render_button(Button_t* button);
extern void vrender_button(int count, ...);
extern void render_button_grid(ButtonGrid_t* buttons);
extern void render_titlebar(TitleBar_t titlebar);
extern void render_toggle(Toggle_t* toggle);
extern void render_label(Label_t* label);
extern void render_winbox(WindowBox_t* winbox);

/* Internal functions for rendering */
extern Vector2 __get_elem_with_border_pos(Rectangle bounds, uint32_t border_width);
extern Vector2 __get_elem_with_border_dims(Rectangle bounds, uint32_t border_width);
extern Vector2 __get_elem_text_pos(Rectangle bounds, Font font, const char* text);
extern Vector2 __get_text_pos_align(Rectangle bounds, uint32_t left_padding, uint32_t right_padding, 
                                    TextAlignment_t text_align, Font font, float font_size, const char* text);

/* Functions for getting elements states */
extern ElemState_t get_button_state(Button_t button, bool* active);
extern ElemState_t get_toggle_state(Toggle_t toggle, bool* active);
extern ElemState_t get_winbox_state(WindowBox_t winbox);

/* Functions for changing element states */
extern void __detect_button_state_change(Button_t* button);
extern void __detect_toggle_state_change(Toggle_t* toggle);
extern void __detect_winbox_state_change(WindowBox_t* winbox);

extern int get_button_index_in_grid_by_its_id(ButtonGrid_t button_grid, ElemID_t id);

/* Memory management functions */
extern void free_button_grid(ButtonGrid_t button_grid);
extern void free_cellbox(CellBox_t cellbox);

/* Miscellaneous functions */
extern char* rlui_strdup(const char* str);

#endif /* RLUI_ELEMS_H_ */
