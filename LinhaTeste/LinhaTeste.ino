#include <analogWrite.h>
#define lineE 2
#define lineD 4
  
void setup() {
  pinMode(lineE, INPUT);
  pinMode(lineD, INPUT);
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
  Serial.print(media10(lineE));
  Serial.print(" ");
  Serial.println(media10(lineD));
  delay(500);
}
