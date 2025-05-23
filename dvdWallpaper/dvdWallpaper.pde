int x ;
int y ;
void setup() {
  size(600, 500);
  //fullScreen();
  fill(0);
  smooth();
  x = height / 2;
  y = width / 2;
}



int growX = 2;
int growY = 2;
String msg = "DVD";
String caption = "video";
int increment = 0;
float r = 200, g = 200, b = 200;

void draw() {
  background(40);
  increment++;
  
  
  if (increment >= 300){
    r = random(100,255);
    g = random(100,255);
    b = random(100,255);
    increment = 0;
  }
  
  fill(r, g, b);
  textSize(50);
  textAlign(CENTER);
  text(msg, x + growX, y + growY);
  textSize(25);
  noStroke();
  ellipse(x + growX, y + growY + 25, 120, 32);
  fill(0);
  text(caption, x + growX, y + growY + 32);
  
  if (x <= 50  || x >= width - 50){
   growX *= -1;
  }
  
  
  if (y <= 40  || y >= height - 40){
   growY *= -1;
  }
  
  x += growX;
  y += growY;
  frameRate(40);
  
}
