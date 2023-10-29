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
int indiceIzq = 0;
int indiceDer = 11;
bool indIzqVisitado = false;
bool indDerVisitado = false;

//Definimos como debe ser un color RGB
typedef struct{
	int rojo;
  int verde;
	int azul;
}color;

//creamos un array de "colores" con los respectivos valores del color que quermos
//Colores rojo,naranja,amarillo,verde lima,verde,cian,agua marina,azul indigo,violeta,magenta,rosa,blanco
// color colores[] = {{1023, 0, 0},{1023, 563, 0},{1023, 1023, 0},{256, 829, 256},{0, 512, 0},{0, 1023, 1023},{280, 542, 451},{193, 0, 423},{439, 0, 613},{1023, 0, 1023},{1023, 727, 772},{1023, 1023, 1023}};
color colores[] = {{0, 1023, 1023},{0, 460, 1023},{0, 0, 1023},{767, 194, 767},{1023, 511, 1023},{1023, 0, 0},{743, 481, 572},{830, 1023, 600},{584, 1023, 410},{0, 1023, 0},{0, 296, 251},{0, 0, 0}};
String nombres[] = {"rojo","naranja","amarillo","verde lima","verde","cian","agua marina","azul indigo","violeta","magenta","rosa","blanco"};
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
              if(indiceIzq != 11 && indDerVisitado == false){ //si el btnIzq no esta en el otro extremo y no ha estado en el otro extremo
              analogWrite(rojo,colores[indiceIzq].rojo);
              analogWrite(verde,colores[indiceIzq].verde); //usamos color actual
              analogWrite(azul,colores[indiceIzq].azul);
              delay(50);
              Serial.println("Color actual: " + nombres[indiceIzq] + " Valores RGB: Rojo:" + colores[indiceIzq].rojo + " Verde:" + colores[indiceIzq].verde + " Azul:" + colores[indiceIzq].azul);//imprimos el nombre actual   y su valor rgb            
              indiceIzq = indiceIzq  + 1;// avanzamos color    
          }  
        if(indDerVisitado == true){// si ya se llego al otro extremo
              analogWrite(rojo,colores[indiceIzq].rojo);
              analogWrite(verde,colores[indiceIzq].verde); //usamos color actual
              analogWrite(azul,colores[indiceIzq].azul);
              delay(50);
               Serial.println("Color actual: " + nombres[indiceIzq] + " Valores RGB: Rojo:" + colores[indiceIzq].rojo + " Verde:" + colores[indiceIzq].verde + " Azul:" + colores[indiceIzq].azul);//imprimos el nombre actual   y su valor rgb  
              if(indiceIzq == 0){ // si color actual es el primero otra vez
                indDerVisitado = false;  //marcamos el extremo derecho como no visitado              
              }else{indiceIzq = indiceIzq - 1;}  //retrocedemos un color       
        }        

        if(indiceIzq == 11){ //si btnIzq esta el extremo derecho
              analogWrite(rojo,colores[indiceIzq].rojo);
              analogWrite(verde,colores[indiceIzq].verde); //usamos color actual
              analogWrite(azul,colores[indiceIzq].azul);
              delay(50);
              Serial.println("Color actual: " + nombres[indiceIzq] + " Valores RGB: Rojo:" + colores[indiceIzq].rojo + 
              " Verde:" + colores[indiceIzq].verde + " Azul:" + colores[indiceIzq].azul);//imprimos el nombre actual   y su valor rgb   
              indDerVisitado = true; //marcamos como visitado el extremo derecho    
              // indiceIzq = indiceIzq - 1;  //retrocedemos un color                
        }  
           
          }         
        }
   }    

  if((millis()-lastDebounceTimebtn2) > debounceDelay){
   if(btn2Reading != btn2State){
      btn2State = btn2Reading;
        if(btn2State == HIGH){ //boton fue presionado
          if(indiceDer != 0 && indIzqVisitado == false){//si el btnDer no esta en el otro extremo y no ha estado en el otro extremo
              analogWrite(rojo,colores[indiceDer].rojo);
              analogWrite(verde,colores[indiceDer].verde); //usamos color actual
              analogWrite(azul,colores[indiceDer].azul);
              delay(50);
              Serial.println("Color actual: " + nombres[indiceDer] + " Valores RGB: Rojo:" + colores[indiceDer].rojo + 
              " Verde:" + colores[indiceDer].verde + " Azul:" + colores[indiceDer].azul);//imprimos el nombre actual   y su valor rgb  
              indiceDer = indiceDer - 1;//visitamos el otro color             
          }
          
          if(indIzqVisitado == true){ // si ya llego al otro extremo
              analogWrite(rojo,colores[indiceDer].rojo);
              analogWrite(verde,colores[indiceDer].verde); //usamos color actual
              analogWrite(azul,colores[indiceDer].azul);
              delay(50);
              Serial.println("Color actual: " + nombres[indiceDer] + " Valores RGB: Rojo:" + colores[indiceDer].rojo + 
              " Verde:" + colores[indiceDer].verde + " Azul:" + colores[indiceDer].azul);//imprimos el nombre actual   y su valor rgb
              if(indiceDer == 11){//si el color actual es el ultimo otra vez
                indIzqVisitado = false; //marcamos el extremo izquierdo como no visitado
              }else{indiceDer = indiceDer + 1;}  //aumentamos un color   
                                             
          }    

          if(indiceDer == 0){//si el btnDer esta en el otro extremo
              analogWrite(rojo,colores[indiceDer].rojo);
              analogWrite(verde,colores[indiceDer].verde); //usamos color actual
              analogWrite(azul,colores[indiceDer].azul);
              delay(50);
              Serial.println("Color actual: " + nombres[indiceDer] + " Valores RGB: Rojo:" + colores[indiceDer].rojo + 
              " Verde:" + colores[indiceDer].verde + " Azul:" + colores[indiceDer].azul);//imprimos el nombre actual   y su valor rgb 
              indIzqVisitado = true;  //marcamos como visitado el extremo izquierdo
              // indiceDer = indiceDer + 1; //avanzamos al siguiente color
         }                  
        
        }
   }   
 } 

   if((millis()-lastDebounceTimebtn3) > debounceDelay){
   if(btn3Reading != btn3State){
      btn3State = btn3Reading;
        if(btn3State == HIGH){ //boton fue presionado
          //reiniciamos los indices a sus posiciones originales
          indiceIzq = 0;
          indiceDer = 11;
          //reiniciamos los extremos visitados
          indIzqVisitado = false;
          indDerVisitado = false;          
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
