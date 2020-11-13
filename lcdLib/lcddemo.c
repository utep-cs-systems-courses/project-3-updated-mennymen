/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

u_char width = screenWidth, height = screenHeight;
char x = screenWidth/2;
char y = screenHeight/2;
char down = 1;
char right = 1; 

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  clearScreen(COLOR_BLUE);

  while(1){
    drawString8x12(20,20, "hello", COLOR_GREEN, COLOR_RED);
    if(right && down){
      if(x < 120 && y < 150){
	fillRectangle(x,y,10,10, COLOR_BLUE);
	fillRectangle(++x,++y,10,10, COLOR_RED);
      }
      
      if (y >= 150){
	down = !down;
      }

      if (x >= 120)
	right = !right;
    }

    else if(right && !down){
      if(x < 120 && y > 0){
	fillRectangle(x,y,10,10, COLOR_BLUE);
	fillRectangle(++x,--y,10,10, COLOR_RED);
      }
      
      if (y <= 0)
	down = !down;

      if (x >= 120)
	right = !right;
    }

    else if(!right && down){
      if(x > 0 && y < 150){
	fillRectangle(x,y,10,10, COLOR_BLUE);
	fillRectangle(--x,++y,10,10, COLOR_RED);
      }
      
      if (y >= 150)
	down = !down;

      if (x <= 0)
	right = !right;
    }
    else if(!right && !down){
      if(x > 0 && y > 0){
	fillRectangle(x,y,10,10, COLOR_BLUE);
	fillRectangle(--x,--y,10,10, COLOR_RED);
      }
      
      if (y <= 0)
	down = !down;
      
      if (x <= 0)
	right = !right;
    }    
  }
  //drawString8x12(20,20, "hello", COLOR_GREEN, COLOR_RED);
  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  
}
