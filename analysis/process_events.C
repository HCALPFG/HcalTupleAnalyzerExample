#include "HcalPfgStudies.C"

void process_events() {
  // use stopwatch to time
  TStopwatch sw;
  sw.Start();

  // create tchain of all files to loop over
  TChain *chain = new TChain("hcalTupleTree/tree");

  // chain files to be looped over
  chain->Add("HcalTupleMaker_output.root",0);
  
  chain->ls();
  cout << "Total number of entries: " << chain->GetEntries() << endl;
  
  // create instance of class, passing our chain
  HcalPfgStudies loop(chain);

  // loop over all entries of our tree
  loop.Loop();

  // stop stopwatch
  sw.Stop();

  // convert total time to minutes
  std::cout << "RealTime : " << sw.RealTime() / 60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << sw.CpuTime()  / 60.0 << " minutes" << std::endl;
}
