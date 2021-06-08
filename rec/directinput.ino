//upload this to a Leonardo or other ATMega32U4 Arduino

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Joystick.h>

Joystick_ Joystick;

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

int Inputs[10];

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  Joystick.begin();
  Joystick.setXAxisRange(0,1023);
  Joystick.setYAxisRange(0,1023);
}

void loop() {
  if (radio.available()) {
    radio.read(&Inputs, sizeof(Inputs));
    for (int i=0;i<8;i++){
      Joystick.setButton(i,Inputs[i]);      
    }
    Joystick.setXAxis(Inputs[8]);
    Joystick.setYAxis(Inputs[9]);
    for (int i=0; i<10; i++){
      Serial.println(Inputs[i]);
          
    }
    Serial.print("break\n");
  }
}
