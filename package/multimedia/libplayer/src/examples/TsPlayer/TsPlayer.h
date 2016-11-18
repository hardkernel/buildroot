#ifndef _TSPLAYER_H_
#define _TSPLAYER_H_

#include <utils/RefBase.h>
#include <surfaceflinger/Surface.h>
#include <surfaceflinger/ISurface.h>
extern "C" {
#include <amports/vformat.h>
#include <amports/aformat.h>
#include <codec.h>
}
using namespace android;

#define TRICKMODE_NONE       0x00
#define TRICKMODE_I          0x01
#define TRICKMODE_FFFB       0x02

typedef struct{
	unsigned short	pid;//pid
	int				nVideoWidth;//��Ƶ���
	int				nVideoHeight;//��Ƶ�߶�
	int				nFrameRate;//֡��
	vformat_t		vFmt;//��Ƶ��ʽ
	unsigned long	cFmt;//�����ʽ
}VIDEO_PARA_T, *PVIDEO_PARA_T;
typedef struct{
	unsigned short	pid;//pid
	int				nChannels;//������
	int				nSampleRate;//������
	aformat_t		aFmt;//��Ƶ��ʽ
	int				nExtraSize;
	unsigned char*	pExtraData;	
}AUDIO_PARA_T, *PAUDIO_PARA_T;
class CTsPlayer{
public:
	CTsPlayer();
	virtual ~CTsPlayer();
public:
	//��ʾ����
	int  SetVideoWindow(int x,int y,int width,int height);
	//16λɫ����Ҫ����colorkey��͸����Ƶ��
	int  SetColorKey(int enable,int key565);
	//x��ʾ��Ƶ
	int  VideoShow(void);
	//������Ƶ
	int  VideoHide(void);
	//��ʼ����Ƶ����
	void InitVideo(PVIDEO_PARA_T pVideoPara);
	//��ʼ����Ƶ����
	void InitAudio(PAUDIO_PARA_T pAudioPara);
	//��ʼ����
	bool StartPlay();
	//��ts��д��
	int WriteData(unsigned char* pBuffer, unsigned int nSize);
	//��ͣ
	bool Pause();
	//��������
	bool Resume();
	//�������
	bool Fast();
	//ֹͣ�������
	bool StopFast();
	//ֹͣ
	bool Stop();
    //��λ
    bool Seek();
    //�趨����
    bool SetVolume(float volume);
    //��ȡ����
    float GetVolume();
private:
	AUDIO_PARA_T aPara;
	VIDEO_PARA_T vPara;	
	int player_pid;
	codec_para_t codec;
	codec_para_t *pcodec;
};
#endif