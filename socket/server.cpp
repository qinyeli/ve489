#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

const char ACK = 0x6; // this is the Acknowledge byte in ASCII

void receiver(int connection);

int main(int argc, char* argv[]) {

	if (argc != 2)  {
		cout << "Usage: ./server port" << endl;
		return 1;
	}

	u_int port = (u_int) atoi(argv[1]);

	/*
	 * Open a TCP socket over the Internet
	 */
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		cerr << "Error when opening stream socket: " << strerror(errno) << endl;
		exit(1);
	}

	/*
	 * Define the port the server is listening on
	 * and the ip the server would connect with
	 */
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // any ip

	/*
	 * Request the port from the operating system
	 */
	if (::bind(sock, (sockaddr*)&addr, sizeof(addr)) == -1) {
		cerr << strerror(errno) << endl;
		exit(1);
	}

	/*
	 * Start listening on that port
	 */
	if (listen(sock, 0) == -1) {
		cerr << strerror(errno) << endl;
		exit(1);
	}
	cout << "Server listening on " << port << endl;

	/*
	 * Accept connection!
	 */
	int clientSock = accept(sock, 0, 0);
	cout << "Accepted connection." << endl;

	receiver(clientSock);

	return 0;
}

void receiver(int connection) {
	while (1) {
		cout << "> ";

		char buf[1024];

		int rc = recv(connection, buf, sizeof(buf), 0);
		if (rc == -1) {
			cout << strerror(errno) << endl;
			return;
		} else if (rc == 0) {
			cout << "Client closed connection." << endl;
			return;
		}

		cout << buf << endl;
		
		// send(connection, &ACK, 1, 0);
	}
}