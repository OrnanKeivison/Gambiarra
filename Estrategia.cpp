#include "Estrategia.h"

void Estrategia::seguirLinha() {

  sensoresLinha.atualizarSensoresRefletancia();

  if (sensoresLinha.frente()) {
    motores.emFrente();
  }

  else if (sensoresLinha.direita()) {
    motores.direita();
  }

  else if (sensoresLinha.esquerda()) {
    motores.esquerda();
  }

  else if (sensoresLinha.pppp()) {
    fazerVerde();
  }
//  else if (sensorCor.PretoDir() && sensorCor.PretoEsq()) {
//      robo.acionarMotores(100, 100);
//      delay(500);
//    }

}

void Estrategia::fazerVerde(){
    motores.emFrente();
    delay(200);
    motores.direita();
    delay(200);
    motores.parar(100);
    
    robo.habilitaTCS34();
    sensorCor.atualizarSensoresCor();
    if (sensorCor.direita()) {
      motores.emFrente();
      delay(200);
      motores.girar90Esq();
      motores.direita();
      delay(200);
    }
    else if (sensorCor.esquerda()) {
      motores.emFrente();
      delay(200);
      motores.girar90Dir();
    }

    else if (sensorCor.becoSemSaida()) {
      motores.emFrente();
      delay(250);
      motores.girar90Dir();
      motores.girar90Dir();
    }
    
    else {
      motores.paraTras();
      delay(300);
      motores.emFrente();
      delay(500);
    }
  
  }

void Estrategia::alinharLinha() {
  while (!sensoresLinha.pppp()) {
    sensoresLinha.atualizarSensoresRefletancia();

    if (sensoresLinha.desalinhou_direita()) {
      motores.direita();
    }
    else if (sensoresLinha.desalinhou_esquerda()) {
      motores.esquerda();
    }
    else {
      motores.paraTras();
    }
  }
}

void Estrategia::desviarObstaculoPelaEsq() {
  sensoresLinha.atualizarSensoresRefletancia();

  motores.girar90Dir();

  alinharLinha();

  motores.emFrente();
  delay(2000);

  motores.girar90Esq();

  motores.emFrente();
  delay(2500);

  motores.girar90Esq();

  motores.emFrente();
  delay(2000);

  sensoresLinha.atualizarSensoresRefletancia();

  alinharLinha();

  motores.emFrente();
  delay(600);

  motores.girar90Dir();

  sensoresLinha.atualizarSensoresRefletancia();
  if (sensoresLinha.bbbb()) {
    motores.paraTras();
    delay(300);
  }
}

void Estrategia::desviarObstaculoPelaDir() {
  sensoresLinha.atualizarSensoresRefletancia();

  motores.girar90Esq();

  alinharLinha();

  motores.emFrente();
  delay(2500);

  motores.girar90Dir();

  motores.emFrente();
  delay(4000);

  motores.girar90Dir();

  motores.emFrente();
  delay(2000);

  sensoresLinha.atualizarSensoresRefletancia();

  alinharLinha();

  motores.emFrente();
  delay(600);

  motores.girar90Esq();

  sensoresLinha.atualizarSensoresRefletancia();
  if (sensoresLinha.bbbb()) {
    motores.paraTras();
    delay(500);
  }
}

void Estrategia::executar() {
  // sensoresLinha.getValues();
  // robo.habilitaTCS34();
  // sensorCor.atualizarSensoresCor();
  // sensorCor.getValues();
  // sensorCor.testar();
  sonar.atualizarSensorSonar();

  if (sonar.getSensorSonar() <= 8) {
    desviarObstaculoPelaEsq();
  }
  else {
    seguirLinha();
  }
}
