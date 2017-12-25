# project_2

Design Document

Names: Judy Liu, Pacy Yan

Each student or group must create a file in their repository named DESIGN. The file should be a plain text file and it should contain the following.




    A statement of the problem you are solving and/or a high level description of the project.
Creating the classic Battleship board game in the terminal 
User plays with computer
A description as to how the project will be used (describe the user interface).
Rules: 
The two players cannot see each other’s boards
You can place one shot at once
To defeat a ship, you must hit all the spots the ship is on
You may not shoot a spot you have already shot before
Game Pieces
2 11x9 boards (ABCs x 123s)
Carrier - 5 holes
Battleship - 4 holes
Cruises - 3 holes
Submarine - 3 holes
Destroyer - 2 holes
Game Process
Setup
Player is presented with a grid and prompted to place each of the pieces on the board
Prints the name of current piece and identifies how many spots it needs
Input
A series of coordinates on the grid to place the first piece
If overlap, return error
If not a straight line, return error
If spot doesn’t exist, return error
If too many spots asked for, return error
If not enough spots, return error
Error returns it back to that piece 
Display
The player is shown two boards, one is their own with the ships on it
The other is the other side and it appears blank
Play
First Round:
Input:
Prompted to give five coordinates 
If coordinates don’t exist, error
After all five are in, the board prints again to display which ones were hit and which were not
Computer does the same thing 
N+1 Round:
Input
a string in grid notation (i.e. A4) and a bullet is placed there
If hit, will print the grid with the “hit” location over the blank board
If not hit, will print the grid with a “missed” notation over the location on the blank board
If input a place that doesn’t exist, will return error 
If already shot there, will return error 
If tries to shoot more than one spot, return error
Error prompts try again
Computer will place a move every other time the player does 
If hit, will show that the ship is hit
If not hit, it will show the same symbol
If ship is down, will take 1 from the ship count
Endgame
If all the ships on either of the boards are all down, the game ends
Prompts restart or quit


A description of your technical design. This should include:
        How you will be using the topics covered in class in the project.
Allocating memory : create a 10x10 grid 
Working with files : hold the history of the player’s moves
Finding information about files (stat and such).
Processes (fork, exec etc.) : forks off after user clicks start game
Signals
Pipes (named and unnamed) : used to send messages between the clients
Shared memory, 
Semaphores.
Networking : used for 2 players

        How you are breaking down the project and who is responsible for which parts.

        What data structures you will be using and how.
Arrays will be used to create the Battleship board and keep track of the coordinates
Strings are used to hold user input
Ints are used to identify the placements on the board
Structs are used for the different types of ships 
Pipes will sended messages between the the clients and servers.
In single player games, clients and servers will send messages about hit and misses
In two player games, clients will send messages about hit and misses

        What algorithms you will be using, and how.
Handshakes are used to verify that the servers and clients are connected
fgets() is used to take in user inputs
fork() is used to create a game after the user chooses to start the game
malloc() is used to create the boards
While loops are used for each turn and wait for user input

A timeline with expected completion dates of parts of the project.
1/2 : Have a home screen
1/5 : Have a printable board for the game
