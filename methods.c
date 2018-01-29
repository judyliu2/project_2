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

int placement(int letter1, int num1, int letter2, int num2){
 
  
  if ((letter1 == (letter2 +1)) && (num1 == num2) ){
    printf("1\n");
    return 1; 
  }
  
  
  else if ((letter1 == letter2) && (num1 == (num2 + 1)) ){
    printf("2\n");
    return 2; 
    }
  
  
  else if ((letter1 == (letter2 -1)) && (num1 == num2) ){
    printf("3\n");
    return 3; 
  }
    
  
  else if ((letter1 == letter2) && (num1 == (num2 - 1)) ){
    printf("4\n");
    return 4; 
  }
  else{
    printf("try again\n");
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
char * userattac_input( char ** board, int *from_server, int *to_server){
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
  printf("1[%d]\n", letter);
  printf("1[%d]\n", num);
  //while (read(from_server, buffer, sizeof(buffer){
  
  if ((letter >= 0 && letter <= 10) && (num >= 0 && num <=10)){
    
    
    //NEEEDS TO COMMUNICATE WITH SERVER TOO SEE IF HIT OR MISS
    //WRITE TO SERVER AND READ BACK
    //  write(*to_server, buffer, sizeof(buffer)); //attack 
    // read(from_server, buffer, sizeof(buffer)); //hit/miss
    
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



int* next_place(char**board, int letter, int num, int dir){
  int * coordinates = (int*) malloc (sizeof(int)*2);
  if (dir == 1){
    if (letter -1 >= 0){
      coordinates[0] = letter-1;
      coordinates[1] = num;
    }
  }
  else if (dir == 2){
    if (num -1 >= 0){
      coordinates[0] = letter;
      coordinates[1] = num -1;
    }
  }
  else if (dir == 3){
    if( letter +1 <10){
      coordinates[0] = letter + 1;
      coordinates[1] = num;
    }
  }
  else{
    if (num + 1 < 10){
      coordinates[0] = letter ;
      coordinates[1] = num + 1;
    }
  }
  return coordinates;
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

  int dir = 0;
  
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

    
    
    *strchr(input, '\n') = 0;
   
    num -= 1; 
 
  
    if ((letter >= 0 && letter < 10) && (num >= 0 && num < 10)){
      
      
      if (board[letter][num] == 'o'){
	if (ship_size == start_size){
	  ship_size -= 1;
	  start_let = letter;
	  start_num = num;
	  prev_let = letter;
	  prev_num = num;
	  board[letter][num] = 's';
	  display(board);
	  printf("ship_size after first input: %d\n", ship_size);
	
	}
	else if (start_size -1 == ship_size ){
	  dir = placement(start_let, start_num, letter,num);
	  if (dir){
	    prev_let = letter;
	    prev_num = num;
	    board[letter][num] = 's';
	    display(board);
	    ship_size -= 1;
	    printf("shipsize: %d \n", ship_size);
	    printf("dir: %d\n", ship_size);
	  }
	}
	else{
       
	  if(dir){
	    //if the input is next to the start coordinates, place down
	    //STILL NEED TO MAKE A CASE SO THAT THE SHIPS ARE ALIGNED
	    // 2&4 left/right
	    // 1&3 top/bottom
	    if (dir % 2 == 1){//top/bottom
	      if (dir == 3){
		if(placement(start_let, start_num, letter, num) == 1 ||
		   placement(prev_let, prev_num, letter, num) == 3){
		  board[letter][num] = 's';
		  display(board);
		  ship_size -=1;
		  printf("shipsize: %d \n", ship_size);
		}
		else{
		  printf("try again1\n");
		}
	      }
	      else{
		if(placement(start_let, start_num, letter, num) == 3 ||
		   placement(prev_let, prev_num, letter, num) == 1){
		  board[letter][num] = 's';
		  display(board);
		  ship_size -=1;
		  printf("shipsize: %d \n", ship_size);
		}
		else{
		  printf("try again2\n");
		}
	      }
	    }
	    else{ //left/right
	      if(dir == 2){
		if(placement(start_let, start_num, letter, num) == 4 ||
		   placement(prev_let, prev_num, letter, num) == 2){
		  board[letter][num] = 's';
		  display(board);
		  ship_size -=1;
		  printf("shipsize: %d \n", ship_size);
		}
		else{
		  printf("try again3\n");
		}
	      }
	      else{
		if(placement(start_let, start_num, letter, num) == 2 ||
		   placement(prev_let, prev_num, letter, num) == 4){
		  board[letter][num] = 's';
		  display(board);
		  ship_size -=1;
		  printf("shipsize: %d \n", ship_size);
		}
		else{
		  printf("try again4\n");
		}
	      }
	    }
	  }
	  
	}
      }
      	  
	
    else{
      printf("placement is invalid. Please try again\n");
    }
        

    }
  }
}

	
void comp_setup(char** board, int ship_size){
  int start_size = ship_size;

  int start_let;
  int start_num;

  int dir = 0;
  int direction;
  
  int r = 0;
  int c = 0;

  int * nextcor;
  int letter = 0;
  int num = 0;
  
  time_t t;

  int * letters;
  letters = (int*) malloc (sizeof(int*));
  int * nums;
  nums = (int*) malloc (sizeof(int*));
  
  srand((unsigned) time(&t));
  
  while(ship_size){
    if (ship_size == start_size){
      letter = rand() % 10;      
      num = rand() % 10 ;
      if(board[letter][num] == 'o'){
	letters[r] = letter;
	nums[c] = num;
	start_let = letter;
	start_num = num;
	r ++;
	c ++;
	ship_size--;
      }
      else{
	letter = rand() % 10;      
	num = rand() % 10 ;
      }
    }
      
    else if(ship_size == start_size -1){
      direction = rand()%2 + 1;
      nextcor = next_place(board, letter, num , direction);
      if(board[nextcor[0]][nextcor[1]] == 'o'){
	letters[r] = nextcor[0];
	nums[c] = nextcor[1];

	r ++;
	c ++;
	ship_size--;
      }
      else{
	direction += 2;
      }
    }
    else{
      nextcor = next_place(board, letters[r-1], nums[c-1] , direction);
      if (board[nextcor[0]][nextcor[1]] == 'o'){
	letters[r] = nextcor[0];
	nums[c] = nextcor[1];

	r ++;
        c ++;
	ship_size--;

      }
      else{
	direction += 2;
	nextcor = next_place(board, start_let, start_num, direction);
	if (board[nextcor[0]][nextcor[1]] == 'o'){
	  letters[r] = nextcor[0];
	  nums[c] = nextcor[1];

	  r ++;
	  c ++;
	  ship_size--;
	}
	else{
	  ship_size = start_size;
	  r = 0;
	  c = 0;
	}
      }
    }
  }

  if (ship_size == 0){
    for (r = 0; r < start_size; r++){
      for (c = 0; c <start_size; c++){
	board[letters[r]][nums[c]] = 's';
      }
    }
  }
}
    //first should check area around it to see it's suitable to place ship
  
    /*
    if (ship_size == start_size){
      letter = rand() % 10;      
      num = rand() % 10 ;
      if (board[letter][num] == 'o'){	
	ship_size -= 1;
	start_let = letter;
	start_num = num;
	prev_let = letter;
	prev_num = num;
	board[letter][num] = 's';
	display(board);
	printf("ship_size after first input: %d\n", ship_size);
      }
    }
      
      
    else if (start_size -1 == ship_size ){
      direction = rand() % 2 + 1;
      nextcor = next_place(board, letter, num, direction);
      
      if (nextcor[0] < 10 && nextcor[1] < 10 &&
	  nextcor[0] >= 0 && nextcor[1] >=0 &&
	  board[nextcor[0]][nextcor[1]] == 'o'){
	prev_let = start_let = letter ;
	prev_num = start_num = num;
	letter = nextcor[0];
	num = nextcor[1];
	board[letter][num] = 's';
	display(board);
	ship_size -= 1;
      }
      else{
	direction += 2;
	nextcor = next_place(board, start_let,start_num, direction);
	if (nextcor[0] < 10 && nextcor[1] < 10 &&
	    nextcor[0] >= 0 && nextcor[1] >=0 &&
	    board[nextcor[0]][nextcor[1]] == 'o'){
	  prev_let = letter ;
	  prev_num = num;
	  letter = nextcor[0];
	  num = nextcor[1];
	  board[letter][num] = 's';
	  display(board);
	  ship_size -= 1;
	}
      }
    }
    
      
    
    else{
      nextcor = next_place(board, letter, num, direction);
      
      if (nextcor[0] < 10 && nextcor[1] < 10 &&
	  nextcor[0] >= 0 && nextcor[1] >=0 &&
	  board[nextcor[0]][nextcor[1]] == 'o'){
	prev_let = start_let = letter ;
	prev_num = start_num = num;
	letter = nextcor[0];
	num = nextcor[1];
	board[letter][num] = 's';
	display(board);
	ship_size -= 1;
      }
      else{
	direction += 2;
	nextcor = next_place(board, start_let,start_num, direction);
	if (nextcor[0] < 10 && nextcor[1] < 10 &&
	    nextcor[0] >= 0 && nextcor[1] >=0 &&
	    board[nextcor[0]][nextcor[1]] == 'o'){
	  prev_let = letter ;
	  prev_num = num;
	  letter = nextcor[0];
	  num = nextcor[1];
	  board[letter][num] = 's';
	  display(board);
	  ship_size -= 1;
	}
      }
    }
      
    
}
    */


void comp_attk(char** board, int * from_client, int *to_client){ //should be VERY similar to setup
  //read(from_client, buffer,sizeof(buffer);
  //checks the coordinates from buffer and writes hit/miss
  //write(to_client, buffer,sizeof(buffer);
  
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

/*
int main(){

  printf("My ships\n");
  char ** mygrid = setup();
  printf("\n");
  comp_setup(mygrid,3);
  comp_setup(mygrid,5);
  comp_setup(mygrid,4);
   comp_setup(mygrid,3);
  comp_setup(mygrid,2);
  display(mygrid);
  // placement(2,3, 2,3,0);
  return 0;
}

*/
