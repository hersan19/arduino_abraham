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
};                                      

const int pinecho = 2;
const int pintrigger = 3;

                                         

unsigned int tiempo, distancia;
boolean leerSensor = true;                //DECIA true; LO CAMBIO A false y no hace lo que que haga 

void setup() {                           // put your setup code here, to run once:
pinMode (PULSADOR, INPUT_PULLUP);         //integra 
pinMode (BUZZER_ACTIVO, OUTPUT);          //integra

Serial.begin(9600);
                                                     
pinMode(pinecho, INPUT);
pinMode(pintrigger, OUTPUT);
                                                                                   
pinMode(IN1, OUTPUT);                             // todos los pines como salida
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() 
{                                       // put your main code here, to run repeatedly:

if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
      delay(100);
      if(incomingByte == 49) // se pregunta si "incomingByte" = 1 ASCII = 49 
      {
        digitalWrite(BUZZER_ACTIVO, HIGH);              //integra   
        delay(1000); 
        digitalWrite(BUZZER_ACTIVO, LOW);
        digitalWrite(pintrigger, LOW);
        delayMicroseconds(2);
        digitalWrite(pintrigger, HIGH);
        delayMicroseconds(10);
        digitalWrite(pintrigger, LOW);
        tiempo = pulseIn(pinecho, HIGH);

        distancia = tiempo / 46;                             // DICE 58 CALIBRA DISTANCIA >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><

        Serial.print(distancia);
        Serial.println(" cm");
        delay(200);                       // DECIA 200                                             

        if (distancia <=40 && distancia >= 3 && leerSensor)
        {
          mover_motor_sin_sonido();
        }
        
      }
      // say what you got:
      Serial.print("I received: ");
      Serial.print(incomingByte);
      Serial.println(" ");
    }  


                                                    //servoMotor.attach(4);  >>integra 1<<
if(digitalRead(PULSADOR) == LOW)                   //integra
{
      for(int i = 0; i < 1; i++){                       //integra DECIA: 5 REPETICIONES<<<<<<ABRAHAM MODIFICA REPETICIONES >>>>
        digitalWrite(BUZZER_ACTIVO, HIGH);              //integra
        delay (1000);                                    //integra <<<<<<<DURACION DEL ZUMBIDO>>>>>
        digitalWrite(BUZZER_ACTIVO, LOW);               //integra
        delay (1000);                                     //integra <<<<<DURACION DEL RETARDO despues del zumbido para iniciar motor>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    while(false);{

    digitalWrite(pintrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(pintrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pintrigger, LOW);
    tiempo = pulseIn(pinecho, HIGH);

    distancia = tiempo / 46;                             // DICE 58 CALIBRA DISTANCIA >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><

    Serial.print(distancia);
    Serial.println(" cm");
    delay(200);                       // DECIA 200                                             

    if (distancia <=40 && distancia >= 3 && leerSensor) {   // DECIA <=16 && distancia >=8 && DICE ABRIR { <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    if(leerSensor){
    leerSensor =true;                                      // DECIA "FALSE" pero no repetia el bucle, solo se activa por una ocasion
    }
                                        
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
      delay (1000); 
      }
    }

      }
  }
    
                 


   }                                                // DICE CERRAR }
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

void mover_motor_sin_sonido(){

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
