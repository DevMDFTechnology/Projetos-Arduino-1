#include <Arduino.h>

String dadosSerial = ""; // String para armazenar os dados recebidos
unsigned int tempoAnterior = 0; // Tempo da última impressão

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read(); 
    
    // Verifica se é um caractere imprimível (ignora caracteres de controle)
    if (isPrintable(c)) {
      dadosSerial += c; // Concatena os caracteres para formar a string completa
    }
  }

  // Chamada da função bufferPrint com a condição de tempo
  bufferPrint(dadosSerial, 500);
}

void bufferPrint(String codigo, unsigned int leituraAnterior){
  // Verifica se passaram 500 ms desde a última impressão
  if (millis() - tempoAnterior >= leituraAnterior && codigo.length() > 0) {
    // Encontra a posição do primeiro caractere de vírgula
    int posVirgula = codigo.indexOf(',');
    if (posVirgula != -1) {
      // Imprime a parte da string até a vírgula
      Serial.println(codigo.substring(0, posVirgula + 1));
      // Imprime 500 em uma nova linha
      Serial.println(leituraAnterior);
      // Remove a parte impressa da string
      dadosSerial = codigo.substring(posVirgula + 1);
    }
    
    // Verifica se ainda há dados para enviar
    if (dadosSerial.length() == 0) {
      Serial.println("\nDados enviados com sucesso!");
    }
    
    tempoAnterior = millis(); // Atualiza o tempo anterior para o atual
  }
}
