import processing.serial.*;
Serial port;
int estado = 0;  // 0: parado, 1: avanzar, 2: reversa, 3: izquierda, 4: derecha
PImage webImg;
PImage paintImg;
PImage controlImg;

// Variables para el área de dibujo
boolean modoDibujo = false;// Si está en modo dibujo o no
int tamañoPaso = 50;         // Tamaño de cada línea en píxeles
PVector posicionActual;      // Posición actual del "carro" en el área de dibujo
ArrayList<Linea> lineas;     // Lista de todas las líneas dibujadas
color btn = #F7CD70;
color verde = #74FC6E;
// Área de dibujo
int areaX = 50;
int areaY = 50;
int areaAncho = 405;
int areaAlto = 305;

// Definición de botones
int buttonWidth = 100;
int buttonHeight = 35;
int buttonSpacing = 10;

// Clase para representar una línea
class Linea {
  PVector inicio, fin;
  boolean esDibujo;  // true si se dibujó en modo dibujo, false si solo es movimiento
  
  Linea(PVector inicio, PVector fin, boolean esDibujo) {
    this.inicio = inicio.copy();
    this.fin = fin.copy();
    this.esDibujo = esDibujo;
  }
}

void setup() {
  size(800, 500);
  smooth();
  
  // DEBUG: Ver todos los puertos disponibles
  println("=== PUERTOS DISPONIBLES ===");
  String[] puertos = Serial.list();
  for(int i = 0; i < puertos.length; i++) {
    println(i + ": " + puertos[i]);
  }
  
  // CAMBIO: Conectar al HC-06 via Bluetooth
  try {
    port = new Serial(this, "/dev/cu.HC-06", 9600); // Tu puerto Bluetooth
    println("✓ CONECTADO a /dev/cu.HC-06");
    delay(2000); // Esperar 2 segundos para estabilizar conexión
  } catch(Exception e) {
    println("✗ ERROR conectando: " + e.getMessage());
    println("Verifica que el HC-06 esté emparejado y conectado");
  }
  
  textAlign(CENTER, CENTER);
  
  // Inicializar variables de dibujo
  posicionActual = new PVector(areaX + areaAncho/2, areaY + areaAlto/2);
  lineas = new ArrayList<Linea>();
}

void draw() {
  background(240);
  dibujarAreaDibujo();
  dibujarControlesCarro();
  dibujarControlesDibujo();
  dibujarInformacion();
  
  // DEBUG: Mostrar estado de conexión
  fill(0);
  textAlign(LEFT);
  textSize(10);
  if (port != null) {
    text(" Bluetooth conectado", 10, height - 10);
  } else {
    text(" Bluetooth desconectado", 10, height - 10);
  }
}

void dibujarAreaDibujo() {
  // Marco del área de dibujo
  stroke(0);
  strokeWeight(2);
  fill(255);
  rect(areaX, areaY, areaAncho, areaAlto,  5);
  
  fill(0);
  textSize(16);
  textAlign(CENTER);
  text("Área de Dibujo ", areaX + areaAncho/2, areaY - 20);
  paintImg = loadImage("https://img.icons8.com/?size=18&id=ebCLKs-3cgGW&format=png&color=000000", "png");
  image(paintImg, areaX + areaAncho/2 + 60 , 25);
  
  // Dibujar todas las líneas
  strokeWeight(2);
  for (Linea linea : lineas) {
    if (linea.esDibujo) {
      stroke(255, 0, 0);  // Rojo para líneas de dibujo
    } else {
      stroke(230);        // Gris para movimientos sin dibujar
    }
    line(linea.inicio.x, linea.inicio.y, linea.fin.x, linea.fin.y);
  }
  
  // Dibujar posición actual del "carro"
  String url = "https://img.icons8.com/?size=18&id=90919&format=png&color=000000";
  imageMode(CENTER);
  webImg = loadImage(url, "png");
  //fill(0, 0, 0);
  noStroke();
  //ellipse(posicionActual.x, posicionActual.y, 8, 8);
  image(webImg, posicionActual.x, posicionActual.y);
  
  // Indicador de modo dibujo
  if (modoDibujo) {
    fill(verde);
    ellipse(areaX + areaAncho - 30, 40, 10 + sin(frameCount * 0.1) * 1.5, 10 + sin(frameCount * 0.1) * 1.5);
    fill(0);
    textSize(12);
    textAlign(LEFT);
    text("Dibujando", areaX + areaAncho - 55, 30);
    
  }
}

