#ifndef SOLVE_SPARSE_LINEAR_SYSTEMS_HPP
#define SOLVE_SPARSE_LINEAR_SYSTEMS_HPP
#include "HeaderFile.h"

// http : //eigen.tuxfamily.org/dox/group__TopicSparseSystems.html
namespace Chapter3_SparseLinearAlgebra
{

//在Eigen中，当系数矩阵稀疏时，有几种方法可用于求解线性系统。
// 由于此类矩阵的特殊表示，因此应格外小心，以获得良好的性能。
// 有关Eigen中稀疏矩阵的详细介绍，请参见稀疏矩阵操作。
//此页面列出了Eigen中可用的稀疏求解器。还介绍了所有这些线性求解器共有的主要步骤。
//取决于矩阵的属性，所需的精度，最终用户能够调整这些步骤，以提高其代码的性能。
//请注意，并不需要深入了解这些步骤背后的内容：
//最后一部分提供了一个基准例程，可以轻松地使用它来深入了解所有可用求解器的性能。
namespace Section2_SolveSparseLinearSystems
{

void ListofSparseSolvers()
{
        //  Here SPD means symmetric positive definite SPD对应对称正定矩阵
        //Eigen当前提供了广泛的内置求解器，以及外部求解器库的包装器。下表中汇总了它们：

        // 1. 内置直接求解器: LLT LDLT需要对阵正定矩阵，LU需要方阵，QR适用于任意矩阵

        // Class	Solver kind	Matrix kind	Features related to performance	License        Notes

        // SimplicialLLT
        // #include<Eigen/SparseCholesky>	Direct LLt factorization	SPD	Fill-in reducing	LGPL    SimplicialLDLT is often preferable

        // SimplicialLDLT
        // #include<Eigen/SparseCholesky>	Direct LDLt factorization	SPD	Fill-in reducing	LGPL  Recommended for very sparse and not too large problems (e.g., 2D Poisson eq.)

        // SparseLU
        // #include<Eigen/SparseLU>	LU factorization	Square	Fill-in reducing, Leverage fast dense algebra	MPL2   optimized for small and large problems with irregular patterns

        // SparseQR
        // #include<Eigen/SparseQR>	QR factorization	Any, rectangular	Fill-in reducing	MPL2	recommended for least-square problems, has a basic rank-revealing feature

        // 2.内置迭代求解器

        //  Class	Solver kind	Matrix kind	Supported preconditioners, [default]	License  Notes

        // ConjugateGradient
        // #include<Eigen/IterativeLinearSolvers>	Classic iterative CG	SPD	IdentityPreconditioner, [DiagonalPreconditioner], IncompleteCholesky	MPL2
        // Recommended for large symmetric problems (e.g., 3D Poisson eq.)

        // LeastSquaresConjugateGradient
        // #include<Eigen/IterativeLinearSolvers>	CG for rectangular least-square problem	Rectangular	IdentityPreconditioner, [LeastSquareDiagonalPreconditioner]	MPL2
        // Solve for min |A'Ax-b|^2 without forming A'A

        // BiCGSTAB
        // #include<Eigen/IterativeLinearSolvers>	Iterative stabilized bi-conjugate gradient	Square	IdentityPreconditioner, [DiagonalPreconditioner], IncompleteLUT	MPL2	To speedup the convergence, try it with the IncompleteLUT preconditioner.

        //3.外部求解器
        //         Class	Module	Solver kind	Matrix kind	Features related to performance	Dependencies,License   Notes
        // PastixLLT
        // PastixLDLT
        // PastixLU	PaStiXSupport	Direct LLt, LDLt, LU factorizations	SPD
        // SPD
        // Square	Fill-in reducing, Leverage fast dense algebra, Multithreading	Requires the PaStiX package, CeCILL-C	optimized for tough problems and symmetric patterns
        // CholmodSupernodalLLT	CholmodSupport	Direct LLt factorization	SPD	Fill-in reducing, Leverage fast dense algebra	Requires the SuiteSparse package, GPL
        // UmfPackLU	UmfPackSupport	Direct LU factorization	Square	Fill-in reducing, Leverage fast dense algebra	Requires the SuiteSparse package, GPL
        // SuperLU	SuperLUSupport	Direct LU factorization	Square	Fill-in reducing, Leverage fast dense algebra	Requires the SuperLU library, (BSD-like)
        // SPQR	SPQRSupport	QR factorization	Any, rectangular	fill-in reducing, multithreaded, fast dense algebra	requires the SuiteSparse package, GPL	recommended for linear least-squares problems, has a rank-revealing feature
        // PardisoLLT
        // PardisoLDLT
        // PardisoLU	PardisoSupport	Direct LLt, LDLt, LU factorizations	SPD
        // SPD
        // Square	Fill-in reducing, Leverage fast dense algebra, Multithreading	Requires the Intel MKL package, Proprietary	optimized for tough problems patterns, see also using MKL with Eigen
}

void SparseSolverConcept()
{
        // 一个通用的例子
        // #include <Eigen/RequiredModuleName>
        // // ...
        // SparseMatrix<double> A;
        // // fill A
        // VectorXd b, x;
        // // fill b
        // // solve Ax = b
        // SolverClassName<SparseMatrix<double>> solver;
        // solver.compute(A);
        // if (solver.info() != Success)
        // {
        //         // decomposition failed
        //         return;
        // }
        // x = solver.solve(b);
        // if (solver.info() != Success)
        // {
        //         // solving failed
        //         return;
        // }
        // // solve for another right hand side:
        // x1 = solver.solve(b1);

        // 对于SPD求解器，第二个可选模板参数允许指定必须使用哪个三角形部分，例如：
        //```
        // #include <Eigen / IterativeLinearSolvers>
        // ConjugateGradient <SparseMatrix <double>，Eigen :: Upper >求解器;
        // x = Solver.compute（A）.solve（b）;

        // ```
        // 在上面的示例中，仅考虑输入矩阵A的上三角部分进行求解。对面的三角形可能为空或包含任意值。

        // 在必须解决具有相同稀疏模式的多个问题的情况下，可以将“计算”步骤分解如下：

        // SolverClassName<SparseMatrix<double>> 求解器;
        // Solver.analyzePattern（A）; //对于此步骤，不使用A的数值
        // resolver.factorize（A）;
        // x1 = Solver.solve（b1）;
        // x2 = Solver.solve（b2）;
        // ... A = ...; //修改A的非零值，非零模式必须保持不变
        // resolver.factorize（A）;
        // x1 = Solver.solve（b1）;
        // x2 = Solver.solve（b2）;
        // ...

        // 该compute（）方法等效于调用analyzerPattern（）和factorize（）。

        // 每个求解器都提供一些特定功能，例如行列式，对因子的访问，迭代控制等。有关更多详细信息，请参见相应类的文档。

        // 最后，大多数迭代求解器也可以在无矩阵的上下文中使用，请参见以下示例。
}

void TheComputeStep()
{
        // 在compute（）函数中，通常对矩阵进行因子分解：LLT用于自伴随矩阵，LDLT用于普通埃尔米特矩阵，LU用于非埃尔米特矩阵，QR用于矩形矩阵。
        //  这些是使用直接求解器的结果。对于这类求解器，将计算步骤进一步细分为analyzerPattern（）和factorize（）。

        // analyticsPattern（）的目标是对矩阵的非零元素进行重新排序，以使分解步骤创建的填充更少。
        //此步骤仅利用矩阵的结构。因此，该步骤的结果可用于矩阵结构相同的其他线性系统。
        //但是请注意，有时某些外部求解器（例如SuperLU）要求在此步骤中设置矩阵的值，以平衡矩阵的行和列。
        // 在这种情况下，此步骤的结果不应与其他矩阵一起使用。

        // Eigen在此步骤中提供了一组有限的方法来对矩阵进行重新排序，这些方法可以是内置的（COLAMD，AMD）或外部的（METIS）。
        // 这些方法在求解器的模板参数列表中设置：

        // DirectSolverClassName <SparseMatrix <double>，OrderingMethod <IndexType>> solver;
        // 有关可用方法和相关选项的列表，请参见OrderingMethods模块。

        // 在factorize（）中，计算系数矩阵的因数。每当矩阵值更改时，都应调用此步骤。但是，矩阵的结构模式不应在多个调用之间改变。

        // 对于迭代求解器，计算步骤用于最终设置预处理器。例如，使用ILUT预处理器，在此步骤中计算不完全因子L和U。
        // 请记住，基本上，预处理器的目标是通过解决系数矩阵具有更多聚类特征值的改进线性系统来加快迭代方法的收敛速度。
        //对于实际问题，迭代求解器应始终与前置条件一起使用。在Eigen中，只需将预处理器作为模板参数添加到迭代求解器对象中，即可选择预处理器。

        // IterativeSolverClassName <SparseMatrix <double>，PreconditionerName <SparseMatrix <double>>求解器;
        // 成员函数preconditioner（）返回对preconditioner的读写引用以直接与其交互。有关可用方法的列表，请参见迭代求解器模块和每个类的文档。
}

void TheSolveStep()
{
        //resolve()函数计算具有一个或多个右侧的线性系统的解。
        // X = Solver.solve（B）;
        // 在此，B可以是向量或矩阵，其中各列形成不同的右侧。可以多次调用solve（）函数，例如，当所有右侧都无法同时使用时。

        // x1 = Solver.solve（b1）;
        // //获得第二个右侧b2
        // x2 = Solver.solve（b2）;
        // // ...
        // 对于直接方法，解决方案以机器精度计算。
        // 有时，解决方案不必太精确。在这种情况下，迭代方法更合适，并且可以在使用setTolerance（）的求解步骤之前设置所需的精度。
        // 有关所有可用功能，请参阅“ 迭代求解器”模块的文档。
}

void BenchmarkRoutine()
{

        // 大多数时候，您需要知道的是解决系统所需的时间，并希望什么是最合适的求解器。
        // 在Eigen中，我们提供了可用于此目的的基准例程。这是非常容易使用。
        // 在构建目录中，导航到bench / spbench并通过键入make spbenchsolver来编译例程。
        // 使用–help选项运行它以获取所有可用选项的列表。基本上，要测试的矩阵应为MatrixMarket坐标格式，并且例程从Eigen中所有可用求解器返回统计信息。
        // 要以矩阵市场格式导出矩阵和右侧矢量，可以使用不受支持的SparseExtra模块：
        // #include <unsupported / Eigen / SparseExtra>
        // ...
        // Eigen :: saveMarket（A，“ filename.mtx”）;
        // Eigen :: saveMarket（A，“ filename_SPD.mtx”，Eigen :: Symmetric）; //如果A为对称正定
        // Eigen :: saveMarketVector（B，“ filename_b.mtx”）;
        // 下表提供了一些Eigen内置和外部求解器的XML统计信息示例。
        // 参见文档，这里不列出了
}
} // namespace Section2_SolveSparseLinearSystems

} // namespace Chapter3_SparseLinearAlgebra
#endif