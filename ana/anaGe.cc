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
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

enum {NDET=2000};

using namespace std;

  // for LAr
  struct lArEvent_t {
    double edep;
    double PE;
    double PVx;
    double PVy;
    double PVz;
    double e0;
    double x0;
    double y0;
    double z0;
    double xf;
    double yf;
    double zf;
    int ev;
    int id;
  };
  lArEvent_t lArEvent;


/*
struct lArEvent_t {
  double Energy;
  double PE;
};
lArEvent_t lArEvent;
*/
void printlArEvent() {
    TString mess;
    mess.Form(" \t ***** lArEvent  **** %llu (%.1f,%.1f,%.1f)",lArEvent.ev,lArEvent.PVx,lArEvent.PVy,lArEvent.PVz);
    cout << mess << endl;
    mess.Form(" \t pid %i e0 %.3f first (%.1f,%.1f,%.1f) last (%.1f,%.1f,%.1f) " ,lArEvent.id,lArEvent.e0,
        lArEvent.x0,lArEvent.y0,lArEvent.z0,lArEvent.xf,lArEvent.yf,lArEvent.zf);
    cout << mess << endl;
    mess.Form(" \t edep %.3f PE %.3f",lArEvent.edep,lArEvent.PE);
    cout << mess << endl;
  }


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
  //if(argc<2 ) {
  //  printf(" enter root file in directory /data2/mgold/MaGe_data/ \n");
  //  return 1;
 // }

  TString inFileName(argv[1]);
  cout << inFileName << endl;

  TRandom * rand = new TRandom();
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
  hOcc->SetXTitle("string");
  hOcc->SetYTitle("unit");
  for(unsigned ih=0; ih<NDET; ++ih) {
    hEnergy[ih]= new TH1D(Form("Energy-det%u",ih),Form("Event Energy det %u",ih),2000,0,6);
  }
  TChain *fChain=new TChain("fTree");
  TChain *aChain=new TChain("fATree");
  
  fChain->Add("/data2/mgold/MaGe_data/TlSource-job31test.root");
  aChain->Add("/data2/mgold/MaGe_data/TlSource-job31test.root");
  

  /*
  fChain->Add("/data2/mgold/MaGe_data/TlSource-job31.root");
  aChain->Add("/data2/mgold/MaGe_data/TlSource-job31.root");
  printf(" fTree %llu ATree %llu \n", fChain->GetEntries(),aChain->GetEntries());
  fChain->Add("/data2/mgold/MaGe_data/TlSource-job32.root");
  aChain->Add("/data2/mgold/MaGe_data/TlSource-job32.root");
  printf(" fTree %llu ATree %llu \n", fChain->GetEntries(),aChain->GetEntries());
  fChain->Add("/data2/mgold/MaGe_data/TlSource-job33.root");
  aChain->Add("/data2/mgold/MaGe_data/TlSource-job33.root");
  */
  printf(" fTree %llu ATree %llu \n", fChain->GetEntries(),aChain->GetEntries());
  //MGDO classes
  MGTMCEventSteps *eventSteps = NULL;
  MGTMCEventHeader *eventHeader = NULL;
  MGTMCStepData *step = NULL;
  fChain->SetBranchAddress("eventSteps", &eventSteps);
  fChain->SetBranchAddress("eventHeader",&eventHeader);
  aChain->SetBranchAddress("lArEvent",&lArEvent);
  if(fChain->GetEntries()!= aChain->GetEntries()) {
    printf(" %llu is not = %llu \n ",fChain->GetEntries(),aChain->GetEntries());
    return 1;
  }
  printf(" fTree %llu ATree %llu ", fChain->GetEntries(),aChain->GetEntries());
  aChain->Print();
  
  Long64_t nentries = aChain->GetEntries();
  for(Long64_t entry=0 ; entry<nentries; ++entry) {
    fChain->GetEntry(entry);  
    aChain->GetEntry(entry);
    hEnergyLAr->Fill(lArEvent.edep);

    std::map<int,double> emap = eventHeader->GetEnergyMap();
    //if( lArEvent.id!=11) printf(" NOT e- entry %llu energy %f pe %f ID %i \n",entry,lArEvent.edep,lArEvent.PE,int(lArEvent.id));
    if(entry%1==0) {
      //printf(" ... event %llu map size %lu \n",entry,emap.size());
      printf(" ... event %llu zf %f \n",entry,lArEvent.zf);
      printlArEvent();
      //unsigned idcount=0;
      //for (std::map<int,double>::iterator idIter=emap.begin() ; idIter!=emap.end(); ++idIter)
      //  printf(" id %u first %i (%i)  second %E \n",idcount++, idIter->first, int(idIter->first)-1010000 , idIter->second);
    }

    double eGe=0;

    for (std::map<int,double>::iterator idIter=emap.begin() ; idIter!=emap.end(); ++idIter) {
      if(idIter->first>1000000) {
        int iarray, istring, iunit, idet;
        decode(idIter->first,iarray,istring,iunit,idet);
        //printf(" array %i istring %i unit = %i idet = %i\n",iarray,istring,iunit,idet);
        hOcc->Fill(istring,iunit);
        if(idet>0&&idet<2000) {
          eGe += idIter->second;
          hEnergy[idet]->Fill(idIter->second);
          hEventEnergy->Fill(idIter->second);
          if(lArEvent.PE<500) hEventEnergyCut->Fill(idIter->second); 
        }
        else 
          printf(" ERROR!! illegal idet %i \n",idet);
      }
    }
    ntEvent->Fill(float(entry),eGe,lArEvent.edep,lArEvent.PE);
  }


  // remove empty histograms;
  for(unsigned ih=0; ih<NDET; ++ih) if(hEnergy[ih]->GetEntries()==0) outputFile->Delete(hEnergy[ih]->GetName());
  outputFile->ls();
  outputFile->Write();
  outputFile->Close();

  //gApplication->Terminate();
  return 0;

}
