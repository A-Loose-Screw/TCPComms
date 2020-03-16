#include <Client/client.h>

using namespace TCPComms;

void Client::ItemIntIO(std::string name, int *item) {
	while(!STOP_SERVICE) {
		#ifdef _WIN32
		
		#else

		#endif
	}
}

void Client::ItemStringIO(std::string name, std::string *item) {
	while(!STOP_SERVICE) {
		#ifdef _WIN32

		#else
			send(sock, item, item->length(), 0);
			valread = read(sock, buffer, 1024);
			// std::cout << "Thread running" << std::endl;
			printf("This thread is running\n");
		#endif
	}
}

void Client::ItemBoolIO(std::string name, bool *item) {
	while(!STOP_SERVICE) {
		#ifdef _WIN32

		#else

		#endif
	}
}

void Client::ItemDoubleIO(std::string name, double *item) {
	while(!STOP_SERVICE) {
		#ifdef _WIN32

		#else

		#endif
	}
}

void Client::Start() {
 #ifdef _WIN32
	/**
	 * @TODO
	 * Make windows version for client start
	 */
 #else
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket Creation Error \n");
	}

	serv_addr.sin_family = AF_INET;
	if (port <= 0) {
		printf("\n Port number invalid \n");
	}
	serv_addr.sin_port = htons(port);

	if (inet_pton(AF_INET, ipaddress, &serv_addr.sin_family) <= 0) {
		printf("\n Invalid IP address/ address not supported \n");
	}

	if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("\n Connection Failed \n");
	}
 #endif
}