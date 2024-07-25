#include <SoftwareSerial.h>

#define Pino_RS485_RX 10 // DI do Módulo RS485
#define Pino_RS485_TX 11 // DO do Módulo RS485
#define SSerialTxControl 3 // Pino de Controle

bool RS485Transmit = HIGH; // Transmissor
bool RS485Receive = LOW; // Receptor

SoftwareSerial RS485Serial(Pino_RS485_RX, Pino_RS485_TX); // Definir os Pinos do Serial RS485

String dadosSerial = ""; // Lista de Dados Enviados
String dadosRecebidos = ""; // Lista De Dados Recebidos


void setup() {
  Serial.begin(9600); // Inicializa o Serial
  Serial.println("Modulo Transmissor"); 
  Serial.println("Digite um Valor na Serial para enviar os dados...");
  pinMode(SSerialTxControl, OUTPUT); // Pino de Controle como Saída
  RS485Serial.begin(4800); // Inicializa o Serial do RS485
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    dadosSerial += c;

    // Se encontrar um caractere de nova linha ('\n'), termina a entrada
    if (c == '\n') {
      enviarDados(dadosSerial); // Envia os dados acumulados
      dadosSerial = ""; // Limpa a string para a próxima entrada
    }
  }

  // Recebimento de dados do Arduino 2 via RS485
  if (RS485Serial.available()) {
    while (RS485Serial.available()) {
      char charReceive = (char)RS485Serial.read();
      dadosRecebidos += charReceive;
      if (charReceive == '\n') {
        bufferPrint(dadosRecebidos, 500); // Processa e exibe os dados recebidos
        dadosRecebidos = ""; // Limpa os dados recebidos
      }
    }
  }
}

void enviarDados(String dados) {
  digitalWrite(SSerialTxControl, RS485Transmit); // Define como Transmissor
  RS485Serial.println(dados); // Envia os dados pela RS485
  RS485Serial.flush(); // Garante que todos os dados sejam enviados
  digitalWrite(SSerialTxControl, RS485Receive); // Define como Receptor
  Serial.println("Dados enviados: " + dados); // Exibe os dados enviados via Serial monitor
}

void bufferPrint(String codigo, unsigned long intervalo) {
  // Remove espaços em branco extras
  codigo.trim();
  
  // Imprime o código
  Serial.print("Codigo Recebido: ");
  Serial.println(codigo);

  // Aguarda o intervalo desejado usando millis()
  unsigned long startTime = millis();
  while (millis() - startTime < intervalo) {
    // Aguarda passivamente até completar o intervalo
  }
}
