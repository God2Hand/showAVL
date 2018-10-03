#include "BBSTNode.h"
#include <Stdlib.h>
#include <stdio.h>

//���������ĺ���������ú�����Ϊ�˷����û��޸�
void visit(RcdType r) {
    printf("%d", r.elem);
}
//���������ĺ���������ú�����Ϊ�˷����û��޸�
void pKey(RcdType r) {
    printf("%d", r.key);
}

//����Сʧ��������������
void R_Rotate(BBSTree &p)
{
    BBSTree lc = p->lchild; //lcָ��p��������
    p->lchild = lc->rchild;    //lc������������Ϊp����������
    lc->rchild = p; //��p��㣨ԭ����㣩Ϊlc�����Һ���
    p = lc; //pָ���µĸ����
}

//����������Ϊƽ���������ʧ�����ʹ��
void L_Rotate(BBSTree &p)
{
    BBSTree rc = p->rchild;    //rcָ��p�����Һ���
    p->rchild = rc->lchild;    //lc������������Ϊp����������
    rc->lchild = p; //��p��㣨ԭ����㣩Ϊlc��������
    p = rc; //pָ���µĸ����
}

//ƽ�����������ƽ�⴦��
void LeftBalance(BBSTree &T)
{
    BBSTree lc,rd;
    lc = T->lchild; //lcָ��T������
    switch(lc->bf)      //���T����������ƽ�����ӣ�������Ӧ����
    {
    case LH:    //LL�ͣ�����������
        T->bf = lc->bf = EH;
        R_Rotate(T);
        break;
    case EH:    //LL�ͣ�������������deleteAVL��Ҫ��insertAVL�ò�����
        T->bf = LH;
        lc->bf = RH;
        R_Rotate(T);
        break;
    case RH:    //LR�ͣ���˫������
        rd = lc->rchild;
        switch(rd->bf)      //�޸�T�������ӵ�ƽ������
        {
        case LH:
            T->bf = RH;
            lc->bf = EH;
            break;
        case EH:
            T->bf = lc->bf = EH;
            break;
        case RH:
            T->bf = EH;
            lc->bf = LH;
            break;
        }
        rd->bf = EH;
        L_Rotate(T->lchild);    //��T������������������
        R_Rotate(T);    //��T����������
        break;
    }
}

//ƽ�����������ƽ�⴦��
void RightBalance(BBSTree &T)
{
    BBSTree rc,ld;
    rc = T->rchild; //lcָ��T���Һ���
    switch(rc->bf)      //���T����������ƽ�����ӣ�������Ӧ����
    {
    case RH:    //RR�ͣ�����������
        T->bf = rc->bf = 0;
        L_Rotate(T);
        break;
    case EH:    //RR�ͣ�������������deleteAVL��Ҫ��insertAVL�ò�����
        T->bf = RH;
        rc->bf = LH;
        L_Rotate(T);
        break;
    case LH:    //RL�ͣ���˫������
        ld = rc->lchild;
        switch(ld->bf)      //�޸�T�������ӵ�ƽ������
        {
        case 1:
            rc->bf = RH;
            T->bf = EH;
            break;
        case 0:
            T->bf = rc->bf = EH;
            break;
        case -1:
            T->bf = LH;
            rc->bf = EH;
            break;
        }
        ld->bf = EH;
        R_Rotate(T->rchild);    //��T������������������
        L_Rotate(T);    //��T����������
        break;
    }
}


//��ʼ������ʵ���Բ���
Status InitBBST(BBSTree &T)
{
    T = NULL;
    return OK;
}

//��ƽ�������T���ڣ�������T
Status DestroyBBST(BBSTree &T)
{
    if (T)
    {
        DestroyBBST(T->lchild);
        DestroyBBST(T->rchild);
        delete T;
        T = NULL;
    }
    return OK;
}

//��ָ���ؼ��ֲ��ң����ؽ�㣬�������ڣ��򷵻�NULL
BBSTree SearchBBST(BBSTree T, KeyType key)
{
    if (T == NULL || key == T->data.key)
    {
        return T;
    }
    if (key < T->data.key)
    {
        return SearchBBST(T->lchild, key);
    }
    return SearchBBST(T->rchild, key);
}

//����·�����������ҵ�����������·���ϵĹؼ���
BBSTree SearchBBST_V2(BBSTree T, KeyType key)
{
    if (T == NULL || key == T->data.key)
    {
        if (T) pKey(T->data);
        else printf("null");
        return T;
    }
    pKey(T->data); printf(", ");
    if (key < T->data.key)
    {
        return SearchBBST_V2(T->lchild, key);
    }
    return SearchBBST_V2(T->rchild, key);
}

