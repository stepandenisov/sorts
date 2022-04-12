#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

stats selection_sort (vector<int>& data)
{
	stats res;
	// res.comparison_count = 0;
	int min, idx;
	for (int i = 0; i < data.size(); i++)
	{
		min = data[i];
		idx = i;
		for (int j = i; j < data.size(); j++)
		{
			if (data[j] < min)
			{
				min = data[j];
				idx = j;
			}
			res.comparison_count++;
		}
		int tmp = data[i];
		data[i] = min;
		data[idx] = tmp;
	}
	return res;
}

stats bubble_sort(vector<int>& data)
{
	stats res;
	for (int i = 0; i < data.size()-1; i++)
	{
		for (int j = data.size() - 1; j > i; j--)
		{
			res.comparison_count++;
			if (data[j - 1] > data[j])
			{
				res.copy_count++;
				int temp = data[j - 1];
				data[j - 1] = data[j];
				data[j] = temp;
			}
		}
	}
	return res;
}

stats quick_sort(vector<int>& data, int left, int right)
{
	int l = left; //����� �������
	int r = right; // ������ �������
	int cur = data[left];
	while (left < right) // ���� ������� �� ���������
	{
		while ((data[right] >= cur) && (left < right))
			right--; // �������� ������ ������� ���� ������� [right] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			data[left] = data[right]; // ���������� ������� [right] �� ����� ������������
			left++; // �������� ����� ������� ������
		}
		while ((data[left] <= cur) && (left < right))
			left++; // �������� ����� ������� ���� ������� [left] ������ [pivot]
		if (left != right) // ���� ������� �� ����������
		{
			data[right] = data[left]; // ���������� ������� [left] �� ����� [right]
			right--; // �������� ������ ������� �����
		}
	}
	data[left] = cur; // ������ ����������� ������� �� �����
	cur = left;
	left = l;
	right = r;
	if (left < cur) // ���������� �������� ���������� ��� ����� � ������ ����� �������
		quick_sort(data, left, cur - 1);
	if (right > cur)
		quick_sort(data, cur + 1, right);
	stats s;
	return s;
}


int main()
{
	vector<int> arr = {5,6,3,8};
	//stats s = bubble_sort(arr);
	stats s = quick_sort(arr, 0, arr.size()-1);
	for (auto j = arr.begin(); j != arr.end(); j++)
	{
		cout << *j << ' ';
	}
	cout << endl << s.comparison_count << endl << s.copy_count;
	return 0;
}