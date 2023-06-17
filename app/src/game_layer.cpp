#include "game_layer.h"

#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"
#include "game_level.h"

GameLayer::GameLayer(const char* layer_name)
{
	// Initializing Phyzics engine
	m_Phyzics = std::make_shared<zeus::Phyzics>();

	// Initializing Camera
	m_Camera = std::make_shared<zeus::Camera>();
	m_Camera->GetProperties().Position = { 32.0f, 32.0f, 0.0f };
	m_Camera->GetProperties().MovementSpeed = 85.0f;

	// Initializing Texture manager
	m_TexManager = zeus::TextureManager::GetInstance();
	m_TexManager->PutTexture({ "wood", "assets/textures/wood.png" });
	m_TexManager->PutSpritesheet({ "person_sheet", "assets/textures/spritesheets/tilemap_packed.png", 16, true });
	m_TexManager->PutSpritesheet({ "building_sheet", "assets/textures/spritesheets/mytilemap.png", 16, true });
	m_TexManager->PutSpritesheet({ "bullet_sheet", "assets/textures/spritesheets/explosion.png", 240, true });

	// Initializing Enemy registry
	m_EnemyReg = std::make_shared<EnemyRegistry>(m_TexManager);
	m_EnemyReg->SetPhyzicsEngine(m_Phyzics);

	// Initializing Main player
	m_Player = std::make_shared<Player>();
	m_Player->SetPhyzicsEngine(m_Phyzics);
	m_Player->SetTextureManager(m_TexManager);
	m_Player->SetPosition({ WIDTH / 2, HEIGHT / 2, 1.0f });

	Sprite PlayerSprite;
	PlayerSprite.Coords = { 24, 16, 2 };
	PlayerSprite.Size = { 32.0f, 32.0f, 0.0f };
	PlayerSprite.Name = "person_sheet";
	m_Player->SetSprite(PlayerSprite);

	m_Player->SetWeapon(WeaponType::Gun);
	m_EnemyReg->SetTarget(m_Player);

	// Initializing Level manager
	const auto& lvl1 = std::make_shared<BeginLevel>();
	lvl1->SetLevelSize(WIDTH, HEIGHT);
	lvl1->SetPhyzicsEngine(m_Phyzics);
	lvl1->SetEnemyRegistry(m_EnemyReg);
	lvl1->GetLevelResources().TexManager = m_TexManager;
	m_LevelManager.AddLevel(m_CurrentLevel, lvl1);

	// Initialize renderer
	zeus::ShaderData shaders;
	shaders.ConsiderAsFiles = true;
	shaders.QuadVertexShader = "assets/app_shaders/quad_vertex_shader.glsl";
	shaders.QuadFragmentShader = "assets/app_shaders/quad_fragment_shader.glsl";
	shaders.LineVertexShader = "assets/app_shaders/line_vertex_shader.glsl";
	shaders.LineFragmentShader = "assets/app_shaders/line_fragment_shader.glsl";
	zeus::Renderer::SetShaderData(shaders);

	zeus::Renderer::Init();
	zeus::Renderer::SetBackgroundColor(CYAN);
	zeus::Renderer::SetColorBlending(true);
	zeus::Renderer::SetDepthTest(true);
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnUpdate(float dt)
{
	// ImGui events
	auto ui = zeus::Application::GetInstance()->GetUI();
	if (ui->IsKeyPressed(KEY_LEFT_CONTROL))
	{
		if (ui->IsKeyPressed(KEY_Q))
		{
			zeus::Application::GetInstance()->Stop();
		}
	}

	// Application events
	if (IsKeyPressed(KEY_ESCAPE))
	{
		zeus::Application::GetInstance()->Stop();
	}
	if (IsKeyPressed(KEY_A))
		m_Player->Move({ -1.0, 0, 0 });
	if (IsKeyPressed(KEY_S))
		m_Player->Move({ 0, -1.0f, 0 });
	if (IsKeyPressed(KEY_D))
		m_Player->Move({ 1.0, 0, 0 });
	if (IsKeyPressed(KEY_W))
		m_Player->Move({ 0, 1.0f, 0 });
	if (IsMousePressed(MOUSE_LEFT))
	{
		const auto& playerPos = m_Player->GetPosition();
		float dir = std::atan2(((HEIGHT - m_MousePos.y) - playerPos.y), (m_MousePos.x - playerPos.x));
		m_Player->Attack(dir);
	}

	m_Player->OnUpdate(dt);
	m_EnemyReg->OnUpdate(dt);
	m_Player->OnUpdate(dt);
}

void GameLayer::OnRender()
{
	zeus::Renderer::Start(m_Camera);

	m_LevelManager.SetActiveLevel(m_CurrentLevel);
	m_LevelManager.Draw();

	m_EnemyReg->OnRender();
	m_Player->OnRender();

	auto& cam = m_Camera->GetProperties();
	ImGui::Begin("info");
	{
		ImGuiIO& io = ImGui::GetIO();
		if (ImGui::IsWindowFocused())
		{
			io.WantCaptureKeyboard = true;
			io.WantCaptureMouse = true;
		}

		ImGui::DragFloat3("camera position", glm::value_ptr(cam.Position));
		ImGui::DragFloat3("character position", glm::value_ptr(m_Player->GetPosition()), 0.1f);

		ImGui::Text("Framerate: %f", io.Framerate);

		ImGui::Text("Enemies count: %d", m_EnemyReg->GetEnemies().size());
		const auto& phyzStat = m_Phyzics->GetStatistics();
		ImGui::Text("Physical bodies: %d", phyzStat.Bodies);

		ImGui::End();
	}

	zeus::Renderer::Flush(m_TexManager);
}

void GameLayer::OnEvent(zeus::Event& evt)
{
	zeus::EventDispatcher dispatcher(evt);

	std::function<bool()> keyPressed = [&]() -> bool {
		auto keyEvent = (zeus::KeyPressedEvent&)evt;
		int keyCode = keyEvent.GetKeycode();
		m_Keys[keyCode] = true;
		return true;
	};

	std::function<bool()> keyReleased = [&]() -> bool {
		auto keyEvent = (zeus::KeyReleasedEvent&)evt;
		int keyCode = keyEvent.GetKeycode();
		m_Keys[keyCode] = false;
		return true;
	};

	std::function<bool()> mousePressed = [&]() -> bool {
		auto mouseEvent = (zeus::MousePressedEvent&)evt;
		int button = mouseEvent.GetMouseButton();
		m_MouseKeys[button] = true;

		return true;
	};

	std::function<bool()> mouseReleased = [&]() -> bool {
		auto mouseEvent = (zeus::MouseReleasedEvent&)evt;
		int button = mouseEvent.GetMouseButton();
		m_MouseKeys[button] = false;

		return true;
	};

	std::function<bool()> mouseMoved = [&]() -> bool {
		auto mouseEvent = (zeus::MouseMovedEvent&)evt;
		m_MousePos = mouseEvent.GetMousePosition();
		return true;
	};

	dispatcher.Dispatch(zeus::EventType::MouseMoved, mouseMoved);
	dispatcher.Dispatch(zeus::EventType::MousePressed, mousePressed);
	dispatcher.Dispatch(zeus::EventType::MouseReleased, mouseReleased);
	dispatcher.Dispatch(zeus::EventType::KeyPressed, keyPressed);
	dispatcher.Dispatch(zeus::EventType::KeyReleased, keyReleased);
}

bool GameLayer::IsKeyPressed(uint32_t keycode)
{
	return m_Keys[keycode];
}

bool GameLayer::IsMousePressed(uint32_t keycode)
{
	return m_MouseKeys[keycode];
}
