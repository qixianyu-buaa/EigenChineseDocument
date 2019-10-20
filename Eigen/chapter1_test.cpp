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

void PrintMsg(int i)
{
        cout << endl
             << "*******  Results   of   Chapter1   Section" << i << "  ********" << endl;
}
void TestChapter1Section1()
{
        PrintMsg(1);
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
        PrintMsg(2);
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
        PrintMsg(3);
        Chapter1_DenseMatrixAndArrary::Section3_ArrayAndCoefficientwiseOperations::AccessingValuesInsideAnArray();
        Chapter1_DenseMatrixAndArrary::Section3_ArrayAndCoefficientwiseOperations::AdditionAndSubtraction();
        Chapter1_DenseMatrixAndArrary::Section3_ArrayAndCoefficientwiseOperations::ArrayMultiplication();
        Chapter1_DenseMatrixAndArrary::Section3_ArrayAndCoefficientwiseOperations::ConvertingBetweenArrayAndMatrixExpressions();
        Chapter1_DenseMatrixAndArrary::Section3_ArrayAndCoefficientwiseOperations::OtherCoefficientwiseOperations();
}
void TestChapter1Section4()
{
        PrintMsg(4);
        Chapter1_DenseMatrixAndArrary::Section4_BlockOperations::UsingBlockOperations();
        Chapter1_DenseMatrixAndArrary::Section4_BlockOperations::BlockAsLeftValue();
        Chapter1_DenseMatrixAndArrary::Section4_BlockOperations::ColumnsAndRows();
        Chapter1_DenseMatrixAndArrary::Section4_BlockOperations::CornerRelatedOperations();
        Chapter1_DenseMatrixAndArrary::Section4_BlockOperations::BlockOperationsForVectors();
}

void TestChapter1Section5()
{
        PrintMsg(5);
        Chapter1_DenseMatrixAndArrary::Section5_AdvancedInitialization::CommaInitializer();
        Chapter1_DenseMatrixAndArrary::Section5_AdvancedInitialization::SpecialMatricesAndArrays();
        Chapter1_DenseMatrixAndArrary::Section5_AdvancedInitialization::UsageAsTemporaryObjects();
}

void TestChapter1Section6()
{
        PrintMsg(6);
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::BooleanReductions();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::Broadcasting();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::CombiningBroadcastingWithOtherOperations();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::CombiningPartialReductionsWithOtherOperations();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::NormComputations();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::PartialReductions();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::Reductions();
        Chapter1_DenseMatrixAndArrary::Section6_ReductionsVisitorsBroadcasting::Visitors();
}

void TestChapter1Section7()
{
        PrintMsg(7);
        Chapter1_DenseMatrixAndArrary::Section7_MapClass::ChangingTheMappedArray();
        Chapter1_DenseMatrixAndArrary::Section7_MapClass::MapConstruct();
        Chapter1_DenseMatrixAndArrary::Section7_MapClass::UsingMapVariables();
}

void TestChapter1Section8()
{
        PrintMsg(8);

        Chapter1_DenseMatrixAndArrary::Section8_ReshapeSlicing::Reshape();
        Chapter1_DenseMatrixAndArrary::Section8_ReshapeSlicing::Slicing();
}

void TestChapter1Section9()
{
        PrintMsg(9);

        Chapter1_DenseMatrixAndArrary::Section9_Aliasing::Aliasing();
        Chapter1_DenseMatrixAndArrary::Section9_Aliasing::ResolvingAliasingIssues();
        Chapter1_DenseMatrixAndArrary::Section9_Aliasing::AliasingAndComponentWiseOperations();
        Chapter1_DenseMatrixAndArrary::Section9_Aliasing::AliasingAndMatrixMultiplication();
}

void TestChapter1Section10()
{
        PrintMsg(10);

        Chapter1_DenseMatrixAndArrary::Section10_StorageOrders::testColumnAndRowMajorStorage();
}
void TestChapter1Section11()
{
        //当前Chapter11没有程序
}
int main()
{
        // build pass
        TestChapter1Section1();

        // build pass
        TestChapter1Section2();

        // build pass
        TestChapter1Section3();

        // build pass
        TestChapter1Section4();

        // build pass
        TestChapter1Section5();

        // build pass
        TestChapter1Section6();

        // build pass
        TestChapter1Section7();

        // build pass
        TestChapter1Section8();

        // build pass
        TestChapter1Section9();

        // build pass
        TestChapter1Section10();

        //TODO:add the program of TestChapter1Section11()

        return 0;
}