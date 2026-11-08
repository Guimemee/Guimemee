# PROJETO INTEGRADO DE ENGENHARIA DA COMPUTAÇÃO - FIAP 2022
## CHALLENGE HOSPITAL ALEMÃO OSWALDO CRUZ
### Exoesqueleto Robótico de Membros Inferiores para Reabilitação Patelofemoral com Interface Cérebro-Máquina (BCI) e Telemetria IoT

---

## 1. DELIMITAÇÃO DO PROBLEMA E CONCEPÇÃO BIOMÉDICA

### 1.1 Descrição Objetiva do Problema
O problema central abordado é o processo lento, doloroso e com alto índice de recidiva na **reabilitação pós-cirúrgica de fraturas e lesões na articulação patelofemoral do joelho**. Tais patologias decorrem de traumas de alto impacto, fraturas de patela, lesões de cartilagem troclear ou processos degenerativos em idosos e atletas de rendimento.

As principais dificuldades clínicas observadas na fisioterapia convencional são:
1. **Atrofia Muscular Rápida e Rigidez Articular:** A imobilização do membro inferior causa hipotrofia severa do quadríceps e retração capsular, exigindo mobilização precoce passiva e ativa.
2. **Subjetividade na Medição do Progresso:** Na clínica tradicional, a amplitude de movimento (ADM) e a força muscular são mensuradas manualmente por goniômetros manuais de forma esporádica, sem registro contínuo e objetivo de dados.
3. **Falta de Monitoramento de Fadiga e Dor:** Exercícios que ultrapassam o limiar doloroso do paciente provocam sobrecarga patelar, inflamação e risco de rompimento ligamentar ou falha da osteossíntese.
4. **Ausência de Comparabilidade Histórica:** Dificuldade em cruzar e comparar o desempenho cinemático e de esforço entre as sessões de fisioterapia consecutivas do paciente.

### 1.2 Esboço da Solução Proposta
A solução desenvolvida consiste em uma **órtese robótica ativa motorizada para membro inferior (articulação do joelho)**, composta por:
* **Estrutura Mecânica Articulada:** Braço e antebraço de sustentação em alumínio/MDF naval acoplados lateralmente à coxa e tíbia do paciente.
* **Atuador Rotacional de Passo:** Motor de passo acoplado a redutor e mancal axial para realizar a movimentação controlada de flexo-extensão.
* **Sensor de Angulação Absoluta:** Potenciômetro linear de precisão / encoder absoluto alinhado concentricamente ao eixo bicondilar do fêmur.
* **Célula de Carga com Strain Gauge:** Medição da força e do peso descarregado pelo membro durante o exercício.
* **Interface Cérebro-Máquina (BCI - NeuroSky MindWave):** Monitoramento contínuo da atenção, foco e indicadores indiretos de estresse/dor através de ondas cerebrais (EEG).
* **Unidade Embarcada de Telemetria (ESP32):** Controle em tempo real, interrupção de segurança e envio automático de telemetria para o prontuário eletrônico.

`
       ESQUEMA MECÂNICO E ARQUITETURA DE CONTROLE DO EXOESQUELETO
       
       [ CÓRTEX CEREBRAL (Fp1) ]
                  │
                  ▼ (Bluetooth EEG - eSense)
       ┌────────────────────────┐
       │   NeuroSky MindWave    │ ───► [ Atenção / Dor / Piscada ]
       └────────────────────────┘                    │
                                                     ▼
       ┌─────────────────────────────────────────────────────────────┐
       │             MICROCONTROLADOR MESTRE (ESP32)                 │
       │  - Máquina de Estados Não-Bloqueante (millis)               │
       │  - Filtro Digital de Média Móvel (12 bits ADC)              │
       │  - Supervisão de Segurança e Limites Angulares [90°, 180°]  │
       └─────────────────────────────────────────────────────────────┘
             ▲                                             ▲
             │                                             │ (Pulsos Digitais)
             │ (Leitura Analógica)                         ▼
       ┌──────────────┐                            ┌──────────────┐
       │ Potenciômetro│                            │ Driver       │
       │ Linear 5k    │                            │ ULN2003      │
       │ Eixo Joelho  │                            └──────────────┘
       └──────────────┘                                    │
                                                           ▼
       ┌──────────────┐                            ┌──────────────┐
       │ Célula Carga │                            │ Motor Passo  │
       │ + CI HX711   │ ───► [ Medição Força ]     │ 28BYJ-48     │
       └──────────────┘                            └──────────────┘
                                                           │
                                                           ▼
                                                [ Órtese Articular ]
                                                Ângulo: 90° a 180°
`

