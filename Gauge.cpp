#include "Gauge.h"
#include "Engine/Image.h"
#include<assert.h>

//�R���X�g���N�^
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1),
     nowPw_(0)
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

    ImageWidth = 512;
    ImageHeight = 64;

    hPictFrame_ = Image::Load("image (1).png");
    assert(hPictFrame_ >= 0);

    //2�̉摜�\���̏ꏊ
   
}

//�X�V
void Gauge::Update()
{
}

//�`��
void Gauge::Draw()
{
    //�t���[���̉摜�`��
    Image::SetTransform(hPictFrame_, transform_);
    Image::Draw(hPictFrame_);

    //�Q�[�W�̉摜��`��
    int left = ImageWidth/2-ImageWidth/2*nowPw_;
    int width = ImageWidth * nowPw_;
    Image::SetRect(hPictGauge_, left, 0, width, ImageHeight);
    Image::SetTransform(hPictGauge_, transform_);
    Image::Draw(hPictGauge_);

}

//�J��
void Gauge::Release()
{
}

void Gauge::SetPosition(float x, float y)
{
    transform_.position_.x = x;
    transform_.position_.y = y;
}

void Gauge::AddValue(float v)
{
    nowPw_ += v;
    if (nowPw_ < 0.0f)
        nowPw_ = 0.0f;
    else if (nowPw_ > maxPw_)
        nowPw_ = maxPw_;
}

void Gauge::SetValue(float v)
{
    assert(v >= 0.0f && v <= 1.0f);
    nowPw_ = v;
    if (nowPw_ < 0.0f)
        nowPw_ = 0.0f;
    else if (nowPw_ > maxPw_)
        nowPw_ = maxPw_;
}

float Gauge::GetValue()
{
    return nowPw_;
}
