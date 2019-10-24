#include <Eigen/Geometry>
#include <iostream>

using namespace Eigen;
using namespace std;
int main()
{
        // scaling 矩阵为一个对角阵
        //2 0
        //0 1
        Matrix<float, 2, 2> t = Scaling(2.0f, 1.0f);
        std::cout << t.matrix() << std::endl;

        Affine3f aux(Affine3f::Identity());

        cout << aux.affine().matrix() << endl;  // aux是一个齐次矩阵，采用.affine()忽略了最后一行

        cout  << aux.matrix()<<endl;

        Transform<double, 3, Affine> Affine_transform;     // 仿射
        Affine_transform.setIdentity();
        Transform<double, 3, Isometry> Isometry_transform;   //等距
        Transform<double, 3, Projective> Projective_transform; // 射影变换
        Affine_transform.prerotate(AngleAxisd(3.14,Vector3d::UnitX()));


}