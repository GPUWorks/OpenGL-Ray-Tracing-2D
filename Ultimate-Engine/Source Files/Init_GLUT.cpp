/*-----------------------------------------------------------------------------
Author: Bîrzu George
Email:	b.gxg7@yahoo.com
Date:	08-11-2015
-----------------------------------------------------------------------------*/

#include "Init_GLUT.h"
#include "WindowsManager.h"


core::listeners::IListener* core::init::Init_GLUT::windowListener = NULL;
core::listeners::KeyListener* core::init::Init_GLUT::keyListener = NULL;
core::info::WindowInfo core::init::Init_GLUT::windowInformation;

int core::init::Init_GLUT::frame = 0;
int core::init::Init_GLUT::time;
int core::init::Init_GLUT::timebase = 0;


void core::init::Init_GLUT::init(
	const core::info::WindowInfo&  windowInfo,
	const core::info::ContextInfo& contextInfo,
	const core::info::FramebufferInfo& framebufferInfo)
{
	int fakeargc = 1;
	char *fakeargv[] = { "fake", NULL };

	glutInit(&fakeargc, fakeargv);

	if (contextInfo.isUsingContextCore())
	{
		glutInitContextVersion(contextInfo.getMajorVersion(), contextInfo.getMinorVersion());
		glutInitContextProfile(GLUT_CORE_PROFILE);
	}
	else
	{
		glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	}

	glutInitDisplayMode(framebufferInfo.getFlags());

	glutInitWindowPosition(windowInfo.get_X_position(), windowInfo.get_Y_position());
	glutInitWindowSize(windowInfo.getWidth(), windowInfo.getHeight());

	glutCreateWindow(windowInfo.getName().c_str());
	std::cout << "GLUT:\tInitialized" << std::endl;

	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);

	glutKeyboardFunc(keyboardDownCallback);
	glutKeyboardUpFunc(keyboardUpCallback);
	glutSpecialFunc(specialDownCallback);
	glutSpecialUpFunc(specialUpCallback);
	glutMotionFunc(motionCallback);
	glutPassiveMotionFunc(passiveMotionCallback);
	glutMouseFunc(mouseCallback);
	glutMouseWheelFunc(mouseWheelCallback);

	core::init::Init_GLEW::init();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);


	printOpenGLInfo(windowInfo, contextInfo);
}

void core::init::Init_GLUT::run()
{
	std::cout << "GLUT:\tStart Running  " << std::endl;
	glutMainLoop();
}


void core::init::Init_GLUT::close()
{
	std::cout << "GLUT:\tFinished" << std::endl;
	glutLeaveMainLoop();
}

void core::init::Init_GLUT::idleCallback(void)
{

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	managers::windows::WindowsManager::current_frame_no = frame;


	if (time - timebase > 1000) {
		float fps = (float) (frame * 1000.0 / (time - timebase));

		printf("FPS: %d", int(fps));

		managers::windows::WindowsManager::fps = int(fps);

		managers::windows::WindowsManager::current_frame_no = 0;
		timebase = time;
		frame = 0;
	}
	printf("\r\r\r\r\r\r\r");

	glutPostRedisplay();
}

void core::init::Init_GLUT::displayCallback()
{

	if (windowListener)
	{

		windowListener->notifyBeginFrame();
		windowListener->notifyDisplayFrame();

		glutSwapBuffers();

		windowListener->notifyEndFrame();
	}
}

void core::init::Init_GLUT::reshapeCallback(int width, int height)
{
	if (windowInformation.isReshapable()) {

		if (windowListener)
			windowListener->notifyReshape(width, height, windowInformation.getWidth(), windowInformation.getHeight());

		windowInformation.setWidth(width);
		windowInformation.setHeight(height);
	}
}

void core::init::Init_GLUT::closeCallback()
{

	close();
}

void core::init::Init_GLUT::enterFullscreen()
{

	glutFullScreen();
}

void core::init::Init_GLUT::exitFullscreen()
{

	glutLeaveFullScreen();
}

void core::init::Init_GLUT::printOpenGLInfo(const core::info::WindowInfo& windowInfo, const core::info::ContextInfo& contextInfo)
{

	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);


	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
	std::cout << "GLUT:\tInitial window is '" << windowInfo.getName() << "', with dimensions (" << windowInfo.getWidth()
		<< "X" << windowInfo.getHeight();
	std::cout << ") starts at (" << windowInfo.get_X_position() << "X" << windowInfo.get_Y_position();
	std::cout << ") and " << ((windowInfo.isReshapable()) ? "is" : "is not ") << " redimensionable" << std::endl;
	std::cout << "GLUT:\tInitial Framebuffer contains double buffers for" << std::endl;

	std::cout << "GLUT:\tOpenGL context is " << contextInfo.getMajorVersion() << "." << contextInfo.getMinorVersion();
	std::cout << " and profile is " << ((contextInfo.isUsingContextCore()) ? "core" : "compatibility") << std::endl;

	std::cout << "*****************************************************************" << std::endl;
}

void core::init::Init_GLUT::setWindowListener(core::listeners::IListener*& window_listener)
{
	windowListener = window_listener;
}

void core::init::Init_GLUT::setKeyListener(core::listeners::KeyListener*& key_listener)
{
	keyListener = key_listener;
}


void core::init::Init_GLUT::keyboardDownCallback(unsigned char key_pressed, int mouse_x, int mouse_y)
{
	if (keyListener) keyListener->notifyKeyPressed(key_pressed, mouse_x, mouse_y);
}

void core::init::Init_GLUT::keyboardUpCallback(unsigned char key_released, int mouse_x, int mouse_y)
{
	if (keyListener) keyListener->notifyKeyReleased(key_released, mouse_x, mouse_y);
}

void core::init::Init_GLUT::specialDownCallback(int key_pressed, int mouse_x, int mouse_y)
{
	if (keyListener) keyListener->notifySpecialKeyPressed(key_pressed, mouse_x, mouse_y);
}

void core::init::Init_GLUT::specialUpCallback(int key_released, int mouse_x, int mouse_y)
{
	if (keyListener) keyListener->notifySpecialKeyReleased(key_released, mouse_x, mouse_y);
}

void core::init::Init_GLUT::motionCallback(int mouse_x, int mouse_y)
{
	if (keyListener) keyListener->notifyMouseDrag(mouse_x, mouse_y);
}

void core::init::Init_GLUT::passiveMotionCallback(int mouse_x, int mouse_y)
{
	if (keyListener) keyListener->notifyMouseMove(mouse_x, mouse_y);
}

void core::init::Init_GLUT::mouseCallback(int button, int state, int mouse_x, int mouse_y)
{
	if (keyListener) keyListener->notifyMouseClick(button, state, mouse_x, mouse_y);
}

void core::init::Init_GLUT::mouseWheelCallback(int wheel, int direction, int mouse_x, int mouse_y)
{
	if (keyListener) keyListener->notifyMouseScroll(wheel, direction, mouse_x, mouse_y);
}