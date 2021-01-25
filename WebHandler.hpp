#ifndef WEBHANDLER_H
#define WEBHANDLER_H
#pragma once
#include "WiFiEsp.h"

class WebHandler  
{
	private:
		//RingBuffer *buf;
		//int ledStatus = LOW;
	public:

		WebHandler();
		~WebHandler();
		void handleLoop(WiFiEspServer &server);
		void sendHttpResponse(WiFiEspClient &client);

};
#endif