#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Gauge : public GameObject
{

private:
    int hPictGauge_;    //ゲージの中身
    int hPictFrame_;  //フレーム
    float nowPw_;//今の値
    const float maxPw_ = 1.0f;//最大値
    float animPw_;//表示用の値
    int ImageWidth;
    int ImageHeight;

public:
    static constexpr float MIN = 0.0f;
    static constexpr float MAX = 1.0f;
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

    
    void SetPosition(float x, float y);

    /// <summary>
    /// 値を加減算する
    /// </summary>
    /// <param name="v"></param>
    void AddValue(float v);

    void SetValue(float v);

    float GetValue();
};
