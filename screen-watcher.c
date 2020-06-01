#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <X11/Xlib.h>

#include "config.h"

int
main() {
    Display *disp = XOpenDisplay(NULL);
    if (disp == NULL) {
        fprintf(stderr, "Unable to open X Display ;-;\n");
        exit(-1);
    }

    int screen = DefaultScreen(disp);
    Window win = RootWindow(disp, screen);

    static int last_width = 0;
    static int last_height = 0;

    static struct timespec sleep_duration;
    sleep_duration.tv_sec = 0;
    sleep_duration.tv_nsec = 10000000; // 10ms
    static struct timespec rem_duration;
    
    while (1) {
        Window root;
        static int x, y;
        static unsigned int width, height;
        static unsigned int border_width;
        static unsigned int depth;
        if(XGetGeometry(disp, win, &root, &x, &y, &width, &height, &border_width, &depth) == False) {
            fprintf(stderr, "Unable to get root window geometry\n");
            exit(-1);
        }

        if (!last_width) last_width = width;
        if (!last_height) last_height = height;

        if (width != last_width || height != last_height) {
            last_width = width;
            last_height = height;
            printf("Display size changed to %dx%d\n", width, height);

            system(cmd);
        }

        // sleep a while to reduce cpu usage
        nanosleep(&sleep_duration, &rem_duration);
    }
    
    return 0;
}