/*!
*  \file  ObjectRoot.h
*  \brief Ce fichier contient la déclaration de la classe ObjectRoot. 
*/
#ifndef __OBJECT_ROOT_H__
#define __OBJECT_ROOT_H__


#include <OgreBulletCollisions.h>
#include <OgreBulletDynamics.h>
#include "OgreBulletCollisionsShape.h"
#include "OgreBulletDynamicsRigidBody.h"

#include "OgreBulletCollisionsPreRequisites.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"
#include "Utils.h"
#include <Ogre.h>


//#include "ListenerCollision.h"

class ListenerCollision;


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
        ObjectRoot();
                
        /*!
         * \brief Destructor
         */
        virtual ~ObjectRoot();
        
        
	public:
        virtual Ogre::SceneNode * getNode() = 0;
        virtual Ogre::String getName() = 0;
        virtual Ogre::Entity * getEntity() = 0;
	
		virtual void createCollisionObject(ListenerCollision * listenerCollision, int size=0);
		
	
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
