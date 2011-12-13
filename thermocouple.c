#include "thermocouple.h"
float k_type_coeff[3][10] = 
{
  // range 0
  // T (-200 C, 0 C)
  // U (-5.891, 0) mV
  {0.0, 2.5173462e1, -1.1662878, -1.0833638, -8.9773540e-1, -3.7342377e-1,
   -8.6632643e-2, -1.0450598e-2, -5.1920577e-4, 0}, 

  // range 1
  // T (0 C, 500 C)
  // U (0, 20.644) mV   
  {0.0, 2.508355e1, 7.860106e-2, -2.503131e-1, 8.315270e-2, -1.228034e-2,
   9.804036e-4, -4.413030e-5, 1.057734e-6, -1.052755e-8},
   
  // range 2
  // T (500 C, 1372 C)
  // U (20.644, 54.886) mV
  { -1.318058e2, 4.830222e1, -1.646031, 5.464731e-2, -9.650715e-4, 8.802193e-6,
    -3.110810e-8, 0.0, 0.0, 0.0}
};

float mvToTemp(float mv)
{
  float x, temp;
  char range;
  
  if(mv < -5.891)                       // temp < -200
    return -200.0;
  if((mv >= -5.891) && (mv < 0))        // temp [-200; 0]
    range = 0;                            
  if((mv >= 0.0) && (mv < 20.644))      // temp [0; 500] 
    range = 1;
  if(mv >= 20.644)                      // temp [500; 1372]
    range = 2;
  if(mv >= 54.886)                      //if temp > 1372 
    return 1372.0;
  
  x = 1.0;
  temp = 0.0;
  for(char i = 0; i <= 9; i++)
  {
    temp += k_type_coeff[range][i] * x;
    x *= mv;
  };
  
  return temp;
}
