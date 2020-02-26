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
    std::vector<TGeDet>  geDet;
    // data elements
    ClassDef(TGeEvent,1);
};
#endif

