#include "BBSTNode.h"
#include <Stdlib.h>
#include <stdio.h>

//输出数据项的函数，引入该函数是为了方便用户修改
void visit(RcdType r) {
    printf("%d", r.elem);
}
//输出数据项的函数，引入该函数是为了方便用户修改
void pKey(RcdType r) {
    printf("%d", r.key);
}

//对最小失衡树作右旋调整
void R_Rotate(BBSTree &p)
{
    BBSTree lc = p->lchild; //lc指向p结点的左孩子
    p->lchild = lc->rchild;    //lc结点的右子树置为p结点的左子树
    lc->rchild = p; //置p结点（原根结点）为lc结点的右孩子
    p = lc; //p指向新的根结点
}

//左旋调整，为平衡二叉树的失衡调整使用
void L_Rotate(BBSTree &p)
{
    BBSTree rc = p->rchild;    //rc指向p结点的右孩子
    p->rchild = rc->lchild;    //lc结点的左子树置为p结点的右子树
    rc->lchild = p; //置p结点（原根结点）为lc结点的左孩子
    p = rc; //p指向新的根结点
}

//平衡二叉树的左平衡处理
void LeftBalance(BBSTree &T)
{
    BBSTree lc,rd;
    lc = T->lchild; //lc指向T的左孩子
    switch(lc->bf)      //检查T的左子树的平衡因子，并作相应处理
    {
    case LH:    //LL型，需右旋调整
        T->bf = lc->bf = EH;
        R_Rotate(T);
        break;
    case EH:    //LL型，需右旋调整（deleteAVL需要，insertAVL用不到）
        T->bf = LH;
        lc->bf = RH;
        R_Rotate(T);
        break;
    case RH:    //LR型，作双旋调整
        rd = lc->rchild;
        switch(rd->bf)      //修改T及其左孩子的平衡因子
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
        L_Rotate(T->lchild);    //对T的左子树作左旋调整
        R_Rotate(T);    //对T作右旋调整
        break;
    }
}

//平衡二叉树的右平衡处理
void RightBalance(BBSTree &T)
{
    BBSTree rc,ld;
    rc = T->rchild; //lc指向T的右孩子
    switch(rc->bf)      //检查T的右子树的平衡因子，并作相应处理
    {
    case RH:    //RR型，需左旋调整
        T->bf = rc->bf = 0;
        L_Rotate(T);
        break;
    case EH:    //RR型，需左旋调整（deleteAVL需要，insertAVL用不到）
        T->bf = RH;
        rc->bf = LH;
        L_Rotate(T);
        break;
    case LH:    //RL型，作双旋调整
        ld = rc->lchild;
        switch(ld->bf)      //修改T及其左孩子的平衡因子
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
        R_Rotate(T->rchild);    //对T的右子树作右旋调整
        L_Rotate(T);    //对T作左旋调整
        break;
    }
}


//初始化，其实可以不用
Status InitBBST(BBSTree &T)
{
    T = NULL;
    return OK;
}

//若平衡二叉树T存在，销毁数T
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

//按指定关键字查找，返回结点，若不存在，则返回NULL
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

//查找路径，，无论找到与否输出查找路径上的关键字
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

//若平衡二叉树T中不存在值为e.key的结点，则插入到T
Status InsertAVL(BBSTree &T, RcdType e, Status &taller)
{
    if (NULL == T)      //T为空，树长高
    {
        T = (BBSTree)malloc(sizeof(BBSTNode));
        T->data = e;
        T->bf = EH;
        T->lchild = NULL;
        T->rchild = NULL;
        taller = TRUE;
    }
    else if (e.key == T->data.key)      //树中已存在和e相等的结点
    {
        taller = FALSE; //未插入
        return FALSE;
    }
    else if (e.key < T->data.key)       //插入到左子树
    {
        if (FALSE == InsertAVL(T->lchild, e, taller)) return FALSE; //未插入
        if (TRUE == taller)
        {
            switch(T->bf)   //检查T的平衡因子
            {
            case LH:
                LeftBalance(T);
                taller = FALSE;
                break; //原左高，左平衡处理
            case EH:
                T->bf = LH;
                taller = TRUE;
                break;  //原等高，左变高
            case RH:
                T->bf = EH;
                taller = FALSE;
                break; //原右高，变等高
            }
        }
    }
    else        //插入到右子树
    {
        if (FALSE == InsertAVL(T->rchild, e, taller)) return FALSE; //未插入
        if (TRUE == taller)
        {
            switch(T->bf)   //检查平衡因子
            {
            case LH:    //原本左高，变等高
                T->bf = EH;
                taller = FALSE;
                break;
            case EH:    //原本等高，变右高
                T->bf = RH;
                taller = TRUE;
                break;
            case RH:    //原本右高，右平衡处理
                RightBalance(T);
                taller = FALSE;
                break;
            }
        }
    }
    return TRUE;    //插入完成
}

