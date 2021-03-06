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
#include "Application.h"
#include "ApplicationListener.h"

/** An implemenation of the {@link Application} interface based on OpenGL for Windows. Instantiate this class with
 * apropriate parameters and then register {@link ApplicationListener} or {@link InputProcessor} instances. */
class GlfwApplication :
	public Application
{
public:
	/** Creates a new {@link JoglApplication} with the given title and dimensions. If useGL20IfAvailable is set the JoglApplication
	 * will try to create an OpenGL 2.0 context which can then be used via JoglApplication.getGraphics().getGL20(). To query
	 * whether enabling OpenGL 2.0 was successful use the JoglApplication.getGraphics().isGL20Available() method.
	 * 
	 * @param listener the ApplicationListener implementing the program logic
	 * @param title the title of the application
	 * @param width the width of the surface in pixels
	 * @param height the height of the surface in pixels
	 * @param useGL20IfAvailable wheter to use OpenGL 2.0 if it is available or not */
	GlfwApplication (ApplicationListener& listener, const char* title, int width, int height,
		bool useGL20IfAvailable);
	virtual ~GlfwApplication(void);

	/** @return the {@link Graphics} instance */
	virtual Graphics* getGraphics ();

	/** @return the {@link Audio} instance */
	virtual Audio* getAudio ();

	/** @return the {@link Input} instance */
	virtual Input* getInput ();

	/** @return the {@link Files} instance */
	virtual Files* getFiles ();
	
	/** @return the {@link Threading} instance */
	virtual Threading* getThreading();

	/** @create a Timer. caller must delete it after use*/
	virtual Timer* createTimer();

	/** Logs a message to the console or logcat */
	virtual void log(const char* tag, const char* message);

	/** Logs a message to the console or logcat */
	//virtual void log (const char* tag, const char* message, class std::exception ex);



	/** Logs an error message to the console or logcat */
	virtual void error (const char* tag, const char* message);

	/** Logs an error message to the console or logcat */
	//virtual void error (const char* tag, const char* message, class std::exception ex);

	/** Logs an error message to the console or logcat */
	virtual void debug (const char* tag, const char* message);

	/** Logs an error message to the console or logcat */
	//virtual void debug (const char* tag, const char* message, std::exception ex);



	/** Sets the log level. {@link #LOG_NONE} will mute all log output. {@link #LOG_ERROR} will only let error messages through.
	* {@link #LOG_INFO} will let all non-debug messages through, and {@link #LOG_DEBUG} will let all messages through.
	* @param logLevel {@link #LOG_NONE}, {@link #LOG_ERROR}, {@link #LOG_INFO}, {@link #LOG_DEBUG}. */
	virtual void setLogLevel (int logLevel);


	/** @return what {@link ApplicationType} this application has, e.g. iOS, Mac, Windows, Android*/
	virtual ApplicationType getType ();



	/** @return the iOS version on iOS, Android API level on Android or 0 on the desktop. */
	virtual int getVersion ();

	//TODO: possible?
	/** @return the heap memory use in bytes */
	//long getHeap ();

	/** Returns the {@link Preferences} instance of this Application. It can be used to store application settings across runs.
	* @param name the name of the preferences, must be useable as a file name.
	* @return the preferences. */

	//virtual const Preferences& getPreferences (const char* name);

	/** Exits the application. This will cause a call to pause() and dispose() some time in the loadFuture, it will not immediately
	* finish your application! */
	virtual void exit ();

private:
	void createWindow(const char* title, int width, int height);
	void runOpenGLLoop();
    void printDebugString(const char* str);
private:
	Graphics* m_pGraphics;
	Input* m_pInput;
	Files* m_pFiles;
	Threading* m_pThreading;
	Audio* m_pAudio;
	int logLevel;
	
};

