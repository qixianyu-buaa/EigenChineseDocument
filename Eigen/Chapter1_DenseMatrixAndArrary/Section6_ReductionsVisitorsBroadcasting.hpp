#ifndef REDUCTIONS_VISITORS_BROADCASTING_HPP
#define REDUCTIONS_VISITORS_BROADCASTING_HPP
#include "HeaderFile.h"
//http://eigen.tuxfamily.org/dox/group__TutorialReductionsVisitorsBroadcasting.html

namespace Chapter1_DenseMatrixAndArrary
{
namespace Section6_ReductionsVisitorsBroadcasting
{

void Reductions()
{
        LOG();
        //在Eigen中，约简是一个采用矩阵或数组并返回单个标量值的函数。最常用的归约方法之一是.sum（），它返回给定矩阵或数组内所有系数的总和。
        Eigen::Matrix2d mat;
        mat << 1, 2,
            3, 4;
        cout << "Here is mat.sum():       " << mat.sum() << endl;
        cout << "Here is mat.prod():      " << mat.prod() << endl;
        cout << "Here is mat.mean():      " << mat.mean() << endl;
        cout << "Here is mat.minCoeff():  " << mat.minCoeff() << endl;
        cout << "Here is mat.maxCoeff():  " << mat.maxCoeff() << endl;
        cout << "Here is mat.trace():     " << mat.trace() << endl;
}

void NormComputations()
{
        LOG();
        // 2范数的平方可以通过squaredNorm()获得。它本身等于矢量的点积，并且等效于其系数的平方绝对值的总和。
        //  norm（）方法返回squaredNorm（）的平方根。
        // 这些运算也可以在矩阵上运算。在这种情况下，n×p矩阵被视为大小（n * p）的向量，
        // 因此，例如norm()方法返回“ Frobenius”或“ Hilbert-Schmidt”范数。
        // 我们避免谈论l^2矩阵的范数，因为那可能意味着不同的事情。
        // 如果需要其他按系数分配的l^p范数，请使用lpNorm <p>()。
        // 如果需要无穷范数，则模板参数p可以采用特殊值Infinity，这是系数绝对值的最大值。
        VectorXf v(2);
        MatrixXf m(2, 2), n(2, 2);
        v << -1,
            2;

        m << 1, -2,
            -3, 4;
        // 向量范数
        cout << "v.squaredNorm() = " << v.squaredNorm() << endl;
        cout << "v.norm() = " << v.norm() << endl;
        cout << "v.lpNorm<1>() = " << v.lpNorm<1>() << endl;
        cout << "v.lpNorm<Infinity>() = " << v.lpNorm<Infinity>() << endl;
        cout << endl;
        // 矩阵范数
        cout << "m.squaredNorm() = " << m.squaredNorm() << endl;
        cout << "m.norm() = " << m.norm() << endl;
        cout << "m.lpNorm<1>() = " << m.lpNorm<1>() << endl;
        cout << "m.lpNorm<Infinity>() = " << m.lpNorm<Infinity>() << endl;

        // 也可自己计算1范数和无穷范数
        MatrixXf mat(2, 2);
        mat << 1, -2,
            -3, 4;
        cout << "1-norm(mat)     = " << mat.cwiseAbs().colwise().sum().maxCoeff()
             << " == " << mat.colwise().lpNorm<1>().maxCoeff() << endl;
        cout << "infty-norm(mat) = " << mat.cwiseAbs().rowwise().sum().maxCoeff()
             << " == " << mat.rowwise().lpNorm<1>().maxCoeff() << endl;
}

void BooleanReductions()
{
        LOG();
        // 矩阵或者数组皆有与，或，个数的方法
        // all() returns true if all of the coefficients in a given Matrix or Array evaluate to true .
        // any() returns true if at least one of the coefficients in a given Matrix or Array evaluates to true .
        // count() returns the number of coefficients in a given Matrix or Array that evaluate to true.
        ArrayXXf a(2, 2);

        a << 1, 2,
            3, 4;
        cout << "(a > 0).all()   = " << (a > 0).all() << endl;
        cout << "(a > 0).any()   = " << (a > 0).any() << endl;
        cout << "(a > 0).count() = " << (a > 0).count() << endl;
        cout << endl;
        cout << "(a > 2).all()   = " << (a > 2).all() << endl;
        cout << "(a > 2).any()   = " << (a > 2).any() << endl;
        cout << "(a > 2).count() = " << (a > 2).count() << endl;
}

void Visitors()
{
        LOG();
        // 这是在矩阵和数组的所有元素中
        //想要获得一个系数在Matrix或Array中的位置时，访问者很有用。
        //最简单的示例是maxCoeff（＆x，＆y）和minCoeff（＆x，＆y），可用于查找Matrix或Array中最大或最小系数的位置。
        //传递给访问者的参数是指向要存储行和列位置的变量的指针。这些变量应为Index类型，

        Eigen::MatrixXf m(2, 2);

        m << 1, 2,
            3, 4;
        //get location of maximum
        MatrixXf::Index maxRow, maxCol;
        float max = m.maxCoeff(&maxRow, &maxCol);
        //get location of minimum
        MatrixXf::Index minRow, minCol;
        float min = m.minCoeff(&minRow, &minCol);
        cout << "Max: " << max << ", at: " << maxRow << "," << maxCol << endl;
        cout << "Min: " << min << ", at: " << minRow << "," << minCol << endl;
}

void PartialReductions()
{
        LOG();
        // 这是在矩阵或数组的列向量和行向量中
        // 记住,element-wise是按元素的，那么colwise()或rowwise()表示按列或行的
        //部分归约是可以在Matrix或Array上按列或按行操作的归约，对每个列或行应用归约运算并返回具有相应值的列或行向量。
        //部分缩减适用于colwise（）或rowwise（）
        //一个简单的示例是获取给定矩阵中每一列中元素的最大值，并将结果存储在行向量中：
        // column-wise返回行向量，row-wise返回列向量。啥意思？应该设计底层操作，以后再看   ******TODO*******
        //注意： column-wise operations return a row vector, while row-wise operations return a column vector.
        Eigen::MatrixXf mat(2, 4);
        mat << 1, 2, 6, 9,
            3, 1, 7, 2;

        std::cout << "Column's maximum: " << std::endl
                  << mat.colwise().maxCoeff() << std::endl; // 对于矩阵mat的每一列，取最大系数值

        // 也可以对行操作
        std::cout << "Row's maximum: " << std::endl
                  << mat.rowwise().maxCoeff() << std::endl; // 对于矩阵mat的每一行，取最大系数值
}

void CombiningPartialReductionsWithOtherOperations()
{
        LOG();

        MatrixXf mat(2, 4);
        mat << 1, 2, 6, 9,
            3, 1, 7, 2;

        MatrixXf::Index maxIndex;
        float maxNorm = mat.colwise().sum().maxCoeff(&maxIndex); //  对于矩阵的每一列中的元素求和，结果的最大系数在第2列

        std::cout << "Maximum sum at position " << maxIndex << std::endl;
        std::cout << "The corresponding vector is: " << std::endl;
        std::cout << mat.col(maxIndex) << std::endl;
        std::cout << "And its sum is is: " << maxNorm << std::endl;
        // Output is :
        //Maximum sum at position 2
        // The corresponding vector is:
        // 6
        // 7
        // And its sum is is: 13
}

void Broadcasting()
{
        LOG();
        //广播背后的概念类似于部分归约，区别在于广播构造了一个表达式，其中向量（列或行）通过在一个方向上复制而被解释为矩阵。
        //一个简单的示例是将某个列向量添加到矩阵中的每一列。这可以通过以下方式完成：
        Eigen::MatrixXf mat(2, 4);
        Eigen::VectorXf v(2);
        mat << 1, 2, 6, 9,
            3, 1, 7, 2;
        v << 0,
            1;

        //add v to each column of m
        //mat.colwise() += v用两种等效的方式解释指令。
        //它将向量添加v到矩阵的每一列。或者，可以将其解释为重复向量v四次以形成四乘二矩阵，然后将其加到mat
        mat.colwise() += v;

        std::cout << "Broadcasting result: " << std::endl;
        std::cout << mat << std::endl;

        // Output is:
        // Broadcasting result:
        // 1 2 6 9
        // 4 2 8 3

        // 在矩阵上，我们可以执行-=,+=,+,-操作，但是不能进行*=,/=,*,/操作
        // 在数组上我们可执行*=,/=,*,/操作
        // If you want multiply column 0 of a matrix mat with v(0), column 1 with v(1), and so on, then use mat = mat * v.asDiagonal().
        // 要逐列或逐行添加的向量必须为Vector类型，并且不能为Matrix。
        // 如果不满足，则会出现编译时错误。
        //这也意味着，在使用Matrix进行操作时，广播操作只能应用于Vector类型的对象。这同样适用于数组类VectorXf是ArrayXf。与往常一样，您不应在同一表达式中混合使用数组和矩阵。

        // 同样，也可以对行执行此操作
        {
                Eigen::MatrixXf mat(2, 4);
                Eigen::VectorXf v(4);

                mat << 1, 2, 6, 9,
                    3, 1, 7, 2;

                v << 0, 1, 2, 3;

                //add v to each row of m
                mat.rowwise() += v.transpose();

                std::cout << "Broadcasting result: " << std::endl;
                std::cout << mat << std::endl;

                //  Broadcasting result:
                //  1  3  8 12
                //  3  2  9  5
        }
}

void CombiningBroadcastingWithOtherOperations()
{
        LOG();
        // 广播还可以与其他操作（例如矩阵或阵列操作），归约和部分归约相结合。
        //现在已经介绍了广播，约简和部分约简，我们可以深入研究一个更高级的示例，该示例v在矩阵的列中找到向量的最近邻m。
        //欧几里德距离将在本示例中使用，计算具有部分归约名为squaredNorm()的平方欧几里德距离：
        Eigen::MatrixXf m(2, 4);
        Eigen::VectorXf v(2);

        m << 1, 23, 6, 9,
            3, 11, 7, 2;

        v << 2,
            3;
        MatrixXf::Index index;
        // find nearest neighbour
        (m.colwise() - v).colwise().squaredNorm().minCoeff(&index);
        cout << "Nearest neighbour is column " << index << ":" << endl;
        cout << m.col(index) << endl;
}
} // namespace Section6_ReductionsVisitorsBroadcasting
} // namespace Chapter1_DenseMatrixAndArrary
#endif