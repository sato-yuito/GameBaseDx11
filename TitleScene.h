#pragma once
#include "Engine/GameObject.h"


class Button;
//�����V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	//int hPictButtonGive_;//������
	//int hPictButtonBack;//�߂�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;


private:
	Button* start;
	Button* back;
	enum SELECT {
		NONE = -1,
		START = 0,
		BACK,
	};
	SELECT selected;

};