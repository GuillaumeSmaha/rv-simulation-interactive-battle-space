 #include "SpeedCompteur.h"
 
using namespace Ogre;


SpeedCompteur::SpeedCompteur(ShipAbstract * ship, ListenerTime * listenerTime)
{
    this->ship = ship;

    OverlayManager& overlayManager = OverlayManager::getSingleton();
    OverlayContainer* panelCompteur = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelCompteur"+Utils::toString(Utils::unique())));
    panelCompteur->setMetricsMode(Ogre::GMM_RELATIVE);
    panelCompteur->setPosition(0.85, 0.85);
    panelCompteur->setDimensions(0.15, 0.15);
    panelCompteur->setMaterialName("jaugeVide");

	panelJaugeName = "PanelJauge"+Utils::toString(Utils::unique());
    OverlayContainer * panelJauge= static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", panelJaugeName));
    panelJauge->setMetricsMode(Ogre::GMM_RELATIVE);
    panelJauge->setPosition(0.875, 0.86);
    panelJauge->setDimensions(0.10, 0.13);
    panelJauge->setMaterialName("jaugePleine");


    overlay = overlayManager.create("OverlayName"+Utils::toString(Utils::unique()));
    overlay->add2D(panelCompteur);
    overlay->add2D(panelJauge);


    listenerTime->signalTimerElapsed.add(&SpeedCompteur::miseAJour,this);
}

SpeedCompteur::~SpeedCompteur()
{

}

void SpeedCompteur::setViewport(Ogre::Viewport * viewport)
{
    viewport->getTarget()->addListener(this);
    viewport->setAutoUpdated(false);
    this->viewport=viewport;
}

void SpeedCompteur::miseAJour(void * useless)
{
    OverlayManager& overlayManager = OverlayManager::getSingleton();
    OverlayContainer * jauge= static_cast<OverlayContainer*>(overlayManager.getOverlayElement(panelJaugeName));
    Ogre::Real acSpeed=this->ship->getSpeed();
    Ogre::Real coef= acSpeed/ShipAbstract::MAXSPEED;
    jauge->setPosition(0.875, (0.99-0.13*coef));
    jauge->setDimensions(0.10, 0.13*coef);
}

void SpeedCompteur::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
        overlay->show();
        viewport->update();
        overlay->hide();
}
