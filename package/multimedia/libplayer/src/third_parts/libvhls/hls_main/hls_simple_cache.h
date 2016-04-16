/******************************************************************************

                  ��Ȩ���� (C), amlogic

 ******************************************************************************
  �� �� ��   : hls_simple_cache.h
  �� �� ��   : ����
  ��    ��   : peter
  ��������   : 2013��3��1�� ������
  ����޸�   :
  ��������   : hls_simple_cache.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��3��1�� ������
    ��    ��   : peter
    �޸�����   : �����ļ�

******************************************************************************/


#ifndef __HLS_SIMPLE_CACHE_H__
#define __HLS_SIMPLE_CACHE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


int hls_simple_cache_alloc(int size_max,void** handle);

int hls_simple_cache_get_free_space(void* handle);
int hls_simple_cache_get_data_size(void* handle);
int hls_simple_cache_reset(void* handle);
int hls_simple_cache_revert(void* handle);
int hls_simple_cache_write(void* handle,void* data,int size);

int hls_simple_cache_read(void* handle,void* buffer,int size);
int hls_simple_cache_free(void* handle);

int hls_simple_cache_grow_space(void* handle,int size);

int hls_simple_cache_move_to_pos(void* handle,int pos);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HLS_SIMPLE_CACHE_H__ */