void dibujarControlesCarro() {
  textAlign(CENTER, CENTER);
  
  // Título
  fill(0);
  textSize(16);
  text("Controles del carro", 600, 25);
  controlImg = loadImage("https://img.icons8.com/?size=18&id=rCMgUHUAhuWi&format=png&color=000000", "png");
  image(controlImg, 677, 28);
  
  // Primera fila de botones (Avanzar, Parar, Reversa)
  int startY = areaY;
  textSize(14);
  // Botón Avanzar
  if (estado == 1) {
    fill(btn);
  } else {
    fill(220);
  }
  rect(500, startY, buttonWidth, buttonHeight, 5);
  fill(0);
  text("Avanzar", 550, startY + buttonHeight/2);
  
  // Botón Parar
  if (estado == 0) {
    fill(#FF655F);
  } else {
    fill(220);
  }
  rect(610, startY, buttonWidth, buttonHeight, 5);
  fill(0);
  text("Parar", 660, startY + buttonHeight/2);
  
  // Botón Reversa
  if (estado == 2) {
    fill(btn);
  } else {
    fill(220);
  }
  rect(555, startY + 50, buttonWidth, buttonHeight, 5);
  fill(0);
  text("Reversa", 605, startY + 50 + buttonHeight/2);
  
  // Segunda fila para los botones de giro
  // Botón Izquierda
  if (estado == 4) { // CAMBIO: era 3, ahora es 4
    fill(btn);
  } else {
    fill(220);
  }
  rect(500, startY + 100, buttonWidth, buttonHeight, 5);
  fill(0);
  text("Izquierda", 550, startY + 100 + buttonHeight/2);
  
  // Botón Derecha
  if (estado == 3) { // CAMBIO: era 4, ahora es 3
    fill(btn);
  } else {
    fill(220);
  }
  rect(610, startY + 100, buttonWidth, buttonHeight, 5);
  fill(0);
  text("Derecha", 660, startY + 100 + buttonHeight/2);
}

void dibujarControlesDibujo() {
  textAlign(CENTER, CENTER);
  
  // Título
  fill(0);
  textSize(16);
  text("Controles de Dibujo", 600, 220);
  
  // Botón modo dibujo(verde)
  if (modoDibujo) {
    fill(#74FC6E);
  } else {
    fill(220);
  }
  
  rect(500, 250, buttonWidth, buttonHeight, 5);
  fill(0);
  textSize(14);
  text("Dibujar", 550, 267);
  
  fill(#D3DDFF);
  rect(510 + buttonWidth, 250, buttonWidth, buttonHeight, 5);
  fill(0);
  textSize(14);
  text("Limpiar", 560 + buttonWidth, 267);
  
 
}

void dibujarInformacion() {
  fill(0);
  textSize(14);
  textAlign(LEFT);
  
  // Estado actual del robot
  String estadoTexto = "";
  if (estado == 0) estadoTexto = "Detenido";
  else if (estado == 1) estadoTexto = "Avanzando";
  else if (estado == 2) estadoTexto = "En reversa";
  else if (estado == 3) estadoTexto = "Girando derecha"; // CAMBIO
  else if (estado == 4) estadoTexto = "Girando izquierda"; // CAMBIO
  
  text("Estado carro: " + estadoTexto, 500, 340);
  text("Posición: (" + int(posicionActual.x - areaX) + ", " + int(posicionActual.y - areaY) + ")", 500, 360);
  text("Líneas dibujadas: " + contarLineasDibujo(), 500, 380);
}

int contarLineasDibujo() {
  int contador = 0;
  for (Linea linea : lineas) {
    if (linea.esDibujo) contador++;
  }
  return contador;
}

void moverEnDireccion(int direccion) {
  PVector nuevaPosicion = posicionActual.copy();
  
  // Calcular nueva posición según la dirección
  switch(direccion) {
    case 1: // Arriba/Avanzar
      nuevaPosicion.y -= tamañoPaso;
      break;
    case 2: // Abajo/Reversa
      nuevaPosicion.y += tamañoPaso;
      break;
    case 3: // Derecha (CAMBIO: era Izquierda)
      nuevaPosicion.x += tamañoPaso;
      break;
    case 4: // Izquierda (CAMBIO: era Derecha)
      nuevaPosicion.x -= tamañoPaso;
      break;
  }
  
  // Verificar que la nueva posición esté dentro del área de dibujo
  if (nuevaPosicion.x >= areaX && nuevaPosicion.x <= areaX + areaAncho &&
      nuevaPosicion.y >= areaY && nuevaPosicion.y <= areaY + areaAlto) {
    
    // Crear la línea
    Linea nuevaLinea = new Linea(posicionActual, nuevaPosicion, modoDibujo);
    lineas.add(nuevaLinea);
    
    // Actualizar posición
    posicionActual = nuevaPosicion;
    
    // CAMBIO PRINCIPAL: Enviar como número entero, no string
    estado = direccion;
    
    // DEBUG: Ver qué se está enviando
    if (port != null) {
      port.write(estado); // Sin "\n", solo el número
      println("✓ Enviado por Bluetooth: " + estado);
    } else {
      println("✗ ERROR: Puerto Bluetooth no conectado");
    }
  }
}

void mousePressed() {
  // Controles del robot
  if (mouseX >= 502 && mouseX <= 602 && mouseY >= 50 && mouseY <= 82) {
    moverEnDireccion(1); // Avanzar
  }
  else if (mouseX >= 610 && mouseX <= 710 && mouseY >= 50 && mouseY <= 82) {
    estado = 0; // Parar
    if (port != null) {
      port.write(estado); // CAMBIO: Sin "\n"
      println("✓ Enviado PARAR: " + estado);
    }
  }
  else if (mouseX >= 555 && mouseX <= 655 && mouseY >= 99 && mouseY <= 130) {
    moverEnDireccion(2); // Reversa
  }
  else if (mouseX >= 502 && mouseX <= 602 && mouseY >= 147 && mouseY <= 177) {
    moverEnDireccion(4); // Izquierda (CAMBIO: era 4, correcto)
  }
  else if (mouseX >= 610 && mouseX <= 710 && mouseY >= 147 && mouseY <= 177) {
    moverEnDireccion(3); // Derecha (CAMBIO: era 3, correcto)
  }
  
  // Control de modo dibujo
  else if (mouseX >= 495 && mouseX <= 598 && mouseY >= 250 && mouseY <= 283) {
    modoDibujo = !modoDibujo;
    println("Modo dibujo: " + modoDibujo);
  }
  
   // Control limpiar área
  else if (mouseX >= 610 && mouseX <= 709 && mouseY >= 250 && mouseY <= 283) {
    lineas.clear();
    posicionActual = new PVector(areaX + areaAncho/2, areaY + areaAlto/2);
  }
}

void keyPressed() {
  if (keyCode == UP || key == 'w' || key == 'W') {
    moverEnDireccion(1);
  }
  else if (keyCode == DOWN || key == 's' || key == 'S') {
    moverEnDireccion(2);
  }
  else if (keyCode == LEFT || key == 'a' || key == 'A') {
    moverEnDireccion(4); // CAMBIO: era 3, ahora 4 para izquierda
  }
  else if (keyCode == RIGHT || key == 'd' || key == 'D') {
    moverEnDireccion(3); // CAMBIO: era 4, ahora 3 para derecha
  }
  else if (key == ' ') {  //  espacio para alternar modo dibujo
    modoDibujo = !modoDibujo;
   //println("Modo dibujo: " + modoDibujo);
  }
  else if (key == 'r' || key == 'R') {  // r para limpiar 
    lineas.clear();
    posicionActual = new PVector(areaX + areaAncho/2, areaY + areaAlto/2);
    //println("Área de dibujo limpiada");
  }
}
