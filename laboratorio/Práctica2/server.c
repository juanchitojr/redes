/* 
 * Servidor simple usando sockets con TCP
 * Modo de ejecución: ./server PORT
 * donde PORT es el puerto en el que va a estar escuchando
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);

}

int main(int argc, char *argv[])
{
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;
  if (argc < 2) {
    fprintf(stderr,"Error, no se ha dado un puerto\n");
    exit(1);
  }
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
    error("Error al abrir el socket");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  printf("Iniciand la ejecución en el puerto: %d\n",portno);
  //HAsta aqui empieza a escuchar
  if (bind(sockfd, (struct sockaddr *) &serv_addr,
	   sizeof(serv_addr)) < 0) 
    error("Error al enlazar");
  
  listen(sockfd, 5);
  clilen = sizeof(cli_addr);
  // Ciclo infinto para escuchar múltiples clientes
  while(1) {
    printf("inciando server\n");
    newsockfd = accept(sockfd, 
		       (struct sockaddr *) &cli_addr, 
		       &clilen);
    if (newsockfd < 0) 
      error("Error al ejecutar la funcion accept");
    printf("Conexión aceptada.\n");
    printf("Esperando mensaje\n");
    bzero(buffer, 256);

    // Aqui se va a guardar la longitude del mensaje
    // que nos van a pasar
    char len[256];
    // lee la longitud
    read(newsockfd, len, 256);
    int longitud = atoi(len); //la convierte a entero
    printf("Longitud del mensj: %d \n", longitud);
    // para continuar con la comunicación
    write(newsockfd, "", 1); 

    // Lee el mensaje completo y lo guarda en buffer
    n = read(newsockfd, buffer, 256);
    if (n < 0)
      error("Error al leer desde el socket");
    printf("Aquí está el mensaje recibido: %s\n", buffer);

    int i=0;
    int cur = buffer[i]; //guarda un byte del mensaje
    // Responde al cliente un byte del mensaje completo
    while(i<longitud-1) {
      if (n < 0) 
	error("Error al escribir en el socket");
      
      n = write(newsockfd, &cur, 1);
      printf("Para mandar por byte:  %c\n", cur);
      cur= buffer[++i];  // actualiza
      read(newsockfd, buffer, 256);
      sleep(1); // duerme el mensaje
      // Descomenta si quieres cerrar el socket después de
      // haber mandao el primer byte
      //close(sockfd);
    }
    n = write(newsockfd, "He terminado contigo", 255);
  }
  close(newsockfd);
  close(sockfd);
  return 0; 
  
}
