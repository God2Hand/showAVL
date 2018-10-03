
/*
 * ƽ���������������ʾ
 *
 * [����Ҫ��]
 *      ʵ�ֶ�̬���ұ�����ֻ������ܣ����ҡ������ɾ������
 *
 * [ѡ������]
 *      (1) �ϲ�����ƽ�����������
 *      (2) ��һ��ƽ�����������Ϊ����ƽ���������ʹ����һ�����е����йؼ��ֶ�С�ڻ����x����һ�����е���һ�ؼ��ֶ�����x����
*/

//��������������ġ���ȡ����ϸ���������Ӧ�ǡ��߶ȡ�����������ָ����

#include <stdio.h>
#include <stdlib.h>
#include "BBSTNode.h"


/*
 * ���鲻Ҫ�ô����Źؼ���
 */
int main()
{
    void testExample();
    BBSTree T1, t1 = NULL, t2 = NULL;
    InitBBST(T1);
    BBSTree T2;
    InitBBST(T2);
    Status taller = FALSE;
    Status shorter = FALSE;
    KeyType key;
    ElemType e;
    int choice = 0;

    while (true) {
        system("cls");
        printf("˵��������Ĺؼ��ֺ���������궨��Ϊint�ͣ��ɸ�����Ҫ�����޸ġ�\\ ����ʾ��ʽΪ���ؼ��֣����ݣ�\n");
        printf("\t\t\t\t\t\t\t\t\t\t����ߣ��������3��--3116004823--�ֽ���\n");//��ĿҪ����ʾ�������Ϣ��
        printf("---------------------------------------------------------------------------------------------------------------------\n\n");
        printf("\t\t\t\t\t      ƽ���������������ʾ\n\n");
        printf("*********************************************************************************************************************\n");
        printf("\t\t\t\t\t\tƽ���������ʾ��\n");
        printf("T1��\n");
        if(!T1 ) printf("\n    ��ǰΪ����\n");
        else PrintBBSTreeV2(T1, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
        printf("\n");
        printf("T2��\n");
        if(!T2 ) printf("\n    ��ǰΪ����\n");
        else PrintBBSTreeV2(T2, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
        printf("\n");
        printf("*********************************************************************************************************************\n");
        printf("        98.�ϲ�T1��T2��T1   99.�ϲ�T1��T2��T2  100.�˳�  \n\n");
        printf("       198.�ϲ�T1��T2��T1(��ʾ�����)  199.�ϲ�T1��T2��T2(��ʾ�����)  \n\n");
        printf("T1������ 0.����   1.����   2.����   3.ɾ��   4.����   5.���   6.����   7.����(��ʾ�����)   8.����(�߼���)\n");
        printf("\n");
        printf("T2������10.����  11.����  12.����  13.ɾ��  14.����  15.���  16.����  17.����(��ʾ�����)  18.����(�߼���)\n");
        printf("*********************************************************************************************************************\n");
        printf("������Ҫ���еĲ�����");
        scanf("%d", &choice);getchar();
        printf("\n");
        switch(choice) {
            case 98://�ϲ�T1��T2��T1
                MergeBBSTree(T1, T2);
                break;
            case 198://�ϲ�T1��T2��T1��ϸ��
                MergeBBSTreeV2(T1, T2);
                printf("������Enter��������...\n");
                getchar();getchar();
                break;
            case 99://�ϲ�T1��T2��T2
                MergeBBSTree(T2, T1);
                break;
            case 199://�ϲ�T1��T2��T2��ϸ��
                MergeBBSTreeV2(T2, T1);
                printf("������Enter��������...\n");
                getchar();getchar();
                break;

            case 100://�˳�
                DestroyBBST(T1);
                DestroyBBST(T2);
                printf("�˳�......\n");
                exit(0);
                break;

            case 0://T1����
                {
                printf("������ؼ��ּ������ݣ�(�ÿո�������Թؼ���-99����(������Ҫ��-99����ؼ��֣����ڲ�������н���.))\n");
                while (true) {
                    scanf("%d %d", &key, &e);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                    if (key == -99) break;
                    RcdType r = { key, e};
                    if (TRUE == InsertAVL(T1, r, taller)) printf("����ɹ�!\n");
                    else printf("����ʧ�ܣ������������Ƿ���ȷ���߹ؼ����Ƿ��Ѵ��ڡ�\n");
                }
                printf("\n");
                printf("������Enter��������...\n");
                getchar();getchar();
                }
                break;
            case 1://T1����
                {
                printf("������һ���ؼ��ּ������ݣ�\n");
                scanf("%d %d", &key, &e);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                RcdType r = { key, e};
                if (FALSE == InsertAVL(T1, r, taller)) {
                    printf("����ʧ�ܣ������������Ƿ���ȷ���߹ؼ����Ƿ��Ѵ��ڡ�\n");
                    printf("\n������Enter������...\n");
                    getchar();getchar();
                }
                }
                break;
            case 2://T1����
                {
                printf("��������Ҫ���ҵĹؼ��֣�");
                scanf("%d", &key);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                BBSTree sch = SearchBBST(T1, key);
                if (NULL == sch) printf("����ʧ�ܣ��ؼ��ֲ����ڡ�\n");
                else {printf("\n�ؼ���%d��Ӧ����Ϊ��", key); visit(sch->data); printf("\n");}/*�����ǣ��޸���������ʱ�޸�*/
                printf("\n����·���Ĺؼ�������Ϊ��( ");SearchBBST_V2(T1, key);printf(" )\n");
                printf("\n������Enter������...\n");
                getchar();getchar();
                }
                break;
            case 3://T1ɾ��
                printf("��������Ҫɾ���Ĺؼ��֣�");
                scanf("%d", &key);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                if (FALSE == DeleteAVL(T1, key, shorter)) {
                    printf("ɾ��ʧ�ܣ����ܹؼ��ֲ����ڡ�\n");
                    printf("\n������Enter������...\n");
                    getchar();getchar();
                }
                break;
            case 4://������T1
                {
                printf("ȷ��������T1�� 1.�� / 2.��\n");
                int yn = 2;
                scanf("%d", &yn);
                if (yn == 1) {
                    if (TRUE == DestroyBBST(T1)) printf("������T1�ɹ���\n");
                }
                }
                break;
            case 5://T1���
                printf("��T1���Ϊ��%d\n", BBSTreeDepth(T1));
                printf("\n������Enter������...\n");
                getchar();getchar();
                break;
            case 6://T1����
                {
                printf("������ؼ����м�ֵx��");
                int x = 0;
                scanf("%d", &x);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                printf("\n-----------------------------------\n");
                splitBBSTree(T1, x, t1, t2);
                printf("\n���Ѻ���������Ϊ��\n");
                printf("t1��\n");
                if(!t1 ) printf("\n    ��ǰΪ����\n");
                else PrintBBSTreeV2(t1, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
                printf("\n");
                printf("t2��\n");
                if(!t2 ) printf("\n    ��ǰΪ����\n");
                else PrintBBSTreeV2(t2, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
                printf("\n");

                printf("��ѡ��---------------------------\n");
                printf("\t0. ����\n");
                printf("\t1. ��t1��T1����t2��T2\n");
                printf("\t2. ��t1��T1\n");
                printf("\t3. ��t2��T1\n");
                printf("-----------------------------------\n");
                int answer = 0;
                scanf("%d", &answer);
                if (answer == 1) {
                    DestroyBBST(T1);
                    DestroyBBST(T2);
                    T1 = t1; t1 = NULL;
                    T2 = t2; t2 = NULL;
                } else if (answer == 2) {
                    DestroyBBST(T1);
                    T1 = t1; t1 = NULL;
                    DestroyBBST(t2);
                } else if (answer == 3) {
                    DestroyBBST(T1);
                    T1 = t2; t2 = NULL;
                    DestroyBBST(t1);
                } else {
                    DestroyBBST(t1);
                    DestroyBBST(t2);
                }
                }
                break;
            case 7://T1����(��ʾ�����)
                {
                printf("������ؼ����м�ֵx��");
                int x = 0;
                scanf("%d", &x);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                splitBBSTreeV2(T1, x, t1, t2);
                printf("\n���Ѻ���������Ϊ��\n");
                printf("t1��\n");
                if(!t1 ) printf("\n    ��ǰΪ����\n");
                else PrintBBSTreeV2(t1, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
                printf("\n");
                printf("t2��\n");
                if(!t2 ) printf("\n    ��ǰΪ����\n");
                else PrintBBSTreeV2(t2, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
                printf("\n");

                printf("��ѡ��---------------------------\n");
                printf("\t0. ����\n");
                printf("\t1. ��t1��T1����t2��T2\n");
                printf("\t2. ��t1��T1\n");
                printf("\t3. ��t2��T1\n");
                printf("-----------------------------------\n");
                int answer = 0;
                scanf("%d", &answer);
                if (answer == 1) {
                    DestroyBBST(T1);
                    DestroyBBST(T2);
                    T1 = t1; t1 = NULL;
                    T2 = t2; t2 = NULL;
                } else if (answer == 2) {
                    DestroyBBST(T1);
                    T1 = t1; t1 = NULL;
                    DestroyBBST(t2);
                } else if (answer == 3) {
                    DestroyBBST(T1);
                    T1 = t2; t2 = NULL;
                    DestroyBBST(t1);
                } else {
                    DestroyBBST(t1);
                    DestroyBBST(t2);
                }
                }
                break;
            case 8://T1����(�߼���)
                {
                printf("������ؼ����м�ֵx��");
                int x = 0;
                scanf("%d", &x);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                splitBBSTree_sp(T1, x, t1, t2);
                printf("��������������Ϊ��\n");
                printf("t1��\n");
                if(!t1 ) printf("\n    ��ǰΪ����\n");
                else PrintBBSTreeV2(t1, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
                printf("\n");
                printf("t2��\n");
                if(!t2 ) printf("\n    ��ǰΪ����\n");
                else PrintBBSTreeV2(t2, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
                printf("\n");
                printf("��ѡ��---------------------------\n");
                printf("\t0. ����\n");
                printf("\t1. ��t1��T1����t2��T2\n");
                printf("\t2. ��t1��T1\n");
                printf("\t3. ��t2��T1\n");
                printf("-----------------------------------\n");
                int answer = 0;
                scanf("%d", &answer);
                if (answer == 1) {
                    DestroyBBST(T1);
                    DestroyBBST(T2);
                    T1 = t1; t1 = NULL;
                    T2 = t2; t2 = NULL;
                } else if (answer == 2) {
                    DestroyBBST(T1);
                    T1 = t1; t1 = NULL;
                    DestroyBBST(t2);
                } else if (answer == 3) {
                    DestroyBBST(T1);
                    T1 = t2; t2 = NULL;
                    DestroyBBST(t1);
                } else {
                    DestroyBBST(t1);
                    DestroyBBST(t2);
                }
                }
                break;

            case 10://T2����
                {
                printf("����������ؼ��ּ������ݣ�(�ÿո�������Թؼ���-99����(������Ҫ��-99����ؼ��֣����ڲ�������н���.))\n");
                while (true) {
                    scanf("%d %d", &key, &e);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                    if (key == -99) break;
                    RcdType r = { key, e};
                    if (TRUE == InsertAVL(T2, r, taller)) printf("����ɹ�!\n");
                    else printf("����ʧ�ܣ������������Ƿ���ȷ���߹ؼ����Ƿ��Ѵ��ڡ�\n");
                }
                printf("\n");
                printf("������Enter��������...\n");
                getchar();getchar();
                }
                break;
            case 11://T2����
                {
                printf("������һ���ؼ��ּ������ݣ�\n");
                scanf("%d %d", &key, &e);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                RcdType r = { key, e};
                if (FALSE == InsertAVL(T2, r, taller)) {
                    printf("����ʧ�ܣ������������Ƿ���ȷ���߹ؼ����Ƿ��Ѵ��ڡ�\n");
                    printf("\n������Enter������...\n");
                    getchar();getchar();
                }
                }
                break;
            case 12://T2����
                {
                printf("��������Ҫ���ҵĹؼ��֣�");
                scanf("%d", &key);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                BBSTree sch = SearchBBST(T2, key);
                if (NULL == sch) printf("����ʧ�ܣ��ؼ��ֲ����ڡ�\n");
                else {printf("\n�ؼ���%d��Ӧ����Ϊ��", key); visit(sch->data); printf("\n");}/*�����ǣ��޸���������ʱ�޸�*/
                printf("\n����·���Ĺؼ�������Ϊ��( ");SearchBBST_V2(T2, key);printf(" )\n");
                printf("\n������Enter������...\n");
                getchar();getchar();
                }
                break;
            case 13://T2ɾ��
                printf("��������Ҫɾ���Ĺؼ��֣�");
                scanf("%d", &key);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                if (FALSE == DeleteAVL(T2, key, shorter)) {
                    printf("ɾ��ʧ�ܣ����ܹؼ��ֲ����ڡ�\n");
                    printf("\n������Enter������...\n");
                    getchar();getchar();
                }
                break;
            case 14://������T2
                {
                printf("ȷ��������T2�� 1.�� / 2.��\n");
                int yn = 2;
                scanf("%d", &yn);
                if (yn == 1) {
                    if (TRUE == DestroyBBST(T2)) printf("������T2�ɹ���\n");
                }
                }
                break;
            case 15://T2���
                printf("��T2���Ϊ��%d\n", BBSTreeDepth(T2));
                printf("\n������Enter������...\n");
                getchar();getchar();
                break;
            case 16://T2����
                {
                printf("������ؼ����м�ֵx��");
                int x = 0;
                scanf("%d", &x);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                splitBBSTree(T2, x, t1, t2);
                printf("\n���Ѻ���������Ϊ��\n");
                printf("t1��\n");
                if(!t1 ) printf("\n    ��ǰΪ����\n");
                else PrintBBSTreeV2(t1, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
                printf("\n");
                printf("t2��\n");
                if(!t2 ) printf("\n    ��ǰΪ����\n");
                else PrintBBSTreeV2(t2, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
                printf("\n");

                printf("��ѡ��---------------------------\n");
                printf("\t0. ����\n");
                printf("\t1. ��t1��T1����t2��T2\n");
                printf("\t2. ��t1��T2\n");
                printf("\t3. ��t2��T2\n");
                printf("-----------------------------------\n");
                int answer = 0;
                scanf("%d", &answer);
                if (answer == 1) {
                    DestroyBBST(T1);
                    DestroyBBST(T2);
                    T1 = t1; t1 = NULL;
                    T2 = t2; t2 = NULL;
                } else if (answer == 2) {
                    DestroyBBST(T2);
                    T2 = t1; t1 = NULL;
                    DestroyBBST(t2);
                } else if (answer == 3) {
                    DestroyBBST(T2);
                    T2 = t2; t2 = NULL;
                    DestroyBBST(t1);
                } else {
                    DestroyBBST(t1);
                    DestroyBBST(t2);
                }
                }
                break;
            case 17://T2����(��ʾ�����)
                {
                printf("������ؼ����м�ֵx��");
                int x = 0;
                scanf("%d", &x);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                splitBBSTreeV2(T2, x, t1, t2);
                printf("\n���Ѻ���������Ϊ��\n");
                printf("t1��\n");
                if(!t1 ) printf("\n    ��ǰΪ����\n");
                else PrintBBSTreeV2(t1, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
                printf("\n");
                printf("t2��\n");
                if(!t2 ) printf("\n    ��ǰΪ����\n");
                else PrintBBSTreeV2(t2, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
                printf("\n");

                printf("��ѡ��---------------------------\n");
                printf("\t0. ����\n");
                printf("\t1. ��t1��T1����t2��T2\n");
                printf("\t2. ��t1��T2\n");
                printf("\t3. ��t2��T2\n");
                printf("-----------------------------------\n");
                int answer = 0;
                scanf("%d", &answer);
                if (answer == 1) {
                    DestroyBBST(T1);
                    DestroyBBST(T2);
                    T1 = t1; t1 = NULL;
                    T2 = t2; t2 = NULL;
                } else if (answer == 2) {
                    DestroyBBST(T2);
                    T2 = t1; t1 = NULL;
                    DestroyBBST(t2);
                } else if (answer == 3) {
                    DestroyBBST(T2);
                    T2 = t2; t2 = NULL;
                    DestroyBBST(t1);
                } else {
                    DestroyBBST(t1);
                    DestroyBBST(t2);
                }
                }
                break;
            case 18://T2����(�߼���)
                {
                printf("������ؼ����м�ֵx��");
                int x = 0;
                scanf("%d", &x);getchar();/*����¼���ǣ��޸���������ʱ�޸�*/
                splitBBSTree_sp(T2, x, t1, t2);
                printf("��������������Ϊ��\n");
                printf("t1��\n");
                if(!t1 ) printf("\n    ��ǰΪ����\n");
                else PrintBBSTreeV2(t1, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
                printf("\n");
                printf("t2��\n");
                if(!t2 ) printf("\n    ��ǰΪ����\n");
                else PrintBBSTreeV2(t2, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
                printf("\n");
                printf("��ѡ��---------------------------\n");
                printf("\t0. ����\n");
                printf("\t1. ��t1��T1����t2��T2\n");
                printf("\t2. ��t1��T1\n");
                printf("\t3. ��t2��T1\n");
                printf("-----------------------------------\n");
                int answer = 0;
                scanf("%d", &answer);
                if (answer == 1) {
                    DestroyBBST(T1);
                    DestroyBBST(T2);
                    T1 = t1; t1 = NULL;
                    T2 = t2; t2 = NULL;
                } else if (answer == 2) {
                    DestroyBBST(T2);
                    T2 = t1; t1 = NULL;
                    DestroyBBST(t2);
                } else if (answer == 3) {
                    DestroyBBST(T2);
                    T2 = t2; t2 = NULL;
                    DestroyBBST(t1);
                } else {
                    DestroyBBST(t1);
                    DestroyBBST(t2);
                }
                }
                break;

            default:
                break;
        }
        //switch����
    }
    //while(true)����
    return 0;
}

/*
 * �����ǹ��ο�����������
 * �����������£��ؼ���(�洢����)
 * 37(1), 13(2), 1(3), 4(4), 7(5), 56(6), 13(7), 95(8), 76(9), 12(10), 2(11), 3(12)
 *
 * 13
 *   4                                                      13
 *     2                                                  /    \
 *       1                                              4       56
 *       3                                             / \      / \
 *     7                                              2   7    37 95
 *       12                                          / \    \     /
 *   56                                             1   3    12  76
 *     37
 *     95
 *       76
*/
