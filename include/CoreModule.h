#pragma once
#include <iostream>
namespace CoreModule {
	void TestEngine();
	void InitializeWindow(int width, int height, const char* windowName);
	void Start();

	//IMGUI
	void CustomWindow();
	void Render();
	void CleanUp();

	void Exit();

	extern int FPS;
}