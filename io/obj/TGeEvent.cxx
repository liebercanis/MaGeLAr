#include "TGeEvent.hxx"
ClassImp(TGeEvent)

TGeEvent::TGeEvent(): TNamed("TGeEvent","TGeEvent")
{
  clear();
}

//TGeEvent::~TGeEvent(){}

void TGeEvent::clear()
{
  triggerType = -1;
  geDet.clear();
}

void TGeEvent::print(Int_t event) 
{
  printf(" \n TGeEvent  %i trig %i dets = %u\n",event,triggerType,unsigned(geDet.size()));
}

