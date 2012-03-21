#include "StdAfx.h"
#include "GlfwInput.h"
#include "Gdx.h"

const int KeyEvent::KEY_DOWN = 0;
const int KeyEvent::KEY_UP = 1;
const int KeyEvent::KEY_TYPED = 2;



GlfwInput::GlfwInput(void)
{
	m_touchDown = false;
	m_justTouched = false;
	m_touchX = m_touchY = 0;

	processor = NULL;
}

void GlfwInput::init()
{
	::glfwSetMouseButtonCallback(mouseButtonEvent);
	::glfwSetKeyCallback(keyboardEvent);
}

GlfwInput::~GlfwInput(void)
{
}


/** @return The value of the accelerometer on its x-axis. ranges between [-10,10]. */
float GlfwInput::getAccelerometerX()
{
	return 0.f;
}

/** @return The value of the accelerometer on its y-axis. ranges between [-10,10]. */
float GlfwInput::getAccelerometerY()
{
	return 0.f;
}

/** @return The value of the accelerometer on its y-axis. ranges between [-10,10]. */
float GlfwInput::getAccelerometerZ()
{
	return 0.f;
}

/** @return the last touch x coordinate in screen coordinates. The screen origin is the top left corner. */
int GlfwInput::getX()
{
	return m_touchX;
}

/** Returns the x coordinate in screen coordinates of the given pointer. Pointers are indexed from 0 to n. The pointer id
* identifies the order in which the fingers went down on the screen, e.g. 0 is the first finger, 1 is the second and so on.
* When two fingers are touched down and the first one is lifted the second one keeps its index. If another finger is placed on
* the touch screen the first free index will be used.
*
* @param pointer the pointer id.
* @return the x coordinate */
int GlfwInput::getX(int pointer)
{
	//TODO:
	return -1;
}

/** @return the different between the current pointer location and the last pointer location on the x-axis. */
int GlfwInput::getDeltaX()
{
	//TODO:
	return -1;
}

/** @return the different between the current pointer location and the last pointer location on the x-axis. */
int GlfwInput::getDeltaX(int pointer)
{
	//TODO:
	return -1;
}

/** @return the last touch y coordinate in screen coordinates. The screen origin is the top left corner. */
int GlfwInput::getY()
{
	return m_touchY;
}


/** Returns the y coordinate in screen coordinates of the given pointer. Pointers are indexed from 0 to n. The pointer id
* identifies the order in which the fingers went down on the screen, e.g. 0 is the first finger, 1 is the second and so on.
* When two fingers are touched down and the first one is lifted the second one keeps its index. If another finger is placed on
* the touch screen the first free index will be used.
*
* @param pointer the pointer id.
* @return the y coordinate */
int GlfwInput::getY(int pointer)
{
	//TODO:
	return -1;
}


/** @return the different between the current pointer location and the last pointer location on the y-axis. */
int GlfwInput::getDeltaY()
{
	//TODO:
	return -1;
}

/** @return the different between the current pointer location and the last pointer location on the y-axis. */
int GlfwInput::getDeltaY(int pointer)
{
	//TODO:
	return -1;
}

/** @return whether the screen is currently touched. */
bool GlfwInput::isTouched()
{
	return m_touchDown;
}

/** @return whether a new touch down event just occured. */
bool GlfwInput::justTouched()
{
	bool ret = m_justTouched;
	m_justTouched = false;
	return ret;
}

/** Whether the screen is currently touched by the pointer with the given index. Pointers are indexed from 0 to n. The pointer
* id identifies the order in which the fingers went down on the screen, e.g. 0 is the first finger, 1 is the second and so on.
* When two fingers are touched down and the first one is lifted the second one keeps its index. If another finger is placed on
* the touch screen the first free index will be used.
*
* @param pointer the pointer
* @return whether the screen is touched by the pointer */
bool GlfwInput::isTouched(int pointer)
{
	//TODO:
	return false;
}

