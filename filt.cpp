#include <iostream>
using namespace std;
#include "string.h"

#include "OIIOServices.h"
#include "GLView.h"
#include "KernalData.h"


ImageData *g_pInImage = NULL, *g_pOutImage = NULL;
KernelData *g_pKernel = NULL;

void DisplayInput() {

	GLView::SetImageToDisplay(*g_pInImage);
	glutReshapeWindow(g_pInImage->GetWidth(), g_pInImage->GetHeight());
	GLView::DisplayImage();
	//glutPostRedisplay();
}


void DisplayOutput() {

	GLView::SetImageToDisplay(*g_pOutImage);
	glutReshapeWindow(g_pOutImage->GetWidth(), g_pOutImage->GetHeight());
	GLView::DisplayImage();

}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	if( 3 > argc){
		cout << " filename not entered" << endl;
		cout << " please enter the in below format:" << endl;
		cout << " ./filt Imagename.png Outputfilename.png" << endl;
		return 0;
	}

	char *pImageName = argv[1];
	char *pFiltname = argv[2];

	g_pInImage = new ImageData(pImageName);


	g_pKernel = new KernelData();
	g_pKernel->ReadFile(pFiltname);
	
	
	g_pOutImage = g_pInImage->ConvolveWith(g_pKernel);

	
	GLView::SetImageToDisplay(*g_pInImage);
	GLView::Init(pImageName);
	glutDisplayFunc(DisplayInput);
	
	GLView::SetImageToDisplay(*g_pOutImage);
	char pOUTFilename[] = "OUTPUT Result";
	GLView::Init(pOUTFilename);
	glutDisplayFunc(DisplayOutput);
	
	glutMainLoop();

	delete g_pInImage;
	delete g_pOutImage;
	delete g_pKernel;

	return 0;
}