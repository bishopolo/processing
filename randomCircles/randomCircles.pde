void setup(){
 size(640, 360);
 background(250);
  
  
}

float x = random(width), y = random(height);
float r = random(50, 200), g = random(50, 200), b = random(50, 200);

void draw(){
  
  fill(r, g, b);
  circle(x, y, 20);
  x = random(width);
  y = random(height);
  r = random(255);
  g = random(255);
  b = random(255);
  frameRate(10);
}


void mousePressed(){
  background(250); 
}
