#pragma once
/*! struct. Kerning
desc.
Distances between two characters next to each other.
*/
struct Kerning
{
	Kerning(Ogre::uint c, float k) : character(c), kerning(k) {}
	Ogre::uint character;
	float kerning;
};

/*! struct. Glyph
desc.
Texture and size information about a single character loaded from a TextureAtlas.
*/
class Glyph : public Ogre::GeneralAllocatedObject
{

public:

	Glyph() : uvTop(0), uvBottom(0), uvWidth(0), uvHeight(0), uvLeft(0), uvRight(0), glyphWidth(0), glyphHeight(0), glyphAdvance(0), verticalOffset(0) {}

	~Glyph() {}

	Ogre::Vector2    texCoords[4];
	float uvTop, uvBottom, uvWidth, uvHeight, uvLeft, uvRight,
		glyphWidth, glyphHeight, glyphAdvance, verticalOffset;
	buffer<Kerning> kerning;

	// Get kerning value of a character to the right of another.
	// Ab -- get the kerning value of b, pass on A.
	inline const float getKerning(unsigned char left_of) const
	{
		if (kerning.size() == 0)
			return 0;
		for (size_t i = 0; i < kerning.size(); i++)
		{
			if (kerning[i].character == left_of)
				return kerning[i].kerning;
		}
		return 0;
	}

};

/*! class. Sprite
desc.
Portions of a texture from a TextureAtlas.
*/
class Sprite : public Ogre::GeneralAllocatedObject
{

public:

	Sprite() {}

	~Sprite() {}

	float uvTop, uvLeft, uvRight, uvBottom, spriteWidth, spriteHeight;
	Ogre::Vector2    texCoords[4];

};

/*! class. GlyphData
desc.
Collection of glyphs of the same size.
*/
class GlyphData : public Ogre::GeneralAllocatedObject
{

	friend class TextureAtlas;

public:

	GlyphData();

	~GlyphData();

	/*! function. getGlyph
	desc.
	Get a glyph (character information) from a specific character.
	note.
	If the character doesn't exist then a null pointer is returned.
	Do not delete the Glyph pointer.
	*/
	inline Glyph* getGlyph(Ogre::uint character) const
	{
		Ogre::uint safe_character = character - mRangeBegin;
		if (safe_character >= 0 && safe_character <= mGlyphs.size())
			return mGlyphs[safe_character];
		return 0;
	}

	std::vector<Glyph*>  mGlyphs;
	Ogre::uint           mRangeBegin, mRangeEnd;
	float           mSpaceLength,
		mLineHeight,
		mBaseline,
		mLineSpacing,
		mLetterSpacing,
		mMonoWidth;

};





/*! class. Polygon
desc.
A regular n-sided polygon.
*/
class Polygon : public Ogre::GeneralAllocatedObject
{

	friend class Layer;

public:

	/*! function. left
	desc.
	Get left position
	*/
	float  left() const
	{
		return mLeft;
	}

