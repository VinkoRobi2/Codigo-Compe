#include "pitches.h"
#define LEDROJO 0
#define LEDAZUL 1
#define LEDVERDE 2
#define LEDAMARILLO 3
#define NUMLEDS 4 
#define TOTAL 32 

int leds[NUMLEDS] =    {2, 4, 6, 8};
int botones[NUMLEDS] = {3, 5, 7, 9};
int buzz = 10;

int partida[TOTAL], nivelActual = 0, nivelIndice = 0;


int jugada = 0;


int nuevoJuego=1;


int melody[] = {
NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
4, 8, 8, 4, 4, 4, 4, 4
};

void setup() 
{
  int i;

  for (i=0; i<NUMLEDS; i++)
  {
    pinMode(leds[i], OUTPUT);
    pinMode(botones[i], INPUT);
  }    
  
  pinMode(buzz, OUTPUT);
  randomSeed(analogRead(0));  
  Serial.begin(9600);
}

void loop() 
{               
    if (nuevoJuego)
    {
      llenarPartida();  
      nivelActual=0;
      nuevoJuego = 0;            
      ejecutarMelodia();
    }
    fxBarrido(30, 2);
    mostrarPartida(nivelActual, 300);

    while (!nuevoJuego && nivelIndice<=nivelActual) 
    {
      Serial.println("leyendo botones");
      Serial.println(partida[nivelIndice]);
      jugada = leerBotones();
      Serial.println(jugada);
      encender(jugada);
      delay(250);  
      apagar(jugada);    
      
      if (partida[nivelIndice] != jugada)
      {       
        Serial.println("Game Over");
        Serial.print("nivel ");
        Serial.println(nivelActual);
        nuevoJuego = 1;  
        fxBaliza(300, 4);               
      }   
      else
      { 
        nivelIndice++; 
        delay(250);                     
      }
    }                  
    nivelIndice = 0;
    nivelActual++;
}

int encender(int led)
{
    digitalWrite(leds[led], 1);
}


int apagar(int led)
{
    digitalWrite(leds[led], 0);
}

void encenderTodos(){
  int i;
  for (i=0; i<NUMLEDS; i++)
  {
    digitalWrite(leds[i], 1);
  }  
}

void apagarTodos()
{
  int i;
  for (i=0; i<NUMLEDS; i++)
  {
    digitalWrite(leds[i], 0);
  }
}


void fxBarrido(int demora, int repeticiones)
{
  int i, j;
  apagarTodos();
  for (i=0; i<=repeticiones; i++)
  {
      for (j=0; j<NUMLEDS; j++)
      {
        encender(j);
        if (j != 0)
        {
            apagar (j-1);            
        }
        delay(demora);
      }  
      for (j=NUMLEDS-2; j>=0; j--)
      {    
        encender(j);
        apagar(j+1);
        delay(demora);    
      }
  }
  apagarTodos();
}


void fxBaliza(int demora, int repeticiones)
{
    int i;
    for (i=0; i<=repeticiones; i++)
    {
        apagarTodos();
        delay(demora);
        encenderTodos();
        delay(demora);
    }
    apagarTodos();
    delay(demora);
}


void llenarPartida()
{  
    int i;
    for (i=0; i<TOTAL; i++)
    {
        partida[i] = random(NUMLEDS);  
    }
}


void mostrarPartida(int hasta, int demora)
{
  int i;
  for (i=0; i<=hasta; i++)
  {
    delay(demora);
    encender(partida[i]);
    delay(demora);
    apagar(partida[i]);
    delay(demora);
  }  
}


int leerBotones()
{
  int flag = 0, btn;
  while (!flag)
  {    
    if(digitalRead(botones[LEDROJO]) && !flag)
    {
      flag = 1;
      btn = LEDROJO;
    }
    if(digitalRead(botones[LEDVERDE]) && !flag)
    {
      flag = 1;
      btn = LEDVERDE;
    }
    if(digitalRead(botones[LEDAZUL]) && !flag)
    {
      flag = 1;
      btn = LEDAZUL;
    }
    if(digitalRead(botones[LEDAMARILLO]) && !flag)
    {
      flag = 1;
      btn = LEDAMARILLO;
    }    
  }
 return btn;
}

void ejecutarMelodia()
{

 for (int thisNote = 0; thisNote < 8; thisNote++) 
    {

     int noteDuration = 1000 / noteDurations[thisNote];
     tone(buzz, melody[thisNote], noteDuration);
    
     int pauseBetweenNotes = noteDuration * 1.30;
     delay(pauseBetweenNotes);

     noTone(buzz);
    }
}



