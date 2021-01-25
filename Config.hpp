#ifndef CONFIG_H
#define CONFIG_H
#pragma once
#include <WString.h>
	
class Config  
{
	private:
		char *ssid = NULL;            // your network SSID (name)
		char *pass = NULL;

	public:

		Config();
		~Config();
		void init();
		char* getSSID();
		char* getPass();
		void parseSetting(String &str);

};
#endif