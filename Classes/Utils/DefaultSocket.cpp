#include "DefaultSocket.h"
#include "cocos2d.h"


USING_NS_CC;

DefaultSocket::DefaultSocket()
{
}

DefaultSocket::~DefaultSocket()
{
}
//khoi tao cho win32
#if WIN32
bool DefaultSocket::initWinSock2_0()
{
	WSADATA wsaData ;
	WORD wVersion = MAKEWORD( 2, 0 ) ;
	if ( ! WSAStartup( wVersion, &wsaData ) )
		return true ;
	return false ;
}
#endif
//Mo ket noi
bool DefaultSocket::connectSocket(const char* serverIP, int serverPort)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if(!initWinSock2_0())
		return false;
#endif	
	hClientSocket = socket(AF_INET, SOCK_STREAM,0);
//	CCLog("connectSocket---hClientSocket:%d", hClientSocket);
	if ( hClientSocket <0 )
	{
		//CCLog("Unable to init socket");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		// Cleanup the environm	ent initialized by WSAStartup()
		WSACleanup( ) ;
#endif	
		return false ;
	}
	struct hostent *server;
	server = gethostbyname(serverIP);
	if (server == NULL) {
		// CCLog("ERROR, no such host/n");
		return false;
	}
	// Create the structure describing various Server parameters
	struct sockaddr_in serverAddr ;

	serverAddr . sin_family = AF_INET ;     // The address family. MUST be AF_INET
	serverAddr . sin_addr . s_addr = inet_addr( serverIP ) ;
	serverAddr . sin_port = htons( serverPort ) ;

	// Connect to the server
	if ( connect( hClientSocket, ( struct sockaddr * ) &serverAddr, sizeof( serverAddr ) ) < 0 )
	{
		// CCLog("Unable to connect to server ");

		closeSocket();
		return false ;
	}

	peerSocket = hClientSocket;


	optval = 1;
	optlen = sizeof(optval);
	if(setsockopt(peerSocket, SOL_SOCKET, SO_LINGER, (char*)&optval, optlen) < 0) {
	// 	CCLog("Option Error");
	}else
	{
		// CCLog("Option DONE!!");
	}

	return true;
}
//Gui du lieu
int DefaultSocket::sendData(const char* data, int nLength)
{
	return send( peerSocket, data, nLength, 0);
}

int	DefaultSocket::readData(vector <char> &vectorBuffer, int len)
{
	char *test = reinterpret_cast<char*>(&vectorBuffer[0]);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return recv(peerSocket, test, len, 0 );
#else
	return read(peerSocket,vectorBuffer.data(), len);
#endif
}

void DefaultSocket::closeSocket(){
	// CCLog("connectSocket---hClientSocket:%d", hClientSocket);
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		WSACleanup( ) ;
	#else
		shutdown(hClientSocket,2);
		close(hClientSocket);
	#endif
}

DefaultSocket *DefaultSocket::_instance = 0;

DefaultSocket *DefaultSocket::getInstance() {
	if (!_instance)
		_instance = new DefaultSocket(); 
	return _instance;
}