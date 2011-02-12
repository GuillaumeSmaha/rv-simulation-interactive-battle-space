#include "Ship.h"

using namespace Ogre;

Ship::Ship(void) : shipLife(100), xShip(0), yShip(0), zShip(0), wAngleShip(0), xAngleShip(0), yAngleShip(0), zAngleShip(0)
{
    this->entity = MeshLoader::getSingleton()->getNodedEntity(MeshLoader::SHIP);
    this->getNode()->setPosition(0, 0, 0);
    //this->node->getAttachedObject(this->getName())-setMaterialName("razor");

    //TODO:voir pour creer un MeshLoader::getParticleSystem
    Ogre::ParticleSystem* thrusters = MeshLoader::getSingleton()->getSceneManager()->createParticleSystem(25);
    thrusters->setMaterialName("Reactor");
    thrusters->setDefaultDimensions(25, 25);

	// Création de 2 émetteurs pour le système de particules
	for (unsigned int i = 0; i < 2; i++)
	{
		Ogre::ParticleEmitter * emitter = thrusters ->addEmitter("Point");

		// set the emitter properties
		emitter->setAngle(Ogre::Degree(3));
		emitter->setTimeToLive(0.5);
		emitter->setEmissionRate(25);
		emitter->setParticleVelocity(5);
		emitter->setDirection(Vector3::NEGATIVE_UNIT_Z);
		emitter->setColour(ColourValue::White, ColourValue::Red);
		emitter->setPosition(Ogre::Vector3(i == 0 ? 5.7 : -18, 0, 0));
	}
	//this->node->createChildSceneNode(Vector3(0, 6.5, -67))->attachObject(thrusters);
    this->getNode()->createChildSceneNode(Vector3(0, 6.5, -77))->attachObject(thrusters);
}

Ship::~Ship(void)
{

}

void Ship::setShipLife(int shipLife)
{
	this->shipLife = shipLife;
}
int Ship::getShipLife()
{
	return this->shipLife;
}

void Ship::setXShip (Ogre::Real x) {
	this->xShip = x;
}
void Ship::setYShip (Ogre::Real y) {
	this->yShip = y;
}
void Ship::setZShip (Ogre::Real z) {
	this->zShip = z;
}

Ogre::Real Ship::getXShip() {
	return this->xShip;
}
Ogre::Real Ship::getYShip() {
	return this->yShip;
}
Ogre::Real Ship::getZShip() {
	return this->zShip;
}

void Ship::setWAngleShip(Ogre::Real wAngle){
	this->wAngleShip = wAngle;
}
void Ship::setXAngleShip(Ogre::Real xAngle){
	this->xAngleShip = xAngle;
}
void Ship::setYAngleShip(Ogre::Real yAngle){
	this->yAngleShip = yAngle;
}
void Ship::setZAngleShip(Ogre::Real zAngle){
	this->zAngleShip = zAngle;
}
Ogre::Real Ship::getWAngleShip() {
	return this->wAngleShip;
}
Ogre::Real Ship::getXAngleShip() {
	return this->xAngleShip;
}
Ogre::Real Ship::getYAngleShip() {
	return this->yAngleShip;
}
Ogre::Real Ship::getZAngleShip() {
	return this->zAngleShip;
}

void Ship::setOrient(Ogre::Quaternion  q) {
	setWAngleShip(q[0]);
	setXAngleShip(q[1]);
	setYAngleShip(q[2]);
	setZAngleShip(q[3]);
}

Quaternion Ship::getOrient() {
	return Ogre::Quaternion::Quaternion(this->getWAngleShip(),this->getXAngleShip(),this->getYAngleShip(),this->getZAngleShip());
}

void Ship::setSpeed (Ogre::Real speed) {
	this->speed = speed;
}
void Ship::setAcceleration (Ogre::Real acceleration) {
	this->acceleration = acceleration;
}
Ogre::Real Ship::getSpeed() {
	return this->speed;
}
Ogre::Real Ship::getAcceleration() {
	return this->acceleration;
}

void Ship::setPosition(Ogre::Real x, Ogre::Real y, Ogre::Real z)
{
    this->getNode()->setPosition(x, y, z);
}

void Ship::touched(void)
{
   MeshLoader::getSingleton()->setMaterial(this->entity, MeshLoader::SHIP_TOUCHED);
}

void Ship::updatePosition()
{
    /*TODO*/
}

