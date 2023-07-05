#include "StartScene.h"
#include"Engine/Image.h"
#include<vector>

namespace
{
	float startX;//移動開始
	float endX;//移動終了
	float totalTime;//移動時間(秒）
	float currentTime;//現在の時間

	int seq_line;//実行している行
	float seq_time;//実行時間
	enum ACT
	{
		A_SLIDEIN = 1,
		A_WAIT,
		A_SLIDOUT,
		A_END
	};
	struct Sequence
	{
		float time;//時間
		int action;
		float param;
	};
	std::vector<Sequence> tbl
	{
		{0.0f,A_SLIDEIN,5.0f},//スライドイン
		{3.0f,A_WAIT,0.0f},//少し待つ
		{4.0f,A_SLIDOUT,-5.0f},//スライドアウト
		{5.0f,A_END,0.0f}//終わったら消える
	};
	ACT currentAction;//今実行しているアクション
	bool CanMove;
}
StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene"), hPict_(-1)
{
	seq_line = -1;
	seq_time = 0.0f;
	CanMove = false;
}

void StartScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Ready.png");
	assert(hPict_ >= 0);
	startX = 5.0f;
	endX = 0;
	totalTime = 3.0f;
	currentTime = 0.0f;
	
}
float easeInCubic(float x)
{
	return x * x * x;
}
void StartScene::Update()
{
	seq_time += 1.0f / 60.0f;
	if (seq_time >= tbl[seq_line + 1].time)
	{
		seq_line++;
		switch (tbl[seq_line].action)
		{
		case A_END:
			KillMe();
			break;
		case A_SLIDEIN:
			startX = tbl[seq_line].param;
			endX = 0;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		case A_WAIT:
			startX = transform_.position_.x;
			endX = transform_.position_.x;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		case A_SLIDOUT:
			CanMove = true;
			startX = transform_.position_.x;
			endX = tbl[seq_line].param;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		}
	}
	currentTime += 1.0f / 60.0f;//一フレームの時間を進ませる処理
	if (currentTime > totalTime)
		currentTime = totalTime;
	float t = currentTime/totalTime; //ここを0.0～1.0の範囲にする
	float val = easeInCubic(t);//いーじんぐ関数を呼ぶ(t)
	transform_.position_.x = val * (endX - startX) + startX;
	
}

void StartScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void StartScene::Release()
{
}

bool StartScene::Finished()
{
	if (CanMove)
		return true;
	return false;
}
