#include <msp430.h>
#include "stateMachines.h"
#include "buzzer.h"
#include "play.h"
#include "lcdutils.h"
#include "led.h"


extern char ballColorState;
extern unsigned int ballColor;
extern char blink_state;

static unsigned char zelda_notes[32] = {0x65,0x64,0xC5,0xE5,0xDC,0x64,0xB5,0xB4,0xA5,0xC5,
					0xE5,0xA5,0x65,0xC5,0xD5,0xE5,0xA5,0xC5,0xF5,0xA5,
					0x6C,0xC5,0xD5,0xF5,0xE5,0x64,0xC5,0xE5,0xD5,0xA4,
					0xB4,0xD5};


void zelda_advance() // Reused from project 2
{
  static unsigned char state = 0;
  play(zelda_notes[state]);
  state = (state+1)%32;
}

void ballSoundAdvance(char ballSoundState)   // This function makes the ball bounce sounds 
{
  switch (ballSoundState) {
  case 0:
    buzzer_set_period(5000);
    break;

  case 1:
    buzzer_set_period(8000);
    break;
  }
}


signed char ballColorAdvance() // This function makes the ball change color whenever it touches something
{
  switch (ballColorState) {
  case 0:
    ballColor = COLOR_ORANGE;  // Only in this case, it will return -1
    return -1;
    break;

  case 1:
    ballColor = COLOR_YELLOW; // Every other case will return 1
    break;

  case 2:
    ballColor = COLOR_GREEN;
    break;

  case 3:
    ballColor = COLOR_BLUE;
    break;

  case 4:
    ballColor = COLOR_VIOLET;
    break;

  case 5:
    ballColor = COLOR_RED;
    break;
  }
  return 1;
}



void red75() /* Red led shines at 75% intensity */
{
  char changed = 0;
  static char state = 0;
  switch(state){
  case 0: /* The led is on for 3 out of the 4 states */
    red_on = 1;
    state = 1;
    changed = 1;
    break;

  case 1:
    red_on = 1;
    state = 2;
    break;

  case 2:
    red_on = 1;
    state = 3;
    break;

  case 3:
    red_on = 0;
    state = 0;
    changed = 1;
  }

  led_changed = changed;
  led_update();
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



void red25() /* Red led shines at 25% intensity */
{
  char changed = 0;
  static char state = 0;
  switch(state){
  case 0: /* The led is on for 1 out of the 4 states */
    red_on = 0;
    state = 1;
    changed = 1;
    break;

  case 1:
    red_on = 0;
    state = 2;
    break;

  case 2:
    red_on = 0;
    state = 3;
    break;

  case 3:
    red_on = 1;
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
    red75(); /* Red at 75% */
    break;
    
  case 2:
    red50(); /* Red at 50% */
    break;

  case 3:
    red25(); /* Red at 25% */
    break;

  case 4: /* Red off */
    red_on = 0;
    break;
  }
  led_changed = 1;
  led_update();
}
