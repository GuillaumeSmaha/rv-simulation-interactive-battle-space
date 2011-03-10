#include "Compteur.h"

using namespace Ogre;


Compteur::Compteur(ShipAbstract * ship, ListenerTime * listenerTime)
{
    this->ship = ship;

    OverlayManager& overlayManager = OverlayManager::getSingleton();
    OverlayContainer* panelCompteurSpeed = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelCompteur"+Utils::toString(Utils::unique())));
    panelCompteurSpeed->setMetricsMode(Ogre::GMM_RELATIVE);
    panelCompteurSpeed->setPosition(0.85, 0.85);
    panelCompteurSpeed->setDimensions(0.15, 0.15);
    panelCompteurSpeed->setMaterialName("jaugeVide");

    OverlayContainer* panelCompteurLife = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelCompteur"+Utils::toString(Utils::unique())));
    panelCompteurLife->setMetricsMode(Ogre::GMM_RELATIVE);
    panelCompteurLife->setPosition(0.0, 0.85);
    panelCompteurLife->setDimensions(0.15, 0.15);
    panelCompteurLife->setMaterialName("jaugeVide");



	panelJaugeNameSpeed = "PanelJauge"+Utils::toString(Utils::unique());
	panelJaugeNameLife = "PanelJauge"+Utils::toString(Utils::unique());

    OverlayContainer * panelJaugeSpeed= static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", panelJaugeNameSpeed));
    panelJaugeSpeed->setMetricsMode(Ogre::GMM_RELATIVE);
    panelJaugeSpeed->setPosition(0.875, 0.86);
    panelJaugeSpeed->setDimensions(0.10, 0.13);
    panelJaugeSpeed->setMaterialName("jaugePleine");

    OverlayContainer * panelJaugeLife= static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", panelJaugeNameLife));
    panelJaugeLife->setMetricsMode(Ogre::GMM_RELATIVE);
    panelJaugeLife->setPosition(0.0025, 0.86);
    panelJaugeLife->setDimensions(0.10, 0.13);
    panelJaugeLife->setMaterialName("jaugePleine");

    overlay = overlayManager.create("OverlayName"+Utils::toString(Utils::unique()));
    overlay->add2D(panelCompteurSpeed);
    overlay->add2D(panelJaugeSpeed);

    overlay->add2D(panelCompteurLife);
    overlay->add2D(panelJaugeLife);



    listenerTime->signalTimerElapsed.add(&Compteur::miseAJour,this);
}

Compteur::~Compteur()
{

}

void Compteur::miseAJour(void *)
{
    miseAJourLifeCompteur();
    miseAJourSpeedCompteur();
}

void Compteur::miseAJourLifeCompteur(void)
{

    OverlayManager& overlayManager = OverlayManager::getSingleton();
    OverlayContainer * jauge= static_cast<OverlayContainer*>(overlayManager.getOverlayElement(panelJaugeNameLife));
    Ogre::Real acLife=this->ship->getShipLife();
    Ogre::Real coef= acLife/ShipAbstract::MAXLIFE;
    jauge->setPosition(0.025, (0.99-0.13*coef));
    jauge->setDimensions(0.10, 0.13*coef);
}

void Compteur::miseAJourSpeedCompteur(void)
{

    OverlayManager& overlayManager = OverlayManager::getSingleton();
    OverlayContainer * jauge= static_cast<OverlayContainer*>(overlayManager.getOverlayElement(panelJaugeNameSpeed));
    Ogre::Real acSpeed=this->ship->getSpeed();
    Ogre::Real coef= acSpeed/ShipAbstract::MAXSPEED;
    jauge->setPosition(0.875, (0.99-0.13*coef));
    jauge->setDimensions(0.10, 0.13*coef);
}

void Compteur::setViewport(Ogre::Viewport * viewport)
{
    viewport->getTarget()->addListener(this);
    viewport->setAutoUpdated(false);
    this->viewport=viewport;
}


void Compteur::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
        overlay->show();
        viewport->update();
        overlay->hide();
}
