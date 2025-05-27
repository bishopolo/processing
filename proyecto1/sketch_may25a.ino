


// // SIN TIEMPO DE EJECUCIÓN DE LOS MOVIMIENTOS
// // Incluimos libreria 
// #include <SoftwareSerial.h>

// // Instanciamos objeto SoftwareSerial para controlar el bluetooth
// SoftwareSerial hc06(2,3);

// // Definición pines EnA y EnB para el control de la velocidad
// int VelocidadMotor1 = 5; 
// int VelocidadMotor2 = 6;

// // Definición de los pines de control de giro de los motores In1, In2, In3 e In4
// int Motor1A = 12; 
// int Motor1B = 13;  
// int Motor2C = 7; 
// int Motor2D = 8;



// // Definición de la velocidad inicial de los motores
// int speedMotor = 180;

// // Variable para capturar el comando que llega desde la app
// String cmd = "";

// // NUEVA FUNCIONALIDAD: Variables para el sistema de protección de motores
// String lastCommand = "0";  // Guardamos el último comando ejecutado (inicia en stop)
// unsigned long lastCommandTime = 0;  // Tiempo del último comando
// const int MOTOR_PROTECTION_DELAY = 150;  // Tiempo de pausa en millisegundos para proteger motores

// void setup(){
//   // Serial Monitor
//   Serial.begin(9600);
   
//   // Bluetooth Serial Port
//   hc06.begin(9600);
 
  
//   // Establecemos modo de los pines del control de motores
//   pinMode(Motor1A, OUTPUT);
//   pinMode(Motor1B, OUTPUT);
//   pinMode(Motor2C, OUTPUT);
//   pinMode(Motor2D, OUTPUT);
//   pinMode(VelocidadMotor1, OUTPUT);
//   pinMode(VelocidadMotor2, OUTPUT);
 
//   // Configuramos velocidad de los dos motores
//   analogWrite(VelocidadMotor1, speedMotor);
//   analogWrite(VelocidadMotor2, speedMotor);
  
//   // Iniciamos con los motores detenidos para seguridad
//   stopCar();
  
//   Serial.println("Sistema iniciado - Protección de motores activada");
// }

// void loop(){
//   // Leemos los datos recibidos 
//   while(hc06.available() > 0){
//     cmd += (char)hc06.read();
//   }
 
//   // Programamos cada una de las acciones a realizar según el comando recibido
//   if(cmd != ""){
//     cmd = cmd[0];  // Tomamos solo el primer carácter
    
//     // PROTECCIÓN DE MOTORES: Verificamos si necesitamos pausa de seguridad
//     if(needsMotorProtection(cmd)){
//       Serial.println("Aplicando protección de motores...");
//       safeDirectionChange();
//     }
    
//     // Ejecutamos el comando solicitado
//     executeCommand(cmd);
    
//     // Actualizamos el registro del último comando para futura protección
//     lastCommand = cmd;
//     lastCommandTime = millis();
    
//     // Damos la orden como ejecutada y esperamos la siguiente
//     cmd = "";
//   }
// }

// // FUNCIÓN DE PROTECCIÓN: Determina si necesitamos aplicar pausa de seguridad
// bool needsMotorProtection(String newCommand){
//   // Si es el primer comando o es parar, no necesita protección
//   if(lastCommand == "0" || newCommand == "0"){
//     return false;
//   }
  
//   // Verificamos cambios peligrosos que requieren protección:
  
//   // 1. Cambio de adelante (1) a atrás (2) o viceversa
//   if((lastCommand == "1" && newCommand == "2") || (lastCommand == "2" && newCommand == "1")){
//     return true;
//   }
  
//   // 2. Cambio de giros básicos a movimientos opuestos
//   if((lastCommand == "3" && newCommand == "4") || (lastCommand == "4" && newCommand == "3")){
//     return true;
//   }
  
//   // 3. Cambio de movimientos diagonales hacia adelante a movimientos hacia atrás
//   if((lastCommand == "5" || lastCommand == "6") && (newCommand == "2" || newCommand == "H" || newCommand == "J")){
//     return true;
//   }
  
