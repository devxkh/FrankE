/*
	Gorilla
	-------

	Copyright (c) 2010 Robin Southern

	Additional contributions by:

	- Murat Sari
	- Nigel Atkinson

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.

*/

#ifndef GORILLA_H
#define GORILLA_H

//#include <Ogre/OgreMain/include/Ogre.h>
#include <Ogre/OgreMain/include/OgreMemoryAllocatorConfig.h>
#include <Ogre/OgreMain/include/OgreVector3.h>
#include <Ogre/OgreMain/include/OgreVector2.h>
#include <Ogre/OgreMain/include/OgreColourValue.h>
#include <Ogre/OgreMain/include/OgreMaterial.h>
#include <Ogre/OgreMain/include/OgreTextureManager.h>
#include <Ogre/OgreMain/include/OgreHardwareVertexBuffer.h>
#include <Ogre/OgreMain/include/OgreConfigFile.h>
#include <Ogre/OgreMain/include/OgreTexture.h>
//#include <Ogre/OgreMain/include/OgreFrameListener.h>


#ifndef GORILLA_USES_EXCEPTIONS
#  define GORILLA_USES_EXCEPTIONS 0
#endif

#if OGRE_COMP == OGRE_COMPILER_GNUC
#   define __FUNC__ __PRETTY_FUNCTION__
#elif OGRE_COMP != OGRE_COMPILER_BORL
#   define __FUNC__ "No function name info"
#endif


#define PUSH_VERTEX(VERTICES, VERTEX, X, Y, UV, COLOUR)   \
  VERTEX.position.x = X;                                           \
  VERTEX.position.y = Y;                                           \
  VERTEX.position.z = 0;                                           \
  VERTEX.uv.x = UV.x;                                              \
  VERTEX.uv.y = UV.y;                                              \
  VERTEX.colour = COLOUR;                                          \
  VERTICES.push_back(VERTEX);                                       

#define PUSH_TRIANGLE(VERTICES, VERTEX, A, B, C, UV, COLOUR)       \
  PUSH_VERTEX(VERTICES, VERTEX, A.x, A.y, UV, COLOUR) \
  PUSH_VERTEX(VERTICES, VERTEX, B.x, B.y, UV, COLOUR) \
  PUSH_VERTEX(VERTICES, VERTEX, C.x, C.y, UV, COLOUR) 

#define PUSH_QUAD(VERTICES, VERTEX, POSITIONS, COLOURS, UV)   \
  PUSH_VERTEX(VERTICES, VERTEX, POSITIONS[3].x, POSITIONS[3].y, UV[3], COLOURS[3]) \
  PUSH_VERTEX(VERTICES, VERTEX, POSITIONS[1].x, POSITIONS[1].y, UV[1], COLOURS[1]) \
  PUSH_VERTEX(VERTICES, VERTEX, POSITIONS[0].x, POSITIONS[0].y, UV[0], COLOURS[0]) \
     \
  PUSH_VERTEX(VERTICES, VERTEX, POSITIONS[3].x, POSITIONS[3].y, UV[3], COLOURS[3]) \
  PUSH_VERTEX(VERTICES, VERTEX, POSITIONS[2].x, POSITIONS[2].y, UV[2], COLOURS[2]) \
  PUSH_VERTEX(VERTICES, VERTEX, POSITIONS[1].x, POSITIONS[1].y, UV[1], COLOURS[1])  

#define PUSH_QUAD2(VERTICES, VERTEX, POSITIONS, COLOUR, UV)   \
  PUSH_VERTEX(VERTICES, VERTEX, POSITIONS[3].x, POSITIONS[3].y, UV[3], COLOUR) \
  PUSH_VERTEX(VERTICES, VERTEX, POSITIONS[1].x, POSITIONS[1].y, UV[1], COLOUR) \
  PUSH_VERTEX(VERTICES, VERTEX, POSITIONS[0].x, POSITIONS[0].y, UV[0], COLOUR) \
     \
  PUSH_VERTEX(VERTICES, VERTEX, POSITIONS[3].x, POSITIONS[3].y, UV[3], COLOUR) \
  PUSH_VERTEX(VERTICES, VERTEX, POSITIONS[2].x, POSITIONS[2].y, UV[2], COLOUR) \
  PUSH_VERTEX(VERTICES, VERTEX, POSITIONS[1].x, POSITIONS[1].y, UV[1], COLOUR)  



