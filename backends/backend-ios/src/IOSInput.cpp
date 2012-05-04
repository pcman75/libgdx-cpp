#include "IOSInput.h"
#include "Gdx.h"

IOSInput::IOSInput(void)
{
	m_touchDown = false;
	m_justTouched = false;
	m_touchX = m_touchY = 0;

	processor = NULL;
}

IOSInput::~IOSInput(void)
{
}

/** @return The value of the accelerometer on its x-axis. ranges between [-10,10]. */
float IOSInput::getAccelerometerX()
{
	return 0.f;
}

/** @return The value of the accelerometer on its y-axis. ranges between [-10,10]. */
float IOSInput::getAccelerometerY()
{
	return 0.f;
}

/** @return The value of the accelerometer on its y-axis. ranges between [-10,10]. */
float IOSInput::getAccelerometerZ()
{
	return 0.f;
}

/** @return the last touch x coordinate in screen coordinates. The screen origin is the top left corner. */
int IOSInput::getX()
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
int IOSInput::getX(int pointer)
{
	//TODO:
	return -1;
}

/** @return the different between the current pointer location and the last pointer location on the x-axis. */
int IOSInput::getDeltaX()
{
	//TODO:
	return -1;
}

/** @return the different between the current pointer location and the last pointer location on the x-axis. */
int IOSInput::getDeltaX(int pointer)
{
	//TODO:
	return -1;
}

/** @return the last touch y coordinate in screen coordinates. The screen origin is the top left corner. */
int IOSInput::getY()
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
int IOSInput::getY(int pointer)
{
	//TODO:
	return -1;
}


/** @return the different between the current pointer location and the last pointer location on the y-axis. */
int IOSInput::getDeltaY()
{
	//TODO:
	return -1;
}

/** @return the different between the current pointer location and the last pointer location on the y-axis. */
int IOSInput::getDeltaY(int pointer)
{
	//TODO:
	return -1;
}

/** @return whether the screen is currently touched. */
bool IOSInput::isTouched()
{
	return m_touchDown;
}

/** @return whether a new touch down event just occured. */
bool IOSInput::justTouched()
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
bool IOSInput::isTouched(int pointer)
{
	//TODO:
	return false;
}

/** Whether a given button is pressed or not. Button constants can be found in {@link Buttons}. On Mobile only the Button#LEFT
* constant is meaningful.
* @param button the button to check.
* @return whether the button is down or not. */
bool IOSInput::isButtonPressed(int button)
{
	//TODO:
	return false;
}

/** Returns whether the key is pressed.
*
* @param key The key code as found in {@link Input.Keys}.
* @return true or false. */
bool IOSInput::isKeyPressed(int key)
{
    //hopefully iOS will never get keys :-)
    return false;
}

/** System dependent method to input a string of text. A dialog box will be created with the given title and the given text as a
* message for the user. Once the dialog has been closed the provided {@link TextInputListener} will be called but not
* necessarily in the rendering thread in which all the {@link ApplicationListener} methods are called. You have to synchronize
* this yourself.
*
* @param listener The TextInputListener.
* @param title The title of the text input dialog.
* @param text The message presented to the user. */
void IOSInput::getTextInput(TextInputListener* listener, const std::string& title, const std::string& text)
{
	//TODO:
}

/** Sets the on-screen keyboard visible if available.
*
* @param visible visible or not */
void IOSInput::setOnscreenKeyboardVisible(bool visible)
{
}

/** Vibrates for the given amount of time. Note that you'll need the permission
* <code> <uses-permission android:name="android.permission.VIBRATE" /></code> in your manifest file in order for this to work.
*
* @param milliseconds the number of milliseconds to vibrate. */
void IOSInput::vibrate(int milliseconds)
{
}

/** Vibrate with a given pattern. Pass in an array of ints that are the times at which to turn on or off the vibrator. The first
* one is how long to wait before turning it on, and then after that it alternates. If you want to repeat, pass the index into
* the pattern at which to start the repeat.
* @param pattern an array of longs of times to turn the vibrator on or off.
* @param repeat the index into pattern at which to repeat, or -1 if you don't want to repeat. */
void IOSInput::vibrate(long pattern[], int patternLength, int repeat)
{
}

