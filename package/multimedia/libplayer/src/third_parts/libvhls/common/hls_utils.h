#ifndef __HLS_UTILS_H__
#define __HLS_UTILS_H__
/******************************************************************************

                  ��Ȩ���� (C), amlogic

 ******************************************************************************
  �� �� ��   : hls_utils.h
  �� �� ��   : ����
  ��    ��   : xiaoqiang.zhu
  ��������   : 2013��2��21�� ������
  ����޸�   :
  ��������   : hls_utils.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��2��21�� ������
    ��    ��   : xiaoqiang.zhu
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include <errno.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define HLSMAX(a,b) ((a) > (b) ? (a) : (b))
#define HLSMIN(a,b) ((a) > (b) ? (b) : (a))


#ifndef MAX_URL_SIZE
#define MAX_URL_SIZE 4096
#endif

/* error handling */
#if EDOM > 0
#define HLSERROR(e) (-(e))   ///< Returns a negative error code from a POSIX error code, to return from library functions.
#else
/* Some platforms have E* and errno already negated. */
#define HLSERROR(e) (e)
#endif


#ifdef __GNUC__
#define hls_dynarray_add(tab, nb_ptr, elem)\
do {\
    __typeof__(tab) _tab = (tab);\
    __typeof__(elem) _elem = (elem);\
    (void)sizeof(**_tab == _elem); /* check that types are compatible */\
    in_dynarray_add(_tab, nb_ptr, _elem);\
} while(0)
#else
#define hls_dynarray_add(tab, nb_ptr, elem)\
do {\
    in_dynarray_add((tab), nb_ptr, (elem));\
} while(0)
#endif


typedef struct _GUID
{
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint16_t Data4;
    uint8_t  Data5[6];
} GUID;

typedef GUID guid_t;

    
#define GUID_FMT "%04X-%02X-%02X-%02X-%02X%02X%02X%02X%02X%02X"
#define GUID_PRINT( guid )  \
    (guid).Data1,\
    (guid).Data2,              \
    (guid).Data3,              \
    (guid).Data4,              \
    (guid).Data5[0],(guid).Data5[1],(guid).Data5[2],    \
    (guid).Data5[3],(guid).Data5[4],(guid).Data5[5]    




/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

int getLocalCurrentTime(char** buf,int* len);

int64_t in_gettimeUs(void);

/**
 * Add an element to a dynamic array. from ffmpeg
 *
 * @param tab_ptr Pointer to the array.
 * @param nb_ptr  Pointer to the number of elements in the array.
 * @param elem    Element to be added.
 */
void in_dynarray_add(void *tab_ptr, int *nb_ptr, void *elem);


void in_freepointer(void *arg);

float in_get_sys_prop_float(char* key);

int in_get_sys_prop_bool(char* key);
void  in_generate_guid (guid_t *p_guid );

char* in_strip_blank(char *pStr);

int in_hex_to_data(const char *p,uint8_t *data);


const char* in_data_to_hex(char *buff, const uint8_t *src, int s, int lowercase);


void in_hex_dump(const char* title,const unsigned char* dat,size_t length);


int in_get_mac_address(const char* device,char* mac,int size);   

unsigned long in_get_free_mem_size();
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HLS_UTILS_H__ */
