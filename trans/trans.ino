/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
const int numofin = 10; // the number of inputs, 10 at the moment
int Inputs [numofin]; // the list of input values

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode (0, INPUT_PULLUP); // setup input buttons
  pinMode (1, INPUT_PULLUP);
  pinMode (2, INPUT_PULLUP);
  pinMode (3, INPUT_PULLUP);
  pinMode (4, INPUT_PULLUP);
  pinMode (5, INPUT_PULLUP);
  pinMode (6, INPUT_PULLUP);
  pinMode (9, INPUT_PULLUP);
  pinMode (A0, INPUT);
  pinMode (A1, INPUT);
}

void loop() {
  Inputs[0] = !digitalRead(5);  // add inputs to list
  Inputs[1] = !digitalRead(4);
  Inputs[2] = !digitalRead(2);  
  Inputs[3] = !digitalRead(1);
  Inputs[4] = !digitalRead(0);  
  Inputs[5] = !digitalRead(3);
  Inputs[6] = !digitalRead(6);  
  Inputs[7] = !digitalRead(9);
  Inputs[8] = analogRead(A0);  
  Inputs[9] = analogRead(A1);
  
  const char text[] = "Hello World";
  radio.write(&Inputs, sizeof(Inputs));
  delay(10);
}
