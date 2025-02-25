#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "config.h"  // Contient le port du serveur

char buf[BUFSIZ];

int main(){

    /**
     * SOCKET
     * Je crée le socket serveur
     */
    int server_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket");
    // Si la création échoue je ferme mon programme
    if(server_fd == -1) return EXIT_FAILURE;

    /**
    * BIND
    * Je relie le socket à un port et une ip avec la fonction bind()
    */
    struct sockaddr_in server_addr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT)
    };
    int error = bind(server_fd,(struct sockaddr*)&server_addr,sizeof server_addr);perror("bind");
    if(error == -1) { close(server_fd); return EXIT_FAILURE; }


    /**
     * LISTEN obligatoire 
     */
    error = listen(server_fd,BUFSIZ);perror("listen");
    if(error == -1) { close(server_fd); return EXIT_FAILURE; }

    printf("Server listen on port : %d\n",SERVER_PORT);
    

    /**
     * ACCEPT
     * J'attend qu'un client se connecter grâce à la fonction bloquante accept()
     * accept renvoi le client accepté ou -1 en cas d'erreur.
     */
    struct sockaddr_in client_addr;
    socklen_t len;
    int client_fd = accept(server_fd,(struct sockaddr*)&client_addr,&len);perror("accept");
    if(client_fd == -1){ close(server_fd); return EXIT_FAILURE; }
 
    /**
     * SEND
     * Ping ! J'envoi un message au client !
     */
    error = send(client_fd,"ping",5,0);perror("send");
    if(error == -1){ close(client_fd); close(server_fd); return EXIT_FAILURE; }


    /**
     * RECV
     * J'attend un message du client avec la fonction bloquante recv()
     */
    int recv_length = recv(client_fd,buf,BUFSIZ,0); perror("recv");
    if(recv_length == -1){
        close(client_fd);
        close(server_fd);
        return EXIT_FAILURE;
    }
    
    printf("$%s\n",buf);
    close(client_fd);
    close(server_fd);
    return EXIT_SUCCESS;

    // printf("%d\n",time(NULL));

    
    
    
}