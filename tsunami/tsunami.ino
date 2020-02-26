#include <BluetoothSerial.h>
#include <LinkedList.h>
#include <Gaussian.h>
#include <GaussianAverage.h>
#include <analogWrite.h>

GaussianAverage averageLinhaE(10);
GaussianAverage averageLinhaD(10);

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

char BT = 'f';   //caracter que é recebida pelo bluetooth
int tempo = 4900;  //delay antes da lutra
char estrategia = 'f';  //estratégio de início da luta (qualquer caracter)
char lupi = '2';  //estratégia após início da luta (1 a 9)

  #define sharpF 32
  #define sharpE 34
  #define sharpD 35

  #define pwmB 18
  #define b1 26
  #define b2 19
  #define stby 3
  #define a1 5
  #define a2 1
  #define pwmA 23
  //sensor de linha
  #define linhaE 39
  #define linhaD 36
  
  bool direc = true;  //Direção de de giro para qualquer estratégia TRUE=DIREITA FALSE=ESQUERDA
  
void setup() {
  pinMode(pwmB, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(linhaE, INPUT);
  pinMode(linhaD, INPUT);
  pinMode(sharpF, INPUT);
  pinMode(sharpE, INPUT);
  pinMode(sharpD, INPUT);
  digitalWrite(stby,1);
  SerialBT.begin("Tsunami"); //Bluetooth device name
  SerialBT.println("LIGOUUUU");
  while(BT != '0'){    //Inicio quando bluetooth recebe o char '0'
      if(SerialBT.available()) {
          BT = SerialBT.read();
          Serial.print(BT);
      }
      if(BT == '+'){    //aumentar delay
          tempo += 100;
      }else if(BT == '-'){  //diminuir delay
          tempo -= 100; 
      }else if(BT == '<'){  //definir para que lado será toda a progrmação
          direc = false;        
      }else if(BT == '>'){
          direc = true;        
      }else if(BT == 'C'){  //Char 'C' checa as estrategias 
          SerialBT.println("Check");
          SerialBT.print("Estrategia: ");
          SerialBT.println(estrategia);
          SerialBT.print("Loop: ");
          SerialBT.println(lupi);
          SerialBT.print("Direc: ");
          if(direc) SerialBT.println("direita");
          else SerialBT.println("esquerda"); 
          SerialBT.print("Delay: ");
          SerialBT.println(tempo);  
      }else if(BT == '0') {
        break;
      }else {
          if(!(BT == 13 || BT == 10 || (BT>48 && BT<58))){     //Se não for ENTER ou numero será estrategia
              estrategia = BT;
          }
          if(BT>48 && BT<58){   // Se for de 1 a 9 altera a função de loop
            lupi = BT;
          }
      }
  }
  delay(tempo);
  //SerialBT.println("Start");
  //SerialBT.println(lupi);
  //SerialBT.println(estrategia);

  switch (estrategia){
  //Estas são estratégias para início de luta, são leitura de sensor nenhum, apenas um movimento inicial
    case 'a': //frentao
      move('D','F',100);
      move('E','F',100);
      SerialBT.print("FRENTAAO");
      delay(500);
      
    break;

    case 'b':  //curvao
      if(direc){
        move('D','T',100);
        move('E','F',100);
        delay(30);
        move('D','F',100);
        move('E','F',80);
        delay(2000);
      }
      else{
        move('D','F',100);
        move('E','T',100);
        delay(30);
        move('D','F',100);
        move('E','F',80);
        delay(2000);
      }
    break;

     default:
      move('D','F',100);
      move('E','F',100);
      delay(1000);
      SerialBT.print("DEFAAAAAAULT");
      break;

    case 'c':  //babacas
      if (direc){
        move('D','T',100);
        move('E','F',100);
        delay(50);
        move('D','F',100);
        move('E','F',100);
        delay(300);
        move('D','F',100);
        move('E','T',100);
        delay(150);
      }
      else {
        move('D','F',100);
        move('E','T',100);
        delay(50);
        move('D','F',100);
        move('E','F',100);
        delay(300);
        move('D','T',100);
        move('E','F',100);
        delay(150);
      }
      break;

    //case 'd':  //costas

    //case 'e':  //costas curvao

    case 'f': //vai direto pro loop
    break;
  }
}
 
void loop() {
  switch(lupi){
    case '1': //parado até leitura
      while(analogRead(sharpF)<50 && analogRead(sharpE)<50 && analogRead(sharpD)<50){
      }
      while(true){
        while(analogRead(sharpF)>50){
          move('D','F',100);
          move('E','F',100);
        }
        if(analogRead(SharpE)>50){
          move('D','F',100);
          move('E','T',100);
          direc = false;
          delay(100);
        }
        else if(analogRead(SharpD)>50){
          move('D','T',100);
          move('E','F',100);
          direc = true;
          delay(100);
        }
        else{
          if (direc){
              move('D','T',35);
              move('E','F',35);
          }else{
              move('D','F',35);
              move('E','T',35);
          }
        }
      }
    break;
    case '2': //girand
       //SerialBT.println("GIRANDI");
       while(true){
       while(averageLinhaE.mean>1500 && averageLinhaD.mean>1500){
          averageLinhaE += analogRead(linhaE);
          averageLinhaE.process();
          averageLinhaD += analogRead(linhaD);
          averageLinhaD.process();
          while(analogRead(sharpF)>50){  //Se viu o oponente pela frente
              move('D','F',100);         //ataca
              move('E','F',100);     
          }
          if(analogRead(sharpE)>100){   //Se viu o oponente por ultimo do lado esquerdo
              move('D','F',100);
              move('E','T',100);
              delay(100);              //gira 90 graus pra ficar de frente para o oponente
              direc = false;           //a direção de giro passa a ser para a esquerda
              SerialBT.println("ESQUERDAAAAA"); 
          }else if(analogRead(sharpD)>100){  //Se viu o oponente por ultimo do lado direito
              move('D','T',100);
              move('E','F',100);
              delay(100);                    //gira 90 graus pra ficar de frente para o oponente
              direc = true;                  //a direção de giro passa a ser para a direita
              SerialBT.println("DIREIIIIIITA");
          }else {
            if (direc){           //Se não leu em nenhum sensor
              move('D','T',35);       //Gira
              move('E','F',35);
            }else{
              move('D','F',35);
              move('E','T',35);
            }
          }
       }
       move('D','T',100);            //-----------------------------
       move('E','T',100);
       delay(300);                   //
       if (direc){
              move('D','T',100);     //       Fuga da linha
              move('E','F',100);
          }else{
              move('D','F',100);     //
              move('E','T',100);
          }
          delay(120);                 //------------------------------
       }
    break;
      
    case '3': //suicide
      SerialBT.println("SUICIDAAAA");
      while (analogRead(linhaE)>2000 && analogRead(linhaD)>2000){ 
        while(analogRead(sharpE)<50 && analogRead(sharpD)<50){  //não ta dos lados
          move('D','F',100);
          move('E','F',100);
          SerialBT.println("loop");
        }
        if(analogRead(sharpE)>=50){
          move('D','F',100);
          move('E','T',100);
          delay(100);
        }
        else{
          move('D','T',100);
          move('E','F',100);
          delay(100);
        }
      }
      //se ler a linha
      move('D','T',100);
      move('E','T',100);
      delay(50);
      if(direc){
        move('D','T',100);
        move('E','T',100);
        delay(100);
      }
      else{
        move('E','T',100);
        move('D','T',100);
        delay(100);
      }
      break;

      
      default:
      SerialBT.println("DEFaaUUUuuLLllti");
      break;
  }
  /*if(SerialBT.available()){
      BT = SerialBT.read();
      if(BT == 'S') digitalWrite(stby,0);
  }*/
}

void move(char M, char S, int V) {
  /*
    M = qual motor 
    'D' -> motor direito || 'E' -> motor esquerdo
    S = quak sentido de rotação
    'F' -> frente || 'T' -> tras
    V = velocidade de rotação
    0 ~ 100
  */
  
  if ((M == 'D') and (S == 'T')) {
    digitalWrite(a1,1);
    digitalWrite(a2,0);
    analogWrite(pwmA,V*2.55);
  }else if ((M == 'D') and (S == 'F')) {
    digitalWrite(a1,0);
    digitalWrite(a2,1);
    analogWrite(pwmA,V*2.55);
  }else if ((M == 'E') and (S == 'F')) {
    digitalWrite(b1,0);
    digitalWrite(b2,1);
    analogWrite(pwmB,V*2.55);
  }else if ((M == 'E') and (S == 'T')) {
    digitalWrite(b1,1);
    digitalWrite(b2,0);
    analogWrite(pwmB,V*2.55);
  }
}
