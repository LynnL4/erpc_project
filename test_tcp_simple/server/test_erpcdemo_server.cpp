#include <iostream>
#include <cassert>
#include "erpcdemo_server.h"
#include "erpc_threading.h"
#include "erpc_tcp_transport.h"
#include "erpc_basic_codec.h"
#include "erpc_simple_server.h"

using namespace std;
using namespace erpc;

void add_services(erpc::SimpleServer *server);

class MyMessageBufferFactory : public MessageBufferFactory
{
public:
    virtual MessageBuffer create()
    {
        uint8_t *buf = new uint8_t[1024];
        return MessageBuffer(buf, 1024);
    }

    virtual void dispose(MessageBuffer *buf)
    {
        assert(buf);
        if (*buf)
        {
            delete[] buf->get();
        }
    }
};

TCPTransport g_transport("localhost", 5407, true);
MyMessageBufferFactory g_msgFactory;
BasicCodecFactory g_basicCodecFactory;
SimpleServer g_server;

Crc16 g_crc16;

void runServer(void *arg)
{
	cout << "start erpcdemo server" << endl;
	/* run server */
	while (true)
	{
		g_server.poll();
	}
	
	g_transport.close();
}

int main(int argc, char *argv[]){
	


	erpc_status_t result = g_transport.open();
    if (result)
    {
    	cout <<  "Failed to open connection\n" ;
        return 1;
    }

	g_transport.setCrc16(&g_crc16);
    g_server.setMessageBufferFactory(&g_msgFactory);
    g_server.setTransport(&g_transport);
    g_server.setCodecFactory(&g_basicCodecFactory);

	add_services(&g_server);

    Thread serverThread(&runServer, 0, 0, "server");
	serverThread.start();

	while(1);

	return 0;
}
