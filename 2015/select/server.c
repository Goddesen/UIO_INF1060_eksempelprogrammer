#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h> 
#include <stdio.h>
#include <string.h> 
#include <unistd.h>
#include <stdlib.h>

fd_set master_fds;
int select_max_fds;

int numsocks = 0;
int maxsocks = 128;

struct timeval timeout = {
	/* Set 20 second timeout */
	.tv_sec = 20,
	.tv_usec = 0
};

int sock[128];
struct sockaddr_in addrs[128];
socklen_t addr_size = sizeof(struct sockaddr_in);

void handle_new_connection(int request_sock)
{
	char buf[256];
	int new_fd;

	printf("Handling new connection!\n");

	/* Accept new connection */
	new_fd = accept(request_sock,
			(struct sockaddr *)&addrs[numsocks], 
			&addr_size);

	FD_SET(new_fd, &master_fds);

	inet_ntop(AF_INET, &addrs[numsocks].sin_addr, buf, INET_ADDRSTRLEN);
	printf("Got new connection from %s!\n", buf);

	sock[numsocks] = new_fd;
	numsocks++;

	/* Update select max socket to keep track of */
	if (new_fd >= select_max_fds)
		select_max_fds = new_fd + 1;
}

void handle_disconnect(int fd)
{
	FD_CLR(fd, &master_fds);
}

void handle_data(int fd)
{
	char buf[1024]; 
	ssize_t len;

	/* Attempt to read data from the connection */
	len = read(fd, buf, 1024);

	if (len < 0) {
		/* Error during read */
		perror("read");
		exit(EXIT_FAILURE);
	}
	if (len == 0) {
		/* Event on the socket, but no data.
		 * Socket has (very likely) been closed remotely */
		handle_disconnect(fd);
		return;
	}

	printf("Read %zd bytes from socket %d: \"%s\"\n", len, fd, buf);
}

int server_loop(int request_sock)
{
	int i, num_fds;
	fd_set read_fds;


	read_fds = master_fds;

	printf("Now waiting for data...\n");
	num_fds = select(select_max_fds, &read_fds, NULL, NULL, &timeout);
	printf("Select returned! Got activity on %d sockets.\n", num_fds);

	if (num_fds < 0) {
		perror("select");
		return -1;
	}

	if (num_fds == 0) {
		/* Select timed out. Shut down server. */
		return -2;
	}

	for (i = 0; i < select_max_fds; i++) {
		if (FD_ISSET (i, &read_fds)) {
			if (i == request_sock) {
				/* Event on server socket.
				 * There is a new incoming connection */
				if(numsocks >= maxsocks) {
					fprintf(stderr,
						"No more space for sockets.\n");
					return -1;
				}
				handle_new_connection(request_sock);
			} else {
				/* Event on existing client socket. */
				handle_data(i);
			}
		}
	}
	return 0;
}

int main(void)
{
	struct sockaddr_in serveraddr; 
	socklen_t serveraddrlen;
	int request_sock, ret;

	/* Opprett request-socket  */
	request_sock = socket(AF_INET, SOCK_STREAM, 
			IPPROTO_TCP);
	if (request_sock == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	printf("Successfully created socket: %d.\n", request_sock);

	/* Opprett adressestruct */
	memset(&serveraddr, 0, sizeof(struct sockaddr_in));
	serveraddr.sin_family = AF_INET; 
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(2009);
	serveraddrlen = sizeof(struct sockaddr_in);

	/* Bind the address to our socket */
	ret = bind(request_sock, (struct sockaddr *)&serveraddr, serveraddrlen);
	if (ret == -1) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	printf("Successfully bound socket.\n");

	/* Listen on the socket */
	listen(request_sock, SOMAXCONN);
	if (ret == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("Now listening on socket.\n");

	/* Initialize the master fd set to zero */
	FD_ZERO(&master_fds);

	/* Add listening socket to the master set */
	FD_SET(request_sock, &master_fds);

	/* Set max file descriptor set size for select */
	select_max_fds = request_sock + 1;

	do {
		ret = server_loop(request_sock);
	} while (ret == 0);

	if (ret == -1) {
		puts("Select error!\n");
		ret = EXIT_FAILURE;
	} else {
		puts("Select timed out. Shutting down.\n");
		ret = EXIT_SUCCESS;
	}
	close(request_sock);

	return ret;
}

