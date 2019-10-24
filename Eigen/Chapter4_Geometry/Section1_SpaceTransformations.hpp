#ifndef SPACE_TRANSFORMATIONS_HPP
#define SPACE_TRANSFORMATIONS_HPP
#include "HeaderFile.h"

namespace Chapter4_Geometry
{

namespace Section1_SpaceTransformations
{

// 在此页面中，我们将介绍几何模块提供的许多可能性，以处理2D和3D旋转以及射影或仿射变换。

// Eigen的Geometry模块提供了两种不同的几何变换：

// 1. 抽象的变换，例如旋转（轴角或四元数表示），平移，缩放。
// 这些转换未表示为矩阵，但是您仍然可以将它们与表达式中的矩阵和向量混合，并根据需要将它们转换为矩阵。

// 2. 射影或仿射变换矩阵：请参见Transform类。这些确实是矩阵。注意, 如果要使用OpenGL 4x4矩阵，则需要Affine3f和Affine3d。
// 由于Eigen默认为列序存储，因此您可以直接使用Transform :: data()方法将转换矩阵传递给OpenGL。

// 您可以从抽象转换构造一个Transform，如下所示：
// Transform t(AngleAxis(angle,axis));
// 或像这样：
// Transform t;
// t = AngleAxis(angle,axis);

// 但是请注意，不幸的是，由于C ++的工作方式，您不能这样做：

// Transform t = AngleAxis(angle,axis);
// 说明：在C ++语言中，这将要求Transform具有一个来自AngleAxis的非显式转换构造函数，但是我们真的不想在此允许隐式转换。

// 变换的类型

// 变换类型                        典型的初始化
// 2D旋转，注意角度单位是弧度
// 2D rotation from an angle
// Rotation2D<float> rot2(angle_in_radian);

// 3D旋转的轴角方法，注意，轴必须归一化(The axis vector must be normalized.)
// 3D rotation as an angle + axis
// AngleAxis<float> aa(angle_in_radian, Vector3f(ax,ay,az));

// 3D旋转的四元数方法，可以由轴角得到
// Quaternion<float> q;  q = AngleAxis<float>(angle_in_radian, axis);

// N维缩放
// Scaling(sx, sy)
// Scaling(sx, sy, sz)
// Scaling(s)
// Scaling(vecN)

// N维平移
// Translation<float,2>(tx, ty)
// Translation<float,3>(tx, ty, tz)
// Translation<float,N>(s)
// Translation<float,N>(vecN)

// N维仿射
// Transform<float,N,Affine> t = concatenation_of_any_transformations;
// Transform<float,3,Affine> t = Translation3f(p) * AngleAxisf(a,axis) * Scaling(s);

// N维线性变换(pure rotations,scaling, etc.) 注意：下面的文档好像有问题，因为Matrix<>需要指定行列数，但是下文指定的只是行数，我们还需要指定列数
// Matrix<float,N> t = concatenation_of_rotations_and_scalings;
// Matrix<float,2> t = Rotation2Df(a) * Scaling(s);
// Matrix<float,3> t = AngleAxisf(a,axis) * Scaling(s);

// 关于旋转的注意事项
// 要变换多个矢量，首选采用的是旋转矩阵，而对于其他用法，四元数是紧凑，快速和稳定的首选表示形式。
// 最后，Rotation2D和AngleAxis主要是创建其他旋转对象的便捷类型。

// 关于平移和缩放的注释
// 像AngleAxis一样，这些类旨在简化线性（Matrix）和仿射（Transform）变换的创建/初始化。
// 但是，与使用效率低下的AngleAxis不同，编写任何类型的转换作为输入的通用高效算法可能仍然很有趣。

// 上述任何转换类型都可以转换为相同性质的任何其他类型，或者转换为更通用的类型。以下是一些其他示例：

// Rotation2Df r;  r  = Matrix2f(..);       // assumes a pure rotation matrix
// AngleAxisf aa;  aa = Quaternionf(..);
// AngleAxisf aa;  aa = Matrix3f(..);       // assumes a pure rotation matrix
// Matrix2f m;     m  = Rotation2Df(..);
// Matrix3f m;     m  = Quaternionf(..);       Matrix3f m;   m = Scaling(..);
// Affine3f m;     m  = AngleAxis3f(..);       Affine3f m;   m = Scaling(..);
// Affine3f m;     m  = Translation3f(..);     Affine3f m;   m = Matrix3f(..);

// 跨转换类型的通用API
// 在某种程度上，Eigen的几何模块允许您编写适用于任何类型的变换表示形式的通用算法：
// Concatenation of two transformations
// gen1 * gen2;
// Apply the transformation to a vector
// vec2 = gen1 * vec1;
// Get the inverse of the transformation
// gen2 = gen1.inverse();
// Spherical interpolation
// (Rotation2D and Quaternion only)
// rot3 = rot1.slerp(alpha,rot2);

void AffineTransformations()
{
        // 本部分介绍仿射变换
        // 概念上，仿射变换是一个非奇异线性变换 linear()与一个平移变换t的复合，可能是因为x' = linear()*x + t ;所以linear()是线性部分
        //  仿射变换的表达为H_{A} = [ linear_part,translation part ;0 ,1 ]

        // 通用仿射变换由Transform类表示，该类内部是（Dim + 1）^ 2的矩阵。
        // 在Eigen中，我们选择不区分点和向量，以使所有点实际上都由原点（$ \ mathbf {p} \ equiv \ mathbf {p} -0 $）的位移向量表示。
        // 注意的是，在应用变换时，点和向量会有所区别。

        // 将变换应用于点
        // VectorNf p1, p2;
        // p2 = t * p1;

        //  将变换应用于向量
        // VectorNf vec1, vec2;
        // vec2 = t.linear() * vec1;   // 可能是考虑到平移部分并不影响向量的变化

        // 应用一个更一般的变换作用在normal vector ，这部分没看懂
        // VectorNf n1, n2;
        // MatrixNf normalMatrix = t.linear().inverse().transpose();     //A^{-1}^{T}???
        // n2 = (normalMatrix * n1).normalized();
        // (See subject 5.27 of this faq for the explanations)

        //将纯旋转变换作用在一个 normal vector (no scaling, no shear)
        // n2 = t.linear() * n1;
        // OpenGL compatibility 3D
        // glLoadMatrixf(t.data());
        // OpenGL compatibility 2D
        // Affine3f aux(Affine3f::Identity());
        // aux.linear().topLeftCorner<2,2>() = t.linear();
        // aux.translation().start<2>() = t.translation();
        // glLoadMatrixf(aux.data());

        // 成分获取
        // 对内部矩阵的完全读写访问
        // full read-write access to the internal matrix
        // t.matrix() = matN1xN1;    // N1 means N+1
        // matN1xN1 = t.matrix();

        // 获取元素系数
        // t(i,j) = scalar;   <=>   t.matrix()(i,j) = scalar;
        // scalar = t(i,j);   <=>   scalar = t.matrix()(i,j);

        // 平移部分
        // t.translation() = vecN;
        // vecN = t.translation();

        // 线性部分
        // t.linear() = matNxN;
        // matNxN = t.linear();
        // extract the rotation matrix
        // matNxN = t.rotation();

        // 生成变换
        // 变换可以是先左乘或者右乘，所以有一系列APII

        // 平移
        // t.translate(Vector_(tx,ty,..));   等价于t *= Translation_(tx,ty,..);即右侧乘法
        // t.pretranslate(Vector_(tx,ty,..));等价于  t = Translation_(tx,ty,..) * t; 即左侧乘法

        // 旋转(注意单位是弧度)
        // t.rotate(any_rotation);  等价于 t *= any_rotation;
        // t.prerotate(any_rotation);等价于 t = any_rotation * t;

        // 缩放
        // t.scale(Vector_(sx,sy,..));   等价于  t *= Scaling(sx,sy,..);
        // t.scale(s);   等价于 t *= Scaling(s);
        // t.prescale(Vector_(sx,sy,..));  等价于 t = Scaling(sx,sy,..) * t;
        // t.prescale(s); 等价于  t = Scaling(s) * t;

        // 错切变换，仅限于2D
        // t.shear(sx,sy);
        // t.preshear(sx,sy);

        // 注意，上述变换可以作为一个表达式为：
        // t.pretranslate(..).rotate(..).translate(..).scale(..); 等价于 t = Translation_(..) * t * RotationType(..) * Translation_(..) * Scaling(..);
}

void EulerAngles()
{

        // 欧拉角
        // 欧拉角可能很方便创建旋转对象。另一方面，由于存在24种不同的约定，因此使用起来相当混乱。
        // 本示例说明如何根据2-1-2约定创建旋转矩阵。ZYZ形式
        // Matrix3f m;
        // m = AngleAxisf（angle1，Vector3f :: UnitZ（））
        //     * AngleAxisf（angle2，Vector3f :: UnitY（））
        //     * AngleAxisf（angle3，Vector3f :: UnitZ（））;
}

} // namespace Section1_SpaceTransformations

} // namespace Chapter4_Geometry

#endif