const int trigPin = 2;  //D4
const int echoPin = 0;  //D3

// define the variables
long duration;
int distance;

#include <ESP8266WiFi.h>
 
String apiKey = "CH8A7HCSO31YI0IF";     

const char *ssid =  "Speedbroadband 9885557436";     // your wi-fi name
const char *pass =  "mythili210600";                 
const char* server = "api.thingspeak.com";           //assign server value for future reference


WiFiClient client;
 
void setup() 
{
       pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
       Serial.begin(115200);
       delay(10);
       
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  
      digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(2000);
      
      
              if (isnan(distance)) 
                 {
                     Serial.println("Failed to read from the sensor!");
                      return;
                 }

                         if (client.connect(server,80))   //   server is already declared as api.thingspeak.com above
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(distance);
                             
                             
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Distance: ");
                             Serial.print(distance);
                             
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(10000);
}

