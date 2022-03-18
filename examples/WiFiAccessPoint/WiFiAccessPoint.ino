/*
  このサンプルプログラムは、OMOMCで販売するToLaREnternをM5Stamp Picoで制御するためのプログラムです。
  
  使い方：
  0. M5Stamp PicoとランタンをGroveケーブルで接続。ランタンを点灯させ、ランタン背面のスイッチをONにする
  1. スマートフォンからアクセスポイント 「yourAp」へ接続
  2. ブラウザから"192.168.4.1"へアクセス。ブラウザからランタンの点灯・消灯を制御する
  
  このサンプルプログラムは、下記プログラムを参考に作成しています。
  https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/WiFiAccessPoint/WiFiAccessPoint.ino
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define LANTERN_PIN 33
#define LED_PIN 32

// Set these to your desired credentials.
const char *ssid = "yourAP";
const char *password = "yourPassword";

WiFiServer server(80);

void lantern_on(){
    digitalWrite(LANTERN_PIN, LOW);
}

void lantern_off(){
    digitalWrite(LANTERN_PIN, HIGH);
}

void led_on(){
    digitalWrite(LED_PIN, HIGH);
}

void setup() {
  pinMode(LANTERN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  led_on();

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn on the Lantern.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn off the Lantenrn.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          lantern_on();               // GET /H turns the Lantern on
        }
        if (currentLine.endsWith("GET /L")) {
          lantern_off();                // GET /L turns the Lantern off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
