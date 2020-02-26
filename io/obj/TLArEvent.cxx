#include "TLArEvent.hxx"
ClassImp(TLArEvent)

TLArEvent::TLArEvent(): TNamed("TLArEvent","TLArEvent")
{
  clear();
}

//TLArEvent::~TLArEvent(){}

void TLArEvent::clear()
{
  triggerType = -1;
  pid=0;
  event=0;
  eLAr=0;
  primaryVertex.Clear();
  hits.clear();
}

void TLArEvent::print() 
{
  printf(" \n TLArEvent  %i trig %i dets = %u\n",event,triggerType,unsigned(hits.size()));
}

