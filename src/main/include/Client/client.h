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
#endif

// Shared Libraries
#include <string>
#include <vector>

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


			/**
			 * Register device for the client to listen for
			 */
			template <typename RegisterType>
			void Register(std::string name, RegisterType item);

			/**
			 * Starts Client
			 */
			void Start();

			/**
			 * Stops Client
			 */
			void Stop();

	#ifdef _WIN32  // Windows 95 and above
		typedef SOCKET sock;
	#else         // UNIX/Linux
		typedef int sock;
	#endif

   private:
	 	// Address
    uint16_t port = 13200; // Define the port type.
	  const char *ipaddress = "10.47.88.100"; // An IP address for IPv4
		struct sockaddr_in serv_addr; // Server Address

		// Item que/ control
		// template<typename ItemType>
		struct item {
			int item;
			std::string itemName;
		};
		// std::vector<item> items(2);
		// std::string itemQue[999];
		// int itemNum = 0;
		template<typename ItemType>
		void SendItem(ItemType item);
		template<typename ItemType>
		void ReceiveItem(ItemType item);
	};
};