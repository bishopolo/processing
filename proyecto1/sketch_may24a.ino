// #include <SoftwareSerial.h>

// #define enA 6
// #define enB 11
// #define in1 5
// #define in2 4
// #define in3 3
// #define in4 2
// #define servo 9
// #define tmpV 8

// int tiempo = 500;              // Tiempo base para movimientos lineales
// int tiempoGiro = 400;          // Tiempo para giros (ajustar según necesites)
// int estadoMotor = 0;           
// int estadoAnterior = 0;        
// int velocidad = 255;           // DIAGNÓSTICO: Usar velocidad máxima temporalmente
// const int tiempoPausa = 500;   

// void setup() {
//   // Configurar todos los pines como salida
//   pinMode(enA, OUTPUT);
//   pinMode(enB, OUTPUT);
//   pinMode(in1, OUTPUT);
//   pinMode(in2, OUTPUT);
//   pinMode(in3, OUTPUT);
//   pinMode(in4, OUTPUT);
  
//   // Comenzar con motores completamente detenidos
//   digitalWrite(in1, LOW);
//   digitalWrite(in2, LOW);
//   digitalWrite(in3, LOW);
//   digitalWrite(in4, LOW);
//   digitalWrite(enA, LOW);  // DIAGNÓSTICO: Regresamos a digitalWrite temporalmente
//   digitalWrite(enB, LOW);  // DIAGNÓSTICO: Regresamos a digitalWrite temporalmente
  
//   Serial.begin(9600);
  
//   // DIAGNÓSTICO: Mensaje de inicio para confirmar que el código se cargó
//   Serial.println("Sistema de diagnóstico iniciado");
//   Serial.println("Probando con digitalWrite en enables y giro diferencial");
// }

// void loop() {
//   // Verificar si hay datos disponibles en el puerto serial
//   if (Serial.available() > 0) {
//     estadoAnterior = estadoMotor;
//     estadoMotor = Serial.parseInt();
    
//     // Consumir cualquier caracter extra
//     while (Serial.available() > 0) {
//       Serial.read();
//     }
    
//     // DIAGNÓSTICO: Mensajes detallados para entender qué está pasando
//     Serial.print("Estado recibido: ");
//     Serial.println(estadoMotor);
//     Serial.print("Estado anterior: ");
//     Serial.println(estadoAnterior);
    
//     // Aplicar el estado a los motores con protección
//     controlarMotoresConSeguridad(estadoMotor, estadoAnterior);
//   }
// }

// void controlarMotoresConSeguridad(int nuevoEstado, int estadoAnterior) {
//   // Si estamos cambiando de avanzar a reversa o viceversa, detenernos primero
//   if ((estadoAnterior == 1 && nuevoEstado == 2) || (estadoAnterior == 2 && nuevoEstado == 1)) {
//     Serial.println("DIAGNÓSTICO: Cambio brusco detectado, aplicando pausa de seguridad");
//     controlarMotores(0);
//     delay(tiempoPausa);
//     controlarMotores(nuevoEstado);
//   } else {
//     controlarMotores(nuevoEstado);
//   }
// }

// void controlarMotores(int estado) {
//   // DIAGNÓSTICO: Reportar qué acción se va a ejecutar
//   Serial.print("DIAGNÓSTICO: Ejecutando estado ");
//   Serial.println(estado);
  
//   switch (estado) {
//     case 0:  // Parar
//       Serial.println("DIAGNÓSTICO: Deteniendo motores");
//       apagarMotores();
//       break;
      
//     case 1:  // Avanzar
//       Serial.println("DIAGNÓSTICO: Avanzando - ambos motores adelante");
//       // Configurar dirección hacia adelante para ambos motores
//       digitalWrite(in1, HIGH);  // Motor izquierdo: adelante
//       digitalWrite(in2, LOW);
//       digitalWrite(in3, HIGH);  // Motor derecho: adelante
//       digitalWrite(in4, LOW);
//       // DIAGNÓSTICO: Usar digitalWrite para máxima potencia
//       digitalWrite(enA, HIGH);  // Máxima velocidad al motor izquierdo
//       digitalWrite(enB, HIGH);  // Máxima velocidad al motor derecho
//       delay(tiempo);
//       apagarMotores();
//       Serial.println("DIAGNÓSTICO: Movimiento adelante completado");
//       break;
      
