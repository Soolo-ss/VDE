#include "Server.h"
#include "DataProcess.h"
#include "SendProcess.h"

#include <cmdline.h>

Server::Server(int argc, char** argv)
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


	dataProcess_ = new DataProcess(fileName_, sendSpeed_);
	sendProcess_ = new SendProcess(listenPort_);
}