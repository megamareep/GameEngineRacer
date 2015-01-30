#include <assert.h>
#include "3rdParty\gl_core_4_3.hpp"
#include "glfw3.h"
#include "UI\GUI.h"
#include <fstream>

SaveState GUI::save = DONTSAVE;

GUI::GUI() :width(0),height(0)
{
	rManager = ResourceManager::getInstance();

}
GUI::~GUI()
{
	delete[] rotate;
	delete[] x;
	delete[] y;
	delete[] z;
	TwTerminate();
}
void TW_CALL GUI::RunCB(void *clientData)
{ 
	save = SAVE;
}
void GUI::saveData()
{
	//std::ofstream output;
	//switch(save)
	//{
	//case SAVE:

	//	output.open ("Scene/"+scene->getFileName()+".txt", std::fstream::out);
	//	if(!output.is_open())
	//	{
	//		std::cout << "filenotOpen";
	//		return;
	//	}

	//	for(unsigned int i = 0; i < scene->GetGameObjects().size(); ++i)
	//	{ 
	//		std::string animComp = "NULL";
	//			std::string animSide = "NULL";
	//		if(i >= 5){
	//			
	//			if(scene->GetGameObjects().at(i)->getAnimComp())
	//			{
	//				animComp = "animComp";

	//				if(!scene->GetGameObjects().at(i)->getAnimComp()->getState())
	//				{
	//					animSide = "RIGHT";
	//				}
	//				else animSide = "LEFT";
	//			}
	//			output << "scene "<< scene->GetGameObjects().at(i)->getName()+" " << 
	//				scene->GetGameObjects().at(i)->getTransformComp()->getTranslate().x <<" "<< scene->GetGameObjects().at(i)->getTransformComp()->getTranslate().y <<" "<< scene->GetGameObjects().at(i)->getTransformComp()->getTranslate().z <<" "<<
	//				scene->GetGameObjects().at(i)->getTransformComp()->getRotate().x <<" "<< scene->GetGameObjects().at(i)->getTransformComp()->getRotate().y <<" "<< scene->GetGameObjects().at(i)->getTransformComp()->getRotate().z <<" "<< 
	//				scene->GetGameObjects().at(i)->getTransformComp()->getScale().x <<" "<< scene->GetGameObjects().at(i)->getTransformComp()->getScale().y <<" "<< scene->GetGameObjects().at(i)->getTransformComp()->getScale().z <<" "<< 
	//				scene->GetGameObjects().at(i)->getIDs().shaderID <<" "<< scene->GetGameObjects().at(i)->getIDs().modelID <<" "<< scene->GetGameObjects().at(i)->getIDs().textureID <<" "<<
	//				animComp <<" "<< animSide <<" "<< std::endl;
	//		}
	//		else 
	//		{
	//			if(scene->GetGameObjects().at(i)->getAnimComp())
	//			{
	//				animComp = "animComp";

	//				if(!scene->GetGameObjects().at(i)->getAnimComp()->getState())
	//				{
	//					animSide = "RIGHT";
	//				}
	//				else animSide = "LEFT";
	//			}
	//			float rotateZ = 0;
	//			if(scene->GetGameObjects().at(i)->getName() == "RightLeg")
	//			{
	//				rotateZ = -10;
	//			}
	//			else if(scene->GetGameObjects().at(i)->getName() == "LeftLeg")
	//			{
	//				rotateZ = 8;
	//			}
	//			else
	//				{
	//					rotateZ =0;
	//			}

	//			output << "scene "<< scene->GetGameObjects().at(i)->getName()+" " << 
	//				0 <<" "<< 6 <<" "<< 0 <<" "<<
	//				0 <<" "<< 0 <<" "<< rotateZ <<" "<< 
	//				0.2 <<" "<< 0.2 <<" "<< 0.2 <<" "<< 
	//				scene->GetGameObjects().at(i)->getIDs().shaderID <<" "<< scene->GetGameObjects().at(i)->getIDs().modelID <<" "<< scene->GetGameObjects().at(i)->getIDs().textureID <<" "<<
	//				animComp <<" "<< animSide <<" "<< std::endl;
	//			/*scene Body 0 6 0 0 0 0 0.2 0.2 0.2 0 4 1 NULL NULL
	//			scene RightArm 0 6 0 0 0 0 0.2 0.2 0.2 0 0 1 animComp RIGHT
	//			scene LeftArm 0 6 0 0 0 0 0.2 0.2 0.2 0 2 1 animComp LEFT
	//			scene RightLeg 0 6 0 0 0 -10 0.2 0.2 0.2 0 1 1 animComp RIGHT
	//			scene LeftLeg 0 6 0 0 0 10 0.2 0.2 0.2 0 3 1 animComp LEFT*/
	//		}

	//	};
	//	output.close();
	//	save = DONTSAVE;
	//	break;
	//case DONTSAVE:
	//	break;
	//}
}
bool GUI::setup(int w, int h, Scene* nScene ) {
	width = w;
	height = h;
	scene = nScene;
	// glfwGetWindowAttrib
	//onResize(w,h);
	TwInit(TW_OPENGL, NULL);
	bar = TwNewBar("GameEngine Tester");

	rotate = new bool[nScene->GetGameObjects().size()];
	x = new float[nScene->GetGameObjects().size()];
	y = new float[nScene->GetGameObjects().size()];
	z = new float[nScene->GetGameObjects().size()]; 
	xR = new float[nScene->GetGameObjects().size()];
	yR = new float[nScene->GetGameObjects().size()];
	zR = new float[nScene->GetGameObjects().size()]; 


	/*bool hit;
	TwAddVarRO(bar, "Hit", TW_TYPE_BOOLCPP, &hit, " group=Color ");  // Hit is put into group Properties (Properties is created)
	int red;
	TwAddVarRW(bar, "Red", TW_TYPE_UINT8, &red, " group=Color ");        // Red is put into group Color (Color is created)
	*/
	int j = 0 ;
	for(unsigned int i = 5; i < nScene->GetGameObjects().size(); ++i)
	{   
		rotate[i]=false;
		x[i] = 0.f;
		y[i] = 0.f;
		z[i] = 0.f;
		xR[i] = 0.f;
		yR[i] = 0.f;
		zR[i] = 0.f;
		std::string xS = std::to_string(j);
		std::string yS = std::to_string(j+1);
		std::string zS = std::to_string(j+2);
		std::string rS = std::to_string(j+3);
		std::string xRS = std::to_string(j+4);
		std::string yRS = std::to_string(j+5);
		std::string zRS = std::to_string(j+6);
		std::string str =" min=-1000 max=1000 step=0.5 label='Translate X' group="+nScene->GetGameObjects().at(i)->getName();
		std::string str1 =" min=-1000 max=1000 step=0.5 label='Translate Y' group="+nScene->GetGameObjects().at(i)->getName();
		std::string str2 =" min=-1000 max=1000 step=0.5 label='Translate Z' group="+nScene->GetGameObjects().at(i)->getName();
		std::string rStr =" min=-1000 max=1000 step=1.0 label='Rotate X' group="+nScene->GetGameObjects().at(i)->getName();
		std::string rStr1 =" min=-1000 max=1000 step=1.0 label='Rotate Y' group="+nScene->GetGameObjects().at(i)->getName();
		std::string rStr2 =" min=-1000 max=1000 step=1.0 label='Rotate Z' group="+nScene->GetGameObjects().at(i)->getName();
		std::string rot ="help='Rotate' label=AutoRotate group="+nScene->GetGameObjects().at(i)->getName();
		const char * s = str.data();
		const char * s1 = str1.data();
		const char * s2 = str2.data();
		const char * r = rStr.data();
		const char * r1 = rStr1.data();
		const char * r2 = rStr2.data();
		const char * ar = rot.data();
		//TwAddVarRW(bar, rS.c_str(), TW_TYPE_BOOL8, &rotate[i], ar);
		TwAddVarRW(bar, xS.c_str(), TW_TYPE_FLOAT, &x[i] ,s );
		TwAddVarRW(bar, yS.c_str(), TW_TYPE_FLOAT, &y[i] ,s1 );
		TwAddVarRW(bar, zS.c_str(), TW_TYPE_FLOAT, &z[i] ,s2 );
		TwAddVarRW(bar, xRS.c_str(), TW_TYPE_FLOAT, &xR[i] ,r );
		TwAddVarRW(bar, yRS.c_str(), TW_TYPE_FLOAT, &yR[i] ,r1 );
		TwAddVarRW(bar, zRS.c_str(), TW_TYPE_FLOAT, &zR[i] ,r2 );
		j+=7;

		x[i] = scene->GetGameObjects().at(i)->getTransformComp()->getTranslate().x;
		y[i] = scene->GetGameObjects().at(i)->getTransformComp()->getTranslate().y;
		z[i] = scene->GetGameObjects().at(i)->getTransformComp()->getTranslate().z;
		xR[i] = scene->GetGameObjects().at(i)->getTransformComp()->getRotate().x;
		yR[i] = scene->GetGameObjects().at(i)->getTransformComp()->getRotate().y;
		zR[i] = scene->GetGameObjects().at(i)->getTransformComp()->getRotate().z;

	}


	// ...
	TwAddButton(bar, "Run", RunCB, NULL , " label='Save Scene' ");
	TwWindowSize(width, height);
	return true;
}