//     case 2:  // Reversa
//       Serial.println("DIAGNÓSTICO: Retrocediendo - ambos motores atrás");
//       // Configurar dirección hacia atrás para ambos motores
//       digitalWrite(in1, LOW);   // Motor izquierdo: atrás
//       digitalWrite(in2, HIGH);
//       digitalWrite(in3, LOW);   // Motor derecho: atrás
//       digitalWrite(in4, HIGH);
//       // DIAGNÓSTICO: Usar digitalWrite para máxima potencia
//       digitalWrite(enA, HIGH);  // Máxima velocidad al motor izquierdo
//       digitalWrite(enB, HIGH);  // Máxima velocidad al motor derecho
//       delay(tiempo);
//       apagarMotores();
//       Serial.println("DIAGNÓSTICO: Movimiento atrás completado");
//       break;
      
//     case 3:  // Girar a la Izquierda - GIRO DIFERENCIAL
//       Serial.println("DIAGNÓSTICO: Giro izquierda - motor izq atrás, motor der adelante");
//       // Motor izquierdo retrocede, motor derecho avanza
//       digitalWrite(in1, LOW);   // Motor izquierdo: hacia atrás
//       digitalWrite(in2, HIGH);
//       digitalWrite(in3, HIGH);  // Motor derecho: hacia adelante
//       digitalWrite(in4, LOW);
//       // DIAGNÓSTICO: Usar digitalWrite para máxima potencia en giro
//       digitalWrite(enA, HIGH);  // Motor izquierdo a máxima velocidad (atrás)
//       digitalWrite(enB, HIGH);  // Motor derecho a máxima velocidad (adelante)
//       delay(tiempoGiro);
//       apagarMotores();
//       Serial.println("DIAGNÓSTICO: Giro izquierda completado");
//       break;
      
//     case 4:  // Girar a la Derecha - GIRO DIFERENCIAL
//       Serial.println("DIAGNÓSTICO: Giro derecha - motor izq adelante, motor der atrás");
//       // Motor izquierdo avanza, motor derecho retrocede
//       digitalWrite(in1, HIGH);  // Motor izquierdo: hacia adelante
//       digitalWrite(in2, LOW);
//       digitalWrite(in3, LOW);   // Motor derecho: hacia atrás
//       digitalWrite(in4, HIGH);
//       // DIAGNÓSTICO: Usar digitalWrite para máxima potencia en giro
//       digitalWrite(enA, HIGH);  // Motor izquierdo a máxima velocidad (adelante)
//       digitalWrite(enB, HIGH);  // Motor derecho a máxima velocidad (atrás)
//       delay(tiempoGiro);
//       apagarMotores();
//       Serial.println("DIAGNÓSTICO: Giro derecha completado");
//       break;
      
//     default:
//       Serial.println("DIAGNÓSTICO: Estado no reconocido, deteniendo por seguridad");
//       apagarMotores();
//       break;
//   }
// }

// void apagarMotores(){
//   Serial.println("DIAGNÓSTICO: Función apagarMotores() ejecutada");
//   // Detener motores configurando todas las direcciones en LOW
//   digitalWrite(in1, LOW);
//   digitalWrite(in2, LOW);
//   digitalWrite(in3, LOW);
//   digitalWrite(in4, LOW);
//   // DIAGNÓSTICO: Usar digitalWrite para apagado
//   digitalWrite(enA, LOW);  // Apagar completamente motor izquierdo
//   digitalWrite(enB, LOW);  // Apagar completamente motor derecho
// }


#include <SoftwareSerial.h>

// Definición de pines para control de motores
// #define enA 6
// #define enB 11
#define enA A0
#define enB A1
#define in1 5
#define in2 4
#define in3 3
#define in4 2

// Configuración de SoftwareSerial para Bluetooth
// RX del Arduino (pin 12) conectado a TX del módulo Bluetooth
// TX del Arduino (pin 13) conectado a RX del módulo Bluetooth
SoftwareSerial bluetooth(13, 12);

