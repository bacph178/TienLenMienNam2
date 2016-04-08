#include "NetworkManager.h"

#if WIN32
	#pragma comment(lib, "libprotobuf.lib")
#endif


#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

#include "cocos2d.h"
#include <thread>
#include <string>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <vector>
#include "zlib.h"
#include "Utils/DefaultSocket.h"
#include "protobufObject/register.pb.h"
#include "protobufObject/initialize.pb.h"
#include "protobufObject/login.pb.h"
#include "protobufObject/ping.pb.h"


#define MOD_GZIP_ZLIB_WINDOWSIZE 15
#define MOD_GZIP_ZLIB_CFACTOR    9
#define MOD_GZIP_ZLIB_BSIZE      8096
#define MAX_SIZE 1024 * 1024
#define DEBUG 1

USING_NS_CC; 
using namespace std;

vector<char> decompress_gzip2(const char* byte_arr, int length) {

	vector<char> result;
	vector<char> nil_vector;
	if (length == 0) return nil_vector;
	bool done = false;
	z_stream zs;
	memset(&zs, 0, sizeof(zs));

	zs.next_in = (Bytef*)byte_arr;
	zs.avail_in = length;
	zs.total_out = 0;
	zs.zalloc = Z_NULL;
	zs.zfree = Z_NULL;

	if (inflateInit2(&zs, MOD_GZIP_ZLIB_WINDOWSIZE + 16) != Z_OK)  return nil_vector;

	int ret;

	char outbuffer[32768];

	do {
		zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
		zs.avail_out = sizeof(outbuffer);

		ret = inflate(&zs, Z_SYNC_FLUSH);

		if (result.size() < zs.total_out) {
			int size = result.size();
			for (int i = 0; i < zs.total_out - size; i++)
				result.push_back(outbuffer[i]);
		}

	} while (ret == Z_OK);

	inflateEnd(&zs);

	if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
		std::ostringstream oss;
		oss << "Exception during zlib decompression: (" << ret << ") "
			<< zs.msg;
		return nil_vector;
	}
	return result;
}

void callNetwork(char* ackBuf, int size) {
	// bool isConnected = DefaultSocket::getInstance()->connectSocket("192.168.1.50", 1240);
	DefaultSocket::getInstance()->sendData(ackBuf, size);
	vector<char> bufferRead(4096);
	DefaultSocket::getInstance()->readData(bufferRead, 4096);
	vector<pair<google::protobuf::Message*, int>> listMessages = NetworkManager::parseFrom(bufferRead, 4096);
	// DefaultSocket::getInstance()->closeSocket();
}

NetworkManager *NetworkManager::getInstance() {
	if (!_instance)
		_instance = new NetworkManager();
	return _instance;
}

void NetworkManager::setInitialize(bool is_initialized) {
	_initialized = is_initialized;
}

bool NetworkManager::isInitialized() {
	return _initialized;
}

google::protobuf::Message* getTypeMessage(google::protobuf::Message* msg, int messageid) {
	switch (messageid) {
	case NetworkManager::INITIALIZE:
		msg = new BINInitializeResponse();
		break;
	case NetworkManager::REGISTER:
		msg = new BINRegisterResponse();
		break;
	case NetworkManager::LOGIN:
		msg = new BINLoginResponse(); 
	default:
		break;
	}
	return msg;
}

