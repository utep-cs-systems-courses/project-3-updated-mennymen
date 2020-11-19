/** \file lcddemo.c
 *  \brief A simple demo that draws a string and circle
 */

#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>


/** Initializes everything, clears the screen, draws "hello" and the circle */
void main()
{
  configureClocks();
  lcd_init();
  p2sw_init(15);
  or_sr(0x8);			/* GIE (enable interrupts) */
  u_char width = screenWidth, height = screenHeight;
  //char x = 50;
  //char y = 50;
  char leftPaddlePos = 30;
  char rightPaddlePos = 30;
  clearScreen(COLOR_BLUE);

  drawLeftPaddle(5,leftPaddlePos,COLOR_WHITE);
  drawRightPaddle(120,rightPaddlePos, COLOR_WHITE);

  while (1) {
    u_int switches = p2sw_read(), i;
    char str[5];
    for (i = 0; i < 4; i++){
      str[i] = (switches & (1<<i)) ? '-' : '0'+i;
      if(str[3] == '3' && rightPaddlePos < 145){
	drawRightPaddle(120,rightPaddlePos, COLOR_BLUE);
	rightPaddlePos++;
	drawRightPaddle(120,rightPaddlePos, COLOR_WHITE);
      }

      if(str[0] == '0' && leftPaddlePos > 0){
	drawLeftPaddle(5,leftPaddlePos,COLOR_BLUE);
	leftPaddlePos--;
	drawLeftPaddle(5,leftPaddlePos,COLOR_WHITE);
      }

      if(str[1] == '1' && leftPaddlePos < 145){
        drawLeftPaddle(5,leftPaddlePos,COLOR_BLUE);
	leftPaddlePos++;
	drawLeftPaddle(5,leftPaddlePos,COLOR_WHITE);
      }

      if(str[2] == '2' && rightPaddlePos > 0){
        drawRightPaddle(120,rightPaddlePos, COLOR_BLUE);
	rightPaddlePos--;
	drawRightPaddle(120,rightPaddlePos, COLOR_WHITE);
      }
    }
    str[4] = 0;
    drawString5x7(20,20, str, COLOR_GREEN, COLOR_BLUE);
    
  }

  /*drawString5x7(10,10, "switches:", COLOR_GREEN, COLOR_BLUE);

  fillRectangle(x,y,10,10, COLOR_RED);

  while (1) {
    u_int switches = p2sw_read(), i;
    char str[5];
    for (i = 0; i < 4; i++){
      str[i] = (switches & (1<<i)) ? '-' : '0'+i;
      if(str[3] == '3' && x < 120){
	fillRectangle(x,y,10,10, COLOR_BLUE);
	x++;
	fillRectangle(x,y,10,10, COLOR_RED);
      }

      if(str[0] == '0' && x > 0){
	fillRectangle(x,y,10,10, COLOR_BLUE);
	x--;
	fillRectangle(x,y,10,10, COLOR_RED);
      }

      if(str[1] == '1' && y < 150){
	fillRectangle(x,y,10,10, COLOR_BLUE);
	y++;
	fillRectangle(x,y,10,10, COLOR_RED);
      }

      if(str[2] == '2' && y > 0){
	fillRectangle(x,y,10,10, COLOR_BLUE);
	y--;
	fillRectangle(x,y,10,10, COLOR_RED);
      }
    }
    str[4] = 0;
    drawString5x7(20,20, str, COLOR_GREEN, COLOR_BLUE);
    
    } */
}
