
#pragma once
#include "Group.h"
#include "Layout.h"


/** A {@link Group} that participates in layout and provides a minimum, preferred, and maximum size.
 * <p>
 * The default preferred size of a widget group is 0 and this is almost always overridden by a subclass. The default minimum size
 * returns the preferred size, so a subclass may choose to return 0 if it wants to allow itself to be sized smaller. The default
 * maximum size is 0, which means no maximum size.
 * <p>
 * See {@link Layout} for details on how a widget group should participate in layout. A widget group's mutator methods should call
 * {@link #invalidate()} or {@link #invalidateHierarchy()} as needed. By default, invalidateHierarchy is called when child widgets
 * are added and removed.
 * @author Nathan Sweet */
class WidgetGroup : public Group , Layout 
{
private:
  bool bNeedsLayout;

public:
	WidgetGroup () ;
	WidgetGroup( std::string name) ;

	float getMinWidth () ;

	float getMinHeight () ;

	float getMaxWidth () ;

	float getMaxHeight () ;

	void invalidate () ;

	void validate () ;

	/** Returns true if the widget's layout has been {@link #invalidate() invalidated}. */
	bool needsLayout () ;

	void invalidateHierarchy () ;

	void childrenChanged () ;

	void pack () ;

	void layout () ;

	/** If this method is overridden, the super method or {@link #validate()} should be called to ensure the widget group is laid
	 * out. */
	void draw (SpriteBatch* batch, float parentAlpha) ;

};
