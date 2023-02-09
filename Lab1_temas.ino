

//**************** Librerias *****************
// Hola sofii

#include <DHT.h>



//*************** Puertos ********************
#define bombillo A1 //bombillo inteligente
#define pResistor A4 //Fotoresistor
#define alarma A7 //Led de alarma

//Sensor de temperatura y humedad

#define DHTPIN 2 // Pin del sensor de temperatura
#define DHTTYPE DHT11 // Tipo de sensor DHT 11
DHT dht(DHTPIN,DHTTYPE); // Función para definir sensor a utilizar

//*************** Variables ********************
int DUTY = 0; //PWM a 50% para no lastimar las plantas
int tiempoEncendido = 0;
int valor_foto = 0; //valor para almacenar datos del fotoresistor (0-1023)

//*************** Set UP ********************
void setup() {
  pinMode( bombillo, OUTPUT ); //bombillo inteligente
  pinMode( alarma, OUTPUT ); //bombillo inteligente
  pinMode( pResistor, INPUT ); 
 /* 
  while (millis()<2000);
  digitalWrite (bombillo,HIGH);
  while (millis()<(2000+8000));
  digitalWrite (LED_BUILTIN,LOW);*/
  dht.begin();
  Serial.begin(115200); 
}

void loop() {
  
  valor_foto = analogRead(pResistor); //Tomar valor del fotoresistor
  analogWrite( bombillo, DUTY );

  if (valor_foto > 500){
    DUTY = 0;
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (t >= 30){
      digitalWrite( alarma, HIGH );
    }
    else{
      digitalWrite( alarma, LOW );
    }

    Serial.println("----No oscurecio----"); 
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C ");

  }

  else{
    DUTY = 127;
    float h = dht.readHumidity();
    float t = dht.readTemperature();

        if (t >= 30){
      digitalWrite( alarma, HIGH );
    }
      else{
        digitalWrite( alarma, LOW );
      }

    Serial.println("----Oscurecio----"); 
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C ");

  }

  delay(2000); //Small delay
}