#include "Arduino.h"
#include "WiFi.h"
#include <HTTPClient.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

HTTPClient client;

char nomeWifi[] = "iPhone Juan";
char senhaWifi[] = "1234aa";
char serverAddress[] = "https://api.tago.io/data";
char contentHeader[] = "application/json";
char tokenHeader[] = "e2a8d931-7f2e-4f9d-a266-242fca6af232";

int const pinoSensorLuz = A0;
int const pinoTemperatura = A1;
int const pinoUmidade = A2;

int valorUmi = 0;
int valorLuz = 0;
int valorTemp = 0;

void setup() {
  lcd.begin(16, 2);
  pinMode(pinoSensorLuz, INPUT);
  pinMode(pinoTemperatura, INPUT);
  pinMode(pinoUmidade, INPUT);
  
  init_wifi();
}

void loop() {
  valorLuz = analogRead(pinoSensorLuz);
  int luminosidade = map(valorLuz, 0, 169, 0, 100);
  if (luminosidade == 0){
  lcd.clear();
  }
  if (luminosidade > 20 && luminosidade < 30 ){
  lcd.clear(); 
  lcd.print("Ambiente a meia ");
  lcd.setCursor(0, 1);
  lcd.print("luz");
  }
  
  if (luminosidade > 70){
  lcd.clear(); 
  lcd.print("Ambiente muito ");
  lcd.setCursor(0, 1);
  lcd.print("CLARO");
  send_luminosidade();
  }
  
  //-------------------------------------------------------

  valorTemp = analogRead(pinoTemperatura);
  int temperaturaC = map(valorTemp, 20, 358, -40, 125);
  
  if (temperaturaC > 13&& temperaturaC < 20){
  lcd.clear(); 
  lcd.print("Temperatura OK ");
  lcd.setCursor(0, 1);
  lcd.print("temp: ");
  lcd.print(temperaturaC);
  lcd.print("C");
  }
  
  if (temperaturaC > 30){
  lcd.clear(); 
  lcd.print("Temperatura ALTA ");
  lcd.setCursor(0, 1);
  lcd.print("temp: ");
  lcd.print(temperaturaC);
  lcd.print("C");
  send_temperaturaC()
  }
  
  //-------------------------------------------------------

  valorUmi = analogRead(pinoUmidade);
  int umidade = map(valorUmi, 0, 1023, 0, 100);
  
  if (umidade > 50 && umidade < 70){
  lcd.clear(); 
  lcd.print("Umidade OK ");
  lcd.setCursor(0, 1);
  lcd.print("Umidade: ");
  lcd.print(umidade);
  lcd.print("%");
  }
  
  if (umidade > 70){
  lcd.clear(); 
  lcd.print("Umidade ALTA ");
  lcd.setCursor(0, 1);
  lcd.print("Umidade: ");
  lcd.print(umidade);
  lcd.print("%");
  send_umidade();
  }
    
  //-------------------------------------------------------

  delay(2000);
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
