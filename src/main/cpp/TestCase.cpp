#include <TestCase.h>

#define PORT 13200
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
	int ItemBuffer;
	int Item;
	while (true) {
		// std::cout << "Value Before: " << Item << std::endl;
		Item = recv(new_socket, &ItemBuffer, sizeof(Item), 0);
		std::cout << "Value: " << Item << std::endl;
		std::cout << "Buffer: " << ItemBuffer << std::endl;
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
	if(inet_pton(AF_INET, "192.168.178.153", &serv_addr.sin_addr)<=0) 
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
	// std::cout << "Server Active" << std::endl;
	// Server();
	// while (true) {
	// 	std::cout << "Server active" << std::endl;
	// 	Server();
	// }
	client.SetIP("192.168.178.153");
	client.SetPort(13200);
	client.Start();
	client.Register("TestCase", &Testcase2);

	sleep(10);
	// *TestCaseMod = 10;
	Testcase2 = 25;

	while(true) {}

	client.Stop();
}
