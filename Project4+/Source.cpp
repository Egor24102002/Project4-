
#define _CRT_NONSTDC_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define HEADER ("Лабораторная работа №4\nВыполнил: Пантюшов Е.И.\n")

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stack>
using namespace std;
struct node
{
	int vertex;
	struct node* next;
};

struct Graph
{
	int numVertices;
	struct node** adjList;
};

struct node* createNode(int v)
{
	struct node* newNode = (node*)malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}

struct Graph* createGraph(int vertices)
{
	struct Graph* graph = (Graph*)malloc(sizeof(struct Graph));
	graph->numVertices = vertices;
	graph->adjList =(node**)malloc(vertices * sizeof(struct node*));
	for (int i = 0; i < vertices; i++)
		graph->adjList[i] = NULL;
	return graph;
}

void addEdge(struct Graph* graph, int i, int j)
{
	struct node* newNode = createNode(j);
	if (graph->adjList[i] == NULL)
	{
		graph->adjList[i] = newNode;
		newNode = NULL;
	}
	struct node* temp = graph->adjList[i];
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = newNode;

	newNode = createNode(i);
	if (graph->adjList[j] == NULL)
	{
		graph->adjList[j] = newNode;
		newNode = NULL;
	}
	temp = graph->adjList[j];
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = newNode;
}

void printGraph(struct Graph* graph)
{
	for (int i = 0; i < graph->numVertices; i++)
	{
		struct node* temp = graph->adjList[i];
		printf("%d-я вершина: ", i);
		while (temp)
		{
			printf("%d ", temp->vertex);
			temp = temp->next;
		}
		printf("\n");
	}
}

void dfs(int** G, int* NUM, int v, int n)
{
	NUM[v] = true;
	printf(" %d ", v);
	for (int i = 0; i < n; i++)
	{
		if ((G[v][i] == 1) && (NUM[i] == false))
		{
			dfs(G, NUM, i, n);
		}
	}
}

void dfs_list(struct Graph* graph, int* NUM, int v, int n)
{
	struct node* list = graph->adjList[v];
	NUM[v] = true;
	printf(" %d ", v);
	while (list)
	{
		if (NUM[list->vertex] == false)
		{
			dfs_list(graph, NUM, list->vertex, n);
		}
		list = list->next;
	}
}

void task_1_1(int** G, int n)
{
	printf("\nЗадание 1.\n\nПункт 1.\nМатрица смежности:\n");
	for (int i = 0; i < n; i++)
	{
		G[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++)
		{
			G[i][j] = rand() % 2;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				G[i][j] = 0;
			}
			else
			{
				G[i][j] = G[j][i];
			}
			printf(" %d ", G[i][j]);
		}
		printf("\n");
	}
}

void task_1_2(int** G, int n)
{
	int* NUM = (int*)malloc(n * sizeof(int));
	int v;
	for (int i = 0; i < n; i++)
	{
		NUM[i] = false;
	}
	printf("\nПункт 2.\nВведите точку входа: ");
	scanf("%d", &v);
	printf("Результат работы алгоритма обхода в глубину(матрица): ");
	dfs(G, NUM, v, n);
	free(NUM);
}

void task_1_3(struct Graph* graph, int n, int** G)
{
	struct node** node = graph->adjList;
	int v;
	int* NUM = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((G[i][j] == 1) && (i < j))
			{
				addEdge(graph, i, j);
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		NUM[i] = false;
	}
	printf("\n\nПункт 3.\nСписок смежности: \n");
	printGraph(graph);
	printf("Введите точку входа: ");
	scanf("%d", &v);
	printf("Результат работы алгоритма обхода в глубину(список): ");
	dfs_list(graph, NUM, v, n);
	printf("\n\n");
	free(NUM);
}

void task_2_1(int** G, int n)
{
	int* NUM = (int*)malloc(n * sizeof(int));
	printf("Задание 2.\n\nПункт 1.\n\nВведите точку входа: ");
	int v;
	scanf("%d", &v);
	printf("Результат работы алгоритма обхода в глубину(матрица)(без рекурсии): ");
	stack <int> stk;
	for (int i = 0; i < n; i++)
	{
		NUM[i] = 0;
	}
	stk.push(v);
	while (!stk.empty())
	{
		v = stk.top();
		stk.pop();
		if (NUM[v] == 2)
			continue;
		NUM[v] = 2;
		for (int j = n - 1; j >= 0; j--)
		{
			if ((G[v][j] == 1) && (NUM[j] != 2))
			{
				stk.push(j);
				NUM[j] = 1;
			}
		}
		printf("%d ", v);
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	printf(HEADER);
	printf("Введите размерность матрицы: ");
	int n;
	scanf("%d", &n);
	int** G = (int**)malloc(n * sizeof(int*));
	struct Graph* graph = createGraph(n);
	task_1_1(G, n);
	task_1_2(G, n);
	task_1_3(graph, n, G);
	task_2_1(G, n);
	free(G);
	system("PAUSE");
	return 0;
}