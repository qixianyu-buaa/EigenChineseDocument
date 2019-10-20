#ifndef MAP_CLASS_HPP
#define MAP_CLASS_HPP
#include "HeaderFile.h"
//http://eigen.tuxfamily.org/dox/group__TutorialMapClass.html
//本页说明了如何使用“原始” C / C ++数组。这在各种情况下都可能有用，特别是在将其他库中的向量和矩阵“导入”Eigen。
//有时您可能要在Eigen中使用预定义的数字数组(C++)作为矢量或矩阵(Eigen)。
//一种选择是复制数据，但最常见的情况是您可能希望将此内存。幸运的是，使用Map类非常容易。
// Map 类 实现C++中的数组内存和Eigen对象的交互
// Map< Matrix<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>  >
// 请注意，在这种默认情况下，Map仅需要一个模板参数。
// 要构造Map变量，您还需要其他两条信息：指向定义系数数组的内存区域的指针，以及所需的矩阵或矢量形状。(注意区分模板参数和函数形参)
// 例如，要定义一个float在编译时确定大小的矩阵，您可以执行以下操作：
// Map <MatrixXf> mf（pf，rows，columns）;
// 其中pf是一个float *指向的存储器阵列。固定大小的整数只读向量可能会声明为
// Map <const Vector4i> mi（pi）;
// 其中pi是int *。在这种情况下，不必将大小传递给构造函数，因为它已经由Matrix / Array类型指定。

// 请注意，Map没有默认的构造函数。您必须传递一个指针来初始化对象。但是，您可以解决此要求（请参阅更改Map数组）。

// Map足够灵活，可以容纳各种不同的数据表示形式。还有其他两个（可选）模板参数：
// Map<typename MatrixType,    int MapOptions,     typename StrideType>
//MapOptions指定指针是Aligned还是Unaligned。默认值为Unaligned。
//StrideType允许您使用Stride类为内存阵列指定自定义布局。一个示例是指定数据数组以行优先格式进行组织MapConstruct()

namespace Chapter1_DenseMatrixAndArrary
{

namespace Section7_MapClass
{

void MapConstruct()
{
        LOG();
        int array[8];
        for (int i = 0; i < 8; ++i)
                array[i] = i;
        cout << "Column-major:\n"
             << Map<Matrix<int, 2, 4>>(array) << endl;
        cout << "Row-major:\n"
             << Map<Matrix<int, 2, 4, RowMajor>>(array) << endl;
        cout << "Row-major using stride:\n"
             << Map<Matrix<int, 2, 4>, Unaligned, Stride<1, 4>>(array) << endl;
        //Output is:
        //Column-major:
        // 0 2 4 6
        // 1 3 5 7
        // Row-major:
        // 0 1 2 3
        // 4 5 6 7
        // Row-major using stride:
        // 0 1 2 3
        // 4 5 6 7

        //However, Stride is even more flexible than this; for details, see the documentation for the Map and Stride classes.
}

void UsingMapVariables()
{
        LOG();
        typedef Matrix<float, 1, Dynamic> MatrixType;
        typedef Map<MatrixType> MapType;
        typedef Map<const MatrixType> MapTypeConst; // a read-only map
        const int n_dims = 5;

        MatrixType m1(n_dims), m2(n_dims);
        m1.setRandom();
        m2.setRandom();
        float *p = &m2(0);                     // get the address storing the data for m2
        MapType m2map(p, m2.size());           // m2map shares data with m2
        MapTypeConst m2mapconst(p, m2.size()); // a read-only accessor for m2
        cout << "m1: " << m1 << endl;
        cout << "m2: " << m2 << endl;
        cout << "Squared euclidean distance: " << (m1 - m2).squaredNorm() << endl;
        cout << "Squared euclidean distance, using map: " << (m1 - m2map).squaredNorm() << endl;
        m2map(3) = 7; // this will change m2, since they share the same array
        cout << "Updated m2: " << m2 << endl;
        cout << "m2 coefficient 2, constant accessor: " << m2mapconst(2) << endl;
        /* m2mapconst(2) = 5; */ // this yields a compile-time error

        //Output is:
        // m1:   0.68 -0.211  0.566  0.597  0.823
        // m2: -0.605  -0.33  0.536 -0.444  0.108
        // Squared euclidean distance: 3.26
        // Squared euclidean distance, using map: 3.26
        // Updated m2: -0.605  -0.33  0.536      7  0.108
        // m2 coefficient 2, constant accessor: 0.536
}

void ChangingTheMappedArray()
{
        LOG();
        //可以使用C ++“ placement new"(位置new，在程序员给定的内存放置元素) 语法更改已声明的Map对象的数组
        ////尽管有出现，但它不会调用内存分配器，因为语法指定了存储结果的位置。(具体参考《C++primer》中的内容)
        // 简单的说，位置new只是在指定位置写入内容，并不会像new一样，先在堆上分配内存，然后再依次初始化对象，
        // 这也是为什么叫位置new，因为它会按照我们指定的位置构造对象
        int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Map<RowVectorXi> v(data, 4);
        cout << "The mapped vector v is: " << v << "\n";
        new (&v) Map<RowVectorXi>(data + 4, 5);
        cout << "Now v is: " << v << "\n";
        //The mapped vector v is: 1 2 3 4
        //Now v is: 5 6 7 8 9

        // TODO : 教程中没有指定n_matrices
        // Map<Matrix3f> A(NULL); // don't try to use this matrix yet!
        // VectorXf b(n_matrices);
        // for (int i = 0; i < n_matrices; i++)
        // {
        //         new (&A) Map<Matrix3f>(get_matrix_pointer(i));
        //         b(i) = A.trace();
        // }
}
} // namespace Section7_MapClass

} // namespace Chapter1_DenseMatrixAndArrary

#endif