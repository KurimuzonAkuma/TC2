#include <stdlib.h>
#include <proj.h>
#include <windowsh.h>
#include <conio.h>
int main() {
    window_t *w1, *w2;
      w1 = window_create ("Window 1", 3, 17, 3, 30, GREEN | BGBLACK, DUAL_BORDER);
      w2 = window_create ("Window 2", 5, 20, 25, 70, RED | BGWHITE, SINGLE_BORDER);
    	clear_screen();
    	window_open (w1);
    	window_open (w2);
    	window_xy (w1, 0, 0);
    	window_gets (w2);
    	window_xy (w1, 2, 1);
    return 0;
}
