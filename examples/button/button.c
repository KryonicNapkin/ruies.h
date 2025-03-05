#include "raylib.h"

#include "../../rlui_elems.h"

int main(void) {
    InitWindow(800, 600, "Test");
    SetTargetFPS(60);

    set_elem_font_size(BUTTON, 20);

    Rectangle button_dims = {100, 100, 200, 50};
    Button_t button = make_button(button_dims, "Click me");

    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            render_button(&button);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0 ;
}
