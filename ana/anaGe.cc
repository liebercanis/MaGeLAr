#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TNtuple.h"
#include "TChain.h"
#include "TString.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TH3D.h"
#include "TRandom.h"
#include "TProof.h"
#include "TParameter.h"
#include "TSystemDirectory.h"
#include "MGTMCEventSteps.hh"
#include "MGTMCEventHeader.hh"
#include "TLArEvent.hxx"
#include "TGeEvent.hxx"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

enum {NDET=2000};

using namespace std;


//sensVolID = 1000000 + columnNo*100 + crystalNo encoded in LGND_200_14String.cc
void decode(int code, int& a, int &s, int & u, int& det) {
  code -= 1000000;
  a = code/10000;
  s = (code -a*10000)/100;
  u = (code -a*10000 -s*100);
  det = s*100+u;
}


int main(int argc, char *argv[])
{
  if(argc>1 ) {
    //printf(" enter root file in directory /data2/mgold/MaGe_data/ \n");
    printf(" takes no args \n");
    return 1;
  }

  TString inFileName(argv[1]);
  cout << inFileName << endl;

  //TRandom * rand = new TRandom();
  gROOT->ProcessLine(".x /home/admin/MGDO/Root/LoadMGDOClasses.C");
  printf(" added MGDO \n");

//  TString sysDir = "/data2/mgold/MaGe_data/";
//  TFile* inputfile = new TFile(sysDir+inFileName,"READONLY");

  
  TFile* outputFile = new TFile( Form("anaGe-%s","TlSource.root") ,"RECREATE");
  TH1D *hEnergy[NDET];
  TH1D *hEventEnergy = new TH1D("EventEnergy","Event Energy",2000,0,6);
  TH1D *hEventEnergyCut = new TH1D("EventEnergyCut","Event Energy cut ",2000,0,6);
  TH2I *hOcc = new TH2I("Occ","occupancy",20,0,20,10,0,10);
  TH1D *hEnergyLAr = new TH1D("EnergyLAr","Energy in LAr",2000,0,6);
  TNtuple *ntEvent = new TNtuple("ntEvent"," event variables ","ev:ege:elar:npe");
  TNtuple *ntGe = new TNtuple("ntGe"," ge hit variables ","ev:ihit:time:edep:x:y:z");
  hOcc->SetXTitle("string");
  hOcc->SetYTitle("unit");
  for(unsigned ih=0; ih<NDET; ++ih) {
    hEnergy[ih]= new TH1D(Form("Energy-det%u",ih),Form("Event Energy det %u",ih),2000,0,6);
  }
  TChain *fChain=new TChain("LTree");
  
  fChain->Add("data/TlSource-test31.root");
  printf(" LTree %llu \n", fChain->GetEntries());
  //MGDO classes
  MGTMCEventSteps *eventSteps = NULL;
  MGTMCEventHeader *eventHeader = NULL;
  //MGTMCStepData *step = NULL;
  // Legend Tree
  TLArEvent *larEvent;
  TGeEvent *geEvent;
  fChain->SetBranchAddress("LArEvent",&larEvent);
  fChain->SetBranchAddress("GeEvent",&geEvent);
  if(fChain->GetEntries()!= fChain->GetEntries()) {
    printf(" %llu is not = %llu \n ",fChain->GetEntries(),fChain->GetEntries());
    return 1;
  }
  printf(" fTree %llu ATree %llu ", fChain->GetEntries(),fChain->GetEntries());
  fChain->Print();
  
  std::map<double, TGeHit>::iterator gIter;
  Long64_t nentries = fChain->GetEntries();
  for(Long64_t entry=0 ; entry<nentries; ++entry) {
    fChain->GetEntry(entry);  
    hEnergyLAr->Fill(larEvent->eLAr);
    if(entry%1==0) printf(" ... event %llu geDets %lu larHits %lu \n",entry, geEvent->geDet.size(),larEvent->hits.size());

    // loop over ge dets
    double eGe=0;
    for(unsigned idet =0; idet < geEvent->geDet.size(); ++idet) {
      TGeDet *gdet = &geEvent->geDet[idet];
      printf(" \t idet %u hits %lu \n",idet,gdet->hitList.size());
      gIter=gdet->hitList.begin();
      unsigned icount=0;
      for(std::map<double, TGeHit>::iterator gIter= gdet->hitList.begin(); gIter!= gdet->hitList.end(); ++gIter ) {
        TGeHit *ghit = &gIter->second;
        Double_t edep =  ghit->eDep;  
        Double_t time = ghit->time;
        TVector3 local = ghit->local;
        printf(" \t\t idet %u ihit %u  edep %E time %E \n",idet,icount++,edep,time);
        eGe += edep;
        hEventEnergy->Fill(eGe);
        ntGe->Fill(float(entry),float(icount),time,edep,local.X(),local.Y(),local.Z());
      }
    }
    if(larEvent->hits.size()>0) ntEvent->Fill(float(entry),eGe,larEvent->hits[0].edep,larEvent->hits[0].PE);
  }


  // remove empty histograms;
  for(unsigned ih=0; ih<NDET; ++ih) if(hEnergy[ih]->GetEntries()==0) outputFile->Delete(hEnergy[ih]->GetName());
  outputFile->ls();
  outputFile->Write();
  outputFile->Close();

  //gApplication->Terminate();
  return 0;

}
