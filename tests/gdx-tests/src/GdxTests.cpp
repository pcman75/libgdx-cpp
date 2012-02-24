#include "stdafx.h"
#include "GdxTests.h"

//#include "AnimationTest.h"
//#include "AccelerometerTest.h"
//#include "ActionTest.h"
//#include "ActionSequenceTest.h"
//#include "GroupTest.h"
#include "AlphaTest.h"
//#include "AtlasIssueTest.h"
//#include "AssetManagerTest.h"
//#include "FilterPerformanceTest.h"
//#include "AudioDeviceTest.h"
//#include "AudioRecorderTest.h"
//#include "BitmapFontAlignmentTest.h"
//#include "BitmapFontFlipTest.h"
//#include "GroupCullingTest.h"
//#include "GestureDetectorTest.h"
//#include "LabelTest.h"
//#include "BitmapFontTest.h"
//#include "BlitTest.h"
//#include "TableTest.h"
//#include "BobTest.h"
//#include "ImageScaleTest.h"
//#include "Box2DInitialOverlapTest.h"
//#include "Box2DTest.h"
//#include "InterpolationTest.h"
//#include "Box2DTestCollection.h"
//#include "BufferUtilsTest.h"
//#include "ImageTest.h"
//#include "CompassTest.h"
//#include "ComplexActionTest.h"
//#include "CullTest.h"
//#include "DeltaTimeTest.h"
//#include "EdgeDetectionTest.h"
//#include "ETC1Test.h"
//#include "ExitTest.h"
//#include "FilesTest.h"
//#include "FlickScrollPaneTest.h"
//#include "FloatTest.h"
//#include "FrameBufferTest.h"
//#include "FramebufferToTextureTest.h"
//#include "FrustumTest.h"
//#include "FullscreenTest.h"
//#include "Gdx2DTest.h"
//#include "GroupFadeTest.h"
//#include "ImmediateModeRendererTest.h"
//#include "ImmediateModeRendererAlphaTest.h"
//#include "IndexBufferObjectClassTest.h"
//#include "IndexBufferObjectShaderTest.h"
//#include "InputTest.h"
//#include "IntegerBitmapFontTest.h"
//#include "InverseKinematicsTest.h"
//#include "IsoCamTest.h"
//#include "IsometricTileTest.h"
//#include "KinematicBodyTest.h"
//#include "LifeCycleTest.h"
//#include "LineDrawingTest.h"
//#include "ScrollPaneTest.h"
//#include "ManagedTest.h"
//#include "ManualBindTest.h"
#include "MatrixJNITest.h"
//#include "MD5Test.h"
//#include "MeshMultitextureTest.h"
#include "MeshShaderTest.h"
#include "MeshTest.h"
//#include "MipMapTest.h"
//#include "MultitouchTest.h"
//#include "MusicTest.h"
//#include "MyFirstTriangle.h"
//#include "ObjTest.h"
//#include "OnscreenKeyboardTest.h"
#include "OrthoCamBorderTest.h"
//#include "ParallaxTest.h"
//#include "ParticleEmitterTest.h"
//#include "PickingTest.h"
//#include "PixelsPerInchTest.h"
#include "PixmapBlendingTest.h"
#include "PixmapTest.h"
#include "SpriteBatchRotationTest.h"
//#include "PreferencesTest.h"
//#include "ProjectiveTextureTest.h"
//#include "Pong.h"
//#include "ProjectTest.h"
//#include "RemoteTest.h"
//#include "RotationTest.h"
//#include "ShaderMultitextureTest.h"
//#include "ShadowMappingTest.h"
//#include "SplineTest.h"
//#include "SimpleTest.h"
//#include "SimpleAnimationTest.h"
//#include "SimpleDecalTest.h"
//#include "SimpleStageCullingTest.h"
//#include "SoundTest.h"
//#include "SpriteCacheTest.h"
//#include "SpriteCacheOffsetTest.h"
//#include "SpriteBatchRotationTest.h"
//#include "SpriteBatchShaderTest.h"
#include "SpriteBatchTest.h"
//#include "SpritePerformanceTest.h"
//#include "SpritePerformanteTest2.h"
//#include "StagePerformanceTest.h"
//#include "StageTest.h"
//#include "TerrainTest.h"
#include "TextureDataTest.h"
//#include "TextureDownloadTest.h"
//#include "TextureFormatTest.h"
//#include "TextureAtlasTest.h"
//#include "TextInputDialogTest.h"
//#include "TextureRenderTest.h"
//#include "TiledMapTest.h"
//#include "TileTest.h"
//#include "UITest.h"
//#include "VBOVATestv
#include "VertexArrayTest.h"
//#include "VertexBufferObjectTest.h"
#include "VertexArrayClassTest.h"
//#include "VertexBufferObjectClassTest.h"
#include "VertexBufferObjectShaderTest.h"
//#include "VibratorTest.h"
//#include "VorbisTest.h"
//#include "WaterRipples.h"
//#include "HelloTriangle.h"
//#include "SimpleVertexShader.h"
//#include "ShapeRendererTest.h"
//#include "MoveSpriteExample.h"
//#include "StbTrueTypeTest.h"
//#include "SoundTouchTest.h"
//#include "Mpg123Test.h"
//#include "WavTest.h"
//#include "TextButtonTest.h"
//#include "TextureBindTest.h"

