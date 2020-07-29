#include <iostream>
#include <time.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <unistd.h>
#include "erpc_threading.h"
#include "erpc_server_setup.h"
#include "erpc_simple_server.h"
#include "erpcCore0.h"
#include "erpcCore1.h"

using namespace std;
/** 返回当前时间字符串 */
static std::string now_str() {
	time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::stringstream ss;
	ss << std::put_time(std::localtime(&t), "%F %T");
	return ss.str();
}

binary_t * Core0_demoHello1(const binary_t * txInput){
	//sleep(5);
	cout << "Core0_demoHello1 called" << endl;
	string o ((char*)txInput->data);
	o.append("@").append(now_str());
	auto ol = strlen(o.c_str());
	char* buf = (char*)malloc(ol + 1);
	strncpy(buf,o.c_str(),ol);

	cout << "Thread1" << endl;
	auto msg = "ADASDASDSD";
	binary_t b = {(uint8_t *)msg, (uint32_t)strlen(msg)};
	callback(&b);
	erpc::Thread::sleep(2000*2000);
	return new binary_t{(uint8_t*)buf,(uint32_t)ol};
}

lockErrors_t Core0_demoHello2(const binary_t * txInput, binary_t * txOutput)
{
	cout << "Core0_demoHello2 called" << endl;
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
lockErrors_t Core0_demoHello3(const binary_t * txInput, int8_t txOutput[64], int32_t * size)
{
	cout << "Core0_demoHello2 called" << endl;
	string o ((char*)txInput->data);
	o.append("@").append(now_str());
	strncpy((char*)txOutput,o.c_str(),64);
	*size = (int32_t)o.size();
	return lErrorOk_c;
}
