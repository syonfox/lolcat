/*//https://fuchsia.googlesource.com/fuchsia/+/refs/heads/main/examples/cowsay/cowsay.c
// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define MAX_WIDTH 40
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a < b) ? a : b)
// Returns the length of the longst line of the message.
static size_t LongestLineLength(int argc, char** argv) {
    size_t max_len = 0;
    size_t cur_line = 0;
    for (int i = 0; i < argc; i++) {
        size_t word_len = strlen(argv[i]) + 1;
        // If the word itself is too long to fit in a line, then
        // we return the maximum width.
        if (word_len >= MAX_WIDTH)
            return MAX_WIDTH;
        if (cur_line + word_len >= MAX_WIDTH) {
            cur_line = word_len;
        } else {
            cur_line += word_len;
        }
        max_len = MAX(cur_line, max_len);
    }
    return max_len;
}
static void PrintPaddedBreak(size_t pad) {
    for (size_t i = 0; i < pad; i++) {
        printf(" ");
    }
    printf(" |\n");
}
// Prints the message
static void PrintMessage(int argc, char** argv, size_t longest) {
    size_t cur_line_len = 0;
    for (int i = 0; i < argc; i++) {
        size_t word_len = strlen(argv[i]) + 1;
        if (cur_line_len == 0)
            printf("| ");
        // If it all fits in the line, then print the word and move on.
        if (cur_line_len + word_len <= MAX_WIDTH) {
            printf("%s ", argv[i]);
            if (cur_line_len + word_len == MAX_WIDTH) {
                PrintPaddedBreak(longest - cur_line_len - word_len);
                cur_line_len = 0;
                continue;
            }
            cur_line_len += word_len;
            if (i == argc - 1)
                PrintPaddedBreak(longest - cur_line_len);
            continue;
        }
        // Create a line break if the current line is nonempty.
        if (cur_line_len > 0) {
            PrintPaddedBreak(longest - cur_line_len);
            printf("| ");
        }
        // If the word itself is too long, then we need to break it apart.
        // Otherwise, we print the current word and move on.
        if (word_len > MAX_WIDTH) {
            char* str = argv[i];
            size_t processed = 0;
            for (size_t j = 0; j <= word_len / MAX_WIDTH; j++) {
                size_t len = MIN(MAX_WIDTH, strlen(str));
                printf("%.*s", (int)len, str);
                PrintPaddedBreak(longest - len);
                str += len;
                processed += len;
                if (processed >= word_len - 1)
                    break;
                printf("| ");
            }
            cur_line_len = 0;
        } else {
            printf("%s ", argv[i]);
            cur_line_len = word_len;
            if (word_len == MAX_WIDTH || i == argc - 1) {
                PrintPaddedBreak(longest - cur_line_len);
            }
        }
    }
}
int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Usage: cowsay [message]\n");
        //todo add stdio pipe in suport: cat file.txt | cowsay
        return 1;
    }

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    // No wordwrap because I'm too lazy. lol bro i got you
    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);


    size_t bubble_width = LongestLineLength(argc - 1, argv + 1) + 1;
    printf(" _");
    for (size_t i = 0; i < bubble_width; i++)
        printf("_");
    printf(" \n");
    PrintMessage(argc - 1, argv + 1, bubble_width - 1);
    printf(" -");
    for (size_t i = 0; i < bubble_width; i++)
        printf("-");
    printf(" \n");
    printf("     \\  ^__^\n");
    printf("      \\ (oo)\\_____\n");
    printf("        (__)\\     )\\/\\\n");
    printf("           ||----w |\n");
    printf("           ||     ||\n");
    return 0;
}*/

//wget https://raw.githubusercontent.com/federicobond/fedux/master/src/software/cowsay.c

//#include "../../include/stdio.h"
//#include "../../include/string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include <sys/ioctl.h> // ioctl, TIOCGWINSZ
#include <err.h>       // err
#include <fcntl.h>     // open
#include <unistd.h>    // close
#include "nos_utils.c"

// move argc value
int args_shift(int n, int *argc, char ***argv) {
    if (*argc >= n) // if we are pointing
    {
        *argc -= n; // remove n from the args
        *argv += n; // increment the pointer
    } else {
        printf("Error not arguments left to shift by %d", n);
    }
    return *argc - n; // will be  less then 0
}



