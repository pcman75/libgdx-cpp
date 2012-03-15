#pragma once
#include "Gdx.h"
#include "Pixmap.h"
#include "Texture.h"
#include "TextureRegion.h"

class Art 
{
public:
  static TextureRegion*** guys;
	static TextureRegion*** player1;
	static TextureRegion*** player2;
	static TextureRegion*** walls;
	static TextureRegion*** gremlins;
	static TextureRegion bg;
	static Pixmap* level;
	static TextureRegion titleScreen;
	static TextureRegion shot;
	static TextureRegion*** buttons;

	static TextureRegion winScreen1;
	static TextureRegion winScreen2;

public:
	static void load () ;

	static TextureRegion*** split (std::string name, int width, int height) ;
  
	static TextureRegion*** split (std::string name, int width, int height, bool flipX) ;
  
	static TextureRegion load (std::string name, int width, int height) ;
  
// private static BufferedImage scale (BufferedImage src, int scale) {
// int w = src.getWidth() * scale;
// int h = src.getHeight() * scale;
// BufferedImage res = new BufferedImage(w, h, BufferedImage.TYPE_INT_ARGB);
// Graphics g = res.getGraphics();
// g.drawImage(src.getScaledInstance(w, h, Image.SCALE_AREA_AVERAGING), 0, 0, null);
// g.dispose();
// return res;
// }
//
// private static BufferedImage[][] mirrorsplit (BufferedImage src, int xs, int ys) {
// int xSlices = src.getWidth() / xs;
// int ySlices = src.getHeight() / ys;
// BufferedImage[][] res = new BufferedImage[xSlices][ySlices];
// for (int x = 0; x < xSlices; x++) {
// for (int y = 0; y < ySlices; y++) {
// res[x][y] = new BufferedImage(xs, ys, BufferedImage.TYPE_INT_ARGB);
// Graphics g = res[x][y].getGraphics();
// g.drawImage(src, xs, 0, 0, ys, x * xs, y * ys, (x + 1) * xs, (y + 1) * ys, null);
// g.dispose();
// }
// }
// return res;
// }

// private static BufferedImage[][] split(BufferedImage src, int xs, int ys) {
// int xSlices = src.getWidth() / xs;
// int ySlices = src.getHeight() / ys;
// BufferedImage[][] res = new BufferedImage[xSlices][ySlices];
// for (int x = 0; x < xSlices; x++) {
// for (int y = 0; y < ySlices; y++) {
// res[x][y] = new BufferedImage(xs, ys, BufferedImage.TYPE_INT_ARGB);
// Graphics g = res[x][y].getGraphics();
// g.drawImage(src, -x * xs, -y * ys, null);
// g.dispose();
// }
// }
// return res;
// }
};
