#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h> 
#include <stdio.h>
#include <string.h> 


main()
{
	struct sockaddr_in serveraddr, clientaddr; 
	int clientaddrlen;
	int request_sock, sock[2], numsocks, maxsocks;
	char buf[12]; 
	int i, rc;
	fd_set fds, readfds;
	struct timeval timeout;
	
	numsocks = 0; maxsocks = 2;

	timeout.tv_sec = 20;
	timeout.tv_usec = 0;

    /* Opprett request-socket  */
    request_sock = socket(AF_INET, SOCK_STREAM, 
						  IPPROTO_TCP);
	
    /* Opprett adressestruct */
    memset((void *) &serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET; 
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(2009);
	
    /* bind adressen til socketen */
    bind(request_sock, (struct sockaddr *)&serveraddr, sizeof serveraddr);
	
    /* aktiver lytting på socketen */
    listen(request_sock, SOMAXCONN);
	
	
	FD_ZERO(&fds);
	FD_SET(request_sock, &fds);
	
	
	for (;;) {
		readfds=fds;
		rc=select (FD_SETSIZE, &readfds, NULL, NULL, &timeout);
		if (rc<0)
			return -1;
		if (rc==0) {
			printf("Timeout!\n");

			for(i=0; i<numsocks; i++) {
				/* Send data tilbake over forbindelsen */
				write(sock[i], "Server ACK!",11); 
				/* Steng socketene */
				close(sock[i]);
				FD_CLR (sock[i], &fds);
				
			}
			return 0;

		}
		
		for (i = 0; i < FD_SETSIZE; i++)
			if (FD_ISSET (i, &readfds)) {
				if (i == request_sock) {
					if(numsocks < maxsocks) {
						/* motta en forbindelse */
						sock[numsocks] = accept(request_sock,(struct sockaddr *)&clientaddr, 
								  (socklen_t *)&clientaddrlen);
						
						FD_SET(sock[numsocks], &fds);
						numsocks++;
					} else {
						printf("Ran out of space for sockets.\n");
						return -1;
					}
				} else {
					
					/* les data fra forbindelsen, og skriv dem ut */
					read(i, buf,11);
					buf[11] = '\0';
					printf("From socket %d: %s\n",i,buf);

				}
				
				
			}
				
	} 

	close(request_sock);
}
