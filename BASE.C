#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <programm/proj.h>
#include <dos.h>
static char*const VMEM = (char*)0xB8000000L;

void error_handler (int err) {
	switch (err) {
		case 0:
			fprintf (stderr,"\n>buffer size error");
			break;
		case 1:
			fprintf (stderr,"\n>start(x/y) or end(x/y) size error");
			break;
		case 2:
			fprintf (stderr,"\n>bordertype error");
			break;
		case 3:
			fprintf (stderr,"\n>window operation error");
			break;
		case 4:
			fprintf (stderr,"\n>window proportion error");
			break;
		case 5:
			fprintf (stderr,"\n>name size error");
			break;
	}
	exit(0);
}

void write_char (int x, int y, char ch, char attrib) {
    char *v;
    v = VMEM + x*160 + y*2;
	*(v++) = ch; *(v++) = attrib;
}

void write_string (int x,int y, char*string,char attrib) {
    char* v = VMEM;
    int i=0;
	v += x*160 + y*2;
    while (string[i]) {
		*(v++) = string[i];
		*(v++) = attrib;
		i++;
    }
}

void clear (int startx, int starty, int endx, int endy, char ch, char attrib) {
    int x, y;
    if ((endx <= startx) || (endy <= starty)) {
		error_handler(1);
		exit(1);
	}
    for (x = startx; x < endx; x++) {
        for (y = starty; y < endy; y++) {
			CHECK_XY (x, y);
            write_char (x, y, ch, attrib);
        }
    }
}

char* create_buffer (int startx, int starty, int endx, int endy){
	char* p;
	int size;
	if ((endx <= startx) || (endy <= starty)) {
		error_handler (1);
		exit (1);
	}
	size = (endx - startx + 1) * (endy - starty + 1) * sizeof(char);
	p = malloc (size);
	if (!p) {
		exit (1);
	}
	return p;
}

void getmem (int startx, int starty, int endx, int endy, char*buffer) {
	int x, y;
	char* v;
	if (buffer == NULL) {
		error_handler (0);
		exit (1);
	}
	if ((endx <= startx) || (endy <= starty)) {
		error_handler (1);
		exit (1);
	}

	for (x = startx; x <= endx; x++) {
		for(y = starty; y <= endy; y++) {
			v = VMEM + x*160 + y*2;
			*(buffer++) = *(v++);
			*(buffer++) = *(v++);
		}
	}
}
void putmem (int startx, int starty, int endx, int endy, char*buffer) {
	char* v;
	int x, y;

	if (buffer == NULL) {
		error_handler (0);
		exit (1);
	}
	if ((endx <= startx) || (endy <= starty)) {
		error_handler(1);
		free(buffer);
		exit(1);
	}
	for (x = startx; x <= endx; x++) {
		for (y = starty; y <= endy; y++) {
			v = VMEM + x*160 + y*2;
			*v++ = *buffer++;
			*v++ = *buffer++;
		}
	}
}
int mario(void) {
    clear (0,0,100,100,0xDB,BLACK);
    write_string(15,15,"oooo",GREEN | BGGREEN); write_string(14,16,"ooo",GREEN | BGGREEN); write_string(13,17,"ooo",RED | BGRED); write_string(13,22,"ooo",RED | BGRED); write_string(12,17,"oooooooo", RED | BGRED);
    write_string(15,23,"oooo",GREEN | BGGREEN); write_string(14,23,"ooo",GREEN | BGGREEN); write_string(12,17,"oooooooo",RED | BGRED); write_string(12,15,"oo",YELLOW | BGYELLOW); write_string(12,25,"oo",YELLOW | BGYELLOW);
    write_string(11,15,"ooo",YELLOW | BGYELLOW); write_string(11,24,"ooo",YELLOW | BGYELLOW); write_string(11,18,"oooooo",RED | BGRED); write_string(10,15,"oo",YELLOW | BGYELLOW); write_string(10,25,"oo",YELLOW | BGYELLOW);
    write_string(10,24,"o",GREEN | BGGREEN); write_string(10,17,"o",GREEN | BGGREEN); write_string(10,18,"o",RED | BGRED); write_string(10,23,"o",RED | BGRED);
    write_string(10,19,"o",YELLOW | BGYELLOW); write_string(10,22,"o",YELLOW | BGYELLOW); write_string(10,20,"oo",RED | BGRED);
    write_string(9,15,"oooooooooooo",GREEN | BGGREEN); write_string(9,19,"oooo",RED | BGRED); write_string(8,16,"oooooooooo",GREEN | BGGREEN); write_string(8,19,"o",RED | BGRED); write_string(8,22,"o",RED | BGRED);
    write_string(7,17,"oooooo",GREEN | BGGREEN); write_string(7,19,"o",RED | BGRED); write_string(7,22,"o",RED | BGRED); /* We love you */
    write_string(6,18,"ooooooo",YELLOW | BGYELLOW); write_string(5,18,"ooooooo",YELLOW | BGYELLOW); write_string(4,17,"oooooooooo",YELLOW | BGYELLOW);  write_string(5,16,"oo",GREEN | BGGREEN);  write_string(5,22,"oooo",GREEN | BGGREEN);
    write_string(4,16,"o",GREEN | BGGREEN); write_string(4,18,"oo",GREEN | BGGREEN); write_string(4,23,"o",GREEN | BGGREEN); write_string(3,18,"ooooooo",YELLOW | BGYELLOW); write_string(3,18,"ooooooo",YELLOW | BGYELLOW);
    write_string(3,17,"ooooooooo",YELLOW | BGYELLOW);  write_string(3,16,"o",GREEN | BGGREEN); write_string(3,22,"o",GREEN | BGGREEN); write_string(3,18,"o",GREEN | BGGREEN);
    write_string(2,17,"ooooooo",YELLOW | BGYELLOW);  write_string(2,17,"ooo",GREEN | BGGREEN); write_string(2,22,"o",GREEN | BGGREEN); write_string(1,17,"ooooooooo",RED | BGRED); write_string(0,18,"ooooo",RED | BGRED);
 	return 0;
}

