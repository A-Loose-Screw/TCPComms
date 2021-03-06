#include <TestCase.h>

#define PORT 13200

#define BUFSIZE 512
#define PACKETSIZE sizeof(ItemStruct)

// Item struct
struct ItemStruct {
	int value;
	char name[BUFSIZE]; // Acts as ID
};

void serializeServer(ItemStruct *msgPacket, char *data) {
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

void deserializeServer(char *data, ItemStruct *msgPacket) {
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

void Server() { 
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello from server"; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 

	std::cout << "section 1 complete" << std::endl;
	
	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt, sizeof(opt))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 

	std::cout << "Section 3 complete" << std::endl;
	
	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	std::cout << "Section 4 complete" << std::endl;
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 

	std::cout << "Section 5 complete" << std::endl;
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen))<0) 
	{ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 

	std::cout << "Section 6 complete" << std::endl;
	// valread = read( new_socket , buffer, 1024); 
	// int ItemBuffer;
	
	ItemStruct *itemStruct = new ItemStruct;int size;
	std::string nameOfItem;
	int valueOfItem;
	while (true) {
		// std::cout << "Value Before: " << Item << std::endl;
		// sleep(1);
		char data[PACKETSIZE];
		size = recv(new_socket, &data, sizeof(data), 0);
		deserializeServer(data, itemStruct);
		if (size > 0) {
			if (itemStruct->name == "Motor2") {
				std::cout << itemStruct->name << ": ";
				std::cout << itemStruct->value << std::endl;
			}
		}
	}
	std::cout << "Section 7 complete" << std::endl;
} 


void Client() { 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char *hello = "Hello from client"; 
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
	} 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.168.178.153", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
		printf("\nConnection Failed \n"); 
	} 
	send(sock , hello , strlen(hello) , 0 ); 
	printf("Hello message sent\n"); 
	valread = read( sock , buffer, 1024); 
	printf("%s\n",buffer ); 
} 

// Test case to send and recieve;
TCPComms::Client client;
std::string Testcase = "This is a test";
int Testcase2 = 5;
// int *TestCaseMod = &Testcase2;
bool Testcase3 = true;
double Tescase4 = 0.5;
int main() {
	std::cout << "Server Active" << std::endl;
	std::thread server_t(Server);
	server_t.detach();
	
	client.SetIP("127.0.0.1");
	client.SetPort(13200);
	client.Start();
	client.SetItem("Motor1", &Testcase2);
	client.SetItem("Motor2", &Testcase2);
	client.SetItem("Motor3", &Testcase2);
	client.SetItem("Motor4", &Testcase2);
	client.SetItem("Motor5", &Testcase2);
	client.SetItem("Motor6", &Testcase2);
	client.SetItem("Motor7", &Testcase2);
	client.SetItem("Motor8", &Testcase2);
	client.SetItem("Motor9", &Testcase2);
	client.SetItem("Motor10", &Testcase2);

	client.SetItem("Motor11", &Testcase2);
	client.SetItem("Motor12", &Testcase2);
	client.SetItem("Motor13", &Testcase2);
	client.SetItem("Motor14", &Testcase2);
	client.SetItem("Motor15", &Testcase2);
	client.SetItem("Motor16", &Testcase2);
	client.SetItem("Motor17", &Testcase2);
	client.SetItem("Motor18", &Testcase2);
	client.SetItem("Motor19", &Testcase2);
	client.SetItem("Motor20", &Testcase2);
	// client.SetItem("TestCase2", &Testcase);

	sleep(10);

	while(true) {
		sleep(0.1);
		if (Testcase2 < 1000) {
			Testcase2 += 1;
		} else {
			Testcase2 = 0;
		}
	}


	client.Stop();
}
