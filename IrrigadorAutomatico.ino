/*******************************************************************************
* Projeto Irrigador Automatico de Solo (v1.0)
* 
* 
*******************************************************************************/

const int PINO_SENSOR = A0; //Pino (analogico) conectado ao sensor
const int PINO_RELE = 2; //Pino conectado ao rele

//Variaveis que armazenam as leituras do sensor
int leitura_sensor = 0;
int leitura_anterior = 0;

//Variaveis que armazenam os valores de calibracao
const int VALOR_MAXIMO = 632; //Valor com solo seco
const int VALOR_MINIMO = 314; //Valor com solo umido

const int CONCENTRACAO_MINIMA = 30;
const int CONCENTRACAO_MAXIMA = 50;

void setup() {

  pinMode(PINO_SENSOR, INPUT); //Define o pino conectado ao sensor como uma entrada do sistema
  pinMode(PINO_RELE, OUTPUT); //Define o pino conectado ao rele como uma saida do sistema

  digitalWrite(PINO_RELE, LOW); //Inicia o pino conectado ao rele com nivel logico baixo

  pinMode(8, OUTPUT); //verde
  pinMode(9, OUTPUT); //amarelo
  pinMode(10, OUTPUT); //vermelho
}

void loop() {
  //Realiza a leitura do sensor, a mapeia entre 0 e 100% e exibe o valor no LCD
  leitura_sensor = analogRead(PINO_SENSOR);
  leitura_sensor = map(leitura_sensor, VALOR_MINIMO, VALOR_MAXIMO, 100, 0);
  Serial.println(leitura_sensor);

  //Verifica se a leitura esta abaixo da concetracao minima desejada
  if(leitura_sensor < CONCENTRACAO_MINIMA){ //Se sim (seco)
    digitalWrite(8, LOW); //verde desligado
    digitalWrite(10, HIGH); //vermelho ligado
  }else if (leitura_sensor > CONCENTRACAO_MAXIMA) { //Caso contrario (umido)
    digitalWrite(8, HIGH); //verde ligado
    digitalWrite(10, LOW); //vermelho desligado
  }

  if(leitura_sensor && !leitura_anterior){ //Se estiver seco
    delay(5000); //Aguarda 5 segundos para nova leitura
    digitalWrite(9, HIGH); //amarelo ligado
    digitalWrite(10, LOW); //vermelho desligado

    while(digitalRead(PINO_SENSOR)) { //Liberar agua ate ficar umido
        digitalWrite(PINO_RELE, HIGH); //Acionamos o rele por meio segundo
        delay(2000);
        digitalWrite(PINO_RELE, LOW); //Desligamos o rele

        delay(10000); //Espera 10 segundo para fazer nova leitura     
    }
    digitalWrite(9, LOW); //amarelo
  } 

  leitura_anterior = leitura_sensor;
}
