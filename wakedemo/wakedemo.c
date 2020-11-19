#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "p2switches.h"

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
u_int fontFgColor = COLOR_RED;

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




void wdt_c_handler()
{
  static int secCount = 0;
  //P1OUT |= LED_GREEN;
  secCount ++;
  if (secCount == 7) {		/* once/sec */
    secCount = 0;
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

    /*if (fontFgColor == COLOR_RED)
      fontFgColor = COLOR_ORANGE;

    else if (fontFgColor == COLOR_ORANGE)
      fontFgColor = COLOR_YELLOW;

    else if (fontFgColor == COLOR_YELLOW)
      fontFgColor = COLOR_GREEN;

    else if (fontFgColor == COLOR_GREEN)
      fontFgColor = COLOR_BLUE;

    else if (fontFgColor == COLOR_BLUE)
      fontFgColor = COLOR_VIOLET;

    else if (fontFgColor == COLOR_VIOLET)
    fontFgColor = COLOR_RED;*/
    
    //fontFgColor = (fontFgColor == COLOR_GREEN) ? COLOR_BLACK : COLOR_GREEN;
    redrawScreen = 1;
  }
}
  

void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  p2sw_init(15);
  or_sr(0x8);			/* GIE (enable interrupts) */
  u_char width = screenWidth, height = screenHeight;
  //char x = 50;
  //char y = 50;
  char leftPaddlePos = 30;
  char rightPaddlePos = 30;

  
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
  /* if (redrawScreen) {
      redrawScreen = 0;
      fillRectangle(20,20,50,50, fontFgColor);*/
      //clearScreen(fontFgColor);
      //drawString5x7(20,20, "hello", fontFgColor, COLOR_BLUE);
      // }
    u_int switches = p2sw_read(), i;
    char str[5];
    for (i = 0; i < 4; i++){
      str[i] = (switches & (1<<i)) ? '-' : '0'+i;
      if(str[3] == '3' && rightPaddlePos < 145){
	drawRightPaddle(120,rightPaddlePos, COLOR_BLACK);
	rightPaddlePos++;
	drawRightPaddle(120,rightPaddlePos, COLOR_WHITE);
      }

      if(str[0] == '0' && leftPaddlePos > 0){
	drawLeftPaddle(5,leftPaddlePos,COLOR_BLACK);
	leftPaddlePos--;
	drawLeftPaddle(5,leftPaddlePos,COLOR_WHITE);
      }

      if(str[1] == '1' && leftPaddlePos < 145){
        drawLeftPaddle(5,leftPaddlePos,COLOR_BLACK);
	leftPaddlePos++;
	drawLeftPaddle(5,leftPaddlePos,COLOR_WHITE);
      }

      if(str[2] == '2' && rightPaddlePos > 0){
        drawRightPaddle(120,rightPaddlePos, COLOR_BLACK);
	rightPaddlePos--;
	drawRightPaddle(120,rightPaddlePos, COLOR_WHITE);
      }
    }
    str[4] = 0;
    drawString5x7(20,20, str, COLOR_GREEN, COLOR_BLACK);


    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */

  }
}  


    
    



