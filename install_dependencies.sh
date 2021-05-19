#!/bin/bash
sudo apt update && sudo apt upgrade -y
sudo apt install -y gcc g++ make git cmake cmake-gui qt5-qmake qt5-default libqt5serialport5-dev
sudo apt install -y libudev-dev libusb-dev libfox-1.6-dev autotools-dev autoconf automake libtool libsfml*

git submodule init
git submodule update

cd hidapi
./bootstrap
./configure
make -j8
sudo make install
cd ../

chmod +x compile_PoolsideGUI.sh
./compile_PoolsideGUI.sh