//   // 4. Cambio de movimientos diagonales hacia atrás a movimientos hacia adelante
//   if((lastCommand == "H" || lastCommand == "J") && (newCommand == "1" || newCommand == "5" || newCommand == "6")){
//     return true;
//   }
  
//   return false;  // No necesita protección
// }

// // FUNCIÓN DE PROTECCIÓN: Detiene motores y aplica pausa de seguridad
// void safeDirectionChange(){
//   // Primero detenemos completamente todos los motores
//   stopCar();
  
//   // Aplicamos pausa para que los motores se detengan completamente
//   // Esto previene picos de corriente y protege el hardware
//   delay(MOTOR_PROTECTION_DELAY);
  
//   Serial.println("Pausa de protección completada - Motores seguros para cambio de dirección");
// }

// // FUNCIÓN MEJORADA: Ejecuta el comando de manera segura
// void executeCommand(String command){
//   Serial.print("Ejecutando comando: ");
//   Serial.println(command);
  
//   if(command == "0"){
//     stopCar();
//   }else if(command == "1"){
//     moveForwardCar();
//   }else if(command == "2"){
//     moveBackwardsCar();
//   }else if(command == "3"){
//     turnLeftCar();
//   }else if(command == "4"){
//     turnRightCar();
//   }else if(command == "5"){
//     moveForwardLeft();
//   }else if(command == "6"){
//     moveForwardRight();
//   }else if(command == "H"){
//     moveBackwardsLeft();
//   }else if(command == "J"){
//     moveBackwardsRight();
//   }else{
//     Serial.println("Comando no reconocido - Deteniendo por seguridad");
//     stopCar();
//   }
// }

// void stopCar(){
//   // Paramos el carrito de forma segura
//   digitalWrite(Motor1A, LOW);
//   digitalWrite(Motor1B, LOW);                       
//   digitalWrite(Motor2C, LOW);
//   digitalWrite(Motor2D, LOW);
// }

// void turnRightCar(){
//   // Configuramos sentido de giro para girar a la derecha
//   // Solo el motor izquierdo gira hacia adelante, creando pivote
//   digitalWrite(Motor1A, HIGH);
//   digitalWrite(Motor1B, LOW);                       
//   digitalWrite(Motor2C, LOW);
//   digitalWrite(Motor2D, LOW);
// }

// void turnLeftCar(){
//   // Configuramos sentido de giro para girar a la izquierda
//   // Solo el motor derecho gira hacia adelante, creando pivote
//   digitalWrite(Motor1A, LOW);
//   digitalWrite(Motor1B, LOW);                       
//   digitalWrite(Motor2C, LOW);
//   digitalWrite(Motor2D, HIGH);
// }

// void moveForwardCar(){
//   // Configuramos ambos motores para avanzar en línea recta
//   digitalWrite(Motor1A, HIGH);
//   digitalWrite(Motor1B, LOW);                       
//   digitalWrite(Motor2C, LOW);
//   digitalWrite(Motor2D, HIGH);
// }

// void moveBackwardsCar(){
//   // Configuramos ambos motores para retroceder en línea recta
//   digitalWrite(Motor1A, LOW);
//   digitalWrite(Motor1B, HIGH);                       
//   digitalWrite(Motor2C, HIGH);
//   digitalWrite(Motor2D, LOW);
// }

// void moveForwardLeft(){
//   // Giramos a la izquierda mientras avanza (curva suave)
//   // Aumentamos temporalmente la velocidad del motor derecho
//   analogWrite(VelocidadMotor2, speedMotor + 60);
   
//   // Ambos motores van hacia adelante, pero uno más rápido
//   digitalWrite(Motor1A, HIGH);
//   digitalWrite(Motor1B, LOW);                       
//   digitalWrite(Motor2C, LOW);
//   digitalWrite(Motor2D, HIGH);
  
//   // Mantenemos la diferencia de velocidad por un momento
//   delay(20);
  
//   // Regresamos a velocidad normal para suavizar el movimiento
//   analogWrite(VelocidadMotor2, speedMotor);
// }

