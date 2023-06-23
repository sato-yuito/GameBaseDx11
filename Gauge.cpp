#include "Gauge.h"
#include "Engine/Image.h"
//�R���X�g���N�^
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1),
    maxPw_(100), nowPw_(0)
{
}

//�f�X�g���N�^
Gauge::~Gauge()
{
}

//������
void Gauge::Initialize()
{
    hPictGauge_ = Image::Load("image.png");
    assert(hPictGauge_ >= 0);

    hPictFrame_ = Image::Load("image (1).png");
    assert(hPictFrame_ >= 0);

    //2�̉摜�\���̏ꏊ
    transform_.position_.x = -0.95f;
    transform_.position_.y = 0.85f;
}

//�X�V
void Gauge::Update()
{
}

//�`��
void Gauge::Draw()
{
    //�Q�[�W�̉摜��`��
    Transform transGauge = transform_;
    transGauge.scale_.x =  (float)nowPw_/(float)maxPw_;//�Q�[�W�̑傫����ς���
    Image::SetTransform(hPictGauge_, transGauge);
    Image::Draw(hPictGauge_);

    //�t���[���̉摜�`��
    Image::SetTransform(hPictFrame_, transform_);
    Image::Draw(hPictFrame_);

}

//�J��
void Gauge::Release()
{
}