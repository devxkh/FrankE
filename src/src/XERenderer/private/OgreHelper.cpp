#include <XERenderer/private/OgreHelper.hpp>

#include <OgreResourceManager.h>
#include <OgreString.h>
#include <OgreLogManager.h>
#include <OgreMaterialManager.h>
#include <OgreTextureManager.h>
#include <OgreHighLevelGpuProgramManager.h>
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgrePass.h>
#include <OgreTechnique.h>

#include <ThirdParty/plog/Log.h>

using namespace Ogre;

#define DEBUG_HELPER 0

namespace OgreHelper
{
	void RenderOneFrame()
	{
		Ogre::Root& root = Ogre::Root::getSingleton();
		Ogre::RenderSystem& render_system = *(root.getRenderSystem());
		//render_system._updateAllRenderTargets(false);
	}
	//---------------------------------------------------------------------
	void UnloadResource(Ogre::ResourceManager* resMgr, const Ogre::String& resourceName)
	{
		Ogre::ResourcePtr rPtr = resMgr->getResourceByName(resourceName);
		if (rPtr.isNull())
		{
			LOG(plog::info) << "Resource no longer exists: " << resourceName;
			return;
		}

		rPtr->unload();
		if (rPtr->isLoaded())
		{
			LOG(plog::info) << "Resource was not unloaded: " << resourceName;
		}
		else
		{
			LOG(plog::info) << "Resource was unloaded: " << resourceName;
		}

		resMgr->remove(resourceName);
		rPtr = resMgr->getResourceByName(resourceName);
		if (rPtr.isNull())
		{
			LOG(plog::info) << "Resource was removed: " << resourceName;
		}
		else
		{
			LOG(plog::info) << "Resource was not removed: " << resourceName;
		}

		if (resMgr->resourceExists(resourceName))
		{
			LOG(plog::info) << "Resource still exists: " << resourceName;
		}
		else
		{
			LOG(plog::info) << "Resource no longer exists: " << resourceName;
		}
	}
	//---------------------------------------------------------------------
	void LoadResource(Ogre::ResourceManager* resMgr, const Ogre::String& resourceName, const Ogre::String& resourceGroup)
	{
		Ogre::ResourcePtr rPtr = resMgr->load(resourceName, resourceGroup);
		if (rPtr.isNull())
		{
			LOG(plog::error) << "Resource no longer exists: " << resourceName;
			return;
		}

		rPtr->reload();
		if (rPtr->isLoaded())
		{
			LOG(plog::info) << "Resource was reloaded: " << resourceName;
		}
		else
		{
			LOG(plog::info) << "Resource was not reloaded: " << resourceName;
		}

		if (resMgr->resourceExists(resourceName))
		{
			LOG(plog::info) << "Resource still exists: " << resourceName;
		}
		else
		{
			LOG(plog::info) << "Resource no longer exists: " << resourceName;
		}
	}
	//---------------------------------------------------------------------
	void UnloadMaterials(const Ogre::String& filename)
	{
		if (filename.empty())
		{
			Ogre::LogManager::getSingleton().logMessage("Filename is empty.");
			return;
		}

		Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(filename);
		if(!stream.isNull())
		{
			try
			{
				while(!stream->eof())
				{
					std::string line = stream->getLine();
					StringUtil::trim(line);

					///
					/// UNLOAD MATERIALS
					///
					if (StringUtil::startsWith(line, "material"))
					{
						std::vector<Ogre::String> vec = StringUtil::split(line," \t:");
						bool skipFirst = true;
						for (std::vector<Ogre::String>::iterator it = vec.begin(); it < vec.end(); ++it)
						{
							if (skipFirst)
							{
								skipFirst = false;
								continue;
							}
							std::string match = (*it);
							StringUtil::trim(match);
							if (!match.empty())
							{
								{
									Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().getByName(match);
									if (!mat.isNull())
									{
										Ogre::Material::TechniqueIterator tech_itr = mat->getTechniqueIterator();
										while (tech_itr.hasMoreElements())
										{
											Ogre::Technique* tech = tech_itr.getNext();
											Ogre::Technique::PassIterator pass_itr = tech->getPassIterator();
											while (pass_itr.hasMoreElements())
											{
												Ogre::Pass* pass = pass_itr.getNext();
												Ogre::Pass::TextureUnitStateIterator tex_itr = pass->getTextureUnitStateIterator();
												while (tex_itr.hasMoreElements())
												{
													Ogre::TextureUnitState* tex = tex_itr.getNext();
													Ogre::String texture_name = tex->getTextureName();
													if (!texture_name.empty())
													{
														Ogre::TextureType tex_type = tex->getTextureType();
														if (tex_type == TEX_TYPE_2D)
														{
															Ogre::TextureManager::getSingleton().unload(texture_name);
														}
													}
												}
											}
										}
									}
								}
								UnloadResource(Ogre::MaterialManager::getSingletonPtr(), match);
								break;
							}
						}
					}
				}
			}
			catch (Ogre::Exception &e)
			{
				LOG(plog::info) << "Exception: FILE: " << __FILE__ << " LINE: " << __LINE__ << " DESC: " << e.getFullDescription();
			}
		}
		stream->close();
	}
	//---------------------------------------------------------------------
	void UnloadVertexPrograms(const Ogre::String& filename)
	{
		if (filename.empty())
		{
			Ogre::LogManager::getSingleton().logMessage("Material filename is empty.");
			return;
		}

		Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(filename);
		if(!stream.isNull())
		{
			try
			{
				while(!stream->eof())
				{
					std::string line = stream->getLine();
					StringUtil::trim(line);

					///
					/// UNLOAD VERTEX PROGRAMS
					///
					if (StringUtil::startsWith(line, "vertex_program") && !StringUtil::startsWith(line, "vertex_program_ref"))
					{
						std::vector<Ogre::String> vec = StringUtil::split(line," \t");
						bool skipFirst = true;
						for (std::vector<Ogre::String>::iterator it = vec.begin(); it < vec.end(); ++it)
						{
							if (skipFirst)
							{
								skipFirst = false;
								continue;
							}
							std::string match = (*it);
							StringUtil::trim(match);
							if (!match.empty())
							{
								UnloadResource(Ogre::HighLevelGpuProgramManager::getSingletonPtr(), match);
								break;
							}
						}
					}
				}
			}
			catch (Ogre::Exception &e)
			{
				LOG(plog::info) << "Exception: FILE: " << __FILE__ << " LINE: " << __LINE__ << " DESC: " << e.getFullDescription();
			}
		}
		stream->close();
	}
	//---------------------------------------------------------------------
	void UnloadFragmentPrograms(const String& filename)
	{
		if (filename.empty())
		{
			Ogre::LogManager::getSingleton().logMessage("Material filename is empty.");
			return;
		}

		Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(filename);
		if(!stream.isNull())
		{
			try
			{
				while(!stream->eof())
				{
					std::string line = stream->getLine();
					StringUtil::trim(line);

					///
					/// UNLOAD FRAGMENT PROGRAMS
					///
					if (StringUtil::startsWith(line, "fragment_program") && !StringUtil::startsWith(line, "fragment_program_ref"))
					{
						std::vector<Ogre::String> vec = StringUtil::split(line," \t");
						bool skipFirst = true;
						for (std::vector<Ogre::String>::iterator it = vec.begin(); it < vec.end(); ++it)
						{
							if (skipFirst)
							{
								skipFirst = false;
								continue;
							}
							std::string match = (*it);
							StringUtil::trim(match);
							if (!match.empty())
							{
								UnloadResource(Ogre::HighLevelGpuProgramManager::getSingletonPtr(), match);
								break;
							}
						}
					}
				}
			}
			catch (Ogre::Exception &e)
			{
				LOG(plog::info) << "Exception: FILE: " << __FILE__ << " LINE: " << __LINE__ << " DESC: " << e.getFullDescription();
			}
		}
		stream->close();
	}
	//---------------------------------------------------------------------
	void ReloadMaterial(const Ogre::String& materialName, const Ogre::String& groupName, const Ogre::String& filename, bool parseMaterialScript)
	{
		if (materialName.empty())
		{
			Ogre::LogManager::getSingleton().logMessage("Material name is empty.");
			return;
		}

		if (groupName.empty())
		{
			Ogre::LogManager::getSingleton().logMessage("Group name is empty.");
			return;
		}

		if (filename.empty())
		{
			Ogre::LogManager::getSingleton().logMessage("Filename is empty.");
			return;
		}

#if defined(_DEBUG) && DEBUG_HELPER
		Ogre::Log::Stream& log_stream = Ogre::LogManager::getSingleton().getDefaultLog()->stream(LML_CRITICAL);
		Ogre::Log::Stream::Flush flush_stream;
		log_stream<<"##################### RELOADING MATERIALS #####################"<<flush_stream;
		log_stream<<"********************* UNLOADING MATERIALS *********************"<<flush_stream;
#endif
		UnloadMaterials(filename);
#if defined(_DEBUG) && DEBUG_HELPER
		log_stream<<"********************* UNLOADING VERTEX PROGRAMS *********************"<<flush_stream;
#endif
		UnloadVertexPrograms(filename);
#if defined(_DEBUG) && DEBUG_HELPER
		log_stream<<"********************* UNLOADING FRAGMENT PROGRAMS *********************"<<flush_stream;
#endif
		UnloadFragmentPrograms(filename);

		if (parseMaterialScript)
		{
#if defined(_DEBUG) && DEBUG_HELPER
			log_stream<<"*********************   PARSING MATERIAL FILE   ***********************"<<flush_stream;
#endif
			Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(filename);
			if(!stream.isNull())
			{
				try
				{
					Ogre::MaterialManager::getSingleton().parseScript(stream, groupName);
					Ogre::MaterialPtr materialPtr = Ogre::MaterialManager::getSingleton().getByName(materialName);
					if (!materialPtr.isNull())
					{
						materialPtr->compile();
						materialPtr->load();
					}
				}
				catch (Ogre::Exception &e)
				{
					LOG(plog::info) << "Exception: FILE: " << __FILE__ << " LINE: " << __LINE__ << " DESC: " << e.getFullDescription();
				}
			}
			stream->close();

#if defined(_DEBUG) && DEBUG_HELPER
			log_stream<<"*********************  RELOADING MATERIAL FILE  ***********************"<<flush_stream;
#endif
			///
			/// RELOAD MATERIAL SCRIPT CONTENTS
			///
			stream = Ogre::ResourceGroupManager::getSingleton().openResource(filename);
			if(!stream.isNull())
			{
				try
				{
					///
					/// RELOAD ALL MATERIAL CONTENTS IN FILE
					///
					while(!stream->eof())
					{
						std::string line = stream->getLine();
						StringUtil::trim(line);
						///
						/// RELOAD MATERIALS
						///
						if (StringUtil::startsWith(line, "material"))
						{
							std::vector<Ogre::String> vec = StringUtil::split(line," \t:");
							bool skipFirst = true;
							for (std::vector<Ogre::String>::iterator it = vec.begin(); it < vec.end(); ++it)
							{
								if (skipFirst)
								{
									skipFirst = false;
									continue;
								}
								std::string match = (*it);
								StringUtil::trim(match);
								if (!match.empty())
								{
									LoadResource(Ogre::MaterialManager::getSingletonPtr(), match, groupName);
									break;
								}
							}
						}
						///
						/// RELOAD VERTEX PROGRAMS
						///
						if (StringUtil::startsWith(line, "vertex_program") && !StringUtil::startsWith(line, "vertex_program_ref"))
						{
							std::vector<Ogre::String> vec = StringUtil::split(line," \t");
							bool skipFirst = true;
							for (std::vector<Ogre::String>::iterator it = vec.begin(); it < vec.end(); ++it)
							{
								if (skipFirst)
								{
									skipFirst = false;
									continue;
								}
								std::string match = (*it);
								StringUtil::trim(match);
								if (!match.empty())
								{
									LoadResource(Ogre::HighLevelGpuProgramManager::getSingletonPtr(), match, groupName);
									break;
								}
							}
						}
						///
						/// RELOAD FRAGMENT PROGRAMS
						///
						if (StringUtil::startsWith(line, "fragment_program") && !StringUtil::startsWith(line, "fragment_program_ref"))
						{
							std::vector<Ogre::String> vec = StringUtil::split(line," \t");
							bool skipFirst = true;
							for (std::vector<Ogre::String>::iterator it = vec.begin(); it < vec.end(); ++it)
							{
								if (skipFirst)
								{
									skipFirst = false;
									continue;
								}
								std::string match = (*it);
								StringUtil::trim(match);
								if (!match.empty())
								{
									LoadResource(Ogre::HighLevelGpuProgramManager::getSingletonPtr(), match, groupName);
									break;
								}
							}
						}
					}
				}
				catch (Ogre::Exception &e)
				{
					LOG(plog::info) << "Exception: FILE: " << __FILE__ << " LINE: " << __LINE__ << " DESC: " << e.getFullDescription();
				}
			}
			stream->close();

			try
			{
				// Do a render test if it fails, leave materials unloaded
				RenderOneFrame();
				//Ogre::Root::getSingleton().renderOneFrame();
				return;
			}
			catch (Ogre::Exception &e)
			{
				UnloadVertexPrograms(filename);

				LOG(plog::error) << "Render test failed. Unloading vertex programs."  << "Exception: FILE: " << __FILE__ << " LINE: " << __LINE__ << " DESC: " << e.getFullDescription();			
			}

			try
			{
				// Do a render test if it fails, leave materials unloaded
				RenderOneFrame();
				//Ogre::Root::getSingleton().renderOneFrame();
			}
			catch (Ogre::Exception &e)
			{
				// Don't load the script this time
				ReloadMaterial(materialName, groupName, filename, false);

				LOG(plog::error) << "Render test failed. Unloading materials." << "Exception: FILE: " << __FILE__ << " LINE: " << __LINE__ << " DESC: " << e.getFullDescription();
			}
		}
#if defined(_DEBUG) && DEBUG_HELPER
		log_stream<<"##################### RELOADING MATERIALS COMPLETE #####################"<<flush_stream;
#endif
	}
	//---------------------------------------------------------------------
	void UpdateSceneManagersForMaterialChange()
	{
		//Ogre::Root& root = Ogre::Root::getSingleton();
		//if(Ogre::Pass::getDirtyHashList().size()!=0 || Ogre::Pass::getPassGraveyard().size()!=0)
		//{
		//	Ogre::SceneManagerEnumerator::SceneManagerIterator scenesIter = root.getSceneManagerIterator();

		//	while(scenesIter.hasMoreElements())
		//	{
		//		Ogre::SceneManager* pScene = scenesIter.getNext();
		//		if(pScene)
		//		{
		//			Ogre::RenderQueue* pQueue = pScene->getRenderQueue();
		//			if(pQueue)
		//			{
		//				Ogre::RenderQueue::QueueGroupIterator groupIter = pQueue->_getQueueGroupIterator();
		//				while(groupIter.hasMoreElements())
		//				{
		//					Ogre::RenderQueueGroup* pGroup = groupIter.getNext();
		//					if(pGroup)
		//						pGroup->clear(false);
		//				}//end_while(groupIter.hasMoreElements())
		//			}//end_if(pScene)
		//		}//end_if(pScene)
		//	}//end_while(scenesIter.hasMoreElements())      

		//	// Now trigger the pending pass updates
		//	Ogre::Pass::processPendingPassUpdates();

		//}//end_if(m_Root..
	}
}
