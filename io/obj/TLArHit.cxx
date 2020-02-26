#include "TLArHit.hxx"
ClassImp(TLArHit)

TLArHit::TLArHit(): TNamed("TLArHit","TLArHit")
{
  clear();
}

TLArHit::~TLArHit(){}

void TLArHit::clear()
{
  edep=0;
  PE=0;
  posEnd.Clear();
  posStart.Clear();
}


void TLArHit::print(UInt_t ihit)
{
  printf("TLArHit %i edep %f PE %f end {%f,%f,%f) \n",ihit,edep,PE,posEnd.X(),posEnd.Y(),posEnd.Z());
}

