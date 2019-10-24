# Eigen教程

## 目的
这是我学习Eigen时翻译的Eigen[官方文档](http://eigen.tuxfamily.org/dox/modules.html)。
翻译的主要原因在于：
- 与其只在用到某一部分的时候查找API，不如先进行初步的整体学习，建立知识体系，益于程序的编写和解Bug;
- 不知为何，英文文档不能一目十行，所以还是翻译一下，利于再次使用时的快速访问和理解;
- 在百度，github等网站未能找到中文版的文档;
- 官方文档中的代码不利于在本地运行，每次还得复制粘贴，编译运行，个人认为较为麻烦;
- 为后来者种一棵小树，方便大家快速掌握Eigen。

当前文档已初步完成，内容肯定需要改善。

## 版本
Eigen  3.3.7

请注意，此程序在3.2版本下会报错!请您确保版本的正确，或者您需要注释掉源码中的部分内容！

## 翻译说明
此文档按照官方教程的结构体系，我把相关内容全部放入到C++代码中，
为了防止命名冲突，使用了两层命名空间，例如:
```
Chapter1_DenseMatrixAndArrary::Section1_MatrixClass::CoefficientAccessors();
Chapter1_DenseMatrixAndArrary::Section1_MatrixClass::MatrixAndVectorRunTime();
Chapter1_DenseMatrixAndArrary::Section3_ArrayAndCoefficientwiseOperations::AdditionAndSubtraction();
```

我并不是逐字翻译，某些部分也添加了自己的理解，并且叙述的应该是十分口水话。
当然，部分内容也是机器翻译的，但是我想它并不影响理解。
此外，可能去掉了文档中比较简单的内容，文档中的Reference也没有翻译(东西太多，本质原因，懒)。


## 当前进展
1. 第一章翻译完成，代码测试通过，见Chapter1_DenseMatrixAndArrary文件夹；
2. 第二章翻译完成，代码测试通过，见Chapter2_DenseLinearProblemsAndDecompositions文件夹；
3. 第三章和第四章翻译完成，但是这两章的代码较少，较多的是翻译的内容。


## 编译代码
1. 请在上文中的github网址中下载代码；
2. 确认CMakeLists.txt文件中的eigen头文件路径正确，确认CMakeLists.txt文件中的Qt5或者Qt4
3. 若只想显示部分内容，请注释chapterX_test.cpp文件中的非相关内容。此外，有些会产生错误的代码，为了编译通过，我给注释了。若想让程序报错，请取消注释这些代码。
4. cd 主目录
5. mkdir build 
6. cd build
7. cmake ..
8. make
9. 运行程序 ./chapterX_test

## 翻译记录
- 2019年10月18-20日，初步完成第一、二章的内容；
- 2019年10月21日，翻译了第三章部分内容；
- 2019年10月22-24日，初步完成了整体内容。


## TODO
- 查缺补漏，提高翻译质量
- 把关键的内容整理，写一篇心得体会

## Contact
由于本人精力和水平有限，希望和大家一起讨论，欢迎想一起翻译的小伙伴。
qixianyu@buaa.edu.cn