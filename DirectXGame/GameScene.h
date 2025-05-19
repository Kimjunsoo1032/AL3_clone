#pragma once
#include "KamataEngine.h"
#include "Player.h"
#include "Skydome.h"
#include <vector>
class GameScene {


	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Model* model_ = nullptr;
	KamataEngine::Model* modelPlayer_ = nullptr;
	KamataEngine::Model* modelBlock_ = nullptr;
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Camera camera_;

	// サウンドデータハンドル
	uint32_t soundDataHandle_ = 0;
	// サウンドデータハンドル
	uint32_t voiceHandle_ = 0;
	Player* player_ = nullptr;
	Skydome* skydome_ = nullptr;
	// std::vector<WorldTransform*> worldTransformBlocks_;
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;
	bool isDebugCameraActive_ = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	KamataEngine::Model* modelSkydome_ = nullptr;

public:
	~GameScene();
	void Initialize();
	void Update();
	void Draw();
};
