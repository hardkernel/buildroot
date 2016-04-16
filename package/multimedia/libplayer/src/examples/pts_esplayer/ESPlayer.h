
#ifndef ESPLAYER_H
#define ESPLAYER_H

/*
* =====================================================================================
* ESPlayer
* Description:  
* =====================================================================================
*/

typedef enum MEDIA_CODEC_TYPE
{ 
	DAL_ES_VCODEC_TYPE_H264,  /* video codec type */ 
	DAL_ES_ACODEC_TYPE_AAC, /* audio codec type */ 
	DAL_CODEC_TYPE_UNKNOWN,

} MEDIA_CODEC_TYPE_E;


/*
����ԭ��: void ES_PlayInit()
��������: ��
��������: ��ʼ��ES������
����ֵ:	 ��
*/
void ES_PlayInit();

/*
����ԭ��: void ES_PlayDeinit()
��������: ��
��������:����ʼ��ES���������ͷų�ʼ��ES������ռ�õ���Ӧ��Դ
����ֵ:	��
*/
void ES_PlayDeinit();
/*
����ԭ��:void ES_PlayPause ()
��������:��
��������:��ͣES����������
����ֵ:��
*/
void ES_PlayPause();
/*	
����ԭ��:void ES_PlayResume ()
��������:��
��������:����ES����������
����ֵ:��
*/
void ES_PlayResume ();
/*
����ԭ��
void ES_PlayFreeze ()
��������
��
��������
����ES��������Ƶ���������ճ�������
����ֵ
��
*/
void ES_PlayFreeze ();

/*
����ԭ��: void ES_PlayResetESBuffer ()
��������:	��
��������:���ES������buffer����Ƶ����
����ֵ:��
*/

void ES_PlayResetESBuffer();
/*
����ԭ��:void ES_PlayGetESBufferStatus (int *audio_rate,int *vid_rate)
��������:audio_rate:��ǰaudio����ռbuffer�İٷֱȣ� vid_rate����ǰvideo����ռbuffer�İٷֱȣ�
��������:��ȡaudio/video��ռbuffer�İٷֱ�
����ֵ:	   ��
*/
void ES_PlayGetESBufferStatus (int *audio_rate,int *vid_rate);

/*	
��������:	 data_type������Ƶ���ݱ������ͣ� *es_buffer������Ƶ����buffer�� buffer_len������Ƶ����buffer�ĳ��ȣ�bytes���� PTS������������Ƶ����Ҫ��PTS��
��������:��ES����Ƶ��������ES������
����ֵ:	��
*/
void ES_PlayInjectionMediaDatas (MEDIA_CODEC_TYPE_E data_type, void *es_buffer, unsigned int buffer_len, unsigned int PTS);



#endif