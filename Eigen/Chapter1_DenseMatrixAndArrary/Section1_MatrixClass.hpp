#ifndef MATRIX_CLASS_HPP
#define MATRIX_CLASS_HPP
#include "HeaderFile.h"

namespace Chapter1_DenseMatrixAndArrary
{

//http://eigen.tuxfamily.org/dox/group__TutorialMatrixClass.html
namespace Section1_MatrixClass
{

// Eigen中的matrix和vector底层采用Matrix<>模板类表示，因为向量是特殊的矩阵，例如行向量是一行多列，列向量是一列多行
//  Matrix<>模板类定义：
// ``` Matrix<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>
//``` typedef Matrix<double, Dynamic, Dynamic> MatrixXd;
//``` typedef Matrix<int, Dynamic, 1> VectorXi;

//```Eigen中的MatrixXt基本上是动态内存分配和初始化分开

//```固定大小的向量提供了初始化操作
//               Vector2d a(5.0, 6.0);
//               Vector3d b(5.0, 6.0, 7.0);
//               Vector4d c(5.0, 6.0, 7.0, 8.0);

// 获取元素：
// 所有元素：m(index)的方式可以获取数据，但是和存储方式有关，
// eigen默认采用column-major storage order, but this can be changed to row-major, 注意，存储顺序与逗号初始化是无关系的
// []运算符只能获取**向量元素**，因为C++[]只支持一个参数；

void CoefficientAccessors()
{
        LOG();
        // MatrixXd type represents a matrix of arbitrary size (hence the X in MatrixXd), in which every entry is a double (hence the d in MatrixXd)
        // Declares a variable of type MatrixXd and specifies that it is a matrix with 2 rows and 2 columns (the entries are not initialized).
        // 定义矩阵大小，但未初始化,该方式在堆上分配内存
        MatrixXd m(2, 2);

        //The statement m(0,0) = 3 sets the entry in the top-left corner to 3. You need to use round parentheses to refer to entries in the matrix.
        //As usual in computer science, the index of the first index is 0, as opposed to the convention in mathematics that the first index is 1.
        // 矩阵元素赋值，index 从0开始
        m(0, 0) = 3;
        m(1, 0) = 2.5;
        m(0, 1) = -1;
        m(1, 1) = m(1, 0) + m(0, 1);
        std::cout << m << std::endl;
        // Output is:
        // Here is the matrix m:
        //   3  -1
        // 2.5 1.5
        // Here is the vector v:
        // 4
        // 3
}

void CommaInitialization()
{
        LOG();
        //矩阵和矢量系数可以使用所谓的逗号初始化语法方便地设置。现在，只需要知道以下示例即可：
        Matrix3f m;
        m << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
        std::cout << m;
}

void Resizing()
{
        LOG();
        //矩阵的当前大小可以通过rows()，cols()和size()获取。
        //这些方法分别返回行数，列数和系数数。调整动态大小矩阵的大小是通过resize()方法完成的。
        // 如果实际矩阵大小不变，则resize()方法为空操作。
        // 否则具有破坏性：系数的值可能会更改。如果你想调整大小()，它不改变系数，使用conservativeResize()

        MatrixXd m(2, 5);
        m.resize(4, 3);
        std::cout << "The matrix m is of size "
                  << m.rows() << "x" << m.cols() << std::endl;
        std::cout << "It has " << m.size() << " coefficients" << std::endl;
        VectorXd v(2);
        v.resize(5);
        std::cout << "The vector v is of size " << v.size() << std::endl;
        std::cout << "As a matrix, v is of size "
                  << v.rows() << "x" << v.cols() << std::endl;
        // Output is:
        // The matrix m is of size 4x3
        // It has 12 coefficients
        // The vector v is of size 5
        // As a matrix, v is of size 5x1

        {
                //为了实现API统一性，所有这些方法仍可用于固定大小的矩阵。当然，您实际上不能调整固定大小的矩阵的大小。尝试将固定大小更改为实际不同的值将触发断言失败。
                //但是以下代码是合法的：
                Matrix4d m;
                m.resize(4, 4); // no operation
                std::cout << "The matrix m is of size "
                          << m.rows() << "x" << m.cols() << std::endl;
        }
}

void MatrixAndVectorRunTime()
{
        LOG();
        // 固定大小的矩阵or向量在栈上分配内存，因为它在编译时期就可以确定大小
        // Matrix4f mymatrix  ≈  float mymatrix[16];
        // MatrixX表示运行时才确定矩阵的大小，因为它在堆上分配内存
        // MatrixXf mymatrix(rows,columns) ≈  float *mymatrix = new float[rows*columns];
        MatrixXd m = MatrixXd::Random(3, 3);          //  random values between -1 and 1
        m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50; // MatrixXd::Constant(3, 3, 1.2) represents a 3-by-3 matrix expression having all coefficients equal to 1.2
        cout << "m =" << endl
             << m << endl;
        VectorXd v(3); // 尚未初始化
        v << 1, 2, 3;  //  uses the so-called comma-initializer
        cout << "m * v =" << endl
             << m * v << endl;
}

void MatrixAndVectorCompileTime()
{
        LOG();
        // 编译时可确定矩阵尺寸，在栈上分配内存
        Matrix3d m = Matrix3d::Random(); //a fixed size
        m = (m + Matrix3d::Constant(1.2)) * 50;
        cout << "m =" << endl
             << m << endl;
        Vector3d v(1, 2, 3);

        cout << "m * v =" << endl
             << m * v << endl;
}

void AssignmentAndResizing()
{
        LOG();
        //operator= 将矩阵复制到另一个矩阵中的操作。Eigen自动调整左侧矩阵的大小，使其与右侧大小的矩阵大小匹配。例如：
        MatrixXf a(2, 2);
        std::cout << "a is of size " << a.rows() << "x" << a.cols() << std::endl;
        MatrixXf b(3, 3);
        a = b;
        std::cout << "a is now of size " << a.rows() << "x" << a.cols() << std::endl;
        
}

void FixedSizeAndDynamicSize()
{

        LOG();
        //固定尺寸与动态尺寸
        // 什么时候应该使用固定尺寸（例如Matrix4f），什么时候应该使用动态尺寸（例如MatrixXf）？
        //简单的答案是：在可能的地方使用固定尺寸来显示非常小的尺寸，在需要的地方使用动态尺寸来显示较大的尺寸。
        //对于小尺寸，尤其是对于小于（大约）16的尺寸，使用固定尺寸对性能有极大的好处，因为它使Eigen避免了动态内存分配并展开了循环。
        //在内部，固定大小的本征矩阵只是一个简单的数组，即
        // Matrix4f mymatrix;
        // 真的等于只是在做
        // float[16];
        // 因此这确实具有零运行时间成本。相比之下，动态大小矩阵的数组始终分配在堆上，因此

        // MatrixXf mymatrix（行，列）;
        // 等于做
        // float * mymatrix = new [行*列];
        // 除此之外，MatrixXf对象还将其行数和列数存储为成员变量。
        // 当然，使用固定大小的限制是，只有当您在编译时知道大小时，才有可能这样做。
        //同样，对于足够大的尺寸（例如，对于大于（大约）32的尺寸），使用固定尺寸的性能优势变得可以忽略不计。
        //更糟糕的是，尝试使用函数内部的固定大小创建非常大的矩阵可能会导致堆栈溢出，因为Eigen会尝试自动将数组分配为局部变量，而这通常是在堆栈上完成的。
        //最后，视情况而定，当使用动态尺寸时，Eigen还可尝试进行矢量化（使用SIMD指令），请参见参考矢量化。
}

void OptionalTemplateParameters()
{
        LOG();
        // 可选模板参数
        // 我们在页面开始时提到Matrix类采用六个模板参数，但到目前为止，我们仅讨论了前三个。其余三个参数是可选的。这是模板参数的完整列表：

        //       Matrix<typename Scalar,
        //        int RowsAtCompileTime,
        //        int ColsAtCompileTime,
        //        int Options = 0,
        //        int MaxRowsAtCompileTime = RowsAtCompileTime,
        //        int MaxColsAtCompileTime = ColsAtCompileTime>

        // Options是位字段。在这里，我们只讨论一点：RowMajor。它指定这种类型的矩阵使用行优先存储顺序。默认情况下，存储顺序为“按列的顺序存储”。
        //请参阅有关存储顺序的页面。例如，此类型表示行优先存储的3x3矩阵：
        // Matrix<float，3、3，RowMajor>
        // MaxRowsAtCompileTime并且MaxColsAtCompileTime在您希望指定时很有用，即使在编译时不知道矩阵的确切大小，在编译时也知道固定的上限。
        //您可能要这样做的最大原因是避免动态内存分配。例如，以下矩阵类型使用12个浮点数的普通数组，而不分配动态内存：
        // Matrix<float，Dynamic，Dynamic，0、3、4>
}

void ConvenienceTypedefs()
{
        LOG();
        // Eigen定义了以下Matrix typedef：

        // MatrixNt for Matrix<type, N, N>. For example, MatrixXi for Matrix<int, Dynamic, Dynamic>.
        // VectorNt for Matrix<type, N, 1>. For example, Vector2f for Matrix<float, 2, 1>.
        // RowVectorNt for Matrix<type, 1, N>. For example, RowVector3d for Matrix<double, 1, 3>.
        // Where:
        // N可以是任何一个2，3，4，或X（意思Dynamic）。
        // t可以是i（表示int），f（表示float），d（表示double），cf（表示complex <float>）或cd（表示complex <double>）的任何一种。
        //仅针对这五个类型定义typedef的事实并不意味着它们是唯一受支持的标量类型。例如，支持所有标准整数类型，请参阅标量类型。
}

} // namespace Section1_MatrixClass

} // namespace Chapter1_DenseMatrixAndArrary

#endif