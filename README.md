# rlui_elems
RaylibUIElementS is a header only library that provides basic UI elements for simple UI creation using raysan5's raylib

## Installation
First you need to have raylib installed for this library to work!
Check [raylib](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux#install-on-gnu-linux) for installation guide

After you are done installing raylib follow these steps below
```bash
# Clone repository
git clone https://github.com/KryonicNapkin/ruies.h
cd ruies.h
# the default font used by the library is PixeloidSans font 
# license : ./assets/License.txt
cp ruies.h <your project path>/
```

And thats it!

## Compilation
You don't need any additional options passed to the compiler
```bash
# Compile
gcc -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o <output> <main_file>
```

BABABOOM! Its done!

## Examples
### Simple button without highligthing
```C
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

    /* Raylib loop */
    while (!WindowShouldClose()) {
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            /* Render the button */
            /* NOTE: you pass it as a pointer because this function also changes the button state structure element */
            render_button(&button);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0 ;
}
```

