#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h> https://github.com/blynkkk/blynk-library
#include <ESP8266WiFi.h>
#include <SimpleTimer.h> https://github.com/jfturcot/SimpleTimer

//WiFi Setup 
char ssid[]="your_ssid";
char pswd[]="your_ssid_password";

//Blynk Setup
char auth[]="blynk_authentication_key_from_email";
SimpleTimer timer;

//Sensor Setup
const int vSensor=13; //D7
int sData =0; //Sensor store in this variable
long measurement;
String vData="";

void myTimerEvent(){
  Blynk.virtualWrite(V1,millis()/1000);
}

void setup() {
  Serial.begin(115200);
  pinMode(vSensor, INPUT);
  Blynk.begin(auth,ssid,pswd);
  
  //Setup function to be called every second
  timer.setInterval(10L,sensorValue);
}

void loop(){
  Blynk.run();
  timer.run();
}

void sensorValue(){
  measurement = TP_init();
  Serial.println(measurement);
  if(measurement > 1000){
    //This notify used for email notification if you set it 
    //Blynk.notify("Vibration Detected value: "+measurement+", Machine need to restart");
    //vData = vData+"Vibration: "+measurement;
    Blynk.virtualWrite(V2,measurement);
    //vData="";
  }
  else{
    Blynk.virtualWrite(V2,measurement);//Will reset to 0 if no vibration detected
  }
  delay(3000);
}

long TP_init(){
  long measurement = pulseIn(vSensor,HIGH);
  return measurement;
}
