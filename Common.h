#ifndef VDE_COMMON_H
#define VDE_COMMON_H

#include <event2\event.h>
#include <boost\filesystem.hpp>
#include <boost\lockfree\spsc_queue.hpp>

#include <string>

#define BUFFER_LEN 2097152

#define FILE_ERROR -2

using std::string;
using boost::lockfree::spsc_queue;

typedef long int32;
typedef long long int64;

struct fileInfo
{
	fileInfo(int64 fileSeek, string sendTime)
		: fileSeek_(fileSeek),
		  sendTime_(sendTime)
	{  }
	int64 fileSeek_;
	string sendTime_;
};

typedef spsc_queue<fileInfo, boost::lockfree::capacity<BUFFER_LEN>> Buffer;

#endif