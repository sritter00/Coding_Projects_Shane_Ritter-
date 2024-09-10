Created by Shane Ritter
*SFML was used and is a separate library that I used. I did not create or have any part in creating SFML*

Make sure SFML is installed and working before compiling. These instructions are also under the assumption that you are using g++ to compile.
To compile:
    1) open terminal(make sure you're in the right directory `cd PongGame`). 
    2) "make" or "mingw32-make" for windows.
    3) then type ".\pong.exe" and run it. 

The controls are as follows: 
If there is one player use the 'W' key to move the paddle up and 'S' key to move the paddle down. For two players use 'W' and 'S' to control the left paddle and the up down arrow keys to move the right paddle respectively.

To run the Pong Game, execute the compiled binary. The program prompts the user to input the number of players (1 or 2) and then runs the game accordingly. 
The game utilizes the SFML library, so make sure to have it installed and linked properly before compiling. If the program is compiled using a Makefile, ensure that the SFML library is included.

For modification or extension, the code is well-structured with clear comments. If additional features were to be implemented, a list of proposed features is available within the source code comments. 

FILE I/O:
File I/O is incorporated to allow users to save game scores to a text file. After each game, scores are stored in a vector of pairs, and the entire history is saved to a text file upon user request. 
This feature provides users with a record of their game scores and contributes to the overall user experience.