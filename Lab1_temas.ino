//**************** Librerias *****************
#include <DHT.h> //Librería sensor

//*************** Puertos ********************
#define bombillo  9 //bombillo inteligente
#define pResistor A4 //Fotoresistor
#define alarma    19 //Led de alarma

//Sensor de temperatura y humedad
#define DHTPIN  2 // Pin del sensor de temperatura
#define DHTTYPE DHT11 // Tipo de sensor DHT 11
DHT dht(DHTPIN,DHTTYPE); // Función para definir sensor a utilizar

//*************** Variables ********************
int valor_foto = 0; //valor para almacenar datos del fotoresistor (0-1023)
const int limite_foto = 800; //Limite para fotoresistor (0-1023)
bool oscurecio = false; // Bandera Oscurecio o no
float temperatura = 0; //Temperatura tomada por el sensor
const int temp_maxima = 30; //Temperatura máxima para activar a alarma
float humedad = 0; //Humedad tomada por el sensor
int Duty = 0; //Ciclo de trabajo para encender bombillo 
int sampleTime = 0; //Tiempo de muestreo en ms
unsigned long sample_start; //Tiempo que ha transcurrido
unsigned long sample_current; //Tiempo que ha transcurrido
unsigned long sample_total; //Tiempo entre currentTime y startTime
bool Serial_stringComplete = false; //Bandera para enviar datos
String Serial_inputString = ""; //String que debe recibirse del serial

//*************** Set UP ********************
void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando");
  pinMode( bombillo, OUTPUT ); //bombillo inteligente
  pinMode( alarma, OUTPUT ); //alarma
  pinMode( pResistor, INPUT ); //Fotoresistor
  dht.begin(); //Sensor
  sample_start = millis();
}


//*************** Loop ********************
void loop() { 
  serialEvent();

  if(Serial_stringComplete){
    analyzeSensorString();
    Serial_inputString = "";
    Serial_stringComplete = false;
  }

  tomarDatos();
  
}


//*************** Funciones ********************


//*************** Función para leer nueva data de entrada ********************
void serialEvent(){
  while(Serial.available()>0){
    char inChar = (char)Serial.read();
    Serial_inputString += inChar;
    if ((byte(inChar) == 10)){ //Solo lo puede leer como byte el enter, no como \n
      Serial_stringComplete = true;
    }      
  }
}


//*************** Función para buscar bandera true ********************
void analyzeSensorString(){
  if(Serial_inputString.indexOf("uno")!= -1){
    sampleTime = 1000;
    Serial.println("1 segundo");
    }

  else if (Serial_inputString.indexOf("cinco")!= -1){
    sampleTime = 5000;
    Serial.println("5 segundos");
  }

    else if (Serial_inputString.indexOf("diez")!= -1){
    sampleTime = 10000;
    Serial.println("10 segundos");
  }
}

//*************** Funcion para tomar temperatura y humedad ********************
void tomarTempHumedad(){  
  temperatura = dht.readTemperature();
  humedad = dht.readHumidity();
  if(temperatura >= temp_maxima){
    digitalWrite(alarma,HIGH);
  }  
}

//*************** Funcion para tomar valor del fotoresistor ********************
void leerFotoresistor(){
  valor_foto = analogRead(pResistor); //Tomar valor del fotoresistor

  if (valor_foto > limite_foto){
    oscurecio = false;
    Duty = 0;
  }

  else{
    oscurecio = true;
    Duty = 127; //50% para no lastimar a las plantas
  }

  analogWrite(bombillo, Duty); // Bombillo permanece apagado
}

//*************** Funcion para enviar datos al monitor serial ********************
void envioSerial(){  
  Serial.println(temperatura);
  Serial.println(humedad);
  Serial.println(oscurecio);
}

void tomarDatos(){
    //Tomar tiempo actual
  sample_current = millis();

  //Tomar cuanto tiempo ha transcurrido desde el último muestreo
  sample_total = sample_current - sample_start;

  if (sampleTime != 0){
    if (sample_total >= sampleTime)
    {
      leerFotoresistor();
      tomarTempHumedad();
      envioSerial();
      sample_start = millis();
    }
  }

}