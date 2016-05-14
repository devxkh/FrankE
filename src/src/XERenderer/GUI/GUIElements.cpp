

namespace XE
{

	QuadList::QuadList(Layer* layer)
		: mLayer(layer)
	{
		mWhiteUV = mLayer->_getSolidUV();
	}

	void  QuadList::begin()
	{
		mQuads.remove_all();
		mDirty = false;
	}

	void  QuadList::rectangle(float x, float y, float w, float h, const Ogre::ColourValue colour)
	{
		Quad q;
		q.mPosition[TopLeft].x = x; q.mPosition[TopLeft].y = y;
		q.mPosition[TopRight].x = x + w; q.mPosition[TopRight].y = y;
		q.mPosition[BottomRight].x = x + w; q.mPosition[BottomRight].y = y + h;
		q.mPosition[BottomLeft].x = x; q.mPosition[BottomLeft].y = y + h;


		q.mColour[0] = q.mColour[1] = q.mColour[2] = q.mColour[3] = colour;
		q.mUV[0] = q.mUV[1] = q.mUV[2] = q.mUV[3] = mWhiteUV;
		mQuads.push_back(q);
	}

	void  QuadList::gradient(float x, float y, float w, float h, Gradient gradient, const Ogre::ColourValue& colourA, const Ogre::ColourValue& colourB)
	{
		Quad q;
		if (gradient == Gradient_NorthSouth)
		{
			q.mColour[0] = q.mColour[1] = colourA;
			q.mColour[2] = q.mColour[3] = colourB;
		}
		else if (gradient == Gradient_WestEast)
		{
			q.mColour[0] = q.mColour[3] = colourA;
			q.mColour[1] = q.mColour[2] = colourB;
		}
		else if (gradient == Gradient_Diagonal)
		{
			Ogre::ColourValue avg;
			avg.r = (colourA.r + colourB.r) * 0.5f;
			avg.g = (colourA.g + colourB.g) * 0.5f;
			avg.b = (colourA.b + colourB.b) * 0.5f;
			avg.a = (colourA.a + colourB.a) * 0.5f;
			q.mColour[0] = colourA;
			q.mColour[1] = avg = q.mColour[3] = avg;
			q.mColour[2] = colourB;
		}

		q.mPosition[TopLeft].x = x; q.mPosition[TopLeft].y = y;
		q.mPosition[TopRight].x = x + w; q.mPosition[TopRight].y = y;
		q.mPosition[BottomRight].x = x + w; q.mPosition[BottomRight].y = y + h;
		q.mPosition[BottomLeft].x = x; q.mPosition[BottomLeft].y = y + h;

		q.mUV[0] = q.mUV[1] = q.mUV[2] = q.mUV[3] = mWhiteUV;
		mQuads.push_back(q);
	}

	void  QuadList::sprite(float x, float y, float w, float h, Sprite* sprite)
	{
		Quad q;
		q.mPosition[TopLeft].x = q.mPosition[BottomLeft].x = x;
		q.mPosition[TopLeft].y = q.mPosition[TopRight].y = y;
		q.mPosition[TopRight].x = q.mPosition[BottomRight].x = x + w;
		q.mPosition[BottomRight].y = q.mPosition[BottomLeft].y = y + h;
		q.mColour[0] = q.mColour[1] = q.mColour[2] = q.mColour[3] = Ogre::ColourValue::White;

		q.mUV[TopLeft].x = sprite->uvLeft;
		q.mUV[TopLeft].y = sprite->uvTop;

		q.mUV[TopRight].x = sprite->uvRight;
		q.mUV[TopRight].y = sprite->uvTop;

		q.mUV[BottomLeft].x = sprite->uvLeft;
		q.mUV[BottomLeft].y = sprite->uvBottom;

		q.mUV[BottomRight].x = sprite->uvRight;
		q.mUV[BottomRight].y = sprite->uvBottom;
		mQuads.push_back(q);

	}

	void  QuadList::border(float x, float y, float w, float h, float thickness, const Ogre::ColourValue& colour)
	{
		border(x, y, w, h, thickness, colour, colour, colour, colour);
	}

