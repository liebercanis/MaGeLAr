#include "TFile.h"
#include "TTree.h"
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


// for LAr
struct lArEvent_t {
  double Energy;
  double PE;
};
lArEvent_t lArEvent;


//sensVolID = 1000000 + columnNo*100 + crystalNo encoded in LGND_200_14String.cc
void decode(int code, int& a, int &s, int & u, int& det) {
  code -= 1000000;
  a = code/10000;
  s = (code -a*10000)/100;
  u = (code -a*10000 -s*100);
  det = s*100+u;
}

using namespace std;
int main(int argc, char *argv[])
{
  if(argc<2 ) {
    printf(" enter root file in directory /data2/mgold/MaGe_data/ \n");
    return 1;
  }

  TString inFileName(argv[1]);
  cout << inFileName << endl;

  TRandom * rand = new TRandom();
  gROOT->ProcessLine(".x /home/admin/MGDO/Root/LoadMGDOClasses.C");
  printf(" added MGDO \n");

  TString sysDir = "/data2/mgold/MaGe_data/";
  TFile* inputfile = new TFile(sysDir+inFileName,"READONLY");

  
  TFile* outputFile = new TFile( Form("anaGe-%s",inFileName.Data()) ,"RECREATE");
  TH1D *hEnergy[NDET];
  TH1D *hEventEnergy = new TH1D("EventEnergy","Event Energy",2000,0,6);
  TH2I *hOcc = new TH2I("Occ","occupancy",20,0,20,10,0,10);
  hOcc->SetXTitle("string");
  hOcc->SetYTitle("unit");
  for(unsigned ih=0; ih<NDET; ++ih) {
    hEnergy[ih]= new TH1D(Form("Energy-det%u",ih),Form("Event Energy det %u",ih),2000,0,6);
  }
  TTree* tree = (TTree*)inputfile->Get("fTree");
  //MGDO classes
  MGTMCEventSteps *eventSteps = NULL;
  MGTMCEventHeader *eventHeader = NULL;
  MGTMCStepData *step = NULL;
  tree->SetBranchAddress("eventSteps", &eventSteps);
  tree->SetBranchAddress("eventHeader",&eventHeader);

  TTree* aTree=NULL;
  inputfile->GetObject("ATree",aTree);
  if(aTree==NULL) printf(" file has no ATree \n");
  else printf(" GOT ATree \n");
  if(aTree) aTree->SetBranchAddress("lArEvent",&lArEvent);

  Long64_t nentries = tree->GetEntries();
  printf(" fTree has %llu entries \n",nentries);
  for(Long64_t entry=0 ; entry<nentries; ++entry) {
    tree->GetEntry(entry);  
    std::map<int,double> emap = eventHeader->GetEnergyMap();
    if(entry%1==0) {
      printf(" ... event %llu map size %lu \n",entry,emap.size());
      //unsigned idcount=0;
      //for (std::map<int,double>::iterator idIter=emap.begin() ; idIter!=emap.end(); ++idIter)
      //  printf(" id %u first %i (%i)  second %E \n",idcount++, idIter->first, int(idIter->first)-1010000 , idIter->second);
    }

    for (std::map<int,double>::iterator idIter=emap.begin() ; idIter!=emap.end(); ++idIter) {
      if(idIter->first>1000000) {
        int iarray, istring, iunit, idet;
        decode(idIter->first,iarray,istring,iunit,idet);
        //printf(" array %i istring %i unit = %i idet = %i\n",iarray,istring,iunit,idet);
        hOcc->Fill(istring,iunit);
        if(idet>0&&idet<2000) {
          hEnergy[idet]->Fill(idIter->second);
          hEventEnergy->Fill(idIter->second);
        }
        else 
          printf(" ERROR!! illegal idet %i \n",idet);
      }
    }
  }

  if(aTree) {
    nentries = aTree->GetEntries();
    printf(" ATree has %llu entries \n",nentries);
    for(Long64_t entry=0 ; entry<nentries; ++entry) {
      aTree->GetEntry(entry);
      printf(" entry %llu energy %f pe %f \n",entry,lArEvent.Energy,lArEvent.PE);

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