// void moveForwardRight(){
//   // Giramos a la derecha mientras avanza (curva suave)
//   // Aumentamos temporalmente la velocidad del motor izquierdo
//   analogWrite(VelocidadMotor1, speedMotor + 60);
     
//   // Ambos motores van hacia adelante, pero uno más rápido
//   digitalWrite(Motor1A, HIGH);
//   digitalWrite(Motor1B, LOW);                       
//   digitalWrite(Motor2C, LOW);
//   digitalWrite(Motor2D, HIGH);
    
//   // Mantenemos la diferencia de velocidad por un momento
//   delay(20);
  
//   // Regresamos a velocidad normal para suavizar el movimiento
//   analogWrite(VelocidadMotor1, speedMotor);
// }

// void moveBackwardsLeft(){
//   // Giramos a la izquierda mientras retrocede (curva suave hacia atrás)
//   // Aumentamos temporalmente la velocidad del motor derecho
//   analogWrite(VelocidadMotor2, speedMotor + 60);
     
//   // Ambos motores van hacia atrás, pero uno más rápido
//   digitalWrite(Motor1A, LOW);
//   digitalWrite(Motor1B, HIGH);                       
//   digitalWrite(Motor2C, HIGH);
//   digitalWrite(Motor2D, LOW);
  
//   // Mantenemos la diferencia de velocidad por un momento
//   delay(20);
  
//   // Regresamos a velocidad normal para suavizar el movimiento
//   analogWrite(VelocidadMotor2, speedMotor);
// }

// void moveBackwardsRight(){
//   // Giramos a la derecha mientras retrocede (curva suave hacia atrás)
//   // Aumentamos temporalmente la velocidad del motor izquierdo
//   analogWrite(VelocidadMotor1, speedMotor + 60);
     
//   // Ambos motores van hacia atrás, pero uno más rápido
//   digitalWrite(Motor1A, LOW);
//   digitalWrite(Motor1B, HIGH);                       
//   digitalWrite(Motor2C, HIGH);
//   digitalWrite(Motor2D, LOW);
  
//   // Mantenemos la diferencia de velocidad por un momento
//   delay(20);
  
//   // Regresamos a velocidad normal para suavizar el movimiento
//   analogWrite(VelocidadMotor1, speedMotor);
// }





// 1 SEC POR MOVIMIENTO

// Incluimos libreria 
#include <SoftwareSerial.h>

// Instanciamos objeto SoftwareSerial para controlar el bluetooth
SoftwareSerial hc06(2,3);

// Definición pines EnA y EnB para el control de la velocidad
int VelocidadMotor1 = 5; 
int VelocidadMotor2 = 6;

// Definición de los pines de control de giro de los motores In1, In2, In3 e In4
int Motor1A = 12; 
int Motor1B = 13;  
int Motor2C = 7; 
int Motor2D = 8;


// Definición de la velocidad inicial de los motores
int speedMotor = 180;

// Variable para capturar el comando que llega desde la app
String cmd = "";

// NUEVA FUNCIONALIDAD: Variables para el sistema de protección de motores
String lastCommand = "0";  // Guardamos el último comando ejecutado (inicia en stop)
unsigned long lastCommandTime = 0;  // Tiempo del último comando
const int MOTOR_PROTECTION_DELAY = 150;  // Tiempo de pausa en millisegundos para proteger motores

// NUEVA FUNCIONALIDAD: Variables para movimientos temporizados
bool isMoving = false;  // Indica si el carro está ejecutando un movimiento temporizado
unsigned long movementStartTime = 0;  // Momento en que inició el movimiento actual
const int MOVEMENT_DURATION = 1000;  // Duración de cada movimiento en milisegundos (1 segundo)

void setup(){
  // Serial Monitor
  Serial.begin(9600);
   
  // Bluetooth Serial Port
  hc06.begin(9600);
 
  
  // Establecemos modo de los pines del control de motores
  pinMode(Motor1A, OUTPUT);
  pinMode(Motor1B, OUTPUT);
  pinMode(Motor2C, OUTPUT);
  pinMode(Motor2D, OUTPUT);
  pinMode(VelocidadMotor1, OUTPUT);
  pinMode(VelocidadMotor2, OUTPUT);
 
  // Configuramos velocidad de los dos motores
  analogWrite(VelocidadMotor1, speedMotor);
  analogWrite(VelocidadMotor2, speedMotor);
  
  // Iniciamos con los motores detenidos para seguridad
  stopCar();
  
  Serial.println("Sistema iniciado - Protección de motores activada");
}