	void  QuadList::border(float x, float y, float w, float h, float thickness, const Ogre::ColourValue& northColour, const Ogre::ColourValue& eastColour, const Ogre::ColourValue& southColour, const Ogre::ColourValue& westColour)
	{

		Ogre::Vector2 a(x, y), b(x + w, y), c(x, y + h), d(x + w, y + h),
			i = a, j = b, k = c, l = d;
		i.x -= thickness;    i.y -= thickness;
		j.x += thickness;    j.y -= thickness;
		k.x -= thickness;    k.y += thickness;
		l.x += thickness;    l.y += thickness;

		Vertex temp;

		// North
		Quad q;
		q.mUV[0] = q.mUV[1] = q.mUV[2] = q.mUV[3] = mWhiteUV;

		// North
		q.mPosition[TopLeft] = i;
		q.mPosition[TopRight] = j;
		q.mPosition[BottomLeft] = a;
		q.mPosition[BottomRight] = b;
		q.mColour[0] = q.mColour[1] = q.mColour[2] = q.mColour[3] = northColour;
		mQuads.push_back(q);

		// East
		q.mPosition[TopLeft] = b;
		q.mPosition[TopRight] = j;
		q.mPosition[BottomLeft] = d;
		q.mPosition[BottomRight] = l;
		q.mColour[0] = q.mColour[1] = q.mColour[2] = q.mColour[3] = eastColour;
		mQuads.push_back(q);

		// South
		q.mPosition[TopLeft] = c;
		q.mPosition[TopRight] = d;
		q.mPosition[BottomLeft] = k;
		q.mPosition[BottomRight] = l;
		q.mColour[0] = q.mColour[1] = q.mColour[2] = q.mColour[3] = southColour;
		mQuads.push_back(q);

		// West
		q.mPosition[TopLeft] = i;
		q.mPosition[TopRight] = a;
		q.mPosition[BottomLeft] = k;
		q.mPosition[BottomRight] = c;
		q.mColour[0] = q.mColour[1] = q.mColour[2] = q.mColour[3] = westColour;
		mQuads.push_back(q);

	}

	void  QuadList::glyph(Ogre::uint glyphDataIndex, float x, float y, unsigned char character, const Ogre::ColourValue& colour)
	{
		GlyphData* glyphData = mLayer->_getGlyphData(glyphDataIndex);
		if (glyphData == 0)
		{
#if GORILLA_USES_EXCEPTIONS == 1
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, "Glyph data not found", __FUNC__);
#else
			return;
#endif
		}

		Glyph* glyph = glyphData->getGlyph(character);
		if (glyph == 0)
			return;

		y += glyph->verticalOffset;

		Quad q;
		q.mPosition[TopLeft].x = x;
		q.mPosition[TopLeft].y = y;
		q.mPosition[TopRight].x = x + glyph->glyphWidth;
		q.mPosition[TopRight].y = y;
		q.mPosition[BottomRight].x = x + glyph->glyphWidth;
		q.mPosition[BottomRight].y = y + glyph->glyphHeight;
		q.mPosition[BottomLeft].x = x;
		q.mPosition[BottomLeft].y = y + glyph->glyphHeight;

		q.mColour[0] = q.mColour[1] = q.mColour[2] = q.mColour[3] = colour;

		q.mUV[TopLeft].x = glyph->uvLeft;
		q.mUV[TopLeft].y = glyph->uvTop;

		q.mUV[TopRight].x = glyph->uvRight;
		q.mUV[TopRight].y = glyph->uvTop;

		q.mUV[BottomRight].x = glyph->uvRight;
		q.mUV[BottomRight].y = glyph->uvBottom;

		q.mUV[BottomLeft].x = glyph->uvLeft;
		q.mUV[BottomLeft].y = glyph->uvBottom;

