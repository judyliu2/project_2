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
    setup();
    while (1) {
      
      printf("Enter coodrinates: ");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
      write(to_server, buffer, sizeof(buffer));
      read(from_server, buffer, sizeof(buffer));
      printf("received: [%s]\n", buffer);
    }
  }
}
