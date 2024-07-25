#include <SoftwareSerial.h>

#define Pino_RS485_RX 10 // DO (Direct Output)
#define Pino_RS485_TX 11 // DI (Direct Input)
#define SSerialTxControl 3
#define RS485Transmit HIGH
#define RS485Receive LOW

SoftwareSerial RS485Serial(Pino_RS485_RX, Pino_RS485_TX);

String inputString = "";
unsigned long previousMillis = 0; // Armazena o último tempo em que a função bufferPrint foi chamada
const unsigned long interval = 500; // Intervalo fixo de 500 ms para todas as chamadas

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

  // Chama bufferPrint em intervalos regulares
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    bufferPrint();
  }
}

void processInput(String input) {
  input.trim();
  input.replace("/", "");
  int startPos = 0;
  int commaPos = input.indexOf(',', startPos);
  while (commaPos != -1) {
    String codigo = input.substring(startPos, commaPos);
    bufferPrint(codigo);
    startPos = commaPos + 1;
    commaPos = input.indexOf(',', startPos);
  }
}

void bufferPrint(String codigo = "") {
  if (codigo.length() > 0) {
    codigo.trim();
    codigo.replace("X", "R");
    codigo.replace("x", "r");
    
    // Imprime o código
    Serial.println(codigo + ",");
  }
}
