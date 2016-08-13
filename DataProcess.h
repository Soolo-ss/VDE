#ifndef VDE_DATAPROCESS_H
#define VDE_DATAPROCESS_H
//baratol ¿â ÎÄ¼þ²Ù×÷  

#include "Common.h"

#include <stdio.h>

class DataProcess : boost::noncopyable
{
public:
	DataProcess(string fileName, short sendSpeed);

	void PreHandData(Buffer& buffer);
private:
	string fileName_;
	short sendSpeed_;

	//for tmep
	FILE* fileObj_;
};

#endif