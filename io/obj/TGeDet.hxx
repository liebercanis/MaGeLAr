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
    TVector3 pMin; // min bounding
    TVector3 pMax; // max bounding
    std::map<Double_t,TGeHit>  hitList;
    void addHit(Double_t t, TGeHit h);
    void setPmin(Double_t dx, Double_t dy, Double_t dz) {
      pMin.SetXYZ(dx,dy,dz);
    }
    void setPmax(Double_t dx, Double_t dy, Double_t dz) {
      pMax.SetXYZ(dx,dy,dz);
    }
    
    //sensVolID = 1000000 + array*10000 + columnNo*100 + unit=crystalNo encoded in LGND_200_14String.cc
    void decode(int &a, int &c, int &u) {
      Int_t code = id;
      code -= 1000000;
      a = code/10000;
      c = (code -a*10000)/100;
      u = (code -a*10000 -c*100);
    }

    //
  ClassDef(TGeDet,1)
};
#endif