// Variables de control del sistema
int tiempo = 500;              // Tiempo base para movimientos lineales en milisegundos
int tiempoGiro = 400;          // Tiempo específico para giros (ajustar según necesites para 90 grados)
int estadoMotor = 0;           // Estado actual: 0=parar, 1=avanzar, 2=reversa, 3=izquierda, 4=derecha
int estadoAnterior = 0;        // Para recordar el estado previo y aplicar protecciones
int velocidad = 255;           // Velocidad PWM para los motores (130-255 recomendado)
const int tiempoPausa = 500;   // Tiempo de pausa entre cambios bruscos de dirección

void setup() {
  // Configurar todos los pines de control de motores como salida
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Inicializar motores en estado completamente detenido
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);  // Usar analogWrite para control PWM preciso
  analogWrite(enB, 0);  // Usar analogWrite para control PWM preciso
  
  // Inicializar comunicación serie principal para debug (opcional)
  Serial.begin(9600);
  Serial.println("Sistema de control por Bluetooth iniciado");
  Serial.println("Esperando conexión Bluetooth...");
  
  // Inicializar comunicación Bluetooth a 9600 baudios (velocidad estándar HC-05/HC-06)
  bluetooth.begin(9600);
  
  // Enviar mensaje de confirmación por Bluetooth para verificar conexión
  bluetooth.println("Carro conectado y listo");
  bluetooth.println("Comandos: 0=Parar, 1=Avanzar, 2=Reversa, 3=Izquierda, 4=Derecha");
}

void loop() {
  // Verificar si hay datos disponibles desde el módulo Bluetooth
  if (bluetooth.available() > 0) {
    // Guardar el estado actual antes de leer el nuevo comando
    estadoAnterior = estadoMotor;
    
    // Leer el comando enviado desde la aplicación móvil
    estadoMotor = bluetooth.parseInt();
    
    // Limpiar cualquier caracter extra del buffer (como saltos de línea)
    while (bluetooth.available() > 0) {
      bluetooth.read();
    }
    
    // Validar que el comando recibido esté dentro del rango esperado
    if (estadoMotor >= 0 && estadoMotor <= 4) {
      // Confirmar recepción del comando por Bluetooth
      bluetooth.print("Comando recibido: ");
      bluetooth.println(estadoMotor);
      
      // También enviar confirmación por puerto serie para debug
      Serial.print("Bluetooth - Estado recibido: ");
      Serial.print(estadoMotor);
      Serial.print(" (anterior: ");
      Serial.print(estadoAnterior);
      Serial.println(")");
      
      // Ejecutar el comando con protecciones de seguridad
      controlarMotoresConSeguridad(estadoMotor, estadoAnterior);
    } else {
      // Comando fuera de rango, enviar mensaje de error
      bluetooth.println("ERROR: Comando no válido. Use 0-4");
      Serial.println("ERROR: Comando Bluetooth fuera de rango");
    }
  }
}

void controlarMotoresConSeguridad(int nuevoEstado, int estadoAnterior) {
  // Aplicar protección contra cambios bruscos de dirección
  // Si estamos cambiando de avanzar directamente a reversa o viceversa
  if ((estadoAnterior == 1 && nuevoEstado == 2) || (estadoAnterior == 2 && nuevoEstado == 1)) {
    bluetooth.println("Aplicando pausa de seguridad...");
    Serial.println("SEGURIDAD: Cambio brusco detectado, aplicando pausa");
    
    // Primero detener completamente los motores
    controlarMotores(0);
    
    // Esperar tiempo de seguridad para que los motores se detengan completamente
    delay(tiempoPausa);
    
    // Ahora sí aplicar el nuevo estado
    controlarMotores(nuevoEstado);
  } else {
    // Si no es un cambio peligroso, aplicar directamente
    controlarMotores(nuevoEstado);
  }
}

