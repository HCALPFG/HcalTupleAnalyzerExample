#!/bin/bash

root -l -b -q makeClass.C

echo " "

echo "Removing HcalPfgStudies.C files from this \"scripts\" directory "
rm HcalPfgStudies.C

echo "Moving HcalPfgStudies.h files to analysis directory"
mv HcalPfgStudies.h ../analysis

echo "Done"

echo " "