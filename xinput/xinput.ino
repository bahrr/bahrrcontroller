//Upload this on a Leonardo to convert the signal to XInput

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <XInput.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

int Inputs[10];

int Outputs[]{ //i am aware of the fact that this is a major bruh moment but it works
  BUTTON_A,
  BUTTON_B,
  BUTTON_X,
  BUTTON_Y,
  BUTTON_LB,
  BUTTON_RB,
  BUTTON_BACK,
  BUTTON_START
};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  XInput.setRange(JOY_LEFT, 0, 1023);
  XInput.begin();
}

void loop() {
  if (radio.available()) {
    radio.read(&Inputs, sizeof(Inputs));
    for (int i=0; i<8; i++) {
      XInput.setButton(Outputs[i], Inputs[i]);
    }
    XInput.setJoystick(JOY_LEFT, Inputs[8], 1023 - Inputs[9]);
    for (int i=0; i<10; i++){ //just prints it to make life easier
      Serial.println(Inputs[i]);
          
    }
    Serial.print("break\n");
  }
}
