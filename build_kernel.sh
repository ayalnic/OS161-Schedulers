#!/bin/bash

module load os161

echo "Make sure you run this script from the root directory of the project!"

base_dir=$PWD
cd $base_dir/src

echo " *** CONFIGURING DUMBVM KERNEL *** "
cd kern/conf
./config DUMBVM
echo "*************************************"
echo ""

echo " *** COMPILING AND INSTALLING KERNEL *** "
cd $base_dir/src/kern/compile/DUMBVM
bmake depend
bmake
bmake install
echo " *************************************** "
echo ""

echo " *** Build done. Run 'sys161 kenrnel' from root*** "
