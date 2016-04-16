/*
 * crc32.c
 *
 *  Created on: 2013-5-31
 *      Author: binsheng.xu@amlogic.com
 */
#include "image_packer_i.h"

#define BUFSIZE     1024*16

static unsigned int crc_table[256];


static void init_crc_table(void)
{
    unsigned int c;
    unsigned int i, j;

    for (i = 0; i < 256; i++) {
        c = (unsigned int)i;
        for (j = 0; j < 8; j++) {
            if (c & 1)
                c = 0xedb88320L ^ (c >> 1);
            else
                c = c >> 1;
        }
        crc_table[i] = c;
    }
}

/*����buffer��crcУ����*/
static unsigned int crc32(unsigned int crc,unsigned char *buffer, unsigned int size)
{
    unsigned int i;
    for (i = 0; i < size; i++) {
        crc = crc_table[(crc ^ buffer[i]) & 0xff] ^ (crc >> 8);
    }
    return crc ;
}

/*
**������ļ���CRCУ����:crc32����,�Ƕ�һ��buffer���д���,
**�����һ���ļ���Խϴ�,��Ȼ����ֱ�Ӷ�ȡ���ڴ浱��
**����ֻ�ܽ��ļ��ֶζ�ȡ��������crcУ��,
**Ȼ��ѭ������һ�ε�crcУ�����ٴ��ݸ��µ�bufferУ�麯��,
**��������ɵ�crcУ������Ǹ��ļ���crcУ����
*/
int calc_img_crc(FILE* fp, off_t offset)
{

    int nread;
    unsigned char buf[BUFSIZE];
    /*��һ�δ����ֵ��Ҫ�̶�,������Ͷ�ʹ�ø�ֵ����crcУ����,
    **��ô���ն�Ҳͬ����Ҫʹ�ø�ֵ���м���*/
    unsigned int crc = 0xffffffff;

    if (fp == NULL) {
        fprintf(stderr,"bad param!!\n");
        return -1;
    }

    init_crc_table();
    fseeko(fp,offset,SEEK_SET);
    while ((nread = fread(buf,1, BUFSIZE,fp)) > 0) {
        crc = crc32(crc, buf, nread);
    }

    if (nread < 0) {
        fprintf(stderr,"%d:read %s.\n", __LINE__, strerror(errno));
        return -1;
    }

    return crc;
}


