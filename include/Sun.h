/*!
*  \file Sun.h
*  \brief Ce fichier contient la déclaration de la classe Sun. C'est la classe qui gère un sleil.
*/
#ifndef __SUN_H__
#define __SUN_H__

#include <Ogre.h>
#include "ClassRoot.h"
#include "GestSceneManager.h"



/*!
* \class Sun
* \brief Classe gérant un soleil
*/
class Sun : public ClassRoot
{


	private:
        /*!
         * \brief Couleur actuelle de la lumiere
         */
		Ogre::ColourValue mColour;
        /*!
         * \brief Node contenant le soleil
         */
		Ogre::SceneNode * mNode;
        /*!
         * \brief Billboard pour le halo
         */
		Ogre::BillboardSet * mHaloSet;
        /*!
         * \brief Billboard pour le burst
         */
		Ogre::BillboardSet * mBurstSet;
        /*!
         * \brief Positon du soleil
         */
		Ogre::Vector3 mLightPosition;
		
	public:
        /*!
         * \brief Constructeur
         * \param lightPosition Position de la lumière
         */
		Sun(Ogre::Vector3 lightPosition);
        /*!
         * \brief Destructeur
         */
		virtual ~Sun();
		
		
        /*!
         * \brief Créer le soleil
         */
		void createSun();
		
        /*!
         * \brief Met à jour le rendu du soleil
         * \param evt Evenement de frame
         */
		void update(const Ogre::FrameEvent &evt);
		
        /*!
         * \brief This function updates the light source position. 
         * This function can be used if the light source is moving.
         * \param pos Nouvelle position du soleil
         */
		void setLightPosition(Ogre::Vector3 pos);
        /*!
         * \brief  This function changes the colour of the burst. 
         * \param color Couleur du burst
         */
		void setBurstColour(Ogre::ColourValue color);
        /*!
         * \brief  This function changes the colour of the halos. 
         * \param color Couleur du halo
         */
		void setHaloColour(Ogre::ColourValue color);
		
		/*!
		 * \brief [Getter] Récupère un pointeur sur le noeud content le mesh
		 * \return Nom du noeud
		*/
		Ogre::SceneNode * getNode() 
		{
			return mNode;
		}
};

#endif
