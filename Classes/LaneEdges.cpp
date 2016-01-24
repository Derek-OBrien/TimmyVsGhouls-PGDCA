
#include "LaneEdges.h"


LaneEdge::LaneEdge(){

}

void LaneEdge::create(Layer* layer){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//Add Collision to Bottom Edge Only 
	auto bottomEdgeBody = PhysicsBody::createEdgeSegment(
		Vec2(origin.x - (visibleSize.width / 2), origin.y - (visibleSize.height / 2)),	//Point a Bottom left corner
		Vec2(origin.x + (visibleSize.width / 2) * 500, origin.y - (visibleSize.height / 2)),	    //Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		10);											//Border

	//Set up edgebody settings
	bottomEdgeBody->setCollisionBitmask(0x001);		//Set Collision Bitmask
	bottomEdgeBody->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	bottomEdgeBody->setMass(PHYSICS_INFINITY);

	auto bottomEdgeNode = Node::create();	//Node for bottom edge collision
	bottomEdgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bottomEdgeNode->setPhysicsBody(bottomEdgeBody);
	layer->addChild(bottomEdgeNode, 6);

	//Add Collision to Top Edge 
	auto topEdgeBody = PhysicsBody::createEdgeSegment(
		Vec2(origin.x , visibleSize.height / 2),	//
		Vec2(origin.x + visibleSize.width , visibleSize.height / 2),	//Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		2);											//Border

	//Set up edgebody settings
	topEdgeBody->setCollisionBitmask(0x02);		//Set Collision Bitmask
	topEdgeBody->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	topEdgeBody->setMass(PHYSICS_INFINITY);

	auto topEdgeNode = Node::create();	//Node for bottom edge collision
	topEdgeNode->setPosition(Vec2(origin.x, visibleSize.height /2));
	topEdgeNode->setPhysicsBody(topEdgeBody);
	layer->addChild(topEdgeNode, 6);



	/****************************************************************************************************************************/
	//Lanes from bottom up 
	/****************************************************************************************************************************/

	/*Top Of Bottom Lane*/
	auto laneEdgeBody = PhysicsBody::createEdgeSegment(
		Vec2(origin.x + visibleSize.width / 10, origin.y + visibleSize.height / 16),	//
		Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height / 16),	//Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		2);											//Border

	//Set up edgebody settings
	laneEdgeBody->setCollisionBitmask(0x02);		//Set Collision Bitmask
	laneEdgeBody->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	laneEdgeBody->setMass(PHYSICS_INFINITY);

	auto laneEdgeNode = Node::create();
	laneEdgeNode->setPosition(Vec2(origin.x + visibleSize.width / 10, origin.y + visibleSize.height / 16));
	laneEdgeNode->setPhysicsBody(laneEdgeBody);
	layer->addChild(laneEdgeNode, 6);


	//top of second lane
	auto laneEdgeBody2 = PhysicsBody::createEdgeSegment(
		Vec2(origin.x + visibleSize.width / 24, origin.y + visibleSize.height / 8),	//
		Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height / 8),	//Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		2);											//Border

	//Set up edgebody settings
	laneEdgeBody2->setCollisionBitmask(0x02);		//Set Collision Bitmask
	laneEdgeBody2->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	laneEdgeBody2->setMass(PHYSICS_INFINITY);

	auto laneEdgeNode2 = Node::create();
	laneEdgeNode2->setPosition(Vec2(origin.x + visibleSize.width / 24, origin.y + visibleSize.height / 8));
	laneEdgeNode2->setPhysicsBody(laneEdgeBody2);
	layer->addChild(laneEdgeNode2, 6);



	/*Middle Lane*/
	auto laneEdgeBody3 = PhysicsBody::createEdgeSegment(
		Vec2(origin.x + visibleSize.width / 24, origin.y + visibleSize.height / 4),	//
		Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height / 4),	//Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		2);											//Border

	//Set up edgebody settings
	laneEdgeBody3->setCollisionBitmask(0x02);		//Set Collision Bitmask
	laneEdgeBody3->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	laneEdgeBody3->setMass(PHYSICS_INFINITY);

	auto laneEdgeNode3 = Node::create();
	laneEdgeNode3->setPosition(Vec2(origin.x + visibleSize.width / 24, origin.y + visibleSize.height / 4));
	laneEdgeNode3->setPhysicsBody(laneEdgeBody3);
	layer->addChild(laneEdgeNode3, 6);

	/**/
	auto laneEdgeBody4 = PhysicsBody::createEdgeSegment(
		Vec2(origin.x + visibleSize.width / 10, origin.y + visibleSize.height / 4 - visibleSize.height / 16),	//
		Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height / 4 - visibleSize.height / 16),	//Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		2);											//Border

	//Set up edgebody settings
	laneEdgeBody4->setCollisionBitmask(0x02);		//Set Collision Bitmask
	laneEdgeBody4->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	laneEdgeBody4->setMass(PHYSICS_INFINITY);

	auto laneEdgeNode4 = Node::create();
	laneEdgeNode4->setPosition(Vec2(origin.x + visibleSize.width / 10, origin.y + visibleSize.height / 4 - visibleSize.height / 16));
	laneEdgeNode4->setPhysicsBody(laneEdgeBody4);
	layer->addChild(laneEdgeNode4, 6);


	/*Top Of Bottom Lane*/
	auto laneEdgeBody7 = PhysicsBody::createEdgeSegment(
		Vec2(origin.x + visibleSize.width / 10, visibleSize.height / 4 + visibleSize.height / 16),	//
		Vec2(origin.x + visibleSize.width, visibleSize.height / 4 + visibleSize.height / 16),	//Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		2);											//Border

	//Set up edgebody settings
	laneEdgeBody7->setCollisionBitmask(0x02);		//Set Collision Bitmask
	laneEdgeBody7->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	laneEdgeBody7->setMass(PHYSICS_INFINITY);

	auto laneEdgeNode7 = Node::create();
	laneEdgeNode7->setPosition(Vec2(origin.x + visibleSize.width / 10, visibleSize.height / 4 + visibleSize.height / 16));
	laneEdgeNode7->setPhysicsBody(laneEdgeBody7);
	layer->addChild(laneEdgeNode7, 6);



	//top of second lane
	auto laneEdgeBody6 = PhysicsBody::createEdgeSegment(
		Vec2(origin.x + visibleSize.width / 24, visibleSize.height / 4 + visibleSize.height / 8),	//
		Vec2(origin.x + visibleSize.width, visibleSize.height / 4 + visibleSize.height / 8),	//Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		2);											//Border

	//Set up edgebody settings
	laneEdgeBody6->setCollisionBitmask(0x02);		//Set Collision Bitmask
	laneEdgeBody6->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	laneEdgeBody6->setMass(PHYSICS_INFINITY);

	auto laneEdgeNode6 = Node::create();
	laneEdgeNode6->setPosition(Vec2(origin.x + visibleSize.width / 24, visibleSize.height / 4 + visibleSize.height / 8));
	laneEdgeNode6->setPhysicsBody(laneEdgeBody6);
	layer->addChild(laneEdgeNode6, 6);






	//Add Collision to Bottom Edge Only 
	auto laneEdgeBody8 = PhysicsBody::createEdgeSegment(
		Vec2(origin.x + visibleSize.width / 10, visibleSize.height / 2 - visibleSize.height / 16),	//
		Vec2(origin.x + visibleSize.width , visibleSize.height /2 - visibleSize.height / 16),	//Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		2);											//Border

	//Set up edgebody settings
	laneEdgeBody8->setCollisionBitmask(0x02);		//Set Collision Bitmask
	laneEdgeBody8->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	laneEdgeBody8->setMass(PHYSICS_INFINITY);

	auto laneEdgeNode8 = Node::create();	//Node for bottom edge collision
	laneEdgeNode8->setPosition(Vec2(origin.x + visibleSize.width / 10, visibleSize.height / 2 - visibleSize.height / 16));
	laneEdgeNode8->setPhysicsBody(laneEdgeBody8);
	layer->addChild(laneEdgeNode8, 6);




	//Add Collision to Bottom Edge Only 
	auto laneEdgeBodyShort = PhysicsBody::createEdgeSegment(
		Vec2(origin.x, visibleSize.height / 2 - visibleSize.height / 16),	//
		Vec2(origin.x + visibleSize.width / 8, visibleSize.height / 2 - visibleSize.height / 16),	//Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		2);											//Border

	//Set up edgebody settings
	laneEdgeBodyShort->setCollisionBitmask(0x02);		//Set Collision Bitmask
	laneEdgeBodyShort->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	laneEdgeBodyShort->setMass(PHYSICS_INFINITY);

	auto laneEdgeNodeShort = Node::create();	//Node for bottom edge collision
	laneEdgeNodeShort->setPosition(Vec2(origin.x, visibleSize.height / 2 - visibleSize.height / 16));
	laneEdgeNodeShort->setPhysicsBody(laneEdgeBodyShort);
	layer->addChild(laneEdgeNodeShort, 6);


	//Add Collision to Bottom Edge Only 
	auto laneEdgeBodyShort2 = PhysicsBody::createEdgeSegment(
		Vec2(origin.x, origin.y + visibleSize.height / 16),	//
		Vec2(origin.x + visibleSize.width / 8, origin.y + visibleSize.height / 16),	//Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		2);											//Border

	//Set up edgebody settings
	laneEdgeBodyShort2->setCollisionBitmask(0x02);		//Set Collision Bitmask
	laneEdgeBodyShort2->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	laneEdgeBodyShort2->setMass(PHYSICS_INFINITY);

	auto laneEdgeNodeShort2 = Node::create();	//Node for bottom edge collision
	laneEdgeNodeShort2->setPosition(Vec2(origin.x, origin.y + visibleSize.height / 16));
	laneEdgeNodeShort2->setPhysicsBody(laneEdgeBodyShort2);
	layer->addChild(laneEdgeNodeShort2, 6);

	//Add Collision to Bottom Edge Only 
	auto laneEdgeBodyShort3 = PhysicsBody::createEdgeSegment(
		Vec2(origin.x, origin.y + visibleSize.height / 4 - visibleSize.height / 16),	//
		Vec2(origin.x + visibleSize.width / 8, origin.y + visibleSize.height / 4 - visibleSize.height / 16),	//Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		2);											//Border

	//Set up edgebody settings
	laneEdgeBodyShort3->setCollisionBitmask(0x02);		//Set Collision Bitmask
	laneEdgeBodyShort3->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	laneEdgeBodyShort3->setMass(PHYSICS_INFINITY);

	auto laneEdgeNodeShort3 = Node::create();	//Node for bottom edge collision
	laneEdgeNodeShort3->setPosition(Vec2(origin.x, origin.y + visibleSize.height / 4 - visibleSize.height / 16));
	laneEdgeNodeShort3->setPhysicsBody(laneEdgeBodyShort3);
	layer->addChild(laneEdgeNodeShort3, 6);



	//Add Collision to Bottom Edge Only 
	auto laneEdgeBodyShort4 = PhysicsBody::createEdgeSegment(
		Vec2(origin.x, origin.y + visibleSize.height / 4 + visibleSize.height / 16),	//
		Vec2(origin.x + visibleSize.width / 8, origin.y + visibleSize.height / 4 + visibleSize.height / 16),	//Point b Bottom right corner
		PHYSICSBODY_MATERIAL_DEFAULT,					//Material
		2);											//Border

	//Set up edgebody settings
	laneEdgeBodyShort4->setCollisionBitmask(0x02);		//Set Collision Bitmask
	laneEdgeBodyShort4->setContactTestBitmask(true);						//Turn on Collision Bitmask so it is picked up
	laneEdgeBodyShort4->setMass(PHYSICS_INFINITY);

	auto laneEdgeNodeShort4 = Node::create();	//Node for bottom edge collision
	laneEdgeNodeShort4->setPosition(Vec2(origin.x, origin.y + visibleSize.height / 4 + visibleSize.height / 16));
	laneEdgeNodeShort4->setPhysicsBody(laneEdgeBodyShort4);
	layer->addChild(laneEdgeNodeShort4, 6);
}