#include "Gauge.h"
#include "Engine/Image.h"
//コンストラクタ
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"), hPictGauge_(-1), hPictFrame_(-1),
    maxPw_(100), nowPw_(0)
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

    hPictFrame_ = Image::Load("image (1).png");
    assert(hPictFrame_ >= 0);

    //2つの画像表示の場所
    transform_.position_.x = -0.95f;
    transform_.position_.y = 0.85f;
}

//更新
void Gauge::Update()
{
}

//描画
void Gauge::Draw()
{
    //ゲージの画像を描画
    Transform transGauge = transform_;
    transGauge.scale_.x =  (float)nowPw_/(float)maxPw_;//ゲージの大きさを変える
    Image::SetTransform(hPictGauge_, transGauge);
    Image::Draw(hPictGauge_);

    //フレームの画像描画
    Image::SetTransform(hPictFrame_, transform_);
    Image::Draw(hPictFrame_);

}

//開放
void Gauge::Release()
{
}