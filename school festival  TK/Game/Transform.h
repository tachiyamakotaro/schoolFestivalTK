#pragma once

class Transform:public Noncopyable
{
	//public�֐�
public:
	Transform();
	~Transform();

	//�X�V����
	void UpdateTransform();
	//���[���h�s��X�V�AUpdateTransform�̕��ŌĂ΂��̂Œ��ڌĂԕK�v�͂Ȃ�
	void UpdateWorldMatrix();

	//�S�Ă̎q�g�����X�t�H�[���Ƃ̕R�Â����O��
	void Release();

	//����̎q�g�����X�t�H�[���Ƃ̕R�Â����O��
	void RemoveChild(Transform* t);

	//�e�g�����X�t�H�[����ݒ�
	void SetParent(Transform* p)
	{
		m_parent = p;
		m_parent->m_children.push_back(this);
	}

	//public�ϐ�
public:
	//���g�̃p�����[�^
	Vector3 m_localPosition;
	Quaternion m_localRotation;
	Vector3 m_localScale;

	//�e�g�����X�t�H�[�����l�������p�����[�^
	Vector3 m_position;
	Quaternion m_rotation;
	Vector3 m_scale;

	//private�ϐ�
private:
	Matrix m_rotationMatrix;
	Matrix m_worldMatrix;

	Transform* m_parent;
	std::vector<Transform*>m_children;
};

