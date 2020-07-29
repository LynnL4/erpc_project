
#include <iostream>
#include <cassert>
#include "erpcCore1_server.h"
#include "erpcCore0.h"
#include "erpc_tcp_transport.h"
#include "erpc_basic_codec.h"
#include "erpc_simple_server.h"
#include "erpc_arbitrated_client_manager.h"
#include "erpc_threading.h"
#include "erpc_transport_arbitrator.h"

using namespace std;
using namespace erpc;

void add_services(erpc::SimpleServer *server)
{
	Core1_service *svc = new Core1_service();

    // add services
    server->addService(svc);
}

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

TCPTransport g_transport("localhost", 5407, false);
MyMessageBufferFactory g_msgFactory;
BasicCodecFactory g_basicCodecFactory;
ArbitratedClientManager *g_client;
TransportArbitrator g_arbitrator;
SimpleServer g_server;
Crc16 g_crc16;

// Free space allocated inside struct binary_t function implementation
static void free_binary_t_struct(binary_t *data)
{
	if (data->data)
	{
		free(data->data);
	}
}


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

void Thread1(void *arg)
{
	for (;;)
	{
		cout << "Thread1" << endl;
		auto msg = "HHHHHHHHHHHHHHHHH";
		binary_t b = {(uint8_t *)msg, (uint32_t)strlen(msg)};
		{
			auto resp = Core0_demoHello1(&b);
			cout << "RD_demoHello response:" << resp->data << endl;
			free_binary_t_struct(resp);
		}
		Thread::sleep(1000 * 1000);
	}
}

void Thread2(void *arg)
{
	Thread::sleep(2000 * 1000);
	cout << "Thread2" << endl;
	auto msg = "GGGGGGGGGGGGGGGGGGGGGG";
	binary_t b = {(uint8_t *)msg, (uint32_t)strlen(msg)};
	{
		binary_t r;
		auto code = Core1_demoHello2(&b, &r);
		if (code == lErrorOk_c)
		{
			cout << "RD_demoHello2 response:" << r.data << endl;
			free(r.data);
		}
		else
		{
			cout << "RD_demoHello response ERROR: " << code << endl;
		}
	}
	Thread::sleep(1000 * 1000);
}

int main(int argc, char *argv[])
{
	erpc_status_t err = g_transport.open();
	if (err)
	{
		cout << "Failed to open connection\n";
		return err;
	}

	g_arbitrator.setSharedTransport(&g_transport);
	g_arbitrator.setCodec(g_basicCodecFactory.create());

	g_client = new ArbitratedClientManager();
	g_client->setArbitrator(&g_arbitrator);
	g_client->setCodecFactory(&g_basicCodecFactory);
	g_client->setMessageBufferFactory(&g_msgFactory);

	g_arbitrator.setCrc16(&g_crc16);

	g_server.setTransport(&g_arbitrator);
	g_server.setCodecFactory(&g_basicCodecFactory);
	g_server.setMessageBufferFactory(&g_msgFactory);

	add_services(&g_server);
	g_client->setServer(&g_server);

    Thread serverThread(&runServer, 0, 0, "server");
    serverThread.start(&err);

	g_client->setServerThreadId(serverThread.getThreadId());
	Thread clientTread1(&Thread1, 0, 0, "thread1");
	clientTread1.start();

	while (1)
	{
	}
}
