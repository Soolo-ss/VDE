#ifndef VDE_COMMON_H
#define VDE_COMMON_H


#include <boost/lockfree/spsc_queue.hpp>
#include <boost/bind.hpp> 
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include <string>

#define BUFFER_LEN 2097152

#define FILE_ERROR -2

using std::string;
using boost::lockfree::spsc_queue;
using namespace boost::asio;
using boost::asio::ip::tcp;
using boost::asio::ip::address;

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


typedef spsc_queue<int, boost::lockfree::capacity<BUFFER_LEN> > Buffer;

#endif