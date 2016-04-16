#ifndef HLS_BANDWIDTH_MEASURE_H
#define HLS_BANDWIDTH_MEASURE_H

/******************************************************************************

                  ��Ȩ���� (C), amlogic

 ******************************************************************************
  �� �� ��   : hls_m3ulivesession.h
  �� �� ��   : ����
  ��    ��   : zz
  ��������   : 2013��2��21�� ������
  ����޸�   :
  ��������   : hls_bandwidth_measure.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��2��21�� ������
    ��    ��   : xiaoqiang.zhu
    �޸�����   : �޸ĺ���������Ӧ�á�

******************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

void *bandwidth_measure_alloc(int measurenum,int flags);
int bandwidth_measure_add(void *band,int bytes,int delay_ns);
int bandwidth_measure_get_bandwidth(void  *band,int *fast_band,int *mid_band,int *avg_band);
void bandwidth_measure_start_read(void *band);
int bandwidth_measure_finish_read(void *band,int bytes);
int bandwidth_measure_free(void *band);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif
