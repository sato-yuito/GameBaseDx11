#pragma once
#include "Engine/GameObject.h"

class Button : public GameObject {
public:
	Button(GameObject* parent);
	~Button();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	bool Finished(); // Button���I�������true

	void SetImage(std::string normal, std::string pushed);//�{�^���摜�̎w��
	void SetPosition(int x, int y);//�{�^���\���ʒu
	void Push(bool pushed);//�������������Ă��Ȃ���
	bool MouseInArea(XMFLOAT3 mousePos);//�}�E�X���͈͓����ǂ���
	
	/// <summary>
	/// �{�^���̓o��V�[��
	/// </summary>
	/// <param name="Tox">�ړ���̍��WX</param>
	/// <param name="Toy">�ړ���̍��WY</param>
	/// <param name="seconds">�ړ�����</param>
	void SetMovePosition(int Tox, int Toy, float seconds);
	
	/// <summary>
	/// �����Ă��Ȃ������������̔���
	/// </summary>
	/// <returns></returns>
	bool IsMoving();
	
	/// <summary>
	///�I�������̏���
	/// </summary>
	void ForceEnd();

private:
	int hImage;//�ʏ�
	int hPush;//�����ꂽ��̉摜
	bool pushed;//�����ꂽ���ǂ����̔��f
	
	XMFLOAT3 center;//���S���W
	XMFLOAT3 size;//�摜�̑傫��

	//�{�^���̓��������
	XMFLOAT3 startPos;
	XMFLOAT3 endPos;
	float totalTime;
	float CurrentTime_;
};
