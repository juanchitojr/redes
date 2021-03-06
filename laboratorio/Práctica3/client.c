/*
 * Cliente simple para el envío de mensajes al servidor.
 * Modo de uso: ./client IPSERVER PORTSERVER
 * donde IPSERVER es la ip del servidor y 
 * PORTSERVER es el puerto del servidor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void send_request();

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usando el puerto %s\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("Error al abrir el socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"Error, no se encontro el servidor\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("Error al iniciar la conexión");
    printf("Por favor ingresa tu mensaje: ");
    bzero(buffer, 256);
    // ingresa el mensaje para mandar
    fgets(buffer, 255, stdin);
    // PAra guardar la longitud del mensaje
    char len[250];
    int longitud = strlen(buffer); //lo convierte a entero
    sprintf(len, "%d", longitud);
    n = write(sockfd, len, sizeof(int));
    //    n = write(sockfd, buffer, (buffer));
    if (n < 0) 
         error("Error al escribir en el socket");
    printf("el mensaje: %s", buffer);
    //read(sockfd, "dumb", 1);
    // escribe el mensaje 
    read(sockfd, "dumb", 1); //para continuar la comunicación
    n = write(sockfd, buffer, longitud);
    if (n < 0) 
         error("Error al escribir en el socket");
    int i = 0;
    char letra;
    // Recibe el mismo mensaje del servidor byte por byte
    while (i<longitud) {
      write(sockfd, "dumb", 1);
      n = read(sockfd, &letra, 1);
      if (n < 0) 
	error("Error al leer desde el socket");
      printf("La letra que nos mandaron: %c\n", letra);
      i++;
    }

    read(sockfd, buffer, 255);
    printf(" %s \n", buffer);
    close(sockfd);
    return 0;
}

