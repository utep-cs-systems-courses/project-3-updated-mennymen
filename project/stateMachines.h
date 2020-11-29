#ifndef stateMachine_included
#define stateMachine_included

void zelda_advance();
void ballSoundAdvance(char ballSoundState);
signed char ballColorAdvance();
char ballSoundUpdateState(char ballSoundState);
void colorAdvance();
void red75();
void red50();
void red25();
void leds_advance(char blink_state);

#endif // included
