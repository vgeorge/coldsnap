## Coldsnap Prototyping Information

The 20k resistors used with the thermistor input circuits are 0.01% precision, surplus/salvage. It is very nice to have such precise resistors since it eliminates the need for calibration in this application, but readily available 0.1% resistors should provide very predictable performance.

With my prototype unit in test mode (with serial connection for data reporting, no 12V supply connection! - powered by the programming interface (FTDI Basic")) and both Room and Fins probes at room temperature 61F the readings on the 2 probes was 599 and 600 (10-bit counts) so the thermistors and A/D are providing very closely matched readings; there is a 9 count change per 1C at this temperature and the calculated table reading for 16C is 598. It is possible that your assembly may give different values. In that case, you can calibrate by placing the ROOM probe and FINS probes in the required temperatures (42F for ROOM (typically), and 32F for FINS (always), and noting the A/D values reported by the serial output for these readings and then substituting those as your values in the Arduino program:

```
[From the Coldsnap.ino sketch]
// critical temp defs  (10-bit values from A/D)
const int _25C = 680;
const int SetPoint = 492;  // 42C on ROOM sensor
const int Freezing = 432;  // 0C on FINS sensor
```

After any changes to the Arduino "sketch" you need to verify the code and upload to your Arduino board. (But, if you are still reading this, I bet you knew that already! ;-)

=============================================

The heater resistor is a 100-ohm 3W Ohmite Series 23 resistor; it gets quite hot to the touch at 100% power (1.44W); also at 75% power (controlled by PWM drive). The resistor is rated at 3W at 25C in still air, linearly derated to 0W dissipated power at 350C (the maximum rated temperature). The resistor is small - 0.515"L x 0.212"dia. In order to spread the heat over a larger area the resistor was wrapped in a 3 x 10 cm piece of aluminum foil that was compressed flat and tightly to the resistor; since aluminum is a good conductor this will spread the heat to more evenly and gently heat the air conditioner probe. But enclosing the resistor may make the resistor itself hotter than in open air, so a measurement was made with a 32ga thermocouple wire wrapped into the aluminum overwrap right against the resistor. With the assembly at 16C room temperature, after the 1 minute turn-on interval at 100% power, the resistor temperature was 65C. The power to the heater then drops to 75% (analogWrite value 192 in the program) and the temperature continued warming: 70C with one additional minute, 72C at 3 minutes, 76C at 5 minutes, 79C at 10 minutes. With linear derating from 3W at 25C to 0W at 350C, this is 325C span and 100%, or 3.25C/%. For the 80C temperature, 80C/3.25C = 24.6% derating. 75% of 3W is 2.25W rating (thermally derated); At 100% power (12V and 100% duty factor) the resistor is only dissipating 1.44W, so operation at even 100% continuous power in this configuration (wrapped, ambient at/below 25C) is well within the resistor rating and should have a long reliable life.

=============================================

Cooling and Moisture...

An air conditioner must chill the coils to cool the air. Cold coils may be below the dew point of the room air and thus condensation will occur on the coils. It requires energy to cool the moist air and condense the water. As the room air becomes colder the difference between the air and evaporator (cooling) coils is less and the coils can fall below the freezing point and begin to ice up. While it is possible to monitor the coils for freezing and force a defrost cycle, it is better to limit the moisture in the cold room air and thus reduce both the work required to cool the air and reduce the chance of freeze-up. One solution is to minimize the moisture getting into the air in the room by compartmentalizing the environment around the transpiring vegetables - cover them; the vegetables will stay more turgid and the AC has less work to do.

======================================================