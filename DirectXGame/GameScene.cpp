#include "GameScene.h"
#include "MyMath.h"
using namespace KamataEngine;

// GameScene::~GameScene() { delete sprite_; }
GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	// for (WorldTransform* worldTransformBlock : worldTransformBlocks_) {
	//	delete worldTransformBlock;
	// }
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
	delete modelSkydome_;
	delete mapChipField_;
}

void GameScene::Initialize() {
	// メンバ変数への代入処理(省略)
	// ここにインゲームの初期化処理を書く

	model_ = Model::Create();
	modelPlayer_ = Model::CreateFromOBJ("player");
	modelBlock_ = Model::CreateFromOBJ("block");
	worldTransform_.Initialize();
	camera_.Initialize();
	// サウンドでーたの読み込み
	soundDataHandle_ = Audio::GetInstance()->LoadWave("fanfare.wav");
	// 音楽再生
	Audio::GetInstance()->PlayWave(soundDataHandle_);
	// サウンドでーたの読み込み
	voiceHandle_ = Audio::GetInstance()->PlayWave(soundDataHandle_, true);
	player_ = new Player();
	player_->Initialize(modelPlayer_, &camera_);
	//
	//
	//const uint32_t kNumBlockVirtical = 10;
	//const uint32_t kNumBlockHorizontal = 20;

	//const float kBlockWidth = 2.0f;
	//const float kBlockHeight = 2.0f;

	// worldTransformBlocks_.resize(kNumBlockVirtical);
	// for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
	//	worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	// }
	// for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
	//	for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
	//		if ((i + j) % 2 == 0)
	//			continue;
	//		worldTransformBlocks_[i][j] = new WorldTransform();
	//		worldTransformBlocks_[i][j]->Initialize();
	//		worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
	//		worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
	//		//}
	//	}
	// }
	debugCamera_ = new DebugCamera(1280, 720);

	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, &camera_);
	mapChipField_ = new MapChipField;
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	GenerateBlocks();
}

void GameScene::Update() {
	// ここにインゲームの更新処理を書く

	// 移動した座標をスプライトに反映
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		Audio::GetInstance()->StopWave(voiceHandle_);
	}
	player_->Update();
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}
			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);
			worldTransformBlock->TransferMatrix();
		}
	}
	debugCamera_->Update();

#ifdef _DEBUG
	if (Input::GetInstance()->TriggerKey(DIK_A)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}
#endif
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;
		camera_.TransferMatrix();
	} else {
		camera_.UpdateMatrix();
	}
}
void GameScene::Draw() {
	// DirectXcommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Model::PreDraw(dxCommon->GetCommandList());
	// ここに3Dモデルインスタンスの描画処理を記述する
	player_->Draw();
	skydome_->Draw();
	for (std::vector<WorldTransform*> worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			modelBlock_->Draw(*worldTransformBlock, camera_);
		}
	}
	Model::PostDraw();
}
void GameScene::GenerateBlocks() {

	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	worldTransformBlocks_.resize(numBlockVirtical);
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}

}