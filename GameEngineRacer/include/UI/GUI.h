#ifndef GUI_H
#define GUI_H


#include <stdio.h>
#include <AntTweakBar.h>
#include "Scene\Scene.h"
#include <vector>
#include <assert.h>
#include "3rdParty\gl_core_4_3.hpp"
#include "glfw3.h"
#include <commdlg.h>
#include "ResourceManager.h"
#include <fstream>


enum SaveState { SAVE, DONTSAVE};
enum FileState { OPEN, DONTOPEN};

class GUI {
private:
	static FileState load;
	static SaveState save;
	float *x, *y, *z;
	float *xR, *yR, *zR;
	TwBar* bar;
	ResourceManager* rManager;
	int width;
	int height;
	Scene* scene;
	Json::StyledWriter writer;
public:
	GUI();
	~GUI();
	bool setup(int w, int h, Scene* nScene );
	void onMouseMoved(double x, double y);
	void onMouseClicked(int bt, int action);
	void onKeyPressed(int key, int mod);
	void onResize(int w, int h);
	void draw();
	void saveData(Scene* nscene);
	void openFile();
	static void TW_CALL Save(void *clientData);
	static void TW_CALL OpenFile(void *clientData);
	//bool getRotate()const{return rotate;};
};

#endif