void loop(){
  // NUEVA FUNCIONALIDAD: Verificamos si hay un movimiento temporizado en progreso
  if(isMoving){
    // Calculamos cuánto tiempo ha pasado desde que inició el movimiento
    unsigned long elapsedTime = millis() - movementStartTime;
    
    // Si ya pasó el tiempo programado (1 segundo), detenemos el carro
    if(elapsedTime >= MOVEMENT_DURATION){
      stopCar();
      isMoving = false;  // Marcamos que ya no hay movimiento en progreso
      Serial.println("Movimiento completado - Carro detenido automáticamente");
    }
  }
  
  // Leemos los datos recibidos 
  while(hc06.available() > 0){
    cmd += (char)hc06.read();
  }
 
  // Programamos cada una de las acciones a realizar según el comando recibido
  if(cmd != ""){
    cmd = cmd[0];  // Tomamos solo el primer carácter
    
    // PROTECCIÓN DE MOTORES: Verificamos si necesitamos pausa de seguridad
    if(needsMotorProtection(cmd)){
      Serial.println("Aplicando protección de motores...");
      safeDirectionChange();
    }
    
    // Ejecutamos el comando solicitado
    executeCommand(cmd);
    
    // Actualizamos el registro del último comando para futura protección
    lastCommand = cmd;
    lastCommandTime = millis();
    
    // Damos la orden como ejecutada y esperamos la siguiente
    cmd = "";
  }
}

// FUNCIÓN DE PROTECCIÓN: Determina si necesitamos aplicar pausa de seguridad
bool needsMotorProtection(String newCommand){
  // Si es el primer comando o es parar, no necesita protección
  if(lastCommand == "0" || newCommand == "0"){
    return false;
  }
  
  // Verificamos cambios peligrosos que requieren protección:
  
  // 1. Cambio de adelante (1) a atrás (2) o viceversa
  if((lastCommand == "1" && newCommand == "2") || (lastCommand == "2" && newCommand == "1")){
    return true;
  }
  
  // 2. Cambio de giros básicos a movimientos opuestos
  if((lastCommand == "3" && newCommand == "4") || (lastCommand == "4" && newCommand == "3")){
    return true;
  }
  
  // 3. Cambio de movimientos diagonales hacia adelante a movimientos hacia atrás
  if((lastCommand == "5" || lastCommand == "6") && (newCommand == "2" || newCommand == "H" || newCommand == "J")){
    return true;
  }
  
  // 4. Cambio de movimientos diagonales hacia atrás a movimientos hacia adelante
  if((lastCommand == "H" || lastCommand == "J") && (newCommand == "1" || newCommand == "5" || newCommand == "6")){
    return true;
  }
  
  return false;  // No necesita protección
}

// FUNCIÓN DE PROTECCIÓN: Detiene motores y aplica pausa de seguridad
void safeDirectionChange(){
  // Primero detenemos completamente todos los motores
  stopCar();
  
  // Aplicamos pausa para que los motores se detengan completamente
  // Esto previene picos de corriente y protege el hardware
  delay(MOTOR_PROTECTION_DELAY);
  
  Serial.println("Pausa de protección completada - Motores seguros para cambio de dirección");
}

// FUNCIÓN MEJORADA: Ejecuta el comando de manera segura con temporización
void executeCommand(String command){
  Serial.print("Ejecutando comando: ");
  Serial.println(command);
  
  if(command == "0"){
    // El comando de parar es inmediato y cancela cualquier movimiento temporizado
    stopCar();
    isMoving = false;
    Serial.println("Carro detenido manualmente");
  }else if(command == "1"){
    startTimedMovement();
    moveForwardCar();
  }else if(command == "2"){
    startTimedMovement();
    moveBackwardsCar();
  }else if(command == "3"){
    startTimedMovement();
    turnLeftCar();
  }else if(command == "4"){
    startTimedMovement();
    turnRightCar();
  }else if(command == "5"){
    startTimedMovement();
    moveForwardLeft();
  }else if(command == "6"){
    startTimedMovement();
    moveForwardRight();
  }else if(command == "H"){
    startTimedMovement();
    moveBackwardsLeft();
  }else if(command == "J"){
    startTimedMovement();
    moveBackwardsRight();
  }else{
    Serial.println("Comando no reconocido - Deteniendo por seguridad");
    stopCar();
  }
}

