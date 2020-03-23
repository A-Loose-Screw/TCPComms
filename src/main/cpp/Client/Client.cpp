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

#define BUFSIZE 512
#define PACKETSIZE sizeof(ItemStruct)

// Item struct
typedef struct ItemStruct {
	int value; // Value
	char name[BUFSIZE]; // Acts as ID
};


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

void serializeClient(ItemStruct *msgPacket, char *data) {
	int *q = (int*)data;	
	*q = msgPacket->value;	q++;	
	
	char *p = (char*)q;
	int i = 0;
	while (i < BUFSIZE) {
		*p = msgPacket->name[i];
		p++;
		i++;
	}
}

void deserializeClient(char *data, ItemStruct *msgPacket) {
	int *q = (int*)data;	
	msgPacket->value = *q;		q++;	
	
	char *p = (char*)q;
	int i = 0;
	while (i < BUFSIZE) {
		msgPacket->name[i] = *p;
		p++;
		i++;
	}
}

void ItemIntOutThread(std::string name, int *itemValue, ClientState *clientState) {
	ItemStruct *itemStruct = new ItemStruct;
	while(*clientState != ClientState::STOPPED) {
		if (*clientState == ClientState::ACTIVE) {
			itemStruct->value = *itemValue;
			strcpy(itemStruct->name, name.c_str());

			char data[PACKETSIZE];
			serializeClient(itemStruct, data);

			#ifdef _WIN32

			#else
				send(cv.sock, &data, sizeof(data), 0);
			#endif
		}
	}
	std::cout << "Named thread '" << name << "' Stopped" << std::endl;
}

// Output Int caller
void Client::ItemIntOut(std::string name, int *itemValue) {
	std::thread ItemIntOut_T(ItemIntOutThread, name, itemValue, &_clientState);
	ItemIntOut_T.detach();
}

void ItemStringOutThread(std::string name, std::string *itemValue, ClientState *clientState) {
	while(*clientState != ClientState::STOPPED) {
		if (*clientState == ClientState::ACTIVE) {
			#ifdef _WIN32

			#else
				// send(cv.sock, itemValue, itemValue->length(), 0);
				// cv.valread = read(cv.sock, cv.buffer, 1024);
				// printf("%s\n", cv.buffer);
			#endif
		}
	}
	std::cout << "Named thread '" << name << "' Stopped" << std::endl;
}

// Output String thread caller
void Client::ItemStringOut(std::string name, std::string *itemValue) {
	struct ItemStruct itemStruct;
	// itemStruct.value = 10;
	std::thread ItemStringOut_T(ItemStringOutThread, name, itemValue, &_clientState);
	ItemStringOut_T.detach();
}

void ItemBoolOutThread(std::string name, bool *itemValue, ClientState *clientState) {

}

// Output Bool thread caller
void Client::ItemBoolOut(std::string name, bool *itemValue) {
	std::thread ItemBoolOut_T(ItemBoolOutThread, name, itemValue, &_clientState);
	ItemBoolOut_T.detach();
}

void ItemDoubleOutThread(std::string name, double *itemValue, ClientState *ClientState) {

}

// Output Double thread caller
void Client::ItemDoubleOut(std::string name, double *itemValue) {
	std::thread ItemDoubleOut_T(ItemDoubleOutThread, name, itemValue, &_clientState);
	ItemDoubleOut_T.detach();
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