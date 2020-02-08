#include <analogWrite.h>
//#include <MPU6050_tockn.h>
//#include <Wire.h>
//#include <SharpDistSensor.h>
//MPU6050 mpu(Wire);

//Wifi
#include <WiFi.h>
//192.168.4.1
const char* ssid = "ESP32";
const char* senha = "esp12345";
String cabecalho;
WiFiServer server(80);

const byte sharpF = 12;
const byte sharpT = 13;
const byte medianFilterWindowSize = 5;
  //#define sharpF 12
  //#define sharpT 13

  #define dip1 33
  #define dip2 32
  #define dip3 35
  #define dip4 34

  #define button 36
  
  #define pwmB 23
  #define b1 5
  #define b2 1
  #define stby 3
  #define a1 26
  #define a2 19
  #define pwmA 18
  //sensor de linha
  #define linha1 2
  #define linha2 4
  //sharp
  int valorSensor1 = 0;
  int valorSensor2 = 0;
  //acelerometro
  float yInicial = 0;
  //potencia
  int a = 100;
  int b = 100;
  bool direc = true;
  int estrategia = 0;
void setup() {
  pinMode(pwmB, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(linha1, INPUT);
  pinMode(linha2, INPUT);
  pinMode(sharpF, INPUT);
  pinMode(sharpT, INPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(dip1,INPUT);
  pinMode(dip2,INPUT);
  pinMode(dip3,INPUT);
  pinMode(dip4,INPUT);
  digitalWrite(stby,1);
  
      Serial.begin(115200);// ------------------------------------------------------------|
      Serial.println(); //----------------------------------------------------------------|
      //APSerial.printf("Configurando ponto de acesso '%s'n", ssid);---| CONFIGURANDO WIFI
      WiFi.softAP(ssid, senha);// --------------------------------------------------------|
      server.begin();// ------------------------------------------------------------------|
      Serial.println("Configuração conluída");// -----------------------------------------|


  wifi();
  
  delay(4800);  
  
  if(estrategia==3){
    frente(200,255);
    delay(500);
    Serial.println("frentao");
  }else if(estrategia == 1){
    //direita
    direc=0;
    drift(); 
    Serial.println("drift direita");
  }else if(estrategia == 2){
    //esquerda
    direc=1;
    drift();  
    Serial.println("drift esquerda");
  }
}
 
void loop() {
  unsigned int sharp1 = analogRead(12);
  unsigned int sharp2 = analogRead(13);
  valorSensor1 = analogRead(linha1);
  valorSensor2 = analogRead(linha2);

//segue adversário
//rever, provavelmente vai bugar
  if(sharp1 > 100 || sharp2 > 100){
    frente(255, 255);
    if(sharp1 < sharp2){
      frente(255, 180);
    }else{  
      frente(180, 255);
    }
  }else if(direc==1){
    esquerda(a, b);
  }else{
    direita(a,b);  
  }

  if(valorSensor2 < 1000 || valorSensor1 < 1000){
   fugaLinha();
  }
}




void tras(int pa, int pb){
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
}
void frente(int pa, int pb){
  digitalWrite(b1,0);
  digitalWrite(b2,1);
  digitalWrite(a1,0);
  digitalWrite(a2,1);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
}
void esquerda(int pa, int pb){
  digitalWrite(b1,0);
  digitalWrite(b2,1);
  digitalWrite(a1,1);
  digitalWrite(a2,0);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
  }
 void direita(int pa, int pb){
  digitalWrite(b1,1);
  digitalWrite(b2,0);
  digitalWrite(a1,0);
  digitalWrite(a2,1);
  analogWrite(pwmB, pb);
  analogWrite(pwmA, pa);
  }

  
void fugaLinha(){
  if(valorSensor1 > valorSensor2){
      tras(250, 250);
      delay(200);
      esquerda(a, b);
      delay(300);
    }
    else{
      tras(250, 250);
      delay(200);
      direita(a, b);
      delay(300);
     }
}

void drift(){
  if(direc==1){
    esquerda(250,250);
    delay(120);
    frente(250, 110);
    delay(1000);
  }
  else{
    direita(250,250);
    delay(120);
    frente(120, 250);
    delay(1000);
  }
  direc = !direc;
}

void fugaAdversario(){
  tras(200, 100);
  delay(250);
  }
void wifi(){
  //Verifica se existe algum cliente na rede 
  while(estrategia == 0){
    WiFiClient client = server.available();   
    //Se existe alguém na rede
    if (client){                           
        //Enquanto client conectado, verifica se existem bytes a serem lidos     
        //e concatena os bytes recebidos na String cabecalho  
        while (client.connected()){     
            if (client.available()){
                cabecalho += (char)client.read();  
                //Se receber nova linha em branco, encerrou leitura dos dados
                if (cabecalho.endsWith("\n\r\n")){
                    // INSIRA AQUI SUA APLICAÇÃO
                    //envia ao client conteúdo HTML
                    pagina(client);
                      
                      if(cabecalho.indexOf("GET /driftDireita")>= 0){ 
                          estrategia = 1;
                      }else if(cabecalho.indexOf("GET /driftEsquerda")>= 0){ 
                          estrategia = 2;
                      }else if(cabecalho.indexOf("GET /frentao")>= 0){ 
                          estrategia = 3;
                      }else if(cabecalho.indexOf("GET /gira")>= 0){ 
                          estrategia = 4;
                      }
                    break; 
                }
            }
        }
        cabecalho = ""; //ao encerrar conexão, limpa variável cabecalho
        client.flush(); client.stop();
        //Serial.println("Client desconectado."); Serial.println();
    }
  }
 }

void pagina(WiFiClient client){ 
   String html_content = \
    "<!DOCTYPE html><html>" \
        "<head><style media='screen' type='text/css'>" \
             "html{margin:10px auto;text-align:center;}" \
        "</style></head>" \
        "<body>" \
            "<h1 style='font-size:80px'>Tamandutech</h1>"; 
            html_content += \
            "<p><a href='/driftDireita'>" \
                "<button style='width:400px;font-size:80px'>driftDireita</button>" \
            "</a></p>" \
            "<br>"\
            "<p><a href='/driftEsquerda'>" \
                "<button style='width:400px;font-size:80px'>driftEsquerda</button>" \
           "</a></p>"
           "<p><a href='/frentao'>" \
                "<button style='width:400px;font-size:80px'>frentao</button>" \
            "</a></p>" \
            "<br>"\
            "<p><a href='/gira'>" \
                "<button style='width:400px;font-size:80px'>gira</button>" \
           "</a></p>";
        html_content += \    
        "</body>" \
    "</html>";
    client.println(html_content);
}
