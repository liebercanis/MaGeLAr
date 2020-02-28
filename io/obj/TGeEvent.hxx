/**
** MG, Feb. 2020 
**/
#ifndef TGEEVENT_DEFINED
#define TGEEVENT_DEFINED
#include "TGeDet.hxx"
#include <iostream>
#include <string>
#include <TNamed.h>
#include <vector>

using namespace std;

// class to store info for the event

class TGeEvent: public TNamed {
	public:
    TGeEvent();
    //		~TGeEvent();
    void clear();
    void print(Int_t event);
    Int_t triggerType;
    std::vector<TGeDet> geDet;

    Double_t getEventEnergy() {
      Double_t eGe=0;
      for(unsigned idet =0; idet < geDet.size(); ++idet) {
        for(std::map<double, TGeHit>::iterator gIter= geDet[idet].hitList.begin(); gIter!= geDet[idet].hitList.end(); ++gIter ) {
          TGeHit *ghit = &gIter->second;
          eGe +=  ghit->eDep;  
        }
      }
      return eGe;
    }

    // data elements
    ClassDef(TGeEvent,1);
};
#endif

