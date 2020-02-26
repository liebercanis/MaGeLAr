#include "TGeHit.hxx"
ClassImp(TGeHit)

TGeHit::TGeHit(): TNamed("TGeHit","TGeHit")
{
  clear();
}


TGeHit::~TGeHit(){}

void TGeHit::clear()
{
  time=0;
  eDep=0;
  local.Clear();
}

void TGeHit::print(UInt_t ihit)
{
  printf("TGeHit %u time %f energy %f position (%f,%f,%f) \n",ihit,time,eDep,local.X(),local.Y(),local.Z());
}

