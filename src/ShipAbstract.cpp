#include "ShipAbstract.h"

using namespace Ogre;

Ogre::Real ShipAbstract::MAXSPEED = 100;
Ogre::Real ShipAbstract::MAXLIFE= 100;

ShipAbstract::ShipAbstract(ObjectRoot::ObjectType type)
	: shipLife(100),
	  speed(0), translateSpeed(0), rollSpeed(0), pitchSpeed(0), yawSpeed(0),
	  acceleration(0), translateAcceleration(0), rollAcceleration(0), pitchAcceleration(0), yawAcceleration(0),
	  isTouched(false), isDead(false), firstPos(true), firstDir(true)
{
    if(type == ObjectRoot::SHIP_IA)
    {
        this->entity = static_cast<Ogre::Entity *>(MeshLoader::getSingleton()->getNodedMovableObject(MeshLoader::SHIP_IA));
    }
    else
    {
        if(type == ObjectRoot::SHIP_BATTLE_STATION)
        {
            this->entity = static_cast<Ogre::Entity *>(MeshLoader::getSingleton()->getNodedMovableObject(MeshLoader::SHIP_BATTLE_STATION));
        }
        else
        {
            this->entity = static_cast<Ogre::Entity *>(MeshLoader::getSingleton()->getNodedMovableObject(MeshLoader::SHIP));
        }
    }

	// Calcul des tangentes (si pas présentes dans le mesh)
	unsigned short src, dest;
	if (!this->entity->getMesh()->suggestTangentVectorBuildParams(VES_TANGENT, src, dest))
	{
		this->entity->getMesh()->buildTangentVectors(VES_TANGENT, src, dest);
	}

	this->colorLaser = Ogre::ColourValue::Red;

    this->getNode()->setPosition(0, 0, 0);

    this->defineParticules();
}

ShipAbstract::~ShipAbstract(void)
{
	MeshLoader::getSingleton()->deleteNodedObject(MeshLoader::SHIP, this->getEntity());
}


void ShipAbstract::updatePosition(void)
{
    std::cout<<"vitesse"<<this->getRollSpeed()<<std::endl;
    std::cout<<"acceleration"<<this->getRollAcceleration()<<std::endl;
    //calcule des nouvelles vitesses et positions
    this->setSpeed(this->getSpeed()+this->getAcceleration());
	this->setTranslateSpeed(this->getTranslateSpeed() + this->getTranslateAcceleration());
	//if (this->getSpeed() != 0)
	//{
		//this->moveRelative(0.0, 0.0, this->getSpeed());
	this->moveRelative(this->getTranslateSpeed(), 0.0, this->getSpeed());
	//}

    this->setRollSpeed(this->getRollSpeed()+this->getRollAcceleration());
    this->rotateRollRelative(this->getRollSpeed());

	this->setYawSpeed(this->getYawSpeed()+this->getYawAcceleration());
    this->rotateYawRelative(this->getYawSpeed());

    this->setPitchSpeed(this->getPitchSpeed()+this->getPitchAcceleration());
    this->goUp(this->getPitchSpeed());

    //on réduit chacune des accélérations
    this->setAcceleration(0);
	this->setTranslateAcceleration(0);
    this->setPitchAcceleration(Ogre::Radian(0));
    this->setRollAcceleration(Ogre::Radian(0));
	this->setYawAcceleration(Ogre::Radian(0));
}


void ShipAbstract::touched(void)
{
   MeshLoader::getSingleton()->setMaterial(this->entity, MeshLoader::SHIP_TOUCHED);
   GestSound::getSingleton()->play(GestSound::SOUND_DEGATS);
}

