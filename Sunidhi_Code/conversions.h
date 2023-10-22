#include <cmath>
#ifndef conversions_h
#define conversions_h

float eta_to_theta (float eta)
  {
    return 2 * atan (exp (-1 * eta)) ;
  }
  
float theta_to_eta (float theta)
  {
    return -1 * log (tan (0.5 * theta)) ;
  }  
  
float polar_to_cart_r (float x, float y, float z)
{
  return sqrt (x*x + y*y + z*z) ;
}

float polar_to_cart_theta (float x, float y, float z)
{
  return acos (z/polar_to_cart_r (x,y,z)) ;
}

float polar_to_cart_phi (float x, float y, float z)
{
  return atan2 (y, x) ;
}

float cart_to_polar_x (float r, float theta, float phi)
{
  return r * sin (theta) * cos (phi) ;
}

float cart_to_polar_y (float r, float theta, float phi)
{
  return r * sin (theta) * sin (phi) ;
}

float cart_to_polar_z (float r, float theta, float phi)
{
  return r * cos (theta) ;
}

float hep_to_polar_x (float t, float eta, float phi)
{
  return t * cos (phi) ;
}

float hep_to_polar_y (float t, float eta, float phi)
{
  return t * sin (phi) ;
}

float hep_to_polar_z (float t, float eta, float phi)
{
  float theta = eta_to_theta (eta) ;
  if (theta == 0) return 0. ;
  else return t / tan (theta) ;
}

float deltaPhi (float phi1, float phi2)
{
  float result = phi1 - phi2;
  while (result > 3.14159265) result -= 2 * 3.14159265;
  while (result <= -3.14159265) result += 2 * 3.14159265;
  return result;
}

float deltaR2 (float eta1, float phi1, float eta2, float phi2)
{
  return deltaPhi (phi1, phi2) * deltaPhi (phi1, phi2) + (eta1 - eta2) * (eta1 - eta2) ;
}

float deltaR (float eta1, float phi1, float eta2, float phi2)
{
  return sqrt (deltaR2 (eta1, phi1, eta2, phi2)) ;
}

#endif