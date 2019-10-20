#include "Chapter2_DenseLinearProblemsAndDecompositions/Section1_LinearAlgebraAndDecompositions.hpp"
#include "Chapter2_DenseLinearProblemsAndDecompositions/Section2_CatalogueOfDenseDecompositions.hpp"
#include "Chapter2_DenseLinearProblemsAndDecompositions/Section3_SolvingLinearLeastSquaresSystems.hpp"
#include "Chapter2_DenseLinearProblemsAndDecompositions/Section4_InplaceDecompisitions.hpp"
#include "Chapter2_DenseLinearProblemsAndDecompositions/Section5_BenchmarkOfDenseDecompositions.hpp"

void PrintMsg(int i)
{
        cout << endl
             << "*******  Results   of   Chapter2   Section" << i << "  ********" << endl;
}

void TestChapter2Section1()
{
        PrintMsg(1);
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::BasicLinearSolving();
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::CheckingIfASolutionReallyExists();
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::ComputingEigenvaluesAndEigenvectors();
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::ComputingInverseAndDeterminant();
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::LeastSquaresSolving();
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::RankRevealingDecompositions();
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::SeparatingTheComputationFromTheConstruction();
}

void TestChapter2Section2()
{
        //这部分没有程序，主要讲解稠密矩阵的分解
}

void TestChapter2Section3()
{
        PrintMsg(3);
        //讨论的三种方法是SVD分解，QR分解和正态方程。
        //其中，SVD分解通常最准确但最慢，正则方程(normal equations)最快但最不准确，QR分解介于两者之间。
        Chapter2_DenseLinearProblemsAndDecompositions::Section3_SolvingLinearLeastSquaresSystems::UsingNormalEquations();
        Chapter2_DenseLinearProblemsAndDecompositions::Section3_SolvingLinearLeastSquaresSystems::UsingTheQRDecomposition();
        Chapter2_DenseLinearProblemsAndDecompositions::Section3_SolvingLinearLeastSquaresSystems::UsingTheSvdDecomposition();
}
void TestChapter2Section4()
{
        PrintMsg(4);
        Chapter2_DenseLinearProblemsAndDecompositions::Section4_InplaceDecompisitions::InplaceMatrixDecompositions();
}
void TestChapter2Section5()
{
        //这部分没有程序，介绍了针对各种方阵和过约束问题提供的稠密矩阵分解的速度比较。
}
int main()
{
        // build pass
        TestChapter2Section1();

        // build pass
        TestChapter2Section3();

        // build pass
        TestChapter2Section4();

        return 0;
}