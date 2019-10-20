#include "Chapter1_DenseMatrixAndArrary/Section1_MatrixClass.hpp"
#include "Chapter1_DenseMatrixAndArrary/Section2_MatrixAndVectorArithmetic.hpp"
#include "Chapter1_DenseMatrixAndArrary/Section3_ArrayAndCoefficientwiseOperations.hpp"
#include "Chapter1_DenseMatrixAndArrary/Section4_BlockOperations.hpp"
#include "Chapter1_DenseMatrixAndArrary/Section5_AdvancedInitialization.hpp"
#include "Chapter1_DenseMatrixAndArrary/Section6_ReductionsVisitorsBroadcasting.hpp"
#include "Chapter1_DenseMatrixAndArrary/Section7_MapClass.hpp"
#include "Chapter1_DenseMatrixAndArrary/Section8_ReshapeAndSlicing.hpp"
#include "Chapter1_DenseMatrixAndArrary/Section9_Aliasing.hpp"
#include "Chapter1_DenseMatrixAndArrary/Section10_StorageOrders.hpp"
#include "Chapter1_DenseMatrixAndArrary/Section11_AlignmentIssues.hpp"
void TestChapter1Section1()
{
        Chapter1_DenseMatrixAndArrary::Section1_MatrixClass::CoefficientAccessors();
        Chapter1_DenseMatrixAndArrary::Section1_MatrixClass::AssignmentAndResizing();
        Chapter1_DenseMatrixAndArrary::Section1_MatrixClass::CommaInitialization();
        Chapter1_DenseMatrixAndArrary::Section1_MatrixClass::ConvenienceTypedefs();
        Chapter1_DenseMatrixAndArrary::Section1_MatrixClass::FixedSizeAndDynamicSize();
        Chapter1_DenseMatrixAndArrary::Section1_MatrixClass::MatrixAndVectorCompileTime();
        Chapter1_DenseMatrixAndArrary::Section1_MatrixClass::MatrixAndVectorRunTime();
        Chapter1_DenseMatrixAndArrary::Section1_MatrixClass::OptionalTemplateParameters();
        Chapter1_DenseMatrixAndArrary::Section1_MatrixClass::Resizing();
}

void TestChapter1Section2()
{
        Chapter1_DenseMatrixAndArrary::Section2_MatrixAndVectorArithmetic::AdditionAndSubtraction();
        Chapter1_DenseMatrixAndArrary::Section2_MatrixAndVectorArithmetic::ScalarMultiplicationAndDivision();
        Chapter1_DenseMatrixAndArrary::Section2_MatrixAndVectorArithmetic::ANoteAboutExpressionTemplates();
        Chapter1_DenseMatrixAndArrary::Section2_MatrixAndVectorArithmetic::TranspositionAndConjugation();
        Chapter1_DenseMatrixAndArrary::Section2_MatrixAndVectorArithmetic::MatrixMatrixAndMatrixVectorMultiplication();
        Chapter1_DenseMatrixAndArrary::Section2_MatrixAndVectorArithmetic::DotProductAndCrossProduct();
        Chapter1_DenseMatrixAndArrary::Section2_MatrixAndVectorArithmetic::BasicArithmeticReductionOperations();
        Chapter1_DenseMatrixAndArrary::Section2_MatrixAndVectorArithmetic::ValidityOfoperations();
}

void TestChapter1Section3()
{
        Chapter1_DenseMatrixAndArrary::Section3_ArrayAndCoefficientwiseOperations::AccessingValuesInsideAnArray();
        Chapter1_DenseMatrixAndArrary::Section3_ArrayAndCoefficientwiseOperations::AdditionAndSubtraction();
        Chapter1_DenseMatrixAndArrary::Section3_ArrayAndCoefficientwiseOperations::ArrayMultiplication();
        Chapter1_DenseMatrixAndArrary::Section3_ArrayAndCoefficientwiseOperations::ConvertingBetweenArrayAndMatrixExpressions();
        Chapter1_DenseMatrixAndArrary::Section3_ArrayAndCoefficientwiseOperations::OtherCoefficientwiseOperations();
}
void TestChapter1Section4()
{
        Chapter1_DenseMatrixAndArrary::Section4_BlockOperations::UsingBlockOperations();
        Chapter1_DenseMatrixAndArrary::Section4_BlockOperations::BlockAsLeftValue();
        Chapter1_DenseMatrixAndArrary::Section4_BlockOperations::ColumnsAndRows();
        Chapter1_DenseMatrixAndArrary::Section4_BlockOperations::CornerRelatedOperations();
        Chapter1_DenseMatrixAndArrary::Section4_BlockOperations::BlockOperationsForVectors();
}

void TestChapter1Section5()
{
        Chapter1_DenseMatrixAndArrary::Section5_AdvancedInitialization::CommaInitializer();
        Chapter1_DenseMatrixAndArrary::Section5_AdvancedInitialization::SpecialMatricesAndArrays();
        Chapter1_DenseMatrixAndArrary::Section5_AdvancedInitialization::UsageAsTemporaryObjects();
}


void TestChapter1Section6()
{
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::BooleanReductions();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::Broadcasting();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::CombiningBroadcastingWithOtherOperations();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::CombiningPartialReductionsWithOtherOperations();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::NormComputations();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::PartialReductions();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::Reductions();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::Visitors();
}
int main()
{
        // build pass
        //TestChapter1Section1();

        // build pass
        // TestChapter1Section2();

        // build pass
        // TestChapter1Section3();

        // build pass
        //TestChapter1Section4();

        // Todo 调整格式
        //TestChapter1Section5();


        TestChapter1Section6();

        return 0;
}