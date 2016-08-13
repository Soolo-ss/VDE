#ifndef VDE_SERVER_H
#define VDE_SERVER_H

#include "Common.h"
#include <boost\noncopyable.hpp>
#include <boost\lockfree\spsc_queue.hpp>
#include <boost\asio.hpp>
 
class DataProcess;
class SendProcess;

class Server : boost::noncopyable
{
public:
	Server(int argc, char** argv);

	bool Init();

	void StartUp();
private:
	string fileName_;
	short listenPort_;
	short sendSpeed_;
	int listenFd_;

	//供处理与发送公用的全局容器(环形缓冲区）
	Buffer sendBuffer_;

	DataProcess* dataProcess_;
	SendProcess* sendProcess_;
};


#endif