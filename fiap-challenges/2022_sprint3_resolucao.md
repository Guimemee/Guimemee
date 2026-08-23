# Resolução do Challenge Hospital Alemão Oswaldo Cruz - 2022
## SPRINT 3 - Relatório de Soluções e Códigos Embarcados

---

### 1. Resolução Diferenciada de Problemas (Otimização Matemática / Cálculo Diferencial)

#### Equação da Receita Mensal:
$$R(V) = -12V^4 + 256V^3 - 1440V^2 + 21000$$
Restrição do domínio: $0 \le V \le 12$, onde:
*   $R(V)$: Receita mensal em milhares de reais.
*   $V$: Preço de venda em dezenas de reais (ex: $V = 6 \implies \text{R\$} 60,00$).

---

#### [Questão 1] Determinar as Coordenadas dos Pontos Críticos da Função Receita
Para encontrar os pontos críticos, calculamos a primeira derivada da função receita $R'(V)$ e a igualamos a zero:

$$R'(V) = \frac{d}{dV}(-12V^4 + 256V^3 - 1440V^2 + 21000)$$
$$R'(V) = -48V^3 + 768V^2 - 2880V$$

Igualando a zero ($R'(V) = 0$):
$$-48V^3 + 768V^2 - 2880V = 0$$
Dividindo toda a equação por $-48$:
$$V(V^2 - 16V + 60) = 0$$

Isso nos dá três valores de $V$ que zeram a derivada:
1.  **$V = 0$** (ponto crítico de fronteira)
2.  Resolvendo a equação quadrática $V^2 - 16V + 60 = 0$ usando a fórmula de Bhaskara ou fatoração:
    $$(V - 10)(V - 6) = 0 \implies \mathbf{V = 6} \quad \text{e} \quad \mathbf{V = 10}$$

##### Coordenadas Completas dos Pontos Críticos (Calculando $R(V)$):
*   **Para $V = 0$:**
    $$R(0) = -12(0)^4 + 256(0)^3 - 1440(0)^2 + 21000 = 21000 \implies \mathbf{(0, 21000)}$$
*   **Para $V = 6$:**
    $$R(6) = -12(6^4) + 256(6^3) - 1440(6^2) + 21000$$
    $$R(6) = -12(1296) + 256(216) - 1440(36) + 21000$$
    $$R(6) = -15552 + 55296 - 51840 + 21000 = 8904 \implies \mathbf{(6, 8904)}$$
*   **Para $V = 10$:**
    $$R(10) = -12(10^4) + 256(10^3) - 1440(10^2) + 21000$$
    $$R(10) = -120000 + 256000 - 144000 + 21000 = 13000 \implies \mathbf{(10, 13000)}$$

---

#### [Questão 2] Classificar os Pontos Críticos com o Teste da Segunda Derivada
Calculamos a segunda derivada $R''(V)$:

$$R''(V) = \frac{d}{dV}(-48V^3 + 768V^2 - 2880V)$$
$$R''(V) = -144V^2 + 1536V - 2880$$

Agora, avaliamos os pontos críticos internos ($V = 6$ e $V = 10$):
*   **Para $V = 6$:**
    $$R''(6) = -144(36) + 1536(6) - 2880$$
    $$R''(6) = -5184 + 9216 - 2880 = 1152$$
    Como $R''(6) > 0$, o ponto crítico $\mathbf{(6, 8904)}$ é classificado como um **Mínimo Local**.

*   **Para $V = 10$:**
    $$R''(10) = -144(100) + 1536(10) - 2880$$
    $$R''(10) = -14400 + 15360 - 2880 = -1920$$
    Como $R''(10) < 0$, o ponto crítico $\mathbf{(10, 13000)}$ é classificado como um **Máximo Local**.

---

#### [Questão 3] Intervalos de Crescimento, Decrescimento e Esboço Gráfico
Análise do sinal da derivada $R'(V) = -48V(V-6)(V-10)$ nos intervalos do domínio $[0, 12]$:

1.  **Intervalo $[0, 6]$:** Escolhendo $V = 3$:
    $$R'(3) = -48(3)(3-6)(3-10) = -144(-3)(-7) = -3024 < 0 \implies \text{\textbf{Decrescente}}$$
2.  **Intervalo $[6, 10]$:** Escolhendo $V = 8$:
    $$R'(8) = -48(8)(8-6)(8-10) = -384(2)(-2) = 1536 > 0 \implies \text{\textbf{Crescente}}$$
3.  **Intervalo $[10, 12]$:** Escolhendo $V = 11$:
    $$R'(11) = -48(11)(11-6)(11-10) = -528(5)(1) = -2640 < 0 \implies \text{\textbf{Decrescente}}$$

##### Resumo dos Intervalos:
*   **Crescimento:** $V \in [6, 10]$ (A receita sobe se o preço subir de R$ 60,00 para R$ 100,00).
*   **Decrescimento:** $V \in [0, 6]$ e $V \in [10, 12]$ (A receita cai se o preço estiver abaixo de R$ 60,00 ou acima de R$ 100,00).

##### Esboço Gráfico Textual:
```
Receita R(V) em mil R$
  ^
21k | * (V=0, R=21k000)
    |  \
    |   \
13k |    \                     * (V=10, R=13k000)
    |     \                   / \
8.9k|      \                 /   \
    |       * (V=6, R=8k904)/     \
7.1k|                              * (V=12, R=7k176)
    +---------------------------------------------> Preço V (dezenas R$)
    0       6              10     12
```

---

### 2. Energia, Cinemática, Forças e Ondas (Física - Mecânica do Torque)

#### Questão 1: Relação entre Raio $r$ e Força $F$ com Torque Constante
Como o torque é dado por $\tau = F \cdot r \cdot \sin(\theta)$, se mantivermos o torque $\tau$ e o ângulo $\theta$ constantes, a força máxima que o motor consegue equilibrar é dada por:

$$F = \frac{\tau}{r \cdot \sin(\theta)}$$

Assim, a força suportada é **inversamente proporcional** à distância $r$. Portanto, se a distância $r$ for maior, a força linear suportada pelo motor será **menor**.

#### Questão 2: Força suportada na configuração da Figura 5
Na Figura 5, o braço do momento está apontando verticalmente para baixo e a força externa de tração linear $F$ está atuando exatamente na mesma direção (verticalmente para baixo). 

O ângulo entre a direção da força e a haste rotativa é $\theta = 180^\circ$. Calculando o torque resultante gerado por esta força externa sobre o eixo do motor:

$$\tau = F \cdot r \cdot \sin(180^\circ) = F \cdot r \cdot 0 = 0$$

Como a força externa não cria nenhum braço de alavanca rotacional (sua linha de ação passa exatamente pelo centro do eixo do motor), o torque gerado sobre o motor é **nulo**. 
Portanto, a força suportada por torque nesta configuração específica é **infinita** (indeterminada). O limite real do sistema será dado unicamente pela resistência de ruptura dos componentes físicos (plástico da haste e engrenagens do rolamento do motor), e não pela capacidade eletromagnética de torque do servo.

#### Desafio: Especificação e Análise de Torque
*   **Motor Escolhido:** Servo Motor de Alto Torque **TowerPro MG995** (engrenagens metálicas).
*   **Capacidade de Torque:** $9.4 \text{ kgf.cm}$ operando em $4.8\text{V}$ ou $11.0 \text{ kgf.cm}$ operando em $6.0\text{V}$.
*   **Significado Prático:** No limite máximo de operação ($6.0\text{V}$), o motor consegue estabilizar uma força de carga equivalente ao peso de $11\text{ kg}$ posicionada a exatos $1\text{ cm}$ de distância do centro de seu eixo. Se a carga for deslocada para $10\text{ cm}$ de distância do eixo, a carga máxima que o servo consegue segurar cai para $1.1\text{ kg}$ ($11 \text{ kgf.cm} / 10\text{ cm} = 1.1 \text{ kgf}$).

---

### 3. Indústria 4.0 (Programação Embarcada de Motor de Passo sem Biblioteca)

#### Modelo do Motor e Driver:
*   **Motor de Passo:** 28BYJ-48 (Unipolar, 5V DC).
*   **Driver de Corrente:** ULN2003.
*   **Modo de Acionamento:** Meio-passo (Half-Step) de 8 fases. Esta sequência oferece o **menor ângulo de rotação possível** (0.087 graus por passo físico após redução interna de 1:64) combinado com **elevado torque** (pois alterna o acionamento de uma e duas bobinas simultaneamente).

#### Código Fonte Completo (Arduino C++):
```cpp
/*
 * PROJETO: Controle de Motor de Passo 28BYJ-48 sem Bibliotecas
 * AUTORES: Guilherme Macario, Thierry Nathan, Caio Eduardo, Kaique Carvalho
 * DISCIPLINA: Industria 4.0 - FIAP Challenge
 */

// Pinos de controle conectados ao driver ULN2003
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 10;
const int IN4 = 11;

// Sequência de 8 passos para acionamento em Meio-Passo (Half-Step)
// Fornece o menor ângulo de passo e alto torque
const bool sequenciaFases[8][4] = {
  {true,  false, false, false}, // Passo 1: A
  {true,  true,  false, false}, // Passo 2: AB (Alto Torque)
  {false, true,  false, false}, // Passo 3: B
  {false, true,  true,  false}, // Passo 4: BC (Alto Torque)
  {false, false, true,  false}, // Passo 5: C
  {false, false, true,  true }, // Passo 6: CD (Alto Torque)
  {false, false, false, true }, // Passo 7: D
  {true,  false, false, true }  // Passo 8: DA (Alto Torque)
};

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

// Executa uma volta de 360 graus (4096 passos para o 28BYJ-48 com redução)
void darVoltaCompleta(bool sentidoHorario, int delayPasso) {
  int totalPassos = 4096; // 64 passos do motor x 64 de redução da caixa de engrenagens
  
  for (int i = 0; i < totalPassos; i++) {
    // Calcula o passo atual na matriz de 8 passos
    int passoAtual;
    if (sentidoHorario) {
      passoAtual = i % 8;
    } else {
      passoAtual = 7 - (i % 8);
    }
    
    // Escreve os estados digitais nas bobinas manualmente
    digitalWrite(IN1, sequenciaFases[passoAtual][0]);
    digitalWrite(IN2, sequenciaFases[passoAtual][1]);
    digitalWrite(IN3, sequenciaFases[passoAtual][2]);
    digitalWrite(IN4, sequenciaFases[passoAtual][3]);
    
    delayMicroseconds(delayPasso); // Controla a velocidade de rotação
  }
  
  // Desenergiza as bobinas ao terminar para evitar superaquecimento
  desenergizarMotor();
}

void desenergizarMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  // Dá 1 volta completa no sentido horário
  darVoltaCompleta(true, 1200); 
  delay(1000); // Aguarda 1 segundo
  
  // Dá outra volta completa no sentido anti-horário
  darVoltaCompleta(false, 1200); 
  delay(1000); // Aguarda 1 segundo
}
```
