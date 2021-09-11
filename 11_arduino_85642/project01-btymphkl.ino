#include <TM1637.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 48
#define CS_PIN 46

MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int LDR = 42;
int LDR_LED = 6;
int PIR = 40;
int PIR_LED = 7;
int SPEAKER = 44;
int frequency = 50;
int CLK = 36;
int DIO = 38;

TM1637 tm(CLK,DIO);

void setup() {
  tm.init();
  tm.set(2);
  Serial.begin(9600);
  myDisplay.begin();
  myDisplay.setIntensity(0);
  myDisplay.displayClear();
  myDisplay.displayScroll("Hello", PA_CENTER, PA_SCROLL_LEFT, 100);  
  pinMode(LDR,INPUT);
  pinMode(LDR_LED,OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(PIR_LED, OUTPUT);
  pinMode(PEAKER, OUTPUT); 
}

void loop() {
  tm.display(0,1);
  tm.display(1,2);
  tm.point(1);
  tm.display(2,10);
  tm.display(3,11);
  displayNumber(1234);
  if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
  }
  ldr();
  pir();
}

void ldr(){
  int State=digitalRead(LDR);      
  Serial.println("Intensity="); 
  Serial.println(State);         
  delay(300);
  if(State==HIGH){              
  digitalWrite(LDR_LED,HIGH);        
  }
  else{
  digitalWrite(LDR_LED,LOW);  
  } 
}

void pir(){
  if(digitalRead(PIR)==HIGH)  {
      Serial.println("Somebody is here.");
      digitalWrite(PIR_LED, HIGH);
      speaker();
    }
    else  {
      Serial.println("Nobody.");
      digitalWrite(PIR_LED, LOW);
    }
}

void speaker(){
    frequency += 100;      
    if (frequency > 8000)
    {
        noTone(SPEAKER);
        frequency = 50;
    }
    tone(SPEAKER, freq);
    delay(100);
}

void displayNumber(int num){   
    tm.display(3, num % 10);   
    tm.display(2, num / 10 % 10);   
    tm.display(1, num / 100 % 10);   
    tm.display(0, num / 1000 % 10);
}
