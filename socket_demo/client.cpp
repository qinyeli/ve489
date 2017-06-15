#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

const char ACK = 0x6; // this is the Acknowledge byte in ASCII

void sender(int connection);

int main(int argc, char* argv[]) {

	if (argc != 3)  {
		cout << "Usage: ./client host port" << endl;
		return 1;
	}

	string host = string(argv[1]);
	u_int port = (u_int) atoi(argv[2]);

	/*
	 * Open a TCP socket over the Internet
	 */
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		cerr << strerror(errno) << endl;
		exit(1);
	}

	/*
	 * Define the server addr the client is connecting to
	 */
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(host.c_str());

	/*
	 * Connect to the server!
	 */
	cout << "Connecting to host " << host << ", port " << port << "\n";
	if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == -1) {
		cout << strerror(errno) << endl;
		exit(0);
	}

	sender(sock);

	return 0;
}

void sender(int connection) {
	while (true) {
		cout << "> ";
		string message;
		cin >> message;

		int bytesSent = send(connection, message.c_str(), message.size(), 0);
		if (bytesSent == -1) {
			cout << "Error when sending: " << strerror(errno) << endl;
			return;
		}

		// char buf;
		// int bytesReceived = recv(connection, &buf, 1, 0);
		// if (bytesReceived == -1) {
		// 	cout << strerror(errno) << endl;
		// 	return;
		// } else if (bytesReceived == 0) {
		// 	cout << "Server closed connection." << endl;
		// 	return;
		// }

		// if (buf == ACK) {
		// 	cout << "ACK" << endl;
		// }
	}
}