namespace XE
{

	//class Silverback;
	class TextureAtlas;
	//class LayerContainer;
	class Screen;
	class ScreenRenderable;
//	class Layer;
	/*class Rectangle;
	class Polygon;
	class LineList;
	class QuadList;
	class Caption;
	class MarkupText;*/




	template<typename T> struct VectorType
	{
#if OGRE_VERSION <= 67077 // If the version is less than or equal to 1.6.5
		typedef std::vector<T> type;
#else
		typedef typename Ogre::vector<T>::type type;
#endif
	};

	namespace Colours
	{
		enum Colour
		{
			None = 0, // No Colour.
			AliceBlue = 0xf0f8ff, Gainsboro = 0xdcdcdc, MistyRose = 0xffe4e1,
			AntiqueWhite = 0xfaebd7, GhostWhite = 0xf8f8ff, Moccasin = 0xffe4b5,
			Aqua = 0x00ffff, Gold = 0xffd700, NavajoWhite = 0xffdead,
			Aquamarine = 0x7fffd4, Goldenrod = 0xdaa520, Navy = 0x000080,
			Azure = 0xf0ffff, Gray = 0x808080, OldLace = 0xfdf5e6,
			Beige = 0xf5f5dc, Green = 0x008000, Olive = 0x808000,
			Bisque = 0xffe4c4, GreenYellow = 0xadff2f, OliveDrab = 0x6b8e23,
			Black = 0x000000, Grey = 0x808080, Orange = 0xffa500,
			BlanchedAlmond = 0xffebcd, Honeydew = 0xf0fff0, OrangeRed = 0xff4500,
			Blue = 0x0000ff, HotPink = 0xff69b4, Orchid = 0xda70d6,
			BlueViolet = 0x8a2be2, IndianRed = 0xcd5c5c, PaleGoldenrod = 0xeee8aa,
			Brown = 0xa52a2a, Indigo = 0x4b0082, PaleGreen = 0x98fb98,
			Burlywood = 0xdeb887, Ivory = 0xfffff0, PaleTurquoise = 0xafeeee,
			CadetBlue = 0x5f9ea0, Khaki = 0xf0e68c, PaleVioletRed = 0xdb7093,
			Chartreuse = 0x7fff00, Lavender = 0xe6e6fa, PapayaWhip = 0xffefd5,
			Chocolate = 0xd2691e, LavenderBlush = 0xfff0f5, PeachPuff = 0xffdab9,
			Coral = 0xff7f50, LawnGreen = 0x7cfc00, Peru = 0xcd853f,
			CornflowerBlue = 0x6495ed, LemonChiffon = 0xfffacd, Pink = 0xffc0cb,
			Cornsilk = 0xfff8dc, LightBlue = 0xadd8e6, Plum = 0xdda0dd,
			Crimson = 0xdc143c, LightCoral = 0xf08080, PowderBlue = 0xb0e0e6,
			Cyan = 0x00ffff, LightCyan = 0xe0ffff, Purple = 0x800080,
			DarkBlue = 0x00008b, LightGoldenrodyellow = 0xfafad2, Red = 0xff0000,
			DarkCyan = 0x008b8b, LightGray = 0xd3d3d3, RosyBrown = 0xbc8f8f,
			DarkGoldenrod = 0xb8860b, LightGreen = 0x90ee90, RoyalBlue = 0x4169e1,
			DarkGray = 0xa9a9a9, LightGrey = 0xd3d3d3, SaddleBrown = 0x8b4513,
			DarkGreen = 0x006400, LightPink = 0xffb6c1, Salmon = 0xfa8072,
			DarkGrey = 0xa9a9a9, LightSalmon = 0xffa07a, SandyBrown = 0xf4a460,
			DarkKhaki = 0xbdb76b, LightSeagreen = 0x20b2aa, SeaGreen = 0x2e8b57,
			DarkMagenta = 0x8b008b, LightSkyblue = 0x87cefa, SeaShell = 0xfff5ee,
			DarkOlivegreen = 0x556b2f, LightSlategray = 0x778899, Sienna = 0xa0522d,
			DarkOrange = 0xff8c00, LightSlategrey = 0x778899, Silver = 0xc0c0c0,
			DarkOrchid = 0x9932cc, LightSteelblue = 0xb0c4de, SkyBlue = 0x87ceeb,
			DarkRed = 0x8b0000, LightYellow = 0xffffe0, SlateBlue = 0x6a5acd,
			DarkSalmon = 0xe9967a, Lime = 0x00ff00, SlateGray = 0x708090,
			DarkSeagreen = 0x8fbc8f, LimeGreen = 0x32cd32, SlateGrey = 0x708090,
			DarkSlateblue = 0x483d8b, Linen = 0xfaf0e6, Snow = 0xfffafa,
			DarkSlategray = 0x2f4f4f, Magenta = 0xff00ff, SpringGreen = 0x00ff7f,
			DarkSlategrey = 0x2f4f4f, Maroon = 0x800000, SteelBlue = 0x4682b4,
			DarkTurquoise = 0x00ced1, MediumAquamarine = 0x66cdaa, Tan = 0xd2b48c,
			DarkViolet = 0x9400d3, MediumBlue = 0x0000cd, Teal = 0x008080,
			DeepPink = 0xff1493, MediumOrchid = 0xba55d3, Thistle = 0xd8bfd8,
			DeepSkyblue = 0x00bfff, MediumPurple = 0x9370db, Tomato = 0xff6347,
			DimGray = 0x696969, MediumSeaGreen = 0x3cb371, Turquoise = 0x40e0d0,
			DimGrey = 0x696969, MediumSlateBlue = 0x7b68ee, Violet = 0xee82ee,
			DodgerBlue = 0x1e90ff, MediumSpringGreen = 0x00fa9a, Wheat = 0xf5deb3,
			FireBrick = 0xb22222, MediumTurquoise = 0x48d1cc, White = 0xffffff,
			FloralWhite = 0xfffaf0, MediumBioletRed = 0xc71585, WhiteSmoke = 0xf5f5f5,
			ForestGreen = 0x228b22, MidnightBlue = 0x191970, Yellow = 0xffff00,
			Fuchsia = 0xff00ff, MintCream = 0xf5fffa, YellowGreen = 0x9acd32
		}; // Colour
	} // namespace Colours

