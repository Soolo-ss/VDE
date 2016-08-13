#include "DataProcess.h"

#include <time.h>

#define READ_MOMERY_SIZE		10485760		

DataProcess::DataProcess(string fileName, short sendSpeed)
	: fileName_(fileName), sendSpeed_(sendSpeed)
{
	fileObj_ = fopen(fileName_.c_str(), "r");
	if (fileObj_ == NULL)
	{
		printf("File is not exits!\n");
		exit(FILE_ERROR);
	}
	fseek(fileObj_, 0, SEEK_SET);
}

void DataProcess::PreHandData(Buffer& buffer)
{
	char* readBuf = new char[READ_MOMERY_SIZE];
	size_t msgPos = 0;
	size_t nextMsgPos = 0;
	
	while (0 != fread(readBuf, 1, READ_MOMERY_SIZE, fileObj_))
	{
		string readStr(readBuf, READ_MOMERY_SIZE);
		msgPos = readStr.find_first_of("A=", msgPos);
		++msgPos;
		nextMsgPos = readStr.find_first_of("A=", msgPos);
		string msg = readStr.substr(msgPos, nextMsgPos - msgPos);
		size_t timePos = msg.find_first_of("B=");
		string time = msg.substr(timePos + 2, 17);
		fileInfo info(msgPos, time);
		buffer.push(info);
	}
}