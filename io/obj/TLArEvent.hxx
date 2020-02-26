/**
** MG, Feb. 2020 
**/
#ifndef TLAREVENT_DEFINED
#define TLAREVENT_DEFINED
#include "TLArHit.hxx"
#include <iostream>
#include <string>
#include <TNamed.h>
#include <TVector3.h>
#include <vector>

using namespace std;

// class to store info for the event

class TLArEvent: public TNamed {
	public:
    TLArEvent();
    //		~TLArEvent();
    void clear();
    void print();
    Int_t triggerType;
    Int_t event;
    Int_t pid;  
    Double_t eLAr;
    TVector3 primaryVertex;
    std::vector<TLArHit>  hits;
    // data elements
    ClassDef(TLArEvent,1);
};
#endif

