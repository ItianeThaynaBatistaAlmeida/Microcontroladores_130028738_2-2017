/*UNIVERSIDADE DE BRASILIA
Disciplina: Microcontroladores e Microprocessadores
Professor: Diogo Caetano
Alunos: Alexandre Jose e Itiane Thayna
Matricula: 130059129 130028738
Ponto de Controle 2 Codigo realizado no Energia
*/

#include <Servo.h>
//Definição dos servos
Servo servohori;            // Motor servo Horizontal
int servoh = 0;  
int servohLimitHigh = 160; // limite maximo de 160 graus
int servohLimitLow = 20;  // limite minimo de 20 graus 

Servo servoverti;            //Motor servo Vertical 
int servov = 0; 
int servovLimitHigh = 160; // limite maximo de 160 graus
int servovLimitLow = 20; // limite minimo de 20 graus 
//Atribuindo os LDRs
int ldrtopl = A0; //"top left" LDR que ficará em cima à esquerda. Conectado a entrada A0
int ldrtopr = A1; //"top right" LDR que ficará em cima à direita. Conectado a entrada A1
int ldrbotl = A2; // "bottom left" LDR que ficará embaixo a esquerda. Conectado a entrada A2
int ldrbotr = A3; // "bottom right" LDR que ficará embaixo a direita. Conectado a entrada A3

 void setup () 
 {
  pinMode(ldrtopl,INPUT); // Definindo pinos como entrada
  pinMode(ldrtopr,INPUT);
  pinMode(ldrbotl,INPUT);
  pinMode(ldrbotr,INPUT);
 
  servohori.attach(9); // Servo horizontal atribuido ao pino 9 - Que é o P2.1
  servohori.write(0); // Inicia o servo horizontal na posição 0
servoverti.attach(10); // Servo vertical atribuido ao pino 10 -  Que é P2.2
  servoverti.write(0);
  delay(500);  // 500 milisegundos para dar estabilidade a parte mecanica
 }

void loop()
{
  servoh = servohori.read(); // define uma leitura de cada servo
  servov = servoverti.read();
  //capturando valores analogicos de cada LDR
  int topl = analogRead(ldrtopl); // realizando a leitura analogica do "top left"
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // calculando a media
  int avgtop = (topl + topr) / 2; // Media dos LDRs Superiores
  int avgbot = (botl + botr) / 2; //Media dos LDRs inferiores
  int avgleft = (topl + botl) / 2; // Media dos LDRs da esquerda
  int avgright = (topr + botr) / 2; //Media dos LDRs da direita

  if (avgtop < avgbot) // Se a media superior for menor que a media inferior
  {
    servoverti.write(servov +1);  // servo vertical aumenta 1
    if (servov > servovLimitHigh)  // se servo vertical for maior que o limite superior(160)
     { 
      servov = servovLimitHigh; // Atribui limite superior ao servo
     }
    delay(10);
  }
  else if (avgbot < avgtop)      // Se media inferior menor que media superior
  {
    servoverti.write(servov -1); // servo vertical diminui um grau
    if (servov < servovLimitLow) // Se Servo vertical for menor que limite inferior(20)
  {
    servov = servovLimitLow;     // Atribui limite inferior ao servo vertical (atribui a posição 20 graus)
  }
    delay(10);
  }
  else 
  {
    servoverti.write(servov);
  }
  
  if (avgleft > avgright)           // Se a media esquerda for maior que a media direita
  {
    servohori.write(servoh +1);    // Servo horizontal aumenta 1 grau
    if (servoh > servohLimitHigh)  // Se servo horizontal for maior que o limite max horizontal (160)
    {
    servoh = servohLimitHigh;     // Atribui ao servo horizontal limite maximo (160)
    }
    delay(10);
  }
  else if (avgright > avgleft)    // Se media da direita maior que media da esquerda
  {
    servohori.write(servoh -1); // Servo horizontal diminui 1 grau
    if (servoh < servohLimitLow) // Se servo horizontal for menor que limite min 
     {
     servoh = servohLimitLow;    // Atribui ao servo horizontal o limite minimo (20)
     }
    delay(10);
  }
  else 
  {
    servohori.write(servoh);
  }
  delay(50);
}
