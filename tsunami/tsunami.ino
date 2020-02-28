// delay(100) com os motores no talo gira 90º

#include <BluetoothSerial.h>
#include <analogWrite.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

char BT = 'f';   //char que é recebida pelo bluetooth
int tempo = 4900;  //delay antes da lutra
char estrategia = 'f';  //estratégio de início da luta (qualquer caracter)
char lupi = '2';  //estratégia após início da luta (1 a 9)

unsigned long tempoAgora = 0;

  #define sharpF 32
  #define sharpE 34
  #define sharpD 35

  #define pwmB 23
  #define b1 1
  #define b2 5
  #define stby 3
  #define a1 19
  #define a2 26
  #define pwmA 18
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
      }else if(BT == 'C'){      //Char 'C' checa as estrategias 
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
          if(!(BT == 13 || BT == 10 || (BT>48 && BT<58))){     //Se não for ENTER ou numero altera a estrategia inicial
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
  //Estas são estratégias para início de luta, sem leitura de sensor nenhum, apenas um movimento inicial
  
    case 'a': //frentao
      move('D','F',100);
      move('E','F',100);
      SerialBT.print("FRENTAAO");
      delay(300);
      
    break;

    case 'b':  //curvao
      if(direc){
        move('D','T',100);
        move('E','F',100);
        delay(80);
        move('D','F',100);
        move('E','F',35);
        delay(500);
        move('D','F',100);
        move('E','T',100);
        delay(100);
        direc = false;
      }
      else{
        move('D','F',100);
        move('E','T',100);
        delay(80);
        move('D','F',45);
        move('E','F',100);
        delay(500);
        move('D','T',100);
        move('E','F',100);
        delay(100);
        direc = true;
      }
    break;

    case 'c':   //curvinha
      if(direc){
        move('D','T',100);
        move('E','F',100);
        delay(90);
        move('D','F',100);
        move('E','F',40);
        delay(800);
      }
      else{
        move('D','F',100);
        move('E','T',100);
        delay(90);
        move('D','F',100);
        move('E','F',40);
        delay(800);
      }
    break;

    case 'd':  //babacas
      if (direc){
        move('D','T',100);
        move('E','F',100);
        delay(50);
        move('D','F',100);
        move('E','F',100);
        delay(250);
        move('D','F',100);
        move('E','T',100);
        delay(120);
      }
      else {
        move('D','F',100);
        move('E','T',100);
        delay(50);
        move('D','F',100);
        move('E','F',100);
        delay(250);
        move('D','T',100);
        move('E','F',100);
        delay(120);
      }
      break;

    case 'e':  //costas   - só gira 180º
      if (direc){  //prestar atenção na direc, pq os robôs estarão de costas
        move('D','T',100);
        move('E','F',100);
        delay(185);
      }
      else{
        move('D','F',100);
        move('E','T',100);
        delay(185);
      }
      
    break;

        
    case 'f': //vai direto pro loop
    break;

    case 'g':  //costas curvao
      if (direc){
        move('D','F',50);
        move('E','F',100);
        delay(200);
      }
      else{
        move('D','F',100);
        move('E','F',50);
        delay(200);
      }
      
      
    break;

    default:        //CÓPIA DO FRENTÃO
      move('D','F',100);
      move('E','F',100);
      delay(500);
      SerialBT.print("DEFAAAAAAULT");
     break;
  }
}
 
