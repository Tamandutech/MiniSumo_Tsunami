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
