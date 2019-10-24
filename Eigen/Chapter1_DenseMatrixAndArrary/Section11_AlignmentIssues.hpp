#ifndef ALIGNMENT_ISSUES_HPP
#define ALIGNMENT_ISSUES_HPP
#include "HeaderFile.h"

namespace Chapter1_DenseMatrixAndArrary
{

namespace Section11_AlignmentIssues
{
// 这节比较抽象，知道咋用就好！
// TODO 继续翻译！

// 对齐错误
//Eigen::internal::matrix_array<T, Size, MatrixOptions, Align>::internal::matrix_array()
// [with T = double, int Size = 2, int MatrixOptions = 2, bool Align = true]:
// Assertion `(reinterpret_cast<size_t>(array) & (sizemask)) == 0 && "this assertion
// is explained here: http://eigen.tuxfamily.org/dox-devel/group__TopicUnalignedArrayAssert.html
//      READ THIS WEB PAGE !!! ****"' failed.

// 首先找到程序触发位置，
// 例如，
//$gdb ./my_program
//>run
//...
//>bt
//然后与下面的4种原因对号入座，修改代码

// 二 四种原因

// 原因1:结构体中具有Eigen对象成员
//请注意，此处Eigen :: Vector2d仅用作示例，
//更一般而言，所有固定大小的可矢量化Eigen类型都会出现此问题
//固定大小的可矢量化Eigen类型是如果它具有固定的大小并且大小是16字节的倍数
// Eigen::Vector2d
// Eigen::Vector4d
// Eigen::Vector4f
// Eigen::Matrix2d
// Eigen::Matrix2f
// Eigen::Matrix4d
// Eigen::Matrix4f
// Eigen::Affine3d
// Eigen::Affine3f
// Eigen::Quaterniond
// Eigen::Quaternionf

// 首先, "固定大小"应该清楚：如果在编译时，Eigen对象的行数和列数是固定的，则其固定大小。
// 因此，例如Matrix3f具有固定大小，但MatrixXf没有（固定大小的对立是动态大小）。
// 固定大小的Eigen对象的系数数组是普通的“静态数组”，不会动态分配。例如，Matrix4f后面的数据只是一个“float array[16]”。
// 固定大小的对象通常很小，这意味着我们要以零的运行时开销（在内存使用和速度方面）来处理它们。
// 现在，矢量化（SSE和AltiVec）都可以处理128位数据包。此外，出于性能原因，这些数据包必须具有128位对齐。
//因此，事实证明，固定大小的Eigen对象可以向量化的唯一方法是，
//如果它们的大小是128位或16个字节的倍数。然后，Eigen将为这些对象请求16字节对齐，并且此后将依赖于这些对象进行对齐，因此不会执行运行时检查以进行对齐。
// class Foo
// {
//   //...
//   Eigen::Vector2d v;
//   //...
// };
// //...
// Foo *foo = new Foo;

// Eigen需要Eigen :: Vector2d的数组（2个双精度）的128位对齐。对于GCC，这是通过属性（（aligned（16）））完成的。
// Eigen重载了Eigen :: Vector2d的“ operator new”，因此它将始终返回128位对齐的指针。
// 因此，通常情况下，您不必担心任何事情，Eigen会为您处理对齐...

// ...除了一种情况。当您具有上述的Foo类，并且如上所述动态分配新的Foo时，则由于Foo没有对齐“ operator new”，因此返回的指针foo不一定是128位对齐的。
// 然后，成员v的alignment属性相对于类的开头foo。如果foo指针未对齐，则foo-> v也不会对齐！
// 解决方案是让Foo类具有一致的“Operator new”

// 解决方法：
//如果定义的结构具有固定大小的可矢量化Eigen类型的成员，
//则必须重载其“ operator new”，以便它生成16字节对齐的指针。
//幸运的是，Eigen为您提供了一个宏EIGEN_MAKE_ALIGNED_OPERATOR_NEW来为您执行此操作。
//换句话说：您有一个类，该类具有固定大小的可矢量化Eigen对象作为成员，然后动态创建该类的对象。

//很简单，您只需将EIGEN_MAKE_ALIGNED_OPERATOR_NEW宏放在您的类的public部分
// class Foo
// {
//         Eigen::Vector2d v;
//         public : EIGEN_MAKE_ALIGNED_OPERATOR_NEW
// };
// Foo *foo = new Foo;
//该宏使“ new Foo”始终返回对齐的指针。
//一个 Eigen::Vector2d有两个double类型，一个double为8字节=64位，则一个Eigen::Vector2d为128位
//这恰好是SSE数据包的大小，这使得可以使用SSE对该向量执行各种操作。
//但是SSE指令（至少Eigen使用的是快速指令）需要128位对齐。否则会出现段错误。
// 出于这个原因，Eigen自己通过执行以下两项工作自行要求对Eigen :: Vector2d进行128位对齐：


//原因2：STL容器或手动内存分配
///如果您将Stl容器（例如std :: vector，std :: map等）
//与Eigen对象或包含Eigen对象的类一起使用，
// std::vector<Eigen::Matrix2f> my_vector;
// struct my_class { ... Eigen::Matrix2f m; ... };
// std::map<int, my_class> my_map;
//请注意，此处Eigen :: Matrix2f仅用作示例，更一般而言，对于所有固定大小的可矢量化Eigen类型和具有此类Eigen对象作为member的结构，都会出现此问题。
//任何类/函数都会绕过new分配内存的运算符，也就是通过执行自定义内存分配，然后调用placement new运算符，
// 也会出现相同的问题。例如，通常就是这种情况，std::make_shared或者std::allocate_shared解决方案是使用对齐的分配器，
//如STL容器解决方案中所述。

//原因3：通过值传递Eigen对象
//如果您代码中的某些函数正在通过值传递Eigen对象，例如这样，
//void func(Eigen::Vector4d v);
//那么您需要阅读以下单独的页面：将Eigen对象按值传递给函数。
//请注意，此处Eigen :: Vector4d仅用作示例，更一般而言，所有固定大小的可矢量化Eigen类型都会出现此问题

//原因4:编译器对堆栈对齐做出错误假设（例如Windows上的GCC）
//这是在Windows上使用GCC（例如MinGW或TDM-GCC）的人们的必读内容。
//如果在声明这样的局部变量的无辜函数中有此断言失败，请执行以下操作：
// void foo()
// {
//   Eigen::Quaternionf q;
//   //...
// }
//那么您需要阅读以下单独的页面：编译器对堆栈对齐做出了错误的假设。
//请注意，此处Eigen :: Quaternionf仅用作示例，更一般而言，所有固定大小的可矢量化Eigen类型都会出现此问题。

// 3  该断言的一般解释:
// 固定大小的矢量化Eigen对象必须绝对在16字节对齐的位置创建，否则寻址它们的SIMD指令将崩溃。
// Eigen通常会为您解决这些对齐问题，方法是在固定大小的可矢量化对象上设置对齐属性，
// 并重载他们的“ operator new”。
// 但是，在某些极端情况下，这些对齐设置会被覆盖：它们是此断言的可能原因。

// 4   我不在乎最佳矢量化，如何摆脱这些东西？
// 三种可能性：
// 使用Matrix，Array，Quaternion等对象的DontAlign选项会给您带来麻烦。
// 这样，Eigen不会尝试对齐它们，因此不会采取任何特殊对齐方式。
// 不利的一面是，您将为它们支付未对齐的加载/存储的成本，但是在现代CPU上，开销为null或边际的。
// 定义EIGEN_DONT_ALIGN_STATICALLY。这将禁用所有16​​字节（或以上）的静态对齐代码，
// 同时保持16字节（或以上）的堆对齐。这具有通过未对齐的存储区（由EIGEN_UNALIGNED_VECTORIZE控制）对固定大小的对象（如Matrix4d）进行矢量化的效果，同时保持动态大小的对象（如MatrixXd）的矢量化不变。
//但是请注意，这会破坏ABI与静态对齐方式默认行为的兼容性。
// 或同时定义EIGEN_DONT_VECTORIZE和EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT。
// 这样可以保留16字节的对齐代码，从而保留ABI兼容性，但完全禁用向量化。
// 如果您想知道为什么定义EIGEN_DONT_VECTORIZE本身并不能禁用16字节对齐和断言，则说明如下：
// 它不会禁用断言，因为如果不执行矢量化，则正常运行的代码将在启用矢量化时突然崩溃。
// 它不会禁用16字节对齐，因为这将意味着矢量化和非矢量化的代码不相互兼容ABI。
// 即使对于仅开发内部应用程序的人，这种ABI兼容性也非常重要，
// 例如，可能希望在同一应用程序中同时具有矢量化路径和非矢量化路径。

} // namespace Section11_AlignmentIssues

} // namespace Chapter1_DenseMatrixAndArrary
#endif