/*!
*  \file  Signal.h
*  \brief Ce fichier contient la déclaration de la classe Signal.
*/
#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#include <vector>
#include "ObjectRoot.h"


/*!
 * \class Signal
 * \brief Permet la communication entre 2 classes facilement et proprement
 */
template <typename Retour>
class Signal : public ObjectRoot
{
    public:
        /*!
		* \brief Constructor
		*/
        Signal()
        {

        }
        /*!
         * \brief Destructor
         */
        virtual ~Signal()
        {

        }

        /*!
		* \brief Enregistre la fonction passée en paramètre comme listener
		* \param function La fonction listener
		* \param ptrClass La class contenant le listener
		*/
        template<class myclass>
        void add(void (myclass::* function)(Retour), myclass * ptrClass)
        {
			this->listenersClass.push_back(ptrClass);
			this->listenersMethod.push_back((void(ObjectRoot::*)(Retour))function);
        }

        /*!
		* \brief Appelle les différents listeners sans leur passer de paramètre
		*/
        void dispatch(void)
        {
            this->dispatch(NULL);
        }

        /*!
		* \brief Appelle les différents listeners en leur passant un paramètre
		* \param argument Paramètre passé aux listeners
		*/
        void dispatch( Retour argument)
        {
            //Utils::log("Dispatch:");
            /*Ogre::String arg = "-> Argument : ";
            arg.append(Utils::toString(argument));
			Utils::log(arg);*/

			ObjectRoot * ptrClass;
            void (ObjectRoot::* func)(Retour);
            for ( size_t i = 0, size = this->listenersClass.size(); i < size; ++i )
            {
				ptrClass = this->listenersClass[i];
                func = this->listenersMethod[i];
                (ptrClass->*func)(argument);
            }
        }

        /*!
		* \brief Retire des listeners la fonction passée en paramètre
		* \param function La fonction listener
		* \param ptrClass La class contenant le listener
		*/
        template<class myclass>
        void remove(void (myclass::* function)(Retour), myclass * ptrClass)
        {
            void (ObjectRoot::* func)(Retour);
            func = (void(ObjectRoot::*)(Retour))function;
			ObjectRoot * ptr_class = ptrClass;

            for ( size_t i = 0; i < this->listenersClass.size(); ++i )
            {
                if(this->listenersClass[i] == ptr_class && this->listenersMethod[i] == func)
                {
                    this->listenersClass.erase(this->listenersClass.begin()+i);
                    this->listenersMethod.erase(this->listenersMethod.begin()+i);
                    break;
                }
            }
        }

    private:
        /*!
         * \brief Contient la liste des listeners Class
         */
		std::vector<ObjectRoot *> listenersClass;
		std::vector<void (ObjectRoot::*)(Retour)> listenersMethod;
        /*!
         * \brief Contient la liste des listeners Method
         */
};

#endif // __SIGNAL_H__






