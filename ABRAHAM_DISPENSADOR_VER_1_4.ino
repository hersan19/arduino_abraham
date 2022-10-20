/* 
Programa: DISPENSADOR DE ALIMENTO POR PROXIMIDAD Y AUDITIVA  VER 1 By: ABRAHAM RIVERA
Autor:  JACK VENTURA
Web: www.AZTECACAMPISMO.WEBS.com
Canal de Youtube: 
Video Exclusivo para mi canal de Youtube
Todos los Derechos Reservados - ABRIL 21, 2022
Código de Dominio Público
CODIGO APORTADO EN COLABORACION CON LA COMUNIDAD ARDUINO
*/

#define PULSADOR 4        //integra DICE 2 
#define BUZZER_ACTIVO 7   //integra DICE 8 

int IN1 = 8;              // pin digital 8 de Arduino a IN1 de modulo controlador
int IN2 = 9;              // pin digital 9 de Arduino a IN2 de modulo controlador
int IN3 = 10;             // pin digital 10 de Arduino a IN3 de modulo controlador
int IN4 = 11;             // pin digital 11 de Arduino a IN4 de modulo controlador
int demora = 10;          // demora entre pasos, no debe ser menor a 10 ms.
                          // paso completo con maximo torque
int paso [4][4] =         // matriz (array bidimensional) con la secuencia de pasos
{
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {1, 0, 0, 1}
};               //1,2, 3, 4,5                     
int tiempos [2] = {3,5}; // 4posiciones = tiempos
int randNumber;
const int pinecho = 2;
const int pintrigger = 3;
int incomingByte = 0; // for incoming serial data
                                         

unsigned int tiempo, distancia;
//boolean leerSensor = true;                //DECIA true; LO CAMBIO A false y no hace lo que que haga 

void setup() 
{                           // put your setup code here, to run once:
  pinMode (PULSADOR, INPUT_PULLUP);         //integra (4,) Siempre recibe 5v, marca cuando se va 0 
  pinMode (BUZZER_ACTIVO, OUTPUT);          //integra // pin(7 - salida) 
                                      
  
  Serial.begin(9600);
  pinMode(pinecho, INPUT);
  pinMode(pintrigger, OUTPUT);
                                                                                    
  pinMode(IN1, OUTPUT);                             // todos los pines como salida
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {                                       // put your main code here, to run repeatedly:
                                                      //servoMotor.attach(4);  >>integra 1<<
  // int dex_tiempo = random(1,5);
  // randNumber = tiempos[dex_tiempo] * 1000;
  // Serial.println(randNumber);
  // if(digitalRead(PULSADOR) == LOW)
  // if(randNumber == 2)
  //{                   //integra
  if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
      delay(100);
      if(incomingByte == 49)
      {
        mover_motor();
      }
      // say what you got:
      Serial.print("I received: ");
      Serial.print(incomingByte);
      Serial.println(" ");
    }  
}

void mover_motor(){
  digitalWrite(BUZZER_ACTIVO, HIGH);              //integra   
  delay(1000); 
  digitalWrite(BUZZER_ACTIVO, LOW);
  long int t1 = millis();
  for (int i = 0; i < 32; i++)                          // DICE 512*4 = 2048 pasos <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    {
      for (int i = 0; i < 4; i++)                       // DICE 4 bucle recupera la matriz de a una fila por vez
      {                                                 // para obtener los valores logicos a aplicar
        digitalWrite(IN1, paso[i][0]);                  // a IN1, IN2, IN3 y IN4
        digitalWrite(IN2, paso[i][1]);
        digitalWrite(IN3, paso[i][2]);
        digitalWrite(IN4, paso[i][3]);
        delay (demora);
      }
    }
  digitalWrite (IN1, LOW);          // desenergiza las bobina con un 0 logico osea apagado.
  digitalWrite (IN2, LOW);
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);
  long int t2 = millis();
  //Serial.print("Time taken by the task_motor: "); Serial.print(t2-t1); Serial.println(" milliseconds");
  //delay (1000);  
}
