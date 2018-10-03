
/*
 * 平衡二叉树操作的演示
 *
 * [基本要求]
 *      实现动态查找表的三种基本功能：查找、插入和删除。√
 *
 * [选做内容]
 *      (1) 合并两棵平衡二叉树。√
 *      (2) 把一棵平衡二叉树分裂为两棵平衡二叉树，使得在一棵树中的所有关键字都小于或等于x，另一棵树中的任一关键字都大于x。√
*/

//纠正：本程序里的“深度”按严格定义上来讲应是“高度”，这里予以指出。

#include <stdio.h>
#include <stdlib.h>
#include "BBSTNode.h"


/*
 * 建议不要用带负号关键字
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
        printf("说明：这里的关键字和主数据项都宏定义为int型，可根据需要自行修改。\\ 树显示格式为：关键字（数据）\n");
        printf("\t\t\t\t\t\t\t\t\t\t设计者：软件工程3班--3116004823--林锦鹏\n");//题目要求，显示设计者信息。
        printf("---------------------------------------------------------------------------------------------------------------------\n\n");
        printf("\t\t\t\t\t      平衡二叉树操作的演示\n\n");
        printf("*********************************************************************************************************************\n");
        printf("\t\t\t\t\t\t平衡二叉树演示区\n");
        printf("T1树\n");
        if(!T1 ) printf("\n    当前为空树\n");
        else PrintBBSTreeV2(T1, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
        printf("\n");
        printf("T2树\n");
        if(!T2 ) printf("\n    当前为空树\n");
        else PrintBBSTreeV2(T2, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
        printf("\n");
        printf("*********************************************************************************************************************\n");
        printf("        98.合并T1和T2到T1   99.合并T1和T2到T2  100.退出  \n\n");
        printf("       198.合并T1和T2到T1(显示步骤版)  199.合并T1和T2到T2(显示步骤版)  \n\n");
        printf("T1操作： 0.创建   1.插入   2.查找   3.删除   4.销毁   5.深度   6.分裂   7.分裂(显示步骤版)   8.分裂(高级版)\n");
        printf("\n");
        printf("T2操作：10.创建  11.插入  12.查找  13.删除  14.销毁  15.深度  16.分裂  17.分裂(显示步骤版)  18.分裂(高级版)\n");
        printf("*********************************************************************************************************************\n");
        printf("输入你要进行的操作：");
        scanf("%d", &choice);getchar();
        printf("\n");
        switch(choice) {
            case 98://合并T1和T2到T1
                MergeBBSTree(T1, T2);
                break;
            case 198://合并T1和T2到T1详细版
                MergeBBSTreeV2(T1, T2);
                printf("按两下Enter键更新树...\n");
                getchar();getchar();
                break;
            case 99://合并T1和T2到T2
                MergeBBSTree(T2, T1);
                break;
            case 199://合并T1和T2到T2详细版
                MergeBBSTreeV2(T2, T1);
                printf("按两下Enter键更新树...\n");
                getchar();getchar();
                break;

            case 100://退出
                DestroyBBST(T1);
                DestroyBBST(T2);
                printf("退出......\n");
                exit(0);
                break;

            case 0://T1构建
                {
                printf("请输入关键字及其数据：(用空格隔开，以关键字-99结束(如果你非要用-99这个关键字，请在插入操作中进行.))\n");
                while (true) {
                    scanf("%d %d", &key, &e);getchar();/*键盘录入标记，修改数据类型时修改*/
                    if (key == -99) break;
                    RcdType r = { key, e};
                    if (TRUE == InsertAVL(T1, r, taller)) printf("插入成功!\n");
                    else printf("插入失败！请检查你输入是否正确或者关键字是否已存在。\n");
                }
                printf("\n");
                printf("按两下Enter键更新树...\n");
                getchar();getchar();
                }
                break;
            case 1://T1插入
                {
                printf("请输入一个关键字及其数据：\n");
                scanf("%d %d", &key, &e);getchar();/*键盘录入标记，修改数据类型时修改*/
                RcdType r = { key, e};
                if (FALSE == InsertAVL(T1, r, taller)) {
                    printf("插入失败！请检查你输入是否正确或者关键字是否已存在。\n");
                    printf("\n按两下Enter键继续...\n");
                    getchar();getchar();
                }
                }
                break;
            case 2://T1查找
                {
                printf("请输入你要查找的关键字：");
                scanf("%d", &key);getchar();/*键盘录入标记，修改数据类型时修改*/
                BBSTree sch = SearchBBST(T1, key);
                if (NULL == sch) printf("查找失败！关键字不存在。\n");
                else {printf("\n关键字%d对应数据为：", key); visit(sch->data); printf("\n");}/*输出标记，修改数据类型时修改*/
                printf("\n查找路径的关键字序列为：( ");SearchBBST_V2(T1, key);printf(" )\n");
                printf("\n按两下Enter键继续...\n");
                getchar();getchar();
                }
                break;
            case 3://T1删除
                printf("请输入你要删除的关键字：");
                scanf("%d", &key);getchar();/*键盘录入标记，修改数据类型时修改*/
                if (FALSE == DeleteAVL(T1, key, shorter)) {
                    printf("删除失败！可能关键字不存在。\n");
                    printf("\n按两下Enter键继续...\n");
                    getchar();getchar();
                }
                break;
            case 4://销毁树T1
                {
                printf("确定销毁树T1吗？ 1.是 / 2.否\n");
                int yn = 2;
                scanf("%d", &yn);
                if (yn == 1) {
                    if (TRUE == DestroyBBST(T1)) printf("销毁树T1成功！\n");
                }
                }
                break;
            case 5://T1深度
                printf("树T1深度为：%d\n", BBSTreeDepth(T1));
                printf("\n按两下Enter键继续...\n");
                getchar();getchar();
                break;
            case 6://T1分裂
                {
                printf("请输入关键字中间值x：");
                int x = 0;
                scanf("%d", &x);getchar();/*键盘录入标记，修改数据类型时修改*/
                printf("\n-----------------------------------\n");
                splitBBSTree(T1, x, t1, t2);
                printf("\n分裂后两棵子树为：\n");
                printf("t1树\n");
                if(!t1 ) printf("\n    当前为空树\n");
                else PrintBBSTreeV2(t1, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
                printf("\n");
                printf("t2树\n");
                if(!t2 ) printf("\n    当前为空树\n");
                else PrintBBSTreeV2(t2, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
                printf("\n");

                printf("请选择：---------------------------\n");
                printf("\t0. 返回\n");
                printf("\t1. 把t1给T1，把t2给T2\n");
                printf("\t2. 把t1给T1\n");
                printf("\t3. 把t2给T1\n");
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
            case 7://T1分裂(显示步骤版)
                {
                printf("请输入关键字中间值x：");
                int x = 0;
                scanf("%d", &x);getchar();/*键盘录入标记，修改数据类型时修改*/
                splitBBSTreeV2(T1, x, t1, t2);
                printf("\n分裂后两棵子树为：\n");
                printf("t1树\n");
                if(!t1 ) printf("\n    当前为空树\n");
                else PrintBBSTreeV2(t1, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
                printf("\n");
                printf("t2树\n");
                if(!t2 ) printf("\n    当前为空树\n");
                else PrintBBSTreeV2(t2, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
                printf("\n");

                printf("请选择：---------------------------\n");
                printf("\t0. 返回\n");
                printf("\t1. 把t1给T1，把t2给T2\n");
                printf("\t2. 把t1给T1\n");
                printf("\t3. 把t2给T1\n");
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
            case 8://T1分裂(高级版)
                {
                printf("请输入关键字中间值x：");
                int x = 0;
                scanf("%d", &x);getchar();/*键盘录入标记，修改数据类型时修改*/
                splitBBSTree_sp(T1, x, t1, t2);
                printf("调整后两棵子树为：\n");
                printf("t1树\n");
                if(!t1 ) printf("\n    当前为空树\n");
                else PrintBBSTreeV2(t1, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
                printf("\n");
                printf("t2树\n");
                if(!t2 ) printf("\n    当前为空树\n");
                else PrintBBSTreeV2(t2, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
                printf("\n");
                printf("请选择：---------------------------\n");
                printf("\t0. 返回\n");
                printf("\t1. 把t1给T1，把t2给T2\n");
                printf("\t2. 把t1给T1\n");
                printf("\t3. 把t2给T1\n");
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

            case 10://T2构建
                {
                printf("请逐行输入关键字及其数据：(用空格隔开，以关键字-99结束(如果你非要用-99这个关键字，请在插入操作中进行.))\n");
                while (true) {
                    scanf("%d %d", &key, &e);getchar();/*键盘录入标记，修改数据类型时修改*/
                    if (key == -99) break;
                    RcdType r = { key, e};
                    if (TRUE == InsertAVL(T2, r, taller)) printf("插入成功!\n");
                    else printf("插入失败！请检查你输入是否正确或者关键字是否已存在。\n");
                }
                printf("\n");
                printf("按两下Enter键更新树...\n");
                getchar();getchar();
                }
                break;
            case 11://T2插入
                {
                printf("请输入一个关键字及其数据：\n");
                scanf("%d %d", &key, &e);getchar();/*键盘录入标记，修改数据类型时修改*/
                RcdType r = { key, e};
                if (FALSE == InsertAVL(T2, r, taller)) {
                    printf("插入失败！请检查你输入是否正确或者关键字是否已存在。\n");
                    printf("\n按两下Enter键继续...\n");
                    getchar();getchar();
                }
                }
                break;
            case 12://T2查找
                {
                printf("请输入你要查找的关键字：");
                scanf("%d", &key);getchar();/*键盘录入标记，修改数据类型时修改*/
                BBSTree sch = SearchBBST(T2, key);
                if (NULL == sch) printf("查找失败！关键字不存在。\n");
                else {printf("\n关键字%d对应数据为：", key); visit(sch->data); printf("\n");}/*输出标记，修改数据类型时修改*/
                printf("\n查找路径的关键字序列为：( ");SearchBBST_V2(T2, key);printf(" )\n");
                printf("\n按两下Enter键继续...\n");
                getchar();getchar();
                }
                break;
            case 13://T2删除
                printf("请输入你要删除的关键字：");
                scanf("%d", &key);getchar();/*键盘录入标记，修改数据类型时修改*/
                if (FALSE == DeleteAVL(T2, key, shorter)) {
                    printf("删除失败！可能关键字不存在。\n");
                    printf("\n按两下Enter键继续...\n");
                    getchar();getchar();
                }
                break;
            case 14://销毁树T2
                {
                printf("确定销毁树T2吗？ 1.是 / 2.否\n");
                int yn = 2;
                scanf("%d", &yn);
                if (yn == 1) {
                    if (TRUE == DestroyBBST(T2)) printf("销毁树T2成功！\n");
                }
                }
                break;
            case 15://T2深度
                printf("树T2深度为：%d\n", BBSTreeDepth(T2));
                printf("\n按两下Enter键继续...\n");
                getchar();getchar();
                break;
            case 16://T2分裂
                {
                printf("请输入关键字中间值x：");
                int x = 0;
                scanf("%d", &x);getchar();/*键盘录入标记，修改数据类型时修改*/
                splitBBSTree(T2, x, t1, t2);
                printf("\n分裂后两棵子树为：\n");
                printf("t1树\n");
                if(!t1 ) printf("\n    当前为空树\n");
                else PrintBBSTreeV2(t1, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
                printf("\n");
                printf("t2树\n");
                if(!t2 ) printf("\n    当前为空树\n");
                else PrintBBSTreeV2(t2, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
                printf("\n");

                printf("请选择：---------------------------\n");
                printf("\t0. 返回\n");
                printf("\t1. 把t1给T1，把t2给T2\n");
                printf("\t2. 把t1给T2\n");
                printf("\t3. 把t2给T2\n");
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
            case 17://T2分裂(显示步骤版)
                {
                printf("请输入关键字中间值x：");
                int x = 0;
                scanf("%d", &x);getchar();/*键盘录入标记，修改数据类型时修改*/
                splitBBSTreeV2(T2, x, t1, t2);
                printf("\n分裂后两棵子树为：\n");
                printf("t1树\n");
                if(!t1 ) printf("\n    当前为空树\n");
                else PrintBBSTreeV2(t1, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
                printf("\n");
                printf("t2树\n");
                if(!t2 ) printf("\n    当前为空树\n");
                else PrintBBSTreeV2(t2, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
                printf("\n");

                printf("请选择：---------------------------\n");
                printf("\t0. 返回\n");
                printf("\t1. 把t1给T1，把t2给T2\n");
                printf("\t2. 把t1给T2\n");
                printf("\t3. 把t2给T2\n");
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
            case 18://T2分裂(高级版)
                {
                printf("请输入关键字中间值x：");
                int x = 0;
                scanf("%d", &x);getchar();/*键盘录入标记，修改数据类型时修改*/
                splitBBSTree_sp(T2, x, t1, t2);
                printf("调整后两棵子树为：\n");
                printf("t1树\n");
                if(!t1 ) printf("\n    当前为空树\n");
                else PrintBBSTreeV2(t1, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
                printf("\n");
                printf("t2树\n");
                if(!t2 ) printf("\n    当前为空树\n");
                else PrintBBSTreeV2(t2, 1);//这里写了多个凹入表显示函数：PrintBBSTree(无/V2/V3/V4)
                printf("\n");
                printf("请选择：---------------------------\n");
                printf("\t0. 返回\n");
                printf("\t1. 把t1给T1，把t2给T2\n");
                printf("\t2. 把t1给T1\n");
                printf("\t3. 把t2给T1\n");
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
        //switch结束
    }
    //while(true)结束
    return 0;
}

/*
 * 这里是供参考测试用例。
 * 测试数据如下：关键字(存储数据)
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
