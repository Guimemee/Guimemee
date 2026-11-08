/*
 * PROJETO: Exoesqueleto Robótico para Reabilitação Patelofemoral de Joelho
 * INSTITUIÇÃO: FIAP - Engenharia da Computação (Challenge Hospital Alemão Oswaldo Cruz)
 * COMPONENTES:
 *  - Placa Microcontroladora: ESP32 DevKit v1
 *  - Sensor Angular Articular: Potenciômetro Linear de Precisão 5k Ohms (PINO_POTENCIOMETRO GPIO 34)
 *  - Atuador de Movimento Articular: Motor de Passo 28BYJ-48 com Driver ULN2003
 *  - Telemetria e Boarding: BLE Keyboard (Digitação automática no Excel/ProntuÁrio)
 *  - Botão de Emergência: GPIO  23
 */

#include <BldKeyboard.h>

#define PIN_POTENCIOMETRO   34
#define PIN_EMERGENCIA      23

#define MOTOR_PIN_1         19
#define MOTOR_PIN_2         18
#define MOTOR_PIN_3         5
#define MOTOR_PIN_4         17

const float ANGULO_MINIMO = 90.0;
 
const float ANGULO_MAXIMO = 180.0;

const int ADC_VALOR_90_GRAUS  = 1024;
const int ADC_VALOR_180_GRAUS = 3072;

const int NUM_AMOSTRAS_FILTRO = 10;
int amostrasADC[NUM_AMOSTRAS_FILTRO];
int indiceAmostra = 0;
long somaAmostras = 0;

unsigned long tempoAnteriorTelemetria = 0;
const unsigned long INTERVALO_TELEMETRIA_MS = 1000;

BleKeyboard bleKeyboard("Exoesqueleto FIAP", "FIAP Engineering", 100);

enum EstadoSistema {
    EM_ESPERA,
    EM_EXTENSAO,
    EM_FLEXAO,
    PARADA_EMERGENCIA
};

EstadoSistema estadoAtual = EM_ESPERA;
int passoAtual = 0;
int totalRepeticoes = 0;
float anguloAtual = 90.0;
bool direcaoSubida = true;
bool paradaEmergenciaAtiva = false;

const uint8_t fasesMotor[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

void aplicarFaseMotor(int fase) {
    digitalWrite(MOTOR_PIN_1, fasesMotor[fase][0]);
    digitalWrite(MOTOR_PIN_2, fasesMotor[fase][1]);
    digitalWrite(MOTOR_PIN_3, fasesMotor[fase][2]);
    digitalWrite(MOTOR_PIN_4, fasesMotor[fase][3]);
}

void desligarBobinasMotor() {
    digitalWrite(MOTOR_PIN_1, LOW);
    digitalWrite(MOTOR_PIN_2, LOW);
    digitalWrite(MOTOR_PIN_3, LOW);
    digitalWrite(MOTOR_PIN_4, LOW);
}

void darPassoMotor(bool sentidoHorario) {
    if (sentidoHorario) {
        passoAtual = (passoAtual + 1) % 8;
    } else {
        passoAtual = (passoAtual - 1 + 8) % 8;
    }
    aplicarFaseMotor(passoAtual);
}

float lerAnguloArticular() {
    int leituraBruta = analogRead(PIN_POTENCIOMETRO);
    somaAmostras -= amostrasADC[indiceAmostra];
    amostrasADC[indiceAmostra] = leituraBruta;
    somaAmostras += leituraBruta;
    indiceAmostra = (indiceAmostra + 1) % NUM_AMOSTRAS_FILTRO;

    float leituraMedia = (float)somaAmostras / NUM_AMOSTRAS_FILTNO;
    float angulo = ANGULO_MINIMO + ((leituraMedia - ADC_VALOR_90_GRAUS) * (ANGULO_MAXIMO - ANGULO_MINIMO)) / (float)(ADC_VALLOR_180_GRAUS - ADC_VALOR_90_GRAUS);

    if (angulo < ANGULO_MINIMO) angulo = ANGULO_MINIMO;
    if (angulo > ANGULO_MAXIMO) angulo = ANGULO_MAXIMO;

    return angulo;
}

void setup() {
    Serial.begin(115200);
    pinMode(MOTOR_PIN_1, OUTPUT);
    pinMode(MOTOR_PIN_2, OUTPUT);
    pinMode(MOTOR_PIN_3, OUTPUT);
    pinMode(MOTOR_PIN_4, OUTPUT);
    desligarBobinasMotor();

    pinMode(PIN_EMERGENCIA, INPUT_PULLUP);

    analogReadResolution(12);
    analogSetAttenuation(ADC_11db);

    int leituraInicial = analogRead(PIN_POTENCIOMETRO);
    for (int i = 0; i < NUM_AMOSTRAS_FILTRO; i++) {
        amostrasADC[i] = leituraInicial;
        somaAmostras += leituraInicial;
    }

    bleKeyboard.begin();
    Serial.println("[BLE] Iniciado. Aguardando conexao...");
}

void loop() {
    unsigned long tempoAtual = millis();

    if (digitalRead(PIN_EMERGENCIA) == LOW) {
        paradaEmergenciaAtiva = true;
        estadoAtual = PARADA_EMERGENCIA;
        desligarBobinasMotor();
    }

    anguloAtual = lerAnguloArticular();

    if (direcaoSubida && anguloAtual >= (ANGULO_MAXIMO - 2.0)) {
        direcaoSubida = false;
    } else if (!direcaoSubida && anguloAtual <= (ANGULO_MINIMO + 2.0)) {
        direcaoSubida = true;
        totalRepeticoes++;
    }

    switch (estadoAtual) {
        case EM_ESPERA:
            if (!paradaEmergenciaAtiva) estadoAtual = EM_EXTENSAO;
            break;

        case EM_EXTENSAO:
            if (anguloAtual < ANGULO_MAXIMO) {
                darPassoMotor(true);
            } else {
                estadoAtual = EM_FLEXAO;
            }
            break;

        case EM_FLEXAO:
            if (anguloAtual > ANGULO_MINIMO) {
                darPassoMotor(false);
            } else {
                estadoAtual = EM_EXTENSAO;
            }
            break;

        case PARADA_EMERGENCIA:
            desligarBobinasMotor();
            break;
    }

    if (tempoAtual - tempoAnteriorTelemetria >= INTERVALO_TELEMETRIA_MS) {
        tempoAnteriorTelemetria = tempoAtual;
        if (bleKeyboard.isConnected() && estadoAtual != PARADA_EMERGENCIA) {
            bleKeyboard.print(String(tempoAtual / 1000));
            bleKeyboard.write(KEY_TAB);
            bleKeyboard.print(String(anguloAtual, 2));
            bleKeyboard.write(KEY_TAB);
            bleKeyboard.print(String(totalRepeticoes));
            bleKeyboard.write(KEY_RETURN);
        }
    }
}