//��ƽ�������T�в�����ֵΪe.key�Ľ�㣬����뵽T
Status InsertAVL(BBSTree &T, RcdType e, Status &taller)
{
    if (NULL == T)      //TΪ�գ�������
    {
        T = (BBSTree)malloc(sizeof(BBSTNode));
        T->data = e;
        T->bf = EH;
        T->lchild = NULL;
        T->rchild = NULL;
        taller = TRUE;
    }
    else if (e.key == T->data.key)      //�����Ѵ��ں�e��ȵĽ��
    {
        taller = FALSE; //δ����
        return FALSE;
    }
    else if (e.key < T->data.key)       //���뵽������
    {
        if (FALSE == InsertAVL(T->lchild, e, taller)) return FALSE; //δ����
        if (TRUE == taller)
        {
            switch(T->bf)   //���T��ƽ������
            {
            case LH:
                LeftBalance(T);
                taller = FALSE;
                break; //ԭ��ߣ���ƽ�⴦��
            case EH:
                T->bf = LH;
                taller = TRUE;
                break;  //ԭ�ȸߣ�����
            case RH:
                T->bf = EH;
                taller = FALSE;
                break; //ԭ�Ҹߣ���ȸ�
            }
        }
    }
    else        //���뵽������
    {
        if (FALSE == InsertAVL(T->rchild, e, taller)) return FALSE; //δ����
        if (TRUE == taller)
        {
            switch(T->bf)   //���ƽ������
            {
            case LH:    //ԭ����ߣ���ȸ�
                T->bf = EH;
                taller = FALSE;
                break;
            case EH:    //ԭ���ȸߣ����Ҹ�
                T->bf = RH;
                taller = TRUE;
                break;
            case RH:    //ԭ���Ҹߣ���ƽ�⴦��
                RightBalance(T);
                taller = FALSE;
                break;
            }
        }
    }
    return TRUE;    //�������
}

//��ƽ�������T�д���ֵΪkey�Ľ�㣬��ɾ��
Status DeleteAVL(BBSTree &T, KeyType key, Status &shorter)
{
    if (NULL == T)      //�Ҳ�����Ԫ��
    {
        return FALSE;   //ɾ��ʧ��
    }
    if (key == T->data.key)     //�ҵ�Ԫ�ؽ��
    {
        BBSTree q = NULL;
        if (T->lchild == NULL)      //������Ϊ��
        {
            q = T;  //��qָ��Ҫɾ����T���
            T = T->rchild;  //��T����������ΪT����˫�׽�����Ӧ����
            delete q;
            shorter = TRUE;
        }
        else if (T->rchild == NULL)     //������Ϊ��
        {
            q = T;  //��qָ��Ҫɾ����T���
            T = T->lchild;  //��T����������ΪT����˫�׽�����Ӧ����
            delete q;
            shorter = TRUE;
        }
        else        //�������������գ�Ѱ��ǰ�����
        {
            q = T->lchild;
            while (q->rchild)
            {
                q = q->rchild;
            }
            T->data = q->data;  //��ǰ���������ݸ��Ƶ�T�����
            DeleteAVL(T->lchild, q->data.key, shorter); //���������еݹ�ɾ��ǰ�����
            //��ɾ����Ӧ�û�Ҫ�ٵ���һ��ԭ�ڵ��ƽ��
            if (TRUE == shorter)
            {
            switch(T->bf)   //���T��ƽ������
            {
            case LH:    //ԭ��ߣ���ȸ�
                T->bf = EH;
                shorter = TRUE;
                break;
            case EH:    //ԭ�ȸߣ����Ҹ�
                T->bf = RH;
                shorter = FALSE;
                break;
            case RH:    //ԭ�Ҹߣ���ƽ�⴦��
                if (T->rchild->bf == EH)    //���ԭ��T�����������������������ڣ�ƽ������Ͳ���䰫
                {
                    shorter = FALSE;
                }
                else        //���ԭ��T������������һ����������ƽ����������䰫
                {
                    shorter = TRUE;
                }
                RightBalance(T);
                break;
            }
            }
        }
    }
    else if (key < T->data.key)     //���������м�������
    {
        if (FALSE == DeleteAVL(T->lchild, key, shorter))
        {
            return FALSE;   //Ԫ�ز����ڣ�ɾ��ʧ��
        }
        if (TRUE == shorter)
        {
            switch(T->bf)   //���T��ƽ������
            {
            case LH:    //ԭ��ߣ���ȸ�
                T->bf = EH;
                shorter = TRUE;
                break;
            case EH:    //ԭ�ȸߣ����Ҹ�
                T->bf = RH;
                shorter = FALSE;
                break;
            case RH:    //ԭ�Ҹߣ���ƽ�⴦��
                if (T->rchild->bf == EH)    //���ԭ��T�����������������������ڣ�ƽ������Ͳ���䰫
                {
                    shorter = FALSE;
                }
                else        //���ԭ��T������������һ����������ƽ����������䰫
                {
                    shorter = TRUE;
                }
                RightBalance(T);
                break;
            }
        }
    }
    else
    {
        if (FALSE == DeleteAVL(T->rchild, key, shorter))
        {
            return FALSE;
        }
        if (TRUE == shorter)
        {
            switch(T->bf)
            {
            case LH:
                if (T->lchild->bf == EH)
                {
                    shorter = FALSE;
                }
                else
                {
                    shorter = TRUE;
                }
                LeftBalance(T);
                break;
            case EH:
                T->bf = LH;
                shorter = FALSE;
                break;
            case RH:
                T->bf = EH;
                shorter = TRUE;
                break;
            }
        }
    }
    return TRUE;
}

