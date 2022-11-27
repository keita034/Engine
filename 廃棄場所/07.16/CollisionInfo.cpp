#include "CollisionInfo.h"

CollisionInfo::CollisionInfo(ModelInterface* object, BaseCollider* collider, const AliceMath::Vector4& inter)
{
	this->object = object;
	this->collider = collider;
	this->inter = inter;
}