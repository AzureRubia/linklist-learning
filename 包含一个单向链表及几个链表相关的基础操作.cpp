#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS 1
/*update_of_version2:�����  @�ƺ�  ���ֵ�bug���ˣ� �����һ������ 
 *update_of_version3:�����  @�е�is  ���ֵ�bug���� 
 *update_of_version4:�����  @�е�is  ���ֵ�bug���� 
 *update_of_version5:�����  @�ƺ�  ���ֵ�bug����
 update_of_version6:�����  ����  ���ֵ�bug
 */
 
typedef struct _node{
	int number;
	struct _node *next;
}node;/*��typedef��һ����ͬ������������������*/


int cmp(const void *a,const void *b);/*���ŵıȽϺ���*/

void node_delate_one_target(node **head,int target);/*�ڵ�ɾ������(����)*/


void node_delate_all_target(node **head,int target);/*�ڵ�ɾ������(����Ŀ��)*/

void Node_free(node* list);/*�����������*/


void Node_insert(node **head,int data);/*��һ������������в���*/



void node_sort(node* head);/*������������*/


void node_add(node **head,int number);/*�ڵ���Ӻ���*/


int main()
{
	char c=0;
	int number = -1;
	node *rear_q = NULL;
	node *head=NULL;/*������һ���ڵ�*/
	
	printf("����һ�����֣�-1�������Ĳ����������\n");
	do
	{
		scanf("%d",&number);
		if(number != -1)
		{
			node_add(&head,number);/*�����ڵ�*/
		}
		else
		{
			while(  (c=getchar()) != EOF && c != '\n'   );/*���һ��ʼ������-1������Ļ������ڵ����ݻ������һ��scanf����һ������Ϊ�����������*/
		}
	} while ( number != -1);/*ֱ������-1��ֹͣ*/
	
	node_sort(head);
	printf("�������\n");
	
	printf("ѡ��һ������ɾ��\n");
	scanf("%d",&number);
	node_delate_all_target(&head,number);/*����ɾ��������*/
	for(rear_q = head;rear_q;rear_q = rear_q->next)
	{
		printf("%d",rear_q->number);/*�����нڵ㶼��ʾ����*/
	}
	
	
	printf("\nѡ��һ�����ֲ���\n");
	scanf("%d",&number);
	Node_insert(&head,number);/*��*/
	printf("�����ǣ�\n");
	for( rear_q = head ; rear_q ; rear_q = rear_q->next)
	{
		printf("%d",rear_q->number);/*�����нڵ㶼��ʾ����*/
	}
	
	Node_free(head);/*�������*/
	system("pause");
	return 0;
}

int cmp(const void *a,const void *b)/*���ŵıȽϺ���*/
{
	return *(int*)a - *(int*)b;
}



void node_delate_one_target(node **head,int target)	/*�ڵ�ɾ������(����)*/
{
	if(!head) return;
	node *ahead_p=NULL,*rear_q=NULL;
	for( ahead_p=*head ; ahead_p ; rear_q = ahead_p,ahead_p = ahead_p->next)
	{
		if( ahead_p->number == target )
		{
			if(rear_q)/*��Ҫɾ���������ڵ�һλʱ*/
			{
				rear_q->next=ahead_p->next;
			}
			else/*��ֹ��Ҫɾ���������ڵ�һλ*/
			{
				*head=ahead_p->next;
				free(ahead_p);
				ahead_p=*head;
				continue;
			}
			free(rear_q);
			break; 
		}
	}
}
void node_delate_all_target(node **head,int target)/*�ڵ�ɾ������(����Ŀ��)*/
{
	if(!*head) return;
	node *ahead_p=NULL;
	node *rear_q=NULL;
	for( ahead_p = *head ; ahead_p ;	)
	{
		if( ahead_p->number == target )
		{
			if(ahead_p->next == NULL)/*��Ҫɾ������ĩβʱ*/
			{
				free(ahead_p);
				rear_q->next = NULL;
				return;
			}
			else if(rear_q)/*��Ҫɾ���������м�ʱ*/
			{
				rear_q->next=ahead_p->next;
				free(ahead_p);
				ahead_p=rear_q;
			}
			else if(!rear_q)/*��Ҫɾ���������ڵ�һλʱ*/
			{
				*head=ahead_p->next;
				free(ahead_p);
				ahead_p=*head;
			}
			continue; 
		}
		rear_q = ahead_p;
		ahead_p = ahead_p->next;
	}
}

void Node_free(node* list)/*�����������*/
{
	if(!list) return;
	node *next = NULL;
	while(list)
	{
		next=list->next;
		free(list);
		list=next;
	}
}
void Node_insert(node **head,int data)/*��һ������������в���*/
{
	node *ahead_p = *head;
	node *rear_q = NULL;
	node *insert = (node*)malloc(1*sizeof(node));
	
	insert->number=data;
	
	if(!*head)/*����������*/
	{
		*head = insert;
		insert -> next = 0;
		return;
	}
	if( insert->number < ahead_p ->number )/*data����Сֵ�����*/
	{
		insert -> next = *head;
		*head = insert;
		return;
	}
	for(   ;ahead_p;rear_q = ahead_p,ahead_p = ahead_p->next)/*�������*/
	{
		if( data <= ahead_p->number)
		{
			insert->next = ahead_p;
			rear_q->next = insert;
			return;
		}
	}
	if(data >= rear_q->number )/*data�����ֵ�����*/
	{
		rear_q->next = insert;
		insert->next = NULL;
	}
}


void node_sort(node* head)/*������������*/
{
	if(!head) return;
	int count = 0;
	node *rear_q = 0;
	for( rear_q = head ; rear_q ; rear_q = rear_q->next )
	{
		count++;
	}
	int *ahead_p = (int*)calloc(count,sizeof(int));/*�����е����ݷŽ�����֮��������*/
	count=0;
	for(rear_q = head ; rear_q ; rear_q = rear_q->next , count++)
	{
		*(ahead_p+count)=rear_q->number; 
	}
	qsort(ahead_p,count,sizeof(int),cmp);
	count=0;
	for( rear_q = head;rear_q;rear_q = rear_q->next,count++ )
	{
		rear_q->number = ahead_p[count];
	}
	free(ahead_p);
}

void node_add(node **head,int number)/*�ڵ���Ӻ���*/
{
	node *ahead_p = (node*)calloc(1,sizeof(node));/*������һ���м�ڵ㣬��ʱ�Ľڵ�׼ȷ��˵ֻ��һ�鲻֪��������Ŀռ䣬��û��ͨ��ָ��ҵ�������*/
	if(ahead_p == NULL)
	{
		printf("\nerror!\n");/*�������ռ�ʧ��*/
		return;//�������κζ����� 
	}
	node *last = *head;/*һ��ָ��ͷ�ڵ��ָ��*/
	ahead_p->number = number;/*���м�ڵ㸳ֵ*/
	ahead_p->next = NULL;/*βָ��*/
	if(last)/*������ָ�벻��βָ�룬����������ֹͷ�ڵ���ôһ��������һ���������ʼ��ʱ���Ǹ�ahead_p��û����ȥ��*/
	{
	
		while( last -> next)
		{
			last = last->next;/*ͨ��ָ��һ�ڽ���Ծ��ֱ��last���β�ڵ�*/
		}
		last->next = ahead_p;/*��ahead_p��������*/
	}
	else
	{
		*head=ahead_p;/*��һ��ֻ�ڸտ�ʼΪ�������ʱ����Ч����ahead_p����ȥ*/
	}
}
