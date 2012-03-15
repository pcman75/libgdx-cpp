#pragma once

class Camera 
{
public:
  int x, y, width, height;

	Camera (int width, int height) 
  {
    x = y = 0;
		this->width = width;
		this->height = height;
	}
};
