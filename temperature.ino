#include <Wire.h>
#define address_temp1 0x4F

unsigned long delay_time = 1000, prev_time;


void setup()
{
  Wire.begin();
  Serial.begin(9600);
  prev_time = millis();
}

void loop()
{
  float temperature_1;
  if (prev_time + delay_time <= millis()){ // only execute every delay_time in miliseconds
    
    temperature_1 = temperature(address_temp1, 2);
    Serial.println("--------Sensor1--------");
    Serial.println("---Tempearature degC---");
    Serial.println(temperature_1,2);
    prev_time = millis();
    delay_time = 3000;
  }
 
}


// Get Temperature. temp_addr - address of the i2C device, byte_read - numberof bytes to read

float temperature(int temp_addr, int byte_read){
  byte msb, lsb;
  Wire.beginTransmission(temp_addr);            // start I2C transmission with sensor
  Wire.write(0x00);                             // set pointer to read data from
  Wire.endTransmission();                       // stop I2C transmisstion with sensor
  
  Wire.requestFrom(temp_addr, byte_read);       // request 2 bytes from the sensor

  if (Wire.available()>=byte_read) {            // check if bytes are available 
      msb = Wire.read();                        // read MSB
      lsb = Wire.read();                        // real LSB
      return  ((msb * 256 + lsb) / 32) * 0.125; // equivalent of shifting MSB by 8 places left and adding lower byte. Then shifting by 5 places right to remove unused bytes
          
  }
  return 0.0;
}
