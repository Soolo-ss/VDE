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

	void SendData(Buffer& buffer);
private:
	int sendFd_;
};

#endif