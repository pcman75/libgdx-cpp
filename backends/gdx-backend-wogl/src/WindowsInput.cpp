#include "StdAfx.h"
#include "WindowsInput.h"


WindowsInput::WindowsInput(void)
{
	m_touchDown = false;
	m_touchX = m_touchY = 0;

}


WindowsInput::~WindowsInput(void)
{
}


/** @return The value of the accelerometer on its x-axis. ranges between [-10,10]. */
float WindowsInput::getAccelerometerX()
{
	return -1;
}

/** @return The value of the accelerometer on its y-axis. ranges between [-10,10]. */
float WindowsInput::getAccelerometerY()
{
	return -1;
}

/** @return The value of the accelerometer on its y-axis. ranges between [-10,10]. */
float WindowsInput::getAccelerometerZ()
{
	return -1;
}

/** @return the last touch x coordinate in screen coordinates. The screen origin is the top left corner. */
int WindowsInput::getX()
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
int WindowsInput::getX(int pointer)
{
	//TODO:
	return -1;
}

/** @return the different between the current pointer location and the last pointer location on the x-axis. */
int WindowsInput::getDeltaX()
{
	//TODO:
	return -1;
}

/** @return the different between the current pointer location and the last pointer location on the x-axis. */
int WindowsInput::getDeltaX(int pointer)
{
	//TODO:
	return -1;
}

/** @return the last touch y coordinate in screen coordinates. The screen origin is the top left corner. */
int WindowsInput::getY()
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
int WindowsInput::getY(int pointer)
{
	//TODO:
	return -1;
}


/** @return the different between the current pointer location and the last pointer location on the y-axis. */
int WindowsInput::getDeltaY()
{
	//TODO:
	return -1;
}

/** @return the different between the current pointer location and the last pointer location on the y-axis. */
int WindowsInput::getDeltaY(int pointer)
{
	//TODO:
	return -1;
}

/** @return whether the screen is currently touched. */
bool WindowsInput::isTouched()
{
	return m_touchDown;
}

/** @return whether a new touch down event just occured. */
bool WindowsInput::justTouched()
{
	//TODO:
	return -1;
}

/** Whether the screen is currently touched by the pointer with the given index. Pointers are indexed from 0 to n. The pointer
* id identifies the order in which the fingers went down on the screen, e.g. 0 is the first finger, 1 is the second and so on.
* When two fingers are touched down and the first one is lifted the second one keeps its index. If another finger is placed on
* the touch screen the first free index will be used.
*
* @param pointer the pointer
* @return whether the screen is touched by the pointer */
bool WindowsInput::isTouched(int pointer)
{
	//TODO:
	return -1;
}

/** Whether a given button is pressed or not. Button constants can be found in {@link Buttons}. On Android only the Button#LEFT
* constant is meaningful.
* @param button the button to check.
* @return whether the button is down or not. */
bool WindowsInput::isButtonPressed(int button)
{
	//TODO:
	return -1;
}

/** Returns whether the key is pressed.
*
* @param key The key code as found in {@link Input.Keys}.
* @return true or false. */
bool WindowsInput::isKeyPressed(int key)
{
	//TODO:
	return -1;
}

/** System dependent method to input a string of text. A dialog box will be created with the given title and the given text as a
* message for the user. Once the dialog has been closed the provided {@link TextInputListener} will be called but not
* necessarily in the rendering thread in which all the {@link ApplicationListener} methods are called. You have to synchronize
* this yourself.
*
* @param listener The TextInputListener.
* @param title The title of the text input dialog.
* @param text The message presented to the user. */
void WindowsInput::getTextInput(TextInputListener* listener, const std::string& title, const std::string& text)
{
	//TODO:
}

/** Sets the on-screen keyboard visible if available.
*
* @param visible visible or not */
void WindowsInput::setOnscreenKeyboardVisible(bool visible)
{
}

/** Vibrates for the given amount of time. Note that you'll need the permission
* <code> <uses-permission android:name="android.permission.VIBRATE" /></code> in your manifest file in order for this to work.
*
* @param milliseconds the number of milliseconds to vibrate. */
void WindowsInput::vibrate(int milliseconds)
{
}

