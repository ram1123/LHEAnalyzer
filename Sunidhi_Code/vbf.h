/*
identification of the jets for the analysis for the 4jets and 3jets cases
*/


#ifndef vbf_h
#define vbf_h

#include <vector>
// CINT does not understand some files included by LorentzVector
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"

using namespace ROOT::Math;
using namespace std ;

typedef LorentzVector<ROOT::Math::PxPyPzE4D<double> > lorentzVector ;

//PG lorentzVector pointers sorting algos
//PG ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

struct TLVP_etaSort: public std::binary_function<int, int, bool>
{
  bool operator() (const lorentzVector * x, const lorentzVector * y)
    {
      return x->Eta () < y->Eta () ;
    }
} ;

struct TLVP_absEtaSort: public std::binary_function<int, int, bool>
{
  bool operator() (const lorentzVector * x, const lorentzVector * y)
    {
      return fabs (x->Eta ()) < fabs (y->Eta ()) ;
    }
} ;

struct TLVP_ptSort: public std::binary_function<int, int, bool>
{
  bool operator() (const lorentzVector * x, const lorentzVector * y)
    {
      return x->Pt () < y->Pt () ;
    }
} ;


//PG jet sortings (JS)
//PG ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----

// - two jets with highest DEta are the VBF ones, then two jets with highest pT are the W ones
vector<const lorentzVector *>
JS_Deta_pT (const lorentzVector * input, int njets)
{
  vector<const lorentzVector *> input_p ;
  vector<const lorentzVector *> output_p ;
  for (int iJet = 0 ; iJet < njets ; ++iJet) input_p.push_back (&(input[iJet])) ;
  sort (input_p.begin (), input_p.end (), TLVP_etaSort ()) ;
  output_p.push_back (input_p.front ()) ;
  output_p.push_back (input_p.back ()) ;
  input_p.erase (input_p.begin (), input_p.begin () + 1) ;
  input_p.erase (input_p.end () - 1, input_p.end ()) ;
  sort (input_p.begin (), input_p.end (), TLVP_ptSort ()) ;
  output_p.push_back (input_p.at (0)) ;
  output_p.push_back (input_p.at (1)) ;
  return output_p ;
}


// - FNAL criterion, with embedded cuts:
//     |etaj|<4.5
//     etaj1 x etaj2 < 0
//     |Deta|>3.5
//     mj1j2 > 300
vector<const lorentzVector *>
JS_FNAL (const lorentzVector * input, int njets)
{
  vector<const lorentzVector *> input_p ;
  vector<const lorentzVector *> output_p ;
  for (int iJet = 0 ; iJet < njets ; ++iJet) input_p.push_back (&(input[iJet])) ;
  float maxDeta = 0. ;
  int iJ1 = 0 ;
  int iJ2 = 0 ;
  for (int iJet = 0 ; iJet < njets - 1 ; ++iJet)
    {
      if (fabs (input_p.at (iJet)->Eta ()) > 4.5) continue ;
      for (int jJet = iJet + 1 ; jJet < njets ; ++jJet) 
        {
          if (fabs (input_p.at (jJet)->Eta ()) > 4.5) continue ;
          if (input_p.at (iJet)->Eta () * input_p.at (jJet)->Eta () > 0) continue ;
          float deta = fabs (input_p.at (iJet)->Eta () - input_p.at (jJet)->Eta ()) ;
          if (deta < 3.5) continue ;
          lorentzVector sum = *input_p.at (iJet) + *input_p.at (jJet) ;
          float mjj = sqrt (sum.M2 ()) ;
          if (mjj < 300) continue ;
          if (deta > maxDeta)
            {
              maxDeta = deta ;
              iJ1 = iJet ;
              iJ2 = jJet ;
            }
        }
    }
  if (maxDeta < 0.1) return output_p ;
  output_p.push_back (input_p.at (iJ1)) ; 
  output_p.push_back (input_p.at (iJ2)) ; 
  if (iJ1 < iJ2) swap (iJ1, iJ2) ;
  input_p.erase (input_p.begin () + iJ1) ;
  input_p.erase (input_p.begin () + iJ2) ;
  sort (input_p.begin (), input_p.end (), TLVP_ptSort ()) ;
  output_p.push_back (input_p.at (0)) ;
  output_p.push_back (input_p.at (1)) ;
  return output_p ;
}


// - two jets with highest Mjj are the VBF ones, then two jets with highest pT are the W ones
vector<const lorentzVector *>
JS_Mjj_pT (const lorentzVector * input, int njets)
{
  vector<const lorentzVector *> input_p ;
  vector<const lorentzVector *> output_p ;
  for (int iJet = 0 ; iJet < njets ; ++iJet) input_p.push_back (&(input[iJet])) ;
  float maxMjj = 0. ;
  int iJ1 = 0 ;
  int iJ2 = 0 ;
  for (int iJet = 0 ; iJet < njets - 1 ; ++iJet)
    {
      for (int jJet = iJet + 1 ; jJet < njets ; ++jJet) 
        {
          lorentzVector sum = *input_p.at (iJet) + *input_p.at (jJet) ;
          float mjj = sqrt (sum.M2 ()) ;
          if (mjj > maxMjj)
            {
              maxMjj = mjj ;
              iJ1 = iJet ;
              iJ2 = jJet ;
            }
        }
    }
  output_p.push_back (input_p.at (iJ1)) ; 
  output_p.push_back (input_p.at (iJ2)) ; 
  if (iJ1 < iJ2) swap (iJ1, iJ2) ;
  input_p.erase (input_p.begin () + iJ1) ;
  input_p.erase (input_p.begin () + iJ2) ;
  sort (input_p.begin (), input_p.end (), TLVP_ptSort ()) ;
  output_p.push_back (input_p.at (0)) ;
  output_p.push_back (input_p.at (1)) ;
  return output_p ;
}




// - two jets with mjj close to W are the W ones, than two jets with highest pT are the VBF ones
// - two jets with mjj close to W are the W ones, than two jets with highest mjj are the VBF ones
// - two jets with mjj close to W are the W ones, than two jets with highest deta are the VBF ones
// - the previous ones, among the four jets with highest pT

#endif