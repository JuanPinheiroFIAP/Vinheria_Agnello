#include "Arduino.h"
#include "WiFi.h"
#include <HTTPClient.h>

HTTPClient client;

char nomeWifi[] = "iPhone Juan";
char senhaWifi[] = "1234aa";
char serverAddress[] = "https://api.tago.io/data";
char contentHeader[] = "application/json";
char tokenHeader[] = "";

int const pinoSensorLuz = A0;
int const pinoTemperatura = A1;
int const pinoUmidade = A2;

//--------------------------------------------------------------

int ledLuminosidadeVerde = 4;
int ledLuminosidadeAmarelo = 3;
int ledLuminosidadeVermelho = 2;

//--------------------------------------------------------------

int ledTemperaturaVerde = 7;
int ledTemperaturaVermelho = 5;

//--------------------------------------------------------------

int ledUmidadeVerde = 10;
int ledUmidadeAmarelo = 9;
int ledUmidadeVermelho = 8;

//--------------------------------------------------------------

int valorUmi = 0;
int valorLuz = 0;
int valorTemp = 0;

//--------------------------------------------------------------

void setup() {
  pinMode(pinoSensorLuz, INPUT);
  pinMode(pinoTemperatura, INPUT);
  pinMode(pinoUmidade, INPUT);

  //--------------------------------------------------------------

  pinMode(ledLuminosidadeVerde, OUTPUT);
  pinMode(ledLuminosidadeAmarelo, OUTPUT);
  pinMode(ledLuminosidadeVermelho, OUTPUT);

  //--------------------------------------------------------------

  pinMode(ledTemperaturaVerde, OUTPUT);
  pinMode(ledTemperaturaVermelho, OUTPUT);

  //--------------------------------------------------------------

  pinMode(ledUmidadeVerde, OUTPUT);
  pinMode(ledUmidadeAmarelo, OUTPUT);
  pinMode(ledUmidadeVermelho, OUTPUT);
  
//--------------------------------------------------------------

  init_wifi();
  Serial.begin(9600);
}

//--------------------------------------------------------------

void loop() {
  valorLuz = analogRead(pinoSensorLuz);
  int luminosidade = map(valorLuz, 0, 169, 0, 100);
  Serial.print("Valor da luminosidade esta em: ");
  Serial.print(luminosidade);
  Serial.println("%\n");
  send_luminosidade();
  delay(5000); 

  if (luminosidade < 50) {
    digitalWrite(ledLuminosidadeVerde, HIGH);
  } else {
    digitalWrite(ledLuminosidadeVerde, LOW);
  }

  if (luminosidade > 50 && luminosidade <= 70) {
    digitalWrite(ledLuminosidadeAmarelo, HIGH);
  } else {
    digitalWrite(ledLuminosidadeAmarelo, LOW);
  }

  if (luminosidade > 70) {
    digitalWrite(ledLuminosidadeVermelho, HIGH);
  } else {
    digitalWrite(ledLuminosidadeVermelho, LOW);
  }

  valorTemp = analogRead(pinoTemperatura);
  int temperaturaC = map(valorTemp, 20, 358, -40, 125);
  Serial.print("Valor da temperatura esta em: ");
  Serial.print(temperaturaC);
  Serial.println(" Graus\n");
  send_temperaturaC();
  delay(5000); 

  if (temperaturaC <= -10 && temperaturaC >= -13) {
    digitalWrite(ledTemperaturaVerde, HIGH);
  } else {
    digitalWrite(ledTemperaturaVerde, LOW);
  }

  if (temperaturaC > -10 || temperaturaC <= -13) {
    digitalWrite(ledTemperaturaVermelho, HIGH);
  } else {
    digitalWrite(ledTemperaturaVermelho, LOW);
  }
  //--------------------------------------------------------------

  valorUmi = analogRead(pinoUmidade);
  int umidade = map(valorUmi, 0, 1023, 0, 100);
  Serial.print("Valor da umidade esta em: ");
  Serial.print(umidade);
  Serial.println("%\n");
  send_umidade();
  delay(5000); 

  if (umidade >= 70 && umidade <= 80) {
    digitalWrite(ledUmidadeVerde, HIGH);
    digitalWrite(ledUmidadeVermelho, LOW);
  } else {
    digitalWrite(ledUmidadeVerde, LOW);
    digitalWrite(ledUmidadeVermelho, HIGH);
  }
}

void init_wifi() {
  Serial.println("Conectando WiFi");
  Serial.print("Wifi: ");
  Serial.println(nomeWifi);
  WiFi.begin(nomeWifi, senhaWifi);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
  }
  Serial.println("WiFi Conectado");
  Serial.print("Meu IP eh: ");
  Serial.println(WiFi.localIP());
}

void send_luminosidade() {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;

  strcpy(postData, "{\n\t\"variable\": \"luminosidade\",\n\t\"value\": ");
  dtostrf(luminosidade, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat(postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(2000);

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}

void send_temperaturaC() {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;

  strcpy(postData, "{\n\t\"variable\": \"temperaturaC\",\n\t\"value\": ");
  dtostrf(temperaturaC, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat(postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(2000);

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}

void send_umidade() {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;

  strcpy(postData, "{\n\t\"variable\": \"umidade\",\n\t\"value\": ");
  dtostrf(umidade, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat(postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  delay(2000);

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();
}
