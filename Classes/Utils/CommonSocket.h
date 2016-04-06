#ifndef _COMMON_SOCKET_H_
#define _COMMON_SOCKET_H_
#include <vector>
using namespace std;
class CommonSocket{
public:
	virtual bool connectSocket(const char* serverIP, int serverPort) = 0;

	virtual int	readData(vector <char> &vectorBuffer,int len) = 0;
	virtual int sendData(const char* data, int len) = 0;
	virtual void closeSocket() = 0;
};
#endif // !1
