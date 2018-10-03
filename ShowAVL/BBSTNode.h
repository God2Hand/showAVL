#ifndef BBSTNODE_H_INCLUDED
#define BBSTNODE_H_INCLUDED

//预定义常量和类型
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERLOW -1
#define LH +1   //左子树比右子树高，简称左高
#define EH 0    //左、右子树等高，简称等高
#define RH -1   //右子树比左子树高，简称右高
typedef int Status; //用作函数值类型，表示函数结果状态
typedef int ElemType;    //用作数据类型，存放真正的数据，可根据需要自行修改
typedef int KeyType;    //关键字项，可根据需要自行修改
typedef struct
{
    KeyType key;    //关键字项
    ElemType elem;  //主要数据项
} RecordType,RcdType;//结点的数据域

typedef struct BBSTNode
{
    RcdType data;   //数据元素
    int bf; //平衡因子
    struct BBSTNode *lchild, *rchild;   //左右孩子指针
} *BBSTree; //平衡二叉树

void R_Rotate(BBSTree &p);  //对最小失衡树作右旋调整，为平衡二叉树的失衡调整使用
void L_Rotate(BBSTree &p);  //对最小失衡树作左旋调整，为平衡二叉树的失衡调整使用
void LeftBalance(BBSTree &T);   //平衡二叉树的左平衡处理
void RightBalance(BBSTree &T);  //平衡二叉树的右平衡处理

void visit(RcdType r);  //输出数据项的函数，引入该函数是为了改变数据类型更方便
void pKey(RcdType r);   //输出数据项的函数，引入该函数是为了方便用户修改

//以下才是给调用的功能
Status InitBBST(BBSTree &T); //初始化，其实可以不用

Status DestroyBBST(BBSTree &T);  //若平衡二叉树T存在，销毁数T

BBSTree SearchBBST(BBSTree T, KeyType key); //按指定关键字查找，返回结点，若不存在，则返回NULL
BBSTree SearchBBST_V2(BBSTree T, KeyType key);  //查找路径，，无论找到与否输出查找路径上的关键字
Status InsertAVL(BBSTree &T, RcdType e, Status &taller);    //若平衡二叉树T中不存在值为e.key的结点，则插入到T
Status DeleteAVL(BBSTree &T, KeyType key, Status &shorter); //若平衡二叉树T中存在值为key的结点，则删除

int BBSTreeDepth(BBSTree T);//返回二叉树深度，T为树根的指针

//

//凹入表显示
void PrintBBSTreeV3(BBSTree &T, int dep);//凹入表形式显示方法（由于普通凹入表不直观，这里采用右子树在上左子树再下的递归显示方法）
void PrintBBSTreeV2(BBSTree &T, int dep);//凹入表形式显示方法（关键字（数据）由于普通凹入表不直观，这里加入“\t”及“|--”方便识别。）
void PrintBBSTree(BBSTree &T, int dep);//凹入表形式显示方法（最原始凹入表，显示的是数据项，非常不建议用！）
//凹入表形式显示方法（关键字（数据）由于普通凹入表不直观，这里加入“\t”及“|--”方便识别。并且此版本打印了空子树，记为null）//并且当左右子树都为null则不打印子树
void PrintBBSTreeV4(BBSTree &T, int dep);
//合并
void MergeBBSTree(BBSTree &T1, BBSTree &T2);//合并(简单合并，把T2元素逐个插入到T1)
void MergeBBSTreeV2(BBSTree &T1, BBSTree &T2);//合并(简单合并，把T2元素逐个插入到T1，显示插入过程)

//分裂
void splitBBSTree(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2);//分裂函数
void splitBBSTreeV2(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2);//分裂函数(显示步骤版)
//分裂(高级分裂但未平衡)
void splitBBSTree_sp(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2);

#endif // BBSTNODE_H_INCLUDED
