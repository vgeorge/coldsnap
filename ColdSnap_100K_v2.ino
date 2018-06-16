/*
  ColdSnap Coolbot Clone
  
*/
 const byte Debug = 1;   //since we don't have conditional compilation......
     // set to "0" to skip Serial output code of diagnostics.
 
 // pin defs
const int RoomSensor = A0;
const int FinSensor = A1;
const int PotSensor = A2;  // reads the potentiometer for setting a variable temperature
const int Heater = 11;  //digital pin 11 has PWM
const int led_pin = 13;
const int VariableJumper = 10; // digital pin 10; pulled H (no jumper) signals to use default SP
    // if pulled L, then read pot on A2 to set 39F to 59F setpoint instead.
    // Note: the potentiometer could be used for completely different uses! Could be used to 
    // set the Deadband - for instance.....  

// some key temp defs  (10-bit values from A/D)
const int Freezing = 244;  // 32F on FINS sensor
const int _2C = 262;   //36F
const int _4C = 280;   //39F
const int _5C = 289;  //41F
const int _6C = 298;  // 43F
const int _10C = 336; // 50F
const int _15C = 385; //59F
const int _17C = 405; //63F
const int _20C = 435;  //68F
const int _25C = 485; // 77F
const int SetPoint_default = _4C;  // 39F on ROOM sensor for this application
    
// other constants for users to set according to their needs.
const int Deadband = 21;     // 21 counts is approximately 5 degrees F
const unsigned long defrost_delay = 300000;  
const byte defaultHeater = 254;

//the variables
int RoomTemp;
int FinsTemp;
int VariableTemp;  // this is read from the potentiometer for setting adjustable temperature, etc..
int SetPoint;
int sensorValue;
byte heaterValue;
byte PWM;
byte ON;    //flag to indicate if AC should be cooling.


// the setup routine runs once at powerup, or when you press reset:
void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(Heater, OUTPUT);
  ON = 0;  //start with the Off condition
  // Enable the following if serial reporting is used for debugging.
  if (Debug) Serial.begin(9600);   // initialize serial communication at 9600 bits per second
  heaterValue = defaultHeater;  //someday maybe get value from potentiometer??
}

// the loop routine runs over and over again forever:
void loop() {
  
 ReadSensors(); // reads all sensors and stores the average values
 
 // figure out which SetPoint we are using.......
 if (digitalRead(VariableJumper)) {
     SetPoint = SetPoint_default;
 } 
 else {  //set SetPoint from the position of the Potentiometer, 35F to 55F range
     SetVariableSetPoint();
 }
     
  if ( (ON) && (RoomTemp <= _17C) && (RoomTemp > SetPoint) ) {
      HeaterSet(heaterValue);  // 75% power should be enough to keep the AC sensor warm with 100 ohm and 12Vunr
      digitalWrite(led_pin, HIGH);  //show the world it is driven
     }
     else {
     HeaterSet(0); //Heater is OFF - not needed - but ON indicates we should be cooling
     digitalWrite(led_pin, LOW); //turn off indicator LED
     }
     
     if ((RoomTemp <= SetPoint) || (FinsTemp <= Freezing)) {
         ON = 0;  //indicate to control loop we don't need AC cooling
         HeaterSet(0);  //and turn off the heater to accomplish this
         digitalWrite(led_pin, LOW);  //turn off indicator LED
     }
     
     if (FinsTemp <= Freezing) {
         if (Debug) Serial.println("Entering Defrost Cycle - see ya in about 5 min!");
         delay(defrost_delay);  //delay to defrost well
         // remember that "delay()" puts all code execution on hold until the delay times out!
         
          // This section extends the fixed defrost delay (if needed) until FINS reach 2C
         do {
             delay(10000);  // 10 sec per pass until 2C or above
             ReadSensors(); 
         }
         while (FinsTemp < _2C);  

     }
    
 
 // if NOT ON, see if it should be put ON
 // This is where the deadband control is implemented: must warm to "Deadband" above SetPoint
 if ((!ON) && ((RoomTemp >= (SetPoint + Deadband)) && (FinsTemp > _2C))) ON = 1;
   // the ON flag will be detected in the ON loop and heater will be put on there.....
 
//  Enable these if debugging and using serial output (since we don't have conditional compilation....)
// This section could also just be commented out to really leave it out of the compiled code...
if (Debug) {
    Serial.print("PWM = ");
    Serial.println(int(PWM));
    Serial.print("FinsTemp = ");
    Serial.println(int(FinsTemp));
    Serial.print("RoomTemp =  ");
    Serial.println(int(RoomTemp));
    Serial.print("VariableTemp = ");
    Serial.println(int(VariableTemp));
     if (digitalRead(VariableJumper)) {
     Serial.println("Using Default programmed SetPoint");
     } 
     else Serial.println("Using Variable SetPoint");
     Serial.print("SetPoint = ");
    Serial.println(int(SetPoint));
    if (ON) {
        Serial.println("State = ON");
    } 
    else {
        Serial.println("State = OFF");
    }
    Serial.println("-----------------"); 
}

  delay(5000);
  
} // the_end

// ======== Subroutines below ====================

// this scales the potentiometer reading to a 4C to 15C range..(39F to 59F)
void SetVariableSetPoint(void) {
    SetPoint = (((float)VariableTemp/(1024))*(_15C - _4C)) + _4C;
}

//=============================

// this sets/retains the heater value for restore after A/D readings....
void HeaterSet(byte myvalue) {
    analogWrite(Heater, myvalue);
    PWM = myvalue;  //save the current value each time it is set.
    return;
}

//=============================

void ReadSensors(void){
 // read the inputs averaging 5 readings for each
    
  // Shut off Heater PWM before analog readings and restore the value after readings
    //for noise reduction.. Previous value will be maintained in the variable "PWM"
  byte temp_value = PWM; //save 
  HeaterSet(0);  //shut it off for the measurements.
  delay(10);   //a brief delay before reading sensors.
  
  sensorValue =0;
  for (int count = 0; count < 5; count++) {
    sensorValue = sensorValue + analogRead(RoomSensor);
    delay(10);
  }
  RoomTemp = sensorValue/5;    // do the average and store

sensorValue =0;
  for (int count = 0; count < 5; count++) {
    sensorValue = sensorValue + analogRead(FinSensor);
    delay(10);
  }
  FinsTemp = sensorValue/5;    // do the average and store
  
sensorValue =0;
  for (int count = 0; count < 5; count++) {
    sensorValue = sensorValue + analogRead(PotSensor); //read potentiometer
    delay(10);
  }
  VariableTemp = sensorValue/5;    // do the average and store
  
  HeaterSet(temp_value);  // restores pwm value and PWM with previous value
}
