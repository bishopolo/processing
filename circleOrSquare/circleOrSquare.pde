void setup(){
  
 size(640, 380);
 background(50);
  
}


void draw(){
  background(50);
  strokeWeight(5);
  line(width /2, 0, width / 2, height ); 
  noFill();
  rectMode(CENTER);
  
  
  
  if (mouseX >= width / 2){
     fill(100, 50, 70);
    square(width / 2, height / 2, 80);
  }else {
    fill(70, 50, 100);
    circle(width / 2, height / 2, 80); 
    
  }
  
  
  
}
