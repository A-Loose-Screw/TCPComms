// ==================================================================================================================
//  Include Files.
// ==================================================================================================================
#ifdef _WIN32                // Windows 95 and above
#include "winsock2.h"       // Almost everything is contained in one file.
#include "Ws2tcpip.h"

#ifndef socklen_t
typedef int socklen_t;
#endif

#else                       // UNIX/Linux
#include <sys/types.h>      // Header containing all basic data types and typedefs.
#include <sys/socket.h>     // Header containing socket data types and functions.
#include <netinet/in.h>     // IPv4 and IPv6 stuff.
#include <unistd.h>         // For gethostname()
#include <netdb.h>          // For DNS - gethostbyname()
#include <arpa/inet.h>      // Contains all inet_* functions.
#include <errno.h>          // Contains the error functions.
#include <fcntl.h>          // File control.
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <iostream>

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#endif

// Shared Libraries
#include <string>
#include <vector>
#include <thread>

namespace TCPComms {

	class Client {

    public:
			/**
			 * Set what IP the client listens to
			 */
			void SetIP(const char *ip) {
				ipaddress = ip;
			}

			/**
			 * return the ip address
			 */
			const char *GetIP() {
				return ipaddress;
			}

			/**
			 * Set what port the client listens on
			 */
			void SetPort(uint16_t Port) {
				port = Port;
			}

			/**
			 * return the port
			 */
			uint16_t GetPort() {
				return port;
			}

			template <typename type>
			void Register(std::string name, type *item) {
				std::cout << "Register active" << std::endl;
				if (typeid(type) == typeid(int)) {
					ItemIntIO(name, item);
				} else if (typeid(type) == typeid(std::string)) {
					// std::thread RegisterStringThread(ItemStringIO, name, item);
					// RegisterStringThread.detach();
				} else if (typeid(type) == typeid(bool)) {
					// std::thread RegisterBoolThread(ItemBoolIO, name, item);
					// RegisterBoolThread.detach();
				} else if (typeid(type) == typeid(double)) {
					// std::thread RegisterDoubleThread(ItemDoubleIO, name, item);
					// RegisterDoubleThread.detach();
				} else {
					std::cout << "No Valid conversion for value named: " << name << std::endl;
				}
			}


			/**
			 * Starts Client
			 */
			void Start();

			/**
			 * Stops Client
			 */
			void Stop() {
				STOP_SERVICE = true;
			}


			/**
			 * Returns the service state
			 */
			bool GetServiceStopped() {
				return STOP_SERVICE;
			}

	#ifdef _WIN32  // Windows 95 and above
		typedef SOCKET sock;
	#else         // UNIX/Linux
		int sock = 0;
		int valread;
		char buffer[1024] = {0};
	#endif

   private:

		// Function to send and receive item
		void ItemIntIO(std::string name, int *item);
		void ItemStringIO(std::string name, std::string *item);
		void ItemBoolIO(std::string name, bool *item);
		void ItemDoubleIO(std::string name, double *item);

	 	// Address
    uint16_t port = 13200; // Define the port type.
	  const char *ipaddress = "10.47.88.100"; // An IP address for IPv4
		struct sockaddr_in serv_addr; // Server Address

		bool STOP_SERVICE;

		static Client _client;
	};
};