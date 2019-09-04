# IEEE_IOT_TECHWEEK
Required codes and instructions.
STEPS TO SETUP ARDUINO IDE FOR NODEMCU
1.	 Open IDE and go to File -> Prefrences.
2.	In the “Additional Board Manager URLs” coloumn enter the link http://arduino.esp8266.com/stable/package_esp8266com_index.json
3.	Click OK.
4.	Now go to Tools -> Board -> Boards Manager.
5.	In the search bar enter “esp8266”.
6.	Click on the result and click install.
7.	After it is installed click OK.
8.	Go to Tools -> Boards. Scroll down and click on “NodeMCU 1.0 (ESP 12E Module)”.
9.	The IDE is ready to go with the NodeMCU module.

STEPS TO INSTALL ADAFRUIT MQTT LIBRARY
1.	Go to the link 
https://github.com/adafruit/Adafruit_MQTT_Library
2.	Click on Download -> Download Zip.
3.	In the arduino IDE click on Sketch -> Include Library -> Add .zip Library.
4.	Select the zip file of the Adafruit MQTT library and click OPEN.
5.	The library is installed.

	STEPS TO SETUP YOUR ADAFRUIT CLOUD:
1.	Go to io.adafruit.com 
2.	Sign up for a new account.
3.	Click on feeds.
4.	Go to actions -> create new feed.
5.	Name your feed “onoff”.
6.	Click on Create.

STEPS TO UPLOAD THE CODE TO NODEMCU :
1.	 Download and open the code “voice_controlled_smart_led.ino”.
2.	In the code that opens replace "...your SSID..." with your wifi SSID (wifi name) and "...your password..." with your password.
3.	Replace "...your AIO username (see https://accounts.adafruit.com)..." with your Adafruit Cloud username and "...your AIO key..." with AIO key.
4.	Click on Upload. It will take a few minutes.
5.	After the code is successfully uploaded you will see Hard reset via RTS pin.


