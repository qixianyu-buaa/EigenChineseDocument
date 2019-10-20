#ifndef ALIASING_HPP
#define ALIASING_HPP
#include "HeaderFile.h"

namespace Chapter1_DenseMatrixAndArrary
{

namespace Section9_Aliasing
{
// 这一节比较绕
// 在Eigen中，混淆(aliasing)是指相同的矩阵（或数组或向量）出现在赋值运算符的左侧和右侧的赋值语句;
// 例如，A = AB ,  a = a^Tb  A=A*A
// 产生混淆的原因是Eigen采用惰性求值
// 混淆可能是有害的，也可能是无害的,有害的混淆，导致可能不正确的结果，无害的混淆可以产生正确的结果

// 有害混淆
// 使用.eval()方法，可以解决混淆问题。具体的说，.eval()方法生成临时对象，然后再执行赋值操作
//  如果Eigen中假定该操作是混淆的，那么它会自动使用.eval()方法，而不需要我们显示调用

// 无害混淆是我们不需要评估，它对系数计算无害。这包括标量乘法和矩阵或数组加法。

// 将两个矩阵相乘时，Eigen会假定发生混叠(注意，Eigen3.3以后的版本中需要区分目标矩阵大小是否改变了)
//如果您知道没有混淆，则可以使用noalias()。

// 在所有其他情况下，Eigen假定不存在混叠问题，因此如果实际上发生混叠，则会给出错误的结果。
// 为防止这种情况，您必须使用eval（）或xxxInPlace（）函数之一。

void Aliasing()
{
        LOG();
        //在Eigen中，混淆(aliasing)是指相同的矩阵（或数组或向量）出现在赋值运算符的左侧和右侧的赋值语句。
        // 例如mat = 2 * mat(虽混淆但无害);或mat = mat.transpose();(有害的混淆)。

        MatrixXi mat(3, 3);
        mat << 1, 2, 3, 4, 5, 6, 7, 8, 9;
        cout << "Here is the matrix mat:\n"
             << mat << endl;
        // This assignment shows the aliasing problem
        mat.bottomRightCorner(2, 2) = mat.topLeftCorner(2, 2);
        cout << "After the assignment, mat = \n"
             << mat << endl;

        // Output  is:
        // Here is the matrix mat:
        // 1 2 3
        // 4 5 6
        // 7 8 9
        // After the assignment, mat =
        // 1 2 3
        // 4 1 2
        // 7 4 1

        // 理解混淆的关键是了解惰性求值

        // 输出结果不是人们所期望的，问题是产生了有害混淆
        // mat.bottomRightCorner（2,2）= mat.topLeftCorner（2,2）;
        // 该赋值具有混淆aliasing）：系数mat(1,1)既出现在mat.bottomRightCorner(2,2)分配左侧的块中mat.topLeftCorner(2,2)，又出现在右侧的块中。
        // 分配后，右下角的（2,2）项应具有mat(1,1)分配前的值5。但是，输出显示mat(2,2)实际上为1。
        // 问题在于Eigen使用了惰性求值。结果类似于
        // mat（1,1）= mat（0,0）;
        // mat（1,2）= mat（0,1）;
        // mat（2,1）= mat（1,0）;
        // mat（2,2）= mat（1,1）;
        // 因此，mat(2,2)分配了新值mat(1,1)而不是旧值。
        // 可以通过调用eval()解决此问题(注:eval()负责生成临时对象而避免混淆)
        // 尝试缩小矩阵时，混淆也会发生。
        // 例如，表达式vec = vec.head(n)和mat = mat.block(i,j,r,c)具有混淆。

        //通常，在编译时无法检测到混淆：如果mat在第一个示例中稍大一点，则块将不会重叠，也不会出现混淆问题。
        //但是Eigen确实会在运行时检测到一些混淆实例。Matrix和向量算术中提到了以下显示别名的示例：

        // 注意：这段代码会报错～～～～～～

        // Matrix2i a;
        // a << 1, 2, 3, 4;
        // cout << "Here is the matrix a:\n"
        //      << a << endl;
        // a = a.transpose(); // !!! do NOT do this !!!
        // cout << "and the result of the aliasing effect:\n"
        //      << a << endl;

        // 输出显示混淆(alising)问题。
        // 但是，默认情况下，Eigen使用运行时断言来检测到此情况并退出，并显示如下消息
        // void Eigen::DenseBase<Derived>::checkTransposeAliasing(const OtherDerived&) const
        // [with OtherDerived = Eigen::Transpose<Eigen::Matrix<int, 2, 2, 0, 2, 2> >, Derived = Eigen::Matrix<int, 2, 2, 0, 2, 2>]:
        // Assertion `(!internal::check_transpose_aliasing_selector<Scalar,internal::blas_traits<Derived>::IsTransposed,OtherDerived>::run(internal::extract_data(derived()), other))
        // && "aliasing detected during transposition, use transposeInPlace() or evaluate the rhs into a temporary using .eval()"' failed.

        //用户可以通过定义EIGEN_NO_DEBUG宏来关闭Eigen的运行时断言
}

void ResolvingAliasingIssues()
{
        LOG();
        //解决方法：Eigen必须将右侧完全看作一个临时矩阵/数组，然后将其分配给左侧。
        //函数**eval()**正是这样做的,作用为生成一个临时对象
        MatrixXi mat(3, 3);
        mat << 1, 2, 3, 4, 5, 6, 7, 8, 9;
        cout << "Here is the matrix mat:\n"
             << mat << endl;
        // The eval() solves the aliasing problem
        mat.bottomRightCorner(2, 2) = mat.topLeftCorner(2, 2).eval();
        cout << "After the assignment, mat = \n"
             << mat << endl;

        //相同的解决方案也适用于第二示例中，与转置：只需更换线a = a.transpose();用a = a.transpose().eval();。但是，在这种常见情况下，有更好的解决方案。
        //Eigen提供了专用函数transposeInPlace()，该函数通过其转置来替换矩阵。如下所示：
        MatrixXf a(2, 3);
        a << 1, 2, 3, 4, 5, 6;
        cout << "Here is the initial matrix a:\n"
             << a << endl;
        a.transposeInPlace();
        cout << "and after being transposed:\n"
             << a << endl;
             
        //如果xxxInPlace()函数可用，则最好使用它，因为它可以更清楚地指示您正在做什么。
        //这也可以让Eigen更积极地进行优化。这些是提供的一些xxxInPlace()函数：
        // Original function	                      In-place function
        // MatrixBase::adjoint()	          MatrixBase::adjointInPlace()
        // DenseBase::reverse()	                 DenseBase::reverseInPlace()
        // LDLT::solve()	                            LDLT::solveInPlace()
        // LLT::solve()	                                      LLT::solveInPlace()
        // TriangularView::solve()	        TriangularView::solveInPlace()
        // DenseBase::transpose()	       DenseBase::transposeInPlace()

        //在特殊情况下，矩阵或向量使用类似的表达式缩小vec = vec.head(n)，则可以使用conservativeResize()。
}

void AliasingAndComponentWiseOperations()
{
        LOG();
        //如果同一矩阵或数组同时出现在赋值运算符的左侧和右侧，则可能很危险，因此通常有必要显示地评估右侧
        //但是，应用基于元素的操作（例如矩阵加法，标量乘法和数组乘法）是安全的。
        //以下示例仅具有基于组件的操作。因此，即使相同的矩阵出现在赋值符号的两侧，也不需要eval()。
        MatrixXf mat(2, 2);
        mat << 1, 2, 4, 7;
        cout << "Here is the matrix mat:\n"
             << mat << endl
             << endl;
        mat = 2 * mat;
        cout << "After 'mat = 2 * mat', mat = \n"
             << mat << endl
             << endl;
        mat = mat - MatrixXf::Identity(2, 2);
        cout << "After the subtraction, it becomes\n"
             << mat << endl
             << endl;
        ArrayXXf arr = mat;
        arr = arr.square();
        cout << "After squaring, it becomes\n"
             << arr << endl
             << endl;
        // Combining all operations in one statement:
        mat << 1, 2, 4, 7;
        mat = (2 * mat - MatrixXf::Identity(2, 2)).array().square();
        cout << "Doing everything at once yields\n"
             << mat << endl
             << endl;
        // Output is:
        // Here is the matrix mat:
        // 1 2
        // 4 7

        // After 'mat = 2 * mat', mat =
        //  2  4
        //  8 14

        // After the subtraction, it becomes
        //  1  4
        //  8 13

        // After squaring, it becomes
        //   1  16
        //  64 169

        // Doing everything at once yields
        //   1  16
        //  64 169
        //通常，如果表达式右侧的（i，j）条目仅取决于左侧矩阵或数组的（i，j）条目
        //而不依赖于其他任何表达式，则赋值是安全的。在这种情况下，不必显示地评估右侧(.evl())。
}

void AliasingAndMatrixMultiplication()
{
        LOG();

        //在目标矩阵**未调整大小**的情况下，矩阵乘法是Eigen中唯一假定默认情况下为混淆的。
        // 若假定混淆，则会使用eval()生成临时对象,所以是安全的。
        //因此，如果matA是平方矩阵，则该语句matA = matA * matA是安全的。
        //Eigen中的所有其他操作都假定没有混淆问题，这是因为结果被分配给了不同的矩阵，或者因为它是逐个元素的操作。
        {
                MatrixXf matA(2, 2);
                matA << 2, 0, 0, 2;
                matA = matA * matA;
                cout << matA << endl;
        }

        // 但是，这是有代价的。执行表达式时matA = matA * matA
        // Eigen会在计算后的临时矩阵中评估赋值给matA的乘积。
        //虽然可以，但是在将乘积分配给其他矩阵（例如matB = matA * matA）时，Eigen会执行相同的操作。
        //在这种情况下，直接评估matB,
        // 而不是先将matA*matA生成临时对象，然后评估临时对象，最后将临时对象赋值给矩阵matB更高效
        //我们可以使用noalias函数指示没有混淆，如下所示：matB.noalias() = matA * matA。
        //这使Eigen可以matA * matA直接将矩阵乘积在matB中评估。
        {
                MatrixXf matA(2, 2), matB(2, 2);
                matA << 2, 0, 0, 2;
                // Simple but not quite as efficient
                matB = matA * matA;
                cout << matB << endl;
                // More complicated but also more efficient
                matB.noalias() = matA * matA;
                cout << matB << endl;
                // Output is:
                //4 0
                // 0 4

                // 4 0
                // 0 4
        }

        {
                //当然，不应该在实际上发生混淆时使用noalias()，如果这样做，则**可能**会得到错误的结果：
                //报错吗？我的平台上没报错
                MatrixXf matA(2, 2);
                matA << 2, 0, 0, 2;
                matA.noalias() = matA * matA;
                cout << matA << endl;
                // Output is:
                //4 0
                // 0 4
        }

        {
                //此外，从Eigen 3.3 开始，
                //如果调整了目标矩阵的大小(注意，上文中的操作假定目标矩阵大小不变)
                //并且未将乘积直接分配给目标，则不假定混淆。因此，以下示例也是错误的：
                MatrixXf A(2, 2), B(3, 2);
                B << 2, 0, 0, 3, 1, 1;
                A << 2, 0, 0, -2;
                A = (B * A).cwiseAbs(); // 由于不假定混淆，所以需要我们显示评价
                cout << A << endl;
                //报错吗？我的平台上没报错
                // Output is
                // 4 0
                // 0 6
                // 2 2
        }

        {
                //对于任何混淆问题，您都可以通过在赋值之前显式评估表达式来解决它：
                MatrixXf A(2, 2), B(3, 2);
                B << 2, 0, 0, 3, 1, 1;
                A << 2, 0, 0, -2;
                A = (B * A).eval().cwiseAbs();
                cout << A << endl;

                // Output is
                // 4 0
                // 0 6
                // 2 2
        }
}

} // namespace Section9_Aliasing
} // namespace Chapter1_DenseMatrixAndArrary

#endif