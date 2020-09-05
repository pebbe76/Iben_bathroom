//#include <DHT.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <SoftwareSerial.h>


int sensorBlackWater = 0;
int sensorShowerSump = 0;
int sensorTankLevel = 0;

//False: liquid detected. True: liquid not detected
bool sensorTank1 = true;
bool sensorTank2 = true;
bool sensorTank3 = true;
bool sensorTank4 = true;

//Pin assignement 
int tankPin1 = 4;
int tankPin2 = 5;
int tankPin3 = 6;
int tankPin4 = 7;
int anaWaterSensorBlackWater = A0;
int anaWaterSensorShowerSump = A2;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//SoftwareSerial usbSerialComm (0, 1); //Digital pin 0 receive (RX), digital pin 1 transmit (TX)
//SerialUSB usbSerialComm;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  //usbSerialComm.begin(9600);
  //while (!Serial){
  //  ; // wait for serial port to connect. Needed for native USB port only
  //}


  pinMode(tankPin1, INPUT);
  pinMode(tankPin2, INPUT);
  pinMode(tankPin3, INPUT);
  pinMode(tankPin4, INPUT);

  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  /*
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x7B for 128x64 (8bit). Remove LIB for = 0x3C for 7bit Arduino max address space
    //Catch error on Display object start
    Serial.println("feil");
  }
  */
  /*
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();
  //display.drawPixel(10, 10, WHITE);
  display.display();
  */
}

void loop() {
  sensorBlackWater = 0;
  sensorShowerSump = 0;
  sensorTankLevel = 0;
  //Serial.println("test serial");
  readTankLevel();

//***************************** BLACK WATER LEAKAGE SENSOR ***********************************
  sensorBlackWater = analogRead(anaWaterSensorBlackWater); //Analog input 2
//********************************************************************************************

//***************************** GREY WATER LEAKAGE SENSOR ************************************
  sensorShowerSump = analogRead(anaWaterSensorShowerSump); //Analog input 5
//********************************************************************************************
/*
  display.clearDisplay();
  delay(2000);
  //display.drawPixel(10, 10, WHITE);
  // Clear the buffer
  //display.clearDisplay();
  //display.display();
  displayOLED();
  transmitData();
  //usbSerialComm.println("test");
*/
delay(2000);
transmitData();
}

void readTankLevel(){
  //********************************** BLACK WATER TANK ****************************************
  sensorTank1 = digitalRead(tankPin1); //Digital input 2
  sensorTank2 = digitalRead(tankPin2); //Digital input 3
  sensorTank3 = digitalRead(tankPin3); //Digital input 4
  sensorTank4 = digitalRead(tankPin4); //Digital input 5
  
  //need one reading for all four sensors, then if/else or switch/case on what sensor is active
  if (sensorTank4 == false) {
    sensorTankLevel = 100;
  }
  else if (sensorTank3 == false){
    sensorTankLevel = 75;
  }
  else if (sensorTank2 == false){
    sensorTankLevel = 50;
  }
  else if (sensorTank1 == false){
    sensorTankLevel = 25;
  }
}

void displayOLED (){
  //display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);   
  //display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0); 
  display.println("   SEPTIK OG DUSJ ");

  display.setCursor(0, 17); 
  display.print("Septiktank:   ");
  display.print(sensorTankLevel);
  display.print("%");

  display.setCursor(0, 30); 
  display.print("Under sump:   ");
  display.print(sensorShowerSump);

  display.setCursor(0, 43);
  display.print("Under septik: ");
  display.print(sensorBlackWater);
    
  display.display();
}

void transmitData(){
  //sensorTankLevel
  //sensorBlackWater
  //sensorShowerSump
  
  //Serial.write("Septiktank: " + sensorTankLevel);
  //Serial.write("Septiklekkasje: " + sensorBlackWater);
  //Serial.write("Dusjlekkasje: " + sensorShowerSump);
  //Serial.println("Septiktank: " + sensorTankLevel);
  //Serial.println("Septiklekkasje: " + sensorBlackWater);
  //Serial.println("Dusjlekkasje: " + sensorShowerSump);

  Serial.print(sensorTankLevel);
  Serial.print(";");
  Serial.print(sensorBlackWater);
  Serial.print(";");
  Serial.print(sensorShowerSump);
  Serial.println(";");
  
/*
  Serial.print("Septiktank: ");
  Serial.println(sensorTankLevel);
  Serial.print("Septiklekkasje: ");
  Serial.println(sensorBlackWater);
  Serial.print("Dusjlekkasje: ");
  Serial.println(sensorShowerSump);
  Serial.println("------");
*/
  //usbSerialComm.println("Septiktank: " + sensorTankLevel);
  //usbSerialComm.println("Septiklekkasje: " + sensorBlackWater);
  //usbSerialComm.println("Dusjlekkasje: " + sensorShowerSump);
}
