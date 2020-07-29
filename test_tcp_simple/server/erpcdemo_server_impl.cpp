/*
 * erpcdemo_server_impl.cpp
 * erpcdemo RPC implementation
 *  Created on: Apr 15, 2020
 *      Author: guyadong
 */

#include <iostream>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include "erpcdemo_server.h"
#include "erpc_threading.h"
#include "erpc_server_setup.h"
#include "erpc_simple_server.h"
using namespace std;
/** 返回当前时间字符串 */
static std::string now_str() {
	time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::stringstream ss;
	ss << std::put_time(std::localtime(&t), "%F %T");
	return ss.str();
}

binary_t * RD_demoHello(const binary_t * txInput){
	//sleep(5);
	cout << "RD_demoHello called" << endl;
	string o ((char*)txInput->data);
	o.append("@").append(now_str());
	auto ol = strlen(o.c_str());
	char* buf = (char*)malloc(ol + 1);
	strncpy(buf,o.c_str(),ol);
	erpc::Thread::sleep(2000*2000);
	return new binary_t{(uint8_t*)buf,(uint32_t)ol};
}

lockErrors_t RD_demoHello2(const binary_t * txInput, binary_t * txOutput)
{
	cout << "RD_demoHello2 called" << endl;
	string o ((char*)txInput->data);
	o.append("@").append(now_str());
	auto ol = strlen(o.c_str());
	char* buf = (char*)malloc(ol + 1);
	if(!buf){
		return lErrorOutofMemory_c;
	}
	strncpy(buf,o.c_str(),ol);
	txOutput->data = (uint8_t*)buf;
	txOutput->dataLength = (uint32_t)ol;
	//erpc::Thread::sleep(1000*2000);
	return lErrorOk_c;
}
lockErrors_t RD_demoHello3(const binary_t * txInput, int8_t txOutput[64], int32_t * size)
{
	cout << "RD_demoHello3 called" << endl;
	string o ((char*)txInput->data);
	o.append("@").append(now_str());
	strncpy((char*)txOutput,o.c_str(),64);
	*size = (int32_t)o.size();
	return lErrorOk_c;
}

void callback1(int32_t a, int32_t b)
{
	cout << "a + b = " << a + b <<endl;
}

void myFun(const callback1_t pCallback1_t)
{
	pCallback1_t(2, 3);
}

void add_services(erpc::SimpleServer *server)
{
    // define services to add on heap
    // allocate on heap so service doesn't go out of scope at end of method
    // NOTE: possible memory leak? not ever deleting
    DEMO_service *svc = new DEMO_service();

    // add services
    server->addService(svc);
}

