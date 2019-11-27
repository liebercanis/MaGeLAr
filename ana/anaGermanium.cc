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

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;
int main(){

  TRandom * rand = new TRandom();
  gROOT->SetBatch(kFALSE);
  //MGDO classesload MGDO classes
  gROOT->ProcessLine(".x /home/admin/MGDO/Root/LoadMGDOClasses.C");
  printf(" added MGDO \n");
  //Set cout precision
  //std::cout << std::fixed;
  //std::cout << std::setprecision(4);
 
  TString sysDir = "/data2/mgold/MaGe_data/";
  TSystemDirectory dir(sysDir,sysDir);
  TList *files = dir.GetListOfFiles(); 
  files->ls();

  TSystemFile *file; 
  TString fname; 
  TIter next(files); 

  TString dummy;
  TString detname;
  int j,n,k;
  int detector;
  int multiplicity;
  Long64_t i, nentries;
  
  n = 0;

  double SiPMQE = 0.164;
  TH3D *hMap;
  TH2D *hMapExterior;
  TH3D *hMapXe;
  TH2D *hMapXeExterior;
  TString mapDir = "/home/nmcfadde/";
  TString mapFileName("OpticalMapL200.14String.5mm");
  TString mapFileNameXe("OpticalMapL200XeD.14String.5mm");
  
  TFile* mapFile = TFile::Open(mapDir+mapFileName+TString(".root"));
  TFile* mapFileXe = TFile::Open(mapDir+mapFileNameXe+TString(".root"));
  if(mapFile == NULL) {
    printf(" aint got map file %s \n",mapFile->GetName());
    return 1;
  }
  if(mapFileXe == NULL) {
    printf(" aint got map file %s \n",mapFile->GetName());
    return 1;
  } 
    mapFile->GetObject("ProbMapInterior",hMap);
    mapFile->GetObject("ProbMapExterior",hMapExterior);
    mapFileXe->GetObject("ProbMapInterior",hMapXe);
    mapFileXe->GetObject("ProbMapExterior",hMapXeExterior);

  TFile *inputfile =0;
  TTree *tree = 0;

  //MGDO classes
  MGTMCEventSteps *eventSteps = 0;
  MGTMCStepData *step = 0;

  double energytotal[2000];

  //energy histograms for each detector
  TH1D *h_energy[2000];
  TH1D *h_energyLAr[2000];
  TH1D *h_energyLArXeD[2000];
  for(j = 0;j<2000;j++){
    h_energy[j] = 0;
    h_energyLAr[j] = 0;
  }

  //this counts events per detector
  TH1D *h_counts = new TH1D("h_counts","h_counts",2000,0,2000);
  TH1D *hEnergySum = new TH1D("hEnergySum","hEnergySum",4000,0,4);
  TH1D *hEnergyInLAr = new TH1D("hEnergyInLAr","hEnergyInLAr",4000,0,4);
  TH1D *hEnergySumLAr = new TH1D("hEnergySumLAr","hEnergySumLAr",4000,0,4);
  TH1D *hEnergySumXeD = new TH1D("hEnergySumXeD","hEnergySumXeD",4000,0,4);
  h_counts->SetDirectory(0);

//////////////////////////////////////////////////////////////

//open all files
  while ((file=(TSystemFile*)next())){
    fname = file->GetName();
    if (!file->IsDirectory() && fname.EndsWith("root")){
      n++;
      //inputfile = TFile::Open("/data4/legend/sim/l200sims/LGND200_14OpticalCalibration/Th228/"+fname);
      //inputfile = TFile::Open("/home/nmcfadden/MaGe/bin/Linux-g++/data/"+fname);
      inputfile = TFile::Open(sysDir+fname);
      tree = (TTree*)inputfile->Get("fTree");
      tree->SetBranchAddress("eventSteps", &eventSteps);
      nentries = tree->GetEntries();
      cout << fname << " " << n << " with  " << nentries << " entries " << endl;
      //if(n > 1) continue;
      //loop through each MaGe file
      for (Long64_t i=0;i<nentries;i++) {
        tree->GetEntry(i);
        j = eventSteps->GetNSteps();
        if(i%(int(nentries*.10)) == 0) cout<<"Processed "<<i<<" entries out of "<<nentries<<" ... "<<100.*(double(i)/nentries)<<"%"<<endl;
        cout<<"Processed "<<i<<" entries out of "<<nentries<<" ... "<<100.*(double(i)/nentries)<<"%"<<endl;
        bool geHit = false;
        double energyLAr = 0;
        double nPhotons  = 0,nPhotonsXeD = 0;
        std::vector<int> stepper;
        //each entry is one Geant4Event
        // beginning of each ith event reset the energy summing constant
        // j steps per event
        for(k = 0; k<2000 || k < j; k++){
          if(k<2000) energytotal[k] = 0;
          if(k < j) stepper.push_back(k);
        }
        multiplicity = 0;
        step =0;
        //Do some time ordered sorting,
        //code written by R. Mazzerkcye
        while(stepper.size()>0){
          step = (MGTMCStepData*)eventSteps->GetStep(stepper[0]);
          detname = step->GetPhysVolName();
          dummy = detname(33,3);
          detector = dummy.Atoi() * 100;
          dummy = detname(45,3);
          detector += dummy.Atoi();
          Double_t edep = step->GetEdep();
          Double_t step_t = step->GetT();
          
          if(detname == "Detector"){
            //calculate Nphotons prior to Ge hits
            energyLAr += edep;//step->GetEdep();
            Int_t bin = hMap->FindBin(step->GetX(),step->GetY(),step->GetZ());
            Double_t mapProb = hMap->GetBinContent(bin);
            Double_t scintYeild = 42370;
            Double_t eThresh = mapProb*scintYeild;
            if(mapProb == 0){
              stepper.erase(stepper.begin());
              continue;
            }
            //average photon yeild accord to map
            nPhotons += edep*eThresh*SiPMQE;
            //Xenon Doped Map
            mapProb = hMapXe->GetBinContent(bin);
            eThresh = mapProb*scintYeild;
            nPhotonsXeD += edep*eThresh*SiPMQE;
          }

          Int_t zero_det = detector;
          Double_t zero_t = step_t;
          Double_t zero_e = edep;
          TString zero_detname = detname;
          stepper.erase(stepper.begin());
          int k = 0;
          while(k<stepper.size() && zero_detname.Contains("ActiveDet") ){
            step = (MGTMCStepData*)eventSteps->GetStep(stepper[k]);
            detname = step->GetPhysVolName();
            dummy = detname(33,3);
            detector = dummy.Atoi() * 100;
            dummy = detname(45,3);
            detector += dummy.Atoi();
            edep = step->GetEdep();
            step_t = step->GetT();
            //LAr aka "Detector" has a detector id (MaGe) of 0, so in order not confuse the LAr with
            //Ge detector 0, we label the liquid argon with detector number -1
            if(detname == "Detector") detector = -1;
            if((detector == zero_det) && (step_t-zero_t < 160000)){
              zero_e += edep;
              stepper.erase(stepper.begin()+k);
              geHit = true;
            }
            else if(detname == "Detector" && (step_t-zero_t < 160000)){
              //calculate Nphotons prior to Ge hits
              energyLAr += edep;//step->GetEdep();
              Int_t bin = hMap->FindBin(step->GetX(),step->GetY(),step->GetZ());
              Double_t mapProb = hMap->GetBinContent(bin);
              Double_t scintYeild = 42370;
              Double_t eThresh = mapProb*scintYeild;
              if(mapProb == 0){
                stepper.erase(stepper.begin()+k);
                continue;
              }
              //average photon yeild accord to map
              nPhotons += edep*eThresh*SiPMQE;
              //Xenon Doped Map
              mapProb = hMapXe->GetBinContent(bin);
              eThresh = mapProb*scintYeild;
              nPhotonsXeD += edep*eThresh*SiPMQE;
              stepper.erase(stepper.begin()+k);
            }
            else{
              k++;
            }
          }
          //FWHM=2.355*sqrt(0.143469^2+0.0175381^2*E+0.000268799^2*E^2)
          double pi = 3.14159265359;
          //in KeV
          double FWHM=2.355*sqrt(pow(0.143469,2)+pow(0.0175381,2)*zero_e+pow(0.000268799,2)*pow(zero_e,2));
          zero_e = rand->Gaus(zero_e,FWHM/(1000*2.355));
          if(geHit) energytotal[detector] += zero_e;
          hEnergyInLAr->Fill(energyLAr);
          energyLAr = 0;
        }
        //Put energy deposition into each Ge histogram
        //skip if no hits were found (i.e. only LAr edep)
        for(k = 0; k<2000 && geHit; k++){
          //energy theshold == 0keV
          if (energytotal[k]>0){
            h_counts->Fill(k);
            multiplicity++;
            double LArWeight = exp(-nPhotons);
            double XeDWeight = exp(-nPhotonsXeD);
            //cout<<"LAr Photons "<<nPhotons<<", weight "<<LArWeight<<", XeD Photons "<<nPhotonsXeD<<", weight "<<XeDWeight<<endl;
            //create histograms only when needed (saves some memory, not so important for 1D hisots, but handy for 2d)
            if (h_energy[k]==0){
              h_energy[k]    = new TH1D(Form("h_energy_%i",k),Form("h_energy_%i",k),4000,0,4);
              h_energyLAr[k] = new TH1D(Form("h_energyLAr_%i",k),Form("h_energyLAr_%i",k),4000,0,4);
              h_energyLArXeD[k] = new TH1D(Form("h_energyLArXeD_%i",k),Form("h_energyLArXeD_%i",k),4000,0,4);
              h_energy[k]->SetDirectory(0);
              h_energyLAr[k]->SetDirectory(0);
              h_energyLArXeD[k]->SetDirectory(0);
            }
            //fill the energy histograms with the information of this step
            int eBin = h_energyLAr[k]->FindBin(energytotal[k]);
            h_energy[k]->Fill(energytotal[k]);
            h_energyLAr[k]->Fill(energytotal[k],LArWeight); //SetBinContent(eBin,h_energyLAr[k]->GetBinContent(eBin)    + LArWeight);
            h_energyLArXeD[k]->Fill(energytotal[k],XeDWeight);//SetBinContent(eBin,h_energyLArXeD[k]->GetBinContent(eBin) + XeDWeight);
            //hEnergySum->Fill(energytotal[k]);
          }
        }
      }

      inputfile->Close();
//      if (n>50) break; //only for test reasons, stops after 50 events
      
    }
  }


///////////////////////////////////////////////////////////////////////
  TFile *outputfile = new TFile(Form("results.root"),"RECREATE");
  outputfile->cd();
  n =0;
  for(j = 0;j<2000;j++){
    if(h_energy[j]){
      n++;
      /*
      h_energy[j]->Write();
      h_energyLAr[j]->Write();
      h_energyLArXeD[j]->Write();
      */
      //Final Spectrum is a sum of each detector histogram
      hEnergySum->Add(h_energy[j]);
      hEnergySumLAr->Add(h_energyLAr[j]);
      hEnergySumXeD->Add(h_energyLArXeD[j]);

    }
  }
  h_counts->Write();
  hEnergySum->Write();
  hEnergySumLAr->Write();
  hEnergySumXeD->Write();
  hEnergyInLAr->Write();
  cout << n << " histograms written" << endl;
  outputfile->Close();

  //gApplication->Terminate();
  return 0;

}
