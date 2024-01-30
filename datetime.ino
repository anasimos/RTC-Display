// C++ code
//
#include <ThreeWire.h>  //importing the three wire module
#include <RtcDS1302.h>

ThreeWire myWire(14,15,16); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

char a = 2;
char b = 3;
char c = 4;
char d = 5;
char e = 6;
char f = 7;
char g = 8;
//define pins for 7 segment seven pins
char digit1 = 13;
char digit2 = 12;
char digit3 = 11;
char digit4 = 10;
char digit22 = 22;
char digit24 = 24;
// define 7 pins for the common control of each digit

char Num[10]={
	
  0b1111110, //0
  0b0110000, //1
  0b1101101, //2
  0b1111001, //3
  0b0110011, //4
  0b1011011, //5
  0b1011111, //6
  0b1110000, //7
  0b1111111, //8
  0b1111011, //9
  
};

int min=0;
int hr=0;
int dy=0;
int lap=0;

void display(int n){      //displying requested number
  
  digitalWrite(a, Num[n] & 0b1000000);
  digitalWrite(b, Num[n] & 0b0100000);
  digitalWrite(c, Num[n] & 0b0010000);
  digitalWrite(d, Num[n] & 0b0001000);
  digitalWrite(e, Num[n] & 0b0000100);
  digitalWrite(f, Num[n] & 0b0000010);
  digitalWrite(g, Num[n] & 0b0000001);
  
}
void offdisplay(){ //turng off all digits
	
  digitalWrite(digit1, 1);
  digitalWrite(digit2, 1);
  digitalWrite(digit3, 1);
  digitalWrite(digit4, 1);
	
}
void digitdisp (int mins, int hrs,int dys){ // it takes min hour and date t display it on 7 segment
  int n4=(hrs%100)/10; 
  int n3=(hrs%10);
  int n2=(mins%100)/10;
  int n1=(mins%10);
  int n22=(dys%100)/10;
  int n24=(dys%10);
  
  offdisplay();
  display(n4);
  digitalWrite(digit4, 0);
  delay(2.5);
  
  offdisplay();
  display(n3);
  digitalWrite(digit3, 0);
  delay(2.5);
  
  offdisplay();
  display(n2);
  digitalWrite(digit2, 0);
  delay(2.5);
  
  offdisplay();
  display(n1);
  digitalWrite(digit1, 0);
  delay(2.5);

  offdisplay();
  display(n22);
  digitalWrite(digit22, 0);
  delay(2.5);
  
  offdisplay();
  display(n4);
  digitalWrite(digit24, 0);
  delay(2.5);

}

void setup()
{
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  Serial.begin(9600);

  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  Rtc.Begin();

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Serial.println();

  if (!Rtc.IsDateTimeValid()) 
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

  if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

  if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled) {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
  else if (now > compiled) {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
  else if (now == compiled) {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }
  
}

void loop()
{

  RtcDateTime now = Rtc.GetDateTime();
  min=int(now.Minute());
  hr=int(now.Hour());
  dy=int(now.Day());
  // min=88;
  // hr=88;
  // dy=88;
  digitdisp(min,hr,dy);
  
  
  // if (lap==6000) {
  // 	lap=0;
  //   if (min == 59){
  //     	min=0;
  //     if ( hr == 12){
  //     	hr=1;
  //     }
  //     else{
  //       hr++;
  //     }
  //   }
  //   else{
  //   	min++;
  //   }
  // }
  // else{
  //   lap++;} 
  
  
}