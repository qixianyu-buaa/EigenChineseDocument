#include "Chapter3_SparseLinearAlgebra/Section1_SparseMatrixManipulations.hpp"
void TestChapter3Section1()
{
        Chapter3_SparseLinearAlgebra::Section1_SparseMatrixManipulations::FirstExample();
}

void TestChapter3Section2()
{
        //TODO:继续翻译此部分
        Chapter3_SparseLinearAlgebra::Section1_SparseMatrixManipulations::TheSparseMatrixClass();
}

int main()
{
        //build pass
        TestChapter3Section1();   // 会生成一张图片，titiled  "result.bmp"

        TestChapter3Section2();
        return 0;
}