// NUEVA FUNCIÓN: Inicia el sistema de temporización para movimientos
void startTimedMovement(){
  isMoving = true;  // Marcamos que hay un movimiento en progreso
  movementStartTime = millis();  // Guardamos el momento exacto en que inició
  Serial.println("Iniciando movimiento temporizado de 1 segundo");
}

void stopCar(){
  // Paramos el carrito de forma segura
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);                       
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, LOW);
}

void turnRightCar(){
  // Configuramos sentido de giro para girar a la derecha
  // Solo el motor izquierdo gira hacia adelante, creando pivote
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);                       
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, LOW);
}

void turnLeftCar(){
  // Configuramos sentido de giro para girar a la izquierda
  // Solo el motor derecho gira hacia adelante, creando pivote
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);                       
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, HIGH);
}

void moveForwardCar(){
  // Configuramos ambos motores para avanzar en línea recta
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);                       
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, HIGH);
}

void moveBackwardsCar(){
  // Configuramos ambos motores para retroceder en línea recta
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);                       
  digitalWrite(Motor2C, HIGH);
  digitalWrite(Motor2D, LOW);
}

void moveForwardLeft(){
  // Giramos a la izquierda mientras avanza (curva suave)
  // Aumentamos temporalmente la velocidad del motor derecho
  analogWrite(VelocidadMotor2, speedMotor + 60);
   
  // Ambos motores van hacia adelante, pero uno más rápido
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);                       
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, HIGH);
  
  // Mantenemos la diferencia de velocidad por un momento
  delay(20);
  
  // Regresamos a velocidad normal para suavizar el movimiento
  analogWrite(VelocidadMotor2, speedMotor);
}

void moveForwardRight(){
  // Giramos a la derecha mientras avanza (curva suave)
  // Aumentamos temporalmente la velocidad del motor izquierdo
  analogWrite(VelocidadMotor1, speedMotor + 60);
     
  // Ambos motores van hacia adelante, pero uno más rápido
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);                       
  digitalWrite(Motor2C, LOW);
  digitalWrite(Motor2D, HIGH);
    
  // Mantenemos la diferencia de velocidad por un momento
  delay(20);
  
  // Regresamos a velocidad normal para suavizar el movimiento
  analogWrite(VelocidadMotor1, speedMotor);
}

void moveBackwardsLeft(){
  // Giramos a la izquierda mientras retrocede (curva suave hacia atrás)
  // Aumentamos temporalmente la velocidad del motor derecho
  analogWrite(VelocidadMotor2, speedMotor + 60);
     
  // Ambos motores van hacia atrás, pero uno más rápido
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);                       
  digitalWrite(Motor2C, HIGH);
  digitalWrite(Motor2D, LOW);
  
  // Mantenemos la diferencia de velocidad por un momento
  delay(20);
  
  // Regresamos a velocidad normal para suavizar el movimiento
  analogWrite(VelocidadMotor2, speedMotor);
}

void moveBackwardsRight(){
  // Giramos a la derecha mientras retrocede (curva suave hacia atrás)
  // Aumentamos temporalmente la velocidad del motor izquierdo
  analogWrite(VelocidadMotor1, speedMotor + 60);
     
  // Ambos motores van hacia atrás, pero uno más rápido
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);                       
  digitalWrite(Motor2C, HIGH);
  digitalWrite(Motor2D, LOW);
  
  // Mantenemos la diferencia de velocidad por un momento
  delay(20);
  
  // Regresamos a velocidad normal para suavizar el movimiento
  analogWrite(VelocidadMotor1, speedMotor);
}