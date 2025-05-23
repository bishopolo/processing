int sizeBall = 50;
int ballWidth;
int ballHeight;

void setup(){
 
  size(400, 400);
  background(50);
  smooth();
  ballWidth = width - sizeBall  / 2;
  ballHeight = height - (sizeBall  / 2);
  
}

int x1 = 200, x2 = 150, x3 = 100;
int grow1 = 3, grow2 = 4, grow3 = 5;


void draw(){
  fill(200, 0, 0);
  circle(x1, x2, sizeBall);
  fill(0, 200, 0);
  circle(x2, x3, sizeBall);
  fill(0, 0, 200);
  circle(x3, x1, sizeBall);
  
  
  println(sizeBall / 2);
  
  if ( x1 >= ballWidth || x1 <= sizeBall  / 2
  ){
     grow1 *= -1;
    
  }
  
   if ( x2 >= ballWidth || x2 <= sizeBall  / 2
  ){
     grow2 *= -1;
    
  }
  
  if ( x3 >= ballWidth || x3 <= sizeBall  / 2
){
     grow3 *= -1;
    
  }
  
  x1 += grow1;
  x2 += grow2;
  x3 += grow3;
  
  println(x1);
  frameRate(30);
  
}
