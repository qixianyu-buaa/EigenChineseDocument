#ifndef HEADER_FILE_H
#define HEADER_FILE_H

#include <iostream>

#include <Eigen/Sparse>
// Module	Header file	Contents
// SparseCore	 #include <Eigen/SparseCore>  SparseMatrix and SparseVector classes, matrix assembly, basic sparse linear algebra (including sparse triangular solvers)
// SparseCholesky	 #include <Eigen/SparseCholesky>    Direct sparse LLT and LDLT Cholesky factorization to solve sparse self-adjoint positive definite problems
// SparseLU	 #include<Eigen/SparseLU>  Sparse LU factorization to solve general square sparse systems
// SparseQR	 #include<Eigen/SparseQR>     Sparse QR factorization for solving sparse linear least-squares problems
// IterativeLinearSolvers	 #include <Eigen/IterativeLinearSolvers>    Iterative solvers to solve large general linear square problems (including self-adjoint positive definite problems)
// Sparse	  #include <Eigen/Sparse>     Includes all the above modules

//All classes and functions defined in this header file (and other Eigen header files) are in the Eigen namespace.
using namespace Eigen;
using namespace std;

#define LOG() printf("\n=========  %s() Output is  ========= \n", __FUNCTION__);

#endif