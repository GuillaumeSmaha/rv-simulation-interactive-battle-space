/*!
*  \file  ClassRoot.h
*  \brief Ce fichier contient la déclaration de la classe ClassRoot. 
*/
#ifndef __CLASS_ROOT_H__
#define __CLASS_ROOT_H__

/*!
 * \class ClassRoot
 * \brief Permet de régir toutes les classes sous le même père (cf NSObject ou Object en Objective-C)
 * Permet de faire des casts pour des méthodes de classes.
 */
class ClassRoot
{
	protected:
        /*!
		* \brief Constructor
		*/
        ClassRoot()
        {

        }        
        /*!
         * \brief Destructor
         */
        virtual ~ClassRoot()
        {

        }
};

#endif // __CLASS_ROOT_H__
