#pragma once

//class GLU;
//class Pixmap;

/** <p>
* This interface encapsulates the communication with the graphics processor. It allows to retrieve {@link GL10}, {@link GL11} and
* {@link GL20} instances depending on the available hardware and configuration of the {@link Application}. Additionally it
* features methods to generate {@link Pixmap}s and {@link Texture}s.
* </p>
* 
* <p>
* {@link Texture}s can be either managed or not managed. Managed and Textures will be restored when the OpenGL context is lost.
* An OpenGL ES context loss happens when a user pauses the Application ( {@link ApplicationListener#pause()}) and switches to
* another application on Android. On the desktop there is no concept of context loss for OpenGL.
* </p>
* 
* <p>
* There are many more utility classes that are not directly generated by the {@link Graphics} interfaces. See {@link VertexArray}, {@link VertexBufferObject}, {@link IndexBufferObject}, {@link Mesh}, {@link ShaderProgram} and {@link FrameBuffer},
* {@link BitmapFont}, {@link SpriteBatch} and so on. All these classes are managed, meaning they don't need to be reloaded on a
* context loss. Explore the com.badlogic.gdx.graphics package for more classes that might come in handy.
* </p>
* 
* <p>
* All graphical resources, be the generated by the {@link Graphics} interface or via a constructor <b>must</b> be disposed when
* no longer used!
* </p>
* 
* @author mzechner */
class Graphics 
{
public:
	virtual ~Graphics() {}
	/** Enumeration describing different types of {@link Graphics} implementations. */
	enum GraphicsType 
	{
		AndroidGL, iOSGL, WOGL
	};

	/** Class describing a fullscreen display mode */
	class DisplayMode 
	{
		int width;
		int height;
		int refreshRate;
		int bitsPerPixel;

	//protected:
		//TODO:
	public:
		DisplayMode (int width, int height, int refreshRate, int bitsPerPixel) 
		{
			this->width = width;
			this->height = height;
			this->refreshRate = refreshRate;
			this->bitsPerPixel = bitsPerPixel;
		}
	public:
		std::string toString () 
		{
			std::stringstream buf;
			buf << width << 'x' << height << " bpp: " << bitsPerPixel << ", hz: " << refreshRate;
			return buf.str();
		}
	};

	/** Class describing the bits per pixel, depth buffer precision, stencil precision and number of MSAA samples. */
	class BufferFormat 
	{
		/** number of bits per color channel **/
		int r, g, b, a;
		/** number of bits for depth and stencil buffer **/
		int depth, stencil;
		/** number of samples for MSAA **/
		int samples;
		/** whether coverage sampling anti-aliasing is used. in that case you have to clear the coverage buffer as well! */
		bool coverageSampling;

		//TODO:
	public:
		BufferFormat (int r, int g, int b, int a, int depth, int stencil, int samples, bool coverageSampling)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
			this->depth = depth;
			this->stencil = stencil;
			this->samples = samples;
			this->coverageSampling = coverageSampling;
		}

		std::string toString () 
		{
			std::stringstream buf;
			buf << "r: " << r << ", g: " << g << ", b: " << b << ", a: " << a << ", depth: " << depth << ", stencil: " << stencil << ", num samples: " << samples;
			buf << (coverageSampling? "true": "false");
			return buf.str();
		}
	};

	/** Returns whether OpenGL ES 1.1 is available. If it is you can get an instance of {@link GL11} via {@link #getGL11()} to
	* access OpenGL ES 1.1 functionality. This also implies that {@link #getGL10()} will return an instance.
	* 
	* @return whether OpenGL ES 1.1 is available */
	virtual bool isGL11Available () = 0;

	/** Returns whether OpenGL ES 2.0 is available. If it is you can get an instance of {@link GL20} via {@link #getGL20()} to
	* access OpenGL ES 2.0 functionality. Note that this functionality will only be available if you instructed the
	* {@link Application} instance to use OpenGL ES 2.0!
	* 
	* @return whether OpenGL ES 2.0 is available */
	virtual bool isGL20Available () = 0;

	/** @return the width in pixels of the display surface */
	virtual int getWidth () = 0;

	/** @return the height in pixels of the display surface */
	virtual int getHeight () = 0;

	/** @return the time span between the current frame and the last frame in seconds */
	virtual float getDeltaTime () = 0;

	/** @return the average number of frames per second */
	virtual int getFramesPerSecond () = 0;

	/** @return the {@link GraphicsType} of this Graphics instance */
	virtual GraphicsType getType () = 0;

	/** @return the pixels per inch on the x-axis */
	virtual float getPpiX () = 0;

	/** @return the pixels per inch on the y-axis */
	virtual float getPpiY () = 0;

	/** @return the pixels per centimeter on the x-axis */
	virtual float getPpcX () = 0;

	/** @return the pixels per centimeter on the y-axis. */
	virtual float getPpcY () = 0;

	/** This is a scaling factor for the Density Independent Pixel unit, following the same conventions as
	* android.util.DisplayMetrics#density, where one DIP is one pixel on an approximately 160 dpi screen. Thus on a 160dpi screen
	* this density value will be 1; on a 120 dpi screen it would be .75; etc.
	* 
	* @return the logical density of the Display. */
	virtual float getDensity () = 0;

	/** Whether the given backend supports a display mode change via calling {@link Graphics#setDisplayMode(DisplayMode)}
	* 
	* @return whether display mode changes are supported or not. */
	virtual bool supportsDisplayModeChange () = 0;

	/** @return the supported fullscreen {@link DisplayMode}. */
	virtual std::vector< DisplayMode> getDisplayModes () = 0;

	/** @return the display mode of the primary graphics adapter. */
	virtual DisplayMode getDesktopDisplayMode () = 0;

	/** Sets the current {@link DisplayMode}. Returns false in case the operation failed. Not all backends support this methods. See
	* {@link Graphics#supportsDisplayModeChange()}.
	* 
	* @param displayMode the display mode.
	* @return whether the operation succeeded. */
	virtual bool setDisplayMode (DisplayMode displayMode) = 0;

	/** Tries to set the display mode width the given width and height in pixels. Will always succeed if fullscreen is set to false,
	* in which case the application will be run in windowed mode. Use {@link Graphics#getDisplayModes()} to get a list of
	* supported fullscreen modes.
	* 
	* @param width the width in pixels
	* @param height the height in pixels
	* @param fullscreen whether to use fullscreen rendering or not */
	virtual bool setDisplayMode (int width, int height, bool fullscreen) = 0;

	/** Sets the title of the window. Ignored on Android.
	* 
	* @param title the title. */
	virtual void setTitle (std::string title) = 0;

	/** Sets one or more icons for the Desktop. This only works for Lwjgl. On Windows you should supply at least one 16x16 icon and
	* one 32x32. Linux (and similar platforms) expect one 32x32 icon. Mac OS X should be supplied one 128x128 icon
	* @param pixmaps 1 or more Pixmaps using {@link Format#RGBA8888} */
	//virtual void setIcon (std::vector<Pixmap> pixmaps) = 0;

	/** Enable/Disable vsynching. This is a best-effort attempt which might not work on all platforms.
	* 
	* @param vsync vsync enabled or not. */
	virtual void setVSync (bool vsync) = 0;

	/** @return the format of the color, depth and stencil buffer in a {@link BufferFormat} instance */
	virtual BufferFormat getBufferFormat () = 0;

	/** @param extension the extension name
	* @return whether the extension is supported */
	virtual bool supportsExtension (std::string extension) = 0;
};

