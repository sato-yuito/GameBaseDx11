#pragma once
#include "Engine/GameObject.h"

class Button : public GameObject {
public:
	Button(GameObject* parent);
	~Button();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	bool Finished(); // Buttonが終わったらtrue

	void SetImage(std::string normal, std::string pushed);//ボタン画像の指定
	void SetPosition(int x, int y);//ボタン表示位置
	void Push(bool pushed);//押したか押していないか
	bool MouseInArea(XMFLOAT3 mousePos);//マウスが範囲内かどうか
	
	/// <summary>
	/// ボタンの登場シーン
	/// </summary>
	/// <param name="Tox">移動後の座標X</param>
	/// <param name="Toy">移動後の座標Y</param>
	/// <param name="seconds">移動時間</param>
	void SetMovePosition(int Tox, int Toy, float seconds);
	
	/// <summary>
	/// 動いていないか動いたかの判定
	/// </summary>
	/// <returns></returns>
	bool IsMoving();
	
	/// <summary>
	///終わったらの処理
	/// </summary>
	void ForceEnd();

private:
	int hImage;//通常
	int hPush;//押された後の画像
	bool pushed;//押されたかどうかの判断
	
	XMFLOAT3 center;//中心座標
	XMFLOAT3 size;//画像の大きさ

	//ボタンの動きを作る
	XMFLOAT3 startPos;
	XMFLOAT3 endPos;
	float totalTime;
	float CurrentTime_;
};
