int x, y;          // Posición de la serpiente
int size = 20;     // Tamaño del rectángulo (segmento de la serpiente)
int speed = 10;    // Velocidad (moverá de a 20 pixeles para que cuadre en la "rejilla")

void setup() {
  size(600, 400);
  x = width / 2;
  y = height / 2;
  rectMode(CORNER);
}

void draw() {
  background(0);
  
  // Dibuja la serpiente (un rectángulo)
  fill(0, 255, 0);
  rect(x, y, size, size);
}

void keyPressed() {
  if (keyCode == UP) {
    y -= speed;
  } else if (keyCode == DOWN) {
    y += speed;
  } else if (keyCode == LEFT) {
    x -= speed;
  } else if (keyCode == RIGHT) {
    x += speed;
  }
  
  // Evitar que la serpiente salga de la ventana
  x = constrain(x, 0, width - size);
  y = constrain(y, 0, height - size);
}
