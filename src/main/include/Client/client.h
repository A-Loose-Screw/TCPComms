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
#include <arpa/inet.h> 
#include <assert.h>

#include <stdio.h>  
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <cstring>
#endif

// Shared Libraries
#include <string>
#include <vector>
#include <iostream>
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
		 * Set Item with name
		 */
		void SetItem(std::string name, int *item) {
			try {
				ItemIntOut(name, item);
			} catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}

		/**
		 * Get Item with name
		 */
		void GetItem(std::string name, int *item) {
			try {
				ItemIntIn(name, item);
			} catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}

		/**
		 * Set Item with name
		 */
		void SetItem(std::string name, std::string *item) {
			try {
				ItemStringOut(name, item);
			} catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}

		/**
		 * Get Item with name
		 */
		void GetItem(std::string name, std::string *item) {
			try {
				ItemStringIn(name, item);
			} catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}

		/**
		 * Set Item with name
		 */
		void SetItem(std::string name, bool *item) {
			try {
				ItemBoolOut(name, item);
			} catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}

		/**
		 * Get Item with name
		 */
		void GetItem(std::string name, bool *item) {
			try {
				ItemBoolIn(name, item);
			} catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}

		/**
		 * Set Item with name
		 */
		void SetItem(std::string name, double *item) {
			try {
				ItemDoubleOut(name, item);
			} catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}

		/**
		 * Get Item with name
		 */
		void GetItem(std::string name, double *item) {
			try {
				ItemDoubleIn(name, item);
			} catch(const std::exception& e) {
				std::cerr << e.what() << '\n';
			}
		}

   private:

		// Function to recieve items
		void ItemIntIn(std::string name, int *item);
		void ItemStringIn(std::string name, std::string *item);
		void ItemBoolIn(std::string name, bool *item);
		void ItemDoubleIn(std::string name, double *item);

		// Function to send items
		void ItemIntOut(std::string name, int *item);
		void ItemStringOut(std::string name, std::string *item);
		void ItemBoolOut(std::string name, bool *item);
		void ItemDoubleOut(std::string name, double *item);

		
		// Thread Controller & Checkers
		void SetState(ClientState state);

		ClientState _clientState{ ClientState::ACTIVE };
	};
};