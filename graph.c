#include"graph.h"
#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTEX 100

Boolean g_visited[MAX_VERTEX] = { 0 };//全局变量 顶点访问标志位数组

//邻接表创建无向网图
GraphAdjList* CreateGraphAdjList()
{
	GraphAdjList* graph = (GraphAdjList*)malloc(sizeof(GraphAdjList));
	int vexNum, edgeNum;
	printf("请输入顶点和边数(用逗号隔开):");
	scanf("%d,%d",&vexNum,&edgeNum);
	graph->edgeNun = edgeNum;
	graph->vexNum = vexNum;
	getchar();//消除上面的换行符
	printf("请输入顶点的值:");

	//每个单链表的尾指针数组
	EdgeNode** tailArr = (EdgeNode**)malloc(sizeof(EdgeNode*)*vexNum);
	//输入顶点值
	for (int i = 0; i < vexNum; i++)
	{
		scanf("%c", &graph->list[i].data);
		graph->list[i].first = (EdgeNode*)malloc(sizeof(EdgeNode));//创建头结点，采用尾插入
		graph->list[i].first->next = NULL;
		tailArr[i] = graph->list[i].first;
	}
	//输入边表数据
	for (int k = 0; k < edgeNum; k++)
	{
		int i, j, w;
		printf("请输入(Vi,Vj)对应的顶点下标和权值(用逗号隔开):");
		scanf("%d,%d,%d", &i, &j, &w);
		//i -> j i出度到j
		EdgeNode* edge = (EdgeNode*)malloc(sizeof(EdgeNode));//创建边结点
		edge->vexIndex = j;
		edge->weight = w;
		edge->next = NULL;
		tailArr[i]->next = edge;	//采用尾插法
		tailArr[i] = edge;

		edge = (EdgeNode*)malloc(sizeof(EdgeNode));
		edge->vexIndex = i;
		edge->weight = w;
		edge->next = NULL;
		tailArr[j]->next = edge;
		tailArr[j] = edge;
	}
	//将头结点释放
	for (int i = 0; i < vexNum; i++)
	{
		EdgeNode* head = graph->list[i].first;
		graph->list[i].first = head->next;
		free(head);
	}
	return graph;
}
//打印 邻接表的无向图
void PrintGraphAdjList(GraphAdjList* graph)
{
	printf("顶点数据:\n");
	//顶点数据
	for (int i = 0; i < graph->vexNum; i++)
	{
		printf("%c ",graph->list[i].data);
	}
	printf("\n边数据:\n");
	EdgeNode* temp = NULL;
	//边数据
	for (int i = 0; i < graph->vexNum; i++)
	{
		temp = graph->list[i].first;
		while (temp)
		{
			printf("%d\t",temp->weight);
			temp = temp->next;
		}
		printf("\n");
	}
	return;
}
//访问顶点元素
void VisitGraphAdjListVertex(VertexType data)
{
	printf("%c ", data);
	return;
}
void DFTGraphAdjList(GraphAdjList* graph,int vexIndex)
{
	//访问过不再访问
	if (g_visited[vexIndex] == TRUE)
	{
		return;
	}
	g_visited[vexIndex] = TRUE;
	VisitGraphAdjListVertex(graph->list[vexIndex].data);

	EdgeNode* node = graph->list[vexIndex].first;
	while (node)
	{
		DFTGraphAdjList(graph, node->vexIndex);
		node = node->next;
	}
	return;
}

//深度优先遍历邻接表
void TraverseGraphAdjList(GraphAdjList* graph)
{
	if (NULL == graph)
	{
		return;
	}
	for (int i = 0; i < graph->vexNum; i++)
	{
		g_visited[i] = FALSE;
	}
	for (int i = 0; i < graph->vexNum; i++)
	{
		if (g_visited[i] == FALSE)
		{
			DFTGraphAdjList(graph, i);
		}
	}

	return;
}
//广度优先遍历邻接表
void BFTGraphAdjList(GraphAdjList* graph)
{

	if (NULL == graph)
	{
		return;
	}
	Queue queue;
	InitQueue(&queue);
	//初始化顶点都没有访问过
	for (int i = 0; i < graph->vexNum; i++)
	{
		g_visited[i] = FALSE;
	}
	for (int i = 0; i < graph->vexNum; i++)
	{
		if (g_visited[i] == FALSE)
		{
			g_visited[i] = TRUE;
			VertexType vex = graph->list[i].data;
			VisitGraphAdjListVertex(vex);//访问顶点数据
			EnQueue(&queue, i);//将访问过的顶点下标入队
			while (!EmptyQueue(&queue))
			{
				int vexIndex;
				DeQueue(&queue, &vexIndex);//将访问过的顶点下标出队
				EdgeNode* node = graph->list[vexIndex].first;
				//将该节点的连接的结点且没有被访问过的结点进行访问，然后入队
				while (node != NULL && g_visited[node->vexIndex] == FALSE)
				{
					g_visited[node->vexIndex] = TRUE;
					VertexType vex = graph->list[node->vexIndex].data;
					VisitGraphAdjListVertex(vex);
					EnQueue(&queue, node->vexIndex);
					node = node->next;
				}
			}

		}
	}
	return;
}
//队列初始化
void InitQueue(Queue* queue)
{
	queue->front = NULL;
	queue->tail = NULL;
	return;
}

//入队
int EnQueue(Queue* queue, EleType data)
{
	if (NULL == queue)
	{
		return ERROR;
	}
	QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
	node->data = data;
	node->next = NULL;
	if (queue->front == NULL)
	{
		queue->front = queue->tail = node;
	}
	else
	{
		queue->tail->next = node;
		queue->tail = node;
	}
	return OK;
}
//出队
int DeQueue(Queue* queue, EleType* data)
{
	if (NULL == queue)
	{
		return ERROR;
	}
	if (!EmptyQueue(queue))
	{
		QueueNode* node = queue->front;
		*data = node->data;
		queue->front = queue->front->next;
		if (NULL != node)
		{
			free(node);
			node = NULL;
		}
	//队列的最后一个元素出队列后，tail指针也要置为空
			if (EmptyQueue(queue))
			{
				queue->tail = queue->front;
			}
	}
	return OK;
}

//队列是否为空
int EmptyQueue(Queue* queue)
{
	if (NULL == queue)
	{
		return ERROR;
	}
	if (queue->front == NULL)
	{
		return TRUE;
	}
	return FALSE;
}