void ShipAbstract::exploded(Ogre::Real size)
{
	Ogre::ParticleSystem * particleSystem = GestSceneManager::getSceneManager()->createParticleSystem("explosions"+Utils::toString(Utils::unique()), "explosionTemplate");
	particleSystem->setDefaultDimensions(size, size);

	// fast forward 1 second  to the point where the particle has been emitted
	particleSystem->fastForward(1.0);

	GestSound::getSingleton()->play(GestSound::SOUND_EXPLOSION);
	// attach the particle system to a scene node
    //~ this->getNode()->createChildSceneNode(Vector3(0.0, 45.0, 0.0))->attachObject(particleSystem);
    this->getNode()->createChildSceneNode(Vector3(0.0, 0.0, 0.0))->attachObject(particleSystem);

    this->isDead = true;

	switch(this->getTypeObject())
	{
		case ObjectRoot::SHIP_PLAYER :
		{
			std::cout << "ShipPlayer : Explosion de " << this->getName() << std::endl;
            Message* message = Message::getSingleton();
            message->afficher_message((CEGUI::utf8*)"Rapport de mission",(CEGUI::utf8 *)"Capitaine, nous avons été détruit!");
			break;
		}

		case ObjectRoot::SHIP_IA :
		{
			std::cout << "ShipIA : Explosion de " << this->getName() << std::endl;
            Message* message = Message::getSingleton();
            message->afficher_message((CEGUI::utf8*)"Rapport de mission",(CEGUI::utf8 *)"Capitaine, un vaisseau ennemi de moins!");
			break;
        }

		case ObjectRoot::SHIP_BATTLE_STATION :
        {
			std::cout << "ShipBattleStation : Explosion de " << this->getName() << std::endl;
            Message* message = Message::getSingleton();
            message->afficher_message((CEGUI::utf8*)"Rapport de mission",(CEGUI::utf8 *)"Capitaine, La station spatiale est détruite!");
			break;
		}

		default:
			break;
	}
}


void ShipAbstract::shootLaser(void)
{
	GestLaser::getSingleton()->create(this->getNode()->_getDerivedPosition(), this->getNode()->_getDerivedOrientation(), this->getColorLaser());
}


void ShipAbstract::defineParticules(void)
{
    thrusters = MeshLoader::getSingleton()->getSceneManager()->createParticleSystem(25);
    thrusters->setMaterialName("Reactor");
    thrusters->setDefaultDimensions(25, 25);
    thrusters->setKeepParticlesInLocalSpace(true);

	// Création de 2 émetteurs pour le système de particules
	for (unsigned int i = 0; i < 2; i++)
	{
		Ogre::ParticleEmitter * emitter = thrusters->addEmitter("Point");

		// set the emitter properties
		emitter->setAngle(Ogre::Degree(3));
		emitter->setTimeToLive(0.5);
		emitter->setEmissionRate(25);
		emitter->setParticleVelocity(5);
		emitter->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Z);
		emitter->setColour(Ogre::ColourValue::White, Ogre::ColourValue::Red);
		emitter->setPosition(Ogre::Vector3(i == 0 ? 12.7 : -5, 0, 0));
	}
    this->getNode()->createChildSceneNode(Vector3(0, 6.5, -77))->attachObject(thrusters);
}


void ShipAbstract::isTouch(int degat)
{
    if(isDead == false)
    {
        setShipLife(getShipLife()-degat);
        if(getShipLife() < 0)
        {
			switch(this->getTypeObject())
			{
				case ObjectRoot::SHIP_BATTLE_STATION :
					this->exploded(1000);
					break;

				default:
					this->exploded();
					break;
			}
            isDead = true;
        }
        else
        {
            if(isTouched == false)
            {
                isTouched = true;
                touched();
            }
        }
    }
}



//void ShipAbstract::createCollisionObject(ListenerCollision * listenerCollision)
//{
//    Ogre::Vector3 pos = this->getNode()->getPosition();
//	this->shape = new OgreBulletCollisions::SphereCollisionShape(100.0);
//
//    std::ostringstream rigidBodyString;
//    rigidBodyString << "RigidShip" << Utils::toString(Utils::unique());
//    this->rigidBody = new OgreBulletDynamics::RigidBody(rigidBodyString.str() ,listenerCollision->getWorld());
//
//    this->rigidBody->setShape (this->getNode(),  this->shape, 0.6, 0.6, 1.0, pos ,Quaternion(0,0,0,1));
//    this->getEntity()->setCastShadows(true);
//
//    //rigidBody->setPosition(pos[0], pos[1], pos[2]);
//
//}


void ShipAbstract::move(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	Vector3 pos = this->getPosition();
	this->setPosition(pos[0]+x, pos[1]+y, pos[2]+z);
}

void ShipAbstract::move(const Ogre::Vector3 &vec)
{
	Vector3 pos = this->getPosition() + vec;
	this->setPosition(pos[0], pos[1], pos[2]);
}