	/*! function. rgb
		desc.
			Convert three/four RGBA values into an Ogre::ColourValue
	*/
	Ogre::ColourValue rgb(Ogre::uchar r, Ogre::uchar g, Ogre::uchar b, Ogre::uchar a = 255);

	/*! function. webcolour
		desc.
			Turn a webcolour from the XE::Colours::Colour enum into an Ogre::ColourValue
	*/
	Ogre::ColourValue webcolour(Colours::Colour, float alpha = 1.0);

	/*! enum. Gradient
		desc.
			Directions for background gradients
	*/
	enum Gradient
	{
		Gradient_NorthSouth,
		Gradient_WestEast,
		Gradient_Diagonal
	};

	/*! enum. Border
		desc.
			Border Directions


			+---------------------+
			|\       NORTH       /|
			| \                 / |
			|  +---------------+  |
			|  |               |  |
			| W|               |E |
			| E|               |A |
			| S|               |S |
			| T|               |T |
			|  |               |  |
			|  +---------------+  |
			| /      SOUTH      \ |
			|/                   \|
			+---------------------+
	*/
	enum Border
	{
		Border_North = 0,
		Border_South = 1,
		Border_East = 2,
		Border_West = 3
	};

	/*! enum. QuadCorner
		desc.
			Names of each corner/vertex of a Quad
	*/
	enum QuadCorner
	{
		TopLeft = 0,
		TopRight = 1,
		BottomRight = 2,
		BottomLeft = 3
	};

	/*! enum. TextAlignment
		desc.
			Horizontal text alignment for captions.
	*/
	enum TextAlignment
	{
		TextAlign_Left,   // Place the text to where left is (X = left)
		TextAlign_Right,  // Place the text to the right of left (X = left - text_width)
		TextAlign_Centre, // Place the text centered at left (X = left - (text_width / 2 ) )
	};

