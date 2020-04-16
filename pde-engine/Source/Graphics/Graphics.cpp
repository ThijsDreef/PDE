#include "pde/Graphics/Graphics.h"
#include "glad/glad.h"

Graphics::Graphics(WindowParameters paramters) {
    initContext(paramters);
    windowParameters = paramters;
}

Graphics::~Graphics() {
    freeContext();
}

void Graphics::initContext(WindowParameters parameters) {
    static PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,						//version number
        PFD_DRAW_TO_WINDOW |	//format must support window
        PFD_SUPPORT_OPENGL |	//format must support opengl
        PFD_DOUBLEBUFFER,		//must support dubble buffering
        PFD_TYPE_RGBA,			// request an rgba format
        (unsigned char)32,					//select color depth
        0, 0, 0, 0, 0, 0,       //color bits ignored
        0,						//no alpha  buffer
        0,						//shift bit ignored
        0,						//no accumulation buffer
        0, 0, 0, 0,				//accumulation bits ignored
        32,						//32bit Z-Buffer (depth Buffer)
        0,						//no stencil buffer
        0,						//no Auxilliary buffer
        PFD_MAIN_PLANE,         //main drawing layer
        0,						//reserved
        0, 0, 0					//layer masks ignored
    };

    int pixelFormat;
    if (!(hDc = GetDC(parameters.hWnd))) {
        MessageBoxA(NULL, "cant create a GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    if (!(pixelFormat = ChoosePixelFormat(hDc, &pfd))) {
        MessageBoxA(NULL, "cant find a suitable pixel format", "ERROR", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    if (!SetPixelFormat(hDc, pixelFormat, &pfd)) {
        MessageBoxA(NULL, "cant set the pixelformat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    if (!(context = wglCreateContext(hDc))) {
        MessageBoxA(NULL, "cant create a GL rendering context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    if (!wglMakeCurrent(hDc, context)) {
        MessageBoxA(NULL, "can't activate the gl rendering context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
        return;
    }
    

//     if (GLAD_ARB && WGLEW_ARB_pixel_format)
//   {
//     int iContextAttribs[] =
//     {
//        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
//        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
//        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
//        0 // End of attributes list
//     };
//     wglMakeCurrent(NULL, NULL);
//     wglDeleteContext(context);
//     hRC = wglCreateContextAttribsARB(hDC, 0, iContextAttribs);
//     wglMakeCurrent(hDC, hRC);
//   }
    gladLoadGL();
}

void Graphics::update() {
    SwapBuffers(hDc);
}

void Graphics::freeContext() {
	if (context)
	{
		if (!wglMakeCurrent(NULL, NULL))
		{
			MessageBoxA(NULL, "Release of DC and RC failed", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(context))
		{
			MessageBoxA(NULL, "release Rendering Context failed.", "SHUTDOWN ERROR", MB_OK);
		}
		context = NULL;
	}
	if (hDc && !ReleaseDC(windowParameters.hWnd, hDc))
	{
		MessageBoxA(NULL, "release device context failed", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDc = NULL;
	}
}