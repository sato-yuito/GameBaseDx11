#include "Player.h"
#include"Engine/Input.h"
#include"ball.h"
#include"Engine/Model.h"
#include"Gauge.h"
#include"StartScene.h"
/*
*マウスで←クリックをしたらゲージが出て球の強さを調整する
* ゲージ調整が強いほど強烈な球が打てる
*/

//こじんてきにやりたかったこと
//ゲージをためる音の追加
//一気に貯めるのではなく階段状のゲージにしたらよかったかも知れないもっとゲームみたいになると思う。
// あと別のキーでゲージを下げる処理をやってよかったかもしれない。そっちのほうが操作性がいいと思う
//球を打ったらゲージがリセットされる処理も追加できたかも.....

namespace {
	static const float Move_ROT = 90.0f;
	const float GAUGE_TIME = 0.5f;//
}
Player::Player(GameObject* parent)
{
	direction = 0.0f;
	power = 0.2f;
	//maxPw_ = 100;
	nowPw_ = 0;
	//MaxPower = nowPw_ +power;
	//difPower = nowPw_ - power;
	hModel = Model::Load("DebugCollision/SphereCollider.fbx");
	transform_.scale_ = XMFLOAT3(0.2f, 0.2f, 0.2f);
}

Player::~Player()
{

}

void Player::Update()
{
	StartScene* pStartScene = FindGameObject<StartScene>();
	if(pStartScene!=nullptr&&!pStartScene->Finished())
	if (Input::IsKey(DIK_W))
	{
		Gauge* pGauge = (Gauge*)FindObject("Gauge");
		if (strengthentheball)
		{
			pGauge->AddValue(Gauge::MAX/GAUGE_TIME/60.0f);
			if (pGauge->GetValue() >= Gauge::MIN)
			{
				strengthentheball = false;
			}
			
		}
		else
		{
			pGauge->AddValue(Gauge::MAX / GAUGE_TIME / 60.0f);
			if (pGauge->GetValue() <= Gauge::MAX)
			{
				strengthentheball = true;
			}
		}
		
	}
	
	
	
	if (Input::IsKey(DIK_A))
		direction -= XMConvertToRadians(Move_ROT) / 60.0f;
	if (Input::IsKey(DIK_D))
		direction += XMConvertToRadians(Move_ROT) / 60.0f;
   
	 if(Input::IsKey(DIK_SPACE))
	{
		
		XMVECTOR base = XMVectorSet(0, 0, power*(nowPw_/static_cast<float>(20)), 0);//回転していないときに移動するベクトル
		XMMATRIX yrot = XMMatrixRotationY(direction);//回転行列の作成
		XMVECTOR v = XMVector3Transform(base, yrot);//その回転でベクトルの向きを変える
		myBall->AddForce(v);//回転後の移動ベクトル
	}
	
	

	
	//pGauge->SetPw(nowPw_, maxPw_);
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