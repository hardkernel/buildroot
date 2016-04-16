/******************************************************************************

                  ��Ȩ���� (C), amlogic

 ******************************************************************************
  �� �� ��   : hls_download.h
  �� �� ��   : ����
  ��    ��   : xiaoqiang.zhu
  ��������   : 2013��2��21�� ������
  ����޸�   :
  ��������   : hls_download.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��2��21�� ������
    ��    ��   : hls_session.h
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/


/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/



#ifndef __HLS_DOWNLOAD_H__
#define __HLS_DOWNLOAD_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef struct _AES128KeyInfo{
    char key_hex[33];
    char ivec_hex[33];
}AES128KeyInfo_t;

typedef enum _KeyType{
    KEY_NONE = 0,
    AES128_CBC = 1,
}KeyType_e;

typedef struct _AESKeyInfo{
    KeyType_e type;
    void* key_info;    
}AESKeyInfo_t;

int hls_http_open(const char* url,const char* headers,void* key,void** handle);
int64_t hls_http_get_fsize(void* handle);
int hls_http_read(void* handle,void* buf,int size);
int hls_http_estimate_bandwidth(void* handle,int* bandwidth_bps);
int hls_http_seek_by_size(void* handle,int64_t pos,int flag);
const char* hls_http_get_redirect_url(void* handle);
int hls_http_get_error_code(void* handle);
//TBD
int hls_http_seek_by_time(void* handle,int64_t timeUs);
int hls_http_close(void* handle);

int fetchHttpSmallFile(const char* url,const char* headers,void** buf,int* length,char** redirectUrl);
int preEstimateBandwidth(void *handle, void *buf, int length);

int hls_task_create(pthread_t *thread_out, pthread_attr_t const * attr, void *(*start_routine)(void *), void * arg);
int hls_task_join(pthread_t thid, void ** ret_val);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HLS_DOWNLOAD_H__ */
