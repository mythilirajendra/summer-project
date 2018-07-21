#define BLYNK_PRINT Serial

#define trigPin 2
#define echoPin 0 
long duration;
int distance;
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "cc219974325f4f3fbcc55ba222e341a0";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xyz";
char pass[] = "12345678";
int flag=0;

void notifyOnSomeoneAtUrDoor()
{
  
  if (distance<25 && flag==0) {
    Serial.println("Someone at the door");

    
    //   We allow 1 notification per 15 seconds for now.
    Blynk.notify("Alert : Someone is at the door");
    flag=1;
  }
  else if(distance>=25){
     
  
    flag=0;
  }
  
 
}

void setup()
{

   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  // Debug console
  Serial.begin(9600);

Blynk.begin(auth, ssid, pass);
  // Setup notification button on pin D1
  pinMode(D1,INPUT_PULLUP);
 timer.setInterval(16000L,notifyOnSomeoneAtUrDoor);
 
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
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