		mQuads.push_back(q);
	}

	void  QuadList::glyph(Ogre::uint glyphDataIndex, float x, float y, float w, float h, unsigned char character, const Ogre::ColourValue& colour)
	{
		GlyphData* glyphData = mLayer->_getGlyphData(glyphDataIndex);
		if (glyphData == 0)
		{
#if GORILLA_USES_EXCEPTIONS == 1
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, "Glyph data not found", __FUNC__);
#else
			return;
#endif
		}

		Glyph* glyph = glyphData->getGlyph(character);
		if (glyph == 0)
			return;

		y += glyph->verticalOffset;

		Quad q;
		q.mPosition[TopLeft].x = x;
		q.mPosition[TopLeft].y = y;
		q.mPosition[TopRight].x = x + w;
		q.mPosition[TopRight].y = y;
		q.mPosition[BottomRight].x = x + w;
		q.mPosition[BottomRight].y = y + h;
		q.mPosition[BottomLeft].x = x;
		q.mPosition[BottomLeft].y = y + h;

		q.mColour[0] = q.mColour[1] = q.mColour[2] = q.mColour[3] = colour;

		q.mUV[TopLeft].x = glyph->uvLeft;
		q.mUV[TopLeft].y = glyph->uvTop;

		q.mUV[TopRight].x = glyph->uvRight;
		q.mUV[TopRight].y = glyph->uvTop;

		q.mUV[BottomRight].x = glyph->uvRight;
		q.mUV[BottomRight].y = glyph->uvBottom;

		q.mUV[BottomLeft].x = glyph->uvLeft;
		q.mUV[BottomLeft].y = glyph->uvBottom;

		mQuads.push_back(q);
	}

	void  QuadList::end()
	{
		mDirty = true;
		mLayer->_markDirty();
	}

	void  QuadList::_redraw()
	{
		if (mDirty == false)
			return;

		mVertices.remove_all();
		Vertex temp;

		for (size_t i = 0; i < mQuads.size(); i++)
		{
			PUSH_QUAD(mVertices, temp, mQuads[i].mPosition, mQuads[i].mColour, mQuads[i].mUV)
		}

		mDirty = false;
	}

















	MarkupText::MarkupText(Ogre::uint defaultGlyphIndex, float left, float top, const Ogre::String& text, Layer* parent)
		: mLayer(parent)
	{
		mDefaultGlyphData = mLayer->_getGlyphData(defaultGlyphIndex);

		if (mDefaultGlyphData == 0)
		{
			mDirty = false;
			mTextDirty = false;
#if GORILLA_USES_EXCEPTIONS == 1
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, "Glyph data not found", __FUNC__);
#else
			return;
#endif
		}

		mDirty = true;
		mTextDirty = true;
		mLayer->_markDirty();
		mLeft = left;
		mTop = top;
		mWidth = 0.0f;
		mHeight = 0.0f;
		mText = text;
		mBackground.a = 0.0f;

	}

	void MarkupText::_calculateCharacters()
	{
		if (mTextDirty == false)
			return;

		float cursorX = mLeft, cursorY = mTop, kerning = 0, texelOffsetX = mLayer->_getTexelX(), texelOffsetY = mLayer->_getTexelY(), right = 0, bottom = 0, left = 0, top = 0;
		unsigned int thisChar = 0, lastChar = 0;
		Glyph* glyph = 0;

		mMaxTextWidth = 0;

		mCharacters.remove_all();

		bool markupMode = false;
		Ogre::ColourValue colour = mLayer->_getMarkupColour(0);
		bool fixedWidth = false;

		GlyphData* glyphData = mDefaultGlyphData;
		float lineHeight = glyphData->mLineHeight;

		for (size_t i = 0; i < mText.length(); i++)
		{

			thisChar = mText[i];

			if (thisChar == ' ')
			{
				lastChar = thisChar;
				cursorX += glyphData->mSpaceLength;
				continue;
			}

			if (thisChar == '\n')
			{
				lastChar = thisChar;
				cursorX = mLeft;
				cursorY += lineHeight;
				lineHeight = glyphData->mLineHeight;
				continue;
			}

			if (thisChar < glyphData->mRangeBegin || thisChar > glyphData->mRangeEnd)
			{
				lastChar = 0;
				continue;
			}

			if (thisChar == '%' && markupMode == false)
			{
				markupMode = true;
				continue;
			}

			if (markupMode == true)
			{
				if (thisChar == '%')
				{
					// Escape Character.
				}
				else
				{
					markupMode = false;

					if (thisChar >= '0' && thisChar <= '9')
					{
						colour = mLayer->_getMarkupColour(thisChar - 48);
					}
					else if (thisChar == 'R' || thisChar == 'r')
					{
						colour = mLayer->_getMarkupColour(0);
					}
					else if (thisChar == 'M' || thisChar == 'm')
					{
						fixedWidth = !fixedWidth;
					}
					else if (thisChar == '@')
					{
						markupMode = false;
						bool foundIt = false;
						size_t begin = i;
						while (i < mText.size())
						{
							if (mText[i] == '%')
							{
								foundIt = true;
								break;
							}
							i++;
						}

						if (foundIt == false)
							return;

						Ogre::uint index = Ogre::StringConverter::parseUnsignedInt(mText.substr(begin + 1, i - begin - 1));
						glyphData = mLayer->_getGlyphData(index);
						if (glyphData == 0)
							return;
						lineHeight = std::max(lineHeight, glyphData->mLineHeight);
						continue;
					}
					else if (thisChar == ':')
					{
						markupMode = false;
						bool foundIt = false;
						size_t begin = i;
						while (i < mText.size())
						{
							if (mText[i] == '%')
							{
								foundIt = true;
								break;
							}
							i++;
						}

						if (foundIt == false)
							return;

						Ogre::String sprite_name = mText.substr(begin + 1, i - begin - 1);

						Sprite* sprite = mLayer->_getSprite(sprite_name);
						if (sprite == 0)
							continue;

						left = cursorX - texelOffsetX;
						top = cursorY - texelOffsetY + glyph->verticalOffset;
						right = left + sprite->spriteWidth + texelOffsetX;
						bottom = top + sprite->spriteHeight + texelOffsetY;

						Character c;
						c.mIndex = i;
						c.mPosition[TopLeft].x = left;
						c.mPosition[TopLeft].y = top;
						c.mPosition[TopRight].x = right;
						c.mPosition[TopRight].y = top;
						c.mPosition[BottomLeft].x = left;
						c.mPosition[BottomLeft].y = bottom;
						c.mPosition[BottomRight].x = right;
						c.mPosition[BottomRight].y = bottom;
						c.mUV[0] = sprite->texCoords[0];
						c.mUV[1] = sprite->texCoords[1];
						c.mUV[2] = sprite->texCoords[2];
						c.mUV[3] = sprite->texCoords[3];
						c.mColour = colour;

						mCharacters.push_back(c);

						cursorX += sprite->spriteWidth;

						lineHeight = std::max(lineHeight, sprite->spriteHeight);

						continue;
					}


					continue;
				}
				markupMode = false;
			}

			glyph = glyphData->getGlyph(thisChar);

			if (!fixedWidth)
			{
				kerning = glyph->getKerning(lastChar);
				if (kerning == 0)
					kerning = glyphData->mLetterSpacing;
			}

			left = cursorX;
			top = cursorY + glyph->verticalOffset;
			right = cursorX + glyph->glyphWidth + texelOffsetX;
			bottom = top + glyph->glyphHeight + texelOffsetY;


			if (fixedWidth)
			{
				float offset = std::floor((glyphData->mMonoWidth - glyph->glyphWidth) / 2.0f);
				left += offset;
				right += offset;
			}

			Character c;
			c.mIndex = i;
			c.mPosition[TopLeft].x = left;
			c.mPosition[TopLeft].y = top;
			c.mPosition[TopRight].x = right;
			c.mPosition[TopRight].y = top;
			c.mPosition[BottomLeft].x = left;
			c.mPosition[BottomLeft].y = bottom;
			c.mPosition[BottomRight].x = right;
			c.mPosition[BottomRight].y = bottom;
			c.mUV[0] = glyph->texCoords[0];
			c.mUV[1] = glyph->texCoords[1];
			c.mUV[2] = glyph->texCoords[2];
			c.mUV[3] = glyph->texCoords[3];
			c.mColour = colour;

			mCharacters.push_back(c);

			if (fixedWidth)
				cursorX += glyphData->mMonoWidth;
			else
				cursorX += glyph->glyphAdvance + kerning;

			if (cursorX > mMaxTextWidth)
				mMaxTextWidth = cursorX;

			lastChar = thisChar;
		}

		mMaxTextWidth -= mLeft;

		mTextDirty = false;
	}

	void  MarkupText::_redraw()
	{

		if (mDirty == false)
			return;

		mVertices.remove_all();

		Vertex temp;
		for (size_t i = 0; i < mCharacters.size(); i++)
		{
			PUSH_QUAD2(mVertices, temp, mCharacters[i].mPosition, mCharacters[i].mColour, mCharacters[i].mUV);
		}

		mDirty = false;
	}








	Polygon::Polygon(float left, float top, float radius, size_t sides, Layer* layer)
		: mLayer(layer), mSprite(0)
	{
		mDirty = true;
		mLayer->_markDirty();
		mLeft = left;
		mTop = top;
		mRadius = radius;
		mSides = sides;
		mBackgroundColour = Ogre::ColourValue::White;
		mBorderColour.a = 0;
		mBorderWidth = 0;
	}

	void  Polygon::_redraw()
	{

		if (mDirty == false)
			return;

		mVertices.remove_all();
		Vertex temp;

		float theta = mAngle.valueRadians();
		float inc = (2 * Ogre::Math::PI) / float(mSides);

		Ogre::Vector2 lastVertex;
		lastVertex.x = mLeft + (mRadius * cos(theta));
		lastVertex.y = mTop + (mRadius * sin(theta));
		Ogre::Vector2 thisVertex;

		if (mBorderWidth != 0)
		{

			Ogre::Vector2 lastOuterVertex, outerVertex, thisVertex, uv;
			uv = mLayer->_getSolidUV();

			lastOuterVertex.x = mLeft + ((mRadius + mBorderWidth) * cos(theta));
			lastOuterVertex.y = mTop + ((mRadius + mBorderWidth) * sin(theta));


			for (size_t i = 0; i < mSides; i++)
			{
				theta += inc;
				thisVertex.x = mLeft + (mRadius * Ogre::Math::Cos(theta));
				thisVertex.y = mTop + (mRadius * Ogre::Math::Sin(theta));
				outerVertex.x = mLeft + ((mRadius + mBorderWidth) * Ogre::Math::Cos(theta));
				outerVertex.y = mTop + ((mRadius + mBorderWidth) * Ogre::Math::Sin(theta));

				PUSH_TRIANGLE(mVertices, temp, lastVertex, outerVertex, lastOuterVertex, uv, mBorderColour);
				PUSH_TRIANGLE(mVertices, temp, lastVertex, thisVertex, outerVertex, uv, mBorderColour);

				lastVertex = thisVertex;
				lastOuterVertex = outerVertex;
			}
		}

		if (mBackgroundColour.a != 0)
		{
			if (mSprite)
			{
				float xRadius = mSprite->spriteWidth * 0.5f;
				float yRadius = mSprite->spriteHeight * 0.5f;

				Ogre::Vector2 centerUV, lastUV, thisUV, baseUV, texSize = mLayer->_getTextureSize();
				baseUV.x = mSprite->uvLeft * texSize.x;
				baseUV.y = mSprite->uvTop * texSize.y;
				baseUV.x += xRadius;
				baseUV.y += yRadius;

				centerUV = baseUV / texSize;
				lastUV = baseUV;
				lastUV.x = baseUV.x + (xRadius * Ogre::Math::Cos(theta));
				lastUV.y = baseUV.y + (yRadius * Ogre::Math::Sin(theta));
				lastUV /= texSize;

				for (size_t i = 0; i < mSides; i++)
				{
					PUSH_VERTEX(mVertices, temp, mLeft, mTop, centerUV, mBackgroundColour);
					theta += inc;
					thisVertex.x = mLeft + (mRadius * Ogre::Math::Cos(theta));
					thisVertex.y = mTop + (mRadius * Ogre::Math::Sin(theta));
					thisUV.x = baseUV.x + (xRadius * Ogre::Math::Cos(theta));
					thisUV.y = baseUV.y + (yRadius * Ogre::Math::Sin(theta));
					thisUV /= texSize;
					PUSH_VERTEX(mVertices, temp, thisVertex.x, thisVertex.y, thisUV, mBackgroundColour);
					PUSH_VERTEX(mVertices, temp, lastVertex.x, lastVertex.y, lastUV, mBackgroundColour);
					lastVertex = thisVertex;
					lastUV = thisUV;
				}
			}
			else
			{
				Ogre::Vector2 uv = uv = mLayer->_getSolidUV();

				for (size_t i = 0; i < mSides; i++)
				{
					PUSH_VERTEX(mVertices, temp, mLeft, mTop, uv, mBackgroundColour);
					theta += inc;
					thisVertex.x = mLeft + (mRadius * Ogre::Math::Cos(theta));
					thisVertex.y = mTop + (mRadius * Ogre::Math::Sin(theta));
					PUSH_VERTEX(mVertices, temp, thisVertex.x, thisVertex.y, uv, mBackgroundColour);
					PUSH_VERTEX(mVertices, temp, lastVertex.x, lastVertex.y, uv, mBackgroundColour);
					lastVertex = thisVertex;
				}
			}
		}

		mDirty = false;

	}



	LineList::LineList(Layer* layer) : mLayer(layer)
	{
		mDirty = false;
	}

	void  LineList::begin(float lineThickness, const Ogre::ColourValue& colour)
	{
		mDirty = false;
		mPositions.remove_all();
		mThickness = lineThickness;
		mColour = colour;
	}

	void  LineList::position(float x, float y)
	{
		mPositions.push_back(Ogre::Vector2(x, y));
	}

	void  LineList::position(const Ogre::Vector2& position)
	{
		mPositions.push_back(position);
	}

	void  LineList::end(bool closed)
	{
		mIsClosed = closed;
		mDirty = true;
	}

	void  LineList::_redraw()
	{
		if (mDirty == false)
			return;

		mVertices.remove_all();

		if (mPositions.size() < 2)
			return;

		Vertex temp;

		float halfThickness = mThickness * 0.5f;

		Ogre::Vector2 perp, lastLeft, lastRight, thisLeft, thisRight, uv = mLayer->_getSolidUV();

		size_t i = 1;

		for (; i < mPositions.size(); i++)
		{

			perp = (mPositions[i] - mPositions[i - 1]).perpendicular().normalisedCopy();
			lastLeft = mPositions[i - 1] - perp * halfThickness;
			lastRight = mPositions[i - 1] + perp * halfThickness;
			thisLeft = mPositions[i] - perp * halfThickness;
			thisRight = mPositions[i] + perp * halfThickness;

			// Triangle A
			PUSH_VERTEX(mVertices, temp, lastRight.x, lastRight.y, uv, mColour);       // Left/Bottom
			PUSH_VERTEX(mVertices, temp, thisLeft.x, thisLeft.y, uv, mColour);         // Right/Top
			PUSH_VERTEX(mVertices, temp, lastLeft.x, lastLeft.y, uv, mColour);          // Left/Top
																						// Triangle B
			PUSH_VERTEX(mVertices, temp, lastRight.x, lastRight.y, uv, mColour);       // Left/Bottom
			PUSH_VERTEX(mVertices, temp, thisRight.x, thisRight.y, uv, mColour);      // Right/Bottom
			PUSH_VERTEX(mVertices, temp, thisLeft.x, thisLeft.y, uv, mColour);         // Right/Top

		}

		if (mIsClosed)
		{
			i = mPositions.size() - 1;
			perp = (mPositions[0] - mPositions[i]).perpendicular().normalisedCopy();
			lastLeft = mPositions[i] - perp * halfThickness;
			lastRight = mPositions[i] + perp * halfThickness;
			thisLeft = mPositions[0] - perp * halfThickness;
			thisRight = mPositions[0] + perp * halfThickness;

			// Triangle A
			PUSH_VERTEX(mVertices, temp, lastRight.x, lastRight.y, uv, mColour);       // Left/Bottom
			PUSH_VERTEX(mVertices, temp, thisLeft.x, thisLeft.y, uv, mColour);         // Right/Top
			PUSH_VERTEX(mVertices, temp, lastLeft.x, lastLeft.y, uv, mColour);          // Left/Top
																						// Triangle B
			PUSH_VERTEX(mVertices, temp, lastRight.x, lastRight.y, uv, mColour);       // Left/Bottom
			PUSH_VERTEX(mVertices, temp, thisRight.x, thisRight.y, uv, mColour);      // Right/Bottom
			PUSH_VERTEX(mVertices, temp, thisLeft.x, thisLeft.y, uv, mColour);         // Right/Top

		}

	}





	GlyphData::GlyphData()
		: mRangeBegin(0),
		mRangeEnd(0),
		mSpaceLength(0),
		mLineHeight(0),
		mBaseline(0),
		mLineSpacing(0),
		mLetterSpacing(0),
		mMonoWidth(0)
	{
	}

	GlyphData::~GlyphData()
	{

		for (std::vector<Glyph*>::iterator it = mGlyphs.begin(); it != mGlyphs.end(); it++)
		{
			OGRE_DELETE(*it);
		}

	}
}