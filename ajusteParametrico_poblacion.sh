#!/bin/bash 

cp ajuste/config/individuos10.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/individuos10.txt
cd ..
cd ..
cd ..

cp ajuste/config/individuos50.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/individuos50.txt
cd ..
cd ..
cd ..

cp ajuste/config/individuos100.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/individuos100.txt
cd ..
cd ..
cd ..

cp ajuste/config/individuos200.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/individuos200.txt
cd ..
cd ..
cd ..

cp ajuste/config/individuos500.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/individuos500.txt
cd ..
cd ..
cd ..