//若平衡二叉树T中存在值为key的结点，则删除
Status DeleteAVL(BBSTree &T, KeyType key, Status &shorter)
{
    if (NULL == T)      //找不到该元素
    {
        return FALSE;   //删除失败
    }
    if (key == T->data.key)     //找到元素结点
    {
        BBSTree q = NULL;
        if (T->lchild == NULL)      //左子树为空
        {
            q = T;  //令q指向要删除的T结点
            T = T->rchild;  //置T结点的右子树为T结点的双亲结点的相应子树
            delete q;
            shorter = TRUE;
        }
        else if (T->rchild == NULL)     //右子树为空
        {
            q = T;  //令q指向要删除的T结点
            T = T->lchild;  //置T结点的左子树为T结点的双亲结点的相应子树
            delete q;
            shorter = TRUE;
        }
        else        //左右子树均不空，寻找前驱结点
        {
            q = T->lchild;
            while (q->rchild)
            {
                q = q->rchild;
            }
            T->data = q->data;  //把前驱结点的数据复制到T结点中
            DeleteAVL(T->lchild, q->data.key, shorter); //在左子树中递归删除前驱结点
            //在删除后，应该还要再调整一次原节点的平衡
            if (TRUE == shorter)
            {
            switch(T->bf)   //检查T的平衡因子
            {
            case LH:    //原左高，变等高
                T->bf = EH;
                shorter = TRUE;
                break;
            case EH:    //原等高，变右高
                T->bf = RH;
                shorter = FALSE;
                break;
            case RH:    //原右高，右平衡处理
                if (T->rchild->bf == EH)    //如果原来T的右子树的左右子树均存在，平衡后树就不会变矮
                {
                    shorter = FALSE;
                }
                else        //如果原来T的右子树仅有一颗子树，则平衡后整棵树变矮
                {
                    shorter = TRUE;
                }
                RightBalance(T);
                break;
            }
            }
        }
    }
    else if (key < T->data.key)     //在左子树中继续查找
    {
        if (FALSE == DeleteAVL(T->lchild, key, shorter))
        {
            return FALSE;   //元素不存在，删除失败
        }
        if (TRUE == shorter)
        {
            switch(T->bf)   //检查T的平衡因子
            {
            case LH:    //原左高，变等高
                T->bf = EH;
                shorter = TRUE;
                break;
            case EH:    //原等高，变右高
                T->bf = RH;
                shorter = FALSE;
                break;
            case RH:    //原右高，右平衡处理
                if (T->rchild->bf == EH)    //如果原来T的右子树的左右子树均存在，平衡后树就不会变矮
                {
                    shorter = FALSE;
                }
                else        //如果原来T的右子树仅有一颗子树，则平衡后整棵树变矮
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

//返回二叉树深度，T为树根的指针
int BBSTreeDepth(BBSTree T)
{
    int depthLeft, depthRight;
    if (NULL == T) return 0;    //空二叉树深度为0
    else
    {
        depthLeft = BBSTreeDepth(T->lchild);    //求左子树的深度
        depthRight = BBSTreeDepth(T->rchild);   //求右子树的深度
        return 1+(depthLeft >= depthRight ? depthLeft : depthRight);
    }
}

//凹入表形式显示方法（关键字（数据）由于普通凹入表不直观，这里采用右子树在上左子树再下的递归显示方法）
void PrintBBSTreeV3(BBSTree &T, int dep) {
    int i;
    if(T->rchild)
        PrintBBSTreeV3(T->rchild, dep+1);
    for(i = 0;i < dep;i++) printf("\t");
    //printf("|--%d(%d)\n", T->data.key, T->data.elem);//弃用！
    printf("|--");pKey(T->data);printf("(");visit(T->data);printf(")\n");
    if(T->lchild)
        PrintBBSTreeV3(T->lchild, dep+1);
}

//凹入表形式显示方法（关键字（数据）由于普通凹入表不直观，这里加入“\t”及“|--”方便识别。）
void PrintBBSTreeV2(BBSTree &T, int dep) {
    int i;
    for(i = 0;i < dep;i++) printf("\t");
    //printf("|--%d(%d)\n", T->data.key, T->data.elem);//弃用！
    printf("|--");pKey(T->data);printf("(");visit(T->data);printf(")\n");
    if(T->lchild)
        PrintBBSTreeV2(T->lchild, dep+1);
    if(T->rchild)
        PrintBBSTreeV2(T->rchild, dep+1);
}

//凹入表形式显示方法（关键字（数据）由于普通凹入表不直观，这里加入“\t”及“|--”方便识别。并且此版本打印了空子树，记为null）
//并且当左右子树都为null则不打印子树
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

//凹入表形式显示方法（最原始凹入表，显示的是数据项，非常不建议用！）
void PrintBBSTree(BBSTree &T, int dep) {
    int i;
    for(i = 0;i < dep;i++) printf("\t");
    //printf("%d\n", T->data.elem);//弃用！
    visit(T->data);printf("\n");
    if(T->lchild)
        PrintBBSTree(T->lchild, dep+1);
    if(T->rchild)
        PrintBBSTree(T->rchild, dep+1);
}


//合并(简单合并，把T2元素逐个插入到T1)
void MergeBBSTree(BBSTree &T1, BBSTree &T2) {
    Status taller = FALSE;
    if(!T2) return;
    InsertAVL(T1, T2->data, taller);
    MergeBBSTree(T1, T2->lchild);
    MergeBBSTree(T1, T2->rchild);
}
//合并(简单合并，把T2元素逐个插入到T1，显示插入过程)
void MergeBBSTreeV2(BBSTree &T1, BBSTree &T2) {
    Status taller = FALSE;
    if(!T2) return;
    if(FALSE == InsertAVL(T1, T2->data, taller)) {
            printf("关键字");pKey(T2->data);printf("已经存在。\n\n");
    }
    //printf("关键字%d插入后：\n", T2->data.key);//弃用！
    else {
            printf("关键字");pKey(T2->data);printf("插入后：\n");
            PrintBBSTreeV2(T1, 1);
    }
    MergeBBSTreeV2(T1, T2->lchild);
    MergeBBSTreeV2(T1, T2->rchild);
}


//分裂调用的操作函数
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
//分裂
void splitBBSTree(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {
    BBSTree t1 = NULL,t2 = NULL;
    split(T,key,t1,t2);
    T1 = t1;
    T2 = t2;
    return;
}

//分裂调用的操作函数(显示步骤版)
void splitV2(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {
    int taller = 0;
    if(!T) return;
    if(T->data.key > key) {
        InsertAVL(T2,T->data,taller);
        printf("关键字");pKey(T->data);printf("插入到t2：\n");
    }
    else {
        InsertAVL(T1,T->data,taller);
        printf("关键字");pKey(T->data);printf("插入到t1：\n");
    }
    printf("t1树\n"); if (!T1) printf("    当前为空树\n");
    else PrintBBSTreeV2(T1, 1);
    printf("t2树\n"); if (!T2) printf("    当前为空树\n");
    else PrintBBSTreeV2(T2, 1);
    printf("-----------------------------------\n");
    splitV2(T->lchild,key,T1,T2);
    splitV2(T->rchild,key,T1,T2);
}
//分裂(显示步骤版)
void splitBBSTreeV2(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {
    BBSTree t1 = NULL,t2 = NULL;
    splitV2(T,key,t1,t2);
    T1 = t1;
    T2 = t2;
    return;
}

//分裂(高级分裂)
void CopyBiTree(BBSTree T, BBSTree &TT)//递归复制二叉树T得到TT
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
void bigger(BBSTree &T, int x) {    //留下二叉树中关键字比x大的结点
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
void nobigger(BBSTree &T, int x) {  //留下二叉树中关键字小于等于x的结点
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
void split_sp(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {   //分割树（未平衡）
    CopyBiTree(T, T1);//复制T到T1
    CopyBiTree(T, T2);//复制T到T2
    nobigger(T1, key);
    bigger(T2, key);
}
void MakeAVL(BBSTree T, BBSTree& TT) {  //将二叉树变成平衡二叉树
    if (NULL == T) return;
    MakeAVL(T->lchild, TT);
    MakeAVL(T->rchild, TT);
    Status taller = FALSE;
    InsertAVL(TT, T->data, taller);
}
void splitBBSTree_sp(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2) {    //高级分裂
    if (T == NULL) return;
    BBSTree t1 = NULL,t2 = NULL, t3 = NULL, t4 = NULL;
    split_sp(T,key,t1,t2);
    printf("-----------------------------------\n");
    printf("分裂后两棵子树为：\n");
    printf("t1树\n");
    if(!t1 ) printf("\n    当前为空树\n");
    else PrintBBSTreeV2(t1, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
    printf("\n");
    printf("t2树\n");
    if(!t2 ) printf("\n    当前为空树\n");
    else PrintBBSTreeV2(t2, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
    printf("\n");
    printf("-----------------------------------\n");
    MakeAVL(t1, t3);
    MakeAVL(t2, t4);
    T1 = t3;
    T2 = t4;
    DestroyBBST(t1);
    DestroyBBST(t2);
}
