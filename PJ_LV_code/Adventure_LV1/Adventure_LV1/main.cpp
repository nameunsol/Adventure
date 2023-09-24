#include <iostream>
#include<cmath>
using namespace std;


int* list;
int* seg_tree;

int Construct_tree(int* list, int start, int end, int* seg_tree, int current)
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

int* Seg_tree_const(int* list, int n)
{
	float height = log(n);
	float t_size = 2 * pow(2, height) - 1;
	seg_tree = new int[t_size];
	Construct_tree(list, 0, n - 1, seg_tree, 0);
	return seg_tree;
}

//세그먼트 트리에서 특정 부분의 합을 구하는 함수
int Query_sum(int* seg_tree, int start, int end, int q_s, int q_e, int current)
{
	if (q_s <= start && q_e >= end)
	{
		return seg_tree[current];
	}
	if (end < q_s || start > q_e)
	{
		return 0;
	}
	int mid = start + (end - start) / 2;
	int child = 2 * current;
	return Query_sum(seg_tree, start, mid, q_s, q_e, child + 1) +
		Query_sum(seg_tree, mid + 1, end, q_s, q_e, child + 2);
}

// 세그먼트 트리에서 특정 위치의 값을 조회하는 함수
int Get_query(int* seg_tree, int n, int q_s, int q_e, int current)
{
	if (q_s<0 || q_e > n - 1 || q_e > q_s)return -1;
	int sum = Query_sum(seg_tree, 0, n - 1, q_s, q_s, current);
	return sum;
}

int* Segtree_update(int* seg_tree, int start, int end, int i, int d_value, int current)
{
	if (i < start || i > end)
	{
		return NULL;
	}
	seg_tree[current] = seg_tree[current] + d_value;
	if (start != end)
	{
		int mid = start + (end - start) / 2;
		int child = 2 * current;
		Segtree_update(seg_tree, start, mid, i, d_value, child + 1);
		Segtree_update(seg_tree, mid + 1, end, i, d_value, child + 2);
	}

	return seg_tree;
}

int main()
{
	int n, end;

	cout << "배열 크기 입력: ";
	cin >> n;
	list = new int[n];
	end = n - 1;

	cout << "배열 값 입력: ";
	for (int i = 0; i < n; i++)
	{
		cin >> list[i];
	}

	Seg_tree_const(list, n);
	
	cout << "세그먼트 트리 출력: ";
	
	cout << "원하는 부분합 위치와 값(start, end): " << endl;
	int a, b;
	cin >> a >> b;
	int sum = Query_sum(seg_tree, 0, end, a, b, 0);
	cout << "부분합: " << sum << endl;
	
	int getq = Get_query(seg_tree, n, 3, 3, 0);
	cout << "Get Query" << getq << endl;

	cout << "변경할 위치와 값: ";
	int date;
	int dvalue;
	cin >> date >> dvalue;
	Segtree_update(seg_tree, 0, end, date, dvalue, 0);
	int t = Get_query(seg_tree, n, date, date, 0);
	cout << t;
	
	return 0;
}