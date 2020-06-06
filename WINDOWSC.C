#include <programm/proj.h>
#include <programm/windowsh.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>

static window_t *windows[WIN_MAXCOUNT];
static int wincount = 0;

window_t* window_create (char* name, int startx, int endx, int starty, int endy, char attrib, int type) {

    window_t *w = NULL;

    w = malloc (sizeof (window_t));
    if (!w) {
		fprintf (stderr, "Error in window_create");
		exit (1);
	}
    w -> startx = startx;
    w -> starty = starty;
    w -> endx = endx;
    w -> endy = endy;
    w -> attrib = attrib;
    w -> type = type;
    strcpy (w -> name, name);
    w -> p = malloc (2*sizeof(char)*(endx-startx+1)*(endy-starty+1));
    if (w -> p == NULL) {
        free (w);
        return NULL;
    }
    w -> active = 0;
    w -> curx = 0;
    w -> cury = 0;
    return w;
}

void window_open (window_t*w) {
    if (w==NULL) {error_handler(3); exit(1);}
    if ((w -> endy - w -> starty) < (w -> endx - w -> startx)) {
        error_handler (4);
        exit (1);
    }
    getmem (w -> startx, w -> starty, w -> endx, w -> endy, w -> p);
    clear (w -> startx, w -> starty, w -> endx, w -> endy, ' ', w -> attrib);
    border (w -> startx, w -> starty, w -> endx, w -> endy, w -> attrib, w -> type);
    name (w -> startx, w -> starty, w -> endy, w -> name, w -> attrib);
    w -> curx=0;
    w -> cury=0;
    w -> active=1;
    windows[wincount] = w;
    wincount++;
}

void window_close (window_t*w) {
    if (windows[wincount-1] == w) {
 		putmem(w -> startx, w -> starty, w -> endx, w -> endy, w -> p);
		w -> active=0;
		wincount--;
	}
    else {
        error_handler (3);
        exit (1);
    }
}

void window_destroy (window_t*w) {
    free (w -> p);
    free (w);
}
int window_getkey (void) {
	int code;
	code = get_key ();

	if(code % 0x100 == 0) {
		code = code / 0x100 + 0x100;
	} else {
		code = code % 0x100;
	}
	return code;
}

int window_xy (window_t*w, int x, int y){
	int endx = w -> endx - w -> startx - 2;
	int endy = w -> endy - w -> starty - 2;

	if (!w -> active) return 1;
	if (y < 0 && x <= 0) return 1;
	if ((y > endy && x == endx) || x > endx) return 1;

	if (y > endy && x < endx) {
		w -> cury = 0; w -> curx++;
	} else if (y < 0 && x > 0) {
		w -> curx--; w -> cury = endy;
	} else {
			w -> cury = y; w -> curx = x;
	}
	goto_xy (w -> startx + w -> curx+1,w -> starty + w -> cury + 1);
	return 0;
}

void window_putchar (window_t*w, char ch) {
	int x, y;
	if (!w -> active) {
        error_handler(3);
        exit(1);
    }
	if (window_xy (w, w -> curx, w -> cury) == 0) {
		x = w -> startx + w -> curx + 1, y = w -> starty + w -> cury + 1;
		write_char (x, y, ch, w -> attrib);
	}
}

void window_gets (window_t* w) {
	int x, y, code;
	int curx = w -> curx, cury = w -> cury;
	char*buffer = create_buffer (curx, cury, w -> endx-1, w -> endy-1);
	if (buffer == NULL) {
        error_handler(1);
        exit(1);
    }
	getmem(w -> startx+curx+1, w -> starty+cury+1, w -> endx-1, w -> endy-1,buffer);
	while (1) { /* We love you! */
		x = w -> curx, y = w -> cury;
		code = window_getkey ();
		if (code > 0xFF && code != F10) continue;
		switch (code) {
			case F10:
				free (buffer);
				return;
			case ESC:
				putmem (w -> startx + curx+1, w -> starty + cury + 1, w -> endx - 1, w -> endy - 1, buffer);
				free (buffer);
				window_xy (w, curx, cury);
				return;
			case ENTER:
				window_xy (w, x + 1, 0);
				break;
			case BKSP:
				if (window_xy (w, x, y - 1) == 0) {
					window_putchar (w, ' ');
				}
				break;
			default:
				window_putchar (w, (char)code);
				if (window_xy (w, x, y + 1)) window_putchar (w, ' ');
		}
    }
}

