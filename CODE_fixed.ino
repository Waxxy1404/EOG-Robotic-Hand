#include <Servo.h>

// Criacao dos objetos Servo
Servo servo1, servo2, servo3, servo4, servo5;

// Pino de entrada analogica do sinal de EOG
const int EOGpin = A0;

// Pinos PWM para controle dos 5 servo motores
const int pinoServo1 = 3;  // Dedo 1
const int pinoServo2 = 5;  // Dedo 2
const int pinoServo3 = 6;  // Dedo 3
const int pinoServo4 = 9;  // Dedo 4
const int pinoServo5 = 10; // Dedo 5

// Variaveis de limiar e estado de repouso
const int VALOR_REST   = 60;
const int LIMIAR_BAIXO = 5;
const int LIMIAR_CIMA  = 180;

// Variaveis para definicao da posicao dos servos
const int POS_ABERTA  = 150;
const int POS_FECHADA = 30;
int PosAtualServo = POS_ABERTA;

// Funcao para mover todos os servos individualmente
void MoverDedos(int novaPosicao1, int novaPosicao2, int novaPosicao3, int novaPosicao4, int novaPosicao5) {
  servo1.write(novaPosicao1);
  servo2.write(novaPosicao2);
  servo3.write(novaPosicao3);
  servo4.write(novaPosicao4);
  servo5.write(novaPosicao5);
  delay(20);
}

void setup() {
  Serial.begin(9600);

  servo1.attach(pinoServo1);
  servo2.attach(pinoServo2);
  servo3.attach(pinoServo3);
  servo4.attach(pinoServo4);
  servo5.attach(pinoServo5);

  MoverDedos(POS_ABERTA, POS_ABERTA, POS_ABERTA, POS_ABERTA, POS_FECHADA);
  Serial.println("Sistema de captura de sinal iniciado - Mao robotica pronta...");
}

void loop() {
  int DsignalEOG = analogRead(EOGpin);

  Serial.println(DsignalEOG);

  // Sinal acima do limiar superior -> gesto "OK"
  if (DsignalEOG > LIMIAR_CIMA) {
    Serial.println(DsignalEOG);
    MoverDedos(POS_ABERTA, POS_ABERTA, POS_ABERTA, POS_FECHADA, POS_ABERTA);
    Serial.println("Comando OK ativado");
    delay(3000);
  }

  // Sinal abaixo do limiar inferior -> gesto "Rock n Roll"
  if (DsignalEOG < LIMIAR_BAIXO) {
    Serial.println(DsignalEOG);
    MoverDedos(POS_ABERTA, POS_FECHADA, POS_FECHADA, POS_ABERTA, POS_FECHADA);
    Serial.println("Comando ROCK N ROLL ativado");
    delay(3000);
  }

  delay(5);
}
