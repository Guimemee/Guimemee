/*
 ====================================================================
 PROJETO INTEGRADO - CHALLENGE HOSPITAL ALEMAO OSWELDO CRUZ (2022)
 SPRINT 3 E 4: CONTROLE MANUAL DE MOTOR DE PASSO EM MODO MEIO-PASSO (HALF-STEP)
 DISCIPLINA: ENGENHARIA DA COMPUTACAO / SISTEMAS EMBARCADOS
 AUTERES EFETIVOS: EQUIPE DE ENGENHARIA BIOMEDICA (FIAP 2022)
 TURMA: 1ECB - 2o SEMESTRE
 ===================================================================

 DESCRICAO DO PROJETO:
  Controle em baixo nivel das 4 bobinas de um motor de passo de 4 fases
  (modelo 28BYJ-48 com driver Darlington ULN2003) ou simulador com 4 LEDs
  vermelhos + resistores de 220 ohms no ESP32 / ESP8266 / Arduino.

 REQUISITOS OBRIGATORIOS ATENDEDOS:
  1. Menor passo angular possivel e maximo torque (Modo Meio-Passo / Half-Step de 8 fases).
  2. Nao utilizacao de bibliotecas facilitadoras de bobinas (como Stepper.h ou AccelStepper.h).
     O acionamento das bobinas e feito 100% manualmente via digitalWrite e tabela de estados.
  3. Padrao de chaveamento exato especificado (analogia do macaco pulando de galho em galho):
     - Passo 1: Bobina 1 = ON  | Bobina 2 = ON   (2 bobinas energizadas -> maximo torque)
     - Passo 2: Bobina 1 = OFF | Bobina 2 = ON   (1 bobina energizada  -> menor passo)
     - Passo 3: Bobina 2 = ON  | Bobina 3 = ON   (2 bobinas energizadas)
     - Passo 4: Bobina 2 = OFF | Bobina 3 = ON   (1 bobina energizada)
     - Passo 5: Bobina 3 = ON  | Bobina 4 = ON   (2 bobinas energizadas)
     - Passo 6: Bobina 3 = OFF | Bobina 4 = ON   (1 bobina energizada)
     - Passo 7: Bobina 4 = ON  | Bobina 1 = ON   (2 bobinas energizadas)
     - Passo 8: Bobina 4 = OFF | Bobina 1 = ON   (1 bobina energizada)
  4. Execucao de 1 volta completa de 360 graus.
  5. Ao completar os 360 graus:
     - Todas as 4 bobinas/LEDs sao DESLIGADAS (desenergizacao segura).
     - Pausa de 1,0 segundo (1000 ms).
     - Reinicio automatico de uma nova volta de 360 graus, ciclicamente ate desenergizar.
 ===================================================================
*/

#define MODO_SIMULACAO_LEDS 1

#if defined(ESP32)
  const int PINO_BOBINA_1 = 19;
  const int PINO_BOBINA_2 = 18;
  const int PINO_BOBINA_3 = 5;
  const int PINO_BOBINA_4 = 17;
#elif defined(ESP8266)
  const int PINO_BOBINA_1 = 14; // D5
  const int PINO_BOBINA_2 = 12; // D6
  const int PINO_BOBINA_3 = 13; // D7
  const int PINO_BOBINA_4 = 15; // D@
#else
  const int PINO_BOBINA_1 = 8;
  const int PINO_BOBINA_2 = 9;
  const int PINO_BOBINA_3 = 10;
  const int PINO_BOBINA_4 = 11;
#endif

#if MODO_SIMULACAO_LEDS
  const int TOTAL_PASSOS_VOLTA = 64;
  const unsigned long TEMPO_ENTRE_PASSOS_MS = 30;
#else
  const int TOTAL_PASSOS_VOLTA = 4096;
  const unsigned long TEMPO_ENTRE_PASSOS_MS = 2;
#endif

const unsigned long TEMPO_PAUSA_ENTRE_VOLTAS_MS = 1000;

const uint8_t TABELA_HALF_STEP[8][4] = {
  { 1, 1, 0, 0 }, // Fase 0: B1 ON, B2 ON  (2 ligadas -> Alto Torque)
  { 0, 1, 0, 0 }, // Fase 1: B1 OFF, B2 ON  (1 ligada  -> Menor Passo)
  { 0, 1, 1, 0 }, // Fase 2: B2 ON, B3 ON  (2 ligadas -> Alto Torque)
  { 0, 0, 1, 0 }, // Fase 3: B2 OFF, B3 ON  (1 ligada  -> Menor Passo)
  { 0, 0, 1, 1 }, // Fase 4: B3 ON, B4 ON  (2 ligadas -> Alto Torque)
  { 0, 0, 0, 1 }, // Fase 5: B3 OFF, B4 ON  (1 ligada  -> Menor Passo)
  { 1, 0, 0, 1 }, // Fase 6: B4 ON, B1 ON  (2 ligadas -> Alto Torque)
  { 1, 0, 0, 0 }  // Fase 7: B4 OFF, B1 ON  (1 ligada  -> Menor Passo)
};

void aplicarFaseBobinas(int indiceFase) {
  digitalWrite(PINO_BOBINA_1, TABELA_HALF_STEP[indiceFase][0]);
  digitalWrite(PINO_BOBINA_2, TABELA_HALF_STEP[indiceFase][1]);
  digitalWrite(PINO_BOBINA_3, TABELA_HALF_STEP[indiceFase][2]);
  digitalWrite(PINO_BOBINA_4, TABELA_HALF_STEP[indiceFase][3]);
}

void desenergizarTodasBobinas() {
  digitalWrite(PINO_BOBINA_1, LOW);
  digitalWrite(PINO_BOBINA_2, LOW);
  digitalWrite(PINO_BOBINA_3, LOW);
  digitalWrite(PINO_BOBINA_4, LOW);
}

void executarVoltaCompleta360() {
  Serial.println("Iniciando rotacao de 360 graus em Meio-Passo...");
  for (int passo = 0; passo < TOTAL_PASSOS_VOLTA; passo++) {
    int faseAtual = passo % 8;
    aplicarFaseBobinas(faseAtual);
    delay(TEMPO_ENTRE_PASSOS_MS);
  }
  Serial.println("Volta de 360 graus concluida com sucesso!");
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("FIAP 2022 - Controle Manual de Motor de Passo (Half-Step)");

  pinMode(PINO_BOBINA_1, OUTPUT);
  pinMode(PINO_BOBINA_2, OUTPUT);
  pinMode(PINO_BOBINA_3, OUTPUT);
  pinMode(PINO_BOBINA_4, OUTPUT);

  desenergizarTodasBobinas();
  delay(500);
}

void loop() {
  executarVoltaCompleta360();
  desenergizarTodasBobinas();
  Serial.println("Bobinas e LEDs apagados. Pausa de 1s...");
  delay(TEMPO_PAUSA_ENTRE_VOLTAS_MS);
}