### 1.3 Tipo de Exoesqueleto Desenvolvido
* **Classificação:** Exoesqueleto Ativo / Assistivo de Membro Inferior, Monoarticular para a Articulação do Joelho (*Active Knee Orthosis*).
* **Modo de Operação:** Movimentação Passiva Contínua (CPM - *Continuous Passive Motion*) combinada com Modo Ativo-Assistido comandado por intenção motora e foco do paciente captados via BCI.

### 1.4 Dispositivo de Entrada BCI: NeuroSky MindWave
* **Princípio de Funcionamento:** Dispositivo vestível de Eletroencefalografia (EEG) de canal único não-invasivo.
* **Topologia de Eletrodos:** Eletrodo de contato seco em liga metálica posicionado no polo frontal esquerdo (posição **Fp1** do Sistema Internacional 10-20), com eletrodo de referência e terra no clipe do lóbulo da orelha.
* **Chip de Processamento:** Processador integrado ThinkGear ASIC, responsável por amplificar os microvolts cerebrais, aplicar filtros Notch (50/60 Hz) e transformada rápida de Fourier (FFT).
* **Espectro de Frequências:** Faixas Delta (0.5 - 2.75 Hz), Theta (3.5 - 6.75 Hz), Alpha (7.5 - 12.5 Hz), Beta (13 - 29.75 Hz) e Gamma (31 - 49.75 Hz).
* **Métricas eSense:** Algoritmo patenteado que sintetiza a atividade em:
  * **Atenção (eSense Attention):** Escala de 0 a 100 indicando foco e esforço mental ativo.
  * **Meditação (eSense Meditation):** Escala de 0 a 100 indicando calma e relaxamento.
  * **Detecção de Piscada (Blink Detection):** Pico eletromiográfico facial utilizado como gatilho de parada intencional de emergência.
* **Protocolo de Comunicação:** UART assíncrona serial / Bluetooth SPP (Baud rate de 57.600 bps padrão ou 9.600 bps), emitindo pacotes estruturados com soma de verificação (Checksum).

---

## 2. FÍSICA E METROLOGIA (ECFO - PROF. NIVALDEX)

### 2.1 Grandezas Físicas Relevantes
1. **Deslocamento Angular ($	heta$):** Posição relativa entre a tíbia e o fêmur expressa em graus (\circ$) e radianos ($	ext{rad}$).
2. **Torque Articular ($	au$):** Momento resultante exercido pelo atuador e pelo membro em torno do centro instantâneo de rotação (CIR), medido em Newton-metro ($	ext{N}\cdot	ext{m}$).
3. **Força Normal e Cisalhante ($):** Força gerada pelo contato da haste mecânica contra a perna do paciente, medida em Newtons ($	ext{N}$).

### 2.2 Limites Operacionais Seguros da Articulação [90°, 180°]
Na reabilitação patelofemoral, o contato entre a faceta articular da patela e os côndilos femorais atinge picos de pressão compressiva conforme a flexão ultrapassa 90°.
* **$	heta = 90^\circ$ ($rac{\pi}{2}	ext{ rad}$):** Posição de flexão máxima permitida nas fases 1 e 2 do pós-operatório. Flexões além de 90° geram estresse cisalhante excessivo no tendão patelar e no enxerto ligamentar.
* **$	heta = 180^\circ$ ($\pi	ext{ rad}$):** Extensão anatômica completa da perna. O sistema mecânico e o software possuem trava física e lógica para impedir hiperextensão ($	heta > 180^\circ$), o que causaria lesão do ligamento cruzado posterior e hiperextensão capsular.

### 2.3 Análise de Incerteza e Ruído em Sensores
* **Potenciômetro Analógico:** Sujeito a ruído de alta frequência causado por interferência eletromagnética (EMI) dos motores, ripple da fonte e atrito elétrico da pista de grafite. O ruído gera flutuações de até $\pm 45	ext{ mV}$ na leitura do ADC.
* **Filtragem Digital Aplicada:** Implementação de um **Filtro de Média Móvel (Moving Average Filter)** com janela de 10 amostras no firmware:
  ar{V}[n] = rac{1}{M}\sum_{k=0}^{M-1} V[n-k], \quad M = 10
* **Calibração de 2 Pontos:**
  1. Calibração do Ponto A: Joelho a ^\circ \implies 	ext{ADC}_{90} = 1024$.
  2. Calibração do Ponto B: Joelho a ^\circ \implies 	ext{ADC}_{180} = 3072$.
  	heta(x) = 90^\circ + rac{(x - 	ext{ADC}_{90}) \cdot (180^\circ - 90^\circ)}{	ext{ADC}_{180} - 	ext{ADC}_{90}}
* **Erro Aceitável:** O erro máximo permissível para fisioterapia articular é de {max} = \pm 2^\circ$. Com a resolução de 12 bits do ESP32 (4096 divisões), a resolução teórica é de $pprox 0,044^\circ/	ext{LSB}$, plenamente adequada às normas da Sociedade Internacional de Biomecânica (ISB).

