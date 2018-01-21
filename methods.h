#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define ACK "HELLO"
#define HANDSHAKE_BUFFER_SIZE 10
#define BUFFER_SIZE 1000

struct coordinates{
  char letter;
  char number;
};

int server_handshake(int * to_client);

int client_handshake(int * to_server);

char ** setup(); //creates boards for user1 and computer/user2 after client/server are connected

int placement(int letter1, int num1, int letter2, int num2); //takes in coordinates and check if they're next to each other

int stringtoint(char *a);

char ** parse_args(char * s1);
char * usersetup_input(char ** board, int ship_size); 
/*
  - A series of coordinates on the grid to place the first piece
  - If overlap, return error
  - If not a straight line, return error
  - If spot doesn’t exist, return error
  - If too many spots asked for, return error
  - If not enough spots, return error
- Error returns it back to that piece
    */
char * userattac_input(char ** board);

void comp_setup(char** board, int ship_size);
void comp_attk(char** board);

void display(char** board);
/*
  - The player is shown two boards, one is their own with the ships on it
  - The other is the other side and it appears blank
*/

void play();
/*

    - First Round:
        - Input:
        - Prompted to give five coordinates 
        - If coordinates don’t exist, error
        - After all five are in, the board prints again to display which ones were hit and which were not
    - Computer does the same thing 
    - N+1 Round:
        - Input
        - a string in grid notation (i.e. A4) and a bullet is placed there
        - If hit, will print the grid with the “hit” location over the blank board
        - If not hit, will print the grid with a “missed” notation over the location on the blank board
        - If input a place that doesn’t exist, will return error 
        - If already shot there, will return error 
        - If tries to shoot more than one spot, return error
            - Error prompts try again
        - Computer will place a move every other time the player does 
            - If hit, will show that the ship is hit
            - If not hit, it will show the same symbol
- If ship is down, will take 1 from the ship count
*/

void endgame();
/*
  - If all the ships on either of the boards are all down, the game ends
  - Prompts restart or quit
*/
