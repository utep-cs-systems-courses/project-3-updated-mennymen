#include <msp430.h>
#include <libTimer.h>
#include <stdlib.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "p2switches.h"
#include "buzzer.h"
#include "led.h"
#include "stateMachines.h"
#include "play.h"

short redrawScreen = 1;
u_int fontFgColor = COLOR_RED;
u_char width = screenWidth, height = screenHeight;
char x = screenWidth/2;
char y = screenHeight/2;
char down = 1;
char right = 0;
char leftPaddlePos = 30;
char rightPaddlePos = 30;
u_int ballColor = COLOR_BLUE;
int p1score = 0;
char p1char[3];
int p2score = 0;
char p2char[3];
char gameOn = 1;
char ballSoundState = 0;
char blink_state;
char songCount = 0;
char ballColorState = 3;

void wdt_c_handler()
{
  static int secCount = 0;
  static int soundCount = 0;
  static int blinkCount = 0;
  secCount ++;

  if (!gameOn && songCount == 32){  // After playing the song, the screen goes blank and some stars are drawn on the screen and the red led keeps cycling
      play(0);
      clearScreen(COLOR_BLACK);
      drawStar(50,50, COLOR_GREEN);
      drawStar(100,100, COLOR_RED);
      drawStar(124,79, COLOR_YELLOW);
      drawStar(21, 81, COLOR_ORANGE);
      drawStar(64,37, COLOR_VIOLET);
      drawStar(5,24, COLOR_BLUE);
      drawStar(120,8, COLOR_GREEN);
      drawStar(40,130, COLOR_RED);
      drawStar(79,98, COLOR_YELLOW);
      drawStar(87, 115, COLOR_ORANGE);
      drawStar(97,5, COLOR_VIOLET);
      drawStar(108,18, COLOR_BLUE);
      songCount = 33;
    }

  else if (!gameOn && blinkCount != 100) {   // When the game is over, the program will start blinking the red led and play a song 
    leds_advance(blink_state);
    blinkCount++;
  } else if (!gameOn && blinkCount == 100){
    blinkCount = 0;
    blink_state = (blink_state+1)%5;
    if (songCount < 32){  // It will only play the song once 
      zelda_advance();
      songCount++;
    }

  } 


  
  if(soundCount > 0 && soundCount < 5){ // This is used to make the bouncing sound play for 1/50 of a second 
    soundCount++;

  } else if(soundCount == 5){
    soundCount = 0;
    buzzer_set_period(0);  // Stop the bouncing sound 
  }

  if (secCount == 5 && gameOn) { // secCount is used to set the speed of the ball  
    secCount = 0;
    if(right && down){  // If the ball is coming down and moving to the right //
      if(x < 110 && y < 150){ // If it doesn't collide with the bottom wall, right paddle, or scores //
	fillRectangle(x,y,10,10, COLOR_BLACK); 
	fillRectangle(++x,++y,10,10, ballColor); //The ball "moves" to the right and down by one pixel //
      }

      if (y >= 150){ // If it touches the bottom wall, it will now go up
	down = !down;
	colorAdvance();
      }

      if (x >= 110 && (y >= rightPaddlePos - 10 && y <= rightPaddlePos + 15)){ // If it collides with the right paddle
	right = !right; // It will now go to the left
	colorAdvance();
	ballSoundState = ballSoundUpdateState(ballSoundState); // Play bouncing sound
	soundCount++;

      } else if (x >= 110 && (y < rightPaddlePos - 10 || y > rightPaddlePos + 15)){ // If the right paddle misses the ball 
	fillRectangle(x,y,10,10, COLOR_BLACK);
	x = screenWidth/2;
	y = screenHeight/2;
	fillRectangle(x,y,10,10, ballColor); // The ball goes back to the center
	p1score++;  // P1 score increases by one
	itoa(p1score, p1char, 10);
	drawString8x12(5, 0, p1char, COLOR_WHITE, COLOR_BLACK);  // Screen updates P1 score

	if(p1score == 10){ // When P1 reaches 10 points, he/she wins, a message is displayed and the game is over
	  drawString8x12(20,30, "P1 WINS!", COLOR_WHITE, COLOR_BLACK);
	  gameOn = 0;
	}
	right = !right;
	down = !down;
      }
      
    } else if(right && !down){ // If the ball is going up and right
      if(x < 110 && y > 21){   // If the ball doesn't collide with a wall, it just keeps going the same direction
	fillRectangle(x,y,10,10, COLOR_BLACK);
	fillRectangle(++x,--y,10,10, ballColor);
      }
 
      if (y <= 21){ // If it collides with the top wall, it will now go up
	down = !down;
	colorAdvance();
      }

      if (x >= 110 && y >= rightPaddlePos - 10 && y <= rightPaddlePos + 15){ // If it touches the right paddle, it will now move to the left
	right = !right;
	colorAdvance();
	ballSoundState = ballSoundUpdateState(ballSoundState);
       	soundCount++;

      } else if (x >= 110 && (y < rightPaddlePos - 10 || y > rightPaddlePos + 15)){ // If it misses the right paddle, P1 scores, the ball goes to the center and the score is updated
	fillRectangle(x,y,10,10, COLOR_BLACK);
	x = screenWidth/2;
	y = screenHeight/2;
	fillRectangle(x,y,10,10, ballColor);
	p1score++;
	itoa(p1score, p1char, 10);
	drawString8x12(5, 0, p1char, COLOR_WHITE, COLOR_BLACK);

	if(p1score == 10){ // If P1 reaches 10 points, he/she wins, the game is over and a message is displayed
	  drawString8x12(20, 30, "P1 WINS!", COLOR_WHITE, COLOR_BLACK);
	  gameOn = 0;
	}
	
	right = !right;
	down = !down;
      }

    } else if(!right && down){ // If the ball is going to the left and down
      if(x > 0 && y < 150){ // If it doesn't collide, it keeps moving on the same direction
	fillRectangle(x,y,10,10, COLOR_BLACK);
	fillRectangle(--x,++y,10,10, ballColor);
      }

      if (y >= 150){ // If it collides with the bottom wall, it will now go up
	down = !down;
	colorAdvance();
      }

      if (x <= 10 && (y >= leftPaddlePos - 10 && y <= leftPaddlePos + 15)){ // If it collides with the left paddle
	right = !right;
	colorAdvance();
	ballSoundState = ballSoundUpdateState(ballSoundState);
	soundCount++;

      } else if (x <= 10 && (y < leftPaddlePos - 10 || y > leftPaddlePos + 15)){ // If it misses the left paddle, P2 will score and it will be updated on the screen
	fillRectangle(x,y,10,10, COLOR_BLACK);
	x = screenWidth/2;
	y = screenHeight/2;
	fillRectangle(x,y,10,10, ballColor);
	p2score++;
	itoa(p2score, p2char, 10);
	drawString8x12(100, 0, p2char, COLOR_WHITE, COLOR_BLACK);

	if(p2score == 10){
	  drawString8x12(20, 30, "P2 WINS!", COLOR_WHITE, COLOR_BLACK);
	  gameOn = 0;
	}

	right = !right;
	down = !down;
      }

    } else if(!right && !down){ // If the ball is going up and left
      if(x > 0 && y > 21){ // If it doesn't collide, it will just keep moving in the same direction
	fillRectangle(x,y,10,10, COLOR_BLACK);
	fillRectangle(--x,--y,10,10, ballColor);
      }

      if (y <= 21){ // If it touches the top wall, it will now go down
	down = !down;
	colorAdvance();
      }

      if (x <= 10 && (y >= leftPaddlePos - 10 && y <= leftPaddlePos + 15)){ // If it touches the left paddle
	right = !right;
	colorAdvance();
	ballSoundState = ballSoundUpdateState(ballSoundState);
       	soundCount++;

      } else if (x <= 10 && (y < leftPaddlePos - 10 || y > leftPaddlePos + 15)){ // If it misses the left paddle, P2 will score and it will be updated on the screen
	fillRectangle(x,y,10,10, COLOR_BLACK);
	x = screenWidth/2;
	y = screenHeight/2;
	fillRectangle(x,y,10,10, ballColor);
	p2score++;
	itoa(p2score, p2char, 10);
	drawString8x12(100, 0, p2char, COLOR_WHITE, COLOR_BLACK);

	if(p2score == 10){ // If P2 scores 10 points, he/she will win, a message is displayed and the game is over
	  drawString8x12(20, 30, "P2 WINS!", COLOR_WHITE, COLOR_BLACK);
	  gameOn = 0;
	}
	
	right = !right;
	down = !down;
      }
    }
  } 
}

