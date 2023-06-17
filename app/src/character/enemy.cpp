#include "enemy.h"
#include "glm/glm.hpp"

#include <iostream>

void Enemy::SetTarget(const std::shared_ptr<Character> target)
{
	m_Target = target;
}

HumanEnemy::HumanEnemy()
{
}

void HumanEnemy::Attack(float direction, float offset)
{
	if (GetPhyzicsEngine() == nullptr)
	{
		LOG(Error, "Runtime Error: Phyzics engine is not initialized!");
		return;
	}
	if (m_Weapon == nullptr)
	{
		LOG(Error, "Runtime Error: Weapon is not selected but trying to shoot!");
	}
	else
	{
		// Face to the enemy's direction when attacking
		if (1.0f < direction && direction < 2.0f)
			m_SpriteCoords.x = m_Sprite.Coords.x + 2;
		else if (-1.0f < direction && direction < 1.0f)
			m_SpriteCoords.x = m_Sprite.Coords.x + 3;
		else if (-2.0f < direction && direction < -1.0f)
			m_SpriteCoords.x = m_Sprite.Coords.x + 1;
		else if (direction < -2.0f && direction < 2.0f)
			m_SpriteCoords.x = m_Sprite.Coords.x;

		SetVelocity({ 0, 0, 0 });
		m_Weapon->Attack(direction, offset);
	}
}

void HumanEnemy::OnUpdate(float dt)
{
	m_Weapon->OnUpdate(dt);

	auto& body = GetPhyzicalBody();
	if (body->Collision.CollisionBody != nullptr)
	{
		const char* bodyName = (const char*)body->Collision.CollisionBody->InternalData;
		QUICK_LOG(Trace, "Hit by %s", bodyName);
		if (strcmp(bodyName, "rock") == 0)
		{
			auto& velo = GetVelocity();
			if (m_Behaviour == Behaviour::WalkUpDown)
				velo.y = -velo.y;
			else if (m_Behaviour == Behaviour::WalkLeftRight)
				velo.x = -velo.x;
			SetVelocity(velo);
			SetPosition(m_LastPosition);
			body->Collision.CollisionBody = nullptr;
		}
		else if (strcmp(bodyName, "bullet") == 0)
		{
			body->IsDead = true;
		}
		else
		{
			Move();
		}
	}
	else
	{
		m_LastPosition = GetPosition();
		Move();
	}

	glm::vec3 targetPos = m_Target->GetPosition();
	glm::vec2 targetSize = m_Target->GetSize();
	zeus::Rectangle targetArea(targetPos.x - targetSize.x / 2, targetPos.y - targetSize.y / 2, targetSize.x, targetSize.y);
	
	glm::vec3 pos = GetPosition();
	glm::vec2 size = GetSize();
	zeus::Rectangle area(pos.x - size.x / 2, pos.y, size.x, size.y);

	if (m_Velocity.x != 0 || m_Velocity.y != 0 || m_Velocity.z != 0)
		m_LastVelocity = m_Velocity;
	if (area.IsIntersectingWith(targetArea, 100))
	{
		float dir = atan2(targetPos.y - pos.y, targetPos.x - pos.x);
		Attack(dir, size.x);
	}
	else
	{
		SetVelocity(m_LastVelocity);
	}
}
