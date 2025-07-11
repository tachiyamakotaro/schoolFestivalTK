#include "stdafx.h"
#include "Transform.h"


Transform::Transform()
	:m_position(Vector3::Zero)
	,m_localPosition(Vector3::Zero)
	, m_scale(Vector3::One)
	, m_localScale(Vector3::One)
	,m_rotation(Quaternion::Identity)
	, m_localRotation(Quaternion::Identity)
	,m_rotationMatrix(Matrix::Identity)
	, m_worldMatrix(Matrix::Identity)
	,m_parent(nullptr)
{
	m_children.clear();
}


Transform::~Transform()
{
	if (m_parent) {
		m_parent->RemoveChild(this);
	}
	Release();
}

void Transform::UpdateTransform()
{
	if (m_parent) {
		//���W�v�Z
		Matrix localPos;
		localPos.MakeTranslation(m_localPosition);

		Matrix pos;
		pos.Multiply(localPos, m_parent->m_worldMatrix);

		//�������s�ړ��̕������Ƃ��Ă邾��
		m_position.x = pos.m[3][0];
		m_position.y = pos.m[3][1];
		m_position.z = pos.m[3][2];

		//�X�P�[��
		m_scale.x = m_localScale.x * m_parent->m_scale.x;
		m_scale.y = m_localScale.y * m_parent->m_scale.y;
		m_scale.z = m_localScale.z * m_parent->m_scale.z;

		//��]
		m_rotation = m_parent->m_rotation * m_localRotation;
	}
	else
	{
		//���[�J���̒l�����̂܂܃R�s�[
		m_position = m_localPosition;
		m_scale = m_localScale;
		m_rotation = m_localRotation;
	}
	
	//��]�s��
	m_rotationMatrix.MakeRotationFromQuaternion(m_rotation);
	//���[���h�s��X�V
	UpdateWorldMatrix();
}

void Transform::UpdateWorldMatrix()
{
	Matrix scal, pos, world;
	scal.MakeScaling(m_scale);
	pos.MakeTranslation(m_position);

	world.Multiply(scal, m_rotationMatrix);
	m_worldMatrix.Multiply(world, pos);

	// �q���̃��[���h�s����X�V
	for (Transform* child : m_children)
	{
		child->UpdateTransform();
	}
}


void Transform::Release()
{
	//�C�e���[�^����
	std::vector<Transform*>::iterator it = m_children.begin();
	//vector�̏I���܂ŉ�
	while (it != m_children.end())
	{
		//�q��Transform����̕R�Â����O��
		(*it)->m_parent = nullptr;
		//�q���g�����X�t�H�[���ւ̕R�Â����O��
		it = m_children.erase(it); //erase�̖߂�l�Ői�߂�
	}
	//�O�̂��߂�vector�̗v�f��S�폜
	m_children.clear();
}

void Transform::RemoveChild(Transform* t)
{
	std::vector<Transform*>::iterator it = m_children.begin();
	// vector�̏I���܂ŉ�
	while (it != m_children.end())
	{
		//�C�e���[�^����q���g�����X�t�H�[���̃|�C���^���󂯎��
		Transform* child = (*it);
		//�󂯎�����q���g�����X�t�H�[�������Ă��ꂽ���̂Ȃ�
		if (child == t)
		{
			//�R�Â����O��
			child->m_parent = nullptr;
			m_children.erase(it);
			//�������I��
			return;
		}

		//�C�e���[�^��i�߂�
		++it;
	}
}
