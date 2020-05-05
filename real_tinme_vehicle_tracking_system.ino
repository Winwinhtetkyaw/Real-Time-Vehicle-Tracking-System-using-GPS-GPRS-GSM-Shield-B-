#include<SoftwareSerial.h>
#include<TinyGPS.h>

float gpslat,gpslon;
TinyGPS gps;
SoftwareSerial mySerial(2,3);

void setup() {
   mySerial.begin(9600);
  Serial.begin(9600);

  delay(2000);
   mySerial.println("AT");   
  delay(200);
  //Send message
  mySerial.println("AT+CGNSPWR=1");
  delay(200);
  //reset GPS in autonomy mode
  mySerial.println("AT+CGNSTST=1");
  delay(200);
}

void loop() {
  while (mySerial.available())
  {
    int c = mySerial.read();
    if (gps.encode(c))
    {
      gps.f_get_position(&gpslat, &gpslon);
        Serial.print("Latitude:");
        Serial.println(gpslat,6);
        Serial.print("Longitude:");
        Serial.println(gpslon,6);
        Serial.println("################");

        Send_Message();
    }

    
}
}

void Send_Message(void)//send message 
{
   mySerial.println("AT");   
  delay(500);
  //Send message
  mySerial.println("AT+CMGF=1");
  delay(500);
  mySerial.println("AT+CMGS=\"09123456789\"");//Change the receiver phone number
  delay(500);
        mySerial.print("Latitude:");
        mySerial.println(gpslat,6);
        mySerial.print("Longitude:");
        mySerial.println(gpslon,6);
        mySerial.println("################");//the message you want to send
        mySerial.print("https://www.google.com/maps/?q=");
        mySerial.print(gpslat, 6);
        mySerial.print(",");
        mySerial.print(gpslon, 6);
        delay(60000);
        mySerial.write(26); 
}
