#include <Client/client.h>

using namespace TCPComms;

template <typename RegisterType>
void Client::Register(std::string name, RegisterType item) {
	// for (unsigned int i = 0; i < sizeof(itemQue)/sizeof(itemQue[0]); i++) {
		
	// }

	// while (itemQue[itemNum] != 0) {
	// 	itemNum++
	// }
	// itemQue[itemNum] = name;
}

void Client::Start() {
 #ifdef _WIN32
	/**
	 * @TODO
	 * Make windows version for client start
	 */
 #else
	int sock = 0, valread;
	char buffer[1024] = {0};
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