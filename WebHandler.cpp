#include "WebHandler.hpp"
RingBuffer buf(8);
int ledStatus = LOW;
WebHandler::WebHandler()
{
   // buf = new RingBuffer(8);
}

WebHandler::~WebHandler()
{
    //delete buf;
}

//int ledStatus = LOW;
void WebHandler::handleLoop(WiFiEspServer &server)
{
    WiFiEspClient client = server.available(); // listen for incoming clients

  if (client)
  {                               // if you get a client,
    Serial.println("New client"); // print a message out the serial port
    buf.init();                   // initialize the circular buffer
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        buf.push(c);            // push it to the ring buffer

        // printing the stream to the serial monitor will slow down
        // the receiving of data from the ESP filling the serial buffer
        //Serial.write(c);

        // you got two newline characters in a row
        // that's the end of the HTTP request, so send a response
        if (buf.endsWith("\r\n\r\n"))
        {
          sendHttpResponse(client);
          break;
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (buf.endsWith("GET /H"))
        {
          Serial.println("Turn led ON");
          ledStatus = HIGH;
          digitalWrite(2, HIGH); // turn the LED on (HIGH is the voltage level)
        }
        else if (buf.endsWith("GET /L"))
        {
          Serial.println("Turn led OFF");
          ledStatus = LOW;
          digitalWrite(2, LOW); // turn the LED off by making the voltage LOW
        }
      }
    }

    // close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}

void WebHandler::sendHttpResponse(WiFiEspClient &client) 
{
    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
    // and a content-type so the client knows what's coming, then a blank line:
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();

    // the content of the HTTP response follows the header:
    client.print("The LED is ");
    client.print(ledStatus);
    client.println("<br>");
    client.println("<br>");

    client.println("Click <a href=\"/H\">here</a> turn the LED on<br>");
    client.println("Click <a href=\"/L\">here</a> turn the LED off<br>");

    // The HTTP response ends with another blank line:
    client.println();
}
