/*!
*  \file  ObjectRoot.h
*  \brief Ce fichier contient la déclaration de la classe ObjectRoot.
*/
#ifndef __OBJECT_ROOT_H__
#define __OBJECT_ROOT_H__


#include <map>
#include <Ogre.h>
#include <OgreBlendMode.h>
#include <OgreBulletCollisions.h>
#include <OgreBulletDynamics.h>
#include "OgreBulletCollisionsShape.h"
#include "OgreBulletDynamicsRigidBody.h"

#include "OgreBulletCollisionsPreRequisites.h"
#include "Shapes/OgreBulletCollisionsSphereShape.h"
#include "Utils/OgreBulletCollisionsMeshToShapeConverter.h"
#include "Utils.h"
#include "GestSceneManager.h"
#include "ClassRoot.h"

//#define LIMIT_DOWN_CULLING 0.5
//#define LIMIT_UP_CULLING 0.7
#define LIMIT_DOWN_CULLING 0.005
#define LIMIT_UP_CULLING 0.00625


//#include "ListenerCollision.h"

class ListenerCollision;


/*!
 * \class ObjectRoot
 * \brief Permet de définir tous les différents objets et leur volumes englobants
 */
class ObjectRoot : public ClassRoot
{
	private:
		/*!
		 * \brief Définit les relations entre un rigid body et l'objet associé
		 */
		static std::map<OgreBulletDynamics::RigidBody *, ObjectRoot *> lstRigidbodyToObject;

	public:
		/*!
		 * \brief Ajoute une relation entre le rigidBody et l'objet
		 * \param rigidBody Le rigid body
		 * \param object L'objet
		 */
		static void addRelationRigidbodyToObject(OgreBulletDynamics::RigidBody * rigidBody, ObjectRoot * object);
		/*!
		 * \brief Récupère l'objet en fonction d'un rigid body
		 * \return L'objet lié au rigid body
		*/
		static ObjectRoot * getObjectWithRigidBody(OgreBulletDynamics::RigidBody * rigidBody);
		/*!
		 * \brief Récupère la liste des relations
		 * \return Liste des relations
		*/
		static std::map<OgreBulletDynamics::RigidBody *, ObjectRoot *> getAllRigidbodyToObject();

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
			LASER = 5,
			SHIP_BATTLE_STATION = 6
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
		/*!
		 * \brief [Getter] Récupère le nom du noeud
		 * \return Nom du noeud
		*/
        virtual Ogre::String getName() = 0;
		/*!
		 * \brief [Getter] Récupère un pointeur sur le noeud content le mesh
		 * \return Nom du noeud
		*/
        virtual Ogre::SceneNode * getNode() = 0;
		/*!
		 * \brief [Getter] Récupère un pointeur sur l'entity
		 * \return Nom du noeud
		*/
        virtual Ogre::Entity * getEntity() = 0;

		/*!
		 * \brief Créer le bouding volum du mesh associé
		 * \param listenerCollision Controler de collision
		 * \param size Dimension du volume englobant
		*/
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
		/*!
		 *  \brief [Getter] Rayon de l'objet
		 * \return Retourne le rayon de l'objet
		 */
       virtual Ogre::Real getRadius()
        {
            return this->getEntity()->getWorldBoundingSphere().getRadius();
        }
        /*!
         * \brief Permet de linker avec un signal
         */
		void updateCulling(void*)
		{

		    this->updateCulling();
		}
        /*!
         * \brief Gère le culling suivant la taille affichée (encore expérimental)
         * TODO: alphablending
         */
		virtual void updateCulling(void)
		{

                Ogre::Real size = GestSceneManager::getProjectedSize(this->getEntity(), this->getRadius());
                if(size > -1)
                {

                    //Utils::log(size);
                    if(size < LIMIT_DOWN_CULLING && this->getEntity()->isVisible())
                    {
                       this->getEntity()->setVisible(false);

                    }
                    if(size > LIMIT_UP_CULLING && !this->getEntity()->isVisible())
                    {

                        this->getEntity()->setVisible(true);


                    }
                }

		}
};

#endif // __OBJECT_ROOT_H__
