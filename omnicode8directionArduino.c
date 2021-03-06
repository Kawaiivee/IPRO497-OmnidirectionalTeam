#include <stdio.h>
#include <math.h>

double radians(double x){
  return x*M_PI/180.0;
}

struct Tuple {
    int a, b, c;
};
struct Tuple calc(int Fx, int Fy){
  struct Tuple result;
  int maxSpeed = 100;
  float tang = fabs((float)Fy/(float)Fx);
  if (tang >= tan(radians(67.5)) && Fy >= 0){
    result.a = maxSpeed;
    result.b = maxSpeed;
    result.c = 0;
    return result;
  }
  else if (tang < tan(radians(67.5)) && tang >= tan(radians(22.5)) && Fy >= 0 && Fx >= 0){
    result.a = maxSpeed/sqrt(2);
    result.b = maxSpeed/sqrt(2);
    result.c = 0;
    return result;
  }
  else if (tang < tan(radians(22.5)) && Fx >= 0){
    result.a = 0;
    result.b = 2*maxSpeed/sqrt(3);
    result.c = maxSpeed/sqrt(3);
    return result;
  }
  else if (tang < tan(radians(67.5)) && tang >= tan(radians(22.5)) && Fy < 0 && Fx >= 0){
    result.a = 2*maxSpeed/sqrt(6);
    result.b = 0;
    result.c = (maxSpeed/sqrt(2)+maxSpeed/sqrt(6));
    return result;
  }
  else if (tang >= tan(radians(67.5)) && Fy < 0){
    result.a = 0;
    result.b = 0;
    result.c = maxSpeed;
    return result;
  }
  else if (tang < tan(radians(67.5)) && tang >= tan(radians(22.5)) && Fy < 0 && Fx < 0){
    result.a = 2*maxSpeed/sqrt(6);
    result.b = 0;
    result.c = (maxSpeed/sqrt(2)+maxSpeed/sqrt(6));
    return result;
  }
  else if (tang < tan(radians(22.5)) && Fx < 0){
    result.a = 2*maxSpeed/sqrt(3);
    result.b = 0;
    result.c = maxSpeed/sqrt(3);
    return result;
  }
  else if (tang < tan(radians(67.5)) && tang >= tan(radians(22.5)) && Fy >= 0 && Fx < 0){
    result.a = maxSpeed/sqrt(2);
    result.b = maxSpeed/sqrt(2);
    result.c = 0;
    return result;
  }
}
int main()
{
  struct Tuple temp = calc(-255,-5);
  printf("%d,%d,%d\n", temp.a,temp.b,temp.c);
  return 0;
}