	/*! enum. VerticalAlignment
		desc.
			Vertical text alignment for captions.
	*/
	enum VerticalAlignment
	{
		VerticalAlign_Top,
		VerticalAlign_Middle,
		VerticalAlign_Bottom
	};

	/*! enum. buffer<T>
		desc.
			Internal container class that is similar to std::vector
	*/
	//template<typename T> class buffer
	//{

	//public:

	//	inline buffer() : mBuffer(0), mUsed(0), mCapacity(0)
	//	{ // no code.
	//	}

	//	inline ~buffer()
	//	{
	//		if (mBuffer && mCapacity)
	//			OGRE_FREE(mBuffer, Ogre::MEMCATEGORY_GEOMETRY);
	//	}

	//	inline size_t size() const
	//	{
	//		return mUsed;
	//	}

	//	inline size_t capacity() const
	//	{
	//		return mCapacity;
	//	}

	//	inline T& operator[](size_t index)
	//	{
	//		return *(mBuffer + index);
	//	}

	//	inline const T& operator[](size_t index) const
	//	{
	//		return *(mBuffer + index);
	//	}

	//	inline T& at(size_t index)
	//	{
	//		return *(mBuffer + index);
	//	}

	//	inline const T& at(size_t index) const
	//	{
	//		return *(mBuffer + index);
	//	}

	//	inline void remove_all()
	//	{
	//		mUsed = 0;
	//	}

	//	inline void resize(size_t new_capacity)
	//	{
	//		T* new_buffer = (T*)OGRE_MALLOC(sizeof(T) * new_capacity, Ogre::MEMCATEGORY_GEOMETRY);

	//		if (mUsed != 0)
	//		{
	//			if (mUsed < new_capacity)  // Copy all
	//				std::copy(mBuffer, mBuffer + mUsed, new_buffer);
	//			else if (mUsed >= new_capacity) // Copy some
	//				std::copy(mBuffer, mBuffer + new_capacity, new_buffer);
	//		}

	//		OGRE_FREE(mBuffer, Ogre::MEMCATEGORY_GEOMETRY);
	//		mCapacity = new_capacity;
	//		mBuffer = new_buffer;
	//	}

	//	inline void push_back(const T& value)
	//	{
	//		if (mUsed == mCapacity)
	//			resize(mUsed == 0 ? 1 : mUsed * 2);
	//		*(mBuffer + mUsed) = value;
	//		mUsed++;
	//	}

	//	inline void pop_back()
	//	{
	//		if (mUsed != 0)
	//			mUsed--;
	//	}

	//	inline void erase(size_t index)
	//	{
	//		*(mBuffer + index) = *(mBuffer + mUsed - 1);
	//		mUsed--;
	//	}

	//	inline  T* first()
	//	{
	//		return mBuffer;
	//	}

	//	inline T* last()
	//	{
	//		return mBuffer + mUsed;
	//	}

	//protected:

	//	T*     mBuffer;
	//	size_t mUsed, mCapacity;
	//};

	/*! struct. Vertex
		desc.
			Structure for a single vertex.
	*/
	//struct Vertex
	//{
	//	Ogre::Vector3 position;
	//	Ogre::ColourValue colour;
	//	Ogre::Vector2 uv;
	//};



	/*! class. TextureAtlas
		desc.
			 The TextureAtlas file represents a .gorilla file which contains all the needed information that
			 describes the portions of a single texture. Such as Glyph and Sprite information, text kerning,
			 line heights and so on. It isn't typically used by the end-user.
	*/
	class TextureAtlas : public Ogre::GeneralAllocatedObject
	{

		//  friend class Silverback;

	public:

		void setTexture(Ogre::TexturePtr texture);

		Ogre::MaterialPtr createOrGet2DMasterMaterial();

		Ogre::MaterialPtr createOrGet3DMasterMaterial();

		/*! function. getTexture
			desc.
				Get the texture assigned to this TextureAtlas
		*/
		inline Ogre::TexturePtr getTexture() const
		{
			return mTexture;
		}

