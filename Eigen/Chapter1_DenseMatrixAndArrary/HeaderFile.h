#ifndef HEADER_FILE_H
#define HEADER_FILE_H

#include <iostream>
// The Eigen/Dense header file defines all member functions for the MatrixXd type and related types
#include <Eigen/Dense>
//All classes and functions defined in this header file (and other Eigen header files) are in the Eigen namespace.

#define LOG()  printf("\n=========  %s() Output is  ========= \n",__FUNCTION__);

using namespace Eigen;
using namespace std;

#endif