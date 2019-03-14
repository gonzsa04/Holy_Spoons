#include "PhysicsComponent.h"
#include <iostream> //temp debug

#include "RenderSystemInterface.h"

void PhysicsComponent::update(GameObject * ent, float time) {
	//auto boxS = nodeS->_getWorldAABB();
	//PxGeometry geoS = , boxS.getSize().y, boxS.getSize().z);
	//std::cout << boxS.getSize().x << std::endl;
}

void PhysicsComponent::setUp() {
	PhysicsSystemManager* physicsManager = PhysicsSystemManager::getSingleton();
	RenderSystemInterface* renderInterface = RenderSystemInterface::getSingleton();

	//cam
	renderInterface->getCameraNode()->setPosition(500, 500, 4000);
	renderInterface->getCameraNode()->lookAt(Ogre::Vector3(0.0f, 0.0f, 0.0f), Ogre::Node::TS_WORLD);
	//auto light = renderInterface->createLight("light", Ogre::Light::LT_POINT, ColourValue(0.75f, 0.2f, 0.2f));
	//light->setPosition(-1.0f, 0.0f, 0.0f);

	//static
	nodeS = renderInterface->createOgreEntity("static", "cube.mesh");
	nodeS->setScale(10.0f, 1.0f, 10.0f);
	nodeS->setPosition(0.0f, -1500.0f, 0.0f);
	PxGeometry *geoS = new PxBoxGeometry(PxVec3(10.0f, 1.0f, 10.0f) / 2); //half extents
	PxTransform transS (PxVec3(0.0f, -15.0f, 0.0f));
	rigidBodyS = physicsManager->createStaticBody(geoS, transS);
	//rigidBodyS->userData = nodeS; //static wont move

	//only after first ogre update...
	//auto boxSs = static_cast<Entity*>(nodeS->getAttachedObject("static"))->getWorldBoundingBox();
	//auto boxS = nodeS->_getWorldAABB();
	//PxGeometry geoS = PxBoxGeometry(boxS.getSize().x, boxS.getSize().y, boxS.getSize().z);

	//dynamic
	nodeD = renderInterface->createOgreEntity("dynamic", "cube.mesh");
	PxGeometry *geoD = new PxBoxGeometry(PxVec3(1.0f));
	PxTransform transD (PxVec3(0.0f, 5.0f, 0.0f) / 2);
	rigidBodyD = physicsManager->createDynamicBody(geoD, transD);
	rigidBodyD->userData = nodeD;
}

void PhysicsComponent::setDown() {
	//release the bodies (which releases the shape etc)
	rigidBodyS->release();
	rigidBodyD->release();
}
