#include "Server.h"
#include "DataProcess.h"
#include "SendProcess.h"

#include "cmdline.h"

Server::Server(int argc, char** argv)
	: isDone_(false),
		acceptor_(ioService_)
{
	cmdline::parser cmdParser;

	//Ìí¼Ó²ÎÊý
	cmdParser.add<string>("file", 'f', "dest file", true, "");
	cmdParser.add<short>("port", 'p', "listen port", false, 7120, cmdline::range(1, 65535));
	cmdParser.add<short>("speed", 's', "send speed", false, 1);

	cmdParser.parse_check(argc, argv);

	fileName_ = cmdParser.get<string>("file");
	listenPort_ = cmdParser.get<short>("port");
	sendSpeed_ = cmdParser.get<short>("speed");

}

bool Server::Init()
{
	serverAddress_ = tcp::endpoint(tcp::v4(), listenPort_);
	boost::system::error_code ec;

	if (acceptor_.open(tcp::v4(), ec))
	{
		return false;
	}



	acceptor_.bind(serverAddress_, ec);

	if (ec)
	{
		if (ec.value() != boost::system::errc::operation_canceled)
		{
			std::cerr << boost::system::system_error(ec).what() << std::endl;
			return false;
		}
	}

	dataProcess_ = new DataProcess(fileName_, sendSpeed_);
	sendProcess_ = new SendProcess(listenPort_);

	return true;
}

void Server::StartUp()
{
	acceptor_.listen(1024);

	boost::shared_ptr<tcp::socket> pSocket(new tcp::socket(ioService_));

	acceptor_.async_accept(*pSocket, boost::bind(&Server::AcceptCallback,
																							this, 
																							pSocket,
																							boost::asio::placeholders::error
																							)
												);

	if (isDone_ == false)
	{
		isDone_ = true;
		dataProcess_->PreHandData(sendBuffer_);
	}
}

bool Server::AcceptCallback(boost::shared_ptr<tcp::socket> pSocket, const boost::system::error_code& error)
{
	if (error)
	{
		if (error.value() != boost::system::errc::operation_canceled)
		{
			std::cerr << boost::system::system_error(error).what() << std::endl;
			return false;
		}
	}

 	//异步调用，不阻塞， 直接返回
	StartUp();

	sendProcess_->SendData(pSocket, sendBuffer_, isDone_);

	return true;
}






