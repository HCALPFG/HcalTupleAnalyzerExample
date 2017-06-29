# HcalTupleAnalyzerExample
Example code to get started with analyzing the output of HcalTupleMaker

## To build
```
# setup environment  
export SCRAM_ARCH=slc6_amd64_gcc530  

# setup cmssw release  
cmsrel CMSSW_9_2_4  
cd CMSSW_9_2_4/src  
cmsenv    

# clone repository  
mkdir HCALPFG  
cd HCALPFG  
git clone git@github.com:HCALPFG/HcalTupleAnalyzerExample.git  
```

## To run
```
# setup cmssw environment  
cd HCALPFG/HcalTupleAnalyzerExample  
cmsenv  

# obtain grid proxy (optional)  
voms-proxy-init -voms cms -rfc  
```