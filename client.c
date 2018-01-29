#include "methods.h"

int main() {

  int to_server;
  int from_server;
  char buffer[BUFFER_SIZE];
  printf("WELCOME TO BATTLESHIP!\n");
  printf("Enter '1' to start game\n");
  char * start = fgets(buffer,sizeof(buffer), stdin);
  if (strcmp(start,"1")){
    
    from_server = client_handshake( &to_server );
    char ** mygrid = setup();
    char ** myattackgrid = setup();
    printf("my grid: \n\n");
    display(mygrid);
    printf("Type coordinates with a space between and after each character");
    printf("\nSetting up for ship of size 5\n");
    usersetup_input(mygrid, 5);
    printf("\nSetting up for ship of size 4\n");
    usersetup_input(mygrid, 4);
    printf("\nSetting up for ship of size 3\n");
    usersetup_input(mygrid, 3);
    printf("\nSetting up for ship of size 3\n");
    usersetup_input(mygrid, 3);
    printf("\nSetting up for ship of size 2\n");
    usersetup_input(mygrid, 2);
    printf("done setting up\n");
    display(mygrid);
    printf("\nattack grid\n\n");
    display(myattackgrid);
    //userattac(input, to_server);
    /*
    while (1) {
      
      printf("Enter coodrinates: ");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
      write(to_server, buffer, sizeof(buffer));
      read(from_server, buffer, sizeof(buffer));
      printf("received: [%s]\n", buffer);
    }
    */
  }
}
