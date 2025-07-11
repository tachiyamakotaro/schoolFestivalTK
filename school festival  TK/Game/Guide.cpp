#include "stdafx.h"
#include "Guide.h"
#include "Title.h"
#include "sound/SoundSource.h"
#include "sound/SoundEngine.h"
#include <algorithm>
using namespace std;

Guide::Guide()
{

}

Guide::~Guide()
{

}

void Guide::setGuideState(int value) {
	if (value < MIN_STATE)value = MIN_STATE;
	if (value > MAX_STATE)value = MAX_STATE;
	m_guideState = value;
}

int Guide::getGuideState() const
{
	return 0;
}

bool Guide::Start()
{
	//�摜�̓ǂݍ���
	//m_spriteRender.Init("Assets/modelData/guide_morning.DDS",1920.0f,1080.0f);

	//BGM
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/AS_1118503_�y���ŃN�[���ȃ`���[�g���A������BGM.wav");
	m_GuideBGM = NewGO<SoundSource>(0);
	m_GuideBGM->Init(3);
	m_GuideBGM->Play(true);

	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/AS_890910_����^�N���b�N�^�I�����i�s�R���b�j.wav");
	//Guide g;						//����Ɖ����̐ݒ�
	//g.setGuideState(0);  //�P�ɐ���
	//cout << g.getGuideState() << endl; //�o�͂P

	//g.setGuideState(2); //���̂܂܎g����
	//cout << g.getGuideState() << endl; //�o��2

	//g.setGuideState(100); //3�ɐ��������
	//cout << g.getGuideState() << endl; //�o��3
	return true;
}

void Guide::Update()
{
	if (g_pad[0]->IsTrigger(enButtonRight)) {
		m_GuideSE = NewGO<SoundSource>(0);
		m_GuideSE->Init(4);
		m_GuideSE->Play(false);
		m_guideState += 1;
		
	}
	if (g_pad[0]->IsTrigger(enButtonLeft)) {
		m_GuideSE = NewGO<SoundSource>(0);
		m_GuideSE->Init(4);
		m_GuideSE->Play(false);
		m_guideState -= 1;
		
	}
	
	

	switch (m_guideState) {
	case 1:
		
		m_spriteRender.Init("Assets/modelData/guide_morning.DDS",1920.0f,1080.0f);
		
		
		break;
	case 2:
		m_spriteRender.Init("Assets/modelData/guide_evening.DDS", 1920.0f, 1080.0f);
	
		break;
	case 3:
		m_spriteRender.Init("Assets/modelData/guide_night.DDS", 1920.0f, 1080.0f);
		
		if (g_pad[0]->IsTrigger(enButtonX)) {
			//���ʉ��̍Đ�
			SoundSource* se = NewGO<SoundSource>(0);
			se->Init(2);
			se->Play(false);

			NewGO<Title>(0);
			DeleteGO(this);
			DeleteGO(m_GuideBGM);
		}
		break;
	default:
		if (m_guideState < 1) {
			m_guideState = 1;
		}
		else if (m_guideState > 3) {
			m_guideState = 3;
		}
		break;
	}
	
}

void Guide::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}