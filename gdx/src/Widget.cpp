#include "stdafx.h"
#include "Widget.h"
#include "Group.h"

Widget::Widget() 
  : Actor( NULL)
{
  bNeedsLayout = true;
}

Widget::Widget ( std::string name) 
  : Actor( name)
{
  bNeedsLayout = true;
}

float Widget::getMinWidth () 
{
	return getPrefWidth();
}

float Widget::getMinHeight () 
{
	return getPrefHeight();
}

float Widget::getPrefWidth () 
{
	return 0;
}

float Widget::getPrefHeight () 
{
	return 0;
}

float Widget::getMaxWidth () 
{
	return 0;
}

float Widget::getMaxHeight () 
{
	return 0;
}

void Widget::invalidate () 
{
	bNeedsLayout = true;
}

void Widget::validate () 
{
	if (!bNeedsLayout) return;
	bNeedsLayout = false;
	layout();
}

/** Returns true if the widget's layout has been {@link #invalidate() invalidated}. */
bool Widget::needsLayout () 
{
	return bNeedsLayout;
}

void Widget::invalidateHierarchy () 
{
	invalidate();

  Layout* pParentLayout = dynamic_cast<Layout*>( parent);
  if( NULL != pParentLayout)
  {
	  pParentLayout->invalidateHierarchy();
  }
}

void Widget::pack () 
{
	float newWidth = getPrefWidth();
	float newHeight = getPrefHeight();
	if (newWidth != width || newHeight != height) 
  {
		width = newWidth;
		height = newHeight;
		invalidate();
		validate();
	}
}

/** If this method is overridden, the super method or {@link #validate()} should be called to ensure the widget is laid out. */
void Widget::draw (SpriteBatch* batch, float parentAlpha) 
{
	validate();
}

Actor* Widget::hit (float x, float y) 
{
	return x > 0 && x < width && y > 0 && y < height ? this : NULL;
}

void Widget::layout () 
{
}

bool Widget::touchDown (float x, float y, int pointer) 
{
	return false;
}

void Widget::touchUp (float x, float y, int pointer) 
{
}

void Widget::touchDragged (float x, float y, int pointer) 
{
}

/** This modifies the specified point in the actor's coordinates to be in the stage's coordinates. Note this method will ONLY
	* work properly for screen aligned, unrotated, unscaled actors! */
void Widget::toScreenCoordinates (Actor* actor, Vector2 point) 
{
	point.x += actor->x;
	point.y += actor->y;
	Actor* parent = ( Actor*) actor->parent;
	while (parent != NULL) 
  {
    if ( ObjectGroup == parent->type()) 
    {
			point.x += parent->x;
			point.y += parent->y;
		}
		parent = ( Actor*) parent->parent;
	}
}