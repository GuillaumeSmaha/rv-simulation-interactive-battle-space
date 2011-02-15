#ifndef __VIEWPORT_LOADER_H__
#define __VIEWPORT_LOADER_H__

#include <Ogre.h>
#include <sstream>
#include "Utils.h"
#include "ListenerWindow.h"
#include "CameraFixeAbstract.h"

/*!
 * \class ViewportLoader
 * \brief Gère les différents viewports
 */
class ViewportLoader
{
	private:
        /*!
		 *  \brief ListenerWindow
		 */
		ListenerWindow * listenerWindow;
        /*!
		 *  \brief Liste des viewports
		 */
		std::vector<Ogre::Viewport *> listViewport;
		/*!
		 *  \brief Instance de ViewportLoader pour le singleton
		 */
		static ViewportLoader * _instance ;

	public:
        /*!
		 *  \brief Retourne une instance du singleton
		 */
		static ViewportLoader * getSingleton(void);
		/*!
		 * \brief Supprime l'instance singleton de ViewportLoader
		 * \return Return true si l'instance à a été détruite. false si l'instance n'existait pas ou plus.
		 */
        static bool deleteViewportLoader(void);

        /*!
		 * \brief Constructor
		 * \param sceneMgr Scène de graphe
		 */
		ViewportLoader(ListenerWindow * listenerWindow);
		/*!
		 * \brief Destructor
		 */
		~ViewportLoader(void);
		
		
		/*!
		 * \brief Ajoute un nouveau viewport
		 * \param camera La caméra correspondant au viewport
		 * \return Id du viewport
		 */
		int addViewport(CameraFixeAbstract * gestCamera);
		/*!
		 * \brief Change la caméra affecté à un viewport
		 * \param idViewport Id du viewport
		 * \param camera La caméra correspondant au viewport
		 * \return Si le changement a réussit
		 */
		bool changeCameraViewport(int idViewport, CameraFixeAbstract * gestCamera);
		/*!
		 * \brief Supprime un viewport
		 * \param idViewport Id du viewport
		 * \return Si la suppression à réussit
		 */
		bool removeViewport(int idViewport);
		
		
		//getter/setter
		
         /*!
		 * \brief Retourne le nombre de viewport
		 * \return Nombre de viewport
         */
		int countViewport(void)
		{
			return this->listViewport.size();
		}
		/*!
		 * \brief Retourne la liste des viewport
		 * \return Liste des viewport
         */
		std::vector<Ogre::Viewport *> getListViewport(void)
		{
			return this->listViewport;
		}	
         /*!
		 * \brief Retourne le listener Window
		 * \return Le listener Window
         */
		ListenerWindow * getListenerWindow()
		{
			return this->listenerWindow;
		}
};

#endif // __VIEWPORT_LOADER_H__
