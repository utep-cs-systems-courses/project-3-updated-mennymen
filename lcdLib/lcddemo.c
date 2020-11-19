
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
u_int ballColor = COLOR_YELLOW;

void ballColorAdvance()
{
  switch(ballColor){
  case COLOR_RED:
    ballColor = COLOR_ORANGE;
    break;

  case COLOR_ORANGE:
    ballColor = COLOR_YELLOW;
    break;
    
  case COLOR_YELLOW:
    ballColor = COLOR_GREEN;
    break;
    
  case COLOR_GREEN:
    ballColor = COLOR_BLUE;
    break;
    
  case COLOR_BLUE:
    ballColor = COLOR_VIOLET;
    break;
    
  case COLOR_VIOLET:
    ballColor = COLOR_RED;
    break;
  }
}


/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  clearScreen(COLOR_BLACK);

  while(1){
    drawString8x12(20,20, "hello", COLOR_GREEN, COLOR_BLACK);
    if(right && down){
      if(x < 120 && y < 150){
	fillRectangle(x,y,10,10, COLOR_BLACK);
	fillRectangle(++x,++y,10,10, ballColor);
      }
      
      if (y >= 150){
	down = !down;
	ballColorAdvance();
      }

      if (x >= 120){
	right = !right;
	ballColorAdvance();
      }

    }

    else if(right && !down){
      if(x < 120 && y > 0){
	fillRectangle(x,y,10,10, COLOR_BLACK);
	fillRectangle(++x,--y,10,10, ballColor);
      }
      
      if (y <= 0){
	down = !down;
	ballColorAdvance();
      }

      if (x >= 120){
	right = !right;
	ballColorAdvance();
      }

    }

    else if(!right && down){
      if(x > 0 && y < 150){
	fillRectangle(x,y,10,10, COLOR_BLACK);
	fillRectangle(--x,++y,10,10, ballColor);
      }
      
      if (y >= 150){
	down = !down;
	ballColorAdvance();
      }

      if (x <= 0){
	right = !right;
	ballColorAdvance();
      }

    }
    else if(!right && !down){
      if(x > 0 && y > 0){
	fillRectangle(x,y,10,10, COLOR_BLACK);
	fillRectangle(--x,--y,10,10, ballColor);
      }
      
      if (y <= 0){
	down = !down;
	ballColorAdvance();
      }
      
      if (x <= 0){
	right = !right;
	ballColorAdvance();
      }

    }
    
  }
  //drawString8x12(20,20, "hello", COLOR_GREEN, COLOR_RED);
  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  //drawLeftPaddle(5,30,COLOR_WHITE);
  //drawRightPaddle(120,30, COLOR_WHITE);
}
