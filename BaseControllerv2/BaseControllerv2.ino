#include <Time.h>
#include <Ethernet.h>
#include <SPI.h>
#include <VirtualWire.h>
//#include <IRremote.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; //I left the MAC address and IP address blank.
byte ip[] = {
  192,168,1,177 };                     // You will want to fill these in with your MAC and IP address.

EthernetServer server(80); // Assigning the port forwarded number. It's almost always 80.

String readString; // We will be using strings to keep track of things.

const int transmit_pin = 12;

//int LED1;
//int LED2;
//int LED3;
//float x;
//float r;
//float g;
//float b;
float temp;

boolean currentState = 255;//stroage for current button state
boolean lastState = 255;//storage for last button state
//
//IRsend irsend;


void setup()
{
    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_setup(100);       // Bits per sec
    
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    // start the Ethernet connection and the server:
    Ethernet.begin(mac, ip);
    Serial.println("Ethernet Begun");

}

byte count = 1;
int var = 0;

void loop(){
  EthernetClient client = server.available();
   if (client) {
    while (client.connected()) {
      if (client.available()) {   // This is all where we start up the server and strings.
        char c = client.read();                     
        if (readString.length() < 100) {
          readString += c;
        } 
        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          Serial.println(readString); // And here we begin including the HTML
          client.println();
          client.println(
            "<!DOCTYPE html PUBLIC '-//W3C//DTD HTML 4.01//EN'>"
            "<html>"
            "<head>"
            "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"
            "<title>"
            "Veda Home Automation"
            "</title>"
            "</head>"
            "<body bgcolor=black>"
            "<center>"
            "<font color=FFFFFF>"
            "RGB Test <input class='left' type='submit' value='Fade' onClick=window.location='/?stopblink\'><input class='right' type='submit' value='Flash' onClick=window.location='/?blink\'>"
            "<br>"
            "Function 2 <input class='left' type='submit' value='Off' onClick=window.location='/?port2off\'><input class='right' type='submit' value='On' onClick=window.location='/?port2on\'>"
            "<br>"
            "Bedroom Blinds <input class='left' type='submit' value='Close' onClick=window.location='/?port3off\'><input class='right' type='submit' value='Open' onClick=window.location='/?port3on\'>"
            "<br>"
            "Bedroom Light <input class='left' type='submit' value='Off' onClick=window.location='/?port4off\'><input class='right' type='submit' value='On' onClick=window.location='/?port4on\'>"
            "<br>"
//            "Bedroom Fan <input class='left' type='submit' value='Off' onClick=window.location='/?fanpower\'><input class='right' type='submit' value='SPEED' onClick=window.location='/?fanspeed\'>"
//            "<br>"
//);            
//            temp = analogRead(0);
//  temp = temp * 0.48828125;
//  client.println("TEMPRATURE = ");
//  client.println(temp);
//  client.println("*C");
//          client.println(

            "</font>"
            "</center>"
            "</body>"
            "</html>")
          ;
          

// RELAY ONE   
          if (readString.indexOf("?blink") > 0) {


            
            
            Serial.println("Blinking");
          }

          else {
            if (readString.indexOf("?stopblink") > 0) {
//              
//              for (int i=0; i<360; i++)
// {
//
////convert into a float to calculate r,g,b ( increase amplitute by multiplying by 127 and make positive by adding 1)
//
//   x=float(i);
//   r=17*(sin(x/180*PI)+1);
//   g=17*(sin(x/180*PI+3/2*PI)+1);
//   b=17*(sin(x/180*PI+0.5*PI)+1);
//   
////convert flaot r,g,b to integer and assisting values to LED
//    LED1= int(r);
//   LED2= int(g);
//   LED3= int(b);
//   
////write LED levels to p0, p1, p4 (ASSIGN PWM values to LEDs)
//    analogWrite (3,LED1);
//   analogWrite (5,LED2);
//   analogWrite (6,LED3);
// 
//}

            
            

              
              Serial.println("Stopping Blink");
            }
          }
          
////RELAY TWO          
          if (readString.indexOf("?port2on") > 0) {
            

            
            
            
            Serial.println("On");
          }

          else {
            if (readString.indexOf("?port2off") > 0) {

              
                       Serial.println("Off");
            }
          }
          
          ////404         
          if (readString.indexOf("?*") > 0) {
            

            
            
            Serial.println("On");
          }

          else {
            if (readString.indexOf("?*") > 0) {

              
              
                       Serial.println("Off");
            }
          }  
  
////RELAY THREE          
          if (readString.indexOf("?port3on") > 0) {

            
            Serial.println("On");
          }

          else {
            if (readString.indexOf("?port3off") > 0) {

              
              Serial.println("Off");
            }
          }

////RELAY FOUR      
          if (readString.indexOf("?port4off") > 0) {
                        
  char msg2[1] = {'1'};

  vw_send((uint8_t *)msg2, 1);
  vw_wait_tx(); // Wait until the whole message is gone

            
            
            Serial.println("Light Off");
          }

          else {
            if (readString.indexOf("?port4on") > 0) {

              
  
  char msg[1] = {'0'};

  vw_send((uint8_t *)msg, 1);
  vw_wait_tx(); // Wait until the whole message is gone

              
              Serial.println("Light On");
            }
          }

//**/
//
//
//////FANNNN
//          if (readString.indexOf("?fanpower") > 0) {
//            
//            
//              analogWrite(6, 0);
//  delay(90);
//    analogWrite(6, 255);
//    delay(90);
//      analogWrite(6, 0);
//  delay(90);
//    analogWrite(6, 255);
//    
//    
//irsend.sendNEC(0x807FE01F, 8);
//            
//            
//                        
//            Serial.println("Fan SPEED");
//          }
//
//          else {
//            if (readString.indexOf("?fanpower") > 0) {
//              
//                analogWrite(5, 0);
//  delay(90);
//    analogWrite(5, 255);
//        delay(90);
//      analogWrite(5, 0);
//  delay(90);
//    analogWrite(5, 255);
//              
//  
//irsend.sendNEC(0x807FC03F, 8);
//
//              
//              Serial.println("Fan Power");
//            }
//          }




          delay(1);

          readString="";
          client.stop();            // End of session.

        }
      }
    }
  }

}


