# embarcatech_2025_UNIDADE_7_PROJETO_FINAL
1.  Escopo do projeto

1.1 - Apresentação do Projeto
 Dodge the Asteroids é um jogo interativo desenvolvido para a plataforma BitDogLab, utilizando uma matriz de LEDs WS2812 e controlado por um joystick. O jogador controla uma nave que deve se esquivar de asteróides que caem do topo da matriz de LEDs. O jogo se torna progressivamente mais difícil à medida que a frequência e a velocidade dos asteróides aumentam. A pontuação é exibida em um display OLED SSD1306 e o jogo termina caso a nave seja atingida.

1.2 - Objetivo do Projeto 
O objetivo do Dodge the Asteroids é demonstrar a implementação de um sistema embarcado interativo utilizando a BitDogLab. O projeto explora conceitos de controle de hardware, comunicação entre dispositivos e processamento de eventos em tempo real, incentivando a lógica de programação voltada para jogos simples em microcontroladores.

1.3 - Descrição do Funcionamento
O jogo inicia com a nave posicionada no centro da matriz de LEDs.
O joystick é usado para mover a nave para a esquerda ou direita.
Asteróides são gerados aleatoriamente e caem da parte superior da matriz.
O jogador deve evitar os asteróides; se um colidir com a nave, o jogo termina.
A pontuação aumenta conforme o tempo que o jogador sobrevive.
O display OLED exibe a pontuação atual e mensagens do jogo.

1.4 - Justificativa 
Este projeto foi desenvolvido para aplicar conhecimentos adquiridos na capacitação sobre sistemas embarcados, combinando a programação em C/C++ com a interação entre componentes eletrônicos. O jogo demonstra como utilizar periféricos como matrizes de LEDs, joysticks e displays OLED de forma eficiente e integrada.

1.5 - Originalidade 
Dodge the Asteroids é um jogo inspirado em mecânicas clássicas de esquiva, porém adaptado para a plataforma BitDogLab com uma matriz de LEDs. Embora existam jogos similares em outros sistemas, este projeto se destaca por sua implementação otimizada para microcontroladores RP2040.


Especificação do Hardware 
2.1 - Diagrama em Bloco 
O diagrama em bloco descreve as interações entre os principais componentes do sistema:
 +---------------------+           +---------------------------+                +------------------------+
  |   Joystick         |           |   RP2040                  |                |   Matriz de LEDs       |
  |   (Entrada)       | ---->      |   (Processamento)         |  ------>       |   WS2812              | 
 +--------------------+            +---------------------------+                 +--------------------------+
                                                     |
                                                     v
                                          +----------------------------+        
                                          |   Display OLED             | 
                                          |   SSD1306 +                |
                                          |    BUTTON A e B           |
                                          |                            |  
                                         +----------------------------+
				
					
2.2 - Componentes e Configuração
Microcontrolador: RP2040 (BitDogLab)
Matriz de LEDs: WS2812 (endereçável)
Joystick: Controle da nave
Display OLED (SSD1306): Exibe a pontuação

Especificação do Firmware 
3.1 - Blocos Funcionais
3.1.1 - Inicialização do Sistema
Inicializa GPIO, I2C, ADC e PIO.
Configura o display OLED.
Inicializa o joystick.
Inicializa a matriz de LEDs.

3.1.2 - Leitura do Joystick
Lê os valores analógicos dos eixos do joystick.
Determina a direção do movimento da nave.
3.1.3 - Movimento da Nave
Atualiza a posição da nave com base no joystick.
Garante que a nave não ultrapasse os limites da matriz.
3.1.4 - Geração de Asteróides
Cria asteróides aleatoriamente na linha superior da matriz.
Move os asteróides para baixo a cada ciclo do jogo.
3.1.5 - Atualização da Matriz de LEDs
Limpa o buffer de LEDs.
Desenha a nave na posição atual.
Desenha os asteróides.
Atualiza a matriz de LEDs com os novos valores.
3.1.6 - Atualização do Display
Atualiza a pontuação.
Exibe mensagens do jogo.

Execução do Projeto
4.1 - Metodologia
Pesquisa sobre controle de LEDs WS2812 e joysticks.
Desenvolvimento e implementação do código em C/C++.
Testes na BitDogLab.
Ajustes e otimizações.
4.2 - Testes de Validação
Movimentação correta da nave.
Detecção de colisão com asteróides.
Exibição correta da pontuação.
Ajuste da dificuldade ao longo do tempo.



Documentação e Entrega
5.1 - Código
Disponibilizado no GitHub com documentação clara.

5.2 - LINK DO VÍDEO: 


Conclusão 
Dodge the Asteroids é um projeto que combina conceitos de sistemas embarcados, programação em C/C++ e interação com hardware. Ele demonstra como a BitDogLab pode ser usada para desenvolver jogos interativos simples, incentivando o aprendizado e a experimentação com microcontroladores RP2040.

