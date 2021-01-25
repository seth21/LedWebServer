#include "Config.hpp" 
#include <SPI.h> 
//#include "SdFat.h"
#include <SD.h>
int cs = 10;
File myFile;
//SdFat SD;

Config::Config()
{
	
};
	
Config::~Config()
{
	delete ssid;
    delete pass;
};

void Config::init() 
{
     // make sure that the default chip select pin is declared OUTPUT
    pinMode(cs, OUTPUT);
   // see if the card is present
    if (!SD.begin(cs)) 
    {
        Serial.println("Card failed to initialize, or not present!"); 
        return;
    }
    Serial.println("SD card initialized.");
    // open the file named ourfile.txt
    myFile = SD.open("config.txt");
    
    if (myFile) {
        Serial.println("Opened config.txt");
        // read from the file until there's nothing else in it:
        String buf;
        while (myFile.available()) {
            buf = myFile.readStringUntil('\n');
            buf.trim();
            parseSetting(buf);
        }
        // close the file:
        myFile.close();
        } else {
        // if the file didn't open, print an error:
        Serial.println("error opening config.txt");
    }
}

char* Config::getSSID() 
{
    return ssid;
}

char* Config::getPass() 
{
    return pass;
}

void Config::parseSetting(String &str) 
{
    int index = str.indexOf(":");
    String s1 = str.substring(0, index);
    String s2 = str.substring(index+1, str.length());
  
    if (s1 == "ssid"){
        ssid = new char[s2.length() +1];
        s2.toCharArray(ssid, s2.length() +1);
    }
    else if (s1 == "pass"){
        pass = new char[s2.length() +1];
        s2.toCharArray(pass, s2.length() +1);
    }
 
};

