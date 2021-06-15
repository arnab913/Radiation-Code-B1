cd BuildrootB1
source /home/anirban/research/builds/geant4/geant4.10.06-install/bin/geant4.sh
cmake -DXercesC_LIBRARY=/opt/xerces-c/lib/libxerces-c.so -DGeant4_DIR=/home/anirban/research/builds/geant4/geant4.10.06-install/ /home/anirban/research/collaboration/Radiation-Code-B1
make -j8
./exampleB1
