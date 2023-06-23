#include "ball.h"
#include"Engine/Model.h"
#include"Engine/Input.h"
#include<assert.h>
//�R���X�g���N�^
ball::ball(GameObject* parent)
    :GameObject(parent, "ball"),hModel(-1)
{
    velocity = XMVectorSet(0,0,0,0);
}

//�f�X�g���N�^
ball::~ball()
{
    if (hModel > 0);
    Model::Release(hModel);
}

//������
void ball::Initialize()
{
}

//�X�V
void ball::Update()
{

    //velocity�̒���len�����߂�
    //len����0.001���炷(0�ɂȂ�����0�ɂ���)
    //velocity�̒�����len�ɂ���
    XMVECTOR lenVec = XMVector3Length(velocity);
    float len = XMVectorGetX(lenVec);
    len -= 0.001f;
    if (len < 0.0f)len = 0.0f;
    velocity = XMVector3Normalize(velocity) * len;
   
    //�{�[�����m�Ŕ��˂�����
    std::list<ball*> all =GetParent()->FindGameObjects<ball>();
    for (std::list<ball*>::iterator itr = all.begin(); itr != all.end(); itr++)
    {
        if (*itr == this)continue;
        XMFLOAT3 next = transform_.position_ + velocity;
        XMFLOAT3 other = (*itr)->GetNextPosition();
        //�{�[�����m�Ԃ������Ƃ��̓��ς����߂�if��
        if (Length(next-other) < 1.0f*2.0f)
        {
            XMVECTOR normal = other - next;
            normal = XMVector3Normalize(normal);//normal�̒�����1�Ƃ��čl����
            XMVECTOR powDot = XMVector3Dot(velocity, normal);
            float pw = XMVectorGetX(powDot);
            //����vector�����߂đ���ɓn������
            XMVECTOR push = normal * pw;
            velocity -= push;
            (*itr)->AddForce(push);//Addforce�ɓn���Ă��

            normal = other - next;
            normal = XMVector3Normalize(normal);
            powDot = XMVector3Dot((*itr)->GetVelocity(), normal);
            pw = XMVectorGetX(powDot);
            push = normal * pw;
            (*itr)->AddForce(-push);
            AddForce(push);
        }
        
    }
    //�ǂɔ��˂�����
    XMFLOAT3 next = transform_.position_ + velocity;
    if (next.x >= 20.0f)
    {
        XMVECTOR n = XMVectorSet(-1, 0, 0, 0);//�E�̒����̖@����1
        n = n * -1;//�t�����ɂ��� = �ǂɌ������x�N�g��
        XMVECTOR ipvec = XMVector3Dot(velocity, n);
        float ip = XMVectorGetX(ipvec);//�ǂ������͂̑傫��
        XMVECTOR push = n * ip;//�ǂ������x�N�g��
        XMVECTOR th = velocity - push;//�ǂɉ����Ă�x�N�g��
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

//�`��
void ball::Draw()
{
    if (hModel < 0)
        return;
    Model::SetTransform(hModel, transform_);
    Model::Draw(hModel);
}

//�J��
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
