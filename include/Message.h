/*!
*  \file  Message.h
*  \brief Ce fichier contient la déclaration de la classe Message. Elle permet d'afficher de court messages pendant le jeux
*/
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <Fenetre.h>
#include "Utils.h"
#include "ListenerTime.h"

/*!
* \class Message
* \brief Permet d'afficher de court message pendant le jeux
*/
class Message: public ClassRoot, public Fenetre
{
	private:
		/*!
		* \brief Nombre de message affiché
		*/
		static int nbMessage;
		
		/*!
		* \brief Indique si le message est en cours d'affichage à l'écran
		*/
		bool affiche;
		/*!
		* \brief Variable de temps pour le timer 
		*/
		int elapsedtime;
		
	public:
	  
		/*!
		* \brief Constructeur
		* \param listenerTime Controller de frame régulée
		*/
		Message(ListenerTime * listenerTime)
		{
			listenerTime->signalTimerElapsed.add(&Message::timer, this);
			elapsedtime = 0;
			affiche = false;
		}
		/*!
		* \brief Destructeur
		*/
		~Message()
		{
		}
		
		/*!
		* \brief Affiche un message
		* \param titre Titre du message à afficher
		* \param txt Contenu du message à afficher
		*/
		void afficher_message(CEGUI::utf8 * titre, CEGUI::utf8 * txt);
		/*!
		* \brief Permet de supprimer une fenetre (appeler par create_std_window, ne devrait pas être utilisé ailleurs).
		* \param evt Evenement de CEGUI
		*/
		bool destroyWindow(const CEGUI::EventArgs & evt);
		/*!
		* \brief Permet de supprimer une fenetre (appeler par create_std_window, ne devrait pas être utilisé ailleurs).
		*/
		bool destroyWindow();
		/*!
		* \brief Fonction appelé via le signal pour effacer le message au bout d'un certains temps
		*/
		void timer(void *);
};

#endif
