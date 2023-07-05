#include "StartScene.h"
#include"Engine/Image.h"
#include<vector>

namespace
{
	float startX;//�ړ��J�n
	float endX;//�ړ��I��
	float totalTime;//�ړ�����(�b�j
	float currentTime;//���݂̎���

	int seq_line;//���s���Ă���s
	float seq_time;//���s����
	enum ACT
	{
		A_SLIDEIN = 1,
		A_WAIT,
		A_SLIDOUT,
		A_END
	};
	struct Sequence
	{
		float time;//����
		int action;
		float param;
	};
	std::vector<Sequence> tbl
	{
		{0.0f,A_SLIDEIN,5.0f},//�X���C�h�C��
		{3.0f,A_WAIT,0.0f},//�����҂�
		{4.0f,A_SLIDOUT,-5.0f},//�X���C�h�A�E�g
		{5.0f,A_END,0.0f}//�I������������
	};
	ACT currentAction;//�����s���Ă���A�N�V����
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
	//�摜�f�[�^�̃��[�h
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
	currentTime += 1.0f / 60.0f;//��t���[���̎��Ԃ�i�܂��鏈��
	if (currentTime > totalTime)
		currentTime = totalTime;
	float t = currentTime/totalTime; //������0.0�`1.0�͈̔͂ɂ���
	float val = easeInCubic(t);//���[���񂮊֐����Ă�(t)
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