/** Whether a given button is pressed or not. Button constants can be found in {@link Buttons}. On Mobile only the Button#LEFT
* constant is meaningful.
* @param button the button to check.
* @return whether the button is down or not. */
bool GlfwInput::isButtonPressed(int button)
{
	//TODO:
	return false;
}

/** Returns whether the key is pressed.
*
* @param key The key code as found in {@link Input.Keys}.
* @return true or false. */
bool GlfwInput::isKeyPressed(int key)
{
	std::set<int>::iterator it = m_keys.find(key);
	return it != m_keys.end();
}

/** System dependent method to input a string of text. A dialog box will be created with the given title and the given text as a
* message for the user. Once the dialog has been closed the provided {@link TextInputListener} will be called but not
* necessarily in the rendering thread in which all the {@link ApplicationListener} methods are called. You have to synchronize
* this yourself.
*
* @param listener The TextInputListener.
* @param title The title of the text input dialog.
* @param text The message presented to the user. */
void GlfwInput::getTextInput(TextInputListener* listener, const std::string& title, const std::string& text)
{
	//TODO:
}

/** Sets the on-screen keyboard visible if available.
*
* @param visible visible or not */
void GlfwInput::setOnscreenKeyboardVisible(bool visible)
{
}

/** Vibrates for the given amount of time. Note that you'll need the permission
* <code> <uses-permission android:name="android.permission.VIBRATE" /></code> in your manifest file in order for this to work.
*
* @param milliseconds the number of milliseconds to vibrate. */
void GlfwInput::vibrate(int milliseconds)
{
}

/** Vibrate with a given pattern. Pass in an array of ints that are the times at which to turn on or off the vibrator. The first
* one is how long to wait before turning it on, and then after that it alternates. If you want to repeat, pass the index into
* the pattern at which to start the repeat.
* @param pattern an array of longs of times to turn the vibrator on or off.
* @param repeat the index into pattern at which to repeat, or -1 if you don't want to repeat. */
void GlfwInput::vibrate(long pattern[], int patternLength, int repeat)
{
}

/** Stops the vibrator */
void GlfwInput::cancelVibrate()
{
}

/** The azimuth is the angle of the device's orientation around the z-axis. The positive z-axis points towards the earths
* center.
*
* @see <a
*      href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])</a>
* @return the azimuth in degrees */
float GlfwInput::getAzimuth()
{
	return 0;	
}

/** The pitch is the angle of the device's orientation around the x-axis. The positive x-axis roughly points to the west and is
* orthogonal to the z- and y-axis.
* @see <a
*      href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])</a>
* @return the pitch in degrees */
float GlfwInput::getPitch()
{
	return 0;	
}

/** The roll is the angle of the device's orientation around the y-axis. The positive y-axis points to the magnetic north pole
* of the earth.
* @see <a
*      href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])</a>
* @return the roll in degrees */
float GlfwInput::getRoll()
{
	return 0;	
}
/**
* Returns the rotation matrix describing the devices rotation as per <a href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">SensorManager#getRotationMatrix(float[], float[], float[], float[])</a>.
* Does not manipulate the matrix if the platform does not have an accelerometer.
* @param matrix
*/
void GlfwInput::getRotationMatrix(float matrix[16])
{
}

/** @return the time of the event currently reported to the {@link InputProcessor}. */
long GlfwInput::getCurrentEventTime()
{
	//TODO:
	return -1;
}

/** Sets whether the BACK button on Android should be caught. This will prevent the app from being paused. Will have no effect
* on the desktop.
*
* @param catchBack whether to catch the back button */
void GlfwInput::setCatchBackKey(bool catchBack)
{
}

/** Sets whether the MENU button on Android should be caught. This will prevent the onscreen keyboard to show up. Will have no
* effect on the desktop.
*
* @param catchMenu whether to catch the menu button */
void GlfwInput::setCatchMenuKey(bool catchMenu)
{
	//TODO:
}