void ShipAbstract::moveRelative(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
	Ogre::Vector3 vec = Ogre::Vector3(x, y, z);
	this->moveRelative(vec);
}

void ShipAbstract::moveRelative(const Ogre::Vector3 &vec)
{
	Vector3 trans = this->getOrientation() * vec;
	Vector3 pos = this->getPosition() + trans;
	this->setPosition(pos[0], pos[1], pos[2]);
}

void ShipAbstract::rotateRollRelative(const Ogre::Radian w)
{
    this->entity->getParentNode()->roll(w);
}

void ShipAbstract::rotateYawRelative(const Ogre::Radian w)
{
    this->entity->getParentNode()->yaw(w);
}

void ShipAbstract::goUp(const Ogre::Radian w)
{
    this->entity->getParentNode()->pitch(w);
}

void ShipAbstract::accelerate(const Ogre::Real coefAcceleration)
{
    this->acceleration += coefAcceleration;

}

void ShipAbstract::translateAccelerate(const Ogre::Real coefAcceleration)
{
	if(coefAcceleration > 0.0)
		this->translateAcceleration += coefAcceleration*this->getFactorRotation();
	else
		this->translateAcceleration += coefAcceleration;
}

void ShipAbstract::rollAccelerate(const Ogre::Radian coefAcceleration)
{
    this->rollAcceleration += Ogre::Radian(coefAcceleration.valueRadians()*this->getFactorRotation());
}

void ShipAbstract::pitchAccelerate(const Ogre::Radian coefAcceleration)
{
    this->pitchAcceleration += Ogre::Radian(coefAcceleration.valueRadians()*this->getFactorRotation());
}

void ShipAbstract::yawAccelerate(const Ogre::Radian coefAcceleration)
{
    this->yawAcceleration += Ogre::Radian(coefAcceleration.valueRadians()*this->getFactorRotation());
}


Ogre::Real ShipAbstract::getFactorRotation(int method)
{
	Ogre::Real factor;
	Ogre::Real ratio = this->getSpeed()/ShipAbstract::MAXSPEED;
	if(method == 2)
	{
		factor = ratio*ratio*ratio;
		//~ factor = std::min(1.0, std::max(0.0, ratio*ratio*ratio*0.5+0.5));
	}
	else
	{
		if(ratio < 0.01)
		{
			factor = 0.0;
		}
		else
		{
			//~ factor = (log10(ratio)+2.0)/2.0;
			factor = std::min(1.0, std::max(0.0, ((log10(ratio)+2.0)/2.0) * 0.25 + 0.75));
		}
	}

	return factor;
}

//Getter-Setter




Quaternion ShipAbstract::getOrientation(void)
{
	return this->getNode()->getOrientation();
}

void ShipAbstract::setOrientation(const Ogre::Quaternion &q)
{
    if(firstDir)
    {
        dirInit = q;
        firstDir = false;
    }
	this->getNode()->setOrientation(q);
}

void ShipAbstract::setOrientation(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z, const Ogre::Real a)
{
    if(firstDir)
    {
        dirInit = Quaternion(x,y,z,a);
        firstDir = false;
    }
	this->getNode()->setOrientation(x, y, z, a);
}


Ogre::Vector3 ShipAbstract::getPosition(void)
{
    return this->getNode()->getPosition();
}

void ShipAbstract::setPosition(const Ogre::Vector3 &v)
{
    if(firstPos)
    {
        posInit = v;
        firstPos = false;
    }
    this->getNode()->setPosition(v);
}

void ShipAbstract::setPosition(const Ogre::Real x, const Ogre::Real y, const Ogre::Real z)
{
    if(firstPos)
    {
        posInit[0] = x;
        posInit[1] = y;
        posInit[2] = z;
        firstPos = false;
    }
    this->getNode()->setPosition(x, y, z);
}

void ShipAbstract::reset()
{
    setSpeed(0);
    setAcceleration(0);
    setTranslateSpeed(0);
    setTranslateAcceleration(0);
    setRollSpeed(Ogre::Radian(0));
    setRollAcceleration(Ogre::Radian(0));
    setPitchSpeed(Ogre::Radian(0));
    setPitchAcceleration(Ogre::Radian(0));
    setYawSpeed(Ogre::Radian(0));
    setYawAcceleration(Ogre::Radian(0));
    setPosition(posInit);
    setOrientation(dirInit);
}
