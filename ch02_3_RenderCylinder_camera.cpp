#include <vtkSmartPointer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkCylinderSource.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleTrackballCamera.h>
//2-2
#include <vtkLight.h>

int main()
{
    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetHeight(3.0);
    cylinder->SetRadius(1.0);
    cylinder->SetResolution(10);//set 分辨率

    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    //GetOutputPort用于获取cylinder对象的输出端口
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());//将cylinder对象的输出端口连接到cylinderMapper的输入端口

    vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(cylinderActor);
    renderer->SetBackground(0.1, 0.2, 0.4);

    //2-2 add light 
    vtkSmartPointer<vtkLight> myLight = vtkSmartPointer<vtkLight>::New();
    myLight->SetColor(0, 1, 0);
    myLight->SetPosition(0, 0, 1);
    myLight->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
    renderer->AddLight(myLight);

    vtkSmartPointer<vtkLight> myLight2 = vtkSmartPointer<vtkLight>::New();
    myLight2->SetColor(1, 0, 1);
    myLight2->SetPosition(0, 0, -1);
    myLight2->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
    renderer->AddLight(myLight2);

    //2-3 add camera
    vtkSmartPointer<vtkCamera> myCamera = vtkSmartPointer<vtkCamera>::New();
    myCamera->SetClippingRange(0.0475, 2.3786);
    myCamera->SetFocalPoint(0.0573, -0.2134, -0.0523);
    myCamera->SetPosition(0.3245, -0.1139, -0.2932);
    myCamera->SetViewUp(-0.2234, 0.9983, 0.0345);
    renderer->SetActiveCamera(myCamera);

    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
    renWin->AddRenderer(renderer);
    renWin->SetSize(300, 300);

    vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    iren->SetRenderWindow(renWin);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    iren->SetInteractorStyle(style);

    iren->Initialize();
    iren->Start();

    return 0;


}