#include "SendProcess.h"

void SendProcess::SendData(boost::shared_ptr<tcp::socket> pSocket, Buffer& buffer, bool isPreHandDone)
{
  fileInfo send;
  buffer.pop(send);
  pSocket->async_write_some()
}