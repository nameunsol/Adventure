#include <iostream>
#include<cmath>
using namespace std;


int* list;
int* seg_tree;



int Construct_tree(int* list,int start,int end,int* seg_tree,int current)
{
	if (start == end)
	{
		seg_tree[current] = list[start];
		return list[start];
	}
	int mid = start + (end - start) / 2;
	int child = 2 * current;
	seg_tree[current] = Construct_tree(list, start, mid, seg_tree, child + 1) +
		Construct_tree(list, mid + 1, end, seg_tree, child + 2);
		return seg_tree[current];
}

int* Seg_tree_const(int* list,int n)
{
	float height = log(n);
	float t_size = 2 * pow(2, height) - 1;
	seg_tree = new int[t_size];
	Construct_tree(list, 0, n - 1, seg_tree, 0);
	return seg_tree;
}

int Query_sum(int* seg_tree,int start,int end,int q_s,int q_e,int current)
{
	if (q_s <= start && end >= end)
	{
		return seg_tree[current];
	}
	if (end<q_s || start>q_e)
	{
		return 0;
	}
	int mid = start + (end - start);
	int child = 2 * current;
	return Query_sum(seg_tree, start, mid, q_s, q_e, child + 1) +
		   Query_sum(seg_tree, mid + 1, end, q_s, q_e, child + 2);
}

int Get_query(int* seg_tree,int n,int q_s,int q_e)
{
	if (q_s<0 || q_e>n - 1 || q_e > q_s)return -1;
	int sum = Query_sum(seg_tree, 0, n - 1, q_s, q_s, current);
	return sum;
}

int main()
{
	int n;
	cin >> n;
	list = new int[n];


	
	return 0;
}