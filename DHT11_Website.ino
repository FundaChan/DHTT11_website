#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <WiFiClient.h>


#define DHTPIN 2 //d4
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE); 
uint8_t suhu, kelembapan; 

//variabel wifi
const char* ssid ="wifi_nyasar";
const char* pass ="#joeChan4";
WiFiClient client; 

// siapkan variabel host/server yang menampung database
const char*host = "192.168.43.122";

void setup() {
  Serial.begin(115200);//mulai serial monitor pada 9600baud
  dht.begin();//memulai sensordht11
  //menghubungkan ke wifi
 Serial.println(); 
 Serial.println(); 
 Serial.print("Connecting to "); 
 Serial.println(ssid); 
 WiFi.begin(ssid, pass); 
 while (WiFi.status() != WL_CONNECTED) 
 {
 delay(500);
 Serial.print(".");
 }
Serial.println(""); 
 Serial.println("WiFi connected");
 Serial.println(WiFi.localIP());
}

void loop() {
 
 suhu = dht.readTemperature(); //membaca suhu pada sensor DHT11
 kelembapan = dht.readHumidity(); //membaca kelembaban sensor DHT11
 //tampilkan di serial monitor
 Serial.print("Temperature Value is :"); 
 Serial.print(suhu); 
 Serial.println("C"); 
 Serial.print("Humidity Value is :"); 
 Serial.print(kelembapan); 
 Serial.println("%"); 

 // kirim data ke server
 const int httpPort = 80;
 if( !client.connect(host, httpPort)){
  Serial.println("connection gagal");
  return;
 }

 //kirim data ke tb_sensor
 String Link;
 HTTPClient http;

 Link = "http://" + String(host) + "/multisensor/kirimdata.php?suhu="+ String(suhu) + "&kelembapan=" + String(kelembapan); 
 // eksekusi alamat link
 http.begin(client, Link);
 http.GET();

 //baca respon setelah berhasil kirim nilai sensor
 String respon = http.getString();
 Serial.println(respon);
 http.end();
 
 delay(3000);
}
