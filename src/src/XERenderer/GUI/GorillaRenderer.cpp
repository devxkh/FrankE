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

#include <XERenderer/GUI/GorillaRenderer.hpp>
#include <Ogre/OgreMain/include/OgreStringConverter.h>
#include <Ogre/OgreMain/include/OgreMaterialManager.h>
#include <Ogre/OgreMain/include/OgreVertexIndexData.h>
#include <Ogre/OgreMain/include/OgreGpuProgram.h>
#include <Ogre/OgreMain/include/OgreRenderQueue.h>
#include <Ogre/OgreMain/include/OgrePass.h>
#include <Ogre/OgreMain/include/OgreTechnique.h>
#include <Ogre/OgreMain/include/OgreRenderOperation.h>
#include <Ogre/OgreMain/include/OgreDefaultHardwareBufferManager.h>
#include <Ogre/OgreMain/include/OgreRoot.h>
#include <Ogre/OgreMain/include/OgreTextureManager.h>

#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>

#include <XERenderer/GUI/GUIRenderer.hpp>

#include <Ogre/OgreMain/include/OgreTextureUnitState.h>
#include <Ogre/OgreMain/include/OgreRoot.h>
#include <Ogre/OgreMain/include/OgreHlmsManager.h>
#include <Ogre/OgreMain/include/OgreHlms.h>

#ifdef OGRE_BUILD_COMPONENT_HLMS_UNLIT
#include <Ogre/Components/Hlms/Unlit/include/OgreHlmsUnlitDatablock.h>
#include <Ogre/OgreMain/include/OgreHardwarePixelBuffer.h>
#else
#include "OgreHlmsUnlitMobileDatablock.h"
#endif

#ifdef OGRE_BUILD_COMPONENT_HLMS_UNLIT
namespace Ogre
{
	class HlmsUnlitDatablock;
	typedef HlmsUnlitDatablock OverlayUnlitDatablock;
}
#else
namespace Ogre
{
	class HlmsUnlitMobileDatablock;
	typedef HlmsUnlitMobileDatablock OverlayUnlitDatablock;
}
#endif

#pragma warning ( disable : 4244 )

namespace XE
{
  
 //enum
 //{
 // SCREEN_RENDERQUEUE = Ogre::RENDER_QUEUE_OVERLAY
 //};

 Ogre::ColourValue rgb(Ogre::uchar r, Ogre::uchar g, Ogre::uchar b, Ogre::uchar a )
 {
  static const float inv255 = float(0.00392156863);
  return Ogre::ColourValue(float(r) * inv255, float(g) * inv255, float(b) * inv255, float(a) * inv255);
 }

 Ogre::ColourValue webcolour(Colours::Colour web_colour, float alpha)
 {
  static const float inv255 = float(0.00392156863);
  Ogre::ColourValue ret;
  ret.b = float(web_colour & 0xFF) * inv255;
  ret.g = float((web_colour >> 8) & 0xFF) * inv255;
  ret.r = float((web_colour >> 16) & 0xFF) * inv255;
  ret.a = alpha;
  return ret;
 }
 
 TextureAtlas::TextureAtlas(Ogre::TexturePtr texture)
 {

	mTexture = texture;

  _reset();

  //_load(gorillaFile, groupName);
  //_calculateCoordinates();
//  _create2DMaterial();
 //todo _create3DMaterial();
 }

 TextureAtlas::~TextureAtlas()
 {
 }

 void  TextureAtlas::_reset()
 {
  refreshMarkupColours();
 }

 void TextureAtlas::setTexture(Ogre::TexturePtr texturePtr)
 {
	 mTexture = texturePtr;
 }
 
