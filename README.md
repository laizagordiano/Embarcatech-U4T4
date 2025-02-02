# Embarcatech-U4T4

Este projeto visa o controle interativo de uma matriz de LEDs WS2812 utilizando botões, com implementação de interrupções, debouncing e controle de LEDs comuns. Ele utiliza uma placa **BitDogLab** e é baseado em um microcontrolador **Raspberry Pi Pico**.

## Requisitos do Projeto

O projeto deve seguir os seguintes requisitos:

1. **Uso de Interrupções**: Todas as funcionalidades relacionadas aos botões são implementadas utilizando rotinas de interrupção (IRQ).
2. **Debouncing**: O tratamento de "bouncing" dos botões é implementado via software, evitando múltiplos registros de uma única ação de pressionamento.
3. **Controle de LEDs**: O projeto inclui o uso de LEDs comuns e LEDs WS2812, demonstrando o domínio de diferentes tipos de controle de LEDs.
4. **Organização do Código**: O código está bem estruturado e comentado para facilitar o entendimento e a manutenção.

## Funcionalidades

- **Controle de Números na Matriz de LEDs**: O número exibido na matriz de LEDs 5x5 pode ser alterado usando os botões A e B. O número exibido vai de 0 a 9.
- **Debounce e Interrupção dos Botões**: O tratamento de interrupções e debouncing garante que os botões A e B só alterem o número quando pressionados de forma estável.
- **Piscar de LED**: Um LED RGB (vermelho) pisca a cada 200ms, indicando que o sistema está em funcionamento.

## Componentes Utilizados

- **Placa BitDogLab**
- **Matriz de LEDs WS2812 5x5** conectada à GPIO 7
- **LED RGB** conectado às GPIOs 11 (vermelho), 12 (verde) e 13 (azul)
- **Botões A e B** conectados às GPIOs 5 e 6

## Como Funciona

- **Botão A**: Ao pressionar o botão A, o número exibido na matriz de LEDs é incrementado de 1 (com valores cíclicos de 0 a 9).
- **Botão B**: Ao pressionar o botão B, o número exibido na matriz de LEDs é decrementado de 1 (com valores cíclicos de 0 a 9).
- **Matriz de LEDs**: A matriz exibe os números de 0 a 9 em um formato 5x5 de LEDs, com cada número representado por um conjunto de LEDs acesos.

## Como Rodar o Projeto

### Pré-requisitos

1. **Placa BitDogLab** com um microcontrolador Raspberry Pi Pico.
2. **Ambiente de Desenvolvimento** configurado para programar o Raspberry Pi Pico (como o **PICO SDK**).
   
### Passos para Compilação e Upload

1. Clone o repositório:
   ```bash
   git clone https://github.com/laizagordiano/Embarcatech-U4T4.git

2. Navegue até o diretório do projeto e crie o diretório build:
    ```bash
    cd Embarcatech-U4T4
    mkdir build
    cd build
3. Execute o comando CMake para configurar a compilação:
    ```bash
    cmake ..
4. Compile o projeto:
    ```bash
    make

5. Faça o upload do binário gerado para o Raspberry Pi Pico.