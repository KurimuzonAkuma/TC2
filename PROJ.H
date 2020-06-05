#if !defined (_PROJ_H_)
#define _PROJ_H_

#if defined DEBUGGING_INFORMATION
#define CHECK_XY (x, y) \
 do { \
	 if (x < 0 || x > 24 || y < 0 || y > 79) { \
		 fprintf (stderr,"\n Wrong coords:\n  \"%s\" in %u line.", __FILE__, __LINE__); \
		 exit (1); \
	 } \
 } while (0)
#else
#define CHECK_XY(x,y)do{}while(0)
#endif

enum COLORS {
 BLACK = 0x0000,
 BLUE = 0x0001,
 GREEN = 0x0002,
 CYAN = 0x0003,
 RED = 0x0004,
 MAGENTA = 0x0005,
 BROWN = 0x0006,
 LIGHTGRAY = 0x0007,
 DARKGRAY = 0x0008,
 LIGHTBLUE = 0x0009,
 LIGHTGREEN = 0x000A,
 LIGHTCYAN = 0x000B,
 LIGHTRED = 0x000C,
 LIGHTMAGENTA = 0x000D,
 YELLOW = 0x000E,
 WHITE = 0x000F,
 BGBLACK = 0x0000,
 BGBLUE = 0x0010,
 BGGREEN = 0x0020,
 BGCYAN = 0x0030,
 BGRED = 0x0040,
 BGMAGENTA = 0x0050,
 BGBROWN = 0x0060,
 BGLIGHTGRAY = 0x0070,
 BGLIGHTBLUE = 0x0090,
 BGLIGHTGREEN = 0x00A0,
 BGLIGHTCYAN = 0x00B0,
 BGLIGHTRED = 0x00C0,
 BRLIGHTMAGENTA = 0x00D0,
 BGYELLOW = 0x00E0,
 BGWHITE = 0x00F0,
 BLINK = 128,
 SINGLE_BORDER = 1,
 DUAL_BORDER = 2
};

void error_handler (int err);
void write_char (int x, int y, char ch, char attrib);
void write_string (int x, int y, char*string, char attrib);
void clear (int startx, int starty, int endx, int endy, char ch, char attrib);
char* create_buffer (int startx, int starty, int endx, int endy);
void getmem (int startx, int starty, int endx, int endy, char*buffer);
void putmem (int startx, int starty, int endx, int endy, char*buffer);
mario (void);
void desktop (void);
void border (int startx, int starty, int endx, int endy, char attrib, int type);
void name (int startx, int starty, int endy, char*str, char attrib);
void clear_screen (void);
int get_key (void);
void goto_xy (int x, int y);
#endif
