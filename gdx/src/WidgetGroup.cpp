#include "stdafx.h"
#include "WidgetGroup.h"


WidgetGroup::WidgetGroup () 
{
  bNeedsLayout = true;
}

WidgetGroup::WidgetGroup( std::string name) 
  : Group( name)
{
  bNeedsLayout = true;
}

float WidgetGroup::getMinWidth () 
{
	return getPrefWidth();
}

float WidgetGroup::getMinHeight () 
{
	return getPrefHeight();
}

float WidgetGroup::getMaxWidth () 
{
	return 0;
}

float WidgetGroup::getMaxHeight () 
{
	return 0;
}

void WidgetGroup::invalidate () 
{
	bNeedsLayout = true;
}

void WidgetGroup::validate () 
{
	if (!bNeedsLayout) return;
	bNeedsLayout = false;
	layout();
}

/** Returns true if the widget's layout has been {@link #invalidate() invalidated}. */
bool WidgetGroup::needsLayout () 
{
	return bNeedsLayout;
}

void WidgetGroup::invalidateHierarchy () 
{
	invalidate();
  Layout* pParentLayout = dynamic_cast<Layout*>( parent);
  if( NULL != pParentLayout)
  {
	  pParentLayout->invalidateHierarchy();
  }
}

void WidgetGroup::childrenChanged () 
{
	invalidateHierarchy();
}

void WidgetGroup::pack () 
{
	float newWidth = getPrefWidth();
	float newHeight = getPrefHeight();
	if (newWidth != width || newHeight != height) {
		width = newWidth;
		height = newHeight;
		invalidate();
		validate();
	}
}

void WidgetGroup::layout () 
{
}

/** If this method is overridden, the super method or {@link #validate()} should be called to ensure the widget group is laid
	* out. */
void WidgetGroup::draw (SpriteBatch* batch, float parentAlpha) 
{
	validate();
	Group::draw( batch, parentAlpha);
}