#include <DS3231.h>

DS3231  rtc(SDA, SCL);


Time  t;

int relay = 7;

const int OnHour = 17;
int OnMin = 30;
int OffHour = 22;
int OffMin = 0;


void setup() {
// The following lines can be uncommented to set the date and time
  //rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(17, 43, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(25, 11, 2023);   // Set the date to January 1st, 2014
  
  // put your setup code here, to run once:
  Serial.begin(115200);
  rtc.begin();
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

}

void loop() {
   t = rtc.getTime();
      
   if(t.date == 24 || t.date == 31) {
    OnMin = 0;
    OffHour = 3;
   }
   else if(t.hour > 3) {
    OnMin = 30;
    OffHour = 22;
    OffMin = 0;
   }

  if(t.hour >= OffHour && t.min >= OffMin) {
    digitalWrite(relay, LOW);
    Serial.print("Off");
   } 
   else if(t.hour >= OnHour) {
    if(t.hour == OnHour && t.min >= OnMin) {
      digitalWrite(relay, HIGH);
      Serial.print("On");
    }
    else if(t.hour > OnHour && t.hour < OffHour) {
     digitalWrite(relay, HIGH);
     Serial.print("On");
    }  
   } 
  
   Serial.print(OffMin);
   Serial.println(rtc.getTimeStr());
   delay(1000);
}
