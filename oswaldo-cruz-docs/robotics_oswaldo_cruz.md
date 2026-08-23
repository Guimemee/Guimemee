# Robôs de Vistoria e Interação Hospitalar (Hospital Oswaldo Cruz)
## Relatório Técnico: Concepção de Hardware, Mecânica e Modelagem 3D

Este documento apresenta as diretrizes de desenvolvimento físico e mecânico do robô autônomo projetado para atuar no monitoramento e suporte à reabilitação clínica e acompanhamento de pacientes no Hospital Alemão Oswaldo Cruz.

---

### 1. Escopo da Solução e Atividades
A solução consiste em um robô móvel autônomo projetado para realizar vistorias periódicas de infraestrutura hospitalar e interagir de forma lúdica e funcional com os pacientes.
*   **Vistoria:** O robô utiliza sensores de mapeamento a laser (LiDAR) e câmeras estereoscópicas para patrulhar corredores, detectando anomalias térmicas ou estruturais.
*   **Interação com Pacientes:** Possui uma tela sensível ao toque acoplada ao dorso, permitindo a comunicação com a equipe de enfermagem, coleta de questionários de bem-estar e acesso a dados sobre a reabilitação física (conectando-se ao sistema de dados do exoesqueleto robótico).

---

### 2. Modelagem 3D (CAD) do Robô
O design mecânico do chassi foi desenvolvido utilizando ferramentas de modelagem paramétrica 3D (AutoCAD / SolidWorks), focado em estabilidade estática e mobilidade interna por rampas e portas.

#### Componentes Mecânicos do Modelo 3D:
1.  **Base Motriz Diferencial:** Estrutura cilíndrica baixa contendo duas rodas tracionadas por motores DC com encoders de alta precisão e duas rodas bobas do tipo *caster* para garantir raio de giro zero.
2.  **Chassi Principal:** Coluna de alumínio anodizado integrada a painéis de acrílico e ABS moldado por impressora 3D, abrigando a eletrônica interna (baterias LiFePO4, placa controladora e sensores de bateria).
3.  **Dorso do Robô:** Suporte inclinado para acomodação da tela interativa do paciente, projetada ergonomicamente para uso tanto por pacientes em cadeiras de rodas quanto de pé.
4.  **Cabeça Sensorial:** Suporte móvel (pan-tilt) contendo o sensor de profundidade e a câmera de visão computacional.

#### Visualização e Simulação em CAD:
A montagem em 3D permite simular o centro de gravidade (CG) do robô para evitar capotamentos durante a movimentação em rampas de até 15 graus de inclinação, além de prever o encaixe perfeito das chapas de alumínio e das rotas de cabeamento elétrico interno antes de iniciar a usinagem das peças físicas.
*(Os modelos e renders tridimensionais completos em arquivos CAD de simulação encontram-se disponíveis no repositório de design industrial).*

---

### 3. Integração com o Exoesqueleto de Reabilitação
Durante as sessões de fisioterapia utilizando o exoesqueleto de membros inferiores (que utiliza sensores de células de carga e EEG NeuroSky), o robô móvel atua como uma interface de controle auxiliar móvel. 

O robô se conecta via rede Wi-Fi interna ao exoesqueleto do paciente e atua como:
*   **Servidor local de armazenamento temporário:** Coleta a telemetria do treino em tempo real de forma assíncrona.
*   **Painel móvel de feedback visual:** Permite que o médico veja os dados de força muscular do paciente exibidos graficamente na tela do robô à medida que o paciente executa a marcha, aumentando o engajamento e a precisão do acompanhamento clínico.
