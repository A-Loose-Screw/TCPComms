#include <Client/client.h>

using namespace TCPComms;

struct ConnectionVars {
	// Address
	uint16_t port = 13200; // Define the port type.
	const char *ipaddress = "127.0.0.1"; // An IP address for IPv4

	#ifdef _WIN32  // Windows 95 and above
		typedef SOCKET sock;
	#else         // UNIX/Linux
		int sock = 0;
		int valread;
		char buffer[1024] = {0};
		struct sockaddr_in serv_addr; // Server Address
	#endif
}; ConnectionVars cv;


void Client::SetIP(const char *ip) {
	cv.ipaddress = ip;
}

const char *Client::GetIP() {
	return cv.ipaddress;
}

void Client::SetPort(uint16_t Port) {
	cv.port = Port;
}

uint16_t Client::GetPort() {
	return cv.port;
}

void ItemIntIOThread(std::string name, int *item, ClientState *clientState) {
	while(*clientState != ClientState::STOPPED) {
		if (*clientState == ClientState::ACTIVE) {
			#ifdef _WIN32

			#else
				send(cv.sock, item, sizeof(item), 0);
				std::cout << "Item: " << *item << std::endl;
				// cv.valread = read(cv.sock, cv.buffer, 1024);
			#endif
		}
	}
	std::cout << "Named thread '" << name << "' Stopped" << std::endl;
}

void Client::ItemIntIO(std::string name, int *item) {
	std::thread ItemIntIO_T(ItemIntIOThread, name, item, &_clientState);
	ItemIntIO_T.detach();
}

// IO for string Looping thread
void ItemStringIOThread(std::string name, std::string *item, ClientState *clientState) {
	while(*clientState != ClientState::STOPPED) {
		if (*clientState == ClientState::ACTIVE) {
			#ifdef _WIN32

			#else
				// send(cv.sock, item, item->length(), 0);
				// cv.valread = read(cv.sock, cv.buffer, 1024);
				// printf("%s\n", cv.buffer);
			#endif
		}
	}
	std::cout << "Named thread '" << name << "' Stopped" << std::endl;
}

// IO String thread caller
void Client::ItemStringIO(std::string name, std::string *item) {
	std::thread ItemStringIO_T(ItemStringIOThread, name, item, &_clientState);
	ItemStringIO_T.detach();
}

void ItemBoolIOThread(std::string name, bool *item, ClientState *clientState) {

}

// IO Bool thread caller
void Client::ItemBoolIO(std::string name, bool *item) {
	std::thread ItemBoolIO_T(ItemBoolIOThread, name, item, &_clientState);
	ItemBoolIO_T.detach();
}

// IO Double thread caller
void Client::ItemDoubleIO(std::string name, double *item) {
	
}

// Connect to address
void Connect(ClientState *_clientState) {
 #ifdef _WIN32
	/**
	 * @TODO
	 * Make windows version for client start
	 */
 #else
	if ((cv.sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket Creation Error \n");
		*_clientState = ClientState::COMM_FAULT;
	}

	cv.serv_addr.sin_family = AF_INET;
	cv.serv_addr.sin_port = htons(cv.port);

	if (inet_pton(AF_INET, cv.ipaddress, &cv.serv_addr.sin_addr) <= 0) {
		printf("\n Invalid IP address/ address not supported \n");
		*_clientState = ClientState::COMM_FAULT;
	}

	if (connect(cv.sock, (struct sockaddr *) &cv.serv_addr, sizeof(cv.serv_addr)) < 0) {
		printf("\n Connection Failed \n");
		*_clientState = ClientState::COMM_FAULT;
	} else {
		*_clientState = ClientState::ACTIVE;
	}
 #endif
}

// Set State
void Client::SetState(ClientState state) {
	_clientState = state;
}

// State Checker
void ClientChecker(ClientState *currentState) {
	while(*currentState != ClientState::STOPPED) {
		if (*currentState == ClientState::COMM_FAULT) {
			printf("\n Client Comm Fault Detected, Recconecting \n");
			sleep(3);
			Connect(currentState);
		} else if (*currentState == ClientState::PAUSED) {
			printf("\n Client Paused \n");
		}
		// char *TestSend = "Connection to Client Successful";
		// send(cv.sock, TestSend, strlen(TestSend), 0);
		// cv.valread = read(cv.sock, cv.buffer, 1024);
		// printf("%s\n", cv.buffer);
	}
	printf("\n Client Stopped \n");
}

// Client Starter
void Client::Start() {
	Connect(&_clientState);
	std::thread ClientChecker_T(ClientChecker, &_clientState);
	ClientChecker_T.detach();
}