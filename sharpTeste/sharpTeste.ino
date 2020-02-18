#include <analogWrite.h>
#define sharpF 12
#define sharpE 14
#define sharpD 13
  
void setup() {
  pinMode(sharpF, INPUT);
  pinMode(sharpE, INPUT);
  pinMode(sharpD, INPUT);
  Serial.begin(9600);
}
int media10(int i){
    int media=0;
    for(int a=0;a<1000;a++){
        media+=analogRead(i);
    }
    return media/1000;
}
 
void loop() {
  Serial.print(media10(13));
  Serial.print(" ");
  Serial.print(media10(12));
  Serial.print(" ");
  Serial.println(media10(14));
  delay(500);
}
