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

namespace TCPComms {
	class Server {

   public:
    /**
     * Register item for the server to broadcast
     */
    template <typename RegisterType>
    void Register(std::string name, RegisterType item);

    /**
     * Starts server and sends all registered items
     */
    void Start();

    /**
     * Stops server
     */
    void Stop();
	#ifdef _WIN32  // Windows 95 and above
		typedef SOCKET sock;

	#else         // UNIX/Linux
		typedef int sock;
	#endif

	};
};