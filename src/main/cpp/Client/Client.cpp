#ifndef SOCKETLIBTYPES_H
#define SOCKETLIBTYPES_H


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

namespace SocketLib
{
	 // =============================================================================================================
	 //  Globals and Typedefs.
	 // =============================================================================================================
#ifdef _WIN32  // Windows 95 and above

	 typedef SOCKET sock; // Although sockets are int's on Unix, windows uses it's own typedef of SOCKET to represent 
						  // them. If you look in the Winsock2 source code, you'll see that it is just a typedef for 
						  // int, but there is absolutely no guarantee that it won't change in a later version. 
						  // Therefore, in order to avoid confusion, this library will create it's own basic socket 
						  // descriptor typedef

#else         // UNIX/Linux
	 typedef int sock;    // See the description above.
#endif
	 // =============================================================================================================
	 //  Ports will be in host byte order, but IP addresses in network byte order. It's easier this way; ports are 
	 //  usually accessed as numbers, but IP addresses are better accessed through the string functions.
	 // =============================================================================================================
	 typedef unsigned short int port;        // Define the port type.
	 typedef unsigned long int ipaddress;    // An IP address for IPv4

} // End namespace SocketLib

#endif 