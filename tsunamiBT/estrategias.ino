void escolheEstrategia(){
  if(cont == 0){
    if(est == "1"){
      frente(200,255);
      delay(500);
    }
    else if(est == "2"){
      driftDireita(); 
    }
    else if(est == "3"){
      driftEsquerda();    
    }
    delay(4700);
    cont += 1;
    }
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
void driftEsquerda(){
    esquerda(250,250);
    delay(120);
    frente(250, 110);
    delay(1000);
    printf("Esquerda");
}
void driftDireita(){
    direita(250,250);
    delay(120);
    frente(120, 250);
    delay(1000);
    printf("direita");
  }
void fugaAdversario(){
  tras(200, 100);
  delay(250);
  }
