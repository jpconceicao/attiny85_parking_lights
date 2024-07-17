/*
Feito por:  Jorge Palma Conceição
Data:       15/07/2024
Cliente:    Morador de Lauro de Freitas
*/

#include <TimerOne.h>

// Definição dos pinos
const int dryContactPin = 0; // PB0
const int relayPin = 1;      // PB1

// Variáveis de estado
bool isDryContactClosed = false;
bool relayState = false;
unsigned long contactOpenedTime = 0;
const unsigned long delayTime = 300000; //300000; // 5 minutos em milissegundos

void setup() {
  pinMode(dryContactPin, INPUT_PULLUP); // Configurar o pino do contato seco como entrada com pull-up
  pinMode(relayPin, OUTPUT);            // Configurar o pino do relé como saída
  digitalWrite(relayPin, LOW);          // Garantir que o relé esteja desligado inicialmente
  
  // Iniciar o temporizador
  Timer1.initialize(1000000); // Configurar o Timer1 para 1 segundo (1000000 microsegundos)
  Timer1.attachInterrupt(timerIsr); // Anexar a interrupção do temporizador
}

void loop() {
  // Verificar o estado do contato seco
  if (digitalRead(dryContactPin) == LOW) { // Contato fechado
    if (!isDryContactClosed) {
      isDryContactClosed = true;
      relayState = true;
      digitalWrite(relayPin, HIGH); // Ligar a lâmpada
    }
  } else { // Contato aberto
    if (isDryContactClosed) {
      isDryContactClosed = false;
      contactOpenedTime = millis(); // Armazenar o tempo em que o contato foi aberto
    }
  }

  // Verificar se o tempo de atraso passou desde que o contato foi aberto
  if (!isDryContactClosed && relayState && (millis() - contactOpenedTime >= delayTime)) {
    relayState = false;
    digitalWrite(relayPin, LOW); // Desligar a lâmpada
  }
}

// Interrupção do temporizador
void timerIsr() {
  // Código da interrupção do temporizador (atualmente não utilizado)
}
