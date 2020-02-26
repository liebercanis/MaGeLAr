/**
** MG, Feb 2020 
**/
#ifndef TGEHIT_DEFINED
#define TGEHIT_DEFINED
#include <iostream>
#include <string>
#include <TNamed.h>
#include <TVector3.h>
#include <vector>

// class to store info for the Ge detector
class TGeHit: public TNamed {
  public:
    TGeHit();
    ~TGeHit();
    void clear();
    void print(UInt_t ihit=0);
    // data elements
    Double_t time;
    Double_t eDep;
    TVector3 local;
    //
  ClassDef(TGeHit,1)
};
#endif

