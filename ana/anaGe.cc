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
  Long64_t maxLoop = 0;
  if(argc>1 ) {
    maxLoop = Long64_t(atoi(argv[1]));
    printf(" maxLoop = %llu \n",maxLoop);
  }

  TString inFileName(argv[1]);
  cout << inFileName << endl;

  


  //TRandom * rand = new TRandom();
  gROOT->ProcessLine(".x /home/admin/MGDO/Root/LoadMGDOClasses.C");
  printf(" added MGDO \n");

//  TString sysDir = "/data2/mgold/MaGe_data/";
//  TFile* inputfile = new TFile(sysDir+inFileName,"READONLY");


  //std::vector(TH1D*) hWave;
  
  TFile* outputFile = new TFile( Form("anaGe-%s","TlSource.root") ,"RECREATE");
  TH1D *hEnergy[NDET];
  TH1D *hEventEnergy = new TH1D("EventEnergy","Event Energy",2000,0,6);
  TH1D *hEventHeaderEnergy = new TH1D("EventHeaderEnergy","Event Energy",2000,0,6);
  TH1D *hEventEnergyCut = new TH1D("EventEnergyCut","Event Energy cut ",2000,0,6);
  TH2I *hOcc = new TH2I("Occ","occupancy",20,0,20,10,0,10);
  TH1D *hEnergyLAr = new TH1D("EnergyLAr","Energy in LAr",2000,0,6);
  TNtuple *ntEvent = new TNtuple("ntEvent"," event variables ","ev:ege:elar:npe:dist");
  TNtuple *ntGe = new TNtuple("ntGe"," ge hit variables ","ev:idet:ihit:time:edep:x:y:rho:r:tdrift:z");
  hOcc->SetXTitle("string");
  hOcc->SetYTitle("unit");
  for(unsigned ih=0; ih<NDET; ++ih) {
    hEnergy[ih]= new TH1D(Form("Energy-det%u",ih),Form("Event Energy det %u",ih),2000,0,6);
  }
  TChain *fChain=new TChain("LTree");
  fChain->Add("data/TlSource31-18-12-2019.root");
  fChain->Add("data/TlSource32-18-12-2019.root");
  fChain->Add("data/TlSource33-18-12-2019.root");
  printf(" LTree %llu \n", fChain->GetEntries());
  
  //
  TChain *fTree =new TChain("fTree");
  fTree->Add("data/TlSource31-18-12-2019.root");
  fTree->Add("data/TlSource32-18-12-2019.root");
  fTree->Add("data/TlSource33-18-12-2019.root");
  
  //MGDO classes
  //MGTMCEventSteps *eventSteps = NULL;
  MGTMCEventHeader *eventHeader = new MGTMCEventHeader();
  //MGTMCStepData *step = NULL;
  fTree->SetBranchAddress("eventHeader",&eventHeader);
  // Legend Tree
  TLArEvent *larEvent;
  TGeEvent *geEvent;
  fChain->SetBranchAddress("LArEvent",&larEvent);
  fChain->SetBranchAddress("GeEvent",&geEvent);
  if(fChain->GetEntries()!= fChain->GetEntries()) {
    printf(" %llu is not = %llu \n ",fChain->GetEntries(),fChain->GetEntries());
    return 1;
  }
  printf(" fTree %llu ATree %llu ", fTree->GetEntries(),fChain->GetEntries());
  //fChain->Print();
  
  Long64_t nentries = fChain->GetEntries();
  if(maxLoop == 0) maxLoop = nentries;
  printf(" maxLoop = %llu \n",maxLoop);
  Int_t ireport = maxLoop/100;
  Int_t jreport=0;
  for(Long64_t entry=0 ; entry<maxLoop; ++entry) {
    fChain->GetEntry(entry);  
    fTree->GetEntry(entry); 
    hEventHeaderEnergy->Fill(eventHeader->GetTotalEnergy());
    hEnergyLAr->Fill(larEvent->eLAr);
    long unsigned geHits0 =0;
    int geId=0;
    if(geEvent->geDet.size()>0) {
      geHits0  = geEvent->geDet[0].hitList.size();
      geId     = geEvent->geDet[0].id;
    }
    if(entry%ireport==0) printf(" ... %i event %llu geDets %lu id= %i geHits %lu larHits %lu \n",
        ++jreport,entry, geEvent->geDet.size(),geId,geHits0,larEvent->hits.size());

    // loop over ge dets
    for(unsigned idet =0; idet < geEvent->geDet.size(); ++idet) {
      TGeDet *gdet = &geEvent->geDet[idet];
      //printf(" \t idet %u hits %lu \n",idet,gdet->hitList.size());
      unsigned icount=0;
      double eGe=0;
      for(std::map<double, TGeHit>::iterator gIter= gdet->hitList.begin(); gIter!= gdet->hitList.end(); ++gIter ) {
        TGeHit *ghit = &gIter->second;
        Double_t edep =  ghit->eDep;  
        Double_t time = ghit->time;
        TVector3 local = ghit->local;
        //printf(" \t\t idet %u ihit %u  edep %E time %E \n",idet,icount++,edep,time);
        eGe += edep;
        Double_t tdrift = local.Mag()/.05; // ns
        ntGe->Fill(float(entry),float(gdet->id),float(icount),time,edep,local.X(),local.Y(),local.Perp(),local.Mag(),tdrift,local.Z());
      }
    }

    double geEventEnergy = geEvent->getEventEnergy();
    //printf(" %f =? %f  \n",eventHeader->GetTotalEnergy(),geEventEnergy);
    
    hEventEnergy->Fill(geEventEnergy);
    if(larEvent->hits.size()==0) hEventEnergyCut->Fill(geEventEnergy);
    if(larEvent->hits.size()>0) {
      TVector3 diff = larEvent->hits[0].posEnd - larEvent->hits[0].posStart;
      ntEvent->Fill(float(entry),geEventEnergy,larEvent->hits[0].edep,larEvent->hits[0].PE,diff.Mag());
    }
  }


  // remove empty histograms;
  for(unsigned ih=0; ih<NDET; ++ih) if(hEnergy[ih]->GetEntries()==0) outputFile->Delete(hEnergy[ih]->GetName());
  outputFile->ls();
  outputFile->Write();
  outputFile->Close();

  //gApplication->Terminate();
  return 0;

}
