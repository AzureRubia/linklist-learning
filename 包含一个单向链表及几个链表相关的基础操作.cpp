#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS 1
/*update_of_version2:解决了  @云何  发现的bug和人， 添加了一个排序 
 *update_of_version3:解决了  @有点is  发现的bug和人 
 *update_of_version4:解决了  @有点is  发现的bug和人 
 *update_of_version5:解决了  @云何  发现的bug和人
 update_of_version6:解决了  本人  发现的bug
 */
 
typedef struct _node{
	int number;
	struct _node *next;
}node;/*用typedef起一个不同的类型名，方便输入*/


int cmp(const void *a,const void *b);/*快排的比较函数*/

void node_delate_one_target(node **head,int target);/*节点删除函数(单个)*/


void node_delate_all_target(node **head,int target);/*节点删除函数(所有目标)*/

void Node_free(node* list);/*链表清除函数*/


void Node_insert(node **head,int data);/*对一段升序链表进行插入*/



void node_sort(node* head);/*链表排序（升序）*/


void node_add(node **head,int number);/*节点添加函数*/


int main()
{
	char c=0;
	int number = -1;
	node *rear_q = NULL;
	node *head=NULL;/*建立第一个节点*/
	
	printf("输入一串数字，-1及其后面的不会进入链表\n");
	do
	{
		scanf("%d",&number);
		if(number != -1)
		{
			node_add(&head,number);/*创建节点*/
		}
		else
		{
			while(  (c=getchar()) != EOF && c != '\n'   );/*如果一开始就输入-1，后面的缓冲区内的数据会进入下一个scanf，这一个就是为了清除缓冲区*/
		}
	} while ( number != -1);/*直到输入-1才停止*/
	
	node_sort(head);
	printf("排序完成\n");
	
	printf("选择一个数字删除\n");
	scanf("%d",&number);
	node_delate_all_target(&head,number);/*定向删除了数字*/
	for(rear_q = head;rear_q;rear_q = rear_q->next)
	{
		printf("%d",rear_q->number);/*把所有节点都显示出来*/
	}
	
	
	printf("\n选择一个数字插入\n");
	scanf("%d",&number);
	Node_insert(&head,number);/*插*/
	printf("现在是：\n");
	for( rear_q = head ; rear_q ; rear_q = rear_q->next)
	{
		printf("%d",rear_q->number);/*把所有节点都显示出来*/
	}
	
	Node_free(head);/*清除链表*/
	system("pause");
	return 0;
}

int cmp(const void *a,const void *b)/*快排的比较函数*/
{
	return *(int*)a - *(int*)b;
}



void node_delate_one_target(node **head,int target)	/*节点删除函数(单个)*/
{
	if(!head) return;
	node *ahead_p=NULL,*rear_q=NULL;
	for( ahead_p=*head ; ahead_p ; rear_q = ahead_p,ahead_p = ahead_p->next)
	{
		if( ahead_p->number == target )
		{
			if(rear_q)/*需要删除的数不在第一位时*/
			{
				rear_q->next=ahead_p->next;
			}
			else/*防止需要删除的数就在第一位*/
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
void node_delate_all_target(node **head,int target)/*节点删除函数(所有目标)*/
{
	if(!*head) return;
	node *ahead_p=NULL;
	node *rear_q=NULL;
	for( ahead_p = *head ; ahead_p ;	)
	{
		if( ahead_p->number == target )
		{
			if(ahead_p->next == NULL)/*需要删除的在末尾时*/
			{
				free(ahead_p);
				rear_q->next = NULL;
				return;
			}
			else if(rear_q)/*需要删除的数在中间时*/
			{
				rear_q->next=ahead_p->next;
				free(ahead_p);
				ahead_p=rear_q;
			}
			else if(!rear_q)/*需要删除的数就在第一位时*/
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

void Node_free(node* list)/*链表清除函数*/
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
void Node_insert(node **head,int data)/*对一段升序链表进行插入*/
{
	node *ahead_p = *head;
	node *rear_q = NULL;
	node *insert = (node*)malloc(1*sizeof(node));
	
	insert->number=data;
	
	if(!*head)/*空链表的情况*/
	{
		*head = insert;
		insert -> next = 0;
		return;
	}
	if( insert->number < ahead_p ->number )/*data是最小值的情况*/
	{
		insert -> next = *head;
		*head = insert;
		return;
	}
	for(   ;ahead_p;rear_q = ahead_p,ahead_p = ahead_p->next)/*正常情况*/
	{
		if( data <= ahead_p->number)
		{
			insert->next = ahead_p;
			rear_q->next = insert;
			return;
		}
	}
	if(data >= rear_q->number )/*data是最大值的情况*/
	{
		rear_q->next = insert;
		insert->next = NULL;
	}
}


void node_sort(node* head)/*链表排序（升序）*/
{
	if(!head) return;
	int count = 0;
	node *rear_q = 0;
	for( rear_q = head ; rear_q ; rear_q = rear_q->next )
	{
		count++;
	}
	int *ahead_p = (int*)calloc(count,sizeof(int));/*把所有的数据放进数组之后再排序*/
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

void node_add(node **head,int number)/*节点添加函数*/
{
	node *ahead_p = (node*)calloc(1,sizeof(node));/*建立了一个中间节点，此时的节点准确来说只是一块不知道在哪里的空间，还没有通过指针挂到链表上*/
	if(ahead_p == NULL)
	{
		printf("\nerror!\n");/*假设分配空间失败*/
		return;//不返回任何东西。 
	}
	node *last = *head;/*一个指向头节点的指针*/
	ahead_p->number = number;/*给中间节点赋值*/
	ahead_p->next = NULL;/*尾指针*/
	if(last)/*如果这个指针不是尾指针，即：该链表不止头节点这么一个，不是一个空链表（最开始的时候那个ahead_p还没挂上去）*/
	{
	
		while( last -> next)
		{
			last = last->next;/*通过指针一节节跳跃，直到last变成尾节点*/
		}
		last->next = ahead_p;/*把ahead_p挂上链表*/
	}
	else
	{
		*head=ahead_p;/*这一块只在刚开始为空链表的时候生效，把ahead_p挂上去*/
	}
}
