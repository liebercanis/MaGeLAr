/**
** MG, Feb 2020 
**/
#ifndef TGEDET_DEFINED
#define TGEDET_DEFINED
#include <iostream>
#include <string>
#include <TNamed.h>
#include <TVector3.h>
#include "TGeHit.hxx"
#include <map>

// class to store info for the Ge detector
class TGeDet: public TNamed {
  public:
    TGeDet(Int_t theId=0);
    ~TGeDet();
    void clear();
    void print();
    // data elements
    Int_t id;
    std::map<Double_t,TGeHit>  hitList;
    void addHit(Double_t t, TGeHit h);
    //
  ClassDef(TGeDet,1)
};
#endif
