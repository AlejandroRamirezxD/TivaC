// Botones de juego
#define Jugador1  PF_0
#define Jugador2  PF_4
#define BotonIni  PD_7

// Variable para restar
int Sub_Loop;
int Sub_Loop_Stop;

// Variables de lectura botones
int valJ1 = 0;
int valJ2 = 0;
int valBI = 0;

// Estados botones
int estado_push1 = 0;
int estado_push2 = 0;

// Variables de conteo 
int turno1 = 0;
int turno2 = 0;

// Semaforo
#define LED_R PF_1
#define LED_B PF_2
#define LED_G PF_3

// Leds de Jugador 2
#define Led_D0    PD_6
#define Led_D1    PC_7
#define Led_D2    PC_6
#define Led_D3    PC_5
#define Led_D4    PC_4
#define Led_D5    PB_3
#define Led_D6    PB_2
#define Led_D7    PA_2  

// Leds de Jugador 1
#define Led_I0    PA_7
#define Led_I1    PE_3
#define Led_I2    PE_2
#define Led_I3    PE_1
#define Led_I4    PD_3
#define Led_I5    PD_2
#define Led_I6    PD_1
#define Led_I7    PD_0  

void setup() {
  Serial.begin(9600);
  // Botones
  pinMode(Jugador1,INPUT_PULLUP);
  pinMode(Jugador2,INPUT_PULLUP);
  pinMode(BotonIni,INPUT_PULLUP);

  // Semaforo
  pinMode(LED_R, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_G, OUTPUT);
  
  // Leds Jugador2
  pinMode(Led_D0, OUTPUT);
  pinMode(Led_D1, OUTPUT);
  pinMode(Led_D2, OUTPUT);
  pinMode(Led_D3, OUTPUT);
  pinMode(Led_D4, OUTPUT);
  pinMode(Led_D5, OUTPUT);
  pinMode(Led_D6, OUTPUT);
  pinMode(Led_D7, OUTPUT);
    
  // Leds Jugador1
  pinMode(Led_I0, OUTPUT);
  pinMode(Led_I1, OUTPUT);
  pinMode(Led_I2, OUTPUT);
  pinMode(Led_I3, OUTPUT);
  pinMode(Led_I4, OUTPUT);
  pinMode(Led_I5, OUTPUT);
  pinMode(Led_I6, OUTPUT);
  pinMode(Led_I7, OUTPUT);

}

void loop() {
  valBI = digitalRead(BotonIni);
  Condiciones_Iniciales();

  if(!valBI){
    Secuencia_Color();
    Sub_Loop = 1;
  }else {
    Sub_Loop = 0;
  }

  
  while(Sub_Loop){  
    //No requiere antirrebote, lee el push de reset
    valBI = digitalRead(BotonIni);
    
    // Si el push de reset se activa, salir de while 
    if(!valBI){
      break;
    }

    // Condiciones para determinar ganador
    if(turno1 == 8 && turno2 < 8){
      Sub_Loop_Stop = 1;// Detiene el conteo de turnos
      S_Azul();
    }
    else if(turno1 < 8 && turno2 == 8){
      Sub_Loop_Stop = 1;// Detiene el conteo de turnos
      S_Rosado();
    }

    if(!Sub_Loop_Stop){ 
      valJ1 = digitalRead(Jugador1);
      valJ2 = digitalRead(Jugador2);
  
      Antirrebote(valJ1,&estado_push1,&turno1);
      Antirrebote(valJ2,&estado_push2,&turno2);

      switch(turno2){
        case 0:
          LI_Off();
          break;
        case 1:
          LI0();
          break;
        case 2:
          LI1();
          break;
        case 3:
          LI2();
          break;
        case 4:
          LI3();
          break;
        case 5:
          LI4();
          break;
        case 6:
          LI5();
          break;
        case 7:
          LI6();
          break;
        case 8:
          LI7();
          break;
      }
      switch(turno1){
        case 0:
          LD_Off();
          break;
        case 1:
          LD0();
          break;
        case 2:
          LD1();
          break;
        case 3:
          LD2();
          break;
        case 4:
          LD3();
          break;
        case 5:
          LD4();
          break;
        case 6:
          LD5();
          break;
        case 7:
          LD6();
          break;
        case 8:
          LD7();
          break;
      }
    } 
  }
}
// Funcion antirebote
void Antirrebote( int valJ, int *estado_push, int *turno){
  if(!valJ){
    *estado_push = HIGH;
  }  
  delay(5);
  
  if(valJ && *estado_push){
    *estado_push = LOW;
    *turno = *turno + 1;
  }
}

