#pragma once

#include "zeus.h"
#include "character/character.h"
#include "character/player.h"
#include "character/enemy.h"
#include "character/enemy_registry.h"
#include "level_manager.h"

#define WIDTH 1280
#define HEIGHT 768

const glm::vec4 RED		= { 1.0f, 0.0f, 0.0f, 1.0f };
const glm::vec4 BLUE	= { 0.0f, 0.0f, 1.0f, 1.0f };
const glm::vec4 GREEN	= { 0.0f, 1.0f, 0.0f, 1.0f };
const glm::vec4 GREY	= { 0.3f, 0.3f, 0.3f, 1.0f };
const glm::vec4 CYAN	= { 0.0f, 1.0f, 1.0f, 1.0f };

class GameLayer : public zeus::Layer
{
private:
	std::string m_Name;
	std::shared_ptr<zeus::Camera> m_Camera;
	std::shared_ptr<zeus::TextureManager> m_TexManager;
	std::shared_ptr<zeus::Phyzics> m_Phyzics;
	zeus::LevelManager m_LevelManager;

	std::vector<std::shared_ptr<Weapon>> m_Weapons;

	uint32_t m_CurrentLevel = 0;

	glm::vec2 m_MousePos{ 0, 0 };

	// coord - x, y, z
	// direction - w
	//    0 - look left
	//    1 - look backward
	//    2 - look forward
	//    3 - look right
	//glm::vec3 m_CharacterSprite;
	//glm::vec3 m_CharacterPos;

	std::shared_ptr<Character> m_Player;
	std::shared_ptr<EnemyRegistry> m_EnemyReg;

	bool m_Keys[65536] = { false };
	bool m_MouseKeys[3] = { false };

public:
	GameLayer(const char* layer_name);
	~GameLayer();

	void OnUpdate(float dt) override;
	void OnRender() override;
	void OnEvent(zeus::Event& evt) override;

	bool IsKeyPressed(uint32_t keycode);
	bool IsMousePressed(uint32_t keycode);
};
