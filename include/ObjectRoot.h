/*!
*  \file  ObjectRoot.h
*  \brief Ce fichier contient la déclaration de la classe ObjectRoot. 
*/
#ifndef __OBJECT_ROOT_H__
#define __OBJECT_ROOT_H__

/*!
 * \class ObjectRoot
 * \brief Permet de régir toutes les classes sous le même père (cf NSObject ou Object en Objective-C)
 * Permet de faire des casts pour des méthodes de classes.
 */
class ObjectRoot
{
	protected:
        /*!
		* \brief Constructor
		*/
        ObjectRoot()
        {

        }        
        /*!
         * \brief Destructor
         */
        virtual ~ObjectRoot()
        {

        }
};

#endif // __OBJECT_ROOT_H__