// #include <commons.h>
// #include <string>
// #include <stdio>
#define MULTILINE_WARNING   "Blah blah blah, try something shorter."
#define BLANK_WARNING       "Nothing to say."

typedef struct {
    char *opt;
    char *eyes;
    char tongue;
} design_t;

static design_t designs[] = {
        {"-b", "==",   ' '},
        {"-d", "XX",   ' '},
        {"-g", "$$",   ' '},
        {"-p", "@@",   ' '},
        {"-s", "**",   'U'},
        {"-t", "--",   ' '},
        {"-w", "OO",   ' '},
        {"-y", "..",   ' '},
        {NULL, "\0\0", 0}
};

/**
 * Adds up remaining arguments arguments
 * @param argc
 * @param argv
 * @return
 */
int cowsay_get_length(int argc, char **argv) {
    int i;
    int sum = 0;
    //for each arg ()
    for (i = 0; i < argc; i++)

        sum += strlen(argv[i]);
    sum += argc - 1;
    return sum;
}

void cowsay_print_singleline(int argc, char **argv, int length) {
    int i;
    putchar(' ');
    for (i = 0; i < length + 2; i++)
        putchar('_');
    printf("\n< ");

    for (i = 0; i < argc; i++) {
        printf("%s", argv[i]);
        putchar(' ');
    }
    printf(">\n ");
    for (i = 0; i < length + 2; i++)
        putchar('-');
    putchar('\n');
}

//actual output a line of text with  ___ above and --- bellow
void cowsay_print_string(char *str) {
    int i;
    int length = strlen(str);
    putchar(' ');
    for (i = 0; i < length + 2; i++)
        putchar('_');
    printf("\n< ");

    printf("%s", str);
    putchar(' ');

    printf(">\n ");
    for (i = 0; i < length + 2; i++)
        putchar('-');
    putchar('\n');
}

//void cowsay_print_top(int len) {
//
//}
//
//void cowsay_print_bottom(int len) {
//
//}
//
//void cowsay_print_aline(int len, char *buffer, size_t remaining) {
//
//}

void cowsay_print_multiline(int argc, char **argv) {

    // foll length of all string??? check
    int len = cowsay_get_length(argc, argv);

    int pref_len = 80;

    //OK LETS GET THE WIDTH OF OUR BuBLE!
    int w = (int) get_screen_width();
    if (w < 8) {
        printf("Warning: Looks like your in a small terminal pretending i didnt see that :)\n");
        w = 80;
    }

    // 80 char width and need 3 char pad on each side
    w = w - 6; //for warping chars < s >
    int bw = 0;
    if (w < len) {
        //strings to long
        if (w < pref_len) {
            //if screen lest then 40
            //use full width
            bw = w;
        } else if (w < pref_len * 2) {
            //up to 90 have a margin on the right
            bw = 3 * w / 4;
        } else {
            //if huge only use half
            bw = w / 2;
        }
    } else {
        //screen wider than length so lets show on one line
        if (w < pref_len) {
            bw = w;
        } else {
            bw = pref_len;
        }
    }


    pref_len = bw;
    // ok now we know how wide our buble should be
    // the strings should role in 6 fewer chars for  | text here for str len |
    int str_len = pref_len - 6;

//    char buffer[str_len*2];
    char *buffer = argv[0];

    printf("Well lets make a w: %d pref: %d, str_len: %d , len: %d \n", w, pref_len, str_len, len);
//NOW FOR EACH char IN EACH string IN ARGV

    int pos = 0; // out of each char in str_len
    int row = 0;
    int i;
    for (i = 0; i < argc; i++) {
        //for each string passed in as an argument.
//        fopen(argv[i], 'r')
        char c = ' ';
        char *s = argv[i];
        int n = strlen(s);

        //  +1,here
/*0123456789..............3+str_len = pref_len-6
 *                                  V|  V s[pref_len-3]
 0   _________________________________  \n
 1  / text thil..................here \ \n
 2 |  Even this one long argument ab- | \n
 3 |                   -solutly rocks | \n
 4  \______.   ,_____________________/  \n
 *          \ |
 *           \|
 *            \
 *
 *
 *
 *
*/

//      * We want to print top,
//      * then  start of line first then all msg
        // if this is the top :)'  _________\n'
//        printf("handling param %d : %s", i, s);

        int len = strlen(s);
        if (row == 0) {
            printf("   ");
            //no -1 = +1
            for (int j = 0; j < str_len; ++j) {
                printf("_");
            }
            printf("\n  /"); // and start of first line
            row++;
        }

        char next;
        //NOW lets print the meat
        for (int j = 0; j < n; ++j) {
            //for each char..
            int next = j + i;

            if (j < n - 1) {
                next = argv[i][j + 1];
            } else {
                next = 0;
            }
            c = argv[i][j];
            //if this pos is the end of the line go to next line before printing
            if (pos != 0 && (pos % str_len) == 0) {
                if (row == 1) {
                    printf("\\\n | "); //finish the line  and start the next
                } else {
                    printf(" |\n | "); //same
                }
//                pos++; // make sure to count this char??
                row++; // and were onto the net row
            }

            if (c == '\n' || (c == '\\' && next == 'n')) {
                //someone wants a new line here lets finish this bubble line;
                j++; // so that we skip the n in \n
                int remaining = str_len - pos % str_len;;
                for (int k = 0; k < remaining; ++k) {
                    printf(" ");
                    pos++;

                }
            } else {
                //well lets print a char and see where that puts us
                putchar(c);
                pos++;
            }


        }


        if (i < argc - 1) {
            printf(" "); // add a space between args
            pos++;
        }
        //i think were dont printing the bubble
    }

    //finish the last line
    int remaining = str_len - pos % str_len;
    for (int k = 0; k < remaining; ++k) {
        printf(" ");
        pos++;
    }
    printf(" |\n");



    //Finally put the bottom on it
    printf("  \\");
    for (int j = 0; j < str_len; ++j) {
        printf("_");
//            if(j == 7) {
//                putchar('\\')
//            } else if(j == 8) {
//                putchar('/')
//            }

    }
    printf("/ \n");// on to the next thing (stem?)


}

