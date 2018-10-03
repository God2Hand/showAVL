#ifndef BBSTNODE_H_INCLUDED
#define BBSTNODE_H_INCLUDED

//Ԥ���峣��������
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERLOW -1
#define LH +1   //���������������ߣ�������
#define EH 0    //���������ȸߣ���Ƶȸ�
#define RH -1   //���������������ߣ�����Ҹ�
typedef int Status; //��������ֵ���ͣ���ʾ�������״̬
typedef int ElemType;    //�����������ͣ�������������ݣ��ɸ�����Ҫ�����޸�
typedef int KeyType;    //�ؼ�����ɸ�����Ҫ�����޸�
typedef struct
{
    KeyType key;    //�ؼ�����
    ElemType elem;  //��Ҫ������
} RecordType,RcdType;//����������

typedef struct BBSTNode
{
    RcdType data;   //����Ԫ��
    int bf; //ƽ������
    struct BBSTNode *lchild, *rchild;   //���Һ���ָ��
} *BBSTree; //ƽ�������

void R_Rotate(BBSTree &p);  //����Сʧ����������������Ϊƽ���������ʧ�����ʹ��
void L_Rotate(BBSTree &p);  //����Сʧ����������������Ϊƽ���������ʧ�����ʹ��
void LeftBalance(BBSTree &T);   //ƽ�����������ƽ�⴦��
void RightBalance(BBSTree &T);  //ƽ�����������ƽ�⴦��

void visit(RcdType r);  //���������ĺ���������ú�����Ϊ�˸ı��������͸�����
void pKey(RcdType r);   //���������ĺ���������ú�����Ϊ�˷����û��޸�

//���²��Ǹ����õĹ���
Status InitBBST(BBSTree &T); //��ʼ������ʵ���Բ���

Status DestroyBBST(BBSTree &T);  //��ƽ�������T���ڣ�������T

BBSTree SearchBBST(BBSTree T, KeyType key); //��ָ���ؼ��ֲ��ң����ؽ�㣬�������ڣ��򷵻�NULL
BBSTree SearchBBST_V2(BBSTree T, KeyType key);  //����·�����������ҵ�����������·���ϵĹؼ���
Status InsertAVL(BBSTree &T, RcdType e, Status &taller);    //��ƽ�������T�в�����ֵΪe.key�Ľ�㣬����뵽T
Status DeleteAVL(BBSTree &T, KeyType key, Status &shorter); //��ƽ�������T�д���ֵΪkey�Ľ�㣬��ɾ��

int BBSTreeDepth(BBSTree T);//���ض�������ȣ�TΪ������ָ��

//

//�������ʾ
void PrintBBSTreeV3(BBSTree &T, int dep);//�������ʽ��ʾ������������ͨ�����ֱ�ۣ���������������������������µĵݹ���ʾ������
void PrintBBSTreeV2(BBSTree &T, int dep);//�������ʽ��ʾ�������ؼ��֣����ݣ�������ͨ�����ֱ�ۣ�������롰\t������|--������ʶ�𡣣�
void PrintBBSTree(BBSTree &T, int dep);//�������ʽ��ʾ��������ԭʼ�������ʾ����������ǳ��������ã���
//�������ʽ��ʾ�������ؼ��֣����ݣ�������ͨ�����ֱ�ۣ�������롰\t������|--������ʶ�𡣲��Ҵ˰汾��ӡ�˿���������Ϊnull��//���ҵ�����������Ϊnull�򲻴�ӡ����
void PrintBBSTreeV4(BBSTree &T, int dep);
//�ϲ�
void MergeBBSTree(BBSTree &T1, BBSTree &T2);//�ϲ�(�򵥺ϲ�����T2Ԫ��������뵽T1)
void MergeBBSTreeV2(BBSTree &T1, BBSTree &T2);//�ϲ�(�򵥺ϲ�����T2Ԫ��������뵽T1����ʾ�������)

//����
void splitBBSTree(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2);//���Ѻ���
void splitBBSTreeV2(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2);//���Ѻ���(��ʾ�����)
//����(�߼����ѵ�δƽ��)
void splitBBSTree_sp(BBSTree T, KeyType key, BBSTree &T1, BBSTree &T2);

#endif // BBSTNODE_H_INCLUDED
