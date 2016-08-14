#include "SendProcess.h"

void SendProcess::SendData(boost::shared_ptr<tcp::socket> pSocket, Buffer& buffer, bool isPreHandDone)
{
  buffer.pop()
  pSocket->async_write_some()
}