#include "stdafx.h"
#include "Assets.h"
#include "Settings.h"

Texture* Assets::background;
TextureRegion* Assets::backgroundRegion;

Texture* Assets::items;
TextureRegion* Assets::mainMenu;
TextureRegion* Assets::pauseMenu;
TextureRegion* Assets::ready;
TextureRegion* Assets::gameOver;
TextureRegion* Assets::highScoresRegion;
TextureRegion* Assets::logo;
TextureRegion* Assets::soundOn;
TextureRegion* Assets::soundOff;
TextureRegion* Assets::arrow;
TextureRegion* Assets::pause;
TextureRegion* Assets::spring;
TextureRegion* Assets::castle;
Animation* Assets::coinAnim;
Animation* Assets::bobJump;
Animation* Assets::bobFall;
TextureRegion* Assets::bobHit;
Animation* Assets::squirrelFly;
TextureRegion* Assets::platform;
Animation* Assets::brakingPlatform;
BitmapFont* Assets::font;

Music* Assets::music;
Sound* Assets::jumpSound;
Sound* Assets::highJumpSound;
Sound* Assets::hitSound;
Sound* Assets::coinSound;
Sound* Assets::clickSound;

Texture* Assets::loadTexture(const char* file)
{
	return new Texture(Gdx.files->internalHandle(file));
}

void Assets::load()
{
	background = loadTexture("data/background.png");
	backgroundRegion = new TextureRegion(background, 0, 0, 320, 480);

	items = loadTexture("data/items.png");
	mainMenu = new TextureRegion(items, 0, 224, 300, 110);
	pauseMenu = new TextureRegion(items, 224, 128, 192, 96);
	ready = new TextureRegion(items, 320, 224, 192, 32);
	gameOver = new TextureRegion(items, 352, 256, 160, 96);
	highScoresRegion = new TextureRegion(Assets::items, 0, 257, 300, 110 / 3);
	logo = new TextureRegion(items, 0, 352, 274, 142);
	soundOff = new TextureRegion(items, 0, 0, 64, 64);
	soundOn = new TextureRegion(items, 64, 0, 64, 64);
	arrow = new TextureRegion(items, 0, 64, 64, 64);
	pause = new TextureRegion(items, 64, 64, 64, 64);

	spring = new TextureRegion(items, 128, 0, 32, 32);
	castle = new TextureRegion(items, 128, 64, 64, 64);

	//coin
	std::list<TextureRegion*> coinFrames;
	coinFrames.push_back(new TextureRegion(items, 128, 32, 32, 32));
	coinFrames.push_back(new TextureRegion(items, 160, 32, 32, 32));
	coinFrames.push_back(new TextureRegion(items, 192, 32, 32, 32));
	coinFrames.push_back(new TextureRegion(items, 160, 32, 32, 32));
	coinAnim = new Animation(0.2f, coinFrames);

	//bob
	std::list<TextureRegion*> bobJumpFrames;
	bobJumpFrames.push_back(new TextureRegion(items, 0, 128, 32, 32));
	bobJumpFrames.push_back(new TextureRegion(items, 32, 128, 32, 32));
	bobJump = new Animation(0.2f, bobJumpFrames);
	
	std::list<TextureRegion*> bobFallFrames;
	bobFallFrames.push_back(new TextureRegion(items, 64, 128, 32, 32));
	bobFallFrames.push_back(new TextureRegion(items, 96, 128, 32, 32));
	bobFall = new Animation(0.2f, bobFallFrames);

	bobHit = new TextureRegion(items, 128, 128, 32, 32);

	std::list<TextureRegion*> squirrelFlyFrames;
	squirrelFlyFrames.push_back(new TextureRegion(items, 0, 160, 32, 32));
	squirrelFlyFrames.push_back(new TextureRegion(items, 32, 160, 32, 32));
	squirrelFly = new Animation(0.2f, squirrelFlyFrames);

	platform = new TextureRegion(items, 64, 160, 64, 16);

	std::list<TextureRegion*> brakingPlatformFrames;
	brakingPlatformFrames.push_back(new TextureRegion(items, 64, 160, 64, 16));
	brakingPlatformFrames.push_back(new TextureRegion(items, 64, 176, 64, 16));
	brakingPlatformFrames.push_back(new TextureRegion(items, 64, 192, 64, 16)); 
	brakingPlatformFrames.push_back(new TextureRegion(items, 64, 208, 64, 16));
	brakingPlatform = new Animation(0.2f, brakingPlatformFrames);

	font = new BitmapFont(Gdx.files->internalHandle("data/font.fnt"), Gdx.files->internalHandle("data/font.png"), false);

	//TODO: enable sound
	/*
	music = Gdx.audio->newMusic(Gdx.files->internalHandle("data/music.mp3"));
	music->setLooping(true);
	music->setVolume(0.5f);
	if(Settings::soundEnabled) 
		music->play();

	jumpSound = Gdx.audio->newSound(Gdx.files->internalHandle("data/jump.ogg"));
	highJumpSound = Gdx.audio->newSound(Gdx.files->internalHandle("data/highjump.ogg"));
	hitSound = Gdx.audio->newSound(Gdx.files->internalHandle("data/hit.ogg"));
	coinSound = Gdx.audio->newSound(Gdx.files->internalHandle("data/coin.ogg"));
	clickSound = Gdx.audio->newSound(Gdx.files->internalHandle("data/click.ogg"));
	*/
}

void Assets::playSound(Sound* sound)
{
	/*TODO: enable sound
	if(Settings::soundEnabled) 
		sound->play(1);
	*/
}