void desktop (void) {
    clear(0, 0, 24, 79, 0xB0, WHITE | BGBLUE);
}

void border (int startx, int starty, int endx, int endy, char attrib, int type) {
    int x, y, a1, a2, a3, a4, a5, a6;
    switch (type) {
        case 1:
		      a1=0xC4; a2=0xB3; a3=0xDA;a4=0xBF;a5=0xC0;a6=0xD9;
		            break;
	    case 2:
		      a1=0xCD; a2=0xBA; a3=0xC9;a4=0xBB;a5=0xC8;a6=0xBC;
		      break;
    }
	CHECK_XY (startx, starty);
	CHECK_XY (endx, endy);
    for (x = startx; x < endx; x++) {
        write_char (x, starty, a2, attrib);
	    write_char (x, endy, a2, attrib);
    }
    for (y = starty; y < endy; y++) {
	    write_char (startx, y, a1 ,attrib);
	    write_char (endx, y, a1, attrib);
    }
    write_char (startx, starty, a3 ,attrib);
    write_char (endx, starty, a5 ,attrib);
    write_char (startx, endy, a4 ,attrib);
    write_char (endx, endy, a6 ,attrib);
}
void name(int startx, int starty, int endy, char*str, char attrib) {
    int y, len;
	CHECK_XY (startx, starty);
	CHECK_XY (endx, endy);
	if (endy < starty) {
		error_handler (1);
		exit (1);
	}
    len = strlen (str);
	if ((endy - starty) < (len + 1)) {
		error_handler (5);
		exit (1);
	}
    y = starty + (endy - starty - len) / 2;
    write_string (startx, y, str, attrib);
}

void clear_screen (void) {
	clear (0, 0, 24, 79, ' ', WHITE | BGBLACK);
}

int get_key (void) {
	_AH = 0x00;
	geninterrupt (0x16);
	return _AX;
}

void goto_xy (int x, int y) {
	CHECK_XY (x,y);
	_AH = 0x02;
	_DL = y;
	_DH = x;
	_BH = 0x00;
	geninterrupt (0x10);
}

