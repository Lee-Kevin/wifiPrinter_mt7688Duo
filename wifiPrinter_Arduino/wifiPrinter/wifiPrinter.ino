/* 
 * File: wifiPrinter.ino
 * 
 * Auther: lambor
 * Date: 2016-03-29
 * 
 * 
 */

#include <Arduino.h>
#include <Process.h>
#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"

#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

char *title = "Message";

#define BUF_SIZE  512
char *g_Buffer;
uint16_t g_BufferSize;

/**
 * @Fcuntion - printerServe
 * brief - call yun-bridge process to cat weather forcast files,
 * the report including a week forcast and the current one.
 */
void getMessage()
{
  String data = "";
  Process p;
  int index = 0;
  
  g_Buffer = (char *)malloc(BUF_SIZE);
  memset(g_Buffer, '\0', BUF_SIZE);
  
  p.begin("cat");  
  p.addParameter("/root/wifi_printer/files/printer_status.txt");     
  p.run();  

  while (p.available() > 0) {
    char c = p.read();
    g_Buffer[index++] += c;
  }
  g_Buffer[index++] += '\0';  
  g_BufferSize = index;
  
  if(g_BufferSize > 0) {
    Serial.print("Status: ");
    Serial.println(g_Buffer);
  }
  
  if(strstr("1", g_Buffer)) {
    p.begin("/bin/ash");  
    p.addParameter("/root/wifi_printer/script/clear_printer_status.sh");     
    p.run();
    
    memset(g_Buffer, '\0', BUF_SIZE);
    index = 0;
    
    p.begin("cat");  
    p.addParameter("/root/wifi_printer/files/message.txt");     
    p.run();  

    while (p.available() > 0) {
    char c = p.read();
    g_Buffer[index++] += c;
    }
    g_Buffer[index++] += '\0';  
    g_BufferSize = index;
    
    if(g_BufferSize > 0) {
      Serial.print("Message: ");
      Serial.println(g_Buffer);
      printerServe(title, g_Buffer);  // print message from your web page.
    }
  }
  
  free(g_Buffer);
}

// Printer server
void printerServe(char *title, String data){  
  printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'  
  printer.justify('C');
  printer.println(title);
  printer.setDefault(); // Restore printer to defaults
  
  printer.print(data);
  printer.feed(4);  
}


void setup() {    
  // Initialize Printer  
  mySerial.begin(19200);  // Initialize SoftwareSerial  
  printer.begin();        // Init printer (same regardless of serial type)
  printer.setDefault(); // Restore printer to defaults  
  
  // Initialize Bridge
  Bridge.begin();
  
  // Initialize Serial 
  Serial.begin(9600);
  Serial.println("begin...");
}

void loop() {
  getMessage();
  delay(1000);
}