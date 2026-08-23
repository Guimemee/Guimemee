# Desenvolvimento de Exoesqueleto Controlado por Interface Cérebro-Máquina (NeuroSky MindWave)
## Relatório Técnico: Circuitos Digitais e Delimitação Lógica da Solução

Este documento apresenta a especificação lógica e a arquitetura de circuitos digitais desenvolvida para integrar o sensor de EEG **NeuroSky MindWave Mobile** com o módulo de processamento do exoesqueleto robótico de reabilitação.

---

### 1. Entradas Lógicas do Sistema
Para que o exoesqueleto se movimente ou interrompa seu curso por segurança, o sinal bruto de EEG é processado pela API proprietária da NeuroSky (eSense) e convertido em valores lógicos. Os valores possíveis de entrada e saída são:

*   **A (Atenção - eSense):** Valor inteiro de 0 a 100. Considerado lógico `1` se Atenção &ge; 50 (limiar de ativação), senão `0`.
*   **M (Meditação/Relaxamento - eSense):** Valor inteiro de 0 a 100. Considerado lógico `1` se Meditação &ge; 50, senão `0`.
*   **B (Detecção de Piscada - Blink):** Força da piscada de 1 a 255. Considerado lógico `1` se força &ge; 80, indicando uma piscada consciente deliberada (parada de emergência), senão `0`.

#### Algoritmo Procedimental Simplificado (Python)
```python
def processar_sinais_eeg(attention, meditation, blink_strength):
    # Limiares de ativação
    LIMIT_ATTENTION = 50
    LIMIT_MEDITATION = 50
    LIMIT_BLINK = 80
    
    # Conversão para lógica binária
    A = 1 if attention >= LIMIT_ATTENTION else 0
    M = 1 if meditation >= LIMIT_MEDITATION else 0
    B = 1 if blink_strength >= LIMIT_BLINK else 0
    
    # Lógica de controle do atuador
    # O motor só liga se houver Atenção e Meditação juntas,
    # contanto que o usuário NÃO pisque forte (botão de parada física)
    motor_ativado = (A and M) and not B
    
    # Retorna o comando para os drivers de potência do motor
    return "MOTOR_ON" if motor_ativado == 1 else "MOTOR_OFF"
```

---

### 2. Tabela Verdade do Sistema Digital
O comportamento do circuito de controle combinacional pode ser resumido pela tabela verdade abaixo, onde a saída **Y** representa o estado do motor (`1` = Ligado, `0` = Desligado).

| A (Atenção) | M (Meditação) | B (Piscada/Parada) | Y (Atuação do Motor) | Status do Paciente |
|:---:|:---:|:---:|:---:|:---|
| 0 | 0 | 0 | **0** | Desconcentrado e relaxado |
| 0 | 0 | 1 | **0** | Desconcentrado, relaxado e piscando (Parado) |
| 0 | 1 | 0 | **0** | Apenas relaxado |
| 0 | 1 | 1 | **0** | Apenas relaxado e piscando |
| 1 | 0 | 0 | **0** | Apenas focado |
| 1 | 0 | 1 | **0** | Apenas focado e piscando |
| 1 | 1 | 0 | **1** | **Foco ideal (Ativação e Movimento)** |
| 1 | 1 | 1 | **0** | Foco ideal, mas executou comando de parada consciente |

#### Expressão Booleana Simplificada:
$$Y = A \cdot M \cdot \bar{B}$$

---

### 3. Testes de Condicionais Lógicas Evidenciados no Projeto
Como parte do protocolo de segurança clínica exigido para a aplicação no Hospital Oswaldo Cruz, a lógica do firmware implementa testes condicionais rígidos:

1.  **Validação de Conexão (PoorSignal):** Antes de ler as variáveis `A`, `M` e `B`, testa-se a qualidade do sinal do sensor (`PoorSignalQuality == 200` significa eletrodo desconectado). Se o sinal for ruim, o motor é desligado imediatamente via condicional lógica `if (signalQuality > 100) motor = 0;`.
2.  **Mapeamento de Histerese:** Para evitar ligar/desligar o motor em frequências oscilatórias rápidas (ruídos de sinal), implementa-se um atraso lógico (Debounce). O motor só altera o estado após o limiar lógico ser mantido estável por 5 iterações consecutivas.
3.  **Parada Lógica de Emergência:** A variável `B` atua como um interrupção prioritária (hardware interrupt no pino do Arduino). Sempre que `B == 1`, a execução principal é interrompida, forçando o motor para `0`.

---

### 4. Referências Científicas e Manuais de Apoio
Para maiores detalhes técnicos de calibração do sinal de ondas cerebrais, consulte os seguintes materiais:
*   [NeuroSky MindWave Mobile 3 - Manual Técnico de Engenharia (FCCID)](https://fccid.io/XG9MW3/User-Manual/Users-Manual-1546394)
*   [NeuroSky SDK & Recursos de EEG para Desenvolvedores](https://eastbaywellness.com.sg/neurosky-resources/)
*   [Estudo Experimental de Controle Robótico por Sinais de EEG - Rusu & Cristea (Semantic Scholar)](https://www.semanticscholar.org/paper/Experimental-Model-of-a-Robotic-Hand-Controlled-by-Ru%C8%99anu-Cristea/8b390b20ccc3b552787d7c9f6691dbe32739f781)
