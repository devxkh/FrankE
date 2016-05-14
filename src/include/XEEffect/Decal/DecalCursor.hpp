    /**
     * @file DecalCursor.h
     * @author Jesse Wright - www.cutthroatstudios.com
     * @note Modified from Brocan's example on the Ogre forums
     * @note Modifications by BloodyFanatic: Decal pass removing and Ogre Shoggoth fix added,
           parameter changed to reference, setPosition 'optimization' removed, proper initialization
     */

    #ifndef SANGUIS_DECALCURSOR_H
    #define SANGUIS_DECALCURSOR_H

    #include "OgreMaterial.h"
    #include "OgreVector3.h"
    #include "OgreVector2.h"

    // forward declaration
    namespace Ogre
    {
       class SceneManager;
       class SceneNode;
       class Frustum;
       class TextureUnitState;
       class Pass;
    }

    /**
     * @class DecalCursor
     * @author Jesse Wright - www.cutthroatstudios.com
     * @date Created on 12/25/2007
     * @date Last modified 5/19/2007
     */
    class DecalCursor
    {
       public:
          DecalCursor(Ogre::SceneManager* man,
                   Ogre::MaterialPtr terrainMat,
                   const Ogre::Vector2& size,
                   const std::string& tex);
          ~DecalCursor();

          inline bool isVisible() const {   return m_bVisible;   }

          Ogre::Vector3 getPosition() const;

          void show();
          void hide();

          void setPosition(const Ogre::Vector3& pos);
          void setSize(const Ogre::Vector2& size);

       private:
          void init(const Ogre::Vector2& size, const std::string& tex);
          void showTerrainDecal();
          void hideTerrainDecal();

          Ogre::Vector2 m_size;            /**< @brief size of decal */
         Ogre::Vector3 m_pos;

          std::string m_sTexName;            /**< @brief texture to apply */

          Ogre::SceneNode* m_nodeProj;         /**< @brief the projection node */
          Ogre::Frustum* m_frustProj;         /**< @brief the projection frustum */
          Ogre::TextureUnitState* m_texState;   /**< @brief pointer to the texture unit state in the pass */
          Ogre::Pass* m_pass;               /**< @brief pointer to the decal pass */
          Ogre::MaterialPtr m_terrainMat;      /**< @brief sharedptr to the terrain material */

          Ogre::SceneManager* m_sceneMgr;      /**< @brief Pointer to the application's Ogre::SceneManager */

          bool m_bVisible;                  /**< @brief true if the decal visible, otherwise false */
    };

    #endif