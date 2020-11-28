#include <msp430.h>
#include "led.h"

unsigned char red_on = 0, green_on = 0;
unsigned char led_changed = 0;

static char redVal[] = {0, LED_RED}, greenVal[] = {0, LED_GREEN};

void led_init()
{
  P1DIR |= LEDS;// bits attached to leds are output
  led_changed = 1;
  led_update();
}

void led_update()
{
  if (led_changed) {
    char ledFlags = redVal[red_on] | greenVal[green_on];

    P1OUT &= (0xff^LEDS) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;     // set bit for on leds
    led_changed = 0;
  }
}

void red50() /* Red led shines at 50% intensity */
{
  char changed = 0;
  static char state = 0;
  switch(state){

  case 0: /* The led is on for 1 out of the 2 states */
    red_on = 1;
    state = 1;
    changed = 1;
    break;

  case 1:
    red_on = 0;
    state = 0;
    changed = 1;
  }

  led_changed = changed;
  led_update();
}

void leds_advance(char blink_state)
{
  switch(blink_state){
  case 0: /* Red at 100% */
    red_on = 1;
    break;

  case 1:
    red50(); /* Red at 50% */
    break;

  case 2: /* Red off */
    red_on = 0;
    break;
  }
  led_changed = 1;
  led_update();
}
