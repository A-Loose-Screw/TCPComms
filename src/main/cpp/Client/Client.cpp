#include <Client/client.h>

using namespace TCPComms;

// Send/Recieve item info
// void Client::ItemStringIO(std::string name, std::string *item) {
// 	// while(!STOP_SERVICE) {
// 	// 	// send(sock, item, strlen((char *)item), 0);
// 	// 	valread = read(sock, buffer, 1024);
// 	// }
// }
// template <typename t>
void Client::ItemStringIO(std::string name, std::string *item) {

}

// void Client::RegisterString(std::string name,	std::string *item) {
// 	std::thread IOthread(ItemStringIO, name, item);
// 	IOthread.detach();
// }

// void Client::Register(std::string name, std::string *item) {
	
// }

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