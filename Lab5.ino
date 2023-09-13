const int buttonPin1 = PUSH1;     // the number of the pushbutton pin
const int buttonPin = PUSH2;     // the number of the pushbutton pin
const int ledPin =  GREEN_LED;      // the number of the LED pin
const int ledPin2 =  BLUE_LED;      // the number of the LED pin
const int ledPin3 =  RED_LED;      // the number of the LED pin

const int J1[8] = {2, 3, 4, 5, 6, 7, 8, 9};
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int buttonP1 = 0;
int Cont = 0;
int bandera =0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
  Serial.begin(9600);  // Iniciar la comunicación serial para depuración     
 
  for (int i = 0; i < 8; i++) 
  {
    pinMode(J1[i],OUTPUT);
    digitalWrite(J1[i],LOW);
    
  }
}

void loop() {
  // Leer el estado de los botones
  buttonState = digitalRead(buttonPin);
  buttonP1 = digitalRead(buttonPin1);

  // Comprobar si se presionó el botón buttonPin
  if (buttonState == LOW && bandera == 0) {
    // Secuencia de encendido y apagado de LEDs
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin3, HIGH); 
    digitalWrite(ledPin2, LOW);
    delay(500);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin, HIGH); 
    digitalWrite(ledPin2, LOW);
    delay(500);
    digitalWrite(ledPin2, LOW);  
    digitalWrite(ledPin3, LOW); 
    digitalWrite(ledPin, HIGH);
    delay(500);

    // Establecer bandera en 1:
    bandera = 1;
  }

  // Si bandera es 1, permite cambiar el estado de los pines de J1
  if (bandera == 1 && buttonP1 == LOW) {
  // Apagar todos los pines en J1
  for (int i = 0; i < 8; i++) {
    digitalWrite(J1[i], LOW);
  }
  
  // Incrementar el contador y asegurarse de que no sea mayor que el número máximo de pines
  Cont+=1;
  if (Cont > 8) {
    Cont = 0;
  }
  
  // Encender el siguiente pin en J1
  digitalWrite(J1[Cont-1], HIGH);
  // Esperar un tiempo para evitar múltiples detecciones del botón
  delay(500);
}
  
  // Restablecer bandera a 0 después de encender y apagar todos los pines del puerto B
  if (Cont == 0 && buttonP1 == LOW) {
    bandera = 0;
   //  Apagar todos los pines en PORTB
    for (int i = 0; i < 8; i++) {
      digitalWrite(J1[i], LOW);
    }
  }
}
