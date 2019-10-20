#ifndef MatrixAndVectorArithmetic_HPP
#define MatrixAndVectorArithmetic_HPP
#include "HeaderFile.h"
namespace Chapter1_DenseMatrixAndArrary
{
namespace Section2_MatrixAndVectorArithmetic
{

// 本部分介绍了矩阵在线性代数中的基本运算，相信学过线性代数的同学理解起来十分容易
// 需要注意的是：
//      1)对于a = a.transpose()操作，应该使用a.transposeInPlace(),  见TranspositionAndConjugation()
//      2)向量叉积只适用于大小为3的向量，点积适用于任意向量, 见DotProductAndCrossProduct()
//      3)理解矩阵Reduction操作的意义

void AdditionAndSubtraction()
{
        LOG();
        //binary operator + as in a+b
        //binary operator - as in a-b
        //unary operator - as in -a
        //compound operator += as in a+=b
        //compound operator -= as in a-=b
        Matrix2d a;
        a << 1, 2,
            3, 4;
        MatrixXd b(2, 2);
        b << 2, 3,
            1, 4;
        std::cout << "a + b =\n"
                  << a + b << std::endl;
        std::cout << "a - b =\n"
                  << a - b << std::endl;
        std::cout << "Doing a += b;" << std::endl;
        a += b;
        std::cout << "Now a =\n"
                  << a << std::endl;
        Vector3d v(1, 2, 3);
        Vector3d w(1, 0, 0);
        std::cout << "-v + w - v =\n"
                  << -v + w - v << std::endl;
        //Output is:
        // a + b =
        // 3 5
        // 4 8
        // a - b =
        // -1 -1
        //  2  0
        // Doing a += b;
        // Now a =
        // 3 5
        // 4 8
        // -v + w - v =
        // -1
        // -4
        // -6
}

void ScalarMultiplicationAndDivision()
{
        LOG();
        // binary operator * as in matrix*scalar
        // binary operator * as in scalar*matrix
        // binary operator / as in matrix/scalar
        // compound operator *= as in matrix*=scalar
        // compound operator /= as in matrix/=scalar
        Matrix2d a;
        a << 1, 2,
            3, 4;
        Vector3d v(1, 2, 3);
        std::cout << "a * 2.5 =\n"
                  << a * 2.5 << std::endl;
        std::cout << "0.1 * v =\n"
                  << 0.1 * v << std::endl;
        std::cout << "Doing v *= 2;" << std::endl;
        v *= 2;
        std::cout << "Now v =\n"
                  << v << std::endl;
        //Output is:
        //  a * 2.5 =
        // 2.5   5
        // 7.5  10
        // 0.1 * v =
        // 0.1
        // 0.2
        // 0.3
        // Doing v *= 2;
        // Now v =
        // 2
        // 4
        // 6
}
void ANoteAboutExpressionTemplates()
{
        LOG();
        // 在Eigen中，诸如算术运算符（例如）operator+自己并不执行任何计算,
        // 它们仅返回描述要执行的计算的“表达式对象”。当计算整个表达式时，实际的计算将在稍后进行，
        // 通常在中operator=。尽管这听起来很沉重，但是任何现代的优化编译器都可以优化该抽象，从而获得完美优化的代码。例如，当您这样做时：

        // VectorXf a(50), b(50), c(50), d(50);
        // ...
        // a = 3*b + 4*c + 5*d;
        // Eigen将其编译为一个for循环，因此数组仅被遍历一次。简化（例如忽略SIMD优化），此循环如下所示：

        // 对于（int i = 0; i <50; ++ i）
        //   a [i] = 3 * b [i] + 4 * c [i] + 5 * d [i]；

        // 因此，您不必担心Eigen使用相对较大的算术表达式：它只会为Eigen提供更多优化机会。
}

void TranspositionAndConjugation()
{

        LOG();
        //矩阵或向量的转置$ a ^ T $，共轭$ \ bar {a} $和伴随（即共轭转置）分别通过成员函数transpose（），conjugate（）和adjoint（）获得
        {
                MatrixXcf a = MatrixXcf::Random(2, 2); //MatrixXcf 为复数矩阵
                cout << "Here is the matrix a\n"
                     << a << endl;
                cout << "Here is the matrix a^T\n"
                     << a.transpose() << endl;
                cout << "Here is the conjugate of a\n"
                     << a.conjugate() << endl;
                cout << "Here is the matrix a^*\n"
                     << a.adjoint() << endl;

                //Output is:
                //   Here is the matrix a
                //  (-0.211,0.68) (-0.605,0.823)
                //  (0.597,0.566)  (0.536,-0.33)
                // Here is the matrix a^T
                //  (-0.211,0.68)  (0.597,0.566)
                // (-0.605,0.823)  (0.536,-0.33)
                // Here is the conjugate of a
                //  (-0.211,-0.68) (-0.605,-0.823)
                //  (0.597,-0.566)    (0.536,0.33)
                // Here is the matrix a^*
                //  (-0.211,-0.68)  (0.597,-0.566)
                // (-0.605,-0.823)    (0.536,0.33)
        }

        // 注意：对于一个矩阵自身的转置，应该使用.transposeInPlace()
        {
                Matrix2i a;
                a << 1, 2, 3, 4;
                cout << "Here is the matrix a:\n"
                     << a << endl;
                // 坑～～～～～～不应该这样～～～～～～～～
                // a = a.transpose(); // !!! do NOT do this !!!
                // cout << "and the result of the aliasing effect:\n"
                //      << a << endl;

                // 应该这样～～～～
                a.transposeInPlace();
                cout << "and after being transposed:\n"
                     << a << endl;
                //Output is:
                // Here is the initial matrix a:
                // 1 2 3
                // 4 5 6
                // and after being transposed:
                // 1 4
                // 2 5
                // 3 6
        }
}

void MatrixMatrixAndMatrixVectorMultiplication()
{
        LOG();
        Matrix2d mat;
        mat << 1, 2,
            3, 4;
        Vector2d u(-1, 1), v(2, 0);
        std::cout << "Here is mat*mat:\n"
                  << mat * mat << std::endl;
        std::cout << "Here is mat*u:\n"
                  << mat * u << std::endl;
        std::cout << "Here is u^T*mat:\n"
                  << u.transpose() * mat << std::endl;
        std::cout << "Here is u^T*v:\n"
                  << u.transpose() * v << std::endl;
        std::cout << "Here is u*v^T:\n"
                  << u * v.transpose() << std::endl;
        std::cout << "Let's multiply mat by itself" << std::endl;
        mat = mat * mat;
        std::cout << "Now mat is mat:\n"
                  << mat << std::endl;

        //Output is:
        // Here is mat*mat:
        //  7 10
        // 15 22
        // Here is mat*u:
        // 1
        // 1
        // Here is u^T*mat:
        // 2 2
        // Here is u^T*v:
        // -2
        // Here is u*v^T:
        // -2 -0
        //  2  0
        // Let's multiply mat by itself
        // Now mat is mat:
        //  7 10
        // 15 22
}

void DotProductAndCrossProduct()
{
        LOG();
        //  cross product is only for vectors of size 3. Dot product is for vectors of any sizes
        // 叉积只适用于大小为3的向量，点积适用于任意向量
        Vector3d v(1, 2, 3);
        Vector3d w(0, 1, 2);
        cout << "Dot product: " << v.dot(w) << endl;
        double dp = v.adjoint() * w; // automatic conversion of the inner product to a scalar
        cout << "Dot product via a matrix product: " << dp << endl;
        cout << "Cross product:\n"
             << v.cross(w) << endl;
        // Output is:
        // Dot product: 8
        // Dot product via a matrix product: 8
        // Cross product:
        //  1
        // -2
        //  1
}

void BasicArithmeticReductionOperations()
{
        LOG();
        // Eigen also provides some reduction operations to reduce a given matrix or vector to a single value
        // such as the sum (computed by sum()), product (prod()), or the maximum (maxCoeff()) and minimum (minCoeff()) of all its coefficients.
        Eigen::Matrix2d mat;
        mat << 1, 2,
            3, 4;
        //元素和，元素乘积，元素均值，最小系数，最大系数，踪
        cout << "Here is mat.sum():       " << mat.sum() << endl;
        cout << "Here is mat.prod():      " << mat.prod() << endl;
        cout << "Here is mat.mean():      " << mat.mean() << endl;
        cout << "Here is mat.minCoeff():  " << mat.minCoeff() << endl;
        cout << "Here is mat.maxCoeff():  " << mat.maxCoeff() << endl;
        cout << "Here is mat.trace():     " << mat.trace() << endl;

        // 可以返回元素位置
        Matrix3f m = Matrix3f::Random();
        std::ptrdiff_t i, j;
        float minOfM = m.minCoeff(&i, &j);
        cout << "Here is the matrix m:\n"
             << m << endl;
        cout << "Its minimum coefficient (" << minOfM
             << ") is at position (" << i << "," << j << ")\n\n";
        RowVector4i v = RowVector4i::Random();
        int maxOfV = v.maxCoeff(&i);
        cout << "Here is the vector v: " << v << endl;
        cout << "Its maximum coefficient (" << maxOfV
             << ") is at position " << i << endl;
        // Output is:
        // Here is mat.sum():       10
        // Here is mat.prod():      24
        // Here is mat.mean():      2.5
        // Here is mat.minCoeff():  1
        // Here is mat.maxCoeff():  4
        // Here is mat.trace():     5
        // Here is the matrix m:
        //  -0.444451   0.257742   0.904459
        //    0.10794  -0.270431    0.83239
        // -0.0452059  0.0268018   0.271423
        // Its minimum coefficient (-0.444451) is at position (0,0)
}

void ValidityOfoperations()
{
        LOG();
        // Eigen的输出很操蛋，但是它把输出中关键的信息大写了～
        // 如果你想体验一下Eigen的错误输出，则注释掉下面的内容

        // Matrix3f m;
        // Vector4f v;
        // v = m * v; // Compile-time error: YOU_MIXED_MATRICES_OF_DIFFERENT_SIZES

        // {
        //         MatrixXf m(3, 3);
        //         VectorXf v(4);
        //         v = m * v; // Run-time assertion failure here: "invalid matrix product"
        // }
}
} // namespace Section2_MatrixAndVectorArithmetic
} // namespace Chapter1_DenseMatrixAndArrary

#endif