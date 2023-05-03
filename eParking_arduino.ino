// Importing the Software serial and the HCSR04 libraries (there is a need to add these libraries) 
#include <SoftwareSerial.h>
#include <HCSR04.h>

// Importing the Keypad library 
#include <Keypad.h>

// Defining the kind of keypad which is 4X3 keypad and the keys on the keypad 
const byte ROWS = 4; 
const byte COLS = 3; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// The pins in which the keypad is connected to of the Arduino Mega
byte rowPins[ROWS] = {8, 7, 6, 5}; 
byte colPins[COLS] = {4, 3, 2}; 

// Function that we use to setup the keypad we get it from the library it maps the keys so that we can use them
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

//Started SoftwareSerial at new RX (10) and new TX (9) pin of Arduino Mega to talk to NodeMCU via serial communication
SoftwareSerial newSerial(10,9);

HCSR04 p1Sonic(22, 23); //initialisation class HCSR04 (trig pin , echo pin), setting the pins for sensor at parking 1
HCSR04 p3Sonic(28, 29); //initialisation class HCSR04 (trig pin , echo pin), setting the pins for sensor at parking 3
HCSR04 p2Sonic(34, 35); //initialisation class HCSR04 (trig pin , echo pin), setting the pins for sensor at parking 2
HCSR04 p4Sonic(40, 41); //initialisation class HCSR04 (trig pin , echo pin), setting the pins for sensor at parking 4
HCSR04 p6Sonic(46, 47); //initialisation class HCSR04 (trig pin , echo pin), setting the pins for sensor at parking 6
HCSR04 p5Sonic(50, 51); //initialisation class HCSR04 (trig pin , echo pin), setting the pins for sensor at parking 5


// Declaring array to hold all parking lot IDS 
String parkingLots[4]; 

// Declaring string to hold the parking lot ID which has been chosen from the keypad 
String selectedParkingLot =  "";

// Declaring string to hold value of parking as T or F based on the occupancy of the parking spots 
String p1Dist;
String p2Dist;
String p3Dist;
String p4Dist;
String p5Dist;
String p6Dist;

unsigned long previousMillis = 0;  // will store last time we went inside the if condition to send the data to the NodeMCU
// Note: As soon as the data is sent to the NodeMCU it will send the data to the server if connected to the server

// constants won't change:
const long interval = 1000;  // interval at which data is sent to the cloud (milliseconds)

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // setting the board rate of serial communication to 115200
  newSerial.begin(115200); // setting the board rate of software serial communication to 115200 (rate at which it will talk to NodeMCU)
  // Assigning values to each of the four array elements of parkingLots as the ID of each parking lot 
  parkingLots[0] = "DggU5M3HtESO4PLVSGTz"; // parkingLots[0] is set as value "DggU5M3HtESO4PLVSGTz" which is the idea for Ithra 
  parkingLots[1] = "gLqJBzLLQe4QSYC3o4Eo"; // parkingLots[1] is set as value "gLqJBzLLQe4QSYC3o4Eo" which is the idea for PMU 
  parkingLots[2] = "sT2Ypq3Y1iRYl58dANq6"; // parkingLots[2] is set as value "sT2Ypq3Y1iRYl58dANq6" which is the idea for Othaim Mall 
  parkingLots[3] = "uB1h1TETpqTENmKTNS0b"; // parkingLots[3] is set as value "uB1h1TETpqTENmKTNS0b" which is the idea for Mall of Mall Of Dhahran 

  // By default the parking lot chosen is Ithra 
  selectedParkingLot = parkingLots [0];
}

void loop() {

  // We check if the distance sensed by the ultrasonic sensor at parking P1 is greater than 10. If that is true it means there is no car hence p1Dist = "F" 
  // else there is a car and the value of P1Dist = "T" 
  // The same logic is applied for all the six parking spots
  
  if (p1Sonic.dist() > 10){
    p1Dist = "F";
  }else {
    p1Dist = "T";
  }

  if (p2Sonic.dist() >10){
    p2Dist = "F";
  }else {
    p2Dist = "T";
  }

  if (p3Sonic.dist() > 10){
    p3Dist = "F";
  }else {
    p3Dist = "T";
  }

  if (p4Sonic.dist() > 10){
    p4Dist = "F";
  }else {
    p4Dist = "T";
  }

  if (p5Sonic.dist() > 10){
    p5Dist = "F";
  }else {
    p5Dist = "T";
  }

if (p6Sonic.dist() > 10){
    p6Dist = "F";
  }else {
    p6Dist = "T";
  }

  // We create a new string with parking lot ID (which changes based on the button pressed on the keypad) and the status of the 6 parking lots
  String myString = selectedParkingLot + ", " + p1Dist + ", " + p2Dist + ", " + p3Dist + ", " + p4Dist + ", " + p5Dist + ", " + p6Dist;
  Serial.println(myString); // The created string is printed for our reference in serial monitor

  // We use this chucnk of code in order to get the value pressed on the keypad
  char customKey = customKeypad.getKey();
  // We check if a key is pressed 
  if (customKey){
    // if  a key is pressed on the keypad we print in the serial to see which keypad was pressed
    Serial.println(customKey);
  // If 1 is pressed then we set the parking lot as Ithra and send data to the NodeMCU which then sends it to cloud
    if (customKey == '1'){
      selectedParkingLot = parkingLots[0]; // set the parking lot ID as Ithra ID and then we create a new string in the next line
      String myString = selectedParkingLot + ", " + p1Dist + ", " + p2Dist + ", " + p3Dist + ", " + p4Dist + ", " + p5Dist + ", " + p6Dist;
      // We make a char buffer to send a string over software serial 
      char* buf = (char*) malloc(sizeof(char)*myString.length()+1);
      myString.toCharArray(buf, myString.length()+1); // The string we created is converted to a array of char
      newSerial.write(buf); // it is sent to the NodeMCU
      Serial.println(buf); // for our reference we print it in the serail of Arduino IDE 
      free(buf); // We clear the buffer (it is like cleaning the buffer so we can free the memory)
    }
    // Same logic repeated if 2,3 or 4 is pressed for PMU, Othaim mall or Mall of Dhahran
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

  // This is the logic we use to autoamitically send data to NodeMCU every 1 seconds as we have set interval = 1000 (the line at the start just above void setup())
  unsigned long currentMillis = millis(); // This function is used to return the number of milliseconds at the time, the Arduino board begins running the current program
  if (currentMillis - previousMillis >= interval) {
    // save the we entered the if condition to previousMillis which was initally set to 0
    previousMillis = currentMillis;

    // This is the same logic we have used in the keypad to make the string of the name myString, create a char array to store the string.
    String myString = selectedParkingLot + ", " + p1Dist + ", " + p2Dist + ", " + p3Dist + ", " + p4Dist + ", " + p5Dist + ", " + p6Dist;
    char* buf = (char*) malloc(sizeof(char)*myString.length()+1);
    // String is converted into an array of char
    myString.toCharArray(buf, myString.length()+1);
    Serial.println(buf); // We print this in the serila
    newSerial.write(buf); // We send the data to NodeMCU
    free(buf); // The memory is freed
  }

}
