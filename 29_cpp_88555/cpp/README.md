## There are totally 3 scripts in the document

## Each of them displays different features from others.

#

# 1solution.cpp

## Reads a csv file and displays a Restaurant Menu. Then asks users what to order in a numeric way.

## Once the person selects all the items, the program will split the amount by number of customers.

## This program also takes multiple orders and calculates all the order total once the program ends.

## To run this file, use following command:

## Compile first, 

## --> g++ 1solution.cp

## --> ./a.out


#

# 2file.cpp

## In this script user can input the values asked in the field. Once everything are answered, then they will be stored in txt file.

## To run this file, use following command:

## Compile first, 

## --> g++ 2file.cp

## --> ./a.out

# 

# 3image.cpp

## Open and displays an image using opencv library. 

# Here I will provide instructions to install opencv in ubuntu 18.04

### --> sudo apt-get update 

### --> sudo apt-get upgrade -y

### --> sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev

### --> sudo apt-get install python3-dev python3-numpy libtbb2 libtbb-dev

### --> sudo apt-get install libjpeg-dev libpng-dev libtiff5-dev libjasper-dev libdc1394-22-dev libeigen3-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev sphinx-common libtbb-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libopenexr-dev libgstreamer-plugins-base1.0-dev libavutil-dev libavfilter-dev libavresample-dev

### --> sudo su

### --> cd /opt

### --> git clone https://github.com/Itseez/opencv.git

### --> git clone https://github.com/Itseez/opencv_contrib.git


### --> cd opencv

### --> mkdir release

### --> cd release

### --> cmake -D BUILD_TIFF=ON -D WITH_CUDA=OFF -D ENABLE_AVX=OFF -D WITH_OPENGL=OFF -D WITH_OPENCL=OFF -D WITH_IPP=OFF -D WITH_TBB=ON -D BUILD_TBB=ON -D WITH_EIGEN=OFF -D WITH_V4L=OFF -D WITH_VTK=OFF -D BUILD_TESTS=OFF -D BUILD_PERF_TESTS=OFF -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib/modules /opt/opencv/

### --> make -j4

### --> make install

### --> ldconfig

### --> exit

### --> cd ~

### --> pkg-config --modversion opencv


## To run this file, use following command:

## Compile first, 

## --> g++ 3image.cpp -o output 'pkg-config --cflags --libs opencv'

## --> ./output