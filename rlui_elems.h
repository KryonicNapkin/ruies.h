#ifndef RLUI_ELEMS_H_
#define RLUI_ELEMS_H_

#include <stdint.h>                    /* For type compatibility */
#ifndef RAYLIB_H
#include "raylib.h"
#endif

/* Button attributes for the button_attr function */
enum ButtonAttr {
    BUTTON_POS = 0,
    BUTTON_DIMS,
    BUTTON_TEXT,
    BUTTON_TEXT_FONT,
    BUTTON_FONT_SZ,
    BUTTON_BORDER_WIDTH,
    BUTTON_BORDER_FG,
    BUTTON_BG,
    BUTTON_TEXT_FG,
    BUTTON_IS_HIGHLIGHTING,
    BUTTON_TEXT_FG_HIGHLIGHT,
    BUTTON_BUTTON_BG_HIGHLIGHT,
    BUTTON_BORDER_FG_HIGHLIGHT,
};

/* Titlebar attributes for the titlebar_attr function */
enum TitleBarAttr {
    TITLEBAR_POS = 0,
    TITLEBAR_DIMS,
    TITLEBAR_TEXT,
    TITLEBAR_TEXT_FONT,
    TITLEBAR_TEXT_ALIGN,
    TITLEBAR_TEXT_PADDING,
    TITLEBAR_FONT_SZ,
    TITLEBAR_BG_COLOR,
    TITLEBAR_TEXT_FG,
};

/* alignment of titlebar's text */
enum TextAlignment {
    ALIGN_LEFT = 0,
    ALIGN_CENTER,
    ALIGN_RIGHT,
};

/* Horizontal padding */
struct PaddingH {
    uint32_t from_left;
    uint32_t from_right;
};

/* Vertical padding */
struct PaddingV {
    uint32_t from_top;
    uint32_t from_down;
};

/* Button structure */
struct Button {
    int32_t idx;
    int32_t posx, posy;
    int32_t width, height;
    char* text;
    Font text_font;
    float font_sz;
    uint32_t border_width_px;
    Color border_fg;
    Color button_bg;
    Color text_fg;
    bool highlighting;
    Color text_fg_highlight;
    Color button_bg_highlight;
    Color border_fg_highlight;
};

/* ButtonArray structure */
struct ButtonArray {
    struct Button* buttons;
    uint32_t rows;
    uint32_t cols;
    int32_t origin_posx, origin_posy;
    uint32_t horizontal_spacing;
    uint32_t vertical_spacing;
};

/* Titlebar structure */
struct TitleBar {
    int32_t idx;
    int32_t posx, posy;
    int32_t width, height;
    char* text;
    Font text_font;
    enum TextAlignment text_alignment;
    struct PaddingH text_padding;
    float font_sz;
    Color bg_color;
    Color text_fg;
};

/* SelectionItem structure for the selection_list_window */
/* struct SelectionItem {
    int32_t idx;
    char* text;
    Font text_font;
    float font_sz;
    Color item_bg;
    Color text_fg;
    enum TextAlignment text_alignment;
    struct PaddingH text_padding;
}; */

/* selection list window structure*/
/* struct SelectionListWin {
    struct SelectionItem* items;
    int32_t currently_highlighted_item;
    char up_position_char, down_position_char;
    char focus_char, unfocus_char;
    int32_t posx, posy;
    int32_t width, height;
    uint32_t border_width_px;
    Color border_fg;
    bool scrollable;
    bool highlighting;
    Color border_fg_highlight;
    Color text_fg_highlight;
    Color bg_highlight;
}; */

/* Typedefs */
typedef struct SelectionItem selection_item_t;
typedef struct SelectionListWin selection_list_win_t;
typedef struct PaddingH hpadding_t;
typedef struct PaddingV vpadding_t;
typedef struct TitleBar titlebar_t;
typedef struct ButtonArray button_array_t;
typedef struct Button button_t;
typedef enum TextAlignment text_align_t;
typedef enum ButtonAttr button_attr_t;
typedef enum TitleBarAttr titlebar_attr_t;

#define NO_HPADDING (hpadding_t){0, 0}
#define NO_VPADDING (vpadding_t){0, 0}

/* Default values for the button and titlebar attributes */
#define DEF_FONT_PATH                        "IosevkaNerdFont-Bold.ttf" 
#define DEF_BUTTON_FONT_SZ                   20.0f
#define DEF_BUTTON_BORDER_WIDTH              1
#define DEF_BUTTON_BORDER_FG_COLOR           BLACK
#define DEF_BUTTON_BG_COLOR                  WHITE
#define DEF_BUTTON_TEXT_FG_COLOR             BLACK
#define DEF_BUTTON_IS_HIGHLIGHTING           false
#define DEF_BUTTON_TEXT_FG_HIGHLIGHT_COLOR   WHITE
#define DEF_BUTTON_BG_HIGHLIGHT_COLOR        GRAY
#define DEF_BUTTON_BORDER_FG_HIGHLIGHT_COLOR LIGHTGRAY

/* variable to keep track of current element id */
extern int _current_elem_idx;

/* Function declarations */
button_t make_button(int32_t posx, int32_t posy, int32_t width, int32_t height, const char* text, bool highlight_on_hover);
titlebar_t make_titlebar(int32_t posx, int32_t posy, int32_t width, int32_t height, const char* text, text_align_t text_alignment, hpadding_t text_padding);
selection_item_t* make_selection_items(int count, const char* desc, ...);
void append_selection_item(selection_list_win_t* list, selection_item_t item);
selection_list_win_t make_selection_list(Vector2 pos, Vector2 dims, selection_item_t* items);
button_array_t make_button_array(int32_t origin_posx, int32_t origin_posy, uint32_t rows, uint32_t cols, button_t orig_button, const char* text[], int32_t horizontal_spacing, int32_t vertical_spacing);
button_t copy_button(button_t button);
void button_attr(button_t* button, button_attr_t attr, const void* value);
void vbutton_attr(int count, button_attr_t attr, const void* value, ...);
void lbutton_attr(button_array_t* button_array, button_attr_t attr, const void* value);
void titlebar_attr(titlebar_t* titlebar, titlebar_attr_t attr, const void* value);
void render_button(button_t button);
void vrender_button(int count, ...);
void lrender_button(button_array_t buttons);
void render_titlebar(titlebar_t titlebar);
void stretch_button_array_horiz(button_array_t* button_array, uint32_t horizontal_spacing, uint32_t until_x);
void stretch_button_array_verti(button_array_t* button_array, uint32_t vertical_spacing, uint32_t until_y);
Vector2 _get_button_with_border_pos(button_t button);
Vector2 _get_button_with_border_dims(button_t button);
Vector2 _get_button_text_pos(button_t button);
bool button_cursor_hover(button_t button);
int32_t vbutton_cursor_hover(int count, ...);
int32_t lbutton_cursor_hover(button_array_t buttons);
bool button_pressed(button_t button);
int32_t vbutton_pressed(int count, ...);
int32_t lbutton_pressed(button_array_t buttons);

void free_buttons(button_t* buttons);
void free_selection_items(struct SelectionItem* items);

char* rl_ui_strdup(const char* str);

#endif /* RL_UI_ELEMS_H_ */
