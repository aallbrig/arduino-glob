// Motion Sensor
const int motionSensor = 2;
volatile boolean rfidHasBeenRead = false;

// LCD screen
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// RFID
volatile boolean motionSense = false;
#include <SoftwareSerial.h>
#define rxPin      3  // RFID SOUT
#define txPin      11  // RFID SIN
#define BUFSIZE    12  // Size of receive buffer (in bytes) for incoming data from the RFID R/W Module (this should be adjusted to be larger than the expected response)
// RFID R/W Module Commands
// Number of bytes returned in ()
#define RFID_Read         0x01	  // Read data from specified address, valid locations 1 to 33 (5)
#define RFID_Write	  0x02	  // Write data to specified address, valid locations 3 to 31 (1)
#define RFID_Login	  0x03	  // Login to tag with password (1)
#define RFID_SetPass      0x04	  // Change tag's password from old to new (1)
#define RFID_Protect	  0x05	  // Enable/disable password protection (1)
#define RFID_Reset        0x06	  // Reset tag (1)
#define RFID_ReadLegacy   0x0F	  // Read unique ID from EM4102 read-only tag (for backwards compatibility with Parallax RFID Card Reader #28140) (12)
// Memory map/address locations for EM4x50 tag
// Each address holds/returns a 32-bit (4 byte) value
#define ADDR_Password     0	  // Password (not readable)
#define ADDR_Protect	  1	  // Protection Word
#define ADDR_Control	  2	  // Control Word
// ADDR 3-31 are User EEPROM area
#define ADDR_Serial	  32	  // Device Serial Number
#define ADDR_DeviceID	  33	  // Device Identification
// Status/error return codes
#define ERR_OK		  0x01	  // No errors
#define ERR_LIW		  0x02	  // Did not find a listen window
#define ERR_NAK		  0x03	  // Received a NAK, could be invalid command
#define ERR_NAK_OLDPW	  0x04	  // Received a NAK sending old password (RFID_SetPass), could be incorrect password
#define ERR_NAK_NEWPW	  0x05	  // Received a NAK sending new password (RFID_SetPass)
#define ERR_LIW_NEWPW	  0x06	  // Did not find a listen window after setting new password (RFID_SetPass)
#define ERR_PARITY	  0x07	  // Parity error when reading data
// For use with RFID_ReadLegacy command
#define LEGACY_StartByte  0x0A
#define LEGACY_StopByte   0x0D


// set up a new serial port
SoftwareSerial rfidSerial =  SoftwareSerial(rxPin, txPin);


void setup(){
  // RFID
  // define pin modes
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  // setup Arduino Serial Monitor
  Serial.begin(9600);
  while (!Serial);   // wait until ready
  Serial.println("\n\nParallax RFID Read/Write Module");
  // set the baud rate for the SoftwareSerial port
  rfidSerial.begin(9600);
  Serial.flush();   // wait for all bytes to be transmitted to the Serial Monitor
//  attachInterrupt(1, onRfidRead, CHANGE);
  
  // Motion Sensor
  attachInterrupt(0, onMotionInterrupt, RISING);

  // Define LCD Display
  lcd.begin(16, 2);
  lcd.write("Begin");
  // any one-time tests
  /*testLcdDisplay();*/
}

void loop(){
//  delay(500); // 5 seconds
//  Serial.println("Start of loop!");
//  int value = digitalRead(motionSensor);
//  int x;
//  if (value == HIGH) {
//    Serial.println("onMotionSense()");
//  } else {
////    Serial.println("onIdle()");
//  }
//  delay(300);
//  if (Serial.available()) {
//    x = Serial.read();
//    Serial.println(x);
//    lcd.write(x);
//  }
//  char idx;
  if(motionSense){
    lcd.clear();
    lcd.print("Interrupt detected");
    delay(1000);
    lcd.clear();
    motionSense = false;
  }
//  if(rfidHasBeenRead){
//    lcd.clear();
//    lcd.print("RFID read");
//    delay(1000);
//    lcd.clear();
//    rfidHasBeenRead = false;
//  }
  uint8_t rfidData[BUFSIZE];  // Buffer for incoming data
  Serial.print("Reading tag's unique serial number lol...");
  while (rfidRead(rfidData, ADDR_Serial) != 0);
  String x = ReturnHex(rfidData, 4);   // The rfidData string should now contain the tag's serial number, so display it on the Serial Monitor
  lcd.clear();
  lcd.print(x);
  if(x == "023adf39"){
    lcd.setCursor(0,1);
    lcd.write("Card!");
  } else if(x == "02609b34"){
    lcd.setCursor(0,1);
    lcd.write("Circle!"); 
  }
  Serial.println();
  Serial.flush();
}

/*** SUPPORTING FUNCTIONS ***/

void onMotionInterrupt() {
  motionSense = true;
}

void onRfidRead() {
  rfidHasBeenRead = true;
}

char rfidRead(uint8_t *data, uint8_t address) {
  char offset;  // offset into buffer
  
  rfidFlush();  // empties any buffered incoming serial data
  
  rfidSerial.print("!RW");       // header
  rfidSerial.write(RFID_Read);   // command
  rfidSerial.write(address);     // address
    
  while (rfidSerial.available() != 5);  // wait until data is received from RFID module
  
  if (rfidSerial.read() == ERR_OK)  // if our status byte is OK
  {
    for (offset = 0; offset < 4; offset++)
      data[offset] = rfidSerial.read();  // get the remaining data
       
    return 0; // return good
  }
  
  return -1; // return error
}

char rfidReadLegacy(uint8_t *data) {
  char offset;  // offset into buffer
  
  rfidFlush();  // empties any buffered incoming serial data
  
  rfidSerial.print("!RW");             // header
  rfidSerial.write(RFID_ReadLegacy);   // command
    
  while (rfidSerial.available() != 12);  // wait until data is received from RFID module
  
  if (rfidSerial.read() == LEGACY_StartByte)  // if our start byte is OK
  {
    for (offset = 0; offset < 10; offset++)
      data[offset] = rfidSerial.read();  // get the remaining data
       
    data[offset] = 0;  // null terminate the string of bytes we just received   
    return 0; // return good
  }
  
  return -1; // return error
}


void rfidFlush() {
    while (rfidSerial.available() > 0)
      rfidSerial.read();
}

String ReturnHex(uint8_t *data, uint8_t length) {
  char tmp[length*2+1];
  byte first ;
  int j=0;
  for (uint8_t i=0; i<length; i++) 
  {
    first = (data[i] >> 4) | 48;
    if (first > 57) tmp[j] = first + (byte)39;
    else tmp[j] = first ;
    j++;

    first = (data[i] & 0x0F) | 48;
    if (first > 57) tmp[j] = first + (byte)39; 
    else tmp[j] = first;
    j++;
  }
  tmp[length*2] = 0;
  return tmp;
}