	/*! function. left
	desc.
	Set left position
	*/
	void  left(const float& left)
	{
		mLeft = left;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. left
	desc.
	Get left position
	*/
	float  top() const
	{
		return mTop;
	}

	/*! function. left
	desc.
	Set left position
	*/
	void  top(const float& top)
	{
		mTop = top;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. radius
	desc.
	Get the radius of the polygon
	*/
	float  radius() const
	{
		return mRadius;
	}

	/*! function. radius
	desc.
	Set the radius of the polygon
	*/
	void  radius(const float& radius)
	{
		mRadius = radius;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. sides
	desc.
	Get the number of sides the polygon has.
	*/
	size_t  sides() const
	{
		return mSides;
	}

	/*! function. sides
	desc.
	Set the number of sides the polygon has.
	note.
	Number of sides must be at least 2.
	*/
	void  sides(size_t sides)
	{
		if (sides < 3)
			sides = 3;
		mSides = sides;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. angle
	desc.
	Get the angle of the polygon
	*/
	Ogre::Radian  angle() const
	{
		return mAngle;
	}

	/*! function. angle
	desc.
	Set the angle of the polygon.
	*/
	void  angle(const Ogre::Radian& angle)
	{
		mAngle = angle;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. background_image
	desc.
	Get the sprite used as a background image or null pointer
	*/
	Sprite*  background_image() const
	{
		return mSprite;
	}

	/*! function. background_image
	desc.
	Set the sprite used as a background image or null pointer to clear.
	*/
	void  background_image(Sprite* sprite)
	{
		mSprite = sprite;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. background_image
	desc.
	Set the sprite used as a background image from a string.
	note.
	Use a empty string or "none" to clear.
	*/
	/*void  background_image(const Ogre::String& name_or_none)
	{
	if (name_or_none.size() == 0 || name_or_none == "none")
	mSprite = 0;
	else
	mSprite = mLayer->_getSprite(name_or_none);

	mDirty = true;
	mLayer->_markDirty();
	}
	*/
	/*! function. background_colour
	desc.
	Get the background colour.
	*/
	Ogre::ColourValue  background_colour() const
	{
		return mBackgroundColour;
	}

	/*! function. background_colour
	desc.
	Set the background colour.
	note.
	If there is a background sprite then it will be tinted by this colour.
	*/
	void  background_colour(const Ogre::ColourValue& colour)
	{
		mBackgroundColour = colour;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. border
	desc.
	Set the border width and colour
	*/
	void border(float width, const Ogre::ColourValue& colour)
	{
		mBorderColour = colour;
		mBorderWidth = width;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. border
	desc.
	Set the border width and colour
	*/
	void border(float width, XE::Colours::Colour colour)
	{
		if (colour == XE::Colours::None)
		{
			mBorderColour.a = 0;
			mBorderWidth = 0;
		}
		else
		{
			mBorderColour = webcolour(colour);
			mBorderWidth = width;
		}
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. border_colour
	desc.
	Get the border colour
	*/
	Ogre::ColourValue  border_colour() const
	{
		return mBorderColour;
	}

	/*! function. border_colour
	desc.
	Set the border colour
	*/
	void  border_colour(const Ogre::ColourValue& bordercolour)
	{
		mBorderColour = bordercolour;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. border_colour
	desc.
	Set the border colour
	*/
	void  border_colour(XE::Colours::Colour colour)
	{
		if (colour == XE::Colours::None)
		{
			mBorderColour.a = 0;
		}
		else
		{
			mBorderColour = webcolour(colour);
		}
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. border_width
	desc.
	Get the border width
	*/
	float  border_width() const
	{
		return mBorderWidth;
	}

	/*! function. border_width
	desc.
	Set the border width
	*/
	void  border_width(float width)
	{
		mBorderWidth = width;
		mDirty = true;
		mLayer->_markDirty();
	}


	/*! function. no_background
	desc.
	Don't draw the background.
	note.
	This just sets the background colour alpha to zero. Which on the next
	draw tells Rectangle to skip over drawing the background.
	*/
	void  no_background()
	{
		mBackgroundColour.a = 0;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. no_border
	desc.
	Don't draw the border.
	note.
	This just sets the border to zero. Which on the next
	draw tells Rectangle to skip over drawing the border.
	*/
	void  no_border()
	{
		mBorderWidth = 0;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. _redraw
	desc.
	Redraw the polygon
	note.
	This should not be needed to be called by the user.
	*/
	void  _redraw();

protected:


	Polygon(float left, float top, float radius, size_t sides, Layer* parent);

	~Polygon() {}

	Layer*             mLayer;
	float         mLeft, mTop, mRadius, mBorderWidth;
	Ogre::Radian       mAngle;
	size_t             mSides;
	Ogre::ColourValue  mBackgroundColour, mBorderColour;
	Sprite*            mSprite;
	bool               mDirty;
	buffer<Vertex>     mVertices;

};

class LineList : public Ogre::GeneralAllocatedObject
{

	friend class Layer;

public:

	/*! function. begin
	desc.
	Clear lines and start again
	*/
	void  begin(float lineThickness = 1.0f, const Ogre::ColourValue& colour = Ogre::ColourValue::White);

	/*! function. begin
	desc.
	Clear lines and start again
	*/
	void  begin(float lineThickness, XE::Colours::Colour colour)
	{
		begin(lineThickness, webcolour(colour));
	}

	/*! function. position
	desc.
	Extent the list to x and y.
	*/
	void  position(float x, float y);

	/*! function. position
	desc.
	Extent the list to given coordinates.
	*/
	void  position(const Ogre::Vector2&);

	/*! function. end
	desc.
	Stop line drawing and calculate vertices.
	note.
	If "isClosed" is set to true, then the line list joins back to the first position.
	*/
	void  end(bool isClosed = false);

	/*! function. _redraw
	desc.
	Redraw the line list
	note.
	This should not be needed to be called by the user.
	*/
	void  _redraw();

protected:

	LineList(Layer* parent);

	~LineList() {}

protected:

	Layer*                mLayer;
	float            mThickness;
	Ogre::ColourValue     mColour;
	bool                  mIsClosed;
	buffer<Ogre::Vector2> mPositions;
	bool                  mDirty;
	buffer<Vertex>        mVertices;
};

/*! class. QuadList
desc.
"ManualObject" like class to quickly draw rectangles, gradients, sprites and borders.
*/
class QuadList : public Ogre::GeneralAllocatedObject
{

	friend class Layer;

public:

	/*! function. begin
	desc.
	Clear everything and start again
	*/
	void  begin();

	/*! function. rectangle
	desc.
	Draw a rectangle sized w,h at x,y
	*/
	void  rectangle(float x, float y, float w, float h, const Ogre::ColourValue = Ogre::ColourValue::White);

	/*! function. gradient
	desc.
	Draw a gradient rectangle sized w,h at x,y
	*/
	void  gradient(float x, float y, float w, float h, Gradient gradient, const Ogre::ColourValue& colourA = Ogre::ColourValue::White, const Ogre::ColourValue& colourB = Ogre::ColourValue::White);

	/*! function. gradient
	desc.
	Draw a gradient rectangle sized w,h at x,y
	*/
	void  gradient(float x, float y, float w, float h, Gradient gradient, const XE::Colours::Colour& colourA, const XE::Colours::Colour& colourB)
	{
		this->gradient(x, y, w, h, gradient, webcolour(colourA), webcolour(colourB));
	}

	/*! function. sprite
	desc.
	Draw a sprite sized w,h at x,y
	*/
	void  sprite(float x, float y, float w, float h, Sprite*);

	/*! function. border
	desc.
	Draw a border sized w,h at x,y of a thickness
	*/
	void  border(float x, float y, float w, float h, float thickness, const Ogre::ColourValue& = Ogre::ColourValue::White);

	/*! function. border
	desc.
	Draw a border sized w,h at x,y of a thickness
	*/
	void  border(float x, float y, float w, float h, float thickness, const XE::Colours::Colour& colour)
	{
		border(x, y, w, h, thickness, webcolour(colour));
	}

	/*! function. border
	desc.
	Draw a border sized w,h at x,y of a thickness
	*/
	void  border(float x, float y, float w, float h, float thickness, const Ogre::ColourValue& northColour, const Ogre::ColourValue& eastColour, const Ogre::ColourValue& southColour, const Ogre::ColourValue& westColour);

	/*! function. border
	desc.
	Draw a border sized w,h at x,y of a thickness
	*/
	void  border(float x, float y, float w, float h, float thickness, const XE::Colours::Colour& northColour, const XE::Colours::Colour& eastColour, const XE::Colours::Colour& southColour, const XE::Colours::Colour& westColour)
	{
		border(x, y, w, h, thickness, webcolour(northColour), webcolour(eastColour), webcolour(southColour), webcolour(westColour));
	}

	/*! function. glyph
	desc.
	Draw a glpyh
	*/
	void  glyph(Ogre::uint glyphDataIndex, float x, float y, unsigned char character, const Ogre::ColourValue& colour);

	/*! function. glyph
	desc.
	Draw a glyph with a custom size.
	*/
	void  glyph(Ogre::uint glyphDataIndex, float x, float y, float w, float h, unsigned char character, const Ogre::ColourValue& colour);

	/*! function. glyph
	desc.
	Draw a glpyh
	*/
	void  glyph(Ogre::uint glyphDataIndex, float x, float y, unsigned char character, const XE::Colours::Colour& colour)
	{
		glyph(glyphDataIndex, x, y, character, webcolour(colour));
	}

	/*! function. glyph
	desc.
	Draw a glyph with a custom size.
	*/
	void  glyph(Ogre::uint glyphDataIndex, float x, float y, float w, float h, unsigned char character, const XE::Colours::Colour& colour)
	{
		glyph(glyphDataIndex, x, y, w, h, character, webcolour(colour));
	}

	/*! function. end
	desc.
	Stop drawing and calculate vertices.
	*/
	void  end();

	void  _redraw();

protected:

	QuadList(Layer*);

	~QuadList() {}

	struct Quad
	{
		Ogre::Vector2        mPosition[4];
		Ogre::Vector2        mUV[4];
		Ogre::ColourValue    mColour[4];
	};

	Ogre::Vector2         mWhiteUV;
	Layer*                mLayer;
	buffer<Quad>          mQuads;
	buffer<Vertex>        mVertices;
	bool                  mDirty;

};



/* class. Caption
desc.
A multi-line collection of text formatted by a light markup language, that can
switch colours, change to monospace and insert sprites directly into the text.
*/
class MarkupText : public Ogre::GeneralAllocatedObject
{

	friend class Layer;

public:

	/*! function. top
	desc.
	Get where the text should be drawn vertically.
	*/
	float  left() const
	{
		return mLeft;
	}

	/*! function. top
	desc.
	Set where the text should be drawn vertically.
	note.
	If the TextAlignment is Right Aligned, then this will be the right-side of the last character drawn (with in width limits).
	If the TextAlignment is Centre Aligned, then this will be the center of the drawn text drawn (with in width limits).
	*/
	void  left(const float& left)
	{
		mLeft = left;
		mDirty = true;
		mTextDirty = true;
		mLayer->_markDirty();
	}

	/*! function. top
	desc.
	Get where the text should be drawn vertically.
	*/
	float  top() const
	{
		return mTop;
	}

	/*! function. top
	desc.
	Set where the text should be drawn vertically.
	*/
	void  top(const float& top)
	{
		mTop = top;
		mDirty = true;
		mTextDirty = true;
		mLayer->_markDirty();
	}


	/*! function. size
	desc.
	Set the maximum width and height of the text can draw into.
	*/
	void size(const float& width, const float& height)
	{
		mWidth = width;
		mHeight = height;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. width
	desc.
	Get the maximum width of the text can draw into.
	*/
	float width() const
	{
		return mWidth;
	}

	/*! function. width
	desc.
	Set the maximum width of the text can draw into.
	*/
	void  width(const float& width)
	{
		mWidth = width;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. height
	desc.
	Get the maximum height of the text can draw into.
	*/
	float height() const
	{
		return mHeight;
	}

	/*! function. height
	desc.
	Set the maximum height of the text can draw into.
	*/
	void  height(const float& height)
	{
		mHeight = height;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. maxTextWidth
	desc.
	Get the width of the text once drawn.
	*/
	float maxTextWidth()
	{
		_calculateCharacters();
		return mMaxTextWidth;
	}

	/*! function. caption
	desc.
	Get the text indented to show.
	*/
	Ogre::String  text() const
	{
		return mText;
	}

	/*! function. alignment
	desc.
	Set the text to show.
	*/
	void  text(const Ogre::String& text)
	{
		mText = text;
		mTextDirty = true;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. background
	desc.
	Get the background colour
	*/
	Ogre::ColourValue  background() const
	{
		return mBackground;
	}

	/*! function. background
	desc.
	Set the background colour
	*/
	void  background(const Ogre::ColourValue& background)
	{
		mBackground = background;
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. background
	desc.
	Set the background colour
	*/
	void  background(XE::Colours::Colour background)
	{
		if (background == Colours::None)
			mBackground.a = 0;
		else
			mBackground = webcolour(background);
		mDirty = true;
		mLayer->_markDirty();
	}

	/*! function. _redraw
	desc.
	Redraw the text.
	note.
	This shouldn't be need to be called by the user.
	*/
	void               _redraw();

	void               _calculateCharacters();

protected:

	MarkupText(Ogre::uint defaultGlyphIndex, float left, float top, const Ogre::String& text, Layer* parent);

	~MarkupText() {}

protected:

	struct Character
	{
		Ogre::Vector2        mPosition[4];
		Ogre::Vector2        mUV[4];
		Ogre::ColourValue    mColour;
		size_t               mIndex;
	};

	Layer*                mLayer;
	GlyphData*            mDefaultGlyphData;
	float            mLeft, mTop, mWidth, mHeight;
	float            mMaxTextWidth;
	Ogre::String          mText;
	Ogre::ColourValue     mBackground;
	bool                  mDirty, mTextDirty;
	buffer<Character>     mCharacters;
	buffer<Vertex>        mVertices;
	size_t                mClippedIndex;

};