		/*! function. getMaterial
			desc.
				Get the material assigned to this TextureAtlas
		*/
		inline Ogre::MaterialPtr get2DMaterial() const
		{
			return m2DMaterial;
		}

		/*! function. getMaterial
			desc.
				Get the material assigned to this TextureAtlas
		*/
		inline Ogre::MaterialPtr get3DMaterial() const
		{
			return m3DMaterial;
		}
		/*! function. getMaterialName
			desc.
				Get the name of the material assigned to this TextureAtlas
		*/
		inline Ogre::String get2DMaterialName() const
		{
			return m2DMaterial->getName();
		}
		/*! function. getMaterialName
			desc.
				Get the name of the material assigned to this TextureAtlas
		*/
		inline Ogre::String get3DMaterialName() const
		{
			return m3DMaterial->getName();
		}

		/*! function. getTextureSize
			desc.
				Get the size of the texture.
		*/
		inline Ogre::Vector2 getTextureSize() const
		{
			return Ogre::Vector2(float(mTexture->getWidth()), float(mTexture->getHeight()));
		}

		/*! function. getTextureSize
			desc.
				Get the reciprocal of the width of the texture.
		*/
		inline float getInvTextureCoordsX() const
		{
			return 1.0f / float(mTexture->getWidth());
		}

		/*! function. getTextureSize
			desc.
				Get the reciprocal of the height of the texture.
		*/
		inline float getInvTextureCoordsY() const
		{
			return 1.0f / float(mTexture->getHeight());
		}

		/*! function. getPass
			desc.
				Get the first pass of the material used by this TextureAtlas
		*/
		inline Ogre::Pass* get2DPass() const
		{
			return m2DPass;
		}

		/*! function. getGlyphMonoWidth
			desc.
				Reset the ten markup colours used in the MarkupText, by default these are:

				 0 = 255, 255, 255
				 1 = 0, 0, 0
				 2 = 204, 204, 204
				 3 = 254, 220, 129
				 4 = 254, 138, 129
				 5 = 123, 236, 110
				 6 = 44,  192, 171
				 7 = 199, 93,  142
				 8 = 254, 254, 254
				 9 = 13,  13,  13
		*/
		void refreshMarkupColours();

		/*! function. setMarkupColour
			desc.
				Change one of the ten markup colours.
			note.
				colour_palette_index must be between or equal to 0 and 9.
		*/
		void setMarkupColour(Ogre::uint colour_palette_index, const Ogre::ColourValue&);

		/*! function. getMarkupColour
			desc.
				Get one of the ten markup colours.
			note.
				colour_palette_index must be between or equal to 0 and 9.
		*/
		Ogre::ColourValue getMarkupColour(Ogre::uint colour_palette_index);

		TextureAtlas(Ogre::TexturePtr texture);

		~TextureAtlas();


	protected:



		void  _reset();
		//void  _load(const Ogre::String& gorillaFile, const Ogre::String& groupName);
		void  _loadTexture(Ogre::ConfigFile::SettingsMultiMap*);
		//void  _loadGlyphs(Ogre::ConfigFile::SettingsMultiMap*, GlyphData*);
		//void  _loadKerning(Ogre::ConfigFile::SettingsMultiMap*, GlyphData*);
		//void  _loadVerticalOffsets(Ogre::ConfigFile::SettingsMultiMap*, GlyphData*);
	//	void  _loadSprites(Ogre::ConfigFile::SettingsMultiMap*);
		void  _create2DMaterial();
		void  _create3DMaterial();
		//void  _calculateCoordinates();

		Ogre::String mMaterial2DName, mMaterial3DName;
		Ogre::TexturePtr                  mTexture;
		Ogre::MaterialPtr                 m2DMaterial, m3DMaterial;
		Ogre::Pass*                       m2DPass, *m3DPass;

		//std::map<Ogre::uint, GlyphData*>  mGlyphData;
		//std::map<Ogre::String, Sprite*>   mSprites;

//		Ogre::Vector2                     mWhitePixel;
//		Ogre::Vector2                     mInverseTextureSize;
		Ogre::ColourValue                 mMarkupColour[10];

	};

	//class LayerContainer
	//{

	//public:

