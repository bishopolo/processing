import processing.serial.*;
Serial port;
int estado = 0;  // 0: parado, 1: avanzar, 2: reversa

// Definición de botones
int buttonWidth = 120;
int buttonHeight = 40;
int buttonSpacing = 50;

void setup() {
  size(600, 400);
  port = new Serial(this, Serial.list()[0], 9600);
  textAlign(CENTER, CENTER);
  textSize(20);
}

void draw() {
  background(200);
  
  // Dibuja los tres botones
  // Botón Avanzar
  if (estado == 1) {
    fill(0, 255, 0);  // Verde si está activo
  } else {
    fill(220);  // Gris claro si está inactivo
  }
  rectMode(CENTER);
  rect(width/2 - buttonWidth - buttonSpacing, height/2, buttonWidth, buttonHeight, 10);
  fill(0);
  text("Avanzar", width/2 - buttonWidth - buttonSpacing, height/2);
  
  // Botón Parar
  if (estado == 0) {
    fill(255, 0, 0);  // Rojo si está activo
  } else {
    fill(220);  // Gris claro si está inactivo
  }
  rect(width/2, height/2, buttonWidth, buttonHeight, 10);
  fill(0);
  text("Parar", width/2, height/2);
  
  // Botón Reversa
  if (estado == 2) {
    fill(255, 255,0);  // Amarillo si está activo
  } else {
    fill(220);  // Gris claro si está inactivo
  }
  rect(width/2 + buttonWidth + buttonSpacing, height/2, buttonWidth, buttonHeight, 10);
  fill(0);
  text("Reversa", width/2 + buttonWidth + buttonSpacing, height/2);
  
  // Muestra el estado actual
  fill(0);
  textSize(24);
  String estadoTexto = "";
  if (estado == 0) estadoTexto = "Detenido";
  else if (estado == 1) estadoTexto = "Avanzando";
  else if (estado == 2) estadoTexto = "En reversa";
  
  text("Estado: " + estadoTexto, width/2, height/2 + 100);
}

void mousePressed() {
  // Verifica si se hizo clic en el botón Avanzar
  if (mouseX > width/2 - buttonWidth*1.5 - buttonSpacing && 
      mouseX < width/2 - buttonSpacing && 
      mouseY > height/2 - buttonHeight/2 && 
      mouseY < height/2 + buttonHeight/2) {
    estado = 1;
    port.write(estado + "\n");
  }
  // Verifica si se hizo clic en el botón Parar
  else if (mouseX > width/2 - buttonWidth/2 && 
           mouseX < width/2 + buttonWidth/2 && 
           mouseY > height/2 - buttonHeight/2 && 
           mouseY < height/2 + buttonHeight/2) {
    estado = 0;
    port.write(estado + "\n");
  }
  // Verifica si se hizo clic en el botón Reversa
  else if (mouseX > width/2 + buttonSpacing && 
           mouseX < width/2 + buttonWidth + buttonSpacing*2 && 
           mouseY > height/2 - buttonHeight/2 && 
           mouseY < height/2 + buttonHeight/2) {
    estado = 2;
    port.write(estado + "\n");
  }
  
  println("Estado actual: " + estado);
}
