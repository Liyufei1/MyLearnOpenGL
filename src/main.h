#pragma once
#include "Common/CommonFunLib.h"
#include "Window/Window.h"

int main()
{
	Window window(1920, 1080, "OpenGL");
	window.Init();


	window.SetRunFunction([](){
		// lyf::Print("run~!~~");
	});
	window.Run();




	window.Close();	
	return 0;
}