// Condiciones Iniciales
void Condiciones_Iniciales(){
  LI_Off ();
  LD_Off ();
  turno2 = 0;
  turno1 = 0;
  Sub_Loop_Stop = 0;
}

// Secuencia Color
void Secuencia_Color(){
    S_Verde();
    delay(1000);
    S_Amarillo();
    delay(1000);
    S_Rojo();
    delay(1000);
    S_Off();
}

// Colores
void S_Rojo(){
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_G, LOW);
}
void S_Amarillo(){
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_G, HIGH);
}
void S_Verde(){
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_G, HIGH);
}
void S_Azul(){
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_G, LOW);
}
void S_Rosado(){
  digitalWrite(LED_R, HIGH);
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_G, LOW);
}
void S_Off(){
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_G, LOW);
}

// Leds Jugador1
void LI_Off (){
  digitalWrite(Led_I0, LOW);
  digitalWrite(Led_I1, LOW);
  digitalWrite(Led_I2, LOW);
  digitalWrite(Led_I3, LOW);
  digitalWrite(Led_I4, LOW);
  digitalWrite(Led_I5, LOW);
  digitalWrite(Led_I6, LOW);
  digitalWrite(Led_I7, LOW); 
}
void LI0 (){
  digitalWrite(Led_I0, HIGH);
  digitalWrite(Led_I1, LOW);
  digitalWrite(Led_I2, LOW);
  digitalWrite(Led_I3, LOW);
  digitalWrite(Led_I4, LOW);
  digitalWrite(Led_I5, LOW);
  digitalWrite(Led_I6, LOW);
  digitalWrite(Led_I7, LOW); 
}     
void LI1 (){
  digitalWrite(Led_I0, LOW);
  digitalWrite(Led_I1, HIGH);
  digitalWrite(Led_I2, LOW);
  digitalWrite(Led_I3, LOW);
  digitalWrite(Led_I4, LOW);
  digitalWrite(Led_I5, LOW);
  digitalWrite(Led_I6, LOW);
  digitalWrite(Led_I7, LOW); 
} 
void LI2 (){
  digitalWrite(Led_I0, LOW);
  digitalWrite(Led_I1, LOW);
  digitalWrite(Led_I2, HIGH);
  digitalWrite(Led_I3, LOW);
  digitalWrite(Led_I4, LOW);
  digitalWrite(Led_I5, LOW);
  digitalWrite(Led_I6, LOW);
  digitalWrite(Led_I7, LOW); 
} 
void LI3 (){
  digitalWrite(Led_I0, LOW);
  digitalWrite(Led_I1, LOW);
  digitalWrite(Led_I2, LOW);
  digitalWrite(Led_I3, HIGH);
  digitalWrite(Led_I4, LOW);
  digitalWrite(Led_I5, LOW);
  digitalWrite(Led_I6, LOW);
  digitalWrite(Led_I7, LOW); 
}
void LI4 (){
  digitalWrite(Led_I0, LOW);
  digitalWrite(Led_I1, LOW);
  digitalWrite(Led_I2, LOW);
  digitalWrite(Led_I3, LOW);
  digitalWrite(Led_I4, HIGH);
  digitalWrite(Led_I5, LOW);
  digitalWrite(Led_I6, LOW);
  digitalWrite(Led_I7, LOW); 
}
void LI5 (){
  digitalWrite(Led_I0, LOW);
  digitalWrite(Led_I1, LOW);
  digitalWrite(Led_I2, LOW);
  digitalWrite(Led_I3, LOW);
  digitalWrite(Led_I4, LOW);
  digitalWrite(Led_I5, HIGH);
  digitalWrite(Led_I6, LOW);
  digitalWrite(Led_I7, LOW); 
}
void LI6 (){
  digitalWrite(Led_I0, LOW);
  digitalWrite(Led_I1, LOW);
  digitalWrite(Led_I2, LOW);
  digitalWrite(Led_I3, LOW);
  digitalWrite(Led_I4, LOW);
  digitalWrite(Led_I5, LOW);
  digitalWrite(Led_I6, HIGH);
  digitalWrite(Led_I7, LOW); 
}
void LI7 (){
  digitalWrite(Led_I0, LOW);
  digitalWrite(Led_I1, LOW);
  digitalWrite(Led_I2, LOW);
  digitalWrite(Led_I3, LOW);
  digitalWrite(Led_I4, LOW);
  digitalWrite(Led_I5, LOW);
  digitalWrite(Led_I6, LOW);
  digitalWrite(Led_I7, HIGH); 
}

