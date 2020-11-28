#include <msp430.h>
#include "libTimer.h"
#include "play.h"
#include "buzzer.h"
#include <string.h>

/* I added this file with the function play to make it easier to play certain notes, but since I had to change the format of the notes, it is not as efficient as it was originally. Still, it helped efficiently to make songs.*/

void play(unsigned char note)
{
  if(note == 0x64)
    buzzer_set_period(5102.10);

  else if(note == 0xA4)
    buzzer_set_period(4545.45);

  else if(note == 0xB4)
    buzzer_set_period(4049.54);

  else if(note == 0xC5)
    buzzer_set_period(3822.25);

  else if(note == 0xD5)
    buzzer_set_period(3405.24);

  else if(note == 0xDC)
    buzzer_set_period(3214.12);

  else if(note == 0xE5)
    buzzer_set_period(3033.72);

  else if(note == 0xF5)
    buzzer_set_period(2863.45);

  else if(note == 0x65)
    buzzer_set_period(2551.04);

  else if(note == 0x6C)
    buzzer_set_period(2407.87);

  else if(note == 0xA5)
    buzzer_set_period(2272.72);

  else if(note == 0xB5)
    buzzer_set_period(2024.76);

  else  /*If it receives something that is not valid, the buzzer will just go silent */
    buzzer_set_period(0);
}

