#ifndef SOLVING_LINEAR_LEAST_SQUARES_SYSTEMS_HPP
#define SOLVING_LINEAR_LEAST_SQUARES_SYSTEMS_HPP
#include "HeaderFile.h"
namespace Chapter2_DenseLinearProblemsAndDecompositions
{

namespace Section3_SolvingLinearLeastSquaresSystems
{
// 本页介绍如何使用本征求解线性最小二乘系统。一个超定方程组，例如Ax = b，没有解。
//在这种情况下，在差异Ax - b尽可能小的意义上，搜索最接近解的向量x是有意义的。
//该x称为最小二乘解（如果使用欧几里得范数）。
//本页讨论的三种方法是SVD分解，QR分解和正态方程。
//其中，SVD分解通常最准确但最慢，正则方程(normal equations)最快但最不准确，QR分解介于两者之间。

void UsingTheSvdDecomposition()
{
        LOG();
        //BDCSVD类中的solve()中方法可以直接用来求解线性最小二乘系统。
        //仅计算奇异值（此类的默认值）是不够的。您还需要奇异矢量，但是稀疏SVD分解足以计算最小二乘解：
        MatrixXf A = MatrixXf::Random(3, 2);
        cout << "Here is the matrix A:\n"
             << A << endl;
        VectorXf b = VectorXf::Random(3);
        cout << "Here is the right hand side b:\n"
             << b << endl;
        cout << "The least-squares solution is:\n"
             << A.bdcSvd(ComputeThinU | ComputeThinV).solve(b) << endl;
        // Output is:
        // Here is the matrix A:
        //   0.68  0.597
        // -0.211  0.823
        //  0.566 -0.605
        // Here is the right hand side b:
        //  -0.33
        //  0.536
        // -0.444
        // The least-squares solution is:
        // -0.67
        // 0.314
}
void UsingTheQRDecomposition()
{
        LOG();
        //QR分解类中的resolve()方法还计算最小二乘解。
        //有3种QR分解类：HouseholderQR（无pivoting，因此快速但不稳定），ColPivHouseholderQR（列枢轴，因此较慢但更准确）和FullPivHouseholderQR（全枢轴，因此最慢且最稳定）。
        MatrixXf A = MatrixXf::Random(3, 2);
        VectorXf b = VectorXf::Random(3);
        cout << "The solution using the QR decomposition is:\n"
             << A.colPivHouseholderQr().solve(b) << endl;
        // Output is:
        // The solution using the QR decomposition is:
        // -0.67
        // 0.314
}

void UsingNormalEquations()
{
        LOG();
        //找到Ax = b的最小二乘解等效于求解法线方程A T Ax = A T b。
        //如果矩阵A是病态的，那么这不是一个好方法，因为A T A的条件数是A的条件数的平方。
        //这意味着与使用其他方法相比，使用正则方程式丢失的数字要多两倍。
        MatrixXf A = MatrixXf::Random(3, 2);
        VectorXf b = VectorXf::Random(3);
        cout << "The solution using normal equations is:\n"
             << (A.transpose() * A).ldlt().solve(A.transpose() * b) << endl;
}
} // namespace Section3_SolvingLinearLeastSquaresSystems
} // namespace Chapter2_DenseLinearProblemsAndDecompositions

#endif