# AquaPraemonitio - Sistema de Monitoramento de Enchente 🌊⚠️ [Vídeo de apresentação](youtube.com/xxxxxxxxxxx)

**AquaPraemonitio** é um sistema de monitoramento de enchentes desenvolvido para a plataforma **Raspberry Pi Pico W** utilizando a linguagem de programação **C** e o **Pico SDK**. O objetivo do sistema é monitorar o nível de água dos rios e o volume de chuva em tempo real, sinalizando potenciais enchentes por meio de alertas visuais e sonoros. O sistema é baseado em um modelo de **tempo real** e utiliza o **FreeRTOS** para gerenciar as tarefas.

Para fins de simulação, os **sensores de nível de água** e **volume de chuva** são **simulados por meio de um joystick** 🎮. O joystick permite ajustar manualmente os valores dos sensores, permitindo testar diferentes cenários e comportamentos do sistema sem a necessidade de sensores físicos.

## Funcionalidades 💡

O sistema **AquaPraemonitio** opera com dois modos principais: **Modo Normal** e **Modo Alerta**.

### Modo Normal ✅

No **Modo Normal**, o sistema coleta e exibe as informações dos sensores sem emitir alertas. Ele opera da seguinte maneira:

- **Display OLED**: Exibe as leituras em tempo real do nível de água e volume de chuva 📊.

- **Matriz de LEDs (WS2812B)**
 A matriz exibe um padrão visual na cor **verde** 🌱, indicando que as condições estão normais e que não há risco iminente de enchente.
  - **Controle da Matriz de LEDs**: A matriz de LEDs é controlada por meio de um **PIO** (Programmable Input/Output) da **Raspberry Pi Pico W**. A máquina de estados do PIO permite controlar os LEDs de forma eficiente, sem sobrecarregar o processador principal do microcontrolador 🖥️.
- **LED RGB (SMD5050)**: O LED RGB permanece na cor **verde** 🟢, sinalizando a ausência de perigo.
- **Buzzer (MLT8530)**: Não emite som, pois o sistema está em estado normal 🔇.

### Modo Alerta ⚠️

O **Modo Alerta** é ativado quando os níveis de risco ultrapassam os limiares definidos:

- O nível de água atinge **70%** de 4095 (do valor máximo de leitura) 🌊.
- O volume de chuva atinge **80%** de 4095 🌧️.

Quando esses valores são ultrapassados, o sistema entra no **Modo Alerta** e muda para o estado de emergência, realizando as seguintes ações:

- **Display OLED**
Exibe as informações de nível de água e volume de chuva, destacando com **ênfase** as leituras críticas e alertando sobre a situação de risco 🚨.
- **Matriz de LEDs (WS2812B)**: Exibe um **símbolo de perigo** ⚠️, como um ícone em vermelho 🔴, piscando ou com destaque para indicar o risco iminente de enchente.
  - **Controle da Matriz de LEDs**: A máquina de estados do **PIO** controla a matriz de LEDs, garantindo que os sinais de alerta sejam emitidos de maneira rápida e eficiente.
- **LED RGB (SMD5050)**: O LED RGB muda para a cor **vermelha** 🔴, sinalizando o alerta.
- **Buzzer (MLT8530)**: Emite **sinais sonoros distintos** 🔊, com diferentes frequências para alertar o usuário sobre o risco de enchente.

## Arquitetura do Sistema 🏗️

### Estrutura de Tarefas - FreeRTOS ⏲️

O sistema é baseado no **FreeRTOS**, um sistema operacional de tempo real, que permite a execução de várias tarefas de forma concorrente. A arquitetura do sistema foi projetada para resolver o problema clássico de **produtor-consumidor**, com uma única tarefa produtora e várias tarefas consumidoras. A dinâmica funciona da seguinte maneira:

1. **Tarefa Produtora**: A tarefa responsável por **ler os sensores de nível de água e volume de chuva** 🌊🌧️ e produzir as informações necessárias. Essa tarefa lê os dados dos sensores periodicamente, os coloca em uma **fila**, e as outras tarefas podem consumir esses dados.
2. **Tarefas Consumidoras**: As tarefas que consomem os dados produzidos pela tarefa de leitura dos sensores e realizam a gestão de atuadores (LEDs, display OLED e buzzer) 💻. As tarefas verificam se os dados consumidos ultrapassam os limites críticos e agem de acordo, acionando os alertas visuais e sonoros quando necessário.

