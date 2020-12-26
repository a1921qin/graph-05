#ifndef __GRAPH_H__
#define __GRAPH_H__
#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_VERTEX 100
 typedef char VertexType;//顶点类型
 typedef int EdgeType;//边上权值类型
//边表结点数据结构
 typedef struct EdgeNode
{
		int vexIndex;//顶点下标
				EdgeType weight;//权值
					struct EdgeNode* next;	//指向下一个结点
}EdgeNode;
//顶点表数据结构
typedef struct VextexNode
{
		VertexType data;
			EdgeNode* first;//边表第一个结点
}VextexNode,AdjList[MAX_VERTEX];
 
typedef struct GraphAdjList
{
		AdjList list;
			int vexNum, edgeNun;//顶点，边 的数量
}GraphAdjList;

typedef int EleType; 
typedef enum { ERROR, OK } Status;
typedef enum {FALSE,TRUE} Boolean;
 
//队列结点
typedef struct QueueNode
{
		EleType data;
			struct QueueNode* next;
}QueueNode;
 
//队列
typedef struct Queue
{
		QueueNode* front;
			QueueNode* tail;
}Queue;
 
//队列初始化
void InitQueue(Queue* queue);
 
//入队
int EnQueue(Queue* queue, EleType data);
 
//出队
int DeQueue(Queue* queue, EleType* data);
 
//队列是否为空
int EmptyQueue(Queue* queue);

GraphAdjList* CreateGraphAdjList();
void PrintGraphAdjList(GraphAdjList* graph);
void VisitGraphAdjListVertex(VertexType data);
void DFTGraphAdjList(GraphAdjList* graph,int vexIndex);
void TraverseGraphAdjList(GraphAdjList* graph);
void BFTGraphAdjList(GraphAdjList* graph);

#endif
