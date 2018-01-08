#include "methods.h"

int server_handshake(int * to_client);

int client_handshake(int * to_server);

 //creates boards for user1 and computer/user2 after client/server are connected
char ** setup(){
  char ** grid = NULL;
  int rows = 0;
  int columns = 0;
  int row_letter = 65;
  grid = (char**) malloc(10* sizeof(char*));
  for (rows = 0; rows < 10; rows++){
    grid[rows] = (char*) malloc(10* sizeof(char)); //columns
  }
  
  
  for (rows = 0; rows<10 ; rows++){
    for (columns = 0; columns < 10; columns++){
      grid[rows][columns] = 'o';
    }
  }
 
  printf("  1 2 3 4 5 6 7 8 9 10\n");
  for (rows = 0; rows<10 ; rows++){
    printf("%c ", row_letter);
    row_letter++;
    for (columns = 0; columns < 10; columns++){
      printf("%c ", grid[rows][columns]);
    
    }
    printf("\n");
  }
  return grid;
}

char ** parse_args(char * s1){
  char ** ret = (char **) calloc (800, sizeof(char*));
  int i = 0;    
  
  while (s1 && i < 799){
    char * string = strsep (&s1," ");
    ret[i] = string;
    i++;
  }
  ret[i] = NULL;
  return ret;
}


//takes in coordinates and check if they're next to each other
int placeship(int x, int y, int n){
}

/*
  - A series of coordinates on the grid to place the first piece
  - If overlap, return error
  - If not a straight line, return error
  - If spot doesn’t exist, return error
  - If too many spots asked for, return error
  - If not enough spots, return error
- Error returns it back to that piece
    */
char * user_input( char ** board, int attk_board){
  char buffer[BUFFER_SIZE];
  char ** coordinates;
  int letter = 0;
  int num = 0;
  fgets(buffer, sizeof(buffer), stdin);
  
  
  *strchr(buffer, '\n') = 0;
  //printf("[%s]\n", buffer);
  
  letter = (int)coordinates[0] - 65;
  num = atoi(coordinates[1]) - 1;
  
  if ((letter >= 0 && letter < 10) && (num >= 0 && num <10)){
    
    if(attk_board){ //attacking enemy ships
      //NEEEDS TO COMMUNICATE WITH SERVER TOO SEE IF HIT OR MISS
      if((board[letter][num] == 's')){
	board[letter][num] = 'x';
	
      }
      else if(board[letter][num] == 'x' ||
	      board[letter][num] == 'm'){
	printf("This coordinate is attacked already. Please try again.\n");
      }
      else{
	printf("Entered coordinate is invalid. Please try again.\n");
      }
    }

    
    else{ //ship setup
      //ask which ship user is getting up
      printf("Setup your ships:\n");
      printf("Please place down your carrier (takes up 5 consecutive horizonal/veritcal spaces)\n");
      printf("Please place down your carrier (takes up 4 consecutive horizonal/veritcal spaces)\n");
      printf("Please place down your carrier (takes up 3 consecutive horizonal/veritcal spaces)\n");
      printf("Please place down your carrier (takes up 3 consecutive horizonal/veritcal spaces)\n");
      printf("Please place down your carrier (takes up 2 consecutive horizonal/veritcal spaces)\n");
    }
  }

  else{
    printf("Input is invalid. Please try again.\n");
  }
  
}


/*
  - The player is shown two boards, one is their own with the ships on it
  - The other is the other side and it appears blank
*/
void display(char ** board){
  int rows = 0;
  int columns = 0;
  int row_letter = 65;
  printf("  1 2 3 4 5 6 7 8 9 10\n");
  for (rows = 0; rows<10 ; rows++){
    printf("%c ", row_letter);
    row_letter++;
    for (columns = 0; columns < 10; columns++){
      printf("%c ", board[rows][columns]);
    
    }
    printf("\n");
  }
 
}

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


int main(){
  printf("My ships\n");
  char ** mygrid = setup();
  printf("\n");
  user_input(mygrid, 0);
  //display(mygrid);
  
  return 0;
}