void loop() {

  // Estratégias do meio da luta, como vai procurar o oponente
  switch(lupi){
    case '1': //parado até leitura

        tempoAgora = millis();
        while(analogRead(sharpF)<100 && analogRead(sharpE)<200 && analogRead(sharpD)<200){
          if(millis() < tempoAgora + 5000){
            move('D','F',100);
            move('D','F',100);
            delay(100);
            move('D','F',0);
            move('D','F',0);
            tempoAgora = millis();  
          }
        }
        while(true){
        while(analogRead(linhaE)>1500 && analogRead(linhaD)>1500){
          while(analogRead(sharpF)>50){  //Se viu o oponente pela frente
              move('D','F',100);         //ataca
              move('E','F',100);     
          }
          if(analogRead(sharpE)>200){   //Se viu o oponente por ultimo do lado esquerdo
              /*move('D','F',40);
              move('E','T',40);             //a direção de giro passa a ser para a esquerda
              //SerialBT.println("ESQUERDAAAAA"); 
              tempoAgora = millis();
              while(millis() < tempoAgora + 100){
                if(analogRead(sharpF)>50){
                  move('D','F',100);         //ataca
                  move('E','F',100);
                  break;
                }
              }*/
              direc = false;         //a direção de giro passa a ser para a esquerda
          }else if(analogRead(sharpD)>200){  //Se viu o oponente por ultimo do lado direito
              /*move('D','T',40);
              move('E','F',40);
              //SerialBT.println("DIREIIIIIITA");
              tempoAgora = millis();
              while(millis() < tempoAgora + 100){
                if(analogRead(sharpF)>50){
                  move('D','F',100);         //ataca
                  move('E','F',100);
                  break; 
                }  
              }*/                                    //gira 90 graus pra ficar de frente para o oponente
              direc = true;                  //a direção de giro passa a ser para a direita
          }else {
            if(direc){           //Se não leu em nenhum sensor
              move('D','T',25);       //Gira
              move('E','F',25);
            }else{
              move('D','F',25);
              move('E','T',25);
            }
          }
       }
       move('D','T',100);            //-----------------------------
       move('E','T',100);
       delay(500);                   //
       if (direc){
              move('D','F',100);     //       Fuga da linha
              move('E','T',100);
          }else{
              move('D','T',100);     //
              move('E','F',100);
          }
       tempoAgora = millis();
       while(millis() < tempoAgora + 100){
        if(analogRead(sharpF)>50){
          move('D','F',100);         //ataca
          move('E','F',100);
          break;
         }  
       }               //------------------------------
    }
    break;
    
    case '2': //girand
       //SerialBT.println("GIRANDI");
       while(true){
       while(analogRead(linhaE)>1500 && analogRead(linhaD)>1500){
          while(analogRead(sharpF)>50){  //Se viu o oponente pela frente
              move('D','F',100);         //ataca
              move('E','F',100);     
          }
          if(analogRead(sharpE)>200){   //Se viu o oponente por ultimo do lado esquerdo
              move('D','F',100);
              move('E','F',0);             //a direção de giro passa a ser para a esquerda
              //SerialBT.println("ESQUERDAAAAA"); 
              delay(300);
              direc = false;         //a direção de giro passa a ser para a esquerda
          }else if(analogRead(sharpD)>200){  //Se viu o oponente por ultimo do lado direito
              move('D','F',0);
              move('E','F',100);
              delay(300);                                 //gira 90 graus pra ficar de frente para o oponente
              direc = true;                  //a direção de giro passa a ser para a direita
          }else {
            if(direc){           //Se não leu em nenhum sensor
              move('D','T',25);       //Gira
              move('E','F',25);
            }else{
              move('D','F',25);
              move('E','T',25);
            }
          }
       }
       move('D','T',100);            //-----------------------------
       move('E','T',100);
       delay(500);                   //
       if (direc){
              move('D','F',100);     //       Fuga da linha
              move('E','T',100);
          }else{
              move('D','T',100);     //
              move('E','F',100);
          }
       tempoAgora = millis();
       while(millis() < tempoAgora + 100){
        if(analogRead(sharpF)>50){
          move('D','F',100);         //ataca
          move('E','F',100);
          break;
         }  
       }               //------------------------------
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

      case '9':                                             //Faz nada PARAAAAAA
        move('D','T',0);
        move('E','T',0);
        while(true){}
      break;

      
      default:                                               //COPIAR ALGUM LOOP PRO DEFAULT
      SerialBT.println("DEFaaUUUuuLLllti");
      break;
      
  }
  /*if(SerialBT.available()){        //desligar motores
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