 Ogre::MaterialPtr TextureAtlas::createOrGet2DMasterMaterial()
 {
	 Ogre::MaterialPtr d2Material = Ogre::MaterialManager::getSingletonPtr()->getByName("Gorilla2D");
  if (d2Material.isNull() == false)
  {
    Ogre::Pass* pass = d2Material->getTechnique(0)->getPass(0);

    if(pass->hasVertexProgram())
    {
      Ogre::GpuProgramPtr gpuPtr = pass->getVertexProgram();
      gpuPtr->load();
    }

    if(pass->hasFragmentProgram())
    {
      Ogre::GpuProgramPtr gpuPtr = pass->getFragmentProgram();
      gpuPtr->load();
    }

	//KH d2Material->setTextureFiltering(Ogre::TFO_ANISOTROPIC); //https://github.com/Robert42/gorilla/blob/space-deminer/Gorilla.cpp

    return d2Material;
  }else
	d2Material = Ogre::MaterialManager::getSingletonPtr()->create("Gorilla2D", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
 // Ogre::Pass* pass = d2Material->getTechnique(0)->getPass(0);
  //Ogre::HlmsBlendblock transparent;
  //Ogre::Pass::_getBlendFlags(Ogre::SceneBlendType::SBT_TRANSPARENT_ALPHA,
	 // transparent.mSourceBlendFactor,
	 // transparent.mDestBlendFactor);
  //pass->setBlendblock(transparent);
  //KH todo!
  //pass->setCullingMode(Ogre::CULL_NONE);
  //pass->setDepthCheckEnabled(false);
  //pass->setDepthWriteEnabled(false);
  //pass->setLightingEnabled(false);
  //pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
  
	 Ogre::TextureUnitState* texLayer = d2Material->getTechnique(0)->getPass(0)->createTextureUnitState("atlas.png");// mSource);
  //KH texLayer->setTextureAddressingMode(Ogre::TAM_CLAMP);
  //KH texLayer->setTextureFiltering(Ogre::FO_NONE, Ogre::FO_NONE, Ogre::FO_NONE);

  Ogre::Hlms *hlmsGui = Ogre::Root::getSingleton().getHlmsManager()->getHlms(Ogre::HLMS_UNLIT);
  Ogre::HlmsMacroblock macroblock;
  Ogre::HlmsBlendblock blendblock;
  macroblock.mCullMode = Ogre::CULL_NONE;
  macroblock.mDepthCheck = false;
  macroblock.mDepthWrite = false;
  //Alpha blending
  blendblock.mSeparateBlend = true;
  blendblock.mSourceBlendFactor = Ogre::SBF_SOURCE_ALPHA;
  blendblock.mSourceBlendFactorAlpha = Ogre::SBF_SOURCE_ALPHA;
  blendblock.mDestBlendFactor = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
  blendblock.mDestBlendFactorAlpha = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;


  Ogre::HlmsParamVec paramsVec;
  //paramsVec.push_back( std::pair<IdString, String>( "diffuse_map", "" ) );
  std::sort(paramsVec.begin(), paramsVec.end());

  std::string datablockName = "Gorilla2D";// "Fonts/" + mName;
  Ogre::HlmsDatablock *mHlmsDatablock = hlmsGui->createDatablock(datablockName, datablockName,
	  macroblock, blendblock, paramsVec);

  Ogre::OverlayUnlitDatablock *guiDatablock = static_cast<Ogre::OverlayUnlitDatablock*>(mHlmsDatablock);
#ifdef OGRE_BUILD_COMPONENT_HLMS_UNLIT
  guiDatablock->setTexture(0, 0, mTexture);
#else
  guiDatablock->setTexture(0, mTexture, OverlayUnlitDatablock::UvAtlasParams());
#endif
  guiDatablock->calculateHash();

  // Make sure material is aware of colour per vertex.
  d2Material->getTechnique(0)->getPass(0)->setVertexColourTracking(Ogre::TVC_DIFFUSE);
  Ogre::HlmsSamplerblock samplerblock = *texLayer->getSamplerblock();
  // Clamp to avoid fuzzy edges
//!!!!!!!!!!!-------------------  samplerblock.setAddressinMode(Ogre::TAM_CLAMP);
  // Allow min/mag filter, but no mip
  samplerblock.mMinFilter = Ogre::FO_LINEAR;
  samplerblock.mMagFilter = Ogre::FO_LINEAR;
  samplerblock.mMipFilter = Ogre::FO_NONE;
  texLayer->setSamplerblock(samplerblock);

  return d2Material;
 }
 
 Ogre::MaterialPtr TextureAtlas::createOrGet3DMasterMaterial()
 {  
  Ogre::MaterialPtr d3Material = Ogre::MaterialManager::getSingletonPtr()->getByName("Gorilla3D");
  if (d3Material.isNull() == false)
  {
    Ogre::Pass* pass = d3Material->getTechnique(0)->getPass(0);

    if(pass->hasVertexProgram())
    {
      Ogre::GpuProgramPtr gpuPtr = pass->getVertexProgram();
      gpuPtr->load();
    }

    if(pass->hasFragmentProgram())
    {
      Ogre::GpuProgramPtr gpuPtr = pass->getFragmentProgram();
      gpuPtr->load();
    }

    return d3Material;
  }

  d3Material = Ogre::MaterialManager::getSingletonPtr()->create("Gorilla3D", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  Ogre::Pass* pass = d3Material->getTechnique(0)->getPass(0);
  //KH todo!
  //pass->setCullingMode(Ogre::CULL_NONE);
  //pass->setDepthCheckEnabled(false);
  //pass->setDepthWriteEnabled(false);
  //pass->setLightingEnabled(false);
  //pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

  Ogre::TextureUnitState* texUnit = pass->createTextureUnitState();
//KH  texUnit->setTextureAddressingMode(Ogre::TAM_CLAMP);
  //KH  texUnit->setTextureFiltering(Ogre::FO_ANISOTROPIC, Ogre::FO_ANISOTROPIC, Ogre::FO_ANISOTROPIC);
  
  return d3Material;
 }
 

 void  TextureAtlas::_create2DMaterial()
 {

//	 std::string matName = "Gorilla2D." + mTexture->getName();
	 if (mMaterial2DName.empty())
		 mMaterial2DName = "Gorilla2D." + mTexture->getName();

	 m2DMaterial = Ogre::MaterialManager::getSingletonPtr()->getByName(mMaterial2DName);

	 if (m2DMaterial.isNull())
		 m2DMaterial = createOrGet2DMasterMaterial()->clone(mMaterial2DName);
	 else
	 {
		 Ogre::Pass* pass = m2DMaterial->getTechnique(0)->getPass(0);
		 if (pass->hasVertexProgram())
		 {
			 Ogre::GpuProgramPtr gpuPtr = pass->getVertexProgram();
			 gpuPtr->load();
		 }

		 if (pass->hasFragmentProgram())
		 {
			 Ogre::GpuProgramPtr gpuPtr = pass->getFragmentProgram();
			 gpuPtr->load();
		 }
	 }

	 m2DPass = m2DMaterial->getTechnique(0)->getPass(0);
	 m2DPass->getTextureUnitState(0)->setTextureName(mTexture->getName());

 }

 void  TextureAtlas::_create3DMaterial()
 {
  
	 //added from https://github.com/Robert42/gorilla/blob/space-deminer/Gorilla.cpp
	 if (mMaterial3DName.empty())
		 mMaterial3DName = "Gorilla3D." + mTexture->getName();

  //std::string matName = "Gorilla3D." + mTexture->getName();
	 m3DMaterial = Ogre::MaterialManager::getSingletonPtr()->getByName(mMaterial3DName);
  
  if (m3DMaterial.isNull())
	  m3DMaterial = createOrGet3DMasterMaterial()->clone(mMaterial3DName);

  m3DPass = m3DMaterial->getTechnique(0)->getPass(0);
  m3DPass->getTextureUnitState(0)->setTextureName(mTexture->getName());
  
 }

 
 void   TextureAtlas::refreshMarkupColours()
 {
  mMarkupColour[0] = rgb(255, 255, 255);
  mMarkupColour[1] = rgb(0, 0, 0);
  mMarkupColour[2] = rgb(204, 204, 204);
  mMarkupColour[3] = rgb(254, 220, 129);
  mMarkupColour[4] = rgb(254, 138, 129);
  mMarkupColour[5] = rgb(123, 236, 110);
  mMarkupColour[6] = rgb(44,  192, 171);
  mMarkupColour[7] = rgb(199, 93,  142);
  mMarkupColour[8] = rgb(254, 254, 254);
  mMarkupColour[9] = rgb(13,  13,  13);
 }

 void   TextureAtlas::setMarkupColour(Ogre::uint index, const Ogre::ColourValue& colour)
 { 
  if (index > 9)
   return;
  
  mMarkupColour[index] = colour;
 }

 Ogre::ColourValue  TextureAtlas::getMarkupColour(Ogre::uint index)
 {
  if (index > 9)
   return Ogre::ColourValue::White;
  
  return mMarkupColour[index];
 }

 
 //LayerContainer::LayerContainer(TextureAtlas* atlas)
 //: mIndexRedrawAll(false), mAtlas(atlas)
 //{
 //}
 //
 //LayerContainer::~LayerContainer()
 //{
 // for (std::vector<Layer*>::iterator it = mLayers.begin(); it != mLayers.end(); it++)
 //  OGRE_DELETE (*it);
 // 
 // _destroyVertexBuffer();
 //}
 //
 //Layer* LayerContainer::createLayer(Ogre::uint index)
 //{
 // Layer* layer = OGRE_NEW Layer(index, this);
 // mLayers.push_back(layer);
 // 
 // std::map<Ogre::uint, IndexData*>::iterator index_data = mIndexData.find( layer->getIndex() );
 // if (index_data == mIndexData.end())
 // {
 //  mIndexData[layer->getIndex()] = OGRE_NEW IndexData();
 //  index_data = mIndexData.find( layer->getIndex() );
 // }
 // 
 // (*index_data).second->mLayers.push_back( layer );
 // (*index_data).second->mRedrawNeeded = true;
 // 
 // mIndexRedrawNeeded = true;
 // 
 // return layer;
 //}
 // 
 ///*! function. destroyLayer
 //    desc.
 //        Destroy a layer and it's contents.
 //*/
 //void LayerContainer::destroy(Layer* layer)
 //{
 // if (layer == 0)
 //  return;
 // 
 // std::map<Ogre::uint, IndexData*>::iterator index_data = mIndexData.find( layer->getIndex() );

 // // Remove layer from index, and delete index if index is empty.
 // if (index_data != mIndexData.end())
 // {
 //  IndexData* indexData = (*index_data).second;
 //  indexData->mLayers.erase(std::find(indexData->mLayers.begin(), indexData->mLayers.end(), layer));
 //  indexData->mRedrawNeeded = true;
 //  mIndexRedrawNeeded = true;
 //  if (indexData->mLayers.size() == 0)
 //  {
 //   mIndexData.erase(index_data);
 //   OGRE_DELETE indexData;
 //  }
 // }
 // 
 // mLayers.erase(std::find(mLayers.begin(), mLayers.end(), layer));
 // OGRE_DELETE layer;
 //}

 //void LayerContainer::_createVertexBuffer(size_t initialSize = 32)
 //{
 // mVertexBufferSize = initialSize * 6;
 // mRenderOpPtr->vertexData = OGRE_NEW Ogre::v1::VertexData;
 // mRenderOpPtr->vertexData->vertexStart = 0;
 // 
 // Ogre::v1::VertexDeclaration* vertexDecl = mRenderOpPtr->vertexData->vertexDeclaration;
 // size_t offset = 0;
 // 
 // // Position.
 // vertexDecl->addElement(0,0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
 // offset += Ogre::v1::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
 // 
 // // Colour
 // vertexDecl->addElement(0, offset, Ogre::VET_FLOAT4, Ogre::VES_DIFFUSE);
 // offset += Ogre::v1::VertexElement::getTypeSize(Ogre::VET_FLOAT4);
 // 
 // // Texture Coordinates
 // vertexDecl->addElement(0, offset, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
 // 
 // mVertexBuffer = Ogre::v1::HardwareBufferManager::getSingletonPtr()
 //    ->createVertexBuffer(
 //        vertexDecl->getVertexSize(0),
 //        mVertexBufferSize,
	//	 Ogre::v1::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE,
 //        false
 //    );
 // 
 // mRenderOpPtr->vertexData->vertexBufferBinding->setBinding(0, mVertexBuffer);
 // mRenderOpPtr->operationType = Ogre::v1::RenderOperation::OT_TRIANGLE_LIST;
 // mRenderOpPtr->useIndexes = false;
 //}
 //
 //void LayerContainer::_destroyVertexBuffer()
 //{
 // OGRE_DELETE mRenderOpPtr->vertexData;
 // mRenderOpPtr->vertexData = 0;
 // mVertexBuffer.setNull();
 // mVertexBufferSize = 0;
 //}
 //
 //void LayerContainer::_resizeVertexBuffer(size_t requestedSize)
 //{
 // 
 // if (mVertexBufferSize == 0)
 //  _createVertexBuffer();
 // 
 // if (requestedSize > mVertexBufferSize)
 // {
 //  size_t newVertexBufferSize = 1;
 //  
 //  while(newVertexBufferSize < requestedSize)
 //   newVertexBufferSize <<= 1;
 //  
 //  mVertexBuffer = Ogre::v1::HardwareBufferManager::getSingletonPtr()->createVertexBuffer(
 //    mRenderOpPtr->vertexData->vertexDeclaration->getVertexSize(0),
 //    newVertexBufferSize,
	// Ogre::v1::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE,
 //    false
 //  );
 //  mVertexBufferSize = newVertexBufferSize;
 //  mRenderOpPtr->vertexData->vertexStart = 0;
 //  mRenderOpPtr->vertexData->vertexBufferBinding->setBinding(0, mVertexBuffer);
 // }
 // 
 //}
 //
 //void LayerContainer::_recalculateIndexes()
 //{
 // 
 // std::map<Ogre::uint, IndexData*>::iterator index_data;
 // 
 // // Clear all index data.
 // for(std::map< Ogre::uint, IndexData* >::iterator index_data = mIndexData.begin(); index_data != mIndexData.end(); index_data++)
 // {
 //  (*index_data).second->mVertices.remove_all();
 //  (*index_data).second->mLayers.clear();
 //  (*index_data).second->mRedrawNeeded = false;
 // }
 // 
 // // Loop through layers, and add them to IndexData
 // for(std::vector<Layer*>::iterator layer = mLayers.begin(); layer != mLayers.end(); layer++)
 // {
 //  index_data = mIndexData.find( (*layer)->getIndex() );
 //  if (index_data == mIndexData.end())
 //  {
 //   mIndexData[(*layer)->getIndex()] = OGRE_NEW IndexData();
 //   index_data = mIndexData.find( (*layer)->getIndex() );
 //  }
 //  
 //  (*index_data).second->mLayers.push_back( (*layer) );
 // }
 // 
 // // Prune any index data that is not.
 // bool deleted = false;
 // 
 // while(0xDEADBEEF)
 // {
 //  deleted = false;
 //  for(std::map< Ogre::uint, IndexData* >::iterator index_data = mIndexData.begin(); index_data != mIndexData.end(); index_data++)
 //  {
 //   if (  (*index_data).second->mLayers.size() == 0)
 //   {
 //    OGRE_DELETE (*index_data).second;
 //    mIndexData.erase(index_data);
 //    deleted = true;
 //    break;
 //   }
 //  }
 //  
 //  if (!deleted)
 //   break;
 //  
 // }
 // 
 // mIndexRedrawAll = true;
 // 
 //}
 //
 //void LayerContainer::_redrawIndex(Ogre::uint index, bool force)
 //{
 // 
 // std::map<Ogre::uint, IndexData*>::iterator it = mIndexData.find( index );
 // if (it == mIndexData.end())
 //  return;
 // 
 // IndexData* indexData = (*it).second;
 // 
 // indexData->mVertices.remove_all();
 // indexData->mRedrawNeeded = false;
 // 
 // for (size_t i=0;i < indexData->mLayers.size();i++)
 // {
 //  if (indexData->mLayers[i]->mVisible)
 //   indexData->mLayers[i]->_render( indexData->mVertices, force );
 // }
 // 
 //}
 //
 //void LayerContainer::_requestIndexRedraw(Ogre::uint index)
 //{
 // std::map<Ogre::uint, IndexData*>::iterator it = mIndexData.find( index );
 // if (it == mIndexData.end())
 //  return;
 //  
 // (*it).second->mRedrawNeeded = true;
 // mIndexRedrawNeeded = true;
 //}
 //
 //void LayerContainer::_redrawAllIndexes(bool force)
 //{
 // mIndexRedrawNeeded = false;
 // for(std::map<Ogre::uint, IndexData*>::iterator it = mIndexData.begin(); it != mIndexData.end();it++)
 // {
 //  IndexData* indexData = (*it).second;
 //  if (indexData->mRedrawNeeded || force)
 //  {
 //   //std::cout << "+++ Drawing Index: " << (*it).first;
 //   indexData->mVertices.remove_all();
 //   indexData->mRedrawNeeded = false;
 //   
 //   for (size_t i=0;i < indexData->mLayers.size();i++)
 //   {
 //    if (indexData->mLayers[i]->mVisible)
 //     indexData->mLayers[i]->_render( indexData->mVertices, force );
 //   }
 //  }
 //  
 // }
 //}
 //
 //void LayerContainer::_renderVertices(bool force)
 //{
 // 
 // if (mIndexRedrawNeeded == false)
 //  if (!force)
 //   return;
 // 
 // _redrawAllIndexes(force);
 // 
 // size_t knownVertexCount = 0;
 // 
 // for(std::map<Ogre::uint, IndexData*>::iterator it = mIndexData.begin(); it != mIndexData.end();it++)
 //  knownVertexCount += (*it).second->mVertices.size();
 // 
 // _resizeVertexBuffer(knownVertexCount);
 // //std::cout << "+++ Known Vertex Count is: " << knownVertexCount << "\n";
 // Vertex* writeIterator = (Vertex*)mVertexBuffer->lock(Ogre::v1::HardwareBuffer::HBL_DISCARD);
 // 
 // size_t i = 0;
 // IndexData* indexData = 0;
 // for(std::map<Ogre::uint, IndexData*>::iterator it = mIndexData.begin(); it != mIndexData.end();it++)
 // {
 //  indexData = (*it).second;
 //  for (i=0;i < indexData->mVertices.size();i++)
 //  {
 //   *writeIterator++ = indexData->mVertices[i];
 //  }
 // }
 // 
 // mVertexBuffer->unlock();
 // mRenderOpPtr->vertexData->vertexCount = knownVertexCount;
 //}
 //
 //
 
 /*Layer::Layer(Ogre::uint index, LayerContainer* parent)
 : mIndex(index), mParent(parent), mVisible(true), mAlphaModifier(1.0f)
 {
 }
 
 Layer::~Layer()
 {
 }
 
 void Layer::_markDirty()
 {
  mParent->_requestIndexRedraw(mIndex);
 }*/

 //void Layer::_render(buffer<Vertex>& vertices, bool force)
 //{
 // 
 // if (mAlphaModifier == 0.0f)
 //  return;
 // 
 // size_t begin = vertices.size();
 // size_t i = 0;
 // 
 // // Render/redraw rectangles
 // //for (Rectangles::iterator it = mRectangles.begin(); it != mRectangles.end(); it++)
 // //{
 // // 
 // // if ((*it)->mDirty || force)
 // //  (*it)->_redraw();
 // //
 // // for (i=0; i < (*it)->mVertices.size(); i++)
 // //  vertices.push_back((*it)->mVertices[i]);
 // //
 // //}
 // 

 // if (mAlphaModifier != 1.0f)
 // {
 //  for (i=begin;i < vertices.size();i++)
 //   vertices[i].colour.a *= mAlphaModifier;
 // }
 // 
 // mParent->_transform(vertices, begin, vertices.size());
 // 
 //}

} // namespace Gorilla
