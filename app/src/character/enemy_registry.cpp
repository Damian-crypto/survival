#include "enemy_registry.h"

#include <cstring>

EnemyRegistry::EnemyRegistry(std::shared_ptr<zeus::TextureManager> texManager)
{
	m_TexManager = texManager;
}

std::shared_ptr<Enemy> EnemyRegistry::CreateEnemy(EnemyType type)
{
	if (m_TexManager == nullptr)
	{
		LOG(Error, "Runtime Error: Texture manager is not initialized for operation!");
	}

	if (m_Phyzics == nullptr)
	{
		LOG(Error, "Runtime Error: Phyzics engine is not initialized for calculations!");
	}

	switch (type)
	{
		case EnemyType::Human:
		{
			std::shared_ptr<Enemy> enemy = std::make_shared<HumanEnemy>();
			enemy->SetTextureManager(m_TexManager);
			enemy->SetPosition({ 500.0f, 300.0f, 0.09f });

			Sprite HumanSprite;
			HumanSprite.Coords = { 24, 13, 2 };
			HumanSprite.Size = { 32, 32, 0 };
			HumanSprite.Name = "person_sheet";
			enemy->SetSprite(HumanSprite);

			enemy->SetWeapon(WeaponType::Gun);
			m_Enemies.push_back(enemy);

			enemy->SetPhyzicsEngine(m_Phyzics);
			return enemy;
		}
	}

	LOG(Error, "Runtime Error: You specified invalid enemy type!");

	return nullptr;
}

void EnemyRegistry::OnUpdate(float dt)
{
	for (size_t i = 0; i < m_Enemies.size(); i++)
	{
		const auto& enemy = m_Enemies[i];
		if (enemy->GetPhyzicalBody()->IsDead)
		{
			m_Enemies.erase(m_Enemies.begin() + i);
		}
		else
		{
			enemy->SetTarget(m_Target);
			enemy->GetPhyzicalBody()->Position = enemy->GetPosition();
			enemy->OnUpdate(dt);
		}
	}
}

void EnemyRegistry::OnRender()
{
	for (auto& enemy : m_Enemies)
	{
		enemy->OnRender();
	}
}

void EnemyRegistry::SetTarget(std::shared_ptr<Character> target)
{
	m_Target = target;
}