/** Sets the {@link InputProcessor} that will receive all touch and key input events. It will be called before the
* {@link ApplicationListener#render()} method each frame.
*
* @param processor the InputProcessor */
void GlfwInput::setInputProcessor(InputProcessor* processor)
{
	this->processor = processor;
}


/** @return the currently set {@link InputProcessor} or null. */
InputProcessor* GlfwInput::getInputProcessor()
{
	return processor;
}

/** Queries whether a {@link Peripheral} is currently available. In case of Android and the {@link Peripheral#HardwareKeyboard}
* this returns the whether the keyboard is currently slid out or not.
*
* @param peripheral the {@link Peripheral}
* @return whether the peripheral is available or not. */
bool GlfwInput::isPeripheralAvailable(Peripheral peripheral)
{
	if (peripheral == Peripheral::HardwareKeyboard) 
		return true;
	return false;
}

/** @return the rotation of the device with respect to its native orientation. */
int GlfwInput::getRotation()
{
	return 0;
}

/** @return the native orientation of the device. */
Orientation GlfwInput::getNativeOrientation()
{
	return Orientation::Landscape;
}

/** Only viable on the desktop. Will confine the mouse cursor location to the window and hide the mouse cursor.
* @param catched whether to catch or not to catch the mouse cursor */
void GlfwInput::setCursorCatched(bool catched)
{
	//TODO:
}


/** @return whether the mouse cursor is catched. */
bool GlfwInput::isCursorCatched()
{
	//TODO:
	return false;
}


/** Only viable on the desktop. Will set the mouse cursor location to the given window coordinates(origin top-left corner).
* @param x the x-position
* @param y the y-position */
void GlfwInput::setCursorPosition(int x, int y)
{
	//TODO:
}

void GlfwInput::mouseButtonEvent(int button, int state)
{
	GlfwInput* input = ((GlfwInput*)Gdx.input);

	if(button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if(state == GLFW_PRESS)
		{
			input->m_touchDown = true;
			input->m_justTouched = true;

			::glfwGetMousePos(&input->m_touchX, &input->m_touchY);
		}
		else if(state == GLFW_RELEASE)
		{
			input->m_touchDown = false;
		}
	}
}

void GlfwInput::keyboardEvent(int key, int state)
{
	GlfwInput* input = ((GlfwInput*)Gdx.input);

	if(state == GLFW_PRESS)
	{
		input->m_keys.insert(input->translateKey(key));
		input->m_keysForProcessor.push_back( KeyEvent( input->translateKey(key), KeyEvent::KEY_DOWN));
	}
	else if(state == GLFW_RELEASE)
	{
		input->m_keys.erase(input->translateKey(key));
		input->m_keysForProcessor.push_back( KeyEvent( input->translateKey(key), KeyEvent::KEY_UP));
	}
}

