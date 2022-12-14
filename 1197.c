#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int v, e;
typedef struct _node{
  int vertex;
  int value;
  struct _node *next;
} node;
node **graph;
void link(int veri, int verj, int val)
{
  node *a = graph[veri];
  while(a->next!=NULL)
  {
    a = a->next;
  }
  node *temp = (node *)malloc(sizeof(node));
  temp->vertex = verj;
  temp->value = val;
  temp->next = NULL;
  a->next = temp;

  node *b = graph[verj];
  while(b->next!=NULL)
  {
    b = b->next;
  }
  node *temp2 = (node *)malloc(sizeof(node));
  temp2->vertex = veri;
  temp2->value = val;
  temp2->next = NULL;
  b->next = temp2;
  
}
int valueij(int veri, int verj)
{
  node *a = graph[veri];

  while(a!=NULL)
  {
    if(a->vertex==verj)
    {
      return a->value;
    }
    else
    {
      a = a->next;
    }
  }
  return 0;

}
int prim(int r)
{
  int* minheap=(int*)calloc(v+1, sizeof(int)); // 사실 minheap 아님
  int minheap_size = 0;
  int *d = (int *)malloc(sizeof(int)*(v+1));
  long long min_prim = 0;
  memset(d, 1000000, (v + 1) * sizeof(int));
  for (int value = 1; value <= v;value++) // minheap에 각각 값 집어넣음
  {
    minheap_size = minheap_size + 1;
    minheap[minheap_size] = value;
    
  }
  d[r] = 0;
  int temp = minheap[1];
  minheap[1] = minheap[r];
  minheap[r] = temp; // r을 minheap의 첫번째로 올림, 나머지는 값 INF로 same
  while(minheap_size!=0)
  {
    int u = minheap[1];
    min_prim = min_prim + d[u];
    minheap_size = minheap_size - 1;
    for (int i = 1; i <= minheap_size;i++)
    {
      minheap[i] = minheap[i + 1];
    }
    // Heap으로 만듦(정확하게는 아님: 최솟값만 위로 올려주는 과정), a[i]는 Heap에서 최소
    for (int j = minheap_size/ 2; j >= 1;j--)
    {
      if(2*j==minheap_size) // 마지막, 자식노드가 왼쪽만 존재
      {
        if(d[minheap[2*j]]<d[minheap[j]])
        {
          int temp = minheap[2 * j];
          minheap[2 * j] = minheap[j];
          minheap[j] = temp;
        }
      }
      else
      {
        if(d[minheap[2*j]]<d[minheap[j]]&&d[minheap[2*j]]<=d[minheap[2*j+1]]) // 왼쪽 자식노드가 최소
        {
          int temp = minheap[2 * j];
          minheap[2 * j] = minheap[j];
          minheap[j] = temp;
        }
        else if(d[minheap[2*j+1]]<d[minheap[j]]&&d[minheap[2*j+1]]<=d[minheap[2*j]]) // 오른쪽 자식노드가 최소
        {
          int temp = minheap[2 * j+1];
          minheap[2 * j+1] = minheap[j];
          minheap[j] = temp;
        }
      }
    }

    for (int i = 1; i <= minheap_size;i++)
    {
      int valueijthingy = valueij(u, minheap[i]);
      if(valueijthingy!=0&&valueijthingy<d[minheap[i]]) // 연결된 점 & d change
      {
        d[minheap[i]] = valueijthingy;
      }
    }
  }
  // 만약 값이 int를 넘어가면, 그냥 int 최대를 반환
  if(min_prim>2147483647)
  {
    return 2147483647;
  }
  else
  {
    return min_prim;
  }
}
int main(void)
{
  scanf("%d %d", &v, &e);
  graph=(node **)malloc((v+1)*sizeof(node*));
  for (int i = 1; i <= v;i++)
  {
    graph[i] = (node *)malloc(sizeof(node));
    graph[i]->vertex = 0;
    graph[i]->value = 0;
    graph[i]->next = NULL;
  }
  for (int i = 0; i <= e - 1; i++)
  {
    int j;
    int k;
    int value_main;
    scanf("%d", &j);
    scanf("%d", &k);
    scanf("%d", &value_main);
    link(j, k, value_main);
  }
  int min = 2147483647;
  for (int i = 1; i <= v;i++)
  {
    int i_value = prim(i);
    if(i_value<min)
    {
      min = i_value;
    }
  }
  printf("%d", min);
  return 0;
}