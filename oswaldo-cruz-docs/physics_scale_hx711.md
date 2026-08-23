# Projeto de Balança Digital com Arduino (HX711) e Estudo de Células de Carga
## Relatório Técnico: Física dos Sensores e Implementação de Hardware

Este documento apresenta a análise física de deformação mecânica e o projeto de circuitos embarcados para a criação de uma balança digital de alta precisão integrada ao exoesqueleto de reabilitação. O objetivo é mensurar a força física exercida pelos membros do paciente no suporte do equipamento.

---

### 1. Processo Escolhido e Limite Máximo de Carga
*   **Aplicação:** Medição de força de reação e peso residual aplicada pelas pernas do paciente no suporte do exoesqueleto robótico durante o repouso e marcha.
*   **Limite Máximo de Carga:** Configurado para suportar até **100 kgf (quilogramas-força)**, garantindo ampla margem de segurança para pacientes de diversos portes físicos.

---

### 2. Física das Células de Carga e Força Elástica (Lei de Hooke)
A célula de carga utilizada baseia-se na aplicação de **Strain Gages** (extensômetros elétricos) colados a um bloco metálico flexível (geralmente alumínio aeronáutico). 

Quando uma força $F$ é aplicada à balança, o bloco metálico sofre uma deformação elástica microscópica. Esta deformação é diretamente proporcional à força exercida, obedecendo à **Lei de Hooke**:

$$F_e = -k \cdot x$$

Onde:
*   **$F_e$ (Força Elástica):** Força de reação restauradora exercida pelo metal para compensar a deformação.
*   **$k$ (Constante Elástica do Material):** Depende da geometria do bloco de alumínio e do módulo de Young do metal.
*   **$x$ (Deformação/Deslocamento linear):** A variação dimensional sofrida pelo metal sob tração ou compressão.

#### Diagrama de Força sobre a Célula de Carga
```
           Força Aplicada (F)
                ↓
      ┌──────────────────┐
      │   Metal Flexível │ ─── Extensômetros sofrem tração/compressão
      └──────────────────┘
                ↑
         Força Elástica (Fe = -k.x)
```
A deformação física altera microscopicamente a resistência elétrica dos extensômetros dispostos em uma **Ponte de Wheatstone**. A variação de tensão em milivolts na ponte é então lida e amplificada pelo CI **HX711**.

---

### 3. Escolha da Célula de Carga e Componentes
Selecionamos uma célula de carga tipo **Single Point (Célula de cisalhamento/barra)** com capacidade máxima de **100kg**, modelo **YZC-161B** (ou similar industrial), devido à sua alta estabilidade sob cargas estáticas e dinâmicas.

---

### 4. Circuito de Integração (Arduino + HX711)
O **HX711** é um conversor analógico-digital de 24 bits específico para balanças. Ele se comunica com o microcontrolador através de uma interface serial simples (Clock e Data).

#### Pinagem e Conexão:
*   **Célula de Carga (Cores padrão):** Vermelho (Exc+), Preto (Exc-), Verde (Sig+), Branco (Sig-) conectados às entradas **A+, A-, E+, E-** do HX711.
*   **HX711 para Arduino:**
    *   VCC ➔ 5V
    *   GND ➔ GND
    *   DT (Data) ➔ Pino Digital 3
    *   SCK (Clock) ➔ Pino Digital 2

---

### 5. Código-Fonte Completo para o Arduino
O programa abaixo realiza a calibração, tara inicial e a leitura em tempo real da massa medida em quilogramas (kg).

```cpp
#include "HX711.h"

// Definição dos pinos de conexão do HX711
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;

HX711 scale;

// Fator de calibração obtido empiricamente com um peso conhecido
// Ajuste esse valor até a leitura corresponder ao peso real colocado
float calibration_factor = 22340.0; 

void setup() {
  Serial.begin(9600);
  Serial.println("Inicializando a Calibracao da Balanca...");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  // Executa a tara automática (zera a balança com o peso do suporte próprio)
  scale.tare(); 
  Serial.println("Tara realizada. Balanca pronta para leitura.");
  
  scale.set_scale(calibration_factor); 
}

void loop() {
  if (scale.is_ready()) {
    // Lê a média de 10 amostras consecutivas
    float weight = scale.get_units(10); 
    
    Serial.print("Peso Medido: ");
    Serial.print(weight, 3); // Exibe com 3 casas decimais
    Serial.println(" kg");
  } else {
    Serial.println("Erro: HX711 nao encontrado ou desconectado.");
  }
  
  delay(500); // Aguarda 500ms para a próxima leitura
}
```