/** Stops the vibrator */
void IOSInput::cancelVibrate()
{
}

/** The azimuth is the angle of the device's orientation around the z-axis. The positive z-axis points towards the earths
* center.
*
* @see <a
*      href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])</a>
* @return the azimuth in degrees */
float IOSInput::getAzimuth()
{
	return 0;	
}

/** The pitch is the angle of the device's orientation around the x-axis. The positive x-axis roughly points to the west and is
* orthogonal to the z- and y-axis.
* @see <a
*      href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])</a>
* @return the pitch in degrees */
float IOSInput::getPitch()
{
	return 0;	
}

/** The roll is the angle of the device's orientation around the y-axis. The positive y-axis points to the magnetic north pole
* of the earth.
* @see <a
*      href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])</a>
* @return the roll in degrees */
float IOSInput::getRoll()
{
	return 0;	
}
/**
* Returns the rotation matrix describing the devices rotation as per <a href="http://developer.android.com/reference/android/hardware/SensorManager.html#getRotationMatrix(float[], float[], float[], float[])">SensorManager#getRotationMatrix(float[], float[], float[], float[])</a>.
* Does not manipulate the matrix if the platform does not have an accelerometer.
* @param matrix
*/
void IOSInput::getRotationMatrix(float matrix[16])
{
}

/** @return the time of the event currently reported to the {@link InputProcessor}. */
long IOSInput::getCurrentEventTime()
{
	//TODO:
	return -1;
}

/** Sets whether the BACK button on Android should be caught. This will prevent the app from being paused. Will have no effect
* on the desktop.
*
* @param catchBack whether to catch the back button */
void IOSInput::setCatchBackKey(bool catchBack)
{
}

/** Sets whether the MENU button on Android should be caught. This will prevent the onscreen keyboard to show up. Will have no
* effect on the desktop and iOS
*
* @param catchMenu whether to catch the menu button */
void IOSInput::setCatchMenuKey(bool catchMenu)
{
	//TODO:
}


/** Sets the {@link InputProcessor} that will receive all touch and key input events. It will be called before the
* {@link ApplicationListener#render()} method each frame.
*
* @param processor the InputProcessor */
void IOSInput::setInputProcessor(InputProcessor* processor)
{
	this->processor = processor;
}


/** @return the currently set {@link InputProcessor} or null. */
InputProcessor* IOSInput::getInputProcessor()
{
	return processor;
}

/** Queries whether a {@link Peripheral} is currently available. In case of Android and the {@link Peripheral#HardwareKeyboard}
* this returns the whether the keyboard is currently slid out or not.
*
* @param peripheral the {@link Peripheral}
* @return whether the peripheral is available or not. */
bool IOSInput::isPeripheralAvailable(Peripheral peripheral)
{
	if(peripheral == Peripheral::MultitouchScreen ||
       peripheral == Peripheral::Accelerometer ||
       peripheral == Peripheral::Compass || //TODO: not all iOS have this?
       peripheral == Peripheral::Vibrator)
        return true;
	return false;
}

/** @return the rotation of the device with respect to its native orientation. */
int IOSInput::getRotation()
{
	return 0;
}

/** @return the native orientation of the device. */
Orientation IOSInput::getNativeOrientation()
{
	return Orientation::Landscape;
}

/** Only viable on the desktop. Will confine the mouse cursor location to the window and hide the mouse cursor.
* @param catched whether to catch or not to catch the mouse cursor */
void IOSInput::setCursorCatched(bool catched)
{
	//TODO:
}


/** @return whether the mouse cursor is catched. */
bool IOSInput::isCursorCatched()
{
	//TODO:
	return false;
}


/** Only viable on the desktop. Will set the mouse cursor location to the given window coordinates(origin top-left corner).
* @param x the x-position
* @param y the y-position */
void IOSInput::setCursorPosition(int x, int y)
{
	//TODO:
}
