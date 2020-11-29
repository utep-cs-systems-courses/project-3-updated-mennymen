Project 3: Graphical LCD Toy
====================

# Project Description

This project features the game Pong, the same game from 1972. It uses
interruptions to make the game flow, as well as use of the buttons on the
green board to controll the paddles. It plays a boncing sound every time the
ball bounces off a paddle, and the ball changes color every time it
bounces. The game is over once a player scores 10 points, after this, the
bottom red LED will start shining at different intensities, and a song from
The Legend of Zelda will play.

# How To Access, Compile, and Run


1) After turning on your VM, type 'emacs' and press ENTER
2) Once in emacs, press M-x, then type 'shell', then press ENTER
3) Type 'cd project-3-updated-mennymen', then press ENTER
4) Type 'make all', then press Enter
5) Type 'cd project', then press Enter
6) Type 'make load', press ENTER to compile the program, and you can start
playing!
7) Optionally, you can type 'make clean' and press ENTER to remove the .o files

# How To Use

Once the program is running, these are the button mappings for the players.

1) S1 and S2 are used by Player 1, which will be the left paddle.
   S1 will make the left paddle go up and S2 will make it go down.


2) S3 and S4 are used by Player 2, which will be the rigle paddle.
   S3 will make the right paddle go up and S4 will make it go down.


Every time a player scores a point, it will be updated on the upper section of
the screen. Once a player reaches 10 points, the game is over. A song will
play once, and after this, the screen will go black. If you want to play
again, you can press the reset button on the red board. 
