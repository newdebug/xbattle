
//#define WIN32_LEAN_AND_MEAN
// Windows Header Files:
//#include <windows.h>
//#include <tchar.h>

// C RunTime Header Files
#include <platform/CCStdC.h>
#include <cocos2d.h>

#include "AppDelegate.h"

USING_NS_CC;

#ifdef _DEBUG
    #define _UNUSED(x)
#else
    #define _UNUSED(x) x
#endif

// 标准c++入口函数main需要工程配置为console类型
int main(int argc, char **argv)
{
    _UNUSED(argc);
    _UNUSED(argv);

    AppDelegate app;
    app.setResourceRootPath("../resources/");
    return app.run();
}

/*
// 标准win32入口,如果使用该入口函数，工程配置中去掉console类型
int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(nCmdShow);

    // create the application instance
    AppDelegate app;
    app.setResourceRootPath("../resources/");
    return app.run();
}
*/
