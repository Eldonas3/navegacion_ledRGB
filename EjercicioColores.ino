//definimos los pines par el led
#define rojo D0
#define verde D1
#define azul D2

//definimos los pines para los botones
#define btn D5
#define btn2 D6
#define btn3 D7

bool btnState = LOW;
bool btn2State = LOW;
bool btn3State = LOW;
bool lastbtnState = LOW;
bool lastbtn2State = LOW;
bool lastbtn3State = LOW;
unsigned long lastDebounceTimebtn = 0;
unsigned long lastDebounceTimebtn2 = 0;
unsigned long lastDebounceTimebtn3 = 0;
unsigned long debounceDelay = 50;
unsigned long previousMillis = 0;
int indice = 1;
bool btnIzqPresOnce = false;
bool btnDerPresOnce = false;

//Definimos como debe ser un color RGB
typedef struct{
	int rojo;
  int verde;
	int azul;
}color;

//creamos un array de "colores" con los respectivos valores del color que quermos
//Colores rojo,naranja,amarillo,verde lima,verde,cian,agua marina,azul,indigo,violeta,magenta,blanco
color colores[] = {{0,255,255},{0,255,183},{92,255,103},{255,200,0},{255,255,0},{255,136,0},{207,52,118},{255,0,255},{4,26,47},{75,0,130},{0,0,255},{0,0,0}};
//indigo, aguamarina,verde lima
String nombres[] = {"rojo","naranja","amarillo","verde lima","verde","cian","agua marina","azul","indigo","violeta","magenta","blanco"};
// 0, 460, 1023 =>1023, 145, 0=> 
void setup() {
pinMode(rojo,OUTPUT);
pinMode(verde,OUTPUT);
pinMode(azul,OUTPUT);
pinMode(btn,INPUT);
pinMode(btn2,INPUT);
pinMode(btn3,INPUT);
analogWrite(rojo,1023);
analogWrite(verde,1023);
analogWrite(azul,1023);
Serial.begin(9600);
}

void loop() {

int btnReading = digitalRead(btn); //boton izquierdo
int btn2Reading = digitalRead(btn2); //boton derecho
int btn3Reading = digitalRead(btn3); //boton reinicio

  if (btnReading != lastbtnState) {
    lastDebounceTimebtn = millis(); // Registra el tiempo actual para debounce de btn
  }

  if (btn2Reading != lastbtn2State) {
    lastDebounceTimebtn2 = millis(); // Registra el tiempo actual para debounce de btn 2
  }

    if (btn3Reading != lastbtn3State) {
    lastDebounceTimebtn3 = millis(); // Registra el tiempo actual para debounce de btn3
  }

 if((millis()-lastDebounceTimebtn) > debounceDelay){
   if(btnReading != btnState){
      btnState = btnReading;
        if(btnState == HIGH){ //boton fue presionado 
            if(btnIzqPresOnce == false && btnDerPresOnce == false){ //si ninguno de los botones a sido presionado
              indice = 0;
              btnIzqPresOnce = true;            
            }    
            if(indice <= 11 && indice > 0){ //Si se encuentra entre los colores 1 y 11, sin en el 0
              indice = indice - 1;
              analogWrite(rojo,colores[indice].rojo);
              analogWrite(verde,colores[indice].verde);
              analogWrite(azul,colores[indice].azul);
              delay(50);
              Serial.println("Color actual: " + nombres[indice] + " Valores RGB: Rojo:" + colores[indice].rojo + " Verde:" + colores[indice].verde + " Azul:" + colores[indice].azul);//imprimos el nombre actual   y su valor rgb                         
            }

            if(indice == 0){ //si se encuentra al inicio
              analogWrite(rojo,colores[indice].rojo);
              analogWrite(verde,colores[indice].verde); //conserva el color del inicio
              analogWrite(azul,colores[indice].azul);
              delay(50);
              Serial.println("Color actual: " + nombres[indice] + " Valores RGB: Rojo:" + colores[indice].rojo + " Verde:" + colores[indice].verde + " Azul:" + colores[indice].azul);//imprimos el nombre actual   y su valor rgb         
            }
            
          }         
        }
   }    

  if((millis()-lastDebounceTimebtn2) > debounceDelay){
   if(btn2Reading != btn2State){
      btn2State = btn2Reading;
        if(btn2State == HIGH){ //boton fue presionado
              if(btnDerPresOnce == false && btnIzqPresOnce == false){ //comprueba si fue presionado una vez
              indice = 11;
              btnDerPresOnce = true;            
              }

              if(indice >= 0 && indice < 11){ //Si se encuentra entre los colores 0 y 10, sin en el 11
                indice = indice + 1;
                analogWrite(rojo,colores[indice].rojo);
                analogWrite(verde,colores[indice].verde);
                analogWrite(azul,colores[indice].azul);
                delay(50);
              Serial.println("Color actual: " + nombres[indice] + " Valores RGB: Rojo:" + colores[indice].rojo + " Verde:" + colores[indice].verde + " Azul:" + colores[indice].azul);//imprimos el nombre actual   y su valor rgb               
              }

              if(indice == 11){//si se encuentra al final
                analogWrite(rojo,colores[indice].rojo);
                analogWrite(verde,colores[indice].verde); //conserva el color del final
                analogWrite(azul,colores[indice].azul);
                delay(50);
              Serial.println("Color actual: " + nombres[indice] + " Valores RGB: Rojo:" + colores[indice].rojo + " Verde:" + colores[indice].verde + " Azul:" + colores[indice].azul);//imprimos el nombre actual   y su valor rgb               
              }
        }
   }   
 } 

   if((millis()-lastDebounceTimebtn3) > debounceDelay){
   if(btn3Reading != btn3State){
      btn3State = btn3Reading;
        if(btn3State == HIGH){ //boton fue presionado
          //reiniciamos el indice
          indice = 1;
          //reiniciamos los extremos visitados
          btnIzqPresOnce = false;
          btnDerPresOnce = false;          
          //apagamos el led
          analogWrite(rojo,1023);
          analogWrite(verde,1023);
          analogWrite(azul,1023);
          delay(50);
          Serial.print("LED RGB Apagado, Reiniciando");
          for(int x = 0;x < 10;x++){
            Serial.print(".");
            delay(200);
          }
          Serial.println("¡Reinicio completado!");
        }
   }   
 } 

lastbtnState = btnReading;
lastbtn2State = btn2Reading;
lastbtn3State = btn3Reading;

}
