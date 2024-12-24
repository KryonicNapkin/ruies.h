# rlui_elems
RayLib UI elements is a small library that provides a few (exactly three) basic UI elements for really simple UI creation using raysan5's raylib

## Installation
First you need to have raylib installed for this library to work!
Check [raylib](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux#install-on-gnu-linux) for installation guide

After you are done installing raylib follow these steps below
```bash
# Clone repository
git clone https://github.com/KryonicNapkin/rlui_elems
cd rlui_elems
# the default font used by the elements is Iosevka Nerd Font Bold
cp rlui_elems.c rlui_elems.h IosevkaNerdFont-Bold.ttf <your project path>/
```

And thats it!

## Compilation
You need all the neccessery flags that are required by raylib and also link rlui_elems.c file to your main.c file 
```bash
# Compile
gcc -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o <output> <main_file> rlui_elems.c
```

BABABOOM! Its done!

## Examples
### Simple button without highligthing
```C
#include "raylib.h"
#include "rlui_elems.h"

#define WINW 800        /* Window width */
#define WINH 600        /* Window height */

int main(void) {
    /* Init default window with defined width and height */
    InitWindow(WINW, WINH, "title");
    /* Set target FPS of the window */
    SetTargetFPS(60);

    /* We define button horizontal and vertical position and also width and height */
    /* For demonstration we set all these values to the same number */
    int32_t button_posx = 100;
    int32_t button_posy = 100;
    int32_t button_width = 100;
    int32_t button_height = 45;

    /* make_button is used to create a button */
    /* This function accepts 6 arguments; first 4 are earlier defined positions and dimensions
     * and 5 is a string the will be displayes as a text inside a button, the 6 argument is
     * whether you like to enable highlight on hover 
     */
     /* We are are not going to set the last value for sake of simplicity */
    button_t button = make_button(button_posx, button_posy, button_width, button_height, "demo", 0);
    /* This function automaticaly sets other values to the DEF_* values in the rlui_elems.h file */
    /* You can change these values using button_attr() function but that will be shown in another example */

    /* Raylib loop */
    while (!WindowShouldClose()) {
        BeginDrawing(); 
        {
            /* This function renders the actual button on the window */
            render_button(button);
            ClearBackground(RAYWHITE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
```

As you could see the button's font is a little small or really not pretty

