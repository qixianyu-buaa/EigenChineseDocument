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

void Block()
{
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
}

// block也可以作为左值
void BlockAsLeftValue()
{
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
}
//单独的列和行是块的特殊情况。Eigen提供了可以轻松解决它们的方法：.col（）和.row（）。
void ColumnsAndRows()
{
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
}

void CornerRelatedOperations()
{
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
}

void BlockOperationsForVectors()
{
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
}

} // namespace Part4_BlockOperations

} // namespace Chapter1_DenseMatrixAndArrary

#endif