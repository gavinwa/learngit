#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

/*
�ӳ���ΪtotalCount������occupied�д��������ҵ�i��false����������
*/
int findAvaialble(int *occupied, int i, int totalCount)
{
    return 0;
}


void perm(const int *orgSet,       // �û���ʼ�����Ҫȫ�ŵ�����
          const int totalCount,     // ����Ԫ�ص�����
          int *results,
          int *occupied,           // ���ڼ�¼ԭʼ�����ĸ����ù���
          int nSelected)            // �Ѿ�ѡ���Ԫ�ظ���
{
    int i=0;
    if (nSelected == totalCount)
    {
        printf("");
        return;
    }
    for (i=0; i<=totalCount-nSelected; i++)
    {
        int availIdx = findAvaialble(occupied, i, totalCount);
        results[nSelected] = orgSet[availIdx];
        occupied[availIdx] = 1;
        perm(orgSet, totalCount, results, occupied, nSelected+1);
        occupied[availIdx] = 0;
    }
}


void ppppp(const int *set, const int length)
{
    int *results = (int*)malloc(sizeof(int)*length);
    int *occupied = (int*)malloc(sizeof(int)*length);
    memset(results, 0, sizeof(int)*length);
    memset(occupied, 0, sizeof(int)*length);
    perm(set, length, results, occupied, 0);
    free(results);
    free(occupied);
}


int main1()
{
    int arr[4] = {1,2,3,4};
    ppppp(arr, 4);
    return 0;
}