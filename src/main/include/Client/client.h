// ==================================================================================================================
//  Include Files.
// ==================================================================================================================

#pragma once
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

	enum class ClientState {
		STOPPED,
		PAUSED,
		COMM_FAULT,
		ACTIVE
	};

	class Client {

   public:
		/**
		 * Set what IP the client listens to
		 */
		void SetIP(const char *ip);

		/**
		 * return the ip address
		 */
		const char *GetIP();

		/**
		 * Set what port the client listens on
		 */
		void SetPort(uint16_t Port);
		/**
		 * return the port
		 */
		uint16_t GetPort();

		/**
		 * Starts Client
		 */
		void Start();

		/**
		 * Stops Client
		 */
		void Stop() {
			_clientState = ClientState::STOPPED;
		}

		/**
		 * Pause Client
		 */
		void Pause() {
			_clientState = ClientState::PAUSED;
		}

		/**
		 * Get State of Client
		 */
		ClientState GetClientState() {
			return _clientState;
		}

		/**
		 * Register Item with name
		 */
		void Register(std::string name, int *item) {
			try {
				ItemIntIO(name, item);
			}
			catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}

		/**
		 * Register Item with name
		 */
		void Register(std::string name, std::string *item) {
			try {
				ItemStringIO(name, item);
			}
			catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}

		/**
		 * Register Item with name
		 */
		void Register(std::string name, bool *item) {
			try {
				ItemBoolIO(name, item);
			}
			catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}

		/**
		 * Register Item with name
		 */
		void Register(std::string name, double *item) {
			try {
				ItemDoubleIO(name, item);
			}
			catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}

   private:

		// Function to send and receive item
		void ItemIntIO(std::string name, int *item);
		void ItemStringIO(std::string name, std::string *item);
		void ItemBoolIO(std::string name, bool *item);
		void ItemDoubleIO(std::string name, double *item);

		
		// Thread Controller & Checkers
		void SetState(ClientState state);

		ClientState _clientState{ ClientState::ACTIVE };
	};
};