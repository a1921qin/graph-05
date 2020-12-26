#include"graph.h"
int main(int argc, char *argv[])
{
	GraphAdjList* graph = CreateGraphAdjList();
	PrintGraphAdjList(graph);
	printf("深度优先遍历邻接表:\n");
	TraverseGraphAdjList(graph);
	printf("\n广度优先遍历邻接表:\n");
	BFTGraphAdjList(graph);
	printf("\n");
	return 0;
}
