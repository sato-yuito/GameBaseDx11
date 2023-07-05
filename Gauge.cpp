#include "Gauge.h"
#include "Engine/Image.h"
#include<assert.h>

//コンストラクタ
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1),
     nowPw_(0)
{
  
}

//デストラクタ
Gauge::~Gauge()
{
}

//初期化
void Gauge::Initialize()
{
    hPictGauge_ = Image::Load("image.png");
    assert(hPictGauge_ >= 0);

    ImageWidth = 512;
    ImageHeight = 64;

    hPictFrame_ = Image::Load("image (1).png");
    assert(hPictFrame_ >= 0);

    //2つの画像表示の場所
   
}

//更新
void Gauge::Update()
{
}

//描画
void Gauge::Draw()
{
    //フレームの画像描画
    Image::SetTransform(hPictFrame_, transform_);
    Image::Draw(hPictFrame_);

    //ゲージの画像を描画
    int left = ImageWidth/2-ImageWidth/2*nowPw_;
    int width = ImageWidth * nowPw_;
    Image::SetRect(hPictGauge_, left, 0, width, ImageHeight);
    Image::SetTransform(hPictGauge_, transform_);
    Image::Draw(hPictGauge_);

}

//開放
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
