#include "Player.h"
#include"Engine/Input.h"
#include"ball.h"
#include"Engine/Model.h"
#include"Gauge.h"
/*
*マウスで←クリックをしたらゲージが出て球の強さを調整する
* ゲージ調整が強いほど強烈な球が打てる
*/
Player::Player(GameObject* parent)
{
	direction = 0.0f;
	power = 0.2f;
	maxPw_ = 100;
	nowPw_ = 0;
	MaxPower = nowPw_ +power;
	difPower = nowPw_ - power;
	hModel = Model::Load("DebugCollision/SphereCollider.fbx");
	transform_.scale_ = XMFLOAT3(0.2f, 0.2f, 0.2f);
}

Player::~Player()
{

}

void Player::Update()
{
	if (Input::IsKey(DIK_W))
	{
		if (strengthentheball)
		{
			nowPw_ += 2.0f;
			if (nowPw_ > maxPw_)
			{
				nowPw_ = maxPw_;
				strengthentheball = false;
			}
			else
			{
				nowPw_ -= 2.0f;
				if (nowPw_ < 0.0f)
				{
					nowPw_ = 0.0f;
					strengthentheball = true;
				}
			}
		}
		
	}
	
	
	
	if (Input::IsKey(DIK_A))
		direction -= 0.01f;
	if (Input::IsKey(DIK_D))
		direction += 0.01f;
   
	 if(Input::IsKey(DIK_SPACE))
	{
		
		XMVECTOR base = XMVectorSet(0, 0, power*(nowPw_/static_cast<float>(20)), 0);//回転していないときに移動するベクトル
		XMMATRIX yrot = XMMatrixRotationY(direction);//回転行列の作成
		XMVECTOR v = XMVector3Transform(base, yrot);//その回転でベクトルの向きを変える
		myBall->AddForce(v);//回転後の移動ベクトル
	}
	
	

	Gauge* pGauge = (Gauge*)FindObject("Gauge");
	pGauge->SetPw(nowPw_, maxPw_);
}

void Player::Draw()
{
	//transform_.position_を設定
	//白い球が原点にあるとして、白い球のどこに表示するかを求める
	//そこに白い球の座標を足す
	//表示座標が求まるので、transform_.position_に代入する
	XMVECTOR base = XMVectorSet(0, 0, 1.2f, 0);
	XMMATRIX yrot = XMMatrixRotationY(direction);
	XMVECTOR v = XMVector3Transform(base, yrot);
	transform_.position_ = myBall->GetPosition()+v;

	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}