//���ض�������ȣ�TΪ������ָ��
int BBSTreeDepth(BBSTree T)
{
    int depthLeft, depthRight;
    if (NULL == T) return 0;    //�ն��������Ϊ0
    else
    {
        depthLeft = BBSTreeDepth(T->lchild);    //�������������
        depthRight = BBSTreeDepth(T->rchild);   //�������������
        return 1+(depthLeft >= depthRight ? depthLeft : depthRight);
    }
}

//�������ʽ��ʾ�������ؼ��֣����ݣ�������ͨ�����ֱ�ۣ���������������������������µĵݹ���ʾ������
void PrintBBSTreeV3(BBSTree &T, int dep) {
    int i;
    if(T->rchild)
        PrintBBSTreeV3(T->rchild, dep+1);
    for(i = 0;i < dep;i++) printf("\t");
    //printf("|--%d(%d)\n", T->data.key, T->data.elem);//���ã�
    printf("|--");pKey(T->data);printf("(");visit(T->data);printf(")\n");
    if(T->lchild)
        PrintBBSTreeV3(T->lchild, dep+1);
}

//�������ʽ��ʾ�������ؼ��֣����ݣ�������ͨ�����ֱ�ۣ�������롰\t������|--������ʶ�𡣣�
void PrintBBSTreeV2(BBSTree &T, int dep) {
    int i;
    for(i = 0;i < dep;i++) printf("\t");
    //printf("|--%d(%d)\n", T->data.key, T->data.elem);//���ã�
    printf("|--");pKey(T->data);printf("(");visit(T->data);printf(")\n");
    if(T->lchild)
        PrintBBSTreeV2(T->lchild, dep+1);
    if(T->rchild)
        PrintBBSTreeV2(T->rchild, dep+1);
}

//�������ʽ��ʾ�������ؼ��֣����ݣ�������ͨ�����ֱ�ۣ�������롰\t������|--������ʶ�𡣲��Ҵ˰汾��ӡ�˿���������Ϊnull��
//���ҵ�����������Ϊnull�򲻴�ӡ����
void PrintBBSTreeV4(BBSTree &T, int dep) {
    int i;
    for(i = 0;i < dep;i++) printf("\t");
    if (NULL == T) { printf("|--null\n"); return; }
    else {
        printf("|--");pKey(T->data);printf("(");visit(T->data);printf(")\n");
    }
    if (NULL == T->lchild && NULL == T->rchild) return;
    PrintBBSTreeV4(T->lchild, dep+1);
    PrintBBSTreeV4(T->rchild, dep+1);
}

//�������ʽ��ʾ��������ԭʼ�������ʾ����������ǳ��������ã���
void PrintBBSTree(BBSTree &T, int dep) {
    int i;
    for(i = 0;i < dep;i++) printf("\t");
    //printf("%d\n", T->data.elem);//���ã�
    visit(T->data);printf("\n");
    if(T->lchild)
        PrintBBSTree(T->lchild, dep+1);
    if(T->rchild)
        PrintBBSTree(T->rchild, dep+1);
}


//�ϲ�(�򵥺ϲ�����T2Ԫ��������뵽T1)
void MergeBBSTree(BBSTree &T1, BBSTree &T2) {
    Status taller = FALSE;
    if(!T2) return;
    InsertAVL(T1, T2->data, taller);
    MergeBBSTree(T1, T2->lchild);
    MergeBBSTree(T1, T2->rchild);
}
//�ϲ�(�򵥺ϲ�����T2Ԫ��������뵽T1����ʾ�������)
void MergeBBSTreeV2(BBSTree &T1, BBSTree &T2) {
    Status taller = FALSE;
    if(!T2) return;
    if(FALSE == InsertAVL(T1, T2->data, taller)) {
            printf("�ؼ���");pKey(T2->data);printf("�Ѿ����ڡ�\n\n");
    }
    //printf("�ؼ���%d�����\n", T2->data.key);//���ã�
    else {
            printf("�ؼ���");pKey(T2->data);printf("�����\n");
            PrintBBSTreeV2(T1, 1);
    }
    MergeBBSTreeV2(T1, T2->lchild);
    MergeBBSTreeV2(T1, T2->rchild);
}


