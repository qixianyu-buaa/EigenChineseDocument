#ifndef SPARSE_MATRIX_MANIPULATIONS_HPP
#define SPARSE_MATRIX_MANIPULATIONS_HPP
namespace Chapter3_SparseLinearAlgebra
{
namespace Section1_SparseMatrixManipulations
{
// 稀疏矩阵格式
// 在许多应用中（例如，有限元方法），通常处理非常大的矩阵，其中只有几个系数与零不同。
// 在这种情况下，通过使用仅存储非零系数的专用表示，可以减少内存消耗并提高性能。这样的矩阵称为稀疏矩阵。

// SparseMatrix类是Eigen的稀疏模块的主要稀疏矩阵表示。
//它提供了高性能和低内存使用率。它实现了广泛使用的压缩列（或行）存储方案的更通用的变体。
//它由四个紧凑数组组成：

// Values: 存储非零的系数值。
// InnerIndices: 存储非零的行（或列）索引。
// OuterStarts: 为每列（分别为行）存储前两个数组中第一个非零的索引。
// InnerNNZs:存储每列（分别为行）的非零数。该词inner指的是内部 向量，
//该向量是列主矩阵的列，或行主矩阵的行。这个词outer是指另一个方向。
// 在一个示例中可以更好地解释此存储方案。以下矩阵

// 0	3	0	0	0
// 22	0	0	0	17
// 7	5	0	1	0
// 0	0	0	0	0
// 0	0	14	0	8
// 及其可能的**稀疏列主**表示形式之一：

// Values:	22	7	_	3	5	14	_	_	1	_	17	8

//内部索引：  1 第一行  2第二行  _ 0 第零行 2 第2 行  4  第四行 ....
// InnerIndices:	1	2	_	0	2	4	_	_	2	_	1	4

// 在前两个数组中的每一列的非零元素索引
// OuterStarts:	0	3	5	8	10	12

// 5个列中的非零元素个数
// InnerNNZs:	2	2	1	1	2	

// 感觉上面这4个数组不能恢复矩阵的形式啊！！！

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
//$ \ Delta u = 0 $使用有限差分方案和Dirichlet边界条件在规则2D网格上求解拉普拉斯方程。这样的问题可以在数学上表示为以下形式的线性问题$ Ax = b $，其中$ x $是的矢量m未知数（在我们的情况下，所述像素的值），$ b $是从边界条件导致的右手侧向量，
//并且$ $是$ m \次m $仅含有基质拉普拉斯算子离散化产生的非零元素很少。



} // namespace Section1_SparseMatrixManipulations
} // namespace Chapter3_SparseLinearAlgebra
#endif