int GlfwInput::translateKey(int keyCode)
{
	if (keyCode == GLFW_KEY_KP_ADD) return Input::Keys::PLUS;
	if (keyCode == GLFW_KEY_KP_SUBTRACT) return Input::Keys::MINUS;
	if (keyCode == 0x30) return Input::Keys::NUM_0;
	if (keyCode == 0x31) return Input::Keys::NUM_1;
	if (keyCode == 0x32) return Input::Keys::NUM_2;
	if (keyCode == 0x33) return Input::Keys::NUM_3;
	if (keyCode == 0x34) return Input::Keys::NUM_4;
	if (keyCode == 0x35) return Input::Keys::NUM_5;
	if (keyCode == 0x36) return Input::Keys::NUM_6;
	if (keyCode == 0x37) return Input::Keys::NUM_7;
	if (keyCode == 0x38) return Input::Keys::NUM_8;
	if (keyCode == 0x39) return Input::Keys::NUM_9;
	if (keyCode == 0x41) return Input::Keys::A;
	if (keyCode == 0x42) return Input::Keys::B;
	if (keyCode == 0x43) return Input::Keys::C;
	if (keyCode == 0x44) return Input::Keys::D;
	if (keyCode == 0x45) return Input::Keys::E;
	if (keyCode == 0x46) return Input::Keys::F;
	if (keyCode == 0x47) return Input::Keys::G;
	if (keyCode == 0x48) return Input::Keys::H;
	if (keyCode == 0x49) return Input::Keys::I;
	if (keyCode == 0x4A) return Input::Keys::J;
	if (keyCode == 0x4B) return Input::Keys::K;
	if (keyCode == 0x4C) return Input::Keys::L;
	if (keyCode == 0x4D) return Input::Keys::M;
	if (keyCode == 0x4E) return Input::Keys::N;
	if (keyCode == 0x4F) return Input::Keys::O;
	if (keyCode == 0x50) return Input::Keys::P;
	if (keyCode == 0x51) return Input::Keys::Q;
	if (keyCode == 0x52) return Input::Keys::R;
	if (keyCode == 0x53) return Input::Keys::S;
	if (keyCode == 0x54) return Input::Keys::T;
	if (keyCode == 0x55) return Input::Keys::U;
	if (keyCode == 0x56) return Input::Keys::V;
	if (keyCode == 0x57) return Input::Keys::W;
	if (keyCode == 0x58) return Input::Keys::X;
	if (keyCode == 0x59) return Input::Keys::Y;
	if (keyCode == 0x5A) return Input::Keys::Z;
	if (keyCode == GLFW_KEY_LALT) return Input::Keys::ALT_LEFT;
	if (keyCode == GLFW_KEY_RALT) return Input::Keys::ALT_RIGHT;
	if (keyCode == '\\') return Input::Keys::BACKSLASH;
	if (keyCode == ',') return Input::Keys::COMMA;
	if (keyCode == GLFW_KEY_DEL) return Input::Keys::DEL;
	if (keyCode == GLFW_KEY_LEFT) return Input::Keys::DPAD_LEFT;
	if (keyCode == GLFW_KEY_RIGHT) return Input::Keys::DPAD_RIGHT;
	if (keyCode == GLFW_KEY_UP) return Input::Keys::DPAD_UP;
	if (keyCode == GLFW_KEY_DOWN) return Input::Keys::DPAD_DOWN;
	if (keyCode == GLFW_KEY_ENTER) return Input::Keys::ENTER;
	if (keyCode == GLFW_KEY_HOME) return Input::Keys::HOME;
	if (keyCode == '-') return Input::Keys::MINUS;
	if (keyCode == '.') return Input::Keys::PERIOD;
	if (keyCode == '+') return Input::Keys::PLUS;
	if (keyCode == ';') return Input::Keys::SEMICOLON;
	if (keyCode == GLFW_KEY_LSHIFT) return Input::Keys::SHIFT_LEFT;
	if (keyCode == GLFW_KEY_RSHIFT) return Input::Keys::SHIFT_RIGHT;
	if (keyCode == '/') return Input::Keys::SLASH;
	if (keyCode == GLFW_KEY_SPACE) return Input::Keys::SPACE;
	if (keyCode == GLFW_KEY_TAB) return Input::Keys::TAB;
	if (keyCode == GLFW_KEY_DEL) return Input::Keys::DEL;
	if (keyCode == GLFW_KEY_LCTRL) return Input::Keys::CONTROL_LEFT;
	if (keyCode == GLFW_KEY_RCTRL) return Input::Keys::CONTROL_RIGHT;
	if (keyCode == GLFW_KEY_ESC) return Input::Keys::ESCAPE;
	if (keyCode == GLFW_KEY_END) return Input::Keys::END;
	if (keyCode == GLFW_KEY_INSERT) return Input::Keys::INSERT;
	//TODO DPAD_CENTER or NUM_5???
	if (keyCode == GLFW_KEY_KP_5) return Input::Keys::DPAD_CENTER;
	if (keyCode == GLFW_KEY_PAGEUP) return Input::Keys::PAGE_UP;
	if (keyCode == GLFW_KEY_PAGEDOWN) return Input::Keys::PAGE_DOWN;
	if (keyCode == GLFW_KEY_F1) return Input::Keys::F1;
	if (keyCode == GLFW_KEY_F2) return Input::Keys::F2;
	if (keyCode == GLFW_KEY_F3) return Input::Keys::F3;
	if (keyCode == GLFW_KEY_F4) return Input::Keys::F4;
	if (keyCode == GLFW_KEY_F5) return Input::Keys::F5;
	if (keyCode == GLFW_KEY_F6) return Input::Keys::F6;
	if (keyCode == GLFW_KEY_F7) return Input::Keys::F7;
	if (keyCode == GLFW_KEY_F8) return Input::Keys::F8;
	if (keyCode == GLFW_KEY_F9) return Input::Keys::F9;
	if (keyCode == GLFW_KEY_F10) return Input::Keys::F10;
	if (keyCode == GLFW_KEY_F11) return Input::Keys::F11;
	if (keyCode == GLFW_KEY_F12) return Input::Keys::F12;
	if (keyCode == ':') return Input::Keys::COLON;
	if (keyCode == GLFW_KEY_KP_0) return Input::Keys::NUM_0;
	if (keyCode == GLFW_KEY_KP_1) return Input::Keys::NUM_1;
	if (keyCode == GLFW_KEY_KP_2) return Input::Keys::NUM_2;
	if (keyCode == GLFW_KEY_KP_3) return Input::Keys::NUM_3;
	if (keyCode == GLFW_KEY_KP_4) return Input::Keys::NUM_4;
	if (keyCode == GLFW_KEY_KP_5) return Input::Keys::NUM_5;
	if (keyCode == GLFW_KEY_KP_6) return Input::Keys::NUM_6;
	if (keyCode == GLFW_KEY_KP_7) return Input::Keys::NUM_7;
	if (keyCode == GLFW_KEY_KP_8) return Input::Keys::NUM_8;
	if (keyCode == GLFW_KEY_KP_9) return Input::Keys::NUM_9;

	return Input::Keys::UNKNOWN;
}


