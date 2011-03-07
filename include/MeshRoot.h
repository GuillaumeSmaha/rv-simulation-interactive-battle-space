/*!
*  \file  MeshRoot.h
*  \brief Ce fichier contient la déclaration de la classe MeshRoot. 
*/
#ifndef __MESH_ROOT_H__
#define __MESH_ROOT_H__

#include "OgreBulletCollisionsShape.h"
#include "OgreBulletDynamicsRigidBody.h"

/*!
 * \class MeshRoot
 * \brief Permet de régir tous les mesh sous le même père.
 */
class MeshRoot
{
	public:
		/*!
		 *  \brief Définit les différents types de mesh
		 */
		enum MeshType {
			SHIP = 0,
			PLANET = 1,
			ASTEROID = 2,
			MISSILE = 3,
			LASER = 4
		};
	
	protected:
		/*!
		 *  \brief Bounding Box de l'objet
		 */
		OgreBulletCollisions::CollisionShape * shape;
		/*!
		 *  \brief Rigid Body
		 */
		OgreBulletDynamics::RigidBody * rigidBody;
		/*!
		 *  \brief Type du mesh
		 */
		MeshType typeMesh;
	
	protected:
        /*!
		* \brief Constructor
		*/
        MeshRoot()
        {
			shape = NULL;
			rigidBody = NULL;
        }        
        /*!
         * \brief Destructor
         */
        virtual ~MeshRoot()
        {
			if(shape != NULL)
				delete shape;
				
			if(rigidBody != NULL)
				delete rigidBody;
        }
};

#endif // __MESH_ROOT_H__
