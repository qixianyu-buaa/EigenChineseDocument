# Eigen教程

## 目的
这是我学习Eigen时翻译的Eigen[官方文档](http://eigen.tuxfamily.org/dox/modules.html)。
翻译的主要原因在于：
- 与其只在用到某一部分的时候查找API，不如先整体进行一个初步的整体学习，建立知识体系，益于程序的编写和解Bug;
- 不知为何，英文文档不能一目十行，所以还是翻译一下，利于再次使用时的快速访问和理解;
-  在百度，github等网站未能找到中文版的文档;
-  官方文档中的代码不利于在本地运行，每次还得复制粘贴，编译运行，个人认为较为麻烦;
-  为后来者种一棵小树。

当前的文档还没有翻译完成，我也会找空闲的时间继续翻译。

## 版本
Eigen  3.3.7

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


## TODO
- 测试当前翻译的内容可编译通过
- 翻译：http://eigen.tuxfamily.org/dox/group__Sparse__chapter.html
- 翻译：http://eigen.tuxfamily.org/dox/group__Geometry__chapter.html
- 查缺补漏，提高翻译质量
  
## Contact
由于本人精力和水平有限，希望和大家一起讨论，欢迎想一起翻译的小伙伴。
qixianyu@buaa.edu.cn