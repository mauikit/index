cd ../../Maui/build
#sudo rm -r *

cmake -DCMAKE_INSTALL_PREFIX=/usr .. && make && make install

pwd && cd ../../index-fm/build/ && pwd
cmake -DCMAKE_INSTALL_PREFIX=/usr .. && make && ./bin/index