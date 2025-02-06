# 📌 Sistema de Controle de Dispositivos via UART e I2C no RP2040

## 📖 Sobre o Projeto
Este projeto tem como objetivo **explorar o uso de interfaces de comunicação serial no microcontrolador RP2040**, utilizando **UART e I2C** para interagir com uma **matriz de LEDs WS2812, um display SSD1306 e botões de entrada**. O projeto combina hardware e software para criar um sistema interativo e funcional.

## 🎯 Objetivos do Projeto
✅ Compreender o funcionamento da **comunicação serial** em microcontroladores.  
✅ Implementar **debouncing via software** para evitar efeitos indesejados ao pressionar botões.  
✅ Manipular e controlar **LEDs comuns e LEDs endereçáveis WS2812**.  
✅ Utilizar **resistores de pull-up internos** nos botões de acionamento.  
✅ Desenvolver um sistema funcional que **integra hardware e software**.  

## 🛠️ Componentes Utilizados
- **Microcontrolador:** RP2040 (Placa BitDogLab)  
- **Matriz de LEDs 5x5 WS2812:** Conectada à **GPIO 7**  
- **LED RGB comum:** Conectado às **GPIOs 11, 12 e 13**  
- **Botão A:** Conectado à **GPIO 5**  
- **Botão B:** Conectado à **GPIO 6**  
- **Display SSD1306:** Conectado via **I2C (GPIO 14 e GPIO 15)**

## 🚀 Funcionalidades Implementadas
✅ **Entrada de caracteres via UART:** O Serial Monitor recebe e processa os caracteres digitados.  
✅ **Exibição de caracteres no display SSD1306.**  
✅ **Exibição de caracteres via UART.** 
✅ **Os números de 0 a 9 são exibidos na matriz WS2812.**  
✅ **As letras maiúsculas são exibidas na matriz WS2812.**  
✅ **Os botões A e B controlam o LED RGB.**  
✅ **Interrupções (IRQ) capturam eventos de botões.**  
✅ **Tratamento de debounce via software.**  

## 🛠️ Configuração do Hardware
1. **Conectar os componentes à BitDogLab** conforme a seguinte tabela:

| Componente | GPIO |
|------------|------|
| Matriz de LEDs WS2812 | 7 |
| LED RGB - Verde | 11 |
| LED RGB - Azul | 12 |
| LED RGB - Vermelho | 13 |
| Botão A | 5 |
| Botão B | 6 |
| Display SSD1306 (I2C) | 14 (SDA), 15 (SCL) |

2. **Ativar os resistores de pull-up internos** para os botões no código.
3. **Configurar o PIO para controlar a matriz WS2812** com eficiência.

## 🖥️ Uso do Projeto
- **O display exibe os caracteres (0-9, A-Z) digitados via UART.**
- **Os números e letras digitados são exibidos na matriz de LEDs e no Display.**
- **As letras maiúsculas são exibidas na matriz de LEDs e Display.**
- **As letras minúsculas limpam a matriz de LEDs, sendo exibidas apenas no Display.**
- **Botão A liga/desliga o LED verde.**
- **Botão B liga/desliga o LED azul.**

## 📸 Demonstração do Projeto
📹 **[Assista ao vídeo demonstrativo]()**

## 📜 Licença
Este projeto é de código aberto e pode ser usado livremente para fins educacionais e experimentação.