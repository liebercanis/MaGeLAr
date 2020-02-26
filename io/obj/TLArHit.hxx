/**
** MG, Feb 2020 
**/
#ifndef TLARHIT_DEFINED
#define TLARHIT_DEFINED
#include <iostream>
#include <string>
#include <TNamed.h>
#include <TVector3.h>
#include <vector>

// class to store info for the Ge detector
class TLArHit: public TNamed {
  public:
    TLArHit();
    ~TLArHit();
    void clear();
    void print(UInt_t ihit=0);
    // data elements
    Double_t edep;
    Double_t PE;
    TVector3 posEnd;
    TVector3 posStart;
    //
  ClassDef(TLArHit,1)
};
#endif