---

## 3. CIRCUITOS DIGITAIS & LÓGICA (PROF. CHRISTIAM SEGUNDO)

### 3.1 Entradas Lógicas e Algoritmo Procedimental
* **$ (Atenção eSense):**  = 1$ se Atenção $\ge 50$; senão $.
* **$ (Meditação eSense):**  = 1$ se Meditação $\ge 50$; senão $.
* **$ (Blink de Parada / Botão de Emergência):**  = 1$ se piscada forte detectada ou botão pressionado; senão $.
* **$ (Sensor de Limite Seguro):**  = 1$ se ^\circ \le 	heta \le 180^\circ$; senão $ (trava por ultrapassagem de curso).

### 3.2 Tabela Verdade do Sistema de Atuação ($)
A saída  = 1$ habilita o acionamento do motor de passo.

| A (Atenção) | M (Meditação) | B (Parada Emergência) | L (Limite Seguro) | Y (Atuação do Motor) | Diagnóstico Clínico / Comportamento |
|:---:|:---:|:---:|:---:|:---:|:---|
| 0 | 0 | 0 | 1 | **0** | Paciente desconcentrado; atuador em espera segura |
| 0 | 1 | 0 | 1 | **0** | Apenas relaxado sem foco motor; sem movimento |
| 1 | 0 | 0 | 1 | **0** | Atenção ativa mas em tensão; aguarda estabilização |
| 1 | 1 | 0 | 1 | **1** | **Condição Ideal: Foco e relaxamento em faixa segura; Motor Ativo** |
| 1 | 1 | 1 | 1 | **0** | Paciente executou comando de interrupção (Blink/Botão) |
| X | X | X | 0 | **0** | **Interrupção Crítica: Fora dos limites angulares seguros** |

### 3.3 Equação Booleana Simplificada e Portas Lógicas
Y = A \cdot M \cdot ar{B} \cdot L
O circuito é sintetizado por:
1. Uma porta inversora (NOT) na entrada $.
2. Uma porta lógica AND quádrupla combinando $, $, $ar{B}$ e $.

---

## 4. PROJETO DE BALANÇA DIGITAL (CÉLULA DE CARGA + HX711)

### 4.1 Princípio de Medição de Massa e Força Elástica
Para aferir a massa dos componentes mecânicos do protótipo e mensurar a força de reação exercida pelo membro sobre a órtese, utiliza-se uma célula de carga resistiva baseada na **Lei de Hooke**:
F_e = k \cdot \Delta x
Onde a força mecânica aplicada deforma microscopicamente a estrutura de alumínio da viga em balanço. A deformação $\Delta x$ altera a resistência $ dos 4 extensômetros elétricos dispostos em uma **Ponte de Wheatstone balanceada**:
\Delta V_{out} = V_{in} \cdot \left(rac{\Delta R}{R}ight)
Essa microtensão em milivolts é amplificada com ganho selecionável (128x) e digitalizada em 24 bits pelo conversor **HX711**.

### 4.2 Diagrama Esquemático de Conexão
`
    [ Célula de Carga ]                       [ Módulo HX711 ]             [ Microcontrolador ]
    Fio Vermelho (E+)  ───────────────────────► E+ (Excitação +)
    Fio Preto    (E-)  ───────────────────────► E- (Excitação -)
    Fio Verde    (A+)  ───────────────────────► A+ (Sinal +)
    Fio Branco   (A-)  ───────────────────────► A- (Sinal -)
                                                VCC ────────────────────────► 5V / 3.3V
                                                GND ────────────────────────► GND
                                                DT  (Data) ─────────────────► GPIO 3
                                                SCK (Clock) ────────────────► GPIO 2
`

---

## 5. IOT & PROTOCOLO MQTT NA SAÚDE DIGITAL (INDÚSTRIA 4.0)

### 5.1 O Protocolo MQTT na Tele-Reabilitação
O **MQTT (Message Queuing Telemetry Transport)** opera sobre TCP/IP no modelo **Publish/Subscribe**. É o padrão de facto da Indústria 4.0 e da área biomédica devido a:
* **Footprint Mínimo:** Cabeçalho de pacote de apenas 2 bytes, ideal para transmissão contínua sem consumir banda ou drenar a bateria do exoesqueleto.
* **QoS (Quality of Service):**
  * *QoS 0:* Telemetria angular instantânea a 10 Hz (dispensa confirmação).
  * *QoS 1:* Contagem de repetições e encerramento de ciclo (garante entrega no prontuário).
  * *QoS 2:* Eventos de alarme de dor e acionamento de parada de emergência (garantia exata de entrega sem duplicatas).
