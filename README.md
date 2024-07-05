# Learn VTK
## 1、初识VTK
VTK最初是教科书The Visualization Toolkit An Object-Oriented Approach to 3D Graphics的部分。威尔·施罗德、肯·马丁和比尔·洛伦森——三名图形和可视化研究人员——从1993年12月开始，在他们自己的时间编写了这本书和配套软件，并得到了他们当时的雇主通用电气研发公司的法律许可。这本书的动机是与其他研究人员合作，开发一个开放的框架来创建前沿的可视化和图形应用程序。
VTK源于作者在通用电气的经验，特别是LYMB面向对象的图形系统。其他影响包括由施罗德等人开发的视觉可视化系统。伦斯勒理工学院开发的面向对象的计算机动画系统；以及比尔·洛伦森合著的面向对象建模与设计书。
在VTK的核心被编写出来之后，世界各地的用户和开发人员开始改进系统并将系统应用于现实世界的问题。特别是，通用电气医疗系统公司和其他通用电气业务对该系统做出了贡献，佩妮·莱茵汉斯博士等研究人员开始用这本书进行教学。其他早期的支持者包括洛斯阿拉莫斯国家实验室的吉姆·阿伦斯和慷慨的石油和天然气支持者。
为了创建一个大的，活跃的，全球社区，肯和威尔连同丽莎阿维拉，查尔斯法律和比尔·霍夫曼离开通用电气在1998年创建Kitware公司.从那时起，成百上千的额外的开发人员把VTK变成现在世界上首屈一指的可视化系统。例如，Sandia国家实验室一直是一个强有力的支持者和共同开发者，他们改进了VTK中的2D图表和信息可视化。


VTK的主要特点包括：

- 跨平台：VTK可以在多种操作系统上运行，包括Windows、Linux、Mac OS X等。
- 开源：VTK是开源软件，可以自由地使用、修改和分发。
- 丰富的功能：VTK提供了丰富的功能，包括数据读取、数据转换、数据可视化、图像处理等。
- 强大的社区支持：VTK有一个活跃的社区，提供了大量的文档、教程和示例代码，可以帮助用户快速上手和使用VTK。
- 易于扩展：VTK的设计使得用户可以很容易地添加新的功能或模块。
- 高性能：VTK使用了高效的算法和数据结构，可以处理大规模的数据和复杂的计算。
- 支持多种编程语言：VTK提供了C++、Python、Java、Tcl等语言的接口，用户可以根据自己的需求选择合适的编程语言。
- 支持多种数据格式：VTK支持多种数据格式，包括VTK、STL、OBJ、PNG、JPEG等，可以方便地读取和保存各种类型的数据。
- 支持多种可视化技术：VTK提供了多种可视化技术，包括体绘制、表面绘制、切片、点云绘制等，可以满足各种可视化需求。
- 支持多种交互方式：VTK提供了多种交互方式，包括鼠标、键盘、触摸屏等，可以方便地与用户进行交互。

## 2、一个简单的VTK程序
```c++
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

int main()
{
    // 创建一个球体数据源
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetCenter(0, 0, 0);
    sphereSource->SetRadius(5);

    // 创建一个多边形数据映射器
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    // 创建一个演员
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    // 创建一个渲染器
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);

    // 创建一个渲染窗口
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    // 创建一个渲染窗口交互器
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    // 启动渲染窗口交互器
    interactor->Initialize();
    interactor->Start();

    return 0;
}
```
这个程序创建了一个球体，并将其显示在一个渲染窗口中。程序首先创建了一个球体数据源，然后创建了一个多边形数据映射器，将球体数据源连接到映射器中。接着创建了一个演员，将映射器连接到演员中。然后创建了一个渲染器，将演员添加到渲染器中。接着创建了一个渲染窗口，将渲染器添加到渲染窗口中。最后创建了一个渲染窗口交互器，将渲染窗口连接到交互器中，并启动交互器。

vtkActor类表示一个可以渲染的物体，vtkPolyDataMapper类将数据源转换为可以渲染的格式，vtkRenderer类表示一个渲染场景，vtkRenderWindow类表示一个渲染窗口，vtkRenderWindowInteractor类表示一个渲染窗口交互器。
vtkActor派生自vtkProp类，渲染场景中数据的可视化通过vtkProp类实现，vtkProp类派生自vtkObject类，vtkObject类是VTK中所有类的基类。如若要选软一个柱体，柱体的数据是vtkPolyData，数据要在场景中渲染时，不是直接将该数据加入渲染场景，而是以vtkProp的形式存在于渲染场景中，三维中最常用的vtkProp子类有vtkActor(几何数据)和vtkVolume(体数据)。vtkProp的子类负责确定渲染场景中的位置、大小、方向等信息，prop依赖于两个对象，一个是Mapper，另一个是Property。Mapper负责将数据转换为可以渲染的格式，存放数据和渲染信息，Property负责确定渲染场景中的颜色、材质、光照等信息。Mapper是可视化管线的末端。

## 2.2 三维场景的基本要素
### 2.2.1 灯光
VTK中使用类vtkLight来表示渲染场景中的光源，可以使用vtkLight来设置光源的属性，vtkLight实例可以打开、关闭，设置灯光的颜色、照射位置（焦点）、灯光所在的位置，强度等。

vtkLight可以分成两类：点光源（Position Light 位置光源/聚光灯）和平行光源（Direction Light 方向光源）。点光源是向各个方向均匀发射光线，可以指定灯光的衰减值、锥角等，而平行光源是指光源在无穷远处，因此将光线视为平行。

光源的位置和焦点的连线定义光线的方向，默认vtkLight为平行光源。
常用的方法有:
```c++
void SetColor(double r, double g, double b); //设置光源的颜色
void SetPosition(double x, double y, double z); //设置光源的位置
void SetFocalPoint(double x, double y, double z); //设置光源的焦点
void SetIntensity(double intensity); //设置光源的强度
void SetConeAngle(double angle); //设置光源的锥角
void SetAttenuation(double constant, double linear, double quadratic); //设置光源的衰减值
void SetLightTypeToPositional(); //设置光源为点光源
void SetLightTypeToDirectional(); //设置光源为平行光源
```
示例见:ch02_2_RenderCylinder_light.cpp
该示例定义了链哥哥vtkLight对象，一个为绿色光，位置在(0,0,1)，一个为蓝色光，位置在(0,0,1-1)焦点都对这相机的焦点。最后用vtkRenderer将灯光对象加载进渲染场景中。一个vtkRenderer可以有多个灯光。

### 2.2.2 相机


### 2.2.3 颜色
### 2.2.4 纹理映射

    