void controlarMotores(int estado) {
  // Reportar la acción que se va a ejecutar
  String accion = "";
  switch(estado) {
    case 0: accion = "PARANDO"; break;
    case 1: accion = "AVANZANDO"; break;
    case 2: accion = "RETROCEDIENDO"; break;
    case 3: accion = "GIRANDO IZQUIERDA"; break;
    case 4: accion = "GIRANDO DERECHA"; break;
  }
  
  bluetooth.println(accion);
  Serial.println("Ejecutando: " + accion);
  
  switch (estado) {
    case 0:  // Parar - Detener completamente todos los motores
      apagarMotores();
      bluetooth.println("Motores detenidos");
      break;
      
    case 1:  // Avanzar - Ambos motores hacia adelante
      // Configurar ambos motores para ir hacia adelante
      digitalWrite(in1, HIGH);  // Motor izquierdo: hacia adelante
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);  // Motor derecho: hacia adelante
      digitalWrite(in4, LOW);
      
      // Aplicar velocidad controlada usando PWM
      analogWrite(enA, velocidad);  // Motor izquierdo a velocidad especificada
      analogWrite(enB, velocidad);  // Motor derecho a velocidad especificada
      
      // Mantener el movimiento durante el tiempo especificado
      delay(tiempo);
      
      // Detener automáticamente después del movimiento
      apagarMotores();
      bluetooth.println("Avance completado");
      break;
      
    case 2:  // Reversa - Ambos motores hacia atrás
      // Configurar ambos motores para ir hacia atrás
      digitalWrite(in1, LOW);   // Motor izquierdo: hacia atrás
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);   // Motor derecho: hacia atrás
      digitalWrite(in4, HIGH);
      
      // Aplicar velocidad controlada usando PWM
      analogWrite(enA, velocidad);  // Motor izquierdo a velocidad especificada
      analogWrite(enB, velocidad);  // Motor derecho a velocidad especificada
      
      // Mantener el movimiento durante el tiempo especificado
      delay(tiempo);
      
      // Detener automáticamente después del movimiento
      apagarMotores();
      bluetooth.println("Reversa completada");
      break;
      
    case 3:  // Girar Izquierda - Giro diferencial (motor izquierdo atrás, derecho adelante)
      // Motor izquierdo retrocede mientras motor derecho avanza
      // Esto crea un giro sobre el eje central del carro
      digitalWrite(in1, LOW);   // Motor izquierdo: hacia atrás
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);  // Motor derecho: hacia adelante
      digitalWrite(in4, LOW);
      
      // Ambos motores trabajan a la misma velocidad en direcciones opuestas
      analogWrite(enA, velocidad);  // Motor izquierdo a velocidad completa (atrás)
      analogWrite(enB, velocidad);  // Motor derecho a velocidad completa (adelante)
      
      // Usar tiempo específico para giros para lograr aproximadamente 90 grados
      delay(tiempoGiro);
      
      // Detener automáticamente después del giro
      apagarMotores();
      bluetooth.println("Giro izquierda completado");
      break;
      
    case 4:  // Girar Derecha - Giro diferencial (motor izquierdo adelante, derecho atrás)
      // Motor izquierdo avanza mientras motor derecho retrocede
      // Esto crea un giro sobre el eje central del carro
      digitalWrite(in1, HIGH);  // Motor izquierdo: hacia adelante
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);   // Motor derecho: hacia atrás
      digitalWrite(in4, HIGH);
      
      // Ambos motores trabajan a la misma velocidad en direcciones opuestas
      analogWrite(enA, velocidad);  // Motor izquierdo a velocidad completa (adelante)
      analogWrite(enB, velocidad);  // Motor derecho a velocidad completa (atrás)
      
      // Usar tiempo específico para giros para lograr aproximadamente 90 grados
      delay(tiempoGiro);
      
      // Detener automáticamente después del giro
      apagarMotores();
      bluetooth.println("Giro derecha completado");
      break;
      
    default:
      // Estado no reconocido, detener por seguridad
      apagarMotores();
      bluetooth.println("ERROR: Estado no reconocido, deteniendo por seguridad");
      Serial.println("ERROR: Estado no válido, motors detenidos");
      break;
  }
}

void apagarMotores() {
  // Detener todos los movimientos configurando todas las direcciones en LOW
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  // Detener completamente la velocidad de ambos motores
  analogWrite(enA, 0);  // Detener motor izquierdo
  analogWrite(enB, 0);  // Detener motor derecho
  
  Serial.println("Motores apagados completamente");
}

