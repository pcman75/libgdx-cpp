/*******************************************************************************
* Copyright 2011 See AUTHORS file.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*   http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
******************************************************************************/

#pragma once

#include "GdxDefines.h"

//forward declarations
class Graphics;
class Audio;
class Input;
class Files;
class Preferences;

class GdxDllImportExport Application {
public:
	virtual ~Application() {};

	/**
	* An <code>Application</code> is the main entry point of your project. It sets up a window and rendering surface and manages the
	* different aspects of your application, namely {@link Graphics}, {@link Audio}, {@link Input} and {@link Files}. Think of an
	* Application being equivalent to a JFrame of Activity.
	* </p>
	* 
	* <p>
	* An application can either be a desktop application WoglApplication, MoglApplication found in gdx-backends-Wogl and
	* gdx-backends-Mogl respectively), or an iOS application iOSApplication found in gdx-backends-iOS). Each
	* application class has it's own startup and initialization methods. Please refer to their documentation for more information.
	* </p>
	* 
	* <p>
	* While game programmers are used to having a main loop, libgdx employs a different concept to accomodate the event based nature
	* of Android applications a little more. You application logic must be implemented in a {@link ApplicationListener} which has
	* methods that get called by the Application when the application is created, resumed, paused, disposed or rendered. As a
	* developer you will simply implement the ApplicationListener interface and fill in the functionality accordingly. The
	* ApplicationListener is provided to a concrete Application instance as a parameter to the constructor or another initialization
	* method. Please refer to the documentation of the Application implementations for more information. Note that the
	* ApplicationListener can be provided to any Application implementation. This means that you only need to write your program
	* logic once and have it run on different platforms by passing it to a concrete Application implementation.
	* </p>
	* 
	* <p>
	* The Application interface provides you with a set of modules for graphics, audio, input and file i/o.
	* </p>
	* 
	* <p>
	* {@link Graphics} offers you various methods to output visuals to the screen. This is achieved via OpenGL ES 1.0, 1.1 or 2.0
	* depending on what's available an the platform. On the desktop the features of OpenGL ES 2.0 are emulated via desktop OpenGL. On
	* iOS the functionality of the OpenGL ES bindings is used.
	* </p>
	* 
	* <p>TODO:
	* {@link Audio} offers you various methods to output and record sound and music. This is achieved via the Java Sound API on the
	* desktop. On iOS the Android media framework is used.
	* </p>
	* 
	* <p>
	* {@link Input} offers you various methods to poll user input from the keyboard, touch screen, mouse and accelerometer.
	* Additionally you can implement an {@link InputProcessor} and use it with {@link Input#setInputProcessor(InputProcessor)} to
	* receive input events.
	* </p>
	* 
	* <p> TODO:
	* {@link Files} offers you various methods to access internal and external files. An internal file is a file that is stored near
	* your application. On iOS internal file are equivalent to assets. On the desktop the root directory of your application is used for a look up.
	* External files are resources you create in your application and write to an external storage. On Android external files reside on the SD-card, on the
	* desktop external files are written to a users home directory. If you know what you do you can also specify absolute file names.
	* This is not portable, so take great care when using this feature.
	* </p>
	* 
	* <p>
	* The <code>Application</code> also has a set of methods that you can use to query specific information such as the operating
	* system the application is currently running on and so forth. This allows you to have operating system dependent code paths. It
	* is however not recommended to use this facilities.
	* </p>
	* 
	* <p> TODO:
	* The <code>Application</code> also has a simple logging method which will print to standard out on the desktop and to logcat on
	* Android.
	* </p>
	*/

public:
	/** Enumeration of possible {@link Application} types */
	enum ApplicationType {
		iOS, Mac, Windows, Android
	};

	static const int LOG_NONE = 0;
	static const int LOG_DEBUG = 3;
	static const int LOG_INFO = 2;
	static const int LOG_ERROR = 1;


	/** @return the {@link Graphics} instance */
	virtual const Graphics& getGraphics () = 0;

	/** @return the {@link Audio} instance */
	//virtual const Audio& getAudio () = 0;

	/** @return the {@link Input} instance */
	virtual const Input& getInput () = 0;

	/** @return the {@link Files} instance */
	virtual const Files& getFiles () = 0;

	/** Logs a message to the console or logcat */
	virtual void log(const wchar_t* tag, const wchar_t* message) = 0;

	/** Logs a message to the console or logcat */
	//virtual void log (const wchar_t* tag, const wchar_t* message, class exception ex) = 0;



	/** Logs an error message to the console or logcat */
	virtual void error (const wchar_t* tag, const wchar_t* message) = 0;

	/** Logs an error message to the console or logcat */
	//virtual void error (const wchar_t* tag, const wchar_t* message, class exception ex) = 0;

	/** Logs an error message to the console or logcat */
	virtual void debug (const wchar_t* tag, const wchar_t* message) = 0;

	/** Logs an error message to the console or logcat */
	//virtual void debug (const wchar_t* tag, const wchar_t* message, class exception ex) = 0;



	/** Sets the log level. {@link #LOG_NONE} will mute all log output. {@link #LOG_ERROR} will only let error messages through.
	* {@link #LOG_INFO} will let all non-debug messages through, and {@link #LOG_DEBUG} will let all messages through.
	* @param logLevel {@link #LOG_NONE}, {@link #LOG_ERROR}, {@link #LOG_INFO}, {@link #LOG_DEBUG}. */
	virtual void setLogLevel (int logLevel) = 0;


	/** @return what {@link ApplicationType} this application has, e.g. iOS, Mac, Windows, Android*/
	virtual ApplicationType getType () = 0;



	/** @return the iOS version on iOS, Android API level on Android or 0 on the desktop. */
	virtual int getVersion () = 0;

	//TODO: possible?
	/** @return the heap memory use in bytes */
	//long getHeap ();

	/** Returns the {@link Preferences} instance of this Application. It can be used to store application settings across runs.
	* @param name the name of the preferences, must be useable as a file name.
	* @return the preferences. */

	//virtual const Preferences& getPreferences (const wchar_t* name) = 0;

	/** Exits the application. This will cause a call to pause() and dispose() some time in the loadFuture, it will not immediately
	* finish your application! */
	virtual void exit () = 0;
};

