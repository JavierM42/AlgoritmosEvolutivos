#!/bin/bash 

cp ajuste/config/cLOmLO.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_blanco.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_blanco_cLOmLO.txt
cd ..
cd ..
cd ..

cp ajuste/config/cLOmMI.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_blanco.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_blanco_cLOmMI.txt
cd ..
cd ..
cd ..

cp ajuste/config/cLOmHI.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_blanco.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_blanco_cLOmHI.txt
cd ..
cd ..
cd ..

cp ajuste/config/cMImLO.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_blanco.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_blanco_cMImLO.txt
cd ..
cd ..
cd ..

cp ajuste/config/cMImMI.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_blanco.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_blanco_cMImMI.txt
cd ..
cd ..
cd ..

cp ajuste/config/cMImHI.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_blanco.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_blanco_cMImHI.txt
cd ..
cd ..
cd ..

cp ajuste/config/cHImLO.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_blanco.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_blanco_cHImLO.txt
cd ..
cd ..
cd ..

cp ajuste/config/cHImMI.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_blanco.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_blanco_cHImMI.txt
cd ..
cd ..
cd ..

cp ajuste/config/cHImHI.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_blanco.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_blanco_cHImHI.txt
cd ..
cd ..
cd ..