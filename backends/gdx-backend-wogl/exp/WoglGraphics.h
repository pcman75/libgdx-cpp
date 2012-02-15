#pragma once
#include "Graphics.h"
#include "ApplicationListener.h"

class WoglGraphics : public Graphics
{
private:
	ApplicationListener& m_listener;
	bool m_useGL20;
	bool created;
	bool exclusiveMode;

	int m_width;
	int m_height;

	//final JoglDisplayMode desktopMode;
	//final JoglApplicationConfiguration config;
	//String extensions;

public:
	WoglGraphics(ApplicationListener& listener, bool useGL20/*, JoglApplicationConfiguration config*/);
	virtual ~WoglGraphics(void);

	virtual bool isGL11Available ();

	/** Returns whether OpenGL ES 2.0 is available. If it is you can get an instance of {@link GL20} via {@link #getGL20()} to
	* access OpenGL ES 2.0 functionality. Note that this functionality will only be available if you instructed the
	* {@link Application} instance to use OpenGL ES 2.0!
	* 
	* @return whether OpenGL ES 2.0 is available */
	virtual bool isGL20Available ();

	/** @return a {@link GLCommon} instance */
	virtual const GLCommon& getGLCommon ();

	/** @return the {@link GL10} instance or null if not supported */
	virtual const GL10& getGL10 ();

	/** @return the {@link GL11} instance or null if not supported */
	virtual const GL11& getGL11 ();

	/** @return the {@link GL20} instance or null if not supported */
	virtual const GL20& getGL20 ();

	/** @return the {@link GLU} instance */
	virtual const GLU& getGLU ();

	/** @return the width in pixels of the display surface */
	virtual int getWidth ();

	/** @return the height in pixels of the display surface */
	virtual int getHeight ();

	/** @return the time span between the current frame and the last frame in seconds */
	virtual float getDeltaTime ();

	/** @return the average number of frames per second */
	virtual int getFramesPerSecond ();

	/** @return the {@link GraphicsType} of this Graphics instance */
	virtual GraphicsType getType ();

	/** @return the pixels per inch on the x-axis */
	virtual float getPpiX ();

	/** @return the pixels per inch on the y-axis */
	virtual float getPpiY ();

	/** @return the pixels per centimeter on the x-axis */
	virtual float getPpcX ();

	/** @return the pixels per centimeter on the y-axis. */
	virtual float getPpcY ();

	/** This is a scaling factor for the Density Independent Pixel unit, following the same conventions as
	* android.util.DisplayMetrics#density, where one DIP is one pixel on an approximately 160 dpi screen. Thus on a 160dpi screen
	* this density value will be 1; on a 120 dpi screen it would be .75; etc.
	* 
	* @return the logical density of the Display. */
	virtual float getDensity ();

	/** Whether the given backend supports a display mode change via calling {@link Graphics#setDisplayMode(DisplayMode)}
	* 
	* @return whether display mode changes are supported or not. */
	virtual bool supportsDisplayModeChange ();

	/** @return the supported fullscreen {@link DisplayMode}. */
	virtual std::vector<DisplayMode> getDisplayModes ();

	/** @return the display mode of the primary graphics adapter. */
	virtual DisplayMode getDesktopDisplayMode ();

	/** Sets the current {@link DisplayMode}. Returns false in case the operation failed. Not all backends support this methods. See
	* {@link Graphics#supportsDisplayModeChange()}.
	* 
	* @param displayMode the display mode.
	* @return whether the operation succeeded. */
	virtual bool setDisplayMode (DisplayMode displayMode);

	/** Tries to set the display mode width the given width and height in pixels. Will always succeed if fullscreen is set to false,
	* in which case the application will be run in windowed mode. Use {@link Graphics#getDisplayModes()} to get a list of
	* supported fullscreen modes.
	* 
	* @param width the width in pixels
	* @param height the height in pixels
	* @param fullscreen whether to use fullscreen rendering or not */
	virtual bool setDisplayMode (int width, int height, bool fullscreen);

	/** Sets the title of the window. Ignored on Android.
	* 
	* @param title the title. */
	virtual void setTitle (std::string title);

	/** Sets one or more icons for the Desktop. This only works for Lwjgl. On Windows you should supply at least one 16x16 icon and
	* one 32x32. Linux (and similar platforms) expect one 32x32 icon. Mac OS X should be supplied one 128x128 icon
	* @param pixmaps 1 or more Pixmaps using {@link Format#RGBA8888} */
	//virtual void setIcon (std::vector<Pixmap> pixmaps);

	/** Enable/Disable vsynching. This is a best-effort attempt which might not work on all platforms.
	* 
	* @param vsync vsync enabled or not. */
	virtual void setVSync (bool vsync);

	/** @return the format of the color, depth and stencil buffer in a {@link BufferFormat} instance */
	virtual BufferFormat getBufferFormat ();

	/** @param extension the extension name
	* @return whether the extension is supported */
	virtual bool supportsExtension (std::string extension);

private:
	void initializeGLInstances();

private:
	GLCommon* m_pGL;
	GL10* m_pGL10;
	GL11* m_pGL11;
	GL20* m_pGL20;
	GLU* m_pGLU;

	int m_major;
	int m_minor;

	///////////////////
	//TODO: temporary
	///////////////////
public:
	void init();                                    // initialize OpenGL states
    void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
    void setViewport(int width, int height);
    void draw();

    void setMouseLeft(bool flag) { mouseLeftDown = flag; };
    void setMouseRight(bool flag) { mouseRightDown = flag; };
    void setMousePosition(int x, int y) { mouseX = x; mouseY = y; };

    void rotateCamera(int x, int y);
    void zoomCamera(int dist);


protected:

private:
    // member functions
    void initLights();                              // add a white light ti scene

    // members
    bool mouseLeftDown;
    bool mouseRightDown;
    int mouseX;
    int mouseY;
    float cameraAngleX;
    float cameraAngleY;
    float cameraDistance;


};

