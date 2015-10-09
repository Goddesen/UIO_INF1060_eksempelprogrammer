#include <netdb.h> 
#include <stdio.h>
#include <string.h> 

#include <netinet/in.h> 
#include <sys/socket.h>

int main(void) {
    struct sockaddr_in serveraddr, clientaddr; 
    int clientaddrlen;
    int request_sock, sock;
    char buf[12]; 

    /* Opprett request-socket  */
    request_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    /* Opprett adressestruct */
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET; 
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(2009);

    /* bind adressen til socketen */
    bind(request_sock, (struct sockaddr *)&serveraddr, sizeof serveraddr);

    /* aktiver lytting på socketen */
    listen(request_sock, SOMAXCONN);

    /* motta en forbindelse */
    sock = accept(request_sock,(struct sockaddr *)&clientaddr, 
            &clientaddrlen);

    /* les data fra forbindelsen, og skriv dem ut */
    read(sock, buf,11);
    buf[11] = '\0';
    printf("%s \n",buf);

    /* Send data tilbake over forbindelsen */
    write(sock, buf,11); 

    /* Steng socketene */
    close(sock);
    close(request_sock);

} 
   
