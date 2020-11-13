#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

#define LED_GREEN BIT6             // P1.6


short redrawScreen = 1;
u_int fontFgColor = COLOR_RED;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount == 25) {		/* once/sec */
    secCount = 0;
    if (fontFgColor == COLOR_RED)
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
      fontFgColor = COLOR_RED;
    
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
  
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      fillRectangle(20,20,50,50, fontFgColor);
      //clearScreen(fontFgColor);
      //drawString5x7(20,20, "hello", fontFgColor, COLOR_BLUE);
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}

    
    



