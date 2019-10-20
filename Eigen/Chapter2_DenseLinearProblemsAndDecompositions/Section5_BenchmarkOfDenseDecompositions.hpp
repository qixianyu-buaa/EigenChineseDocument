#ifndef BENCHMARK_OF_DENSE_DECOMPOSITIONS_HPP
#define BENCHMARK_OF_DENSE_DECOMPOSITIONS_HPP
#include "HeaderFile.h"
namespace Chapter2_DenseLinearProblemsAndDecompositions
{
//complete pivoting和partial pivoting
// （1） complete pivoting（即full pivoting），就是在矩阵分解或高斯消元的过程中，主元是在未进行变换的所有行和列之间进行选择。也就是需要同时进行行交换和列交换。
// （2） partial pivoting就是只在当前进行变换的列中选择主元，只需要进行行交换
namespace Section5_BenchmarkOfDenseDecompositions
{

// 本页介绍了Eigen针对各种方阵和过约束问题提供的稠密矩阵分解的速度比较。

// 有关线性求解器和分解的特征和数值鲁棒性的更一般的概述，请查看此表。http://eigen.tuxfamily.org/dox/group__TopicLinearAlgebraDecompositions.html

// 该基准测试已在配备Intel Core i7 @ 2,6 GHz的笔记本电脑上运行，
//并使用启用了AVX和FMA指令集但没有多线程的clang进行编译。它使用单 精度 浮点数。对于双精度，您可以通过将时序乘以2来获得良好的估计。

// 方矩阵是对称的，对于过度约束的矩阵，报告的时间包括$ A ^ TA $基于Cholesky和LU为前四个求解器计算对称协方差矩阵的成本，如*符号所示（表的右上角部分） ）。
//时间以毫秒为单位，并且因数是相对于LLT分解而言的，这是最快的，但也是最不通用且最不可靠的。

// 求解器/大小	8x8	100x100	1000x1000	4000x4000	10000x8	10000x100	10000x1000	10000x4000
// LLT	0.05	0.42	5.83	374.55	6.79 *	30.15 *	236.34 *	3847.17 *
// LDLT	0.07（x1.3）	0.65（x1.5）	26.86（x4.6）	2361.18（x6.3）	6.81（x1）*	31.91（x1.1）*	252.61（x1.1）*	5807.66（x1.5）*
// PartialPivLU	0.08（x1.5）	0.69（x1.6）	15.63（x2.7）	709.32（x1.9）	6.81（x1）*	31.32（x1）*	241.68（x1）*	4270.48（x1.1）*
// FullPivLU	0.1（x1.9）	4.48（x10.6）	281.33（x48.2）	--	6.83（x1）*	32.67（x1.1）*	498.25（x2.1）*	--
// HouseholderQR	0.19（x3.5）	2.18（x5.2）	23.42（x4）	1337.52（x3.6）	34.26（x5）	129.01（x4.3）	377.37（x1.6）	4839.1（x1.3）
// ColPivHouseholderQR	0.23（x4.3）	2.23（x5.3）	103.34（x17.7）	9987.16（x26.7）	36.05（x5.3）	163.18（x5.4）	2354.08（x10）	37860.5（x9.8）
// CompleteOrthogonalDecomposition	0.23（x4.3）	2.22（x5.2）	99.44（x17.1）	10555.3（x28.2）	35.75（x5.3）	169.39（x5.6）	2150.56（x9.1）	36981.8（x9.6）
// FullPivHouseholderQR	0.23（x4.3）	4.64（x11）	289.1（x49.6）	--	69.38（x10.2）	446.73（x14.8）	4852.12（x20.5）	--
// JacobiSVD	1.01（x18.6）	71.43（x168.4）	--	--	113.81（x16.7）	1179.66（x39.1）	--	--
// BDCSVD	1.07（x19.7）	21.83（x51.5）	331.77（x56.9）	18587.9（x49.6）	110.53（x16.3）	397.67（x13.2）	2975（x12.6）	48593.2（x12.6）
// *：此分解不支持对过度约束的问题进行直接最小二乘法求解，并且所报告的时间包括形成对称协方差矩阵的成本$ A ^ TA $。

// 观察结果：

// LLT始终是最快的解决方案。
// 对于很大程度上过度约束的问题，Cholesky / LU分解的成本主要由对称协方差矩阵的计算决定。
// 对于较大的问题，只有实现高速缓存友好的分块策略的分解才能很好地进行扩展。
//这些包括LLT，PartialPivLU，HouseholderQR和BDCSVD。这解释了为什么对于4k x 4k矩阵，HouseholderQR比LDLT更快。将来，LDLT和ColPivHouseholderQR也将实施分块策略。
// CompleteOrthogonalDecomposition基于ColPivHouseholderQR，因此可以达到相同的性能水平。
// 上表是由bench / dense_solvers.cpp文件生成的，可以随意修改以生成与您的硬件，编译器和喜欢的问题大小相匹配的表。

} // namespace Section5_BenchmarkOfDenseDecompositions
} // namespace Chapter2_DenseLinearProblemsAndDecompositions
#endif