std::vector<std::pair<google::protobuf::Message*, int>> NetworkManager::parseFrom(
	std::vector<char> read_str, int len)  
{
	vector<std::pair<google::protobuf::Message*, int>> listMessages;
	char* chars_from_read = &read_str[0];
	google::protobuf::io::ArrayInputStream arrayIn(chars_from_read, len);
	google::protobuf::io::CodedInputStream codedIn(&arrayIn);
	//read data size
	char *data_size_chars = new char[4];
	codedIn.ReadRaw(data_size_chars, 4);

	int bytes_size = ((data_size_chars[0] & 0xFF) << 24) + ((data_size_chars[1] & 0xFF) << 16) + ((data_size_chars[2] & 0xFF) << 8) + ((data_size_chars[3] & 0xFF) << 0);

	//read compress
	char *is_compress_chars = new char[1];
	codedIn.ReadRaw(is_compress_chars, 1);

	int is_compress = is_compress_chars[0];

	int left_byte_size = bytes_size - 1;

	google::protobuf::Message *response = 0;

	/*if is_compress = 1 */
	if (is_compress == 1) {
		google::protobuf::io::CodedInputStream::Limit msgLimit = codedIn.PushLimit(left_byte_size); //limit compressed size
		//read data compressed
		char *data_compressed = new char[left_byte_size];
		// test data
		// char test_data[] = {31,-117, 8, 0, 0, 0, 0, 0, 0, 0, 99, -32, 102, 126, -55, -63, 40, -60, -102, -101, 24, -97, -101, 8, 0, -41, 18, 51, -108, 13, 0, 0, 0};

		codedIn.ReadRaw(data_compressed, left_byte_size);
		codedIn.PopLimit(msgLimit);
		vector<char> result = decompress_gzip2(data_compressed, (uLong)left_byte_size);
		char* data_uncompressed = reinterpret_cast<char*>(result.data());

		int length = result.size();
		int index = 0;
		bool debug = false;
		while (index < length) {
			//read datablocksize 
			int data_size_block = ((data_uncompressed[index] & 0xFF) << 8) + ((data_uncompressed[index + 1] & 0xFF) << 0);
			//read messageid
			int messageid = ((data_uncompressed[index + 2] & 0xFF) << 8) + ((data_uncompressed[index + 3] & 0xFF) << 0);
			//read protobuf message

			switch (messageid) {
				case NetworkManager::INITIALIZE:
					response = new BINInitializeResponse();
					break;
				case NetworkManager::REGISTER:
					response = new BINRegisterResponse();
					break;
				default:
					break;
			}

			response->ParseFromArray(&data_uncompressed[index + 4], data_size_block - 2);
			index += (data_size_block + 2);
			listMessages.push_back(std::make_pair(response, messageid));
			if (messageid == NetworkManager::INITIALIZE) {
				//initialize 
				NetworkManager::setInitialize(true);
			}
		}
	}
	else {
		/* if is_compression = 0 */
		while (left_byte_size > 0) {
			//read protobuf + data_size_block + mid
			//read datasizeblock
			char *data_size_block_chars = new char[2];

			codedIn.ReadRaw(data_size_block_chars, 2);

			int data_size_block = ((data_size_block_chars[0] & 0xFF) << 8) + ((data_size_block_chars[1] & 0xFF) << 0);

			// read messageid

			char *mid_chars = new char[2];

			codedIn.ReadRaw(mid_chars, 2);

			int messageid = ((mid_chars[0] & 0xFF) << 8) + ((mid_chars[1] & 0xFF) << 0);

			google::protobuf::io::CodedInputStream::Limit msgLimit = codedIn.PushLimit(data_size_block - 2);

			response = getTypeMessage(response, messageid);
			
			response->ParseFromCodedStream(&codedIn);
			
			// vectorMessage.push_back(response);
			codedIn.PopLimit(msgLimit);
			left_byte_size -= (data_size_block + 2);
			if (messageid == NetworkManager::INITIALIZE) {
				//initialize 
				NetworkManager::setInitialize(true);
			}
			listMessages.push_back(std::make_pair(response, messageid));
		}
	}
	return listMessages; 
}

google::protobuf::Message* NetworkManager::initLoginMessage(string username, string password) {
	auto request = new BINLoginRequest();
	if (DEBUG) {
		request->set_username("sanglx");
		request->set_password("123456789");
	}
	else {
	}
	return request;

}

char* NetworkManager::sendData(google::protobuf::Message* request, int os, int messid, 
	std::string _session, int &len) 
{
	std::vector<char> bytes(_session.begin(), _session.end());
	bytes.push_back('\0');
	//N byte session
	char *session = &bytes[0];
	//2 byte lenSession
	int lenSession = strlen(session);
	int size = request->ByteSize() + 11 + lenSession;
	char* ackBuf = new char[size];

	google::protobuf::io::ArrayOutputStream arrayOut(ackBuf, size);
	google::protobuf::io::CodedOutputStream codedOut(&arrayOut);

	char* buf = new char[1];
	buf[0] = os;
	codedOut.WriteRaw(buf, 1); //write os
	char* dataSize = new char[4];


	//data size: protobuf + eot + messageid

	int data_size = request->ByteSize() + 4;
	dataSize[0] = (data_size >> 24) & 0xFF;
	dataSize[1] = (data_size >> 16) & 0xFF;
	dataSize[2] = (data_size >> 8) & 0xFF;
	dataSize[3] = (data_size >> 0) & 0xFF;

	//4 byte data size
	codedOut.WriteRaw(dataSize, 4); 

	//write data size
	char* char_len_session = new char[2];
	char_len_session[0] = (lenSession >> 8) & 0xFF;
	char_len_session[1] = (lenSession >> 0) & 0xFF;
	//2 byte length session
	codedOut.WriteRaw(char_len_session, 2);

	//n byte session
	codedOut.WriteRaw(session, lenSession);
	// loginRequest->SerializeToCodedStream(&codedOut);


	//2 byte messid
	char* mid = new char[2];
	mid[0] = (messid >> 8) & 0xFF;
	mid[1] = (messid >> 0) & 0xFF;

	codedOut.WriteRaw(mid, 2);

	//protobuf 
	request->SerializeToCodedStream(&codedOut);
	
	char *eot = new char[2];
	eot[0] = '\r';
	eot[1] = '\n';

	codedOut.WriteRaw(eot, 2);
	len = size;
	return ackBuf;

}

