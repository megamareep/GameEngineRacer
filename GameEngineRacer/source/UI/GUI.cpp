#include "UI\GUI.h"

SaveState GUI::save = DONTSAVE;
FileState GUI::load = DONTOPEN;

GUI::GUI() :width(0),height(0)
{
	rManager = ResourceManager::getInstance();

}

GUI::~GUI()
{
	delete[] x;
	delete[] y;
	delete[] z;
	x = NULL;
	y= NULL;
	z = NULL;
	TwTerminate();
}

void TW_CALL GUI::Save(void *clientData)
{ 
	save = SAVE;
}

void TW_CALL GUI::OpenFile(void *clientData)
{
	load = OPEN;
}

void GUI::openFile()
{
	if(load == OPEN)
	{
		OPENFILENAME ofn={0};
		char szFileName[MAX_PATH]={0};
		ofn.lStructSize=sizeof(OPENFILENAME);
		ofn.Flags=OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
		ofn.lpstrFilter = "Obj Files\0*.OBJ\0Scene Files\0*.scn\0";
		ofn.lpstrFile=szFileName;
		ofn.nMaxFile=MAX_PATH;
		::GetOpenFileName(&ofn);

		std:: cout << ofn.lpstrFile << std::endl;
		load = DONTOPEN;
	}

}

void GUI::saveData(Scene* nscene)
{ 
	if(save == SAVE)
	{

		OPENFILENAME ofn={0};
		char szFileName[MAX_PATH]={0};
		ofn.lStructSize=sizeof(OPENFILENAME);
		ofn.Flags=OFN_EXPLORER;
		ofn.lpstrFilter="Scene Files (*.scn)\0";
		ofn.lpstrFile=szFileName;
		ofn.nMaxFile=MAX_PATH;
		ofn.lpstrDefExt = "scn";

		GetSaveFileName(&ofn);
		
		scene = nscene;
		std::ofstream myfile;
		myfile.open (ofn.lpstrFile);
		myfile << writer.write( scene->createJson() );
		myfile.close();
		save = DONTSAVE;
	}
}

bool GUI::setup(int w, int h, Scene* nScene ) {
	width = w;
	height = h;
	scene = nScene;

	TwInit(TW_OPENGL, NULL);
	bar = TwNewBar("GameEngine");

	x = new float[nScene->GetGameObjects().size()];
	y = new float[nScene->GetGameObjects().size()];
	z = new float[nScene->GetGameObjects().size()]; 
	xR = new float[nScene->GetGameObjects().size()];
	yR = new float[nScene->GetGameObjects().size()];
	zR = new float[nScene->GetGameObjects().size()]; 


	int j = 0 ;
	for(unsigned int i = 0; i < nScene->GetGameObjects().size(); ++i)
	{   
		x[i] = 0.f;
		y[i] = 0.f;
		z[i] = 0.f;
		xR[i] = 0.f;
		yR[i] = 0.f;
		zR[i] = 0.f;
		std::string xS = std::to_string(j++);
		std::string yS = std::to_string(j++);
		std::string zS = std::to_string(j++);
		std::string rS = std::to_string(j++);
		std::string xRS = std::to_string(j++);
		std::string yRS = std::to_string(j++);
		std::string zRS = std::to_string(j++);
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

		if(nScene->GetGameObjects().at(i)->getEntityType() == "light")
		{
			std::string grouping = "GameEngine/"+nScene->GetGameObjects().at(i)->getName()+"  group='Lights' opened='false'     \n" ;
			TwDefine(grouping.c_str());  
		}
		else{
			std::string grouping = "GameEngine/"+nScene->GetGameObjects().at(i)->getName()+"  group='Objects'  opened='false'   \n" ;
			TwDefine(grouping.c_str());  
		}
		TwDefine("GameEngine/Objects opened='false'");  
		TwDefine("GameEngine/Lights opened='false'");  

		x[i] = scene->GetGameObjects().at(i)->getTransformComp()->getTranslate().x;
		y[i] = scene->GetGameObjects().at(i)->getTransformComp()->getTranslate().y;
		z[i] = scene->GetGameObjects().at(i)->getTransformComp()->getTranslate().z;
		xR[i] = scene->GetGameObjects().at(i)->getTransformComp()->getRotate().x;
		yR[i] = scene->GetGameObjects().at(i)->getTransformComp()->getRotate().y;
		zR[i] = scene->GetGameObjects().at(i)->getTransformComp()->getRotate().z;

	}


	TwAddButton(bar, "Saving", Save, NULL , " label='Save Scene' ");
	TwAddButton(bar, "OpenFiles", OpenFile, NULL , " label='Open File' ");
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

	if(scene)
	{
		int j =0;
		for(unsigned int i = 0; i < scene->GetGameObjects().size(); ++i)
		{   
			scene->GetGameObjects().at(i)->getTransformComp()->setTranslate(glm::vec3(x[i],y[i],z[i]));
			scene->GetGameObjects().at(i)->getTransformComp()->setRotate(glm::vec3(xR[i],yR[i],zR[i])) ;
			if(scene->GetGameObjects().at(i)->getEntityType() == "light")
			{
				scene->getLights().at(j++).position = glm::vec3(x[i],y[i],z[i]);
			}

		}

	}

	TwDraw();
}
