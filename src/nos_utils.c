/**
* Implementation of nos_utils signatures
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h> // ioctl, TIOCGWINSZ
#include <err.h>       // err
#include <fcntl.h>     // open
#include <unistd.h>    // close
//#include <termios.h>   // don't remember, but it's needed
#include "nos_utils.h"

/**
 * @return  struct winsize
 *  unsigned short int ws_row;
 *   unsigned short int ws_col;
 *   unsigned short int ws_xpixel;
 *   unsigned short int ws_ypixel;
 */
struct winsize get_screen_size() {
    struct winsize ws;
    int fd;

    fd = open("/dev/tty", O_RDWR);
    if (fd < 0 || ioctl(fd, TIOCGWINSZ, &ws) < 0) err(8, "/dev/tty");
    close(fd); // dont forget to close files
    return ws;
}

unsigned short get_screen_width() {
    struct winsize ws = get_screen_size();
    return ws.ws_col;
}

unsigned short get_screen_height() {
    struct winsize ws = get_screen_size();
    return ws.ws_row;
}

void test_screen_size() {
    struct winsize ws = get_screen_size();
//    unsigned short  h = ws.ws_row;
//    unsigned short  w = ws.ws_col;
    printf("The Teminal Size is\n rows: %zu  in %upx\n cols: %zu in %upx\n", ws.ws_row, ws.ws_ypixel, ws.ws_col,
           ws.ws_xpixel);

    unsigned short  h = get_screen_height();
    unsigned short  w = get_screen_width();
    h = h - 4; //for the 3 lines above + 1 fro new terminal line after :)
    for (unsigned short  i = 0; i < h; i++) {// for each row
        for (unsigned short  j = 0; j < w; j++) { // for each col
            //new line if we are last char
            if (j == w - 1) {
                printf(" \n");
            }//one space buffer around edge
            else if (i == 0 || i == h - 1 || j == 0) {
                printf(" ");
            } //the up arrows
            else if (i == 1) {
                printf("^");
            } else if (i == h - 2) {
                printf("v");
            } else if (j == 1) {
                printf("<");
            } else if (j == w - 2) {
                printf(">");
            } else {
                printf("#");
            }
        }//end col
    }//end row
}
