int plot_hf() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1,0);
  gStyle->SetNdivisions(505);
  gStyle->SetOptStat("ourme");
  
  TFile *f = TFile::Open("../analysis/hcal_histograms.root");
  cout << "Opening " << f->GetName() << endl;

  int nTS_hf = 3;

  TCanvas *c_adc = new TCanvas("c_adc","",1600,800);
  c_adc->Divide(3,1);
  for (int ts = 0; ts < nTS_hf; ++ts) {
    TString TS = Form("%d",ts);
    c_adc->cd(1+ts);
    TH1D *h = (TH1D*) f->Get("hf_ADC_all_channels_ts_"+TS);
    h->Draw();
    h->SetTitle("all channels TS"+ TS);
    h->GetXaxis()->SetTitle("ADC");
    h->GetXaxis()->SetRangeUser(0,150);
    gPad->SetLogy();
  }
  c_adc->SaveAs("hf_adc_all_channels.pdf");
    
  return 0;
}
