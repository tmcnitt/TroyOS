#include "io.h"
#include "fb.h"
#include "clib/string.h"

volatile char *fb = (char *) 0xC00B8000;
volatile unsigned short framebuffer_position = 0;

/**
 * Writes c to position c with foreground color fg and background color bg to the framebuffer
 * @param i  The framebuffer position to write to
 * @param c  The char to write
 * @param fg The foreground color
 * @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg){
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}



/**
 * Moves the cursor to the pos
 * @param pos The position to move the cursor
 */
void fb_move_cursor(unsigned short pos){
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

int fb_color_write(char* buf, unsigned char fg, unsigned char bg){
  unsigned int len = strlen(buf);
  unsigned int i = 0;
  for (i = 0; i < len; i++) {
    if(buf[i] == '\n'){
      framebuffer_position += 80;
      framebuffer_position -= framebuffer_position % 80;
      fb_move_cursor(framebuffer_position);
    }else if (buf[i] == '\b'){
      framebuffer_position--;
      fb_move_cursor(framebuffer_position);
      fb_write(" ");
      framebuffer_position--;
      fb_move_cursor(framebuffer_position);
    } else if (buf[i] == '\t'){
      fb_write("     ");
    } else {
      fb_write_cell(framebuffer_position*2, buf[i], bg, fg);
      fb_move_cursor(framebuffer_position + 1);
      framebuffer_position += 1;
    }
  }
  return len;
}

/**
 * Writes the len characters of buf to the screen and moves the cursor
 * @param  buf The text to write
 * @return  returns len
 */
int fb_write(char* buf){
  int len = fb_color_write(buf, 15, 0);
  return len;
}


/**
 * Writes the text and then the status in a format
 * The status is put at x 50
 * @param text   The text
 * @param status The status of the function. 1 for success
 */
void fb_status(char * text, int status){
  fb_write(text);

  int len = strlen(text);

  framebuffer_position -= len;
  framebuffer_position += 50;
  fb_move_cursor(framebuffer_position);


  if(status){
    fb_color_write(" [  PASSED  ] \n", 10, 0);
  }else {
    fb_color_write(" [  FAILED  ] \n", 4, 0);
  }
}

/**
 * Clears the framebufer
 */
void fb_clear(){
  unsigned int i;
  for(i = 0; i< (80*25); i++){
    fb_write(" ");
  }
  framebuffer_position = 0;
  fb_move_cursor(0);
}
