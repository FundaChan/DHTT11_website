#include <ESP8266WiFi.h> 
#include <WiFiClient.h> 
#include <DHT.h>
#include <ThingSpeak.h> 

#define DHTPIN 0 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 

const char *ssid = "Moka"; 
const char *password = "tempetahu"; 
WiFiClient client; 

unsigned long myChannelNumber = 2022525; 
const char * myWriteAPIKey = "N74EOYM2DWDE6581"; 
uint8_t temperature, humidity; 

boolean data_state;

void setup() {
 Serial.begin(115200); 
 dht.begin(); 
 delay(10); 
 //menghubungkan ke wifi
 Serial.println(); 
 Serial.println(); 
 Serial.print("Connecting to "); 
 Serial.println(ssid); 
 WiFi.begin(ssid, password); 
 while (WiFi.status() != WL_CONNECTED) 
 {
 delay(500);
 Serial.print(".");
 }
Serial.println(""); 
 Serial.println("WiFi connected");
 Serial.println(WiFi.localIP());
 ThingSpeak.begin(client); //memulai thingspeak
}

void loop() 
{ 
 static boolean data= false; 
 temperature = dht.readTemperature(); //membaca suhu pada sensor DHT11
 humidity = dht.readHumidity(); //membaca kelembaban sensor DHT11
 Serial.print("Temperature Value is :"); 
 Serial.print(temperature); 
 Serial.println("C"); 
 Serial.print("Humidity Value is :"); 
 Serial.print(humidity); 
 Serial.println("%"); 
 if( data_state ) 
 {
 ThingSpeak.writeField(myChannelNumber, 1, temperature, myWriteAPIKey); 
 }
 else 
 { 
 ThingSpeak.writeField(myChannelNumber, 2, humidity, myWriteAPIKey); 
 data_state = true; 
 } 
 delay(1000); 
}
