#include <stdlib.h>
#include <proj.h>
#include <windowsh.h>
#include <conio.h>
int main() {
    window_t *w1, *w2;
      w1 = window_create ("Window 1", 3, 23, 3, 30, WHITE | BGBLUE, DUAL_BORDER);
      w2 = window_create ("Window 2", 5, 12, 20, 70, WHITE | BGRED, SINGLE_BORDER);
    	clear_screen();
    	window_open (w1);
    	window_open (w2);
    	window_xy (w1, 0, 0);
    	window_gets (w2);
    	window_xy (w1, 2, 1);
    return 0;
}