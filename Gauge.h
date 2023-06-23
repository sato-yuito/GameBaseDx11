#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Gauge : public GameObject
{

public:
    int hPictGauge_;    //�Q�[�W�̒��g
    int hPictFrame_;  //�t���[��

    int nowPw_, maxPw_, animPw_;
    //�R���X�g���N�^
    Gauge(GameObject* parent);

    //�f�X�g���N�^
    ~Gauge();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetPw(int nowPw, int maxPw)
    {
        nowPw_ = nowPw;
        maxPw_ = maxPw;
        animPw_ = (animPw_ * 8 + nowPw_) / 8;
    }
};
