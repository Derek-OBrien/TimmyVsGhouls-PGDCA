
#include "CollisionCheck.h"
#include "GameDefines.h"

CollisionCheck::CollisionCheck(){}


bool CollisionCheck::checkForCollision(PhysicsContact &contact, Layer* layer, Hud* hud){
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	bool m_Collided = false;

	if ((PLAYER_BITMASK == a->getCollisionBitmask() && LANE_BITMASK == b->getCollisionBitmask()) || (PLAYER_BITMASK == b->getCollisionBitmask() && LANE_BITMASK == a->getCollisionBitmask())){

		m_Collided = true;
	}

	if ((ENEMY_BITMASK == a->getCollisionBitmask() && PROJECTILE_BITMASK == b->getCollisionBitmask() )
		|| (ENEMY_BITMASK == b->getCollisionBitmask() && PROJECTILE_BITMASK == a->getCollisionBitmask())){
		//Get game object node
		auto nodeA = contact.getShapeA()->getBody()->getNode();
		auto nodeB = contact.getShapeB()->getBody()->getNode();

		if (nodeA && nodeB){

			nodeB->removeFromParentAndCleanup(true);
			nodeA->removeFromParentAndCleanup(true);

			m_Collided = true;
			hud->updateAmount(10);
		}

		return m_Collided;
	}


	return m_Collided;
}