google::protobuf::Message* NetworkManager::initInitializeMessage(string cp, string appversion, 
	string country, string language, string device_id, string device_info, string ipaddress) {
	auto request = new BINInitializeRequest(); 
	if (DEBUG) {
		request->set_cp("0");
		request->set_appversion("1");
		request->set_country("vn");
		request->set_language("vi");
		request->set_deviceid("00000000");
		request->set_deviceinfo("Samsung galaxy S2");
		request->set_ipaddress("192.168.1.47");
	}
	else {
	}
	return request; 
}

google::protobuf::Message* NetworkManager::initRegisterMessage(string username, string passsword,
	string cp, string app_version, int client_type, string device_id) 
{
	BINRegisterRequest *request = new BINRegisterRequest(); 
	if (DEBUG) {
		request->set_username("sanglx1");
		request->set_password("12345678");
		request->set_cp("0");
		request->set_appversion("1");
		request->set_clienttype(1);
		request->set_deviceid("000000000");
	}
	else {
	}
	return request; 
}

void NetworkManager::connectServer(const char* ip, const int port)
{
	if (DEBUG)
		DefaultSocket::getInstance()->connectSocket("192.168.1.50", 1240);
	else
		DefaultSocket::getInstance()->connectSocket(ip, port);
} 

google::protobuf::Message* NetworkManager::initPingMessage(int disconnectTime) {
	auto request = new BINPingRequest(); 
	request->set_disconecttime(disconnectTime);
	return request; 
}

void sendPing(char* ackBuf, int size) {
	while (1) {
		DefaultSocket::getInstance()->sendData(ackBuf, size);
		std::this_thread::sleep_for(chrono::seconds::duration(5));
	}
}

void NetworkManager::getPingMessageFromServer() {
	google::protobuf::Message* request = initPingMessage(0);
	int size; 
	char* ackBuf = sendData(request, 2, NetworkManager::PING, "", size);
	std::thread *t = new std::thread(sendPing, ackBuf, size);
	if (t->joinable())
		t->detach();
}

void NetworkManager::getInitializeMessageFromServer() {
	//connect to server
	DefaultSocket::getInstance()->connectSocket("192.168.1.50", 1240);

	google::protobuf::Message *request = initInitializeMessage();
	int size; 
	char* ackBuf = sendData(request, 2, NetworkManager::INITIALIZE, "", size); 

	std::thread *t = new std::thread(callNetwork, ackBuf, size);
	if (t->joinable())
		t->detach(); 
}

void NetworkManager::getLoginMessageFromServer() {
	google::protobuf::Message *request = initLoginMessage();
	int size;
	char* ackBuf = sendData(request, 2, NetworkManager::LOGIN, "", size);

	std::thread *t = new std::thread(callNetwork, ackBuf, size);
	if (t->joinable())
		t->detach();
}

void NetworkManager::getRegisterMessageFromServer() 
{

	int size; 
	google::protobuf::Message *request = initRegisterMessage();
	char* ackBuf = sendData(request, 2, NetworkManager::REGISTER, "", size);


	std::thread *t = new std::thread(callNetwork, ackBuf, size);
	if (t->joinable())
		t->detach();
	
}

void NetworkManager::recvMessage() {
	while (1) {
		vector<char> bufferRead(4096);
		int canRead = DefaultSocket::getInstance()->readData(bufferRead, 4096);
		vector<pair<google::protobuf::Message*, int>> listMessages = NetworkManager::parseFrom(bufferRead, 4096);
		if (listMessages.size() > 0) {
			NetworkManager::listEvent.push_back(listMessages);
		}
	}
}

void NetworkManager::listenData() {
	std::thread *t = new std::thread(&NetworkManager::recvMessage, this);
	if (t->joinable())
		t->detach(); 
}

NetworkManager::NetworkManager() 
{
}

NetworkManager::~NetworkManager()
{
}	

bool NetworkManager::_initialized = false;

NetworkManager *NetworkManager::_instance = 0;

vector<std::vector<std::pair<google::protobuf::Message*, int>>> NetworkManager::listEvent;