void cowsay_print_bubble(int argc, char **argv) {
    int length = cowsay_get_length(argc, argv);
    if (length < 40) {
        cowsay_print_singleline(argc, argv, length);
    } else {
        cowsay_print_multiline(argc, argv);
    }
}

void cowsay_print_cow(design_t design) {
    printf("        \\   ^__^\n"
           "         \\  (%s)\\_______\n"
           "            (__)\\        )\\/\\\n"
           "             %c  ||----w |\n"
           "                ||     ||\n",
           design.eyes, design.tongue);
}

int exec_cowsay(int argc, char **argv) {
    int i;
    design_t current = {NULL, "oo", ' '};

    // shift to first paramater??
    args_shift(1, &argc, &argv);

    //if next one is option do that
    if (argc == 1 && strcmp(argv[0], "--version") == 0) {
        printf("cowsay 1.0 (Fedux release 1.0)\n");
        printf("Copyright (C) 2012 Federico Pomar & Federico Bond\n");
        return 0;
    }

    if (argc == 1 && strcmp(argv[0], "--help") == 0) {
        /* Texts stolen from the Wikipedia article on cowsay: */
        /* http://en.wikipedia.org/wiki/Cowsay */
        printf("Usage: cowsay [OPTION] MESSAGE\n"
               "Prints a cute cow with the message in a speech bubble.\n\n"
               "Available designs:\n"
               "  -b    \"Borg\" mode, uses == in place of oo for the cow eyes.\n"
               "  -d    \"Dead\", uses XX.\n"
               "  -g    \"Greedy\", uses $$.\n"
               "  -p    \"Paranoid\", uses @@.\n"
               "  -s    \"Stoned\", uses ** to represent bloodshot eyes, plus a descending U to\n"
               "        represent an extruded tongue.\n"
               "  -t    \"Tired\", uses --.\n"
               "  -w    \"Wired\", uses OO.\n"
               "  -y    \"Youthful\", uses .. to represent smaller eyes.\n\n"
               "General help available by running 'help' command.\n");
        return 0;
    }

    //change eyes

    if (argc == 0) {
        printf("Usage: cowsay [-design] str1 str2 ... str3\n");
    }
    if (argc > 0) {
        for (i = 0; designs[i].opt != NULL; i++) {
            if (strcmp(argv[0], designs[i].opt) == 0) {
                current = designs[i];
                args_shift(1, &argc, &argv);
            }
        }
        cowsay_print_bubble(argc, argv);

    } else {
        cowsay_print_string(BLANK_WARNING);
    }

    cowsay_print_cow(current);

    return 0;
}

int main(int argc, char **argv) {
    return exec_cowsay(argc, argv);
}