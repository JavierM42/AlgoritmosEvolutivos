#!/bin/bash 

cd malva/rep/GA
make
make SEQ
cd res
cp sol.txt ../../../../salida.txt