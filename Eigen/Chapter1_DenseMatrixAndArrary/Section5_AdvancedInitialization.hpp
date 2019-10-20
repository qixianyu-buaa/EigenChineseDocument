#ifndef ADVANCED_INITIALIZATION_HPP
#define ADVANCED_INITIALIZATION_HPP
#include "HeaderFile.h"
namespace Chapter1_DenseMatrixAndArrary
{
// 本页讨论了几种初始化矩阵的高级方法。
// 它提供了有关之前介绍的逗号初始化程序的更多详细信息。
// 它还说明了如何获得特殊矩阵，例如单位矩阵和零矩阵。

namespace Section5_AdvancedInitialization
{

void CommaInitializer()
{
        LOG();
        // Eigen提供了一种逗号初始化器语法，该语法使用户可以轻松设置矩阵，向量或数组的所有系数
        // 简单地列出系数，开始在左上角，并从左至右，从顶部向底部移动。
        // 需要预先指定对象的大小。
        // 如果列出的系数太少或太多，就会报错。

        Matrix3f mat;
        mat << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;

        std::cout << mat << endl;

        //此外，初始化列表的元素本身可以是向量或矩阵。
        //通常的用途是将向量或矩阵连接在一起。
        //例如，这是将两个行向量连接在一起的方法。
        //  注意：～～～～～
        //请记住，必须先设置大小，然后才能使用逗号初始化程序
        RowVectorXd vec1(3);
        vec1 << 1, 2, 3;
        std::cout << "vec1 = " << vec1 << std::endl;
        RowVectorXd vec2(4);
        vec2 << 1, 4, 9, 16;
        std::cout << "vec2 = " << vec2 << std::endl;
        RowVectorXd joined(7);
        joined << vec1, vec2;
        std::cout << "joined = " << joined << std::endl;

        // 类似分块矩阵的初始化方式
        MatrixXf matA(2, 2);
        matA << 1, 2, 3, 4;
        MatrixXf matB(4, 4);
        matB << matA, matA / 10, matA / 10, matA;
        std::cout << matB << std::endl;

        //  对矩阵的某一块赋值
        Matrix3f m;
        m.row(0) << 1, 2, 3;
        m.block(1, 0, 2, 2) << 4, 5, 7, 8;
        m.col(2).tail(2) << 6, 9;
        std::cout << m;
}

void SpecialMatricesAndArrays()
{
        LOG();
        // 模板类Matrix<>和Array<>有静态方法，可以帮助初始化；
        //有三种变体:
        //第一个变体不带参数，只能用于固定大小的对象。如果要将动态尺寸对象初始化为零，则需要指定尺寸。
        //第二个变体需要一个参数，并且可以用于一维动态尺寸对象，
        //第三个变体需要两个参数，并且可以用于二维对象。

        std::cout << "A fixed-size array:\n";
        Array33f a1 = Array33f::Zero();
        std::cout << a1 << "\n\n";
        std::cout << "A one-dimensional dynamic-size array:\n";
        ArrayXf a2 = ArrayXf::Zero(3);
        std::cout << a2 << "\n\n";
        std::cout << "A two-dimensional dynamic-size array:\n";
        ArrayXXf a3 = ArrayXXf::Zero(3, 4);
        std::cout << a3 << "\n";

        //同样，静态方法Constant(value)会将所有系数设置为value。
        // 如果需要指定对象的大小，则附加参数放在value参数之前，如
        // MatrixXd::Constant(rows, cols, value)。

        //Random()用随机系数填充矩阵或数组。

        //Identity()获得单位矩阵, 此方法仅适用于Matrix，不适用于Array，因为“单位矩阵”是线性代数概念。

        //该方法LinSpaced（尺寸，低，高）是仅可用于载体和一维数组; 它产生一个指定大小的向量，其系数在low和之间平均间隔high。
        //方法LinSpaced()以下示例说明了该示例，该示例打印一张表格，其中包含以度为单位的角度，以弧度为单位的相应角度以及它们的正弦和余弦值。
        ArrayXXf table(10, 4);
        table.col(0) = ArrayXf::LinSpaced(10, 0, 90);
        table.col(1) = M_PI / 180 * table.col(0);
        table.col(2) = table.col(1).sin();
        table.col(3) = table.col(1).cos();
        std::cout << "  Degrees   Radians      Sine    Cosine\n";
        std::cout << table << std::endl;

        //Eigen定义了诸如setZero()，MatrixBase :: setIdentity（）和DenseBase :: setLinSpaced()之类的实用程序函数来方便地执行此操作。
        //即，可以采用对象的成员函数设置初始值。

        //下面的示例对比了三种构造矩阵的J =[O  I ; I O ] 方法
        // 使用静态方法和operator=
        const int size = 6;
        MatrixXd mat1(size, size);
        mat1.topLeftCorner(size / 2, size / 2) = MatrixXd::Zero(size / 2, size / 2);
        mat1.topRightCorner(size / 2, size / 2) = MatrixXd::Identity(size / 2, size / 2);
        mat1.bottomLeftCorner(size / 2, size / 2) = MatrixXd::Identity(size / 2, size / 2);
        mat1.bottomRightCorner(size / 2, size / 2) = MatrixXd::Zero(size / 2, size / 2);
        std::cout << mat1 << std::endl
                  << std::endl;
        //使用.setXxx()方法
        MatrixXd mat2(size, size);
        mat2.topLeftCorner(size / 2, size / 2).setZero();
        mat2.topRightCorner(size / 2, size / 2).setIdentity();
        mat2.bottomLeftCorner(size / 2, size / 2).setIdentity();
        mat2.bottomRightCorner(size / 2, size / 2).setZero();
        std::cout << mat2 << std::endl
                  << std::endl;
        MatrixXd mat3(size, size);
        
        //使用静态方法和逗号初始化
        mat3 << MatrixXd::Zero(size / 2, size / 2), MatrixXd::Identity(size / 2, size / 2),
            MatrixXd::Identity(size / 2, size / 2), MatrixXd::Zero(size / 2, size / 2);
        std::cout << mat3 << std::endl;
}

void UsageAsTemporaryObjects()
{
        LOG();
        //如上所示，可以在声明时或在赋值运算符的右侧使用静态方法Zero()和Constant()来初始化变量。
        //您可以将这些方法视为返回矩阵或数组。
        //实际上，它们返回所谓的**表达式对象**，这些表达式对象在需要时求值到矩阵或数组，因此该语法不会产生任何开销。
        //这些表达式也可以用作临时对象。

        MatrixXd m = MatrixXd::Random(3, 3);
        m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;
        cout << "m =" << endl
             << m << endl;
        VectorXd v(3);
        v << 1, 2, 3;
        cout << "m * v =" << endl
             << m * v << endl;

        // The comma-initializer, too, can also be used to construct temporary objects.
        //The following example constructs a random matrix of size 2-by-3,
        // and then multiplies this matrix on the left with [0 1; 1 0]
        MatrixXf mat = MatrixXf::Random(2, 3);
        std::cout << mat << std::endl
                  << std::endl;
        //
        // The finished() method is necessary here to get the actual matrix object
        //  once the comma initialization of our temporary submatrix is done.
        //  finished 类似于endl，让它立即生成
        mat = (MatrixXf(2, 2) << 0, 1, 1, 0).finished() * mat;
        std::cout << mat << std::endl;
}

} // namespace Section5_AdvancedInitialization
} // namespace Chapter1_DenseMatrixAndArrary
#endif