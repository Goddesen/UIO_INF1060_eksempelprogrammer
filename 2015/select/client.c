#include <netinet/in.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h> 
#include <stdio.h>
#include <string.h> 
#include <unistd.h>

char *data[5] =  {
	"Hello world!",
	"Use the force, Luke! - Darth Vader",
	"Luke the use, force! - Yoda",
	"Programmeringsspraag. - Dag Langmyhr",
	"The problem with quotes on the internet is you can't always depend "
		"on their accuracy. - Abraham Lincoln, 1864"
};

int main(void)
{
	struct sockaddr_in serveraddr;
	int sock;
	int i;

	/* Create socket */
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	/* Initialize server address struct to zero */
	memset(&serveraddr, 0, sizeof(serveraddr));

	/* Set domain to Internet */
	serveraddr.sin_family = AF_INET;

	/* Set address to localhost */
	inet_pton(AF_INET, "localhost", &serveraddr.sin_addr);

	/* Set port number. Note that this value in particular needs to be in
	 * network order. This is not the case for a lot of other functions.
	 * read(2) and write(2), for example, are general system calls and take
	 * a length value in regular host byte order. */
	serveraddr.sin_port = htons(2009);

	connect(sock, (struct sockaddr *)&serveraddr, sizeof serveraddr); 

	/* Send data */
	for(i = 0; i < 5; i++) {
		write(sock, data[i], strlen(data[i]) + 1);
		sleep(2);
	}

	/* Close the socket */
	close(sock);
}

