#include "Button.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"

namespace {
	float startX; // 移動開始X座標
	float endX;   // 移動終了X座標
	float totalTime; // 移動時間（秒）
	float currentTime; // 現在の時間

	int seq_line; // 今実行している行
	float seq_time; // シーケンスを実行している時間
	enum ACT { // やることをコマンド化
		A_SLIDEIN = 1,
		A_WAIT,
		A_SLIDEOUT,
		A_END
	};
	struct Sequence {
		float time; // 時間
		ACT action; // やること
		float param; // 必要な値
	};
	Sequence tbl[] = {

		{ 0.0f, A_SLIDEIN, 5.0f }, // まずはスライドイン
		{ 3.0f, A_WAIT, 0.0f/*意味なし*/}, // 1秒待ってから
		{ 4.0f, A_SLIDEOUT, -5.0f }, // スライドアウト
		{ 5.0f, A_END, 0.0f} // ここで消える
	};
	ACT currentAction; // 今実行しているアクション
	bool canMove; // 移動できる
};

Button::Button(GameObject* parent)
{
	seq_line = -1;
	seq_time = 0.0f;
	canMove = false;
	CurrentTime_ = 0.0f;
}

Button::~Button()
{
}

void Button::Initialize()
{
	pushed = false;
	hImage = -1;
	transform_.position_.x = 0.0f;
	transform_.position_.y = 0.0f;
}

void Button::Update()
{
	CurrentTime_ += 1.0f / 60.0f;
	if (CurrentTime_ >= totalTime)
	{
		SetPosition(endPos.x, endPos.y);
	}
	else
	{
		float x = (endPos.x - startPos.x) * (CurrentTime_ / totalTime) + startPos.x;
		float y= (endPos.y - startPos.y) * (CurrentTime_ / totalTime) + startPos.y;
		SetPosition(x, y);
	}
}

void Button::Draw()
{

	if (pushed) {
		Image::SetTransform(hPush, transform_);
		Image::Draw(hPush);
	}
	else {
		Image::SetTransform(hImage, transform_);
		Image::Draw(hImage);
	}
}

bool Button::Finished()
{
	return canMove;
}

void Button::SetImage(std::string normal, std::string pushed)
{
	hImage = Image::Load((normal + ".png").c_str());
	hPush = Image::Load((pushed + ".png").c_str());
	size = Image::GetSize(hImage);
}

void Button::SetPosition(int x, int y)
{
	transform_.position_.x = (float)(x - Direct3D::screenWidth_ / 2) / Direct3D::screenWidth_;
	transform_.position_.y = -(float)(y - Direct3D::screenHeight_ / 2) / (Direct3D::screenHeight_ / 2);
	center = XMFLOAT3(x, y, 0);
}

void Button::Push(bool pushed)
{
	this->pushed = pushed;
}

bool Button::MouseInArea(XMFLOAT3 mousePos)
{
	if (abs(mousePos.x - center.x) > size.x / 2)
		return false;
	if (abs(mousePos.y - center.y) > size.y / 2)
		return false;
	return true;
}

void Button::SetMovePosition(int Tox, int Toy, float seconds)
{
	startPos = center;
	endPos = XMFLOAT3((float)Tox, (float)Toy, 0);
	totalTime = seconds;
	CurrentTime_ = 0.0f;
}

bool Button::IsMoving()
{
	return(CurrentTime_ < totalTime);
}

void Button::ForceEnd()
{
	if (IsMoving())
	{
		SetPosition(endPos.x, endPos.y);
		CurrentTime_ = totalTime;
	}
}