void GUI::onResize(int w, int h) {
	width = w;
	height = h;
	TwWindowSize(w, h);
}

void GUI::onMouseMoved(double x, double y) {
	TwMouseMotion((int)x, (int)y);
}

void GUI::onMouseClicked(int bt, int action) {
	TwMouseButtonID btn = (bt == 0) ? TW_MOUSE_LEFT : TW_MOUSE_RIGHT;
	TwMouseAction ma = (action == GLFW_PRESS) ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED;
	TwMouseButton(ma, btn);
}

void GUI::onKeyPressed(int key, int mod) {

	switch(key) {
	case GLFW_KEY_LEFT: key = TW_KEY_LEFT; break;
	case GLFW_KEY_RIGHT: key = TW_KEY_RIGHT; break;
	case GLFW_KEY_UP: key = TW_KEY_UP; break;
	case GLFW_KEY_DOWN: key = TW_KEY_DOWN; break;
	default: break;
	}

	int tw_mod = TW_KMOD_NONE;

	if(mod & GLFW_MOD_SHIFT) {
		tw_mod |= TW_KMOD_SHIFT;
	}

	if(mod & GLFW_MOD_CONTROL) {
		tw_mod |= TW_KMOD_CTRL;
	}

	if(mod & GLFW_MOD_ALT) {
		tw_mod |= TW_KMOD_ALT;
	}

	TwKeyPressed(key, TW_KMOD_NONE);
}

void GUI::draw() {
	/*static bool pressed = false;
	/*if(keys[key] == GLFW_PRESS && !pressed)
	{
	pressed = true;
	return true;
	}
	else if(keys[key] == GLFW_RELEASE )
	{
	pressed = false;
	return false;	
	}
	else return false;*/

	if(scene)
	{
		for(unsigned int i = 5; i < scene->GetGameObjects().size(); ++i)
		{   
			//scene->GetGameObjects().at(i)->getTransformComp()->getTranslate() = glm::vec3(x[i],y[i],z[i]);
			//scene->GetGameObjects().at(i)->getTransformComp()->getRotate() = glm::vec3(xR[i],yR[i],zR[i]);

		}
	}

	TwDraw();
}
