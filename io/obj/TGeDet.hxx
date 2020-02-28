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

    //sensVolID = 1000000 + columnNo*100 + crystalNo encoded in LGND_200_14String.cc
    void decode(int &column, int &crystal) {
      Int_t code =id;
      if(code >= 1000000) code -= 1000000;
      column = code/100;
      crystal = (code -column*100);
    }


    //
  ClassDef(TGeDet,1)
};
#endif
