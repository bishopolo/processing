void setup(){
  
 size(700, 500);
 background(25);
  
}


void draw(){
  background(25);
  rectMode(CENTER);
  fill(200, 50, 70, 150);
  square(mouseY, height / 2, 100); 
  //rectMode(TOP);
  fill(170, 100, 30, 150);
  square(400, mouseX / 2, 100); 
  
  
}
