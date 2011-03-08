/*!
*  \file  ObjectRoot.h
*  \brief Ce fichier contient la déclaration de la classe ObjectRoot. 
*/
#ifndef __OBJECT_ROOT_H__
#define __OBJECT_ROOT_H__

#include "OgreBulletCollisionsShape.h"
#include "OgreBulletDynamicsRigidBody.h"

/*!
 * \class ObjectRoot
 * \brief Permet de définir tous les différents objets et leur volumes englobants
 */
class ObjectRoot
{
	public:
		/*!
		 *  \brief Définit les différents types de mesh
		 */
		enum ObjectType {
			SHIP_PLAYER = 0,
			SHIP_IA = 1,
			PLANET = 2,
			ASTEROID = 3,
			MISSILE = 4,
			LASER = 5
		};
	
	protected:
		/*!
		 *  \brief Bounding Volum de l'objet
		 */
		OgreBulletCollisions::CollisionShape * shape;
		/*!
		 *  \brief Rigid Body
		 */
		OgreBulletDynamics::RigidBody * rigidBody;
		/*!
		 *  \brief Type de l'objet
		 */
		ObjectType typeObject;
	
	protected:
        /*!
		* \brief Constructor
		*/
        ObjectRoot()
        {
			shape = NULL;
			rigidBody = NULL;
        }        
        /*!
         * \brief Destructor
         */
        virtual ~ObjectRoot()
        {
			if(shape != NULL)
				delete shape;
				
			if(rigidBody != NULL)
				delete rigidBody;
        }
        
	public:
	/*
		virtual void createCollisionObject(ListenerCollision * listenerCollision)
		{
			Ogre::Vector3 pos = this->getNode()->getPosition();
			this->shape = new OgreBulletCollisions::SphereCollisionShape(100.0);

			std::ostringstream rigidBodyString;
			rigidBodyString << "RigidObjectRoot" << Utils::toString(this->typeObject) << "_" << Utils::toString(Utils::unique());
			this->rigidBody = new OgreBulletDynamics::RigidBody(rigidBodyString.str() ,listenerCollision->getWorld());

			this->rigidBody->setShape (this->getNode(),  this->shape, 0.6, 0.6, 1.0, pos ,Quaternion(0,0,0,1));
			this->getEntity()->setCastShadows(true);
			
			listenerCollision->getWorld()->addRigidBody(this->rigidBody, 0, 0);
		}
		
		virtual void destroyCollisionObject()
		{
		}
	*/
	
		//Getter/Setter
		
		/*!
		 *  \brief [Getter] Bounding Volum de l'objet
		 * \return Retourne la bounding volum de l'objet
		 */
		OgreBulletCollisions::CollisionShape * getShape(void)
		{
			return shape;
		}
		
		/*!
		 *  \brief [Getter] Rigid Body
		 * \return Retourne rigid body
		 */
		OgreBulletDynamics::RigidBody * getRigidBody(void)
		{
			return rigidBody;
		}
		
		/*!
		 *  \brief [Getter] Type de l'objet
		 * \return Retourne le type de l'objet
		 */
		ObjectType getTypeObject(void)
		{
			return typeObject;
		}
};

#endif // __OBJECT_ROOT_H__