void GlfwInput::processEvents()
{
	if (processor != NULL) 
	{
		int len = m_keysForProcessor.size();
		for (int i = 0; i < len; i++) 
		{
			KeyEvent e = m_keysForProcessor[ i];
			switch (e.type) 
			{
			case KeyEvent::KEY_DOWN:
				processor->keyDown(e.keyCode);
				break;
			case KeyEvent::KEY_UP:
				processor->keyUp(e.keyCode);
				break;
				/*case KeyEvent::KEY_TYPED:
				processor->keyTyped(e.keyChar);
				break;
				*/
			}
		}

		/*
		len = touchEvents.size();
		for (int i = 0; i < len; i++) 
		{
		TouchEvent e = touchEvents.get(i);
		currentEventTimeStamp = e.timeStamp;
		switch (e.type) {
		case TouchEvent.TOUCH_DOWN:
		processor.touchDown(e.x, e.y, e.pointer, e.button);
		break;
		case TouchEvent.TOUCH_UP:
		processor.touchUp(e.x, e.y, e.pointer, e.button);
		break;
		case TouchEvent.TOUCH_DRAGGED:
		processor.touchDragged(e.x, e.y, e.pointer);
		break;
		case TouchEvent.TOUCH_MOVED:
		processor.touchMoved(e.x, e.y);
		break;
		case TouchEvent.TOUCH_SCROLLED:
		processor.scrolled(e.scrollAmount);
		}
		usedTouchEvents.free(e);
		}
		*/
	} 
	/*
	else 
	{
	int len = touchEvents.size();
	for (int i = 0; i < len; i++) 
	{
	usedTouchEvents.free(touchEvents.get(i));
	}

	len = keyEvents.size();
	for (int i = 0; i < len; i++) 
	{
	usedKeyEvents.free(keyEvents.get(i));
	}
	}
	*/

	m_keysForProcessor.clear();
	//touchEvents.clear();

}

