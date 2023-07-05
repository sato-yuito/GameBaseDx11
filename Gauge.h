#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Gauge : public GameObject
{

private:
    int hPictGauge_;    //�Q�[�W�̒��g
    int hPictFrame_;  //�t���[��
    float nowPw_;//���̒l
    const float maxPw_ = 1.0f;//�ő�l
    float animPw_;//�\���p�̒l
    int ImageWidth;
    int ImageHeight;

public:
    static constexpr float MIN = 0.0f;
    static constexpr float MAX = 1.0f;
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

    
    void SetPosition(float x, float y);

    /// <summary>
    /// �l�������Z����
    /// </summary>
    /// <param name="v"></param>
    void AddValue(float v);

    void SetValue(float v);

    float GetValue();
};
