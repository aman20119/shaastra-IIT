#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
const char* ssid = "Redmi 69";
const char* password = "12345678";
//SoftwareSerial ESPserial(D2,D3);

WiFiClient client;
unsigned long myChannelNumber =  982309;
const char * myWriteAPIKey = "X5A90DBZP3SO7NW0";
String MakerIFTTT_Key ;
;String MakerIFTTT_Event;
char *append_str(char *here, String s) {  int i=0; while (*here++ = s[i]){i++;};return here-1;}
char *append_ul(char *here, unsigned long u) { char buf[20]; return append_str(here, ultoa(u, buf, 10));}
char post_rqst[256];char *p;char *content_length_here;char *json_start;int compi;

 
void setup() {
   // pinMode(D2,INPUT);
  //pinMode(D3,OUTPUT);

Serial.begin(115200);
//ESPserial.begin(115200);
delay(10);
 // setup_wifi();
   Firebase.begin("health-care-456ee.firebaseio.com","n0BkhKo5kEAM40ti82KOVQLPbeidWy23no9Q4Oms"); 

WiFi.begin(ssid, password);
// Connect to WiFi network
ThingSpeak.begin(client);

}
int time1=0;
int y=(analogRead(A0)/50 + 50);
void loop() {

Serial.println();
delay(1000);
//if ( ESPserial.available() ){  
 //Serial.write( analogRead(A0) );}
  Firebase.push("pulse/time",time1);
  Firebase.push("pulse/slot_1",y);
  time1++;
  ThingSpeak.writeField(myChannelNumber, 1,y, myWriteAPIKey);
  Serial.println(analogRead(A0));

delay(100);
if(analogRead(A0)>700){
  
  if (client.connect("maker.ifttt.com",80)) {
    MakerIFTTT_Key ="cyk3RcqmJ4FUjC3jMfJ7ba";
    MakerIFTTT_Event ="msg";
    p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");
    content_length_here = p;
    p = append_str(p, "NN\r\n");
    p = append_str(p, "\r\n");
    json_start = p;
    p = append_str(p, "{\"value1\":\"");
    p = append_str(p, "9234449737");
    p = append_str(p, "\",\"value2\":\"");
    p = append_str(p, "PULSE RATE IS HIGH");
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, "");
    p = append_str(p, "\"}");
    Serial.println("PULSE RATE IS HIGH");

    compi= strlen(json_start);
    content_length_here[0] = '0' + (compi/10);
    content_length_here[1] = '0' + (compi%10);
    client.print(post_rqst);
    delay(10000);
  
  }

  }
  else if(analogRead(A0)<300){
  
     if (client.connect("maker.ifttt.com",80)) {
    MakerIFTTT_Key ="cyk3RcqmJ4FUjC3jMfJ7ba";
    MakerIFTTT_Event ="msg";
    p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");
    content_length_here = p;
    p = append_str(p, "NN\r\n");
    p = append_str(p, "\r\n");
    json_start = p;
    p = append_str(p, "{\"value1\":\"");
    p = append_str(p, "9234449737");
    p = append_str(p, "\",\"value2\":\"");
    p = append_str(p, "PULSE RATE IS LOW");
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, "");
    p = append_str(p, "\"}");
    Serial.println("PULSE RATE IS LOW");

    compi= strlen(json_start);
    content_length_here[0] = '0' + (compi/10);
    content_length_here[1] = '0' + (compi%10);
    client.print(post_rqst);
    delay(10000);
  
  }
    }
    else{
      Serial.println("PULSE RATE IS NORMAL.");
  
      }

  
  
  }
