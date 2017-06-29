void makeClass() {
  // choose file to make class from
  TFile *f = TFile::Open("root://cmseos.fnal.gov//store/user/abuccill/hcal-analysis/hf_phase_settings_2017/hcal_pfg_ZeroBias_Run2017A-v1_RAW_fill_5822_merged.root");
  
  // list the contents of this file
  f->ls();
  
  // get tree
  TTree *tree = (TTree *) f->Get("hcalTupleTree/tree");
  
  // print tree contents
  tree->Print();
  
  // list the total number of entries in tree
  cout << "Entries: " << tree->GetEntries() << endl;
  
  // make class
  tree->MakeClass("HcalPfgStudies");
}
