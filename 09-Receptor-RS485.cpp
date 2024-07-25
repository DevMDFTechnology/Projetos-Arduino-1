#include <SoftwareSerial.h>

#define Pino_RS485_RX 10 // DO (Direct Output)
#define Pino_RS485_TX 11 // DI (Direct Input)
#define SSerialTxControl 3
#define RS485Transmit HIGH
#define RS485Receive LOW

SoftwareSerial RS485Serial(Pino_RS485_RX, Pino_RS485_TX);

String inputString = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Módulo Receptor");
  Serial.println("Aguardando dados...");
  pinMode(SSerialTxControl, OUTPUT);
  digitalWrite(SSerialTxControl, RS485Receive);
  RS485Serial.begin(4800);
}

void loop() {
  if (RS485Serial.available()) {
    while (RS485Serial.available()) {
      char inChar = (char)RS485Serial.read();
      inputString += inChar;
      if (inChar == '\n') {
        processInput(inputString);
        inputString = "";
      }
    }
  }
}

void processInput(String input) {
  // Remove espaços em branco extras
  input.trim();
  
  // Substitui todas as '/' por '' (vazio)
  input.replace("/", "");
  
  // Separa os códigos por vírgula
  int startPos = 0;
  int commaPos = input.indexOf(',', startPos);
  while (commaPos != -1) {
    String codigo = input.substring(startPos, commaPos);
    bufferPrint(codigo, 500); // Chama bufferPrint com intervalo de 500 ms
    startPos = commaPos + 1;
    commaPos = input.indexOf(',', startPos);
  }
  
  // Processa o último código depois da última vírgula
  if (startPos < input.length()) {
    String codigo = input.substring(startPos);
    bufferPrint(codigo, 500); // Chama bufferPrint com intervalo de 500 ms
  }
  
  Serial.println(""); // Adiciona uma linha em branco entre as entradas
}

void bufferPrint(String codigo, unsigned long intervalo) {
  // Remove espaços em branco extras
  codigo.trim();
  
  // Substitui 'X' por 'R'
  codigo.replace("X", "R");
  codigo.replace("x", "r");
  
  // Imprime o código
  Serial.println(codigo + ",");
  
  // Aguarda o intervalo desejado usando millis()
  unsigned long startTime = millis();
  while (millis() - startTime < intervalo) {
    // Aguarda passivamente até completar o intervalo
  }
}
