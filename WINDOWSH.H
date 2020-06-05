#if !defined (_WINDOWSH_H_)
#define _WINDOWSH_H_
#define WIN_MAXCOUNT 20

enum KEY_BUTTONS {
    UP = 0x148,
    LEFT = 0x14B,
    DOWN = 0x150,
    RIGHT = 0x14D,
    PGUP = 0x149,
    PGDN = 0x151,
    HOME = 0x147,
    END = 0x14F,
    INSERT = 0x152,
    DELETE = 0x153,
    F1 = 0x13B,
    F2 = 0x13C,
    F3 = 0x13D,
    F4 = 0x13E,
    F5 = 0x13F,
    F6 = 0x140,
    F7 = 0x141,
    F8 = 0x142,
    F9 = 0x143,
    F10 = 0x144,
    F11 = 0x157,
    F12 = 0x158,
    BKSP = 0x08,
    ENTER = 0x0D,
    ESC = 0x1B
};

typedef struct window {
    int startx, starty, endx, endy;
    int curx, cury, active;
	int attrib;
	int type;
	char name[80];
	char*p;
} window_t;

window_t* window_create (char* name, int startx, int endx, int starty, int endy, char attrib, int type);
void window_open (window_t*w);
void window_close (window_t*w);
void window_destroy (window_t*w);
int window_getkey (void);
int window_xy (window_t*w, int x, int y);
void window_putchar (window_t*w, char ch);
void window_gets (window_t* w);
#endif

