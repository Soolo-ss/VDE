#ifndef VDE_SERVER_H
#define VDE_SERVER_H

#include "Common.h"
#include <boost/noncopyable.hpp>
 
class DataProcess;
class SendProcess;

class Server : boost::noncopyable
{
public:
	Server(int argc, char** argv);

	bool Init();

	void StartUp();

protected:
	bool AcceptCallback(boost::shared_ptr<tcp::socket> pSocket, const boost::system::error_code& error);

private:
	string fileName_;
	short listenPort_;
	short sendSpeed_;
	int listenFd_;

	boost::atomic<bool> isDone_;

	//boost.asio 配置
	io_service ioService_;
	tcp::acceptor acceptor_;
	ip::tcp::endpoint serverAddress_;

	//global Buffer without lock
	Buffer sendBuffer_;

	DataProcess* dataProcess_;
	SendProcess* sendProcess_;
};


#endif