A comunicação entre as tarefas é feita por meio de **filas** no FreeRTOS, que permitem uma troca de informações eficiente e sem bloqueios.

### Periféricos Utilizados 🔌

O sistema utiliza diversos periféricos da **BitDogLab/RP2040** para interagir com o ambiente e gerar sinais de alerta. Estes periféricos são gerenciados diretamente pelo código, usando as interfaces adequadas, como **GPIO**, **PWM**, **I2C** e **ADC**.

- **GPIO (General Purpose Input/Output)**: Usado para controlar os atuadores (LEDs e buzzer) 🔦🔊. As pins GPIO são configuradas para enviar sinais digitais para ativar ou desativar esses componentes.
- **PWM (Pulse Width Modulation)**: Usado para controlar a intensidade de cor do **LED RGB** 🌈 e a **frequência do buzzer** 🔊. A modulação permite variar a intensidade de luz e o som emitido conforme necessário.
- **I2C**: Usado para comunicação com o **display OLED** 🖥️. O protocolo I2C permite que o microcontrolador envie e receba dados de maneira eficiente, exibindo as leituras de sensores no display.
- **ADC (Analog-to-Digital Converter)**: O sistema utiliza o ADC para ler os sinais analógicos dos sensores de nível de água e volume de chuva 🌊🌧️. O RP2040 possui múltiplos canais ADC que convertem os sinais analógicos em valores digitais (0 a 4095) para serem processados pelo código.

### Simulação dos Sensores 🎮

Para facilitar o desenvolvimento e testes, os **sensores de nível de água** e **volume de chuva** são **simulados por meio de um joystick** 🎮. O joystick é utilizado para ajustar manualmente os valores dos sensores em tempo real, permitindo que o comportamento do sistema seja verificado e testado em diferentes cenários, como simulação de aumento de volume de chuva ou nível de água. Com isso, é possível testar o **modo alerta** sem a necessidade de sensores físicos, facilitando o processo de desenvolvimento e validação do sistema.

## Como Funciona ⚙️

O **AquaPraemonitio** coleta dados de sensores de nível de água e volume de chuva em tempo real. O código, baseado em **FreeRTOS**, organiza a execução das tarefas de forma eficiente. Quando os dados de um sensor ultrapassam os limiares críticos, o sistema ativa os **alertas visuais e sonoros**.

### Fluxo de Operação 🔄

1. **Leitura dos Sensores**: A tarefa produtora coleta periodicamente os dados dos sensores de nível de água e volume de chuva através do **ADC**. No caso da simulação, os dados dos sensores são lidos diretamente do **joystick** 🎮.
2. **Verificação dos Limiares**: A tarefa de controle verifica se os valores de leitura ultrapassam os limiares (70% para o nível de água e 80% para o volume de chuva). Se sim, o sistema entra em **modo alerta** ⚠️.
3. **Exibição de Dados**: O **display OLED** exibe as leituras de sensores, destacando os valores críticos no **modo alerta**.
4. **Controle de Atuadores**: As **tarefas consumidoras** alteram o estado do **LED RGB** para vermelho 🔴, acionam a **matriz de LEDs** para exibir um símbolo de perigo ⚠️ e ativam o **buzzer** 🔊 para alertar o usuário.

## Como Rodar o Sistema 🚀

### Requisitos ⚙️

- **Raspberry Pi Pico W** (ou placa compatível com RP2040) 🖥️
- **Pico SDK** instalado 💻
- **FreeRTOS** configurado
- **Joystick** para simulação dos sensores de nível de água e volume de chuva 🎮
- Matriz de LEDs **WS2812B** 🌈
- LED RGB **SMD5050** 🟢🔴
- Buzzer passivo **MLT8530** 🔊
- Display **OLED** com interface **I2C** 🖥️

### Passo a Passo de Instalação 🛠️

1. **Clone o repositório**:

   ```bash
   git clone https://github.com/seuusuario/AquaPraemonitio.git
   cd AquaPraemonitio
