#define HcalPfgStudies_cxx
#include "HcalPfgStudies.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void HcalPfgStudies::Loop()
{
//   In a ROOT session, you can do:
//      root> .L HcalPfgStudies.C
//      root> HcalPfgStudies t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;

  // total number of entries
  Long64_t nentries = fChain->GetEntriesFast();

  std::map<int,TH1D*> hf_adc;
  std::map<int,TH1D*> hf_tdc;
  std::map<int,TH1D*> hf_charge;

  TH1D *hf_capID_SOI_check = new TH1D("hf_capID_SOI_check","",4,0,4);

  // std::map<std::vector<int>, TH1D*> hf_channel_timing;
  
  int hf_soi = 1;
  
  int power = 0;
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if (jentry+1 == std::pow(2,power)) {
      std::cout << "Processing event " << jentry+1 << "/" << nentries << std::endl;
      power++;
    }
    
    for (int ch = 0; ch < QIE10DigiIEta->size(); ++ch) {
      // cout << "HF channel " << "(" << QIE10DigiIEta->at(ch) << ", " << QIE10DigiIPhi->at(ch) << ", " << QIE10DigiDepth->at(ch) << ")" << endl;
      
      for (int ts = 0; ts < QIE10DigiCapID->at(ch).size(); ++ts) {
	// cout << "TS" << ts << endl;
	// cout << "ADC = " << QIE10DigiADC->at(ch).at(ts) << ", TDC = " <<  QIE10DigiLETDC->at(ch).at(ts) << endl;

	// ADC all channels each TS
	if (hf_adc.find(ts) == hf_adc.end()) {
	  hf_adc[ts] = new TH1D(Form("hf_ADC_all_channels_ts_%d",ts),"",300,0,300);
	}
	hf_adc[ts]->Fill(QIE10DigiADC->at(ch).at(ts));
	
	// TDC all channels each TS
	if (hf_tdc.find(ts) == hf_tdc.end()) {
	  hf_tdc[ts] = new TH1D(Form("hf_TDC_all_channels_ts_%d",ts),"",80,0,80);
	}
	hf_tdc[ts]->Fill(QIE10DigiLETDC->at(ch).at(ts));

	// charge all channels each TS
	if (hf_charge.find(ts) == hf_charge.end()) {
	  hf_charge[ts] = new TH1D(Form("hf_charge_all_channels_ts_%d",ts),"",300,0,3000);
	}
	hf_charge[ts]->Fill(QIE10DigiFC->at(ch).at(ts));
	
	// check cap ID rotation in SOI
	if (ts == hf_soi) {
	  int capId_check = (QIE10DigiCapID->at(ch).at(ts) - bx) % 4;
	  hf_capID_SOI_check->Fill(capId_check);
	}
	
	// HF timing for each channel (all TS)
	// std::vector<int> channel = {QIE10DigiIEta->at(ch),QIE10DigiIPhi->at(ch),QIE10DigiDepth->at(ch)};
	// if (hf_channel_timing.find(channel) == hf_channel_timing.end()) {
	// hf_channel_timing[channel] = new TH1D(Form("hf_timing_iEta_%d_iPhi_%d_depth_%d",QIE10DigiIEta->at(ch),QIE10DigiIPhi->at(ch),QIE10DigiDepth->at(ch)),"",150,0,75);
	// }
	// if (QIE10DigiLETDC->at(ch).at(ts) < 60.) {
	// double timing = QIE10DigiLETDC->at(ch).at(ts) / 2. + 25. * ts;  
	// hf_channel_timing[channel]->Fill(timing);
	// }

      } // end for loop over HF TS    
    } // end for loop over HF channels
    
  } // end for loop over nentries

  // output file for histograms
  TFile file_out("hcal_histograms.root","RECREATE");

  // write histograms to output file

  for (std::map<int,TH1D*>::iterator it = hf_adc.begin() ; it != hf_adc.end(); ++it)
    it->second->Write();
  for (std::map<int,TH1D*>::iterator it = hf_tdc.begin() ; it != hf_tdc.end(); ++it)
    it->second->Write();
  for (std::map<int,TH1D*>::iterator it = hf_charge.begin() ; it != hf_charge.end(); ++it)
    it->second->Write();
  
  hf_capID_SOI_check->Write();
  
  // for (std::map<std::vector<int>,TH1D*>::iterator it = hf_channel_timing.begin() ; it != hf_channel_timing.end(); ++it)
  // it->second->Write();
  
  file_out.ls();
  file_out.Close();
  
} // end Loop()
