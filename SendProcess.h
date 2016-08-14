#ifndef VDE_SENDPROCESS_H
#define VDE_SENDPROCESS_H

#include "Common.h"

class SendProcess : boost::noncopyable
{
public:
	SendProcess(int sendFd)
		: sendFd_(sendFd)
	{

	}

	void SendData(boost::shared_ptr<tcp::socket> pSocket, Buffer& buffer, bool isPreHandDone);
private:
	int sendFd_;
};

#endif