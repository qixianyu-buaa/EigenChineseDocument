#ifndef CATALOGUE_OF_DENSE_DECOMPOSITIONS_HPP
#define CATALOGUE_OF_DENSE_DECOMPOSITIONS_HPP
#include "HeaderFile.h"
namespace Chapter2_DenseLinearProblemsAndDecompositions
{

namespace Section2_CatalogueOfDenseDecompositions
{
// 此页面显示了Eigen提供的稠密矩阵分解的目录。

// 分解	矩阵要求  速度	 算法的可靠性和准确性	可计算矩阵秩	允许计算（除了线性求解） Eigen提供的线性求解器	Eigen实施的成熟度   最佳化

// 这个分解类似于没有行交换的A=LU
// PartialPivLU	可逆的	快速	取决于条件数	--	--	是	优秀的	  Blocking，隐式MT

//这个分解类似于PA=LU
// FullPivLU	--	慢	久经考验	是	--	是	优秀的	 --

// 一般的矩阵QR分解要求特征向量线性无关，不知道为啥这个QR没要求
// HouseholderQR	--	快速	取决于条件数	--	正交化	是	优秀的	Blocking

//列主元QR分解？
// ColPivHouseholderQR	--	快速	好	是	正交化	是	优秀的	很快：Blocking

//全主元QR分解
// FullPivHouseholderQR	--	慢	久经考验	是	正交化	是	平均	--

// LLT	正定	非常快	取决于条件数	--	--	是	优秀的	 Blocking

// LDLT	正或负半定	非常快	   好    	--	--	是	优秀的	 很快：Blocking

// 奇异值和特征值分解

// BDCSVD（分而治之）	--	最快的SVD算法之一	优秀的	是	奇异值/向量，最小二乘	是的（并且最小二乘）	优秀的	阻断  双对角化

// JacobiSVD（双面）	--	慢（但对于小型矩阵则快）	证明3	是	奇异值/向量，最小二乘	是的（并且最小二乘）	优秀的	R-SVD

// 自伴特征算法	自伴	快速平均2	好	是	特征值/向量	--	优秀的	2x2和3x3的解析解

// 复杂特征求解器	平方	慢-非常慢2	取决于条件数	是	特征值/向量	--	一般	--

// 特征解算器	正方形和实数	平均-慢  	取决于条件数	是	特征值/向量	--	一般	--

// 广义自我伴随特征求解	  方阵	快速-一般2	取决于条件数	--	广义特征值/向量	--	好	 --

// 辅助分解

// RealSchur	正方形和实数	一般-慢2	取决于条件数	是	--	--	一般	 --

// ComplexSchur	正方形	慢-非常慢2	取决于条件数	是	--	--	一般	 --

// Tridiagonalization	自伴	快速	好	--	--	--	好	很快：封锁

// HessenbergDecomposition	正方形	平均	好	--	--	--	好	很快：封锁

// 笔记：
// 1：LDLT算法有两种变体。Eigen的一个生成纯对角D矩阵，因此它不能处理不定的矩阵，这与Lapack的一个生成块对角D矩阵不同。
// 2：特征值，SVD和Schur分解依赖于迭代算法。它们的收敛速度取决于特征值的分离程度。
// 3：我们的JacobiSVD是双面的，可为平方矩阵提供经过验证的最佳精度。对于非平方矩阵，我们必须首先使用QR预调节器。默认选择ColPivHouseholderQR已经非常可靠，但是如果您想证明这一点，请改用FullPivHouseholderQR。
// 术语：
// 自伴
// 对于实矩阵，自伴是对称的同义词。对于复杂的矩阵，自伴为同义词埃尔米特。更一般地，A当且仅当矩阵等于其伴随时A*，矩阵才是自伴随的$ A ^ * $。伴随也称为共轭转置。
// 正/负定
// $ $如果$ v ^ * A v> 0 $对于任何非零向量，则自伴矩阵是正定的$ v $。同样，如果$ v ^ * A v <0 $对于任何非零向量，则为负定$ v $
// 正/负半定
// $ $如果$ v ^ * A v \ ge 0 $对于任何非零向量，自伴矩阵是正半定的$ v $。同样，$ v ^ * A v \ le 0 $对于任何非零向量，它为负半定数$ v $

// Blocking
// 意味着该算法可以按块工作，从而保证了大型矩阵性能的良好缩放。
// 隐式多线程（MT）
// 意味着该算法可以通过OpenMP利用多核处理器。“隐式”是指算法本身不是并行的，而是依赖于并行矩阵矩阵乘积的规则。
// 显式多线程（MT）
// 意味着该算法已显式并行化，以通过OpenMP利用多核处理器。
// 元展开器
// 意味着对于很小的固定大小矩阵，该算法将自动显式展开。
} // namespace Section2_CatalogueOfDenseDecompositions
} // namespace Chapter2_DenseLinearProblemsAndDecompositions

#endif