/********************************************************************/
// First we include the libraries
#include <OneWire.h>  //for DS18B20 Sensor
#include <DallasTemperature.h>  //for DS18B20 Sensor
#include "DHT.h"  //for DHT11 Sensor
#include <DHT.h>  //for DHT11 Sensor
#include <Arduino.h>
#include <ESP8266WiFi.h>  //for ESP8266 Module
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <Hash.h>
#include <Adafruit_Sensor.h>
/********************************************************************/
/********************************************************************/
//we define our data pins for both of the sensors and 
#define ONE_WIRE_BUS 4   //Data pin for DS18B20 temperature Sensor on pin 4
OneWire oneWire(ONE_WIRE_BUS);  // Setup a oneWire instance to communicate with any OneWire devices  
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature. 
float temperature = 0 ;

#define DHTPIN 2  //Data pin for DHT11 Sensor (Humidity) on pin 2 
#define DHTTYPE DHT11  //Define our DHT sensor type
DHT dht(DHTPIN, DHTTYPE);  //function to detect the type and pin of DHT sensor

String toJSON(float, float);  //declaration of function called toJSON
int postValues(String json);  //declaration of function called postValues
 
String user_network_name; 
String user_password; 
String restURL = "http://192.168.43.116:8000/measures"; //
char* serial_tochar(int choose_data);

char* networkname;
char* password;
char* data[]={"user","pass"};
const char* network_name="sasa";   //here we enter our network name
//const char* password="sasagamed";    //here we enter our password for that network
/********************************************************************/ 
/********************************************************************/ 
/********************************************************************/ 
void setup() {
  Serial.begin(115200);  //initialize the Serial Monitor for debugging purposes
  dht.begin();        //Initialize the DHT sensor
  delay(1000);
  sensors.begin(); 
  delay(1000);
  connect_to_network();  //function shows the networks then takes ssid and password and connects to the network
}
/********************************************************************/ 
/********************************************************************/ 
/********************************************************************/ 
void loop() {
  //get humidity readings from DHT11 Sensor
  delay(2000);  // Wait a few seconds between measurements.
  float humidity = dht.readHumidity();  // Reading humidity takes about 250 milliseconds
  Serial.print(F(" Humidity: "));
  Serial.print(humidity);
  
  //get temperature readings from DS18B20 Sensor
  delay(2000);  // Wait a few seconds between measurements.
  sensors.requestTemperatures(); // Send the command to get temperature readings
  float temperature = sensors.getTempCByIndex(0); // Why "byIndex"? because You can have more than one DS18B20 on the same bus, 0 refers to the first IC on the wire  
  Serial.print("Temperature is: "); 
  Serial.print(temperature); //printing tempearture readings on serial monitor 
  delay(1000); 

  
  String temp_json = toJSON(temperature, "temp"); 
   String hum_json = toJSON(humidity, "hum");  
  int httpCode = postValues(temp_json);   
  
      if (httpCode == 201) 
        {
         Serial.print("POSTED: ");
         Serial.println(temp_json);
         delay(1000);
        } 
      else 
        {
         Serial.print("Fail. HTTP ");
         Serial.println(httpCode);
         Serial.println(WiFi.status());
        } 
          httpCode = postValues(hum_json);   
  
      if (httpCode == 201) 
        {
         Serial.print("POSTED: ");
         Serial.println(hum_json);
         delay(1000);
        } 
      else 
        {
         Serial.print("Fail. HTTP ");
         Serial.println(httpCode);
         Serial.println(WiFi.status());
        } 


} //end of void loop
/********************************************************************/
/********************************************************************/

//function that scans for the networks around your device and displays it  
void connect_to_network(){
  WiFi.disconnect();
  WiFi.scanNetworks();
  Serial.print("Scan start ... ");
  int n = WiFi.scanNetworks();
  if ( n > 0 ) 
     {
        Serial.print(n);
        Serial.println(" network(s) found");
        for (int i = 0; i < n; i++)
           {
             Serial.println(WiFi.SSID(i));
           }
        Serial.println();
      }

  networkname = strtok(getname(0), " ");
password = strtok(getname(1), " ");
  
  WiFi.begin(networkname,password);  //takes the ssid and password to connect
  delay(1000);
  Serial.print("Connected, IP address: ");
  Serial.println(network_name);
  Serial.println(password);
  Serial.println(WiFi.localIP());
}

/********************************************************************/
/********************************************************************/
//convert the readings to JSON object
String toJSON(float value,String type) {
     return String("{\"measure\": ") + value + ", \"measure_type\": " + "\"" + type +"\""+ "}";
} 

/********************************************************************/
/********************************************************************/
//sends the data to the server
int postValues(String json) {
      WiFiClient ourClient;
      HTTPClient http; //Declare object of class HTTPClient
      Serial.print(restURL);
      http.begin(ourClient,restURL); //Specify request destination
//http.begin("0.0.0.0",3000,"/measures");
      http.addHeader("Content-Type", "application/json"); //Specify content-type header
//http.addHeader("Accept", "application/json");
      Serial.print(json);
      int httpCode = http.POST(json); //Send the request
      String payload = http.getString(); //Get the response payload
      Serial.print(payload);
      return httpCode;
}
char* getname(int choose_data) {
    while(Serial.available()==0) { }
    String str =Serial.readString();
    str.toCharArray(data[choose_data], str.length());
    return data[choose_data];
}



// WiFi.mode(WIFI_STA); 1st line after void connect_to_network

// Serial.print("HTTP Response: "); //Print HTTP return code
// Serial.print(httpCode);
// Serial.println(payload); //Print request response payload
 

//   while (WiFi.status() != WL_CONNECTED)
//  {
  
//    Serial.print("Please enter a valid network name and password...\n");
//  Serial.println("please enter network name");
//  while (Serial.available() == 0)   
//   {}
//   user_network_name = Serial.readString();
// Serial.println("The network name you have entered is");
//  Serial.println(user_network_name);
// 
//   Serial.println("please enter network password");
//  while (Serial.available() == 0)   
//   {}
//   user_password = Serial.readString();
//  Serial.println("The password you have entered is:");
//  Serial.println(user_password);
