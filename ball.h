#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class ball : public GameObject
{
private:
    int hModel;
    int number;//�{�[���̔ԍ����w��B���ʂ�0
    XMVECTOR velocity;
public:
    //�R���X�g���N�^
    ball(GameObject* parent);

    //�f�X�g���N�^
    ~ball();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�{�[���ԍ�(1~9)���w��
    void SetNumber(int no);

    void AddForce(XMVECTOR f);

    XMFLOAT3 GetNextPosition()
    {
        return GetPosition() + velocity;
    }

    XMVECTOR GetVelocity()
    {
        return velocity;
    }
};

