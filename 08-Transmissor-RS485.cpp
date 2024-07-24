#include <SoftwareSerial.h>

#define Pino_RS485_RX 10 // DI do Módulo RS485
#define Pino_RS485_TX 11 // DO do Módulo RS485
#define SSerialTxControl 3 

#define RS485Transmit HIGH
#define RS485Receive LOW

SoftwareSerial RS485Serial(Pino_RS485_RX, Pino_RS485_TX);

String dadosSerial = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Modulo Transmissor");
  Serial.println("Digite um Valor na Serial para enviar os dados ...");
  pinMode(SSerialTxControl, OUTPUT);
  RS485Serial.begin(4800);
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (isPrintable(c)) {
      dadosSerial += c;
    }
  }

  if (dadosSerial.length() > 0) {
    enviarDados(dadosSerial); // Adiciona o sufixo "X" aos dados antes de enviar
    dadosSerial = "";
  }
}

void enviarDados(String dados) {
  digitalWrite(SSerialTxControl, RS485Transmit);
  RS485Serial.println(dados);
  RS485Serial.flush();
  digitalWrite(SSerialTxControl, RS485Receive);
  Serial.println("Dados enviados: " + dados);
}
