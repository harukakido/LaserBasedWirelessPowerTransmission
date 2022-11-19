//Program variables
int exampleVariable = 0;
int sensorPin = A5;

//Serial data variables
//Incoming Serial Data Array
const byte kNumberOfChannelsFromExcel = 3; 

//Comma delimiter to separate consecutive data if using more than 1 sensor
const char kDelimiter = ',';    
// Interval between serial writes
const int kSerialInterval = 50;   
//Timestamp to track serial interval
unsigned long serialPreviousTime; 

char* arr[kNumberOfChannelsFromExcel];

//SETUP
void setup() {
  //Initialize Serial Communication
  Serial.begin(9600);  
}

//START OF MAIN LOOP
void loop()
{
  //Gather and process sensor data
  processSensors();

  //Read Excel variables from serial port (Data Streamer)
  processIncomingSerial();

  //Process and send data to Excel via serial port (Data Streamer)
  processOutgoingSerial();

//Compares STR1 to STR2 returns 0 if true.
//   if ( strcmp ("Apple", arr[0]) == 0){ 
//       Serial.println("working");
//   }
}

//SENSOR INPUT CODE
void processSensors() 
{
  //Read sensor pin and store to a variable
  exampleVariable = analogRead(sensorPin);
  
  // Add any additional raw data analysis below (e.g. unit conversions)
}

//Add any specialized methods and processing code below

//OUTGOING SERIAL DATA PROCESSING CODE
void sendDataToSerial()
{
  //Send data out separated by a comma (kDelimiter)
  //Repeat next 2 lines of code for each variable sent:

  Serial.print(exampleVariable);
  Serial.print(kDelimiter);
  Serial.println(); //Add final line ending character only once
}

//DO NOT EDIT ANYTHING BELOW THIS LINE

//OUTGOING SERIAL DATA PROCESSING CODE
void processOutgoingSerial()
{
   //Enter into this only when serial interval has elapsed
  if((millis() - serialPreviousTime) > kSerialInterval) 
  {
    //Reset serial interval timestamp
    serialPreviousTime = millis(); 
    sendDataToSerial(); 
  }
}

//INCOMING SERIAL DATA PROCESSING CODE
void processIncomingSerial()
{
  if(Serial.available()){
    parseData(GetSerialData());
  }
}

//Gathers bytes from serial port to build inputString
char* GetSerialData()
{
  static char inputString[64];                     //Create a char array to store incoming data
  memset(inputString, 0, sizeof(inputString));     //Clear the memory from a pervious reading
  while (Serial.available()){
    Serial.readBytesUntil('\n', inputString, 64);  //Read every byte in Serial buffer until line end or 64 bytes
  }
  return inputString;
}

//Separate the data at each delimeter
void parseData(char data[])
{
    char *token = strtok(data, ",");    //Find the first delimeter and return the token before it
    int index = 0;                      //Index to track storage in the array
    while (token != NULL){              //Char* strings terminate w/ a Null character. We'll keep running the command until we hit it
      arr[index] = token;               //Assign the token to an array
      token = strtok(NULL, ",");        //Conintue to the next delimeter
      index++; //incremenet index to store next value
    }
}
