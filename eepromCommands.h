
#ifndef EEPROMCOMMANDS_H
#define EEPROMCOMMANDS_H

#include "Wire.h"
#include "I2C_eeprom.h"


bool checkROM(int address,I2C_eeprom ee){
  Serial.println("Checking Rom");
  Wire.begin();
  delay(1000);
  Wire.beginTransmission(address);
  int error = Wire.endTransmission();
  if (error==0){
    Serial.print("EEPROM device found at address  0x");
    Serial.print(address,HEX);
    Serial.println();
    

  if (! ee.isConnected())
  {
    Serial.println("ERROR: Can't find eeprom\nstopped...");
    while (1);
  }

  Serial.println("\nTEST: determine size");
  uint32_t size = ee.determineSize();
  if (size > 0)
  {
    Serial.print("SIZE: ");
    Serial.print(size);
    Serial.println(" KB");
  }
  else if (size == 0)
  {
    Serial.println("WARNING: Can't determine eeprom size");
  }

  }
  else{
    Serial.print("ERROR!: EEPROM not found\n");
    return false;
  }
  Serial.println("DONE");
  return true;
}

void writeNumber(I2C_eeprom rom, int number, int start, int length){
  int x=number;
  for(int i=start; i<start+length; ++i){
    int digit=x%10;
    Serial.print("Digit to write: ");
    Serial.println(digit);
    if(rom.readByte(i)!=digit){
      rom.writeByte(i, digit);
      delay(100);
      Serial.print("Value ");
      Serial.print(rom.readByte(i));
      Serial.print(" written on address ");
      Serial.println(i);
    }
    else{
      Serial.println("Value already exist, skipping");
    } 
    x=x/10;   
    delay(100);
    
  }
  for(int i=start; i<start+length; ++i){
//    Serial.println(rom.readByte(i));
    delay(100);
  }
}

int readNumber(I2C_eeprom rom,  int start, int length){
  int number=0;
  for(int i=start+length-1; i>start; --i){
    number*=10;
    number+=rom.readByte(i);
//    Serial.println(number);
    delay(100);
  }
  return number;
}


// bool clearROM(AT24Cxx rom, uint16_t bytes=128){
//   Serial.print("Clearing ROM for");
//   Serial.print(bytes);
//   Serial.println(" bytes");

//   //write a test data 22 on address 5 to check 
//   rom.write(5, 22);
//   Serial.print("Read Rom 5: ");
//   Serial.print( rom.read(5));
//   Serial.println();

//   Serial.println("Cleaning ROM");
//   unsigned long start_time = millis();
//   unsigned int mid_time = start_time;
  
//   for(uint16_t i=0; i<bytes; ++i){
    
    
//     if(millis()-mid_time >500){
//       mid_time =millis();
//       Serial.print("Progress: ");
//       Serial.print((float)i/(float)bytes *100);
//       Serial.print("%\n");
//     }
//     rom.write(i,0);
//   }

//   Serial.print("All ");
//   Serial.print(bytes);
//   Serial.print(" Addresses have been cleared in ");
//   Serial.print(millis() - start_time);
//   Serial.println(" ms.\n");
//   Serial.print("Testing address 0x05, Should be 0\n");
//   Serial.println(rom.read(5));
//   if(rom.read(5) == 0){
//     Serial.println("ROM Cleaning Successful");
//     return 1;
//   }
//   else{
//     Serial.println("ERROR: ROM Cleaning NOT Successful!!");
//     return 0;
//   }
// }


#endif