/** Vibrate with a given pattern. Pass in an array of ints that are the times at which to turn on or off the vibrator. The first
* one is how long to wait before turning it on, and then after that it alternates. If you want to repeat, pass the index into
* the pattern at which to start the repeat.
* @param pattern an array of longs of times to turn the vibrator on or off.
* @param repeat the index into pattern at which to repeat, or -1 if you don't want to repeat. */
void WindowsInput::vibrate(long pattern[], int patternLength, int repeat)
{
}

/** Stops the vibrator */
void WindowsInput::cancelVibrate()
{
}

/** The azimuth is the angle of the device's orientation around the z-axis. The positive z-axis points towards the earths
* center.
*
* @see <a
*      href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])</a>
* @return the azimuth in degrees */
float WindowsInput::getAzimuth()
{
	return 0;	
}

/** The pitch is the angle of the device's orientation around the x-axis. The positive x-axis roughly points to the west and is
* orthogonal to the z- and y-axis.
* @see <a
*      href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])</a>
* @return the pitch in degrees */
float WindowsInput::getPitch()
{
	return 0;	
}

/** The roll is the angle of the device's orientation around the y-axis. The positive y-axis points to the magnetic north pole
* of the earth.
* @see <a
*      href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])</a>
* @return the roll in degrees */
float WindowsInput::getRoll()
{
	return 0;	
}
/**
* Returns the rotation matrix describing the devices rotation as per <a href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">SensorManager#getRotationMatrix(float[], float[], float[], float[])</a>.
* Does not manipulate the matrix if the platform does not have an accelerometer.
* @param matrix
*/
void WindowsInput::getRotationMatrix(float matrix[16])
{
}

/** @return the time of the event currently reported to the {@link InputProcessor}. */
long WindowsInput::getCurrentEventTime()
{
	//TODO:
	return -1;
}

/** Sets whether the BACK button on Android should be caught. This will prevent the app from being paused. Will have no effect
* on the desktop.
*
* @param catchBack whether to catch the back button */
void WindowsInput::setCatchBackKey(bool catchBack)
{
}

/** Sets whether the MENU button on Android should be caught. This will prevent the onscreen keyboard to show up. Will have no
* effect on the desktop.
*
* @param catchMenu whether to catch the menu button */
void WindowsInput::setCatchMenuKey(bool catchMenu)
{
	//TODO:
}


/** Sets the {@link InputProcessor} that will receive all touch and key input events. It will be called before the
* {@link ApplicationListener#render()} method each frame.
*
* @param processor the InputProcessor */
void WindowsInput::setInputProcessor(InputProcessor* processor)
{
	//TODO:
}


/** @return the currently set {@link InputProcessor} or null. */
InputProcessor* WindowsInput::getInputProcessor()
{
	//TODO:
	return 0;
}

/** Queries whether a {@link Peripheral} is currently available. In case of Android and the {@link Peripheral#HardwareKeyboard}
* this returns the whether the keyboard is currently slid out or not.
*
* @param peripheral the {@link Peripheral}
* @return whether the peripheral is available or not. */
bool WindowsInput::isPeripheralAvailable(Peripheral peripheral)
{
	if (peripheral == Peripheral::HardwareKeyboard) 
		return true;
	return false;
}

/** @return the rotation of the device with respect to its native orientation. */
int WindowsInput::getRotation()
{
	return 0;
}

/** @return the native orientation of the device. */
Orientation WindowsInput::getNativeOrientation()
{
	return Orientation::Landscape;
}

/** Only viable on the desktop. Will confine the mouse cursor location to the window and hide the mouse cursor.
* @param catched whether to catch or not to catch the mouse cursor */
void WindowsInput::setCursorCatched(bool catched)
{
	//TODO:
}


/** @return whether the mouse cursor is catched. */
bool WindowsInput::isCursorCatched()
{
	//TODO:
	return false;
}


/** Only viable on the desktop. Will set the mouse cursor location to the given window coordinates(origin top-left corner).
* @param x the x-position
* @param y the y-position */
void WindowsInput::setCursorPosition(int x, int y)
{
	//TODO:
}


void WindowsInput::buttonDown(WPARAM state, int x, int y)
{
	if(state == MK_LBUTTON)
	{
		m_touchDown = true;
	}
	m_touchX = x;
	m_touchY = y;
}

void WindowsInput::buttonUp(WPARAM state, int x, int y)
{
	if(m_touchDown)
		m_touchDown = false;
}


