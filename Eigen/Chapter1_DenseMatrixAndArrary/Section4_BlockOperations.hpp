#ifndef BLOCK_OPERATIONS_HPP
#define BLOCK_OPERATIONS_HPP
#include "HeaderFile.h"
namespace Chapter1_DenseMatrixAndArrary
{
namespace Section4_BlockOperations
{
//前言：
//块是矩阵或数组的某一部分。块表达式既可以用作右值，也可以用作左值。
// Block operation
// Block of size (p,q), starting at (i,j)

//Version constructing a  dynamic-size block expression
// 起始位置+行列数
// matrix.block(i,j,p,q);

//Version constructing a fixed-size block expression
// 模板参数为行列数，函数参数为起始位置
// matrix.block<p,q>(i,j);

//两种版本均可用于固定大小和动态大小的矩阵和数组。
//这两个表达式在语义上是等效的。
//唯一的区别是，如果块大小较小，则固定大小版本通常会为您提供更快的代码，但是需要在编译时知道此大小。

void UsingBlockOperations()
{
        LOG();
        Eigen::MatrixXf m(4, 4);
        m << 1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16;
        cout << "Block in the middle" << endl;
        cout << m.block<2, 2>(1, 1) << endl
             << endl;
        for (int i = 1; i <= 3; ++i)
        {
                cout << "Block of size " << i << "x" << i << endl;
                cout << m.block(0, 0, i, i) << endl
                     << endl;
        }

        // Output is:
        // Block in the middle
        //  6  7
        // 10 11

        // Block of size 1x1
        // 1

        // Block of size 2x2
        // 1 2
        // 5 6

        // Block of size 3x3
        //  1  2  3
        //  5  6  7
        //  9 10 11
}

// block也可以作为左值
void BlockAsLeftValue()
{
        LOG();
        Array22f m;
        m << 1, 2,
            3, 4;
        Array44f a = Array44f::Constant(0.6);
        cout << "Here is the array a:" << endl
             << a << endl
             << endl;
        a.block<2, 2>(1, 1) = m; //可作为左值
        cout << "Here is now a with m copied into its central 2x2 block:" << endl
             << a << endl
             << endl;
        a.block(0, 0, 2, 3) = a.block(2, 1, 2, 3);
        cout << "Here is now a with bottom-right 2x3 block copied into top-left 2x2 block:" << endl
             << a << endl
             << endl;

        // Output is:
        // ere is the array a:
        // 0.6 0.6 0.6 0.6
        // 0.6 0.6 0.6 0.6
        // 0.6 0.6 0.6 0.6
        // 0.6 0.6 0.6 0.6

        // Here is now a with m copied into its central 2x2 block:
        // 0.6 0.6 0.6 0.6
        // 0.6   1   2 0.6
        // 0.6   3   4 0.6
        // 0.6 0.6 0.6 0.6

        // Here is now a with bottom-right 2x3 block copied into top-left 2x2 block:
        //   3   4 0.6 0.6
        // 0.6 0.6 0.6 0.6
        // 0.6   3   4 0.6
        // 0.6 0.6 0.6 0.6
}
//单独的列和行是块的特殊情况。Eigen提供了可以轻松解决它们的方法：.col（）和.row（）。
void ColumnsAndRows()
{
        LOG();
        Eigen::MatrixXf m(3, 3);
        m << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
        cout << "Here is the matrix m:" << endl
             << m << endl;
        cout << "2nd Row: " << m.row(1) << endl;

        m.col(2) += 3 * m.col(0);
        cout << "After adding 3 times the first column into the third column, the matrix m is:\n";
        cout << m << endl;

        // Output is:
        // Here is the matrix m:
        // 1 2 3
        // 4 5 6
        // 7 8 9
        // 2nd Row: 4 5 6
        // After adding 3 times the first column into the third column, the matrix m is:
        //  1  2  6
        //  4  5 18
        //  7  8 30
}

void CornerRelatedOperations()
{
        LOG();
        //一系列矩阵的边角块操作
        // Block operation	Version constructing a dynamic-size block expression	Version constructing a fixed-size block expression
        // Top-left p by q block *	                                      matrix.topLeftCorner(p,q);                            matrix.topLeftCorner<p,q>();
        // Bottom-left p by q block *	                                 matrix.bottomLeftCorner(p,q);                    matrix.bottomLeftCorner<p,q>();
        // Top-right p by q block *	                                    matrix.topRightCorner(p,q);                         matrix.topRightCorner<p,q>();
        // Bottom-right p by q block *	                               matrix.bottomRightCorner(p,q);                 matrix.bottomRightCorner<p,q>();
        // Block containing the first q rows *	                  matrix.topRows(q);                                           matrix.topRows<q>();
        // Block containing the last q rows *	                  matrix.bottomRows(q);                                  matrix.bottomRows<q>();
        // Block containing the first p columns *	     matrix.leftCols(p);                                              matrix.leftCols<p>();
        // Block containing the last q columns *	     matrix.rightCols(q);                                           matrix.rightCols<q>();
        Eigen::Matrix4f m;
        m << 1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16;
        cout << "m.leftCols(2) =" << endl
             << m.leftCols(2) << endl
             << endl;
        cout << "m.bottomRows<2>() =" << endl
             << m.bottomRows<2>() << endl
             << endl;
        m.topLeftCorner(1, 3) = m.bottomRightCorner(3, 1).transpose();
        cout << "After assignment, m = " << endl
             << m << endl;
        // Output is:
        // m.leftCols(2) =
        //  1  2
        //  5  6
        //  9 10
        // 13 14

        // m.bottomRows<2>() =
        //  9 10 11 12
        // 13 14 15 16

        // After assignment, m =
        //  8 12 16  4
        //  5  6  7  8
        //  9 10 11 12
        // 13 14 15 16
}

void BlockOperationsForVectors()
{
        LOG();
        //同样，向量也有一系列类似于矩阵的边角块操作
        // Block operation	Version                                                       constructing adynamic-size block expression	                        Version constructing afixed-size block expression
        // Block containing the first n elements *	                                                    vector.head(n);                                                                   vector.head<n>();
        // Block containing the last n elements *	                                                    vector.tail(n);                                                                       vector.tail<n>();
        // Block containing n elements, starting at position i *                           vector.segment(i,n);                                                         vector.segment<n>(i);
        Eigen::ArrayXf v(6);
        v << 1, 2, 3, 4, 5, 6;
        cout << "v.head(3) =" << endl
             << v.head(3) << endl
             << endl;
        cout << "v.tail<3>() = " << endl
             << v.tail<3>() << endl
             << endl;
        v.segment(1, 4) *= 2;
        cout << "after 'v.segment(1,4) *= 2', v =" << endl
             << v << endl;

        // Output is:
        // v.head(3) =
        // 1
        // 2
        // 3

        // v.tail<3>() =
        // 4
        // 5
        // 6

        // after 'v.segment(1,4) *= 2', v =
        //  1
        //  4
        //  6
        //  8
        // 10
        //  6
}

} // namespace Section4_BlockOperations

} // namespace Chapter1_DenseMatrixAndArrary

#endif