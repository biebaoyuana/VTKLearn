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
//2-4
#include <vtkJPEGReader.h>
#include <vtkTexture.h>
#include <vtkPlaneSource.h>

//./RenderCylinder ../texture.jpg 
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout<<argv[0]<<" "<<"TextureFile(*.jpg)"<<std::endl;
		return EXIT_FAILURE;
	}
    // vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    // cylinder->SetHeight(3.0);
    // cylinder->SetRadius(1.0);
    // cylinder->SetResolution(10);//set 分辨率

    // vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    // //GetOutputPort用于获取cylinder对象的输出端口
    // cylinderMapper->SetInputConnection(cylinder->GetOutputPort());//将cylinder对象的输出端口连接到cylinderMapper的输入端口

    // vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    // cylinderActor->SetMapper(cylinderMapper);

    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    // renderer->AddActor(cylinderActor);
    renderer->SetBackground(0.1, 0.2, 0.4);


    //2-4 add texture
    vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
    reader->SetFileName(argv[1]);

    vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
    texture->SetInputConnection(reader->GetOutputPort());
    texture->InterpolateOn();

    vtkSmartPointer<vtkPlaneSource> plan = vtkSmartPointer<vtkPlaneSource>::New();
    vtkSmartPointer<vtkPolyDataMapper> planMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    planMapper->SetInputConnection(plan->GetOutputPort());

    vtkSmartPointer<vtkActor> planActor = vtkSmartPointer<vtkActor>::New();
    planActor->SetMapper(planMapper);
    planActor->SetTexture(texture);

    renderer->AddActor(planActor);
    renderer->ResetCamera();

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