	//	LayerContainer(TextureAtlas*);

	//	virtual ~LayerContainer();

	//	/*! function. createLayer
	//		desc.
	//			Create a layer for drawing on to.

	//			Index represents the z-order, 0 being the layer drawn first and 15
	//			the layer drawn last. Layers drawn after another layer will appear
	//			to be top than the other.

	//		note.
	//			Index must be between or equal to 0 and 15. Any other value will cause
	//			a very nasty crash.
	//	*/
	//	Layer*  createLayer(Ogre::uint index = 0);

	//	/*! function. destroyLayer
	//		desc.
	//			Destroy a layer and it's contents.
	//	*/
	//	void   destroy(Layer* layer);

	//	/*! function. getAtlas
	//		desc.
	//			Get atlas assigned to this LayerContainer
	//	*/
	//	TextureAtlas* getAtlas() const { return mAtlas; }

	//	virtual float getTexelOffsetX() const { return 0.0f; }

	//	virtual float getTexelOffsetY() const { return 0.0f; }

	//	/*! function. _createVertexBuffer
	//		desc.
	//			Create the vertex buffer
	//	*/
	//	void _createVertexBuffer(size_t initialSize);

	//	/*! function. _destroyVertexBuffer
	//		desc.
	//			Destroy the vertex buffer
	//	*/
	//	void _destroyVertexBuffer();

	//	/*! function. _resizeVertexBuffer
	//		desc.
	//			Resize the vertex buffer to the greatest nearest power
	//			of 2 of requestedSize.
	//	*/
	//	void _resizeVertexBuffer(size_t requestedSize);

	//	/* function. _recalculateIndexes
	//	   desc.
	//		   Clear mIndexes, mIndexVertices and mIndexRedraw,
	//		   and from mLayers fill them out again. A full redraw
	//		   is required.
	//	*/
	//	void _recalculateIndexes();

	//	/*! function. _redrawIndex
	//		desc.
	//			Redraw all layers of an index.
	//			If force is true, then all elements of that layer
	//			will be redrawn regardless of anything has changed
	//			or not.
	//	*/
	//	void _redrawIndex(Ogre::uint id, bool force);

	//	/*! function. _redrawAllIndexes
	//		desc.
	//			Redraw all layers of all indexes
	//			If force is true, then all elements of all layers
	//			will be redrawn regardless of anything has changed
	//			or not.
	//	*/
	//	void _redrawAllIndexes(bool force = false);

	//	/*! function. _redrawAllIndexes
	//		desc.
	//			Redraw a redraw of an index on the next call of _renderVertices
	//	*/
	//	void _requestIndexRedraw(Ogre::uint index);

	//	/*! function. _renderVertices
	//		desc.
	//			Bundle up mIndexData (redraw any if needed) then copy them
	//			into mVertexBuffer, and update mRenderOpPtr with the new
	//			vertex count.
	//	*/
	//	void _renderVertices(bool force = false);

	//	/*! function. renderOnce
	//		desc.
	//			Draw the vertices from mVertexBuffer into Ogre.
	//	*/
	//	virtual void renderOnce() = 0;

	//	virtual void _transform(buffer<Vertex>& vertices, size_t begin, size_t end) {}

	//protected:

	//	/// mLayers -- Master copy of all layers of this Target.
	//	std::vector<Layer*>     mLayers;

	//	struct IndexData : public Ogre::GeneralAllocatedObject
	//	{
	//		std::vector<Layer*>    mLayers;
	//		buffer<Vertex>         mVertices;
	//		bool                   mRedrawNeeded;
	//	};

	//	/// mIndexes -- Copies pointers to Layers arranged their index.
	//	std::map< Ogre::uint, IndexData* >  mIndexData;

	//	/// mIndexRedrawNeeded -- An index (not sure what) needs to be redrawn.
	//	bool  mIndexRedrawNeeded;

	//	/// mRedrawAll -- All indexes need to be redrawn regardless of state.
	//	bool  mIndexRedrawAll;

	//	/// mVertexBuffer -- Compiled layers of all indexes go into here for rendering directly to the screen or scene.
	//	Ogre::v1::HardwareVertexBufferSharedPtr   mVertexBuffer;

