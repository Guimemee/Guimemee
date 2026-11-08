# RELATÓRIO TÉCNICO INTEGRADO - SPRINT 3 E SPRINT 4
## CHALLENGE HOSPITAL ALEMÃO OSWALDO CRUZ (FIAP 2022)
### CURSO: BACHARELADO EM ENGENHARIA DA COMPUTAÇÃO

---

## 1. CONTROLE MANUAL DE MOTOR DE PASSO EM MODO MEIO-PASSO (HALF-STEP)
### Requisitos Mandatórios de Firmware (Sprints 3 e 4)

1. **Menor Passo Possível e Elevado Torque:** Implementação mandatória do **Modo Meio-Passo (Half-Step de 8 fases)**.
2. **Proibição Estrita de Bibliotecas Facilitadoras de Bobinas:** O acionamento é realizado em baixo nível de forma manual via tabela de estados lógicos e digitalWrite(), garantindo o aprendizado direto da polarização dos enrolamentos estatóricos.
3. **Sequência Exata do Feedback Docente (Chaveamento 2-1-2-1):**
   * *Estado 0:* Bobina 1 = ON, Bobina 2 = ON (2 bobinas ligadas -> máximo torque de retenção)
   * *Estado 1:* Bobina 1 = OFF, Bobina 2 = ON (1 bobina ligada -> menor passo angular de transição)
   * *Estado 2:* Bobina 2 = ON, Bobina 3 = ON (2 bobinas ligadas)
   * *Estado 3:* Bobina 2 = OFF, Bobina 3 = ON (1 bobina ligada)
   * *Estado 4:* Bobina 3 = ON, Bobina 4 = ON (2 bobinas ligadas)
   * *Estado 5:* Bobina 3 = OFF, Bobina 4 = ON (1 bobina ligada)
   * *Estado 6:* Bobina 4 = ON, Bobina 1 = ON (2 bobinas ligadas)
   * *Estado 7:* Bobina 4 = OFF, Bobina 1 = ON (1 bobina ligada)
4. **Ciclo Operacional de 360 graus:**
   * O eixo completa 1 volta exata de 360 graus.
   * Imediatamente ao atingir 360 graus, **todas as 4 bobinas/LEDs são completamente desligadas** (desenergização de proteção térmica).
   * O sistema permanece em repouso por **1,0 segundo (1000 ms)**.
   * Inicia-se automaticamente uma nova volta de 360 graus, repetindo o processo ciclicamente até a placa ser desenergizada.

