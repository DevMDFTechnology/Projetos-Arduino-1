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
  Serial.println("Digite um Valor na Serial para enviar os dados...");
  pinMode(SSerialTxControl, OUTPUT);
  RS485Serial.begin(4800);
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    dadosSerial += c;
    
    // Se encontrar um caractere de nova linha ('\n'), termina a entrada
    if (c == '\n') {
      // Envia os dados no formato solicitado: /003011X,/001011X,/002022X,
      dadosSerial.replace("R", "X");
      enviarDados(dadosSerial); // Envia os dados acumulados
      dadosSerial = ""; // Limpa a string para a próxima entrada
    }
  }
}

void enviarDados(String dados) {
  digitalWrite(SSerialTxControl, RS485Transmit);
  RS485Serial.println(dados); // Envia os dados pela RS485
  RS485Serial.flush(); // Garante que todos os dados sejam enviados
  digitalWrite(SSerialTxControl, RS485Receive);
  Serial.println("Dados enviados: " + dados); // Exibe os dados enviados via Serial monitor
}