* **Tópicos Hierárquicos de Saúde:**
  * hospital/blocoB/leito12/exoesqueleto/telemetria
  * hospital/blocoB/leito12/exoesqueleto/alarmes
  * hospital/blocoB/leito12/exoesqueleto/sessao_anterior

---

## 6. RESOLUÇÃO DIFERENCIADA DE PROBLEMAS (RDP - PROF. ISMAEL)

### 6.1 Entregável 1: Modelagem Linear de Produção e Ponto de Equilíbrio
* **Custo Variável Unitário:**  = 	ext{R\$} 535,00$ por exoesqueleto.
* **Custo Fixo Mensal:**  = 	ext{R\$} 46.750,00$.
* **Preço de Venda Unitário:**  = 	ext{R\$} 785,00$.

#### Modelos Matemáticos:
1. **Custo Total Mensal:**
   C(N) = 535N + 46750
2. **Receita Bruta Total:**
   R(N) = 785N
3. **Lucro Líquido Total:**
   L(N) = R(N) - C(N) = 785N - (535N + 46750) = 250N - 46750
4. **Ponto de Equilíbrio (Break-even Point):**
   L(N) = 0 \implies 250N = 46750 \implies N = rac{46750}{250} = 187 	ext{ unidades}
   * **Margem de Contribuição:** $	ext{R\$} 250,00$ por unidade.
   * **Interpretação:** Abaixo de 187 unidades produzidas no mês há prejuízo operacional; a partir da 188ª unidade, a empresa opera em faixa de lucro líquido positivo.

---

### 6.2 Entregável 2: Modelagem Quadrática com Demanda com Preço Flexível
Neste cenário de mercado, o preço unitário diminui conforme a quantidade ofertada aumenta:
* **Equação de Demanda (Preço Unitário):** (N) = 860 - N$
* **Custo Total Operacional:** (N) = 640N + 7200$

#### Dedução dos Modelos:
1. **Receita Total Mensal:**
   R(N) = N \cdot P(N) = N(860 - N) = -N^2 + 860N
2. **Lucro Líquido Total:**
   L(N) = R(N) - C(N) = (-N^2 + 860N) - (640N + 7200)
   L(N) = -N^2 + 220N - 7200

#### Resolução Passo a Passo:
1. **Pontos de Lucro Nulo (Raízes da Parábola (N) = 0$):**
   -N^2 + 220N - 7200 = 0 \iff N^2 - 220N + 7200 = 0
   \Delta = b^2 - 4ac = (-220)^2 - 4(1)(7200) = 48400 - 28800 = 19600
   \sqrt{\Delta} = \sqrt{19600} = 140
   N = rac{-(-220) \pm 140}{2(1)} = rac{220 \pm 140}{2}
   N_1 = rac{220 - 140}{2} = rac{80}{2} = 40 	ext{ unidades}
   N_2 = rac{220 + 140}{2} = rac{360}{2} = 180 	ext{ unidades}

2. **Intervalo para Lucro Estritamente Positivo ((N) > 0$):**
   Como a concavidade é voltada para baixo ( = -1 < 0$), o lucro é estritamente positivo no interior das raízes:
   40 < N < 180
   Em quantidades inteiras de produção:
   41 \le N \le 179 	ext{ robôs/mês}

3. **Vértice da Parábola (Produção Ótima de Lucro Máximo):**
   N_v = -rac{b}{2a} = -rac{220}{2(-1)} = 110 	ext{ robôs}

4. **Valor do Lucro Máximo Mensal:**
   L(110) = -(110)^2 + 220(110) - 7200 = -12100 + 24200 - 7200 = 	ext{R\$} 4.900,00

5. **Preço Ótimo de Venda para Maximizar o Lucro:**
   P(110) = 860 - 110 = 	ext{R\$} 750,00 	ext{ por exoesqueleto}

---

## 7. CÓDIGO REFATORADO E ARQUITETURA DE FIRMWARE (ESP32)

O código desenvolvido para a placa microcontroladora ESP32 soluciona todas as limitações identificadas em protótipos acadêmicos anteriores:
1. **Zero Delays Bloqueantes:** Controle temporal integral com millis().
2. **Filtro Digital Estável:** Média móvel no ADC de 12 bits com atenuação adequada para 3.3V.
3. **Mapeamento Angular Rígido:** Limites de segurança biomecânica de ^\circ$ a ^\circ$.
4. **Telemetria Direta com Prontuário:** Envio automático via Bluetooth HID (BleKeyboard) tabulado para preenchimento de prontuários em tempo real no Excel/Hospitalar.
5. **Arquivo Fonte Oficial:** Disponível integralmente em:
   D:\Github_Guimemee\Guimemee\fiap-challenges\firmware_esp32_exoesqueleto.ino
