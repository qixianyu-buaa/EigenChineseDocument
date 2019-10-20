#ifndef INPLACE_MATRIX_DECOMPOSITIONS_HPP
#define INPLACE_MATRIX_DECOMPOSITIONS_HPP
#include "HeaderFile.h"
namespace Chapter2_DenseLinearProblemsAndDecompositions
{
//complete pivoting和partial pivoting
// （1） complete pivoting（即full pivoting），就是在矩阵分解或高斯消元的过程中，主元是在未进行变换的所有行和列之间进行选择。也就是需要同时进行行交换和列交换。
// （2） partial pivoting就是只在当前进行变换的列中选择主元，只需要进行行交换
namespace Section4_InplaceDecompisitions
{
void InplaceMatrixDecompositions()
{
        LOG();
        // 从Eigen 3.3开始，LU，Cholesky和QR分解可以就地进行操作，即直接在给定的输入矩阵内进行。
        //当处理大量矩阵或可用内存非常有限（嵌入式系统）时，此功能特别有用。

        // 为此，必须使用Ref <>矩阵类型实例化各个分解类，
        //并且必须使用输入矩阵作为参数来构造分解对象。作为示例，让我们考虑partial pivoting的LU分解。

        //声明一个2x2矩阵 A:

        MatrixXd A(2, 2);
        A << 2, -1, 1, 3;
        cout << "Here is the input matrix A before decomposition:\n"
             << A << endl;
        // Output is:
        // Here is the input matrix A before decomposition:
        //  2 -1
        //  1  3

        //毫不奇怪！然后，声明我们的Inplace LU对象lu，并检查矩阵的内容A:
        // 这相当于把A和lu绑定了，所以后文中即使计算A1，A1的内容也不会改变
        PartialPivLU<Ref<MatrixXd>> lu(A);
        cout << "Here is the input matrix A after decomposition:\n"
             << A << endl;

        // Output is:
        // Here is the input matrix A after decomposition:
        //   2  -1
        // 0.5 3.5

        // 在这里，lu对象计算并将L和U因数存储在矩阵所保存的内存中A。
        //因此，系数A在分解过程中已被破坏，并由L和U因子代替，可以验证：
        // 也就是分解的结果保存在矩阵中
        cout << "Here is the matrix storing the L and U factors:\n"
             << lu.matrixLU() << endl;
        // Output is:
        // Here is the matrix storing the L and U factors:
        //   2  -1
        // 0.5 3.5
        //然后，该lu对象可以像往常一样使用，例如解决Ax = b问题：
        MatrixXd A0(2, 2);
        A0 << 2, -1, 1, 3;
        VectorXd b(2);
        b << 1, 2;
        VectorXd x = lu.solve(b);
        cout << "Residual: " << (A0 * x - b).norm() << endl;
        // Output is:
        //Residual: 0
        //在这里，由于原始矩阵的内容A已丢失，因此我们必须声明一个新矩阵A0以验证结果。

        //由于在A和lu之间共享内存，因此修改矩阵A将导致lu无效。
        //可以通过修改的内容A并尝试再次解决初始问题来轻松验证这一点：
        A << 3, 4, -2, 1;
        x = lu.solve(b);
        // Output is:
        //Residual: 15.8114
        //请注意，这没有共享指针，所以保持输入矩阵A和lu具有共同的生命周期是用户的责任

        //如果要使用修改后的A更新因式分解，则必须像往常一样调用compute方法：
        A0 = A; // save A
        lu.compute(A);
        x = lu.solve(b);
        cout << "Residual: " << (A0 * x - b).norm() << endl;
        // Output is:
        //Residual: 0

        //请注意，调用compute不会更改该lu对象引用的内存。
        //因此，如果使用A1不同于的另一个矩阵调用计算方法A，
        //则A1不会修改内容。这仍然A是将用于存储矩阵的L和U因子的内容A1。可以很容易地验证如下：
        MatrixXd A1(2, 2);
        A1 << 5, -2, 3, 4;
        lu.compute(A1);
        cout << "Here is the input matrix A1 after decomposition:\n"
             << A1 << endl;
        // Output is:
        // Here is the input matrix A1 after decomposition:
        //  5 -2
        //  3  4

        //矩阵A1是不变的，因此可以求解A1 *x = b，直接检查残差而无需任何副本A1 :
        x = lu.solve(b);
        cout << "Residual: " << (A1 * x - b).norm() << endl;
        // Output is:
        //Residual: 2.48253e-16

        //这是支持此就位机制的矩阵分解列表：
        // class LLT
        // class LDLT
        // class PartialPivLU
        // class FullPivLU
        // class HouseholderQR
        // class ColPivHouseholderQR
        // class FullPivHouseholderQR
        // class CompleteOrthogonalDecomposition
}

} // namespace Section4_InplaceDecompisitions
} // namespace Chapter2_DenseLinearProblemsAndDecompositions

#endif