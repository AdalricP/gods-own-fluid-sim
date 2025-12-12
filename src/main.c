#include <stdio.h>
#include "window.c"

int main() {
    int code = create_sdl_window(800, 600);
    printf("\n:Exited with success code %d\n", code);
    return 0;
}