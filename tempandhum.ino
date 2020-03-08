#include<DHT.h>
#include <ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

#define DHTTYPE DHT11   // DHT 11
const int DHTPin=D3;
DHT dht(DHTPin, DHTTYPE);

const char* ssid="abcd";
const char* password="123456789";

void setup() {
  Serial.begin(115200);
  
  
  dht.begin();
   delay(100);
 
  pinMode(DHTPin, INPUT);
              

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
}

void loop() {
  delay(1000);

if (WiFi.status () ==WL_CONNECTED)
{
  HTTPClient http;
  float h =dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  Serial.print("temperature =");
  Serial.print(t);
  Serial.print("C ");
  Serial.print("humidity = ");
  Serial.print(h);
  Serial.println("");
 
    String url = "http://dhairya.eu-gb.mybluemix.net";
    String api = "/data";
    url += api;
    String param1 = "?temp=" + String(t);
    url += param1;
    String param2 = "&hum=" + String(h);
    url += param2;
    Serial.print("HTTP GET : ");
    Serial.println(url);

    http.begin(url);                              //Specify request destination

    int httpCode = http.GET();                    //Send the request

    if (httpCode > 0) {                           //Check the returning code
      String payload = http.getString();          //Get the request response payload
      Serial.println(payload);                    //Print the response payload
    }

    http.end();   //Close connection
  }

  delay(10000);    //Send a request every 30 seconds

}
