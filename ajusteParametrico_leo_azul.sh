#!/bin/bash 

cp ajuste/config/cLOmLO.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_azul_cLOmLO.txt
cd ..
cd ..
cd ..

cp ajuste/config/cLOmMI.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_azul_cLOmMI.txt
cd ..
cd ..
cd ..

cp ajuste/config/cLOmHI.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_azul_cLOmHI.txt
cd ..
cd ..
cd ..

cp ajuste/config/cMImLO.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_azul_cMImLO.txt
cd ..
cd ..
cd ..

cp ajuste/config/cMImMI.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_azul_cMImMI.txt
cd ..
cd ..
cd ..

cp ajuste/config/cMImHI.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_azul_cMImHI.txt
cd ..
cd ..
cd ..

cp ajuste/config/cHImLO.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_azul_cHImLO.txt
cd ..
cd ..
cd ..

cp ajuste/config/cHImMI.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_azul_cHImMI.txt
cd ..
cd ..
cd ..

cp ajuste/config/cHImHI.cfg malva/rep/GA/newGA.cfg
cp ajuste/instancias/leo_azul.txt malva/ProblemInstances/CATAN-instances/entrada.txt
cd malva/rep/GA
make
make SEQ
cp res/sol.txt ../../../ajuste/resultados/leo_azul_cHImHI.txt
cd ..
cd ..
cd ..