	//	/// mVertexBufferSize -- How much the VertexBuffer can hold.
	//	size_t  mVertexBufferSize;

	//	/// mRenderOpPtr -- Pointer to the RenderOperation (Not owned by LayerContainer)
	//	Ogre::v1::RenderOperation*  mRenderOpPtr;

	//	/// Atlas assigned to this LayerContainer
	//	TextureAtlas*  mAtlas;

	//};


	/*! class. Layer
		desc.
			Text
	*/
	//class Layer : public Ogre::GeneralAllocatedObject
	//{

	//	friend class LayerContainer;

	//public:

	//	/*typedef XE::VectorType<Rectangle*>::type            Rectangles;
	//	typedef Ogre::VectorIterator<Rectangles>                 RectangleIterator;*/
	//	//typedef XE::VectorType<Polygon*>::type              Polygons;
	//	//typedef Ogre::VectorIterator<Polygons>                   PolygonIterator;
	//	//typedef XE::VectorType<LineList*>::type             LineLists;
	//	//typedef Ogre::VectorIterator<LineLists>                  LineListIterator;
	//	//typedef XE::VectorType<QuadList*>::type             QuadLists;
	//	//typedef Ogre::VectorIterator<QuadLists>                  QuadListIterator;
	//	/*typedef XE::VectorType<Caption*>::type              Captions;
	//	typedef Ogre::VectorIterator<Captions>                   CaptionIterator;*/
	//	//typedef XE::VectorType<MarkupText*>::type           MarkupTexts;
	//	//typedef Ogre::VectorIterator<MarkupTexts>                MarkupTextIterator;

	//	/*! function. isVisible
	//		desc.
	//			Is the layer being drawn on screen or not?
	//	*/
	//	inline  bool isVisible() const
	//	{
	//		return mVisible;
	//	}

	//	/*! function. setVisible
	//		desc.
	//			Show or hide the layer
	//	*/
	//	inline void setVisible(bool isVisible)
	//	{
	//		if (mVisible == isVisible)
	//			return;
	//		mVisible = isVisible;
	//		_markDirty();
	//	}

	//	/*! function. show
	//		desc.
	//			Show the layer
	//	*/
	//	inline void show()
	//	{
	//		if (mVisible)
	//			return;
	//		mVisible = true;
	//		_markDirty();
	//	}

	//	/*! function. hide
	//		desc.
	//			hide the layer
	//	*/
	//	inline void hide()
	//	{
	//		if (!mVisible)
	//			return;
	//		mVisible = false;
	//		_markDirty();
	//	}

	//	/*! function. setAlphaModifier
	//		desc.
	//			Set's a modifier to the alpha component of all colours of the vertices that make up this layer
	//		note.
	//			Final alpha value of all vertices in this layer is the following:

	//			 final_alpha = vertex_alpha * alphaModifier;

	//			Alpha modifier should be between 0.0 and 1.0
	//	*/
	//	void setAlphaModifier(const float& alphaModifier)
	//	{
	//		mAlphaModifier = alphaModifier;
	//		_markDirty();
	//	}

	//	/*! function. getAlphaModifier
	//		desc.
	//			Set's a modifier to the alpha component of all colours of the vertices that make up this layer
	//	*/
	//	float getAlphaModifier() const
	//	{
	//		return mAlphaModifier;
	//	}

	//	/*! function. getIndex
	//		desc.
	//			Get render index
	//	*/
	//	Ogre::uint getIndex() const
	//	{
	//		return mIndex;
	//	}

	//	/*! function. _markDirty
	//		desc.
	//			Make this layer redraw itself on the next time that
	//			Gorilla updates to the screen.
	//		note.
	//			This shouldn't be needed to be called by the user.
	//	*/
	//	void _markDirty();


	//private:

	//	//void _render(buffer<Vertex>&, bool force = false);

	//	Layer(Ogre::uint index, LayerContainer*);

	//	~Layer();

	//	Ogre::uint               mIndex;

	//	std::vector<RenderableShape> _renderableShapes;

	//	LayerContainer*          mParent;
	//	bool                     mVisible;
	//	float               mAlphaModifier;
	//};

}


#endif
