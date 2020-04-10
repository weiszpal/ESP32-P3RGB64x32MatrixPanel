#include <WiFi.h>

#include <Adafruit_GFX.h>
#include "P3RGB64x32MatrixPanel.h"
#include <Fonts/FreeSansBold9pt7b.h>

// constructor with default pin wiring
P3RGB64x32MatrixPanel matrix;

// use this constructor for custom pin wiring instead of the default above
// these pins are an example, you may modify this according to your needs
//P3RGB64x32MatrixPanel matrix(25, 26, 27, 21, 22, 23, 15, 32, 33, 12, 16, 17, 18);

char ssid[] = "SSID-of-your-wifi";
char pass[] = "********";

WiFiServer wifiServer(23);

void setup() {
  
  WiFi.begin(ssid, pass);
  pinMode(LED_BUILTIN, OUTPUT);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(700);
  }
  
  wifiServer.begin();

  matrix.begin();
  matrix.setTextWrap(false);
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
    ESP.restart();

  WiFiClient client = wifiServer.available();

  if (client) {

    char buffer[3][11] = {0};
    
    while (client.connected()) {
      
      if(client.available()>0){
        
        int i = 0;
        
        while (client.available()>0) {
          buffer[i/10][i%10] = client.read();        
          i++;
          if(i>33)
            i = 33;
        }

        buffer[0][9] = 0;
        buffer[1][10] = 0;
        buffer[2][10] = 0;
    
        matrix.fillScreen(0);
    
        matrix.setTextColor(matrix.color444(15, 2, 0));
        matrix.setFont();
        matrix.setCursor(5, 2);
        matrix.printf(buffer[0]);
    
        matrix.setTextColor(matrix.color444(15, 8, 0));
        matrix.setCursor(2, 11);
        matrix.printf(buffer[1]);
                     
        matrix.setTextColor(matrix.color444(10, 12, 6));
        matrix.setCursor(2, 22);
        matrix.printf(buffer[2]);
      
        matrix.swapBuffer();
      }
      delay(10);
    }

    client.stop();
  }
}
