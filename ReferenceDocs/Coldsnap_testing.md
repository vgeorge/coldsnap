## How to benchtest the Coldsnap for basic functionality.

The testing procedure suggests putting the probes into cold water to set their temperature to known values. Immersing them in water assumes that you have assembled probes that are sufficiently waterproof that this will not damage them. Since the probes are likely to spend much time in damp or wet conditions, good construction and waterproofing should be done; please see the probe construction notes, or use your own knowledge and judgement as guidance in assembling your probes.

Required:
* 1 cup water at about 50F
* 1 cup (insulated cup is good) with several ice cubes and a little water (32F)
* 1 ice pack for a "below freezing" reference (FINS sensor testing)

## Procedure

Plug in the 12V power supply and plug it into the Coldsnap power connector. If the cover of the unit is open so the Arduino board is visible, there should be one or 2 LEDs visible. The LED in the center of the board near the pins of the programming header is the "Power" LED to show the unit has power. There is another LED on the Arduino board that is located in the corner away from the programming header pins; this LED is put on when the Heater drive is active and will be referred to as the "Heater LED".

If the Coldsnap unit and all the probes are at a room temperature above 65F the heater should not feel warm to the touch. Why? The heater would not ordinarily be required at this temperature since the AC (set to coldest temp) should cool fine by itself at this temperature without the heating function.

If the ROOM sensor is placed in a glass with cool water (60F or below) the heater should start feeling warm after a few seconds and the Heater LED in the corner of the Arduino board should be lit to show the heater drive.

Now lift the ROOM probe from the water and warm it between your fingers - the heater LED should go off after a few seconds and the heater will stop heating - it may be warm when it first turns off, but the heat will diminish over time if it has shut off. 

Note that when the heater shuts off it will remain off for 3 minutes before the program retests the temperature and (possibly) turns the heating back ON. This is true in all of the steps below when the HEATER turns OFF (3 min HOLDOFF).

If the ROOM sensor is placed back in the COOL water (about 55F is good) the heating LED and HEATER should come again turn ON. (continue)

If a number of ice cubes are put in the cup of water and stirred so that the water falls below the SETPOINT (42F), the Heater LED should go off as will the heater drive (3 min HOLDOFF), allowing the heater unit to cool - which would allow the AC probe to cool and turn off the compressor.... 

If the ROOM sensor is placed in cool water (55F) the HEATER should come on (within 3 min, or else unplug the power connector and replug it to restart the Arduino program and break out of the 3 min time delay loop. One can also push the RESET button on the Arduino board...). With the heater active and warm, place the FINS sensor in an insulated cup with a little water and several ice cubes. If this water reaches 32F the heater should turn OFF (3 min HOLDOFF). This holdoff delay in response to the FINS sensor at freezing is the protection to allow the coils to defrost. NOTE! The threshold for this sensor is set for 32F and it is possible that the water/ice may not sufficiently cool the FINS probe to trigger the heater shutdown since the water/ice mix will only reach 32F and not below. Putting the FINS probe inside a freezer compartment or with an ice pack should definitely trigger the heater to be shut down.

If the FINS probe is removed from the freezing temps and the ROOM sensor is in a cool temperature, the heater LED and Heater should come ON within 3 min from the time the FINS probe exceeds freezing.

That is it for basic control testing!