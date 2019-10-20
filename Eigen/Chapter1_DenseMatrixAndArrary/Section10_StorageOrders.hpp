#ifndef STORAGE_ORDERS_HPP
#define STORAGE_ORDERS_HPP
#include "HeaderFile.h"

namespace Chapter1_DenseMatrixAndArrary
{
//矩阵和二维数组有两种不同的存储顺序：列优先和行优先。本页说明了这些存储顺序以及如何指定应使用的存储顺序。
//矩阵的条目形成一个二维网格。但是，当矩阵存储在存储器中时，必须以某种方式线性排列条目。有两种主要方法可以做到这一点，按行和按列。
//我们说矩阵是**按行优先存储**。首先存储整个第一行，然后存储整个第二行，依此类推。
//另一方面，如果矩阵是逐列存储的，则以主列顺序存储，从整个第一列开始，然后是整个第二列，依此类推

//可以通过Options为Matrix或Array指定模板参数来设置矩阵或二维数组的存储顺序。
//由于Matrix类解释，Matrix类模板有六个模板参数，
// 其中三个是强制性的（Scalar，RowsAtCompileTime和ColsAtCompileTime）
// 三个是可选的（Options，MaxRowsAtCompileTime和MaxColsAtCompileTime）。
//如果Options参数设置为RowMajor，则矩阵或数组以行优先顺序存储；
//如果将其设置为ColMajor，则以列优先顺序存储。
//如果未指定存储顺序，则Eigen默认将条目存储在column-major中。
//如果方便的typedef（Matrix3f，ArrayXXd等）也是默认按列存储。

//可以将使用一种存储顺序的矩阵和数组分配给使用另一种存储顺序的矩阵和数组，如一个按行存储的矩阵使用按列存储矩阵初始化。
//Eigen将自动对元素重新排序。更一般而言，按行存储矩阵和按列存储矩阵可以根据需要在表达式中混合使用。

//选择哪个存储顺序？
//那么，您应该在程序中使用哪个存储顺序？这个问题没有简单的答案。这取决于您的应用程序。请记住以下几点：

//您的用户可能希望您使用特定的存储顺序。或者，您可以使用Eigen以外的其他库，并且这些其他库可能需要一定的存储顺序。
//在这些情况下，在整个程序中使用此存储顺序可能是最简单，最快的。
//当矩阵以行优先顺序存储时，逐行遍历矩阵的算法会更快，因为数据位置更好。同样，对于主要列矩阵，逐列遍历更快。可能需要尝试一下以找出对您的特定应用程序更快的方法。
//Eigen中的默认值是column-major。自然，对Eigen库的大多数开发和测试都是使用列主矩阵完成的。
//这意味着，即使我们旨在透明地支持列主存储和行主存储顺序，Eigen库也最好与列主存储矩阵配合使用。
namespace Section10_StorageOrders
{

void testColumnAndRowMajorStorage()
{
        LOG();
        // PlainObjectBase::data()  返回第一个元素的内存位置，和C++的数组名作用一样

        Matrix<int, 3, 4, ColMajor> Acolmajor;
        Acolmajor << 8, 2, 2, 9,
            9, 1, 4, 4,
            3, 5, 4, 5;
        cout << "The matrix A:" << endl;
        cout << Acolmajor << endl
             << endl;
        cout << "In memory (column-major):" << endl;
        for (int i = 0; i < Acolmajor.size(); i++)
                cout << *(Acolmajor.data() + i) << "  ";
        cout << endl
             << endl;
        Matrix<int, 3, 4, RowMajor> Arowmajor = Acolmajor;
        cout << "In memory (row-major):" << endl;
        for (int i = 0; i < Arowmajor.size(); i++)
                cout << *(Arowmajor.data() + i) << "  ";
        cout << endl;

        // Output is
        // The matrix A:
        // 8 2 2 9
        // 9 1 4 4
        // 3 5 4 5

        // In memory (column-major):
        // 8  9  3  2  1  5  2  4  4  9  4  5

        // In memory (row-major):
        // 8  2  2  9  9  1  4  4  3  5  4  5
}

} // namespace Section10_StorageOrders
} // namespace Chapter1_DenseMatrixAndArrary

#endif