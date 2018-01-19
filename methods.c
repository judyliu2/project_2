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
  char ** ret = (char **) calloc (sizeof(char*), 20);
  int i = 0;    
  
  while (s1 && i < 20){
    char * string = strsep (&s1, " ");
    ret[i] = string;
    i++;
  }
  ret[i] = NULL;
  return ret;
}


/*
  - takes in coordinates and check if they're next to each othe
  - int direction checks if the direction is correct
     - 1 - top
     - 2 - left
     - 3 - down
     - 4 - right

   returns the direction
*/

int placeship(int letter1, int num1, int letter2, int num2, int direction){
  //DIRECTION IS ONLY USED FOR COMPUTER GENERATED PLACEMENTS
  if (direction == 0){
    if (letter1 == letter2 -1 && num1 == num2 ){
      return 1; 
    }
    
    
    else if (letter1 == letter2 && num1 == num2 + 1 ){
      return 2; 
    }
  
    
    else if (letter1 == letter2 +1 && num1 == num2 ){
      return 3; 
    }
    
  
    else if (letter1 == letter2 && num1 == num2 - 1 ){
      return 4; 
    }
  }
    
  else{
    return 0;
  }
}


int stringtoint(char *a){
  if (!strcmp(a, "A")){
    return 0;
  }
  else if (!strcmp(a, "B")){
    return 1;
  }
  else if (!strcmp(a, "C")){
    return 2;
  }
  else if (!strcmp(a, "D")){
    return 3;
  }
  else if (!strcmp(a, "E")){
    return 4;
  }
  else if (!strcmp(a, "F")){
    return 5;
  }
  else if (!strcmp(a, "G")){
    return 6;
  }
  else if (!strcmp(a, "H")){
    return 7;
  }
  else if (!strcmp(a, "I")){
    return 8;
  }
  else if (!strcmp(a, "J")){
    return 9;
  }
  else{
    return 10;
  }
  
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
char * userattac_input( char ** board){
  //  char buffer[BUFFER_SIZE];
  char * input = (char*) calloc (BUFFER_SIZE, sizeof(char));
  
  //char ** coordinates;
  int letter;
  int num = 0;
  printf("coordinate:");
  fgets(input, sizeof(input), stdin);

  printf("hello\n");
  letter = stringtoint(strsep(&input," "));
  
  num = atoi(strsep(&input, " "));

  
  
  *strchr(input, '\n') = 0;
  printf("1[%s]\n", letter);
  printf("1[%d]\n", num);

  //printf("2[%s]\n", input);
  
  //  num = atoi(coordinates[1]);
  //printf("3[%s]\n", input); 
  
  if ((letter >= 0 && letter < 10) && (num >= 0 && num <10)){
    
    
    //NEEEDS TO COMMUNICATE WITH SERVER TOO SEE IF HIT OR MISS
    //WRITE TO SERVER AND READ BACK
    
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

  
  	

  else{
    printf("Input is invalid. Please try again.\n");
  }
  
}




/*
  - The player is shown two boards, one is their own with the ships on it
  - The other is the other side and it appears blank
*/

char * usersetup_input(char ** board, int ship_size){
/*
  - setup for 1 ship at a time
  - start with one spot
  - check if that spot is valid
      - if valid, open a while loop for ship_size-1 times for the last few spots
        - check if the spots placed are next to each other
      - else try again

*/
  char * input = (char*) calloc (BUFFER_SIZE, sizeof(char));

  int start_size = ship_size;
  
  //char ** coordinates;
  int start_let;
  int start_num;

  int dir;
  
  int prev_let;
  int prev_num;
  
  int letter;
  int num = 0;
  

  while (ship_size){
    
    printf("coordinate:");
    fgets(input, sizeof(input), stdin);
    
    printf("hello\n");
    letter = stringtoint(strsep(&input," "));
  
    num = atoi(strsep(&input, " "));

    
    if (ship_size == start_size){
      start_let = letter;
      start_num = num;
    }

    prev_let = letter;
    prev_num = num;
    
    *strchr(input, '\n') = 0;
    printf("1[%s]\n", letter);
    printf("1[%d]\n", num);

  //printf("2[%s]\n", input);
  
  //  num = atoi(coordinates[1]);
  //printf("3[%s]\n", input); 
  
    if ((letter >= 0 && letter < 10) && (num >= 0 && num <10)){

      
      if (board[letter][num-1] == 'o'){
	
	if(ship_size != start_size){ // not first ship, compare placements
	  if (ship_size == start_size -1){
	    dir = placeship(start_let, start_num, letter,num-1,0);
	  }
	  
	  //if the input is next to the start coordinates, place down
	  else if (dir){
	    board[letter][num-1] = 's';
	    display(board);

	    //STILL NEED TO MAKE A CASE SO THAT THE SHIPS ARE ALIGNED
	    // 2&4 left/right
	    // 1&3 top/bottom
	  }
	  else{
	    printf("try entering a coordinate next to the first previous input\n");
	  }
	}
	
       
	  //when you have the direction
	
	
	else{
	  board[letter][num-1] = 's';
	  display(board);
	}
       
      }
    }
  
    else{
      printf("placement is invalid. Please try again\n");
    }
    ship_size -= 1;
  }
  printf("hello\n");
}
	


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
  //char * = "Hello my name is";
  printf("My ships\n");
  char ** mygrid = setup();
  printf("\n");
  usersetup_input(mygrid,3);
  display(mygrid);
  
  return 0;
}

