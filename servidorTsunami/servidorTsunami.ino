#include <WiFi.h>
//192.168.4.1
const char* ssid = "ESP32";
const char* senha = "esp12345";
String cabecalho;
WiFiServer server(80);

void setup() {
      Serial.begin(115200);// ------------------------------------------------------------|
      Serial.println(); //----------------------------------------------------------------|
      //APSerial.printf("Configurando ponto de acesso '%s'n", ssid); -------------------| CONFIGURANDO WIFI
      WiFi.softAP(ssid, senha);// --------------------------------------------------------|
      server.begin();// ------------------------------------------------------------------|
      Serial.println("Configuração conluída");// -----------------------------------------|
      
      }

void loop() {
    //Verifica se existe algum cliente na rede 
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
                          Serial.println("driftDireita");
                      }else if(cabecalho.indexOf("GET /driftEsquerda")>= 0){ 
                          Serial.println("driftEsquerda");
                      }
                    break; //sai do while loop
                }
            }
        }
        cabecalho = ""; //ao encerrar conexão, limpa variável cabecalho
        client.flush(); client.stop();
        //Serial.println("Client desconectado."); Serial.println();
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
           "</a></p>";
        html_content += \    
        "</body>" \
    "</html>";
    client.println(html_content);
}
