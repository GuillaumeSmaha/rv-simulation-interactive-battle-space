#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#include <vector>
#include "Utils.h"

/*!
 * \class Signal
 * \brief Permet la communication entre 2 classes facilement et proprement
 */
template <typename Retour>
//typedef  void(*SIGNAL)(Retour);

class Signal
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
		*/
        template<typename myclass>
        void add(void (myclass::* function)(Retour))
        {
               this->listeners.push_back((void(*)(Retour))function);
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
            Utils::log("Dispatch:");
            Utils::log(argument);
            void (* func)(Retour);
            for ( size_t i = 0, size = this->listeners.size(); i < size; ++i )
            {
                //(*(this->listeners[i])) (argument);
                func = this->listeners[i];
                (*func)(argument);
            }
        }
        
        /*!
		* \brief Retire des listeners la fonction passée en paramètre
		* \param function La fonction listener
		*/
        template<typename myclass>
        void remove(void (myclass::* function)(Retour))
        {
            void (* func)(Retour);
            func = (void(*)(Retour))function;
            std::vector<void (* )(Retour)> _listeners;
            for ( size_t i = 0; i < this->listeners.size(); ++i )
            {
                if(this->listeners[i]!=func)
                {
                    _listeners.push_back(this->listeners[i]);
                }
            }
            this->listeners = _listeners;
        }

    private:
        /*!
         * \brief Contient la liste des listeners
         */
		//  std::vector<void (* )(void *)> listeners;
		std::vector<void (* )(Retour)> listeners;
};

#endif // __SIGNAL_H__