### Arquivos Gerados para a Entrega:
* **Código Fonte Arduino (.ino):** [controle_motor_passo_halfstep.ino](file:///D:/Github_Guimemee/Guimemee/fiap-challenges/controle_motor_passo_halfstep.ino)
* **Documento Impresso em PDF (.pdf):** [controle_motor_passo_halfstep.pdf](file:///D:/Github_Guimemee/Guimemee/fiap-challenges/controle_motor_passo_halfstep.pdf)
* **Pacote Compactado para Envio (.zip):** [entrega_sprint3_motor_passo.zip](file:///D:/Github_Guimemee/Guimemee/fiap-challenges/entrega_sprint3_motor_passo.zip)

---

## 2. RESOLUÇÃO DIFERENCIADA DE PROBLEMAS - SPRINT 3 (PROF. ISMAEL)
### Otimização e Estudo de Máximos e Mínimos da Função Receita

Função da Receita Mensal:
$$R(V) = -12V^4 + 256V^3 - 1440V^2 + 21000, \quad 0 \le V \le 12$$
Onde:
* $R(V)$: Receita mensal em milhares de reais.
* $V$: Preço unitário de venda em dezenas de reais (exemplo: $V = 6 \implies \text{R\$} 60,00$).

### [Questão 1] Determinar as Coordenadas dos Pontos Críticos
Primeira derivada:
$$R'(V) = \frac{d}{dV}(-12V^4 + 256V^3 - 1440V^2 + 21000) = -48V^3 + 768V^2 - 2880V$$
Igualando a zero:
$$-48V(V^2 - 16V + 60) = 0$$

Raízes:
1. $V_1 = 0$
2. $V^2 - 16V + 60 = 0 \implies \Delta = 256 - 240 = 16 \implies \sqrt{\Delta} = 4$
   $$V = \frac{16 \pm 4}{2} \implies V_2 = 6 \quad \text{e} \quad V_3 = 10$$

Coordenadas dos Pontos Críticos:
* **$V = 0$ (Fronteira):** $R(0) = 21000 \implies P_1 = (0, 21000)$ [R$ 21.000.000,00]
* **$V = 6$:** $R(6) = 8904 \implies P_2 = (6, 8904)$ [R$ 8.904.000,00]
* **$V = 10$:** $R(10) = 13000 \implies P_3 = (10, 13000)$ [R$ 13.000.000,00]
* **$V = 12$ (Fronteira):** $R(12) = 7176 \implies P_4 = (12, 7176)$ [R$ 7.176.000,00]

### [Questão 2] Classificação dos Pontos Críticos (Segunda Derivada)
Segunda derivada:
$$R''(V) = -144V^2 + 1536V - 2880$$

* Para $V = 6$: $R''(6) = -144(36) + 1536(6) - 2880 = +1152 > 0 \implies$ **MÍNIMO LOCAL** em (6, 8904).
* Para $V = 10$: $R''(10) = -144(100) + 1536(10) - 2880 = -1920 < 0 \implies$ **MÁXIMO LOCAL** em (10, 13000).

### [Questão 3] Intervalos de Crescimento e Decrescimento e Representação Gráfica
* Intervalo $(0, 6)$: $R'(V) < 0 \implies$ **Decrescente**
* Intervalo $(6, 10)$: $R'(V) > 0 \implies$ **Crescente** (Faixa ótima de venda entre R$ 60,00 e R$ 100,00)
* Intervalo $(10, 12)$: $R'(V) < 0 \implies$ **Decrescente**

![Gráfico da Receita RDP Sprint 3](file:///D:/Github_Guimemee/Guimemee/fiap-challenges/images/grafico_rdp_sprint3.png)

---

## 3. RESOLUÇÃO DIFERENCIADA DE PROBLEMAS - SPRINT 4 (PROF. ISMAEL)
### Otimização e Estudo de Máximos e Mínimos da Função Lucro

Função do Lucro Anual:
$$L(N) = 3N^5 - 585N^3 + 43740N - 40000, \quad -10 \le N \le 10$$
*(Onde $N=0$ representa o ano de 2022; $N=1$ para 2023; $N=-1$ para 2021, etc.)*

### [Questão 1] Determinar as Coordenadas dos Pontos Críticos
Primeira derivada:
$$L'(N) = 15N^4 - 1755N^2 + 43740 = 0$$
Dividindo por 15:
$$N^4 - 117N^2 + 2916 = 0$$

Substituindo $u = N^2$:
$$u^2 - 117u + 2916 = 0$$
$$\Delta = (-117)^2 - 4(1)(2916) = 13689 - 11664 = 2025 \implies \sqrt{\Delta} = 45$$
$$u = \frac{117 \pm 45}{2} \implies u_1 = 81 \quad \text{e} \quad u_2 = 36$$

Retornando para $N$:
* $N^2 = 81 \implies N = \pm 9$ (Anos 2013 e 2031)
* $N^2 = 36 \implies N = \pm 6$ (Anos 2016 e 2028)

Coordenadas dos Pontos:
* **$N = -9$ (2013):** Coordenada $(-9, 58406) \implies$ Lucro de R$ 58.406,00
* **$N = -6$ (2016):** Coordenada $(-6, -169600) \implies$ Prejuízo de -R$ 169.600,00
* **$N = 6$ (2028):** Coordenada $(6, 89600) \implies$ Lucro Máximo de R$ 89.600,00
* **$N = 9$ (2031):** Coordenada $(9, -138406) \implies$ Prejuízo de -R$ 138.406,00

### [Questão 2] Classificação pela Segunda Derivada
$$L''(N) = 60N^3 - 3510N$$

* $N = -9$: $L''(-9) = -12150 < 0 \implies$ **MÁXIMO LOCAL**
* $N = -6$: $L''(-6) = +8100 > 0 \implies$ **MÍNIMO LOCAL**
* $N = 6$: $L''(6) = -8100 < 0 \implies$ **MÁXIMO LOCAL**
* $N = 9$: $L''(9) = +12150 > 0 \implies$ **MÍNIMO LOCAL**

### [Questão 3] Intervalos de Crescimento e Decrescimento e Representação Gráfica
* **Crescente em:** $[-10, -9]$, $[-6, 6]$ e $[9, 10]$ (com destaque para o ciclo de expansão até 2028 com lucro de R$ 89.600,00).
* **Decrescente em:** $[-9, -6]$ e $[6, 9]$.

![Gráfico do Lucro RDP Sprint 4](file:///D:/Github_Guimemee/Guimemee/fiap-challenges/images/grafico_rdp_sprint4.png)

---

## 4. ECFO (FÍSICA) - ROBÔ SKATISTA (CONSERVAÇÃO DA ENERGIA MECÂNICA)
### Desafio da Pista Parabólica - Simulador PhET Colorado

### Parâmetros Experimentais:
* Aceleração da gravidade: g = 10 m/s^2
* Altura no topo da pista: h = 6 m
* Ponto de referência zero: Fundo do vale (h = 0 m)

### 1) Massa Pequena (m = 50 kg) a h = 6 m:
* **Energia Potencial Gravitacional no topo:**
  $$E_{pg} = m \cdot g \cdot h = 50\text{ kg} \times 10\text{ m/s}^2 \times 6\text{ m} = \mathbf{3.000\text{ J}}$$
* **Energia Cinética no topo:**
  Como parte do repouso (v = 0 m/s): $E_c = \mathbf{0\text{ J}}$
* **Energia Mecânica Total:**
  $$E_m = E_{pg} + E_c = 3.000\text{ J} + 0 = \mathbf{3.000\text{ J}}$$
* **Velocidade no fundo (h = 0 m):**
  $$E_c = 3.000\text{ J} \implies \frac{1}{2}(50)v^2 = 3000 \implies 25v^2 = 3000 \implies v = \sqrt{120} \approx \mathbf{10,954\text{ m/s}}$$

### 2) Massa Grande (m = 80 kg) a h = 6 m:
* **Energia Potencial Gravitacional no topo:**
  $$E_{pg} = m \cdot g \cdot h = 80\text{ kg} \times 10\text{ m/s}^2 \times 6\text{ m} = \mathbf{4.800\text{ J}}$$
* **Energia Cinética no topo:**
  $E_c = \mathbf{0\text{ J}}$
* **Energia Mecânica Total:**
  $$E_m = E_{pg} + E_c = 4.800\text{ J} + 0 = \mathbf{4.800\text{ J}}$$
* **Velocidade no fundo (h = 0 m):**
  $$E_c = 4.800\text{ J} \implies \frac{1}{2}(80)v^2 = 4800 \implies 40v^2 = 4800 \implies v = \sqrt{120} \approx \mathbf{10,954\text{ m/s}}$$
  *(A velocidade final independe da massa do corpo, dependendo unicamente da aceleração da gravidade e do desnível vertical).*

### 3) Relação Física entre E_pg e E_c e Teorema da Conservação:
Durante o movimento sem atrito, a força peso atua como força puramente conservativa. Na descida, toda a energia potencial é transformada em energia cinética, atingindo valor máximo no fundo da pista (h = 0). Na subida, a energia cinética é integralmente restaurada em energia potencial, fazendo o robô parar momentaneamente na altura inicial de 6 m na outra borda da pista. A soma escalar Em = Epg + Ec permanece estritamente constante em todos os instantes.

![Gráfico Comparativo de Energia](file:///D:/Github_Guimemee/Guimemee/fiap-challenges/images/grafico_robo_skatista_energia.png)

---

## 5. INTEGRAÇÃO DOS ARQUIVOS CAD E LITERATURA NO REPOSITÓRIO
* Modelos CAD 3D (.ipt):
  * [Encaixe-Motor.ipt](file:///D:/Github_Guimemee/Guimemee/fiap-challenges/cad-models/Encaixe-Motor.ipt)
  * [Peça2 - Encaixe do eixo.ipt](file:///D:/Github_Guimemee/Guimemee/fiap-challenges/cad-models/Peça2%20-%20Encaixe%20do%20eixo.ipt)
* Literatura Científica:
  * [Exoskeletons Towards Industrie 4.0 Benefits and Challenges of the IoT.pdf](file:///D:/Github_Guimemee/Guimemee/fiap-challenges/cad-models/Exoskeletons%20Towards%20Industrie%204.0%20Benefits%20and%20Challenges%20of%20the%20IoT.pdf)