void main()
{
  P1DIR |= LED_GREEN;/**< Green led on when CPU on */
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  buzzer_init();

  enableWDTInterrupts();     /**< enable periodic interrupt */
  or_sr(0x8);                /**< GIE (enable interrupts) */
  p2sw_init(15);
  or_sr(0x8);                /* GIE (enable interrupts) */
  u_char width = screenWidth, height = screenHeight; 
  clearScreen(COLOR_BLACK);
 
  for(int i = 0; i < screenWidth; i++) // This just draws the line between the score and the "play field"
    drawPixel(i, 20, COLOR_WHITE);
  
  itoa(p1score, p1char, 10);
  itoa(p2score, p2char, 10);
  drawString8x12(5, 0, p1char, COLOR_WHITE, COLOR_BLACK); // Draw P1 score on the screen
  drawString8x12(100, 0, p2char, COLOR_WHITE, COLOR_BLACK); // Draw P2 score on the screen

  while (gameOn) { // While the game is still going
    u_int switches = p2sw_read(), i; // It will keep checking for input from the buttons
    char str[4];
    for (i = 0; i < 4; i++){
      str[i] = (switches & (1<<i)) ? '-' : '0'+i;

      if(str[0] == '0' && leftPaddlePos > 21){ // If S1 is pressed and the left paddle isn't colliding with the top wall, it will make the left paddle go up
	drawLeftPaddle(5, leftPaddlePos, COLOR_BLACK);
	leftPaddlePos--;
	drawLeftPaddle(5, leftPaddlePos, COLOR_WHITE);
      }

      if(str[1] == '1' && leftPaddlePos < 145){ // If S2 is pressed and the left paddle isn't colliding with the bottom wall, it will make the right paddle go down
	drawLeftPaddle(5, leftPaddlePos, COLOR_BLACK);
	leftPaddlePos++;
	drawLeftPaddle(5, leftPaddlePos, COLOR_WHITE);
      }
      
      if(str[2] == '2' && rightPaddlePos > 21){ // If S3 is pressed and the right paddle isn't colliding with the top wall, it will make the right paddle go up
	drawRightPaddle(120,rightPaddlePos, COLOR_BLACK);
	rightPaddlePos--;
	drawRightPaddle(120,rightPaddlePos, COLOR_WHITE);
      }

      
      if(str[3] == '3' && rightPaddlePos < 145){ // If S4 is pressed and the right paddle isn't colliding with the bottom wall, it will make the left paddle go down
	drawRightPaddle(120, rightPaddlePos, COLOR_BLACK);
	rightPaddlePos++;
	drawRightPaddle(120, rightPaddlePos, COLOR_WHITE);
      }
    }
    
    P1OUT &= ~LED_GREEN;/* GREEN OFF */
    or_sr(0x10);/**< cpu off */
    P1OUT |= LED_GREEN;/* GREEN ON */
  }

  while(!gameOn){
    P1OUT &= ~LED_GREEN;/* GREEN OFF */
    or_sr(0x10);/**< cpu off */
    P1OUT |= LED_GREEN;/* GREEN ON */
  }
}
