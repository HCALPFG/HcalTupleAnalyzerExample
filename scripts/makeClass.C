void makeClass() {
  // choose file to make class from
  TFile *f = TFile::Open("HcalTupleMaker_output.root");
  
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
