#ifndef  _NETWORK_MANAGER_H_
#define  _NETWORK_MANAGER_H_

#include <vector>
#include <string>

using namespace std;

class NetworkManager
{
public:
	NetworkManager();
	virtual ~NetworkManager();	
	char* initRegisterMessage(int, int &); 
	char* initInitializeMessage(int, int &); 
	void getRegisterMessageToServer();
	void getInitializeMessageToServer();
	// static void callNetwork(char* , int); 
	static void parseFrom(std::vector<char> , int);
	static void setInitialize(bool _isInitialize);
	static bool isInitialized(); 
	static bool _initialized;
};

#endif // _NETWORK_MANAGER_H_

