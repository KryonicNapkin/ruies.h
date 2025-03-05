/* NOTE: You MUST #include "raylib.h" before RUIES_IMPLEMENTATION for the library to work */
#include "raylib.h"

/* Library and its implementation */
#define RUIES_IMPLEMENTATION
#include "../../ruies.h"

int main(void) {
    /* Standard raylib initialization */
    InitWindow(800, 600, "Test");
    SetTargetFPS(60);

    /* NOTE: For text to be displayed you need to call ruies_load_default_font() before any other function */
    ruies_load_default_font();

    /* Button dimensions as of type Ruies_Rect_t */
    Ruies_Rect_t button_dims = {100, 100, 200, 50};
    /* Creation of button */
    Ruies_Button_t button = make_button(button_dims, "Click me");

    /* true if button state is CLICKED */
    bool active;

    /* Raylib loop */
    while (!WindowShouldClose()) {
        /* Set the variable to true if button state is CLICKED */
        get_button_state(button, &active);
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            /* Render the button */
            /* NOTE: you pass it as a pointer because this function also changes the button state structure element */
            render_button(&button);
            if (active) DrawRectangle(300, 300, 300, 300, RED);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