#define GDX_DEFINE_TEST(testClassName) \
	tests[#testClassName] = testClassName::createInstance

GdxTests::TestsMap GdxTests::tests;
GdxTests GdxTests::self;

GdxTests::GdxTests()
{
	//GDX_DEFINE_TEST(AnimationTest
	//GDX_DEFINE_TEST(AccelerometerTest
	//GDX_DEFINE_TEST(ActionTest
	//GDX_DEFINE_TEST(ActionSequenceTest
	//GDX_DEFINE_TEST(GroupTest
	GDX_DEFINE_TEST(AlphaTest);
	//GDX_DEFINE_TEST(AtlasIssueTest
	//GDX_DEFINE_TEST(AssetManagerTest
	//GDX_DEFINE_TEST(FilterPerformanceTest
	//GDX_DEFINE_TEST(AudioDeviceTest
	//GDX_DEFINE_TEST(AudioRecorderTest
	//GDX_DEFINE_TEST(BitmapFontAlignmentTest
	//GDX_DEFINE_TEST(BitmapFontFlipTest
	//GDX_DEFINE_TEST(GroupCullingTest
	//GDX_DEFINE_TEST(GestureDetectorTest
	//GDX_DEFINE_TEST(LabelTest
	//GDX_DEFINE_TEST(BitmapFontTest
	//GDX_DEFINE_TEST(BlitTest
	//GDX_DEFINE_TEST(TableTest
	//GDX_DEFINE_TEST(BobTest
	//GDX_DEFINE_TEST(ImageScaleTest
	//GDX_DEFINE_TEST(Box2DInitialOverlapTest
	//GDX_DEFINE_TEST(Box2DTest
	//GDX_DEFINE_TEST(InterpolationTest
	//GDX_DEFINE_TEST(Box2DTestCollection
	//GDX_DEFINE_TEST(BufferUtilsTest
	//GDX_DEFINE_TEST(ImageTest
	//GDX_DEFINE_TEST(CompassTest
	//GDX_DEFINE_TEST(ComplexActionTest
	//GDX_DEFINE_TEST(CullTest
	//GDX_DEFINE_TEST(DeltaTimeTest
	//GDX_DEFINE_TEST(EdgeDetectionTest
	//GDX_DEFINE_TEST(ETC1Test
	//GDX_DEFINE_TEST(ExitTest
	//GDX_DEFINE_TEST(FilesTest
	//GDX_DEFINE_TEST(FlickScrollPaneTest
	//GDX_DEFINE_TEST(FloatTest
	//GDX_DEFINE_TEST(FrameBufferTest
	//GDX_DEFINE_TEST(FramebufferToTextureTest
	//GDX_DEFINE_TEST(FrustumTest
	//GDX_DEFINE_TEST(FullscreenTest
	//GDX_DEFINE_TEST(Gdx2DTest
	//GDX_DEFINE_TEST(GroupFadeTest
	//GDX_DEFINE_TEST(ImmediateModeRendererTest
	//GDX_DEFINE_TEST(ImmediateModeRendererAlphaTest
	//GDX_DEFINE_TEST(IndexBufferObjectClassTest
	//GDX_DEFINE_TEST(IndexBufferObjectShaderTest
	//GDX_DEFINE_TEST(InputTest
	//GDX_DEFINE_TEST(IntegerBitmapFontTest
	//GDX_DEFINE_TEST(InverseKinematicsTest
	//GDX_DEFINE_TEST(IsoCamTest
	//GDX_DEFINE_TEST(IsometricTileTest
	//GDX_DEFINE_TEST(KinematicBodyTest
	//GDX_DEFINE_TEST(LifeCycleTest
	//GDX_DEFINE_TEST(LineDrawingTest
	//GDX_DEFINE_TEST(ScrollPaneTest
	//GDX_DEFINE_TEST(ManagedTest
	//GDX_DEFINE_TEST(ManualBindTest
	GDX_DEFINE_TEST(MatrixJNITest);
	//GDX_DEFINE_TEST(MD5Test
	//GDX_DEFINE_TEST(MeshMultitextureTest
	GDX_DEFINE_TEST(MeshShaderTest);
	GDX_DEFINE_TEST(MeshTest);
	//GDX_DEFINE_TEST(MipMapTest
	//GDX_DEFINE_TEST(MultitouchTest
	//GDX_DEFINE_TEST(MusicTest
	//GDX_DEFINE_TEST(MyFirstTriangle
	//GDX_DEFINE_TEST(ObjTest
	//GDX_DEFINE_TEST(OnscreenKeyboardTest
	GDX_DEFINE_TEST(OrthoCamBorderTest);
	//GDX_DEFINE_TEST(ParallaxTest
	//GDX_DEFINE_TEST(ParticleEmitterTest
	//GDX_DEFINE_TEST(PickingTest
	//GDX_DEFINE_TEST(PixelsPerInchTest
	GDX_DEFINE_TEST(PixmapBlendingTest);
	GDX_DEFINE_TEST(PixmapTest);
  GDX_DEFINE_TEST(SpriteBatchRotationTest);
	//GDX_DEFINE_TEST(PreferencesTest
	//GDX_DEFINE_TEST(ProjectiveTextureTest
	//GDX_DEFINE_TEST(Pong
	//GDX_DEFINE_TEST(ProjectTest
	//GDX_DEFINE_TEST(RemoteTest
	//GDX_DEFINE_TEST(RotationTest
	//GDX_DEFINE_TEST(ShaderMultitextureTest
	//GDX_DEFINE_TEST(ShadowMappingTest
	//GDX_DEFINE_TEST(SplineTest
	//GDX_DEFINE_TEST(SimpleTest
	//GDX_DEFINE_TEST(SimpleAnimationTest
	//GDX_DEFINE_TEST(SimpleDecalTest
	//GDX_DEFINE_TEST(SimpleStageCullingTest
	//GDX_DEFINE_TEST(SoundTest
	//GDX_DEFINE_TEST(SpriteCacheTest
	//GDX_DEFINE_TEST(SpriteCacheOffsetTest
	//GDX_DEFINE_TEST(SpriteBatchRotationTest
	//GDX_DEFINE_TEST(SpriteBatchShaderTest
	GDX_DEFINE_TEST(SpriteBatchTest);
	//GDX_DEFINE_TEST(SpritePerformanceTest
	//GDX_DEFINE_TEST(SpritePerformanteTest2
	//GDX_DEFINE_TEST(StagePerformanceTest
	//GDX_DEFINE_TEST(StageTest
	//GDX_DEFINE_TEST(TerrainTest
	GDX_DEFINE_TEST(TextureDataTest);
	//GDX_DEFINE_TEST(TextureDownloadTest
	//GDX_DEFINE_TEST(TextureFormatTest
	//GDX_DEFINE_TEST(TextureAtlasTest
	//GDX_DEFINE_TEST(TextInputDialogTest
	//GDX_DEFINE_TEST(TextureRenderTest
	//GDX_DEFINE_TEST(TiledMapTest
	//GDX_DEFINE_TEST(TileTest
	//GDX_DEFINE_TEST(UITest
	//GDX_DEFINE_TEST(VBOVATest
	GDX_DEFINE_TEST(VertexArrayTest);
	//GDX_DEFINE_TEST(VertexBufferObjectTest
	GDX_DEFINE_TEST(VertexArrayClassTest);
	//GDX_DEFINE_TEST(VertexBufferObjectClassTest
	GDX_DEFINE_TEST(VertexBufferObjectShaderTest);
	//GDX_DEFINE_TEST(VibratorTest
	//GDX_DEFINE_TEST(VorbisTest
	//GDX_DEFINE_TEST(WaterRipples
	//GDX_DEFINE_TEST(HelloTriangle
	//GDX_DEFINE_TEST(SimpleVertexShader
	//GDX_DEFINE_TEST(ShapeRendererTest
	//GDX_DEFINE_TEST(MoveSpriteExample
	//GDX_DEFINE_TEST(StbTrueTypeTest
	//GDX_DEFINE_TEST(SoundTouchTest
	//GDX_DEFINE_TEST(Mpg123Test
	//GDX_DEFINE_TEST(WavTest
	//GDX_DEFINE_TEST(TextButtonTest
	//GDX_DEFINE_TEST(TextureBindTest
}

GdxTest* GdxTests::newTest(const char* name)
{
	GdxTest* ret = NULL;
	TestsMapIterator it = tests.find(name);
	if(it != tests.end())
	{
		ret = it->second();
	}
	return ret;
}