#pragma once
#include "KamataEngine.h"
class Player {
	KamataEngine::Sprite* sprite_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;

public:
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera);
	void Update();
	void Draw();

private:
	KamataEngine::WorldTransform worldTransform_;
	KamataEngine::Model* model_ = nullptr;
};
