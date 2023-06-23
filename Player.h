#pragma once
#include"Engine/GameObject.h"
class ball;

class Player :public GameObject
{
private:
	int hModel;
	ball* myBall;
	float direction;//向き(Y回転のラジアン:ラジアン)
	float power;
	int nowPw_, maxPw_;
	float MaxPower;
	float difPower;
public:
	Player(GameObject* parent);
	~Player();
	void Update();
	void Draw();

	void SetMyBall(ball* Ball)
	{
		myBall = Ball;
	}
};

