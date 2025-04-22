void setup(){
 size(600, 400); 
}

void draw(){
  background(50);
  strokeWeight(5);
  line(200, 0, 200, height);
  line(400, 0, 400, height);
  rectMode(CENTER);
  noFill();
  fill(random(255), random(255), random(255));
  
  
  if (mouseX <= 200){
    rect(100, height / 2, 20, 50);
  }else if (mouseX <= 400){
    circle(300, height / 2, 50);
  }else{
    square(500, height / 2, 50); 
  }
  
  
}
