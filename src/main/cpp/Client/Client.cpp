#include <Client/client.h>

using namespace TCPComms;

void ItemIntIOThread(std::string name, int *item, ClientState *_clientState, int valread, int sock, char buffer[]) {
	while(*_clientState != ClientState::STOPPED) {
		#ifdef _WIN32

		#else
			// send(sock, item, , 0);
			valread = read(sock, buffer, 1024);
		#endif
	}
	std::cout << "Named thread '" << name << "' Stopped";
}

void Client::ItemIntIO(std::string name, int *item) {
	std::cout << "ItemInt Called" << std::endl;
	std::thread ItemIntIO_T(ItemIntIOThread, name, item, &_clientState, valread, sock, buffer);
	ItemIntIO_T.detach();
}

// IO for string Looping thread
void ItemStringIOThread(std::string name, std::string *item, ClientState *_clientState, int valread, int sock, char buffer[]) {
	while(*_clientState != ClientState::STOPPED) {
		if (*_clientState == ClientState::ACTIVE) {
			#ifdef _WIN32

			#else
				// send(sock, item, item->length(), 0);
				// valread = read(sock, buffer, 1024);
				// printf("%s\n", buffer);
			#endif
		}
	}
	std::cout << "Named thread '" << name << "' Stopped";
}

// IO String thread caller
void Client::ItemStringIO(std::string name, std::string *item) {
	std::thread ItemStringIO_T(ItemStringIOThread, name, item, &_clientState, valread, sock, buffer);
	ItemStringIO_T.detach();
}

// IO Bool thread caller
void Client::ItemBoolIO(std::string name, bool *item) {
	while(!STOP_SERVICE) {
		#ifdef _WIN32

		#else

		#endif
	}
}

// IO Double thread caller
void Client::ItemDoubleIO(std::string name, double *item) {
	while(!STOP_SERVICE) {
		#ifdef _WIN32

		#else

		#endif
	}
}

// Connect to address
void Connect(int *sock, int *valread, char *buffer, uint16_t *port, const char *ipaddress, struct sockaddr_in *serv_addr, ClientState *_clientState) {
 #ifdef _WIN32
	/**
	 * @TODO
	 * Make windows version for client start
	 */
 #else
	if ((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket Creation Error \n");
		*_clientState = ClientState::COMM_FAULT;
	}

	serv_addr->sin_family = AF_INET;
	if (port <= 0) {
		printf("\n Port number invalid \n");
		*_clientState = ClientState::COMM_FAULT;
	}
	serv_addr->sin_port = htons(*port);

	if (inet_pton(AF_INET, ipaddress, &serv_addr->sin_family) <= 0) {
		printf("\n Invalid IP address/ address not supported \n");
		*_clientState = ClientState::COMM_FAULT;
	}

	if (connect(*sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("\n Connection Failed \n");
		*_clientState = ClientState::COMM_FAULT;
	}
 #endif
}

// Set State
void Client::SetState(ClientState state) {
	_clientState = state;
}

// State Checker
void StateChecker(int *sock, int *valread, char *buffer, uint16_t *port, const char *ipaddress, struct sockaddr_in *serv_addr, ClientState *state) {
	while(*state != ClientState::STOPPED) {
		if (*state == ClientState::COMM_FAULT) {
			std::cout << "Client Comm Fault Detected, Recconecting" << std::endl;
			Connect(sock, valread, buffer, port, ipaddress, serv_addr, state);
		} else if (*state == ClientState::PAUSED) {
			std::cout << "Client Comms Paused" << std::endl;
		}
	}
	printf("\n Client Has Stopped \n");
}

// Client Starter
void Client::Start() {
	Connect(&sock, &valread, buffer, &port, ipaddress, &serv_addr, &_clientState);
	std::thread StateChecker_T(StateChecker, &sock, &valread, buffer, &port, ipaddress, &serv_addr, &_clientState);
	StateChecker_T.detach();
}