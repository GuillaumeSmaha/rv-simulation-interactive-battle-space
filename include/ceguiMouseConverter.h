/*!
 *  \file  ceguiMouseConverter.h
 *  \brief Contient la déclaration de fonctions pour la conversion d'événement de OIS à CEGUI
 */
#ifndef __CEGUI_MOUSE_CONVERTER_H__
#define __CEGUI_MOUSE_CONVERTER_H__

#include <OISMouse.h>
#include <CEGUI.h>

/*!
 *  \brief Converti les événements souris de OIS en événements souris de CEGUI
 *  \param buttonID Evénements souris de OIS 
 * 	\return Evénements souris de CEGUI
 */
CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

#endif //__CEGUI_MOUSE_CONVERTER_H__
