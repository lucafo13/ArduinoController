const int leds[] = {3, 5, 6, 9, 10};
const int quantidade = 5;

int padraoAtual = 1;
bool mudouPadrao = false;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < quantidade; i++) {
    pinMode(leds[i], OUTPUT);
    analogWrite(leds[i], 0);
  }
}

void loop() {
  lerComandos();

  if (padraoAtual == 1) {
    repouso();
  } 
  else if (padraoAtual == 2) {
    impulsoNervoso();
  } 
  else if (padraoAtual == 3) {
    lesaoMedular();
  } 
  else if (padraoAtual == 4) {
    polilaminina();
  }
}

void lerComandos() {
  while (Serial.available() > 0) {
    char comando = Serial.read();

    if (comando >= '1' && comando <= '4') {
      padraoAtual = comando - '0';
      mudouPadrao = true;
      apagarTodos();
    }
  }
}

bool esperar(int tempo) {
  for (int i = 0; i < tempo; i++) {
    lerComandos();

    if (mudouPadrao) {
      mudouPadrao = false;
      return false;
    }

    delay(1);
  }

  return true;
}

void apagarTodos() {
  for (int i = 0; i < quantidade; i++) {
    analogWrite(leds[i], 0);
  }
}

void acenderTodos() {
  for (int i = 0; i < quantidade; i++) {
    analogWrite(leds[i], 255);
  }
}

void repouso() {
  const int brilhoMaximo = 255;
  const int passo = 5;
  const int intervalo = 20;
  const int atrasoEntreLeds = 8;

  int brilho[5] = {255, 255, 255, 255, 255};
  int direcao[5] = {-1, -1, -1, -1, -1};
  int tempo = 0;

  while (true) {
    for (int i = 0; i < quantidade; i++) {
      if (tempo >= i * atrasoEntreLeds) {
        brilho[i] += direcao[i] * passo;

        if (brilho[i] <= 0) {
          brilho[i] = 0;
          direcao[i] = 1;
        }

        if (brilho[i] >= brilhoMaximo) {
          brilho[i] = brilhoMaximo;
          direcao[i] = -1;
        }

        analogWrite(leds[i], brilho[i]);
      }
    }

    tempo++;

    if (!esperar(intervalo)) return;
  }
}

void impulsoNervoso() {
  while (true) {
    for (int i = 0; i < quantidade; i++) {
      analogWrite(leds[i], 255);
      if (!esperar(65)) return;
    }

    if (!esperar(100)) return;

    for (int i = 0; i < quantidade; i++) {
      analogWrite(leds[i], 0);
      if (!esperar(65)) return;
    }

    if (!esperar(100)) return;
  }
}

void lesaoMedular() {
  while (true) {
    for (int repeticao = 0; repeticao < 4; repeticao++) {
      for (int i = 0; i < 3; i++) {
        analogWrite(leds[i], 255);
        if (!esperar(75)) return;
      }

      if (!esperar(180)) return;

      for (int i = 0; i < 3; i++) {
        analogWrite(leds[i], 0);
        if (!esperar(55)) return;
      }

      if (!esperar(220)) return;
    }
  }
}

void polilaminina() {
  while (true) {
    apagarTodos();

    int brilho4 = 0;
    int brilho5 = 0;

    while (brilho4 < 255 || brilho5 < 255) {
      for (int i = 0; i < 3; i++) {
        analogWrite(leds[i], 255);
        if (!esperar(90)) return;
      }

      for (int i = 0; i < 3; i++) {
        analogWrite(leds[i], 0);
        if (!esperar(60)) return;
      }

      if (brilho4 < 255) {
        brilho4 += 3;
        if (brilho4 > 255) brilho4 = 255;
      }

      if (brilho5 < 255) {
        brilho5 += 3;
        if (brilho5 > 255) brilho5 = 255;
      }

      analogWrite(leds[3], brilho4);
      analogWrite(leds[4], brilho5);

      if (!esperar(200)) return;
    }

    unsigned long inicio = millis();

    while (millis() - inicio < 10000UL) {
      for (int i = 0; i < quantidade; i++) {
        analogWrite(leds[i], 255);
        if (!esperar(90)) return;
      }

      for (int i = 0; i < quantidade; i++) {
        analogWrite(leds[i], 0);
        if (!esperar(65)) return;
      }

      if (!esperar(120)) return;
    }

    for (int repeticao = 0; repeticao < 8; repeticao++) {
      for (int i = 0; i < 3; i++) {
        analogWrite(leds[i], 255);
        if (!esperar(90)) return;
      }

      for (int i = 0; i < 3; i++) {
        analogWrite(leds[i], 0);
        if (!esperar(60)) return;
      }

      analogWrite(leds[3], 255);
      analogWrite(leds[4], 255);

      if (!esperar(100)) return;

      analogWrite(leds[3], 0);
      analogWrite(leds[4], 0);

      if (!esperar(180)) return;
    }

    analogWrite(leds[3], 0);
    analogWrite(leds[4], 0);

    if (!esperar(3000)) return;

    unsigned long inicioFinal = millis();

    while (millis() - inicioFinal < 3000UL) {
      for (int i = 0; i < 3; i++) {
        analogWrite(leds[i], 255);
        if (!esperar(90)) return;
      }

      for (int i = 0; i < 3; i++) {
        analogWrite(leds[i], 0);
        if (!esperar(60)) return;
      }

      if (!esperar(120)) return;
    }


  }
}