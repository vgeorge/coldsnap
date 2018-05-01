> This is a partial recovery of documentation writen by [Dale A. Callaham](https://people.umass.edu/~dac/) about a prototype of air conditioner temperature override controller called **ColdSnap**. The project seems to be discontinued and the original webpage is offline, but some parts are acessible via Wayback Machine and mirrored here for educational purposes.

* [ColdSnap at Internet Archive's Wayback Machine](https://web.archive.org/web/20160211232038/http://people.umass.edu:80/~dac/projects/ColdSnap/ColdSnap.html)

---


## The ColdSnap - a cool concept just got better!

Air Conditioner temperature override controller
Coldsnap prototype.

### Brief Description

The "ColdSnap" is a device which manipulates an ordinary window air conditioner to cool a room to temperatures below the design minimum - to a chosen temperature down to near freezing - using the same low-power non-connected control concept  as used in the commercial product "CoolBot" (http://www.storeitcold.com). Unlike the commercial Coolbot, the ColdSnap is an open source project that provides basic functionality and a code/controller framework that can be built inexpensively by Do-It-Yourselfers, and easily modified and extended beyond the current rudimentary prototype form. The ColdSnap is prototyped with an Arduino Pro Mini microcontroller board ($10 for authentic Arduino versions, or as cheap as $2.60 for clones on eBay; please buy authentic to support the Arduino project and ensure you get a top quality and fully conforming product) and a few easily available additional components for the sensors and "heater". Enough information and testing data and analysis is available to allow DIY builders to confidently launch their own projects from this design and information.

Since this controller provides the same essential functionality (Air Conditioner override) as the CoolBot (without display or temperature setting controls), all of the information about using a Coolbot in a coldroom setting also apply to this device - it is a stripped-down functional mimic. The essence of controlling an air-conditioner for refrigeration in this way is extremely simple: you sense the temperature of the evaporator fins and of the room. The controller drives the warming of the AirConditioner temperature probe as needed to keep the AC running and achieve the chosen Room Temperature, while holding off the warming of the probe to allow the AC temperature probe to cool (to the real room temperature) as needed to achieve the desired temperature setpoint but avoid coil icing. With the open source nature of this project users may be able to better adapt this controller to specific installation requirements.

While the Arduino Pro Mini is a very powerful microcontroller board, the design goal was to build a miminal device that would "just work"; to this end there is no digital display and no control to change the setpoint (yes, in Version 01 there is...) or other parameters; parameters are set in the program. With the inexpensive and commonly available components specified, the programming of the device should allow for a temperature within about 1C of the chosen temperature, and the program is easily changed for a different setpoint or other parameters as needed. It would be quite easy to incorporate displays and inputs to have essentially the same functionality as the Coolbot. The prototype code is very basic and easy to follow and would be easy to modify and extend to implement other features. Again, while this is a functional prototype that can be put into service, a key part of the existing project is to demonstrate how simply this control system is accomplished with some inexpensive and readily available electronic components and show how the system requirements were considered and components were chosen and tested to meet those requirements.

Finally, before starting this project I looked hard to find an open-source project implementing the control concept used in the CoolBot and did not find any (as of 20150430); I found a number of forum posts inquiring about such a project, and at least one a few years old stating the intention for a DIY clone, but that seemed to have never been done. Due to the utility of this method of using a window AC to provide inexpensive "cold room" cooling I am publishing this information in hopes that it may be useful to someone with DIY skills and greatly reduce the costs of such an installation, or at least stimulate some competition for Coolbot, and competition is always good for the consumer. I have nothing to sell.

The prototype is due to be installed and tested in June 2015 for an agricultural produce storage coldroom. This prototype works as expected in the basic functionality tests (link below) but some changes may be required when it goes live and those changes and any knowledge gained in that process will be updated here.

### A second prototype is out for field testing as well...

**UPDATE - 20150614** - This prototype is being run to cool a cellar beer cave in Pennsylvania and has been online for a couple of weeks as of the time I write this. This unit was programmed for 50F turn-off and 55F turn-on (50F setpoint and 5F deadband) to minimize AC compressor cycling (this setting is configurable by the user in the programming) and has been running for a couple of weeks with no icing of the coils, maintaining an average room temperature about 52F (thermometer in a glass of water). It worked straight out of the box, no adjustments were needed. The deadband idea was contributed by this user/tester - Thanks Seven! This version has the optional potentiometer to allow the room temperature setting to be tweeked without reprogramming.

**A missing image was here.**

### The ColdSnap Prototype (This page is being actively revised and updated.)


[Design and Prototype information](ReferenceDocs/Coldsnap_prototyping_information.md):  Images, construction notes, testing, design thoughts and component choices.

ColdSnap Parts List (pdf) **(missing)**

If ordering from Digi-key, note that they still accept mailed orders and if a mailed order is accompanied by a check then Digi-key pays the shipping. This is a great service for small orders. Since I haven't been able to find the mail-in form on their website since 2011, I'm putting a copy here that you can download and print.  Check part numbers on their website for correctness, price, and adequate stock so as to avoid unexpected backorders.  Digi-key mail-in Order Form.

### ColdSnap testing

The assembled and programmed ColdSnap can be tested as a "black box" for basic functionality with these instructions.

---

### Electronics Schematics for ColdSnap prototypes: 

ColdSnap     - the original prototype

ColdSnap_01    - the second prototype, with potentiometer + jumper to enable variable temperature setpoints

---

Arduino Code for ColdSanp

The following links are for zip files of the code folder that can be placed in the "Sketchbook" folder of Arduino. The schematic and some other info specific to the version is included in the folder archive. The ".ino" file is the Arduino source code; a jpg or png will be the schematic, and a ".dsn" file is a TinyCad design file used for the schematic.

ColdSnap  - Initial Prototype

ColdSnap_01  Coding improvements, design includes jumper and potentiometer for adjustable temperature feature; programmable deadband

For quick evaluation, here is the Arduino source code for the Coldsnap_01:

/*
ColdSnap_01

An Air-Conditioner Override Controller based on Arduino Pro Mini 328P

This version has significant re-coding, including these changes:
1) Deadband parameter. Cooling to setpoint, then OFF (no heater) until ROOM reaches SP+Deadband
2) Has potentiometer to set a temperature 39F-59F (0V to 5V, or 0 to 1023 counts); this temperature is
    used IF pin D10 is pulled L by the jumper being across the header. If jumper is OPEN then D10 will be
    H and the default "SetPoint_default" temperature is used instead.
3) Eliminated the probably unnecessary varying of heater power: On is 75% PWM (192)
4) There is a 5 min defrost period (no heater) if the FINS sensor reaches freezing.

This prototype version will be tested for a 50F coldroom application.

This project is intended to replicate the basic functions of the CoolBot, a commercial control device
which is used with a standard window air conditioner to trick the AC unit into cooling below it's
natural low limit (about 62F typically) and provide monitoring of the cooling fins to avoid freeze-up,
thus allowing the compressor to shut off if fin icing is detected. The "trick" of the control system is to
warm the AC unit's temperature sensor with a heater so it "thinks" that the room is still warm, tricking
it to continue cooling below it's natural low limit. Unlike the CoolBot, this version has no controls and
should require no settings to function properly; removing controls and displays will improve reliability
and reduce the cost of a unit. All of the basic guidance for selecting a window AC, installing, and
operations are the same as for the CoolBot.

This project will use 2 thermistors as sensors; Sensor_1 is the room temperature sensor, and Sensor_2
is the cooling fin sensor (for freeze detection). The thermistors used will be Murata NCP15XH103F03RC.
This is a 10k ohm (25C) 1% thermistor in chip form; it is tiny and inexpensive, and available from Digikey.
The builder of a ColdSnap using these thermistors will need to solder them to wires and provide
protection as needed (epoxy coat and heat shrink overwrap?); example assembly is given in the associated
documentation.  If other thermistors or commercial thermistor probes are used instead this code will need
to be modified by the user to suit their probes.

The "heater" will simply be a power resistor. On 12V nominal raw power (as designed) a 50 ohm resistor will
produce 3W of dissipated power. Since the heater will only be energized at <70F and a 3W-rated resistor
is designed to operate with 3W dissipation at this temperature, there should be no problem. A 100 ohm
resistor may be adequate for the heating and in this case only 1.5 W will be dissipated and this is
certainly within specifications of a 3W-rated resistor. See test results document for guidance - individual
installations could require different choices.

It is possible to incorporate a third temperature sensor which would be bundled with the heater resistor
and wrapped with the detached AC sensor; this sensor would provide feedback on the temperature of
the AC sensor and the heater could be modulated to tune the heating to the minimum required to
maintain the AC sensor at about 70F (to keep the compressor running), or hold the AC sensor at
about 55F (when the compressor has been allowed to cycle off) so the temperature of the AC sensor
is closer to the 62F trip point so it can respond more rapidly to the heating required for further cooling.
This heater feedback may not be needed. An effort will be made to tune the heating power to
avoid the need for this additional sensor in most cases: not implemented in the prototype!

The control algorithm is simple: If the room temperature (RT) is above about 62F the AC should just simply
cool by itself. If the RT is 65F or below, apply power to the heater (warms the AC sensor) so the AC will
continue cooling below it's natural low-limit. If the fin sensor is found to be at 32F (continuously monitored)
then stop heater power to allow the compressor to cycle off making sure icing will not take place.
When the fin temperature is 35F or above, and if RT is above 35F, apply power to the heater again.

Thermistor used: Murata NCP15XH103F03RC 10k ±1% (chip thermistor 1.0mm x 0.5mm)

```
 This example code is in the public domain.

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
const int Freezing = 432;  // 32F on FINS sensor
const int _2C = 454;   //36F
const int _4C = 475;   //39F
const int _5C = 486;  //41F
const int _6C = 496;  // 43F
const int _10C = 538; // 50F
const int _15C = 589; //59F
const int _20C = 636;  //68F
const int _25C = 680; // 77F
const int SetPoint_default = -5C;  // 41F on ROOM sensor for this application
    
// other constants for users to set according to their needs.
const int Deadband = 31;     // 31 counts is approximately 5 degrees F
const unsigned long defrost_delay = 300000;  
const byte defaultHeater = 128;

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
     
  if ( (ON) && (RoomTemp <= _20C) && (RoomTemp > SetPoint) ) {
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
```