#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Gauge : public GameObject
{

public:
    int hPictGauge_;    //ゲージの中身
    int hPictFrame_;  //フレーム

    int nowPw_, maxPw_, animPw_;
    //コンストラクタ
    Gauge(GameObject* parent);

    //デストラクタ
    ~Gauge();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetPw(int nowPw, int maxPw)
    {
        nowPw_ = nowPw;
        maxPw_ = maxPw;
        animPw_ = (animPw_ * 8 + nowPw_) / 8;
    }
};
