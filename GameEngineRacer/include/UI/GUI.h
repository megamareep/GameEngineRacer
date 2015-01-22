#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <AntTweakBar.h>
#include "Scene\Scene.h"
#include <vector>

#include "ResourceManager.h"

enum SaveState { SAVE, DONTSAVE};


class GUI {
private:
	static SaveState save;
	float *x, *y, *z;
	float *xR, *yR, *zR;
	TwBar* bar;
	ResourceManager* rManager;
	bool* rotate;
	int width;
	int height;
	Scene* scene;

public:
	GUI();
	~GUI();
	bool setup(int w, int h, Scene* nScene );
	void onMouseMoved(double x, double y);
	void onMouseClicked(int bt, int action);
	void onKeyPressed(int key, int mod);
	void onResize(int w, int h);
	void draw();
	void saveData();
	static void TW_CALL RunCB(void *clientData);
	//bool getRotate()const{return rotate;};
};

#endif

