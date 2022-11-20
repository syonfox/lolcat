/**
* This hrlper lib is for the odd utility functions i need for c
*/

#ifndef	_NOS_UTILS_H
#define	_NOS_UTILS_H	1


#include <stdlib.h>
#include <sys/ioctl.h> // ioctl, TIOCGWINSZ

struct winsize get_screen_size();

unsigned short get_screen_width();
unsigned short get_screen_height();

void test_screen_size();

#endif