//���ѵ��õĲ�������
void split(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {
    int taller = 0;
    if(!T) return;
    if(T->data.key > key)
    InsertAVL(T2,T->data,taller);
    else
    InsertAVL(T1,T->data,taller);
    split(T->lchild,key,T1,T2);
    split(T->rchild,key,T1,T2);
}
//����
void splitBBSTree(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {
    BBSTree t1 = NULL,t2 = NULL;
    split(T,key,t1,t2);
    T1 = t1;
    T2 = t2;
    return;
}

//���ѵ��õĲ�������(��ʾ�����)
void splitV2(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {
    int taller = 0;
    if(!T) return;
    if(T->data.key > key) {
        InsertAVL(T2,T->data,taller);
        printf("�ؼ���");pKey(T->data);printf("���뵽t2��\n");
    }
    else {
        InsertAVL(T1,T->data,taller);
        printf("�ؼ���");pKey(T->data);printf("���뵽t1��\n");
    }
    printf("t1��\n"); if (!T1) printf("    ��ǰΪ����\n");
    else PrintBBSTreeV2(T1, 1);
    printf("t2��\n"); if (!T2) printf("    ��ǰΪ����\n");
    else PrintBBSTreeV2(T2, 1);
    printf("-----------------------------------\n");
    splitV2(T->lchild,key,T1,T2);
    splitV2(T->rchild,key,T1,T2);
}
//����(��ʾ�����)
void splitBBSTreeV2(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {
    BBSTree t1 = NULL,t2 = NULL;
    splitV2(T,key,t1,t2);
    T1 = t1;
    T2 = t2;
    return;
}

//����(�߼�����)
void CopyBiTree(BBSTree T, BBSTree &TT)//�ݹ鸴�ƶ�����T�õ�TT
{
    if (T)
    {
        TT = (BBSTree)malloc(sizeof(BBSTNode));
        TT->data = T->data;
        CopyBiTree(T->lchild, TT->lchild);
        CopyBiTree(T->rchild, TT->rchild);
    }
    else
    {
        TT = NULL;
    }
}
void bigger(BBSTree &T, int x) {    //���¶������йؼ��ֱ�x��Ľ��
    if (NULL == T) return;
    bigger(T->lchild, x);
    bigger(T->rchild, x);
    if (T->data.key <= x) {
        BBSTree temp = T->rchild;
        T->rchild = NULL;
        DestroyBBST(T);
        T = temp;
    }
}
void nobigger(BBSTree &T, int x) {  //���¶������йؼ���С�ڵ���x�Ľ��
    if (NULL == T) return;
    nobigger(T->lchild, x);
    nobigger(T->rchild, x);
    if (T->data.key > x) {
        BBSTree temp = T->lchild;
        T->lchild = NULL;
        DestroyBBST(T);
        T = temp;
    }
}
void split_sp(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {   //�ָ�����δƽ�⣩
    CopyBiTree(T, T1);//����T��T1
    CopyBiTree(T, T2);//����T��T2
    nobigger(T1, key);
    bigger(T2, key);
}
void MakeAVL(BBSTree T, BBSTree& TT) {  //�����������ƽ�������
    if (NULL == T) return;
    MakeAVL(T->lchild, TT);
    MakeAVL(T->rchild, TT);
    Status taller = FALSE;
    InsertAVL(TT, T->data, taller);
}
void splitBBSTree_sp(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {    //�߼�����
    if (T == NULL) return;
    BBSTree t1 = NULL,t2 = NULL, t3 = NULL, t4 = NULL;
    split_sp(T,key,t1,t2);
    printf("-----------------------------------\n");
    printf("���Ѻ���������Ϊ��\n");
    printf("t1��\n");
    if(!t1 ) printf("\n    ��ǰΪ����\n");
    else PrintBBSTreeV2(t1, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
    printf("\n");
    printf("t2��\n");
    if(!t2 ) printf("\n    ��ǰΪ����\n");
    else PrintBBSTreeV2(t2, 1);//����д�˶���������ʾ������PrintBBSTree(��/V2/V3/V4)
    printf("\n");
    printf("-----------------------------------\n");
    MakeAVL(t1, t3);
    MakeAVL(t2, t4);
    T1 = t3;
    T2 = t4;
    DestroyBBST(t1);
    DestroyBBST(t2);
}
