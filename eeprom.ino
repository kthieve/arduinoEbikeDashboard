
#include "Wire.h"
#include "I2C_eeprom.h"
#include "eepromCommands.h"

#define EEPROM_ADDRESS 0x50 

I2C_eeprom rom(EEPROM_ADDRESS, I2C_DEVICESIZE_24LC16);


int d=50; //delay


void setup() {
  Serial.begin(115200);
  rom.begin();
  checkROM(EEPROM_ADDRESS,rom);
  delay(5);
  Serial.println("Writing");
  int x= 12345;
  int start=20;
  int length =5;
  writeNumber(rom,x,start,length);
  Serial.println(readNumber(rom,start,length));

}

void loop() {


}
