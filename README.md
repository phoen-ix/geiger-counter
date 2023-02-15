# **ngnt-geiger-counter**
This project uses a RadiationD v1.1 cajoe and gives it additional functionality and a simple casing that holds everything together.  
![preview of an assembled device](https://user-images.githubusercontent.com/100175489/219118323-df211fda-93e7-4437-bd8e-3e14d5e2e7f8.jpg)


#### **Things needed:**  
1x assembled RadiationD v1.1 Cajoe (for example look for "diy geiger" on the bay)  
1x LCD2004 Display with i2c (I recommend to buy a display that already has the i2c interface soldered onto)  
1x Wemos D1 R2  
3d printed front- & back-plate https://www.printables.com/model/399474-ngnt-geiger-counter-not-great-not-terrible  
7x M-F dupont cables  

screws:  
8x M3x8mm  
4x M3x12mm  
4x M3 spacer (at least 35mm or more if you don't want to bend some of the dupont cables)  
4x M3 screws fitting the spacer  
12x M3 nuts  

#### **HowTo**  
- print the front and backplate  
- mount the Wemos to the backplate (4x M3x8mm & nuts)  
- mount the LCD to the front plate (4x M3x12mm & nuts)  
- remove the 4 screws on the RadiationD that hold the acryl, mount everything to the front plate (4x M3x8mm)  

- Connect Dupont-cables:  

###### **LCD -> Wemos D1 R2**  
GND -> GND  
VCC -> 3.3V  
SDA -> SDA/D2  
SCL -> SCL/D1  


###### **RadiationD Cajoe V1.1 -> Wemos D1 R2**  
GND -> GND  
5V  -> 5V  
VIN -> D6(GPIO12)  


- use M3 spacer, screws and nuts to mount the front plate on the back plate  
- Flash Wemos D1 R2  



#### **ToBeDone**  
- create a new frontplate with fitting for two switches, one that controls the backlight of the lcd and one that can switch off the speaker (I recommend if you assemble the RadiationD to leave out the speaker for now)
- create network capability & save data; open to suggestions but my current plan is to create an mqtt broker that saves the cpm in a database (all dockerized)
<br><br><br><br>

**Additional; I asked ChatGPT to simply explain what the arduino code does:**  
This code is used to create a Geiger counter with a display that shows counts per minute (CPM) and microsieverts per hour (uSv/h). The Geiger counter uses a Geiger-Müller tube that detects ionizing radiation such as alpha and beta particles, gamma rays and X-rays. The code uses interrupts to count the impulses generated by the Geiger counter tube, and calculates the CPM and uSv/h based on the counts.

The code uses the Wire.h and LiquidCrystal_I2C.h libraries to interface with a 20x4 LCD display. The LCD display shows the CPM, the uSv/h, and a countdown timer that starts at 1 minute and counts down to 0. When the countdown reaches 0, the CPM and uSv/h values are reset, and the countdown starts again.

The code starts by defining several constants and variables. The ONE_MINUTE constant is set to 60000 milliseconds (1 minute), and the COUNTDOWN_SECONDS constant is set to 60 seconds. The cpm_constant is set to 0.0057, and the geiger_pin is set to pin 12.

The impulse_counter variable is used to count the impulses generated by the Geiger counter tube, and the previousMillis variable is used to track the time when the CPM and uSv/h values were last updated. The countdownMillis variable is used to track the time remaining in the countdown, and the countdownFinished variable is used to indicate when the countdown has reached 0.

The setup() function is used to initialize the Geiger counter and the LCD display. The impulse_counter is set to 0, the geiger_pin is set as an input, and an interrupt is attached to the pin using the attachInterrupt() function. The LCD display is initialized using the lcd.init() function, the backlight is turned on using the lcd.backlight() function, and the display is cleared using the lcd.clear() function. The countdownMillis variable is set to the current time plus ONE_MINUTE.

The loop() function is used to update the LCD display and the Geiger counter values. The currentMillis variable is set to the current time using the millis() function. If the countdown has not finished, the remainingSeconds variable is calculated as the difference between countdownMillis and currentMillis, divided by 1000. If the remainingSeconds is less than 0, it is set to 0. The remainingSeconds value is then formatted into a string using the sprintf() function, and displayed on the LCD display using the lcd.setCursor() and lcd.print() functions. If the remainingSeconds is 0, the countdownFinished variable is set to true.

The Geiger counter values are updated once per minute using the if statement that checks if the difference between currentMillis and previousMillis is greater than ONE_MINUTE. The impulse_counter value is formatted into a string using the sprintf() function, and displayed on the LCD display using the lcd.setCursor() and lcd.print() functions. The uSv/h value is calculated by multiplying the impulse_counter value by the cpm_constant, and is displayed on the LCD display with four decimal places.

Finally, the countdownFinished variable is set to false, the countdownMillis variable is reset to the current time plus ONE_MINUTE, and the impulse_counter variable is set to 0. This starts the countdown again and resets the Geiger counter values.


