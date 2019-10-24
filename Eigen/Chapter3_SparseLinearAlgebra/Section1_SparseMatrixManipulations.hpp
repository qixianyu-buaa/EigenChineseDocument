#ifndef SPARSE_MATRIX_MANIPULATIONS_HPP
#define SPARSE_MATRIX_MANIPULATIONS_HPP
#include "HeaderFile.h"
#include "HelpFunctions.hpp"
namespace Chapter3_SparseLinearAlgebra
{
namespace Section1_SparseMatrixManipulations
{
// 稀疏矩阵格式
// 在许多应用中，矩阵其只有少量非零系数，这样的矩阵称为稀疏矩阵(Sparse Matrix)。
// 在这种情况下，采用稀疏矩阵的存储方式，即仅存储非零系数，可以减少内存消耗并提高性能。

// 在Eigen中，SparseMatrix<>模板类是用于表示稀疏矩阵，注意稠密的用的是Matrix<>
//SparseMatrix<>提供了高性能和低内存使用率。
//它实现了广泛使用的压缩列（或行）存储方案的更通用的变体。

//它由四个紧凑数组组成：
// 1. Values: 存储非零的系数值。注意，压缩列存储按照一列一列的顺序存储非零元素，同样，压缩行按照一行一行的顺序存储元素；
// 2. InnerIndices: 存储非零的行（或列）下标。简单的说，我们可以先按照列或者行的顺序存储values，然后对于values中的每一个元素，确定其所在的行or列的下标；
// 3. OuterStarts: 为每列（分别为行）存储前两个数组中第一个非零的索引。注意，这个数组存储的Values和InnerIndices中的位置；
// 4. InnerNNZs:存储每列（分别为行）的非零元素个数。
// 注意：术语inner指的是内部向量，该向量是列主矩阵的列，或行主矩阵的行。
// 术语outer是指另一个方向，即行or列；

// 在一个示例中可以更好地解释此存储方案。以下矩阵
// 0	3	0	0	0
// 22	0	0	0	17
// 7	5	0	1	0
// 0	0	0	0	0
// 0	0	14	0	8
// 及其可能的稀疏**列主**表示形式之一：

// Values:	22	7	_	3	5	14	_	_	1	_	17	8                注释：按列主方式，一列一列的存储非零元素， _ 是为了插入元素用的
 
// InnerIndices:	1	2	_	0	2	4	_	_	2	_	1	4      注释：有了Values后，我们可以看Values元素所在的每一行，例如，22在第1行，7在第2行，以此类推


// OuterStarts:	0	3	5	8	10	12      注释：OutStarts表示的每一列中的起始非零元素在Values or InnerIndices中的索引，
// 例如,第一列非零元素22在Values中的第0索引，第二列中的3在Values中的第3索引，第三列中的14在Values中的第5索引...
 // 令我困惑的是，OutStarts多了一个元素，比如上述方阵有5列，那么应该只有5个元素，但是它有6个元素，难道是存储了最后一个元素？


// InnerNNZs:	2	2	1	1	2       注释：5个列中的非零元素个数


// TODO:
// 当前，确保始终通过增加内部索引来对给定内部向量的元素进行排序。
//该"_"指示可用空间来快速插入新的元素。假设不需要重新分配，
//则在O（nnz_j）中插入随机元素，其中nnz_j是相应内部向量的非零数。
//另一方面，在给定的内部向量中插入具有增加的内部索引的元素会更加有效，
//因为这仅需要增加InnerNNZs作为O（1）运算的各个元素。

// 没有可用空间的情况是一种特殊情况，称为压缩模式。
//它对应于广泛使用的压缩列（或行）存储方案（CCS或CRS）。
//通过调用SparseMatrix :: makeCompressed（）函数，可以将任何SparseMatrix转换为这种形式。
//在这种情况下，因为我们等于：[j] = [j + 1]- [j] ，所以可以指出该数组是多余的。
//因此，实际上，对SparseMatrix :: makeCompressed（）的调用将释放此缓冲区。
//InnerNNZsOuterStartsInnerNNZsOuterStartsOuterStarts
// 值得注意的是，我们对外部库的大多数包装都需要压缩矩阵作为输入。

//Eigen运算的结果始终会生成压缩的稀疏矩阵。
//另一方面，在SparseMatrix中插入新元素会将其稍后转换为非压缩模式。
// 这是以前以压缩模式表示的矩阵：

// Values:	22	7	3	5	14	1	17	8
// InnerIndices:	1	2	0	2	4	2	1	4
// OuterStarts:	        0	2	4	5	6	8
// 一个稀疏向量是一个的一种特殊情况稀疏矩阵，其中只有Values和InnerIndices数组存储。
//SparseVector没有压缩/未压缩模式的概念。

// 第一个例子
// 在描述每个类之前，让我们从以下典型示例开始：
//$ \ Delta u = 0 $使用有限差分方案和Dirichlet边界条件在规则2D网格上求解拉普拉斯方程。
//这样的问题可以在数学上表示为Ax = b形式的线性问题，其中x是一个m维向量，在本例中，它表示像素值, b是从边界条件中获得，
//并且A是一个mXm的方阵，它是从离散化的拉普拉斯算子中获得的稀疏矩阵，即，只含有少数的非0元素

void FirstExample()
{
        LOG();

        int n = 300;   // size of the image
        int m = n * n; // number of unknows (=number of pixels)
        // Assembly:
        std::vector<T> coefficients;      // list of non-zeros coefficients,在HelpFunctions.hpp中的```typedef Eigen::Triplet<double> T;```
        Eigen::VectorXd b(m);             // the right hand side-vector resulting from the constraints
        buildProblem(coefficients, b, n); //在HelpFunctions.hpp中的```void buildProblem(std::vector<T> &coefficients, Eigen::VectorXd &b, int n);```
        SpMat A(m, m);
        A.setFromTriplets(coefficients.begin(), coefficients.end());
        // Solving:
        Eigen::SimplicialCholesky<SpMat> chol(A); // performs a Cholesky factorization of A,即首先执行稀疏乔里斯基分解
        Eigen::VectorXd x = chol.solve(b);        // use the factorization to solve for the given right hand side，然后求解Ax=b

        // Export the result to a file:
        saveAsBitmap(x, n, "result.bmp");
}

void TheSparseMatrixClass()
{
        LOG();

        //  稀疏矩阵和矢量是一模板类，具有三种模板参数：
        //   1. Scaler（例如，double）,
        //   2. 存储顺序（例如，ColMajor或RowMajor，默认是ColMajor)
        //   3. 内索引类型（默认为int）

        // 类似于Matrix对象，构造函数参数为对象的大小，例如：
        SparseMatrix<std::complex<float>> mat_c(1000, 2000); // declares a 1000x2000 column-major compressed sparse matrix of complex<float>
        SparseMatrix<double, RowMajor> mat(1000, 2000);      // declares a 1000x2000 row-major compressed sparse matrix of double
        SparseVector<std::complex<float>> vec_c(1000);       // declares a column sparse vector of complex<float> of size 1000
        SparseVector<double, RowMajor> vec(1000);            // declares a row sparse vector of double of size 1000

        // 维数可以使用下面的方法获得：
        // Standard    dimensions，标准的维度
        // mat.rows()
        // mat.cols()
        // vec.size()

        // Sizes along the  inner/outer dimensions，内部和外部维度的大小
        // mat.innerSize()
        // mat.outerSize()

        // Number of non zero coefficients，非零系数的个数
        // mat.nonZeros()
        // vec.nonZeros()

        //  迭代非零系数:
        //随机访问的稀疏对象的元素可以通过来完成coeffRef(i,j)功能。
        //但是，此功能涉及相当昂贵的二进制搜索。在大多数情况下，一个人只想遍历非零元素。
        //这是通过在外部尺寸上进行标准循环，然后通过InnerIterator对当前内部向量的非零值进行迭代来实现的。
        //因此，必须以与存储顺序相同的顺序访问非零条目。这是一个例子：

        {
                SparseMatrix<double> mat(rows, cols);
                for (int k = 0; k < mat.outerSize(); ++k)
                {
                        for (SparseMatrix<double>::InnerIterator it(mat, k); it; ++it)
                        {
                                it.value();
                                it.row();   // row index
                                it.col();   // col index (here it is equal to k)
                                it.index(); // inner index, here it is equal to it.row()
                        }
                }
        }
        //对于可写表达式，可以使用valueRef（）函数修改参考值。如果稀疏矩阵或向量的类型取决于模板参数，则typename需要关键字来指示InnerIterator表示类型；
}

void FillingASparseMatrix()
{
        //由于SparseMatrix的特殊存储方案，因此在添加新的非零条目时必须格外小心。例如，将单个纯随机插入SparseMatrix的成本为O(nnz)，其中nnz是非零系数的当前数量。

        // 因此，在确保良好性能的同时创建稀疏矩阵的最简单方法是:
        // 首先构建所谓的三元组列表，然后将其转换为SparseMatrix。
        // 这是一个典型的用法示例：

        // typedef Eigen::Triplet<double> T;
        // std::vector<T> tripletList;
        // tripletList.reserve(estimation_of_entries);
        // for (...)
        // {
        //         // ...
        //         tripletList.push_back(T(i, j, v_ij));
        // }
        // SparseMatrixType mat(rows, cols);
        // mat.setFromTriplets(tripletList.begin(), tripletList.end());
        // mat is ready to go!
}

} // namespace Section1_SparseMatrixManipulations
} // namespace Chapter3_SparseLinearAlgebra
#endif