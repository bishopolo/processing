void setup(){
 size(640, 360);
  
     background(40);

}

float x = random(width), y = random(height);
float r = random(50, 250), g = random(100, 250), b = random(100, 250);
float alpha = random(100, 250);
float widthCircle = random(50);

void draw(){

  // para que se note algo de transparencia
  //fill(r, g, b, 50);
  
  // usamos una variable alpha para tener varios grados de transparencia
  fill(r, 0, 0, alpha);
  
  // usamos solo un color para en este caso el red
  //fill(r, 10, 10, 250); 
  //circle(mouseX, mouseY, 20);
  //circle(x, y, widthCircle);
  square(x, y, widthCircle);
  //rect(x, y, 10, widthCircle);
  x = random(width);
  y = random(height);
  r = random(255);
  g = random(255);
  b = random(255);
  alpha = random(100, 250);
  widthCircle = random(50);
  frameRate(60);
}


void mousePressed(){
  background(40); 
}
