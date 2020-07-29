
#include "erpcdemo.h"
#include <iostream>
#include <cassert>
#include "erpcdemo_server.h"
#include "erpc_threading.h"
#include "erpc_tcp_transport.h"
#include "erpc_basic_codec.h"
#include "erpc_simple_server.h"
#include "erpc_client_manager.h"

using namespace std;
using namespace erpc;

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
ClientManager *g_client;
Crc16 g_crc16;

// Free space allocated inside struct binary_t function implementation
static void free_binary_t_struct(binary_t *data)
{
	if (data->data)
	{
		free(data->data);
	}
}

void Thread1(void *arg)
{
	for (;;)
	{
		cout << "Thread1" << endl;
		auto msg = "HHHHHHHHHHHHHHHHH";
		binary_t b = {(uint8_t *)msg, (uint32_t)strlen(msg)};
		{
			auto resp = RD_demoHello(&b);
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
		auto code = RD_demoHello2(&b, &r);
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

	g_client = new ClientManager();
    erpc_status_t err = g_transport.open();
	if (err)
    {
        cout << "Failed to open connection\n";
        return err;
    }

	g_transport.setCrc16(&g_crc16);
    g_client->setMessageBufferFactory(&g_msgFactory);
    g_client->setTransport(&g_transport);
    g_client->setCodecFactory(&g_basicCodecFactory);

	Thread clientTread1(&Thread1, 0, 0, "thread1");
	clientTread1.start();

	while (1)
	{
	}
}
