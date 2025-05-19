#include "Skydome.h"
using namespace KamataEngine;

void Skydome::Initialize(Model* model, uint32_t textureHandle, Camera* camera) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;
	worldTransform_.Initialize();
}
void Skydome::Update() {
	// ここにインゲームの更新処理を書く
	worldTransform_.TransferMatrix();
}
void Skydome::Draw() { model_->Draw(worldTransform_, *camera_); };