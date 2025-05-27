#include <SoftwareSerial.h>
#include <Servo.h>

// Definición de pines para control de motores
#define enA 5
#define enB 6
#define in1 12
#define in2 13
#define in3 7
#define in4 8
#define servo 11

SoftwareSerial bluetooth(2, 3); // Configuración de para bluetooth tx, rx

// Variables de control del sistema
Servo lapiz;
//const int POSICION_ARRIBA = 5;    // Lápiz alzado (posición por defecto)
//const int POSICION_ABAJO = 25;    // Lápiz abajo (dibujando)
//int posicionActualServo = POSICION_ARRIBA; // Siempre inicia en posición arriba

int tiempo = 1000;              // Tiempo base para avanzar y retroceder
int tiempoGiro = 400;          // Tiempo base para giros
int estadoMotor = 0;           // Estado actual: 0=parar, 1=avanzar, 2=reversa, 3=izquierda, 4=derecha
int estadoAnterior = 0;       
int velocidad = 200;          
const int tiempoPausa = 500;   // Tiempo entre cambios bruscos de dirección

void setup() {
  // Configurar todos los pines de control de motores como salida
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Por defecto se apagan motores al prender el carro
  apagarMotores();
  
  // Configuración del servo - SIEMPRE va a posición inicial
 //lapiz.attach(servo);
  //delay(1000);
  //lapiz.write(POSICION_ARRIBA);
  //delay(300);
  //posicionActualServo = POSICION_ARRIBA;

  // Inicializar comunicación serie principal y bluetooth
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  // Enviar mensaje de confirmación por Bluetooth para verificar conexión
  bluetooth.println("Carro conectado y listo");
  bluetooth.println("Lapiz en posición inicial (arriba)");
  bluetooth.println("Comandos: 0=Parar, 1=Avanzar, 2=Reversa, 3=Izquierda, 4=Derecha");
  bluetooth.println("Servo: 5=Subir lapiz, 6=Bajar lapiz");
   pinMode(LED_BUILTIN, OUTPUT);
  for(int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
}

// ------ NUEVA FUNCIÓN CORRECTA ------
// void controlarLapiz(int comando) {
//   if (comando == 5) {
//     if (posicionActualServo == POSICION_ARRIBA) {
//       bluetooth.println("Lapiz ya está arriba - No se mueve");
//     } else {
//       bluetooth.println("SUBIENDO LAPIZ...");
//       moverServoGradual(posicionActualServo, POSICION_ARRIBA);
//       posicionActualServo = POSICION_ARRIBA;
//       bluetooth.println("Lapiz subido");
//     }
//   } else if (comando == 6) {
//     if (posicionActualServo == POSICION_ABAJO) {
//       bluetooth.println("Lapiz ya está abajo - No se mueve");
//     } else {
//       bluetooth.println("BAJANDO LAPIZ...");
//       moverServoGradual(posicionActualServo, POSICION_ABAJO);
//       posicionActualServo = POSICION_ABAJO;
//       bluetooth.println("Lapiz bajado");
//     }
//   }
// }

// // Mueve desde 'desde' hasta 'hacia' con suavidad
// void moverServoGradual(int desde, int hacia) {
//   if (desde < hacia) {
//     for (int pos = desde; pos <= hacia; pos++) {
//       lapiz.write(pos);
//       delay(25);
//     }
//   } else {
//     for (int pos = desde; pos >= hacia; pos--) {
//       lapiz.write(pos);
//       delay(25);
//     }
//   }
//   lapiz.write(hacia);
// }

void loop() {
    // Verificar si hay datos disponibles desde el módulo Bluetooth
    if (bluetooth.available() > 0) {
       Serial.println("=== DATO RECIBIDO ===");
    // Guardar estado actual antes de leer el nuevo comando
    estadoAnterior = estadoMotor;
    // Leer el comando enviado desde la aplicación móvil
    estadoMotor = bluetooth.parseInt();
    // Limpiar cualquier caracter extra del buffer (como saltos de línea)
    while (bluetooth.available() > 0) {
      bluetooth.read();
    }
    // Validar que el comando recibido esté en el rango 0-4
    if (estadoMotor >= 0 && estadoMotor <= 4) {
      bluetooth.print("Comando recibido: ");
      bluetooth.println(estadoMotor);   
      controlarMotoresConSeguridad(estadoMotor, estadoAnterior);
    } else if(estadoMotor >= 5 && estadoMotor <= 6){
      bluetooth.println("Comando de lapiz recibido");
      //controlarLapiz(estadoMotor);
    }else  {
      bluetooth.println("ERROR: Comando no válido ");
    }
  }
}


void controlarMotoresConSeguridad(int nuevoEstado, int estadoAnterior) {
  // Aplicar protección contra cambios bruscos de dirección
  if ((estadoAnterior == 1 && nuevoEstado == 2) || (estadoAnterior == 2 && nuevoEstado == 1)) {
    controlarMotores(0); // Primero detener los motores
    // tiempo de seguridad para que los motores se detengan 
    delay(tiempoPausa);
    controlarMotores(nuevoEstado);
  } else {
    // Si no hay cambio peligroso, aplicar directamente
    controlarMotores(nuevoEstado);
  }
}

void controlarMotores(int estado) {
  // mostrar acción a ejecutar
  String accion = "";
  switch(estado) {
    case 0: accion = "PARANDO"; break;
    case 1: accion = "AVANZANDO"; break;
    case 2: accion = "RETROCEDIENDO"; break;
    case 3: accion = "GIRANDO IZQUIERDA"; break;
    case 4: accion = "GIRANDO DERECHA"; break;
  }
  
  bluetooth.println(accion);
  
  switch (estado) {
    case 0:  // Parar - Detener completamente todos los motores
      apagarMotores();
      bluetooth.println("Motores detenidos");
      break;
      
    case 1:  // Avanzar - Ambos motores hacia adelante, ambos motores para ir hacia adelante
      digitalWrite(in1, HIGH);  // Motor izquierdo: hacia adelante
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);  // Motor derecho: hacia adelante
      digitalWrite(in4, LOW);
      // velocidad controlada usando PWM
      analogWrite(enA, velocidad); 
      analogWrite(enB, velocidad); 
      delay(tiempo);  // Mantener el movimiento durante el tiempo especificado
      apagarMotores(); // Detener automáticamente después del movimiento
      bluetooth.println("Avance completado");
      break;
      
    case 2:  // Reversa - Ambos motores hacia atrás
      digitalWrite(in1, LOW);   // Motor izquierdo: hacia atrás
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);   // Motor derecho: hacia atrás
      digitalWrite(in4, HIGH);
      // velocidad controlada usando PWM
      analogWrite(enA, velocidad);  
      analogWrite(enB, velocidad); 
      delay(tiempo * 1.2);  // Mantener el movimiento durante el tiempo especificado
      apagarMotores();   // Detener automáticamente después del movimiento
      bluetooth.println("Reversa completada");
      break;
      
    case 4:  // Girar Izquierda - motor izquierdo atrás, derecho adelante
      digitalWrite(in1, LOW);   // Motor izquierdo: hacia atrás
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);  // Motor derecho: hacia adelante
      digitalWrite(in4, LOW);
      // velocidad controlada usando PWM
      analogWrite(enA, velocidad + 20);  
      analogWrite(enB, velocidad + 20); 
      delay(tiempoGiro * 1.6); // Mantener el movimiento durante el tiempo especificado
      apagarMotores(); // Detener automáticamente después del giro
      bluetooth.println("Giro izquierda completado");
      break;
      
    case 3:  // Girar Derecha - motor izquierdo adelante, derecho atrás
      digitalWrite(in1, HIGH);  // Motor izquierdo: hacia adelante
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);   // Motor derecho: hacia atrás
      digitalWrite(in4, HIGH);
      // velocidad controlada usando PWM
      analogWrite(enA, velocidad + 20);  
      analogWrite(enB, velocidad + 20);
      delay(tiempoGiro * 1.6); // Mantener el movimiento durante el tiempo especificado
      apagarMotores();  // Detener automáticamente después del giro
      bluetooth.println("Giro derecha completado");
      break;
      
    default:
      // Estado no reconocido, detener por seguridad
      apagarMotores();
      bluetooth.println("ERROR: Estado no reconocido, deteniendo por seguridad");
      break;
  }
}

void apagarMotores() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  // Detener completamente la velocidad de ambos motores
  analogWrite(enA, 0);  
  analogWrite(enB, 0); 
}