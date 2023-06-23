#include "ball.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
#include<assert.h>
//コンストラクタ
ball::ball(GameObject* parent)
    :GameObject(parent, "ball"),hModel(-1)
{
    velocity = XMVectorSet(0,0,0,0);
}

//デストラクタ
ball::~ball()
{
    if (hModel > 0);
    Model::Release(hModel);
}

//初期化
void ball::Initialize()
{
}

//更新
void ball::Update()
{

    //velocityの長さlenを求める
    //lenから0.001減らす(0になったら0にする)
    //velocityの長さをlenにする
    XMVECTOR lenVec = XMVector3Length(velocity);
    float len = XMVectorGetX(lenVec);
    len -= 0.001f;
    if (len < 0.0f)len = 0.0f;
    velocity = XMVector3Normalize(velocity) * len;
   
    //ボール同士で反射させる
    std::list<ball*> all =GetParent()->FindGameObjects<ball>();
    for (std::list<ball*>::iterator itr = all.begin(); itr != all.end(); itr++)
    {
        if (*itr == this)continue;
        XMFLOAT3 next = transform_.position_ + velocity;
        XMFLOAT3 other = (*itr)->GetNextPosition();
        //ボール同士ぶつかったときの内積を求めるif文
        if (Length(next-other) < 1.0f*2.0f)
        {
            XMVECTOR normal = other - next;
            normal = XMVector3Normalize(normal);//normalの長さを1として考える
            XMVECTOR powDot = XMVector3Dot(velocity, normal);
            float pw = XMVectorGetX(powDot);
            //押すvectorを求めて相手に渡した力
            XMVECTOR push = normal * pw;
            velocity -= push;
            (*itr)->AddForce(push);//Addforceに渡してやる

            normal = other - next;
            normal = XMVector3Normalize(normal);
            powDot = XMVector3Dot((*itr)->GetVelocity(), normal);
            pw = XMVectorGetX(powDot);
            push = normal * pw;
            (*itr)->AddForce(-push);
            AddForce(push);
        }
        
    }
    //壁に反射させる
    XMFLOAT3 next = transform_.position_ + velocity;
    if (next.x >= 20.0f)
    {
        XMVECTOR n = XMVectorSet(-1, 0, 0, 0);//右の長さの法線が1
        n = n * -1;//逆向きにする = 壁に向かうベクトル
        XMVECTOR ipvec = XMVector3Dot(velocity, n);
        float ip = XMVectorGetX(ipvec);//壁を押す力の大きさ
        XMVECTOR push = n * ip;//壁を押すベクトル
        XMVECTOR th = velocity - push;//壁に沿ってるベクトル
        push *= -1;
        velocity = push + th;
        /*XMFLOAT3 f;
        XMStoreFloat3(&f, velocity);
        f.x = -f.x;
        velocity = XMLoadFloat3(&f);*/
    }
    if (next.x <= -20.0f)
    {
        XMFLOAT3 f;
        XMStoreFloat3(&f, velocity);
        f.x = -f.x;
        velocity = XMLoadFloat3(&f);
    }

    if (next.z>= 20.0f)
    {
        XMFLOAT3 f;
        XMStoreFloat3(&f, velocity);
        f.z = -f.z;
        velocity = XMLoadFloat3(&f);
    }
    if (next.z <= -20.0f)
    {
        XMFLOAT3 f;
        XMStoreFloat3(&f, velocity);
        f.z = -f.z;
        velocity = XMLoadFloat3(&f);
    }
    transform_.position_ += velocity;
}

//描画
void ball::Draw()
{
    if (hModel < 0)
        return;
    Model::SetTransform(hModel, transform_);
    Model::Draw(hModel);
}

//開放
void ball::Release()
{
}

void ball::SetNumber(int no)
{
    number = no;
    hModel = Model::Load("no"+std::to_string(no)+".fbx");

    assert(hModel >= 0);
}

void ball::AddForce(XMVECTOR f)
{
    velocity += f;
}
