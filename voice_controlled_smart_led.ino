#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "steins gate"
#define WLAN_PASS       "keshav.99"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "keshav31"
#define AIO_KEY         "0d95795afac84e328aa8f99ba09fdd4a"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");

/*************************** Sketch Code ************************************/

void MQTT_connect();
int LED = 13;
void setup() {
  Serial.begin(115200);//Begins Serial communication with Computer
  delay(10);
  pinMode(LED, OUTPUT); //Set our LED pin to output mode

  Serial.println("Adafruit MQTT demo");

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS); //Connecting Nodemcu to the internet
  while (WiFi.status() != WL_CONNECTED) { //try to connect untill connected
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());//Displays the IP address assigned to your NodeMCU in the connected network

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);
}

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;  //Creates an object for the class 
  while ((subscription = mqtt.readSubscription(5000))) { //reads the data from our feed wait for 5000 milliseconds for the data.
    if (subscription == &onoffbutton) { //Checks wether the data recieved is from our required feed or not
      Serial.print("Got: ");
      Serial.println((char *)onoffbutton.lastread); // .lastread stores the last message from the feed which in our case would either be ON or OFF
      if(!strcmp((char *)onoffbutton.lastread , "ON"))
      {
        digitalWrite(LED, HIGH);  //if the data recieved is ON, then the digital pin gives HIGH output i.e 3.3V and our led glows.
      }
      else
        digitalWrite(LED, LOW);  //if the data recieved is OFF, then the digital pin gives LOW output i.e 0V
      
    }
  }


}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
