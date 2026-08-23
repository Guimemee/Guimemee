# Resolução do Challenge Hospital Alemão Oswaldo Cruz - 2022
## SPRINT 1 - Relatório de Desenvolvimento e Modelagem

---

### 1. Resolução Diferenciada de Problemas (Matemática Financeira e Modelagem Linear)

#### Contexto e Dados:
*   Custo Unitário de Produção (variável): $C_u = \text{R\$} 535,00$ por robô.
*   Custo Fixo Mensal (aluguel, salários, energia, impostos): $C_f = \text{R\$} 46.750,00$.
*   Preço de Venda Unitário: $P_v = \text{R\$} 785,00$ por robô.
*   Quantidade produzida e vendida no mês: $N$.

---

#### [QUESTÃO 1] Modelo Matemático do Custo Mensal Total $C(N)$
O Custo Total é a soma do Custo Fixo com o Custo Variável (que depende da quantidade $N$ produzida).

$$C(N) = C_u \cdot N + C_f$$
$$C(N) = 535N + 46750$$

*   **Significado:** Representa a saída de caixa total necessária para fabricar $N$ unidades do robô em um mês.

---

#### [QUESTÃO 2] Modelo Matemático da Receita Mensal Total $R(N)$
A Receita representa todo o capital que entra na empresa a partir da venda das unidades produzidas.

$$R(N) = P_v \cdot N$$
$$R(N) = 785N$$

*   **Significado:** Representa a entrada bruta de capital referente à venda de $N$ robôs.

---

#### [QUESTÃO 3] Modelo Matemático do Lucro Mensal Total $L(N)$
O Lucro é a diferença entre a Receita Total e o Custo Total.

$$L(N) = R(N) - C(N)$$
$$L(N) = 785N - (535N + 46750)$$
$$L(N) = 250N - 46750$$

*   **Significado:** Representa o ganho líquido real da empresa após abater todos os custos operacionais de produção.

---

#### [QUESTÃO 4] Ponto de Equilíbrio (Breakeven Point) e Análise Gráfica
O Ponto de Equilíbrio ocorre quando a Receita é exatamente igual ao Custo Total, resultando em um Lucro igual a zero ($L(N) = 0$).

$$L(N) = 0 \implies 250N - 46750 = 0$$
$$250N = 46750$$
$$N = \frac{46750}{250} = 187 \text{ unidades}$$

##### Análise do Ponto de Equilíbrio:
*   **Zona de Prejuízo ($N < 187$):** Se a empresa produzir e vender menos de 187 robôs por mês, a receita obtida não cobrirá as despesas fixas e variáveis, resultando em saldo negativo.
*   **Ponto de Equilíbrio ($N = 187$):** A operação se paga exatamente. A receita de R$ 146.795,00 cobre os R$ 146.795,00 de custo operacional.
*   **Zona de Lucro ($N > 187$):** A partir da 188ª unidade vendida, cada robô adicional gera um lucro marginal líquido de R$ 250,00 (Margem de Contribuição).

##### Esboço Gráfico Conceitual:
```
Valor (R$)
  ^
  |                                 / Receita R(N) = 785N
  |                                /
  |                               /
  |                              /
  |                             / 
  |                            /-- Ponto de Equilíbrio (187, 146.795)
  |                           /  
  |                          /-- Custo C(N) = 535N + 46750
  |                         /  
  |   _____________________/   
  |  |                    /
  |  |                   /
  |  |                  /
  +--+-----------------+----------------------> Quantidade (N)
     0                187
```

---

### 2. Digital Circuits & Logic (Sistemas de Controle e EEG)

#### 1) Problema Identificado:
Dificuldade na reabilitação motora e readaptação de pacientes que sofreram lesões medulares parciais ou acidentes vasculares cerebrais (AVC). A perda de controle neuromuscular nos membros inferiores reduz drasticamente a autonomia. O grupo estudará o desenvolvimento de órteses ativas inteligentes para auxiliar no treino de marcha.

#### 2) Esboço da Solução:
Um exoesqueleto robótico motorizado controlado por impulsos cerebrais (EEG) e monitorado em tempo real por uma rede de sensores de força colocados nas solas dos pés para medir a distribuição do peso.

#### 3) Tipo de Exoesqueleto:
Exoesqueleto ativo para membros inferiores com atuadores rotacionais nas articulações do quadril e joelho.

#### 4) Dispositivo de Entrada (Neurosky MindWave):
*   **Características Lógicas:** O Neurosky MindWave é um headset de eletroencefalografia (EEG) de canal único não invasivo. O eletrodo principal é posicionado na testa (Fp1) e a referência na orelha. Ele filtra ruídos musculares e elétricos e digitaliza os sinais de microvolts da atividade cerebral na banda de 0.5 a 100Hz.
*   O hardware interno aplica algoritmos matemáticos patenteados (eSense) para classificar o foco mental do usuário em dois estados (Atenção e Meditação) em uma escala numérica de 0 a 100, transmitidos de forma serial via Bluetooth para o microcontrolador do exoesqueleto.

---

### 3. Indústria 4.0: Resumo e Integração de Exoesqueletos

#### O Papel dos Exoesqueletos na Indústria 4.0 (Resumo Técnico)

A Indústria 4.0 preconiza a fusão de sistemas físicos e digitais (Sistemas Ciber-Físicos - CPS), a conectividade IoT e a automação de alta performance. Nesse ambiente altamente dinâmico, o fator humano continua sendo indispensável, porém a integridade física do trabalhador é um ponto de atenção crítico. É nesse cenário que os **exoesqueletos industriais** surgem como uma das principais inovações ergonômicas e produtivas.

Os exoesqueletos são dispositivos mecânicos vestíveis que aumentam, atenuam ou auxiliam a capacidade física humana. Na manufatura moderna, trabalhadores realizam tarefas repetitivas, levantamento de cargas pesadas ou posturas estressantes (como montagens aéreas em linhas automobilísticas). A implementação de exoesqueletos ativos (motorizados) ou passivos (com molas e amortecedores) atua reduzindo o esforço muscular em até 40%, prevenindo diretamente Distúrbios Osteomusculares Relacionados ao Trabalho (DORT).

Do ponto de vista da **Indústria 4.0**, o exoesqueleto não é apenas uma órtese passiva; ele é integrado como um **nó IoT ativo**. Equipados com sensores de torque, acelerômetros e batimentos cardíacos, esses dispositivos transmitem dados operacionais em tempo real para servidores de nuvem industrial via protocolos leves de telemetria. 

Estes dados são analisados por algoritmos de Machine Learning para monitorar a fadiga do operador e ajustar dinamicamente o suporte mecânico fornecido pelos atuadores. Assim, os exoesqueletos fundem-se perfeitamente ao conceito de **Sistemas Ciber-Físicos**, onde a biologia humana e a mecânica digital trabalham de forma simbiótica para criar um ambiente fabril seguro, ergonômico e altamente eficiente.