// Leds Jugador2
void LD_Off (){
  digitalWrite(Led_D0, LOW);
  digitalWrite(Led_D1, LOW);
  digitalWrite(Led_D2, LOW);
  digitalWrite(Led_D3, LOW);
  digitalWrite(Led_D4, LOW);
  digitalWrite(Led_D5, LOW);
  digitalWrite(Led_D6, LOW);
  digitalWrite(Led_D7, LOW); 
}
void LD0 (){
  digitalWrite(Led_D0, HIGH);
  digitalWrite(Led_D1, LOW);
  digitalWrite(Led_D2, LOW);
  digitalWrite(Led_D3, LOW);
  digitalWrite(Led_D4, LOW);
  digitalWrite(Led_D5, LOW);
  digitalWrite(Led_D6, LOW);
  digitalWrite(Led_D7, LOW); 
}     
void LD1 (){
  digitalWrite(Led_D0, LOW);
  digitalWrite(Led_D1, HIGH);
  digitalWrite(Led_D2, LOW);
  digitalWrite(Led_D3, LOW);
  digitalWrite(Led_D4, LOW);
  digitalWrite(Led_D5, LOW);
  digitalWrite(Led_D6, LOW);
  digitalWrite(Led_D7, LOW); 
} 
void LD2 (){
  digitalWrite(Led_D0, LOW);
  digitalWrite(Led_D1, LOW);
  digitalWrite(Led_D2, HIGH);
  digitalWrite(Led_D3, LOW);
  digitalWrite(Led_D4, LOW);
  digitalWrite(Led_D5, LOW);
  digitalWrite(Led_D6, LOW);
  digitalWrite(Led_D7, LOW); 
} 
void LD3 (){
  digitalWrite(Led_D0, LOW);
  digitalWrite(Led_D1, LOW);
  digitalWrite(Led_D2, LOW);
  digitalWrite(Led_D3, HIGH);
  digitalWrite(Led_D4, LOW);
  digitalWrite(Led_D5, LOW);
  digitalWrite(Led_D6, LOW);
  digitalWrite(Led_D7, LOW); 
}
void LD4 (){
  digitalWrite(Led_D0, LOW);
  digitalWrite(Led_D1, LOW);
  digitalWrite(Led_D2, LOW);
  digitalWrite(Led_D3, LOW);
  digitalWrite(Led_D4, HIGH);
  digitalWrite(Led_D5, LOW);
  digitalWrite(Led_D6, LOW);
  digitalWrite(Led_D7, LOW); 
}
void LD5 (){
  digitalWrite(Led_D0, LOW);
  digitalWrite(Led_D1, LOW);
  digitalWrite(Led_D2, LOW);
  digitalWrite(Led_D3, LOW);
  digitalWrite(Led_D4, LOW);
  digitalWrite(Led_D5, HIGH);
  digitalWrite(Led_D6, LOW);
  digitalWrite(Led_D7, LOW); 
}
void LD6 (){
  digitalWrite(Led_D0, LOW);
  digitalWrite(Led_D1, LOW);
  digitalWrite(Led_D2, LOW);
  digitalWrite(Led_D3, LOW);
  digitalWrite(Led_D4, LOW);
  digitalWrite(Led_D5, LOW);
  digitalWrite(Led_D6, HIGH);
  digitalWrite(Led_D7, LOW); 
}
void LD7 (){
  digitalWrite(Led_D0, LOW);
  digitalWrite(Led_D1, LOW);
  digitalWrite(Led_D2, LOW);
  digitalWrite(Led_D3, LOW);
  digitalWrite(Led_D4, LOW);
  digitalWrite(Led_D5, LOW);
  digitalWrite(Led_D6, LOW);
  digitalWrite(Led_D7, HIGH); 
}
