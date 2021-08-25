// Adafruit IO Publish & Subscribe Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
float volt = 0;
String lambadurum;
// Track time of last published messages and limit feed->save events to once
// every IO_LOOP_DELAY milliseconds.
//
// Because this sketch is publishing AND subscribing, we can't use a long
// delay() function call in the main loop since that would prevent io.run()
// from being called often enough to receive all incoming messages.
//
// Instead, we can use the millis() function to get the current time in
// milliseconds and avoid publishing until IO_LOOP_DELAY milliseconds have
// passed.
#define IO_LOOP_DELAY 5000
unsigned long lastUpdate = 0;

// set up the 'counter' feed
AdafruitIO_Feed *voltaj = io.feed("voltaj");
AdafruitIO_Feed *lamp = io.feed("lamp");
void setup() {
pinMode(D8,OUTPUT);
  // start the serial connection
 /* Serial.begin(115200);
  
  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO"); */

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  lamp->onMessage(handleMessage);

  // wait for a connection
/*  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText()); */
  lamp->get();

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  
   volt=analogRead (A0)*0.0176;// Analog sinyal değerini 0-255 aralığına daraltıyoruz.
  
  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
    // save count to the 'counter' feed on Adafruit IO
   // Serial.print("sending -> ");
   // Serial.println(volt);
    voltaj->save(volt);

    // increment the count by 1
    //count++;

    // after publishing, store the current time
    lastUpdate = millis();
  }

}

// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data) {

 // Serial.print("received <- ");
 // Serial.println(data->value());
  lambadurum= data->value();
  if(lambadurum=="0"){
 digitalWrite(D8,LOW);
 }
 else if(lambadurum=="1"){
 digitalWrite(D8,HIGH);
 }
}
