
#include <Ogre/OgreMain/include/OgreManualObject.h>

class SelectionRectangle
	: public Ogre::ManualObject
{
public:
	SelectionRectangle(const Ogre::String& name)
		: Ogre::ManualObject(name)
	{
			setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
			setUseIdentityProjection(true);
			setUseIdentityView(true);
			setQueryFlags(0);
			SetCorners(0, 0, 0, 0);
			setVisible(false);
	}

	void SetCorners(float left, float top, float right, float bottom)
	{
		left = left * 2 - 1;
		right = right * 2 - 1;
		top = 1 - top * 2;
		bottom = 1 - bottom * 2;

		clear();
		begin("", Ogre::RenderOperation::OT_LINE_STRIP);
		position(left, top, -1);
		position(right, top, -1);
		position(right, bottom, -1);
		position(left, bottom, -1);
		position(left, top, -1);
		end();

		setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);
	}

	void SetCorners(const Ogre::Vector2& topLeft, const Ogre::Vector2& bottomRight)
	{
		SetCorners(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
	}
};
