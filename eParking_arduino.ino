#include <SoftwareSerial.h>
#include <HCSR04.h>

#include <Keypad.h>
const byte ROWS = 4; 
const byte COLS = 3; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {8, 7, 6, 5}; 
byte colPins[COLS] = {4, 3, 2}; 
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//Started SoftwareSerial at new RX (10) and new TX (9) pin of ESP8266/NodeMCU
SoftwareSerial newSerial(10,9);

HCSR04 p1Sonic(22, 23); //initialisation class HCSR04 (trig pin , echo pin)
HCSR04 p3Sonic(28, 29); //initialisation class HCSR04 (trig pin , echo pin)
HCSR04 p2Sonic(34, 35); //initialisation class HCSR04 (trig pin , echo pin)
HCSR04 p4Sonic(40, 41); //initialisation class HCSR04 (trig pin , echo pin)
HCSR04 p6Sonic(46, 47); //initialisation class HCSR04 (trig pin , echo pin)
HCSR04 p5Sonic(50, 51); //initialisation class HCSR04 (trig pin , echo pin)



String parkingLots[4]; 
String selectedParkingLot =  "";

String p1Dist;
String p2Dist;
String p3Dist;
String p4Dist;
String p5Dist;
String p6Dist;

unsigned long previousMillis = 0;  // will store last time LED was updated

// constants won't change:
const long interval = 1000;  // interval at which data is sent to the cloud (milliseconds)


int sensorPin = A0; // select the input pin for LDR

int sensorValue = 0; // variable to store the value coming from the sensor

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  newSerial.begin(115200);
  parkingLots[0] = "DggU5M3HtESO4PLVSGTz";
  parkingLots[1] = "gLqJBzLLQe4QSYC3o4Eo"; 
  parkingLots[2] = "sT2Ypq3Y1iRYl58dANq6";
  parkingLots[3] = "uB1h1TETpqTENmKTNS0b";
  selectedParkingLot = parkingLots [0];
}

void loop() {

//  sensorValue = analogRead(sensorPin); // read the value from the sensor
//  Serial.println(sensorValue); //prints the values coming from the sensor on the screen
  
  // put your main code here, to run repeatedly:
//  buttonState1 = digitalRead(buttonPin1); 
//  buttonState2 = digitalRead(buttonPin2);
//  buttonState3 = digitalRead(buttonPin3);
//  buttonState4 = digitalRead(buttonPin4);

  // We will send a command to show it in the admin pannel... on the left side.
//  if (buttonState1 == HIGH) {
//    Serial.println( "B1 Pressed"); 
//    selectedParkingLot = parkingLots[0];
//  }
//  if (buttonState2 == HIGH) {
//    Serial.println( "B2 Pressed"); 
//    selectedParkingLot = parkingLots[1];
//  }
//  if (buttonState3 == HIGH) {
//    Serial.println( "B3 Pressed"); 
//    selectedParkingLot = parkingLots[2];
//  }
//  if (buttonState4 == HIGH) {
//    Serial.println( "B4 Pressed");
//    selectedParkingLot = parkingLots[3]; 
//  }

//  Serial.println( "Selected Parking Lot"); 
//  Serial.println(selectedParkingLot); 

  if (p1Sonic.dist() > 10){
    p1Dist = "F";
  }else {
    p1Dist = "T";
  }
//  delay (80);

  if (p2Sonic.dist() >10){
    p2Dist = "F";
  }else {
    p2Dist = "T";
  }
//  delay (80);

  if (p3Sonic.dist() > 10){
    p3Dist = "F";
  }else {
    p3Dist = "T";
  }
//  delay (80);

  if (p4Sonic.dist() > 10){
    p4Dist = "F";
  }else {
    p4Dist = "T";
  }
//  delay (80);

  if (p5Sonic.dist() > 10){
    p5Dist = "F";
  }else {
    p5Dist = "T";
  }
//  delay (80);

if (p6Sonic.dist() > 10){
    p6Dist = "F";
  }else {
    p6Dist = "T";
  }

  String myString = selectedParkingLot + ", " + p1Dist + ", " + p2Dist + ", " + p3Dist + ", " + p4Dist + ", " + p5Dist + ", " + p6Dist;
  Serial.println(myString);
//Serial.println("Hello There");
//Serial.println(p1Sonic.dist());

  char customKey = customKeypad.getKey();
  if (customKey){
    Serial.println(customKey);
    if (customKey == '1'){
      selectedParkingLot = parkingLots[0];
      String myString = selectedParkingLot + ", " + p1Dist + ", " + p2Dist + ", " + p3Dist + ", " + p4Dist + ", " + p5Dist + ", " + p6Dist;
      char* buf = (char*) malloc(sizeof(char)*myString.length()+1);
      myString.toCharArray(buf, myString.length()+1);
      newSerial.write(buf);
      Serial.println(buf);
      free(buf);
    }
    if (customKey == '2'){
      selectedParkingLot = parkingLots[1];
      String myString = selectedParkingLot + ", " + p1Dist + ", " + p2Dist + ", " + p3Dist + ", " + p4Dist + ", " + p5Dist + ", " + p6Dist;
      char* buf = (char*) malloc(sizeof(char)*myString.length()+1);
      myString.toCharArray(buf, myString.length()+1);
      newSerial.write(buf);
      Serial.println(buf);
      free(buf);
    }
    if (customKey == '3'){
      selectedParkingLot = parkingLots[2];
      String myString = selectedParkingLot + ", " + p1Dist + ", " + p2Dist + ", " + p3Dist + ", " + p4Dist + ", " + p5Dist + ", " + p6Dist;
      char* buf = (char*) malloc(sizeof(char)*myString.length()+1);
      myString.toCharArray(buf, myString.length()+1);
      newSerial.write(buf);
      Serial.println(buf);
      free(buf);
    }
    if (customKey == '4'){
      selectedParkingLot = parkingLots[3];
      String myString = selectedParkingLot + ", " + p1Dist + ", " + p2Dist + ", " + p3Dist + ", " + p4Dist + ", " + p5Dist + ", " + p6Dist;
      char* buf = (char*) malloc(sizeof(char)*myString.length()+1);
      myString.toCharArray(buf, myString.length()+1);
      newSerial.write(buf);
      Serial.println(buf);
      free(buf);
    }
  }

//  delay(3000);
//  String myString_2 = selectedParkingLot + ", " + p1Dist + ", " + p2Dist + ", " + p3Dist + ", " + p4Dist + ", " + p5Dist + ", " + p6Dist;
//  char* buf = (char*) malloc(sizeof(char)*myString_2.length()+1);
//  myString_2.toCharArray(buf, myString_2.length()+1);
//  newSerial.write(buf);
//  Serial.println(buf);
//  free(buf);

//newSerial.write("Push this");
   
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    
    String myString = selectedParkingLot + ", " + p1Dist + ", " + p2Dist + ", " + p3Dist + ", " + p4Dist + ", " + p5Dist + ", " + p6Dist;
    char* buf = (char*) malloc(sizeof(char)*myString.length()+1);
    myString.toCharArray(buf, myString.length()+1);
    Serial.println(buf);
    newSerial.write(buf);
    free(buf);

  }

}
