cd BuildrootB1
source /home/anamika/Cyclotron/Build/geant4.10.06-install/bin/geant4.sh
cmake -DXercesC_LIBRARY=/opt/xerces-c/lib/libxerces-c.so -DGeant4_DIR=/home/anamika/Cyclotron/Build/geant4.10.06-install /home/anamika/Cyclotron/g4_examples/root_B1
make -j8
./exampleB1

