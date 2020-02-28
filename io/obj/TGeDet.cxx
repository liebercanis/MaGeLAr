#include "TGeDet.hxx"
ClassImp(TGeDet)

TGeDet::TGeDet(Int_t theId): TNamed("TGeDet","TGeDet")
{
  clear();
  id=theId;
}


TGeDet::~TGeDet(){}

void TGeDet::clear()
{
  hitList.clear();
}

void TGeDet::addHit(Double_t t, TGeHit h) {
  // if the key already exists, add energy to the existing hit
  std::map<Double_t,TGeHit>::iterator iter = hitList.find(t);
  if(iter != hitList.end()) {
    *(&iter->second.eDep) += h.eDep;
    return;
  }
  hitList.insert(std::pair<Double_t,TGeHit>(t,h));
}


void TGeDet::print()
{
  printf("TGeDet %i #hits = %u \n",id,(unsigned)hitList.size());
}

