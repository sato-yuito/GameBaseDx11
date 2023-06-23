#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class ball : public GameObject
{
private:
    int hModel;
    int number;//ボールの番号を指定。白玉は0
    XMVECTOR velocity;
public:
    //コンストラクタ
    ball(GameObject* parent);

    //デストラクタ
    ~ball();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //ボール番号(1~9)を指定
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

