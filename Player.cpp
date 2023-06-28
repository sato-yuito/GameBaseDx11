#include "Player.h"
#include"Engine/Input.h"
#include"ball.h"
#include"Engine/Model.h"
#include"Gauge.h"
/*
*�}�E�X�Ł��N���b�N��������Q�[�W���o�ċ��̋����𒲐�����
* �Q�[�W�����������قǋ���ȋ����łĂ�
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
		
		XMVECTOR base = XMVectorSet(0, 0, power*(nowPw_/static_cast<float>(20)), 0);//��]���Ă��Ȃ��Ƃ��Ɉړ�����x�N�g��
		XMMATRIX yrot = XMMatrixRotationY(direction);//��]�s��̍쐬
		XMVECTOR v = XMVector3Transform(base, yrot);//���̉�]�Ńx�N�g���̌�����ς���
		myBall->AddForce(v);//��]��̈ړ��x�N�g��
	}
	
	

	Gauge* pGauge = (Gauge*)FindObject("Gauge");
	pGauge->SetPw(nowPw_, maxPw_);
}

void Player::Draw()
{
	//transform_.position_��ݒ�
	//�����������_�ɂ���Ƃ��āA�������̂ǂ��ɕ\�����邩�����߂�
	//�����ɔ������̍��W�𑫂�
	//�\�����W�����܂�̂ŁAtransform_.position_�ɑ������
	XMVECTOR base = XMVectorSet(0, 0, 1.2f, 0);
	XMMATRIX yrot = XMMatrixRotationY(direction);
	XMVECTOR v = XMVector3Transform(base, yrot);
	transform_.position_ = myBall->GetPosition()+v;

	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}