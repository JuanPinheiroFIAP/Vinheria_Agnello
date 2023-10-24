# Vinheria Agnello
Este repositório contém o código-fonte e o projeto do Tinkercad para os desafios CP4 e CP5, que consistem em criar um sistema de IoT usando o Arduino e a Tago. O objetivo é monitorar a temperatura, luminosidade e a umidade de um ambiente e enviar os dados para a plataforma online, onde podem ser visualizados e analisados.

## Projeto Tinkercad
### CP4
O projeto do Tinkercad pode ser acessado pelo link: https://www.tinkercad.com/things/3VrRYY2JcHB
O projeto usa os seguintes componentes:

  - Arduino Uno R3
  - Protoboard
  - Fotorresistor
  - Resistor de 100 ohms
  - Sensor de temperatura [TMP36]
  - Potenciômetro de 250 kilohms
  - 7 resistores de 220 ohms
  - 7 LEDs
  - 
O código lê os valores de temperatura, luminosidade e umidade do sensor a cada 5 segundos e os envia para a Tago usando o protocolo MQTT.
Para simulação online através da plataforma TinkerCad foi utilizado o Arduino Uno R3, porém para obter os resultados esperados será utilizado a plaquinha WI-FI ESP32.

## Configuração
Para executar o código, é necessário configurar as seguintes variáveis:
  - ssid: o nome da rede Wi-Fi
  - pass: a senha da rede Wi-Fi
  - token: o código do seu token da plataforma IoT
  
## Referências
: https://www.tinkercad.com/things/3VrRYY2JcHB

## Projeto Tinkercad
### CP5
O projeto do Tinkercad pode ser acessado pelo link: https://www.tinkercad.com/things/lgmG01b7IDp
O projeto usa os seguintes componentes:

  - Arduino Uno R3
  - Protoboard
  - Fotorresistor
  - Resistor de 100 ohms
  - Sensor de temperatura [TMP36]
  - Dois potenciômetros de 250 kilohms
  - Dois resistores de 1 kilohms
  - LCD 16x2
  
O código lê os valores de temperatura, luminosidade e umidade do sensor a cada 5 segundos e os envia para a Tago usando o protocolo MQTT.
Para simulação online através da plataforma TinkerCad foi utilizado o Arduino Uno R3, porém para obter os resultados esperados será utilizado a plaquinha WI-FI ESP32.

## Configuração
Para executar o código, é necessário configurar as seguintes variáveis:
  - ssid: o nome da rede Wi-Fi
  - pass: a senha da rede Wi-Fi
  - token: o codigo do seu token da plataforma IoT

## Referências
: https://www.tinkercad.com/things/lgmG01b7IDp

## Preview
![tikercad-preview](/images/cp5.png)