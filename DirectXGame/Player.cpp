#include "Player.h"

using namespace KamataEngine;

void Player::Initialize(Model* model, Camera* camera) {
	// メンバ変数への代入処理(省略)
	// ここにインゲームの初期化処理を書く
	assert(model);
	model_ = model;
	camera_ = camera;
	worldTransform_.Initialize();
	// camera_ = camera;
}
void Player::Update() {
	// ここにインゲームの更新処理を書く
	worldTransform_.TransferMatrix();
}
void Player::Draw() { model_->Draw(worldTransform_, *camera_); }