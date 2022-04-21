#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

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

void rquick_sort(vector<int>& data, int left, int right, stats& res)
{
	int l = left;
	int r = right;
	int cur = data[left];
	while (left < right)
	{
		while ((data[right] >= cur) && (left < right))
		{
			res.comparison_count++;
			right--;
		}
		if (left < right)
		{
			data[left] = data[right];
			res.copy_count++;
			left++;
		}
		while ((data[left] <= cur) && (left < right))
		{
			res.comparison_count++;
			left++;
		}
		if (left < right)
		{
			data[right] = data[left];
			res.copy_count++;
			right--;
		}
	}
	data[left] = cur;
	cur = left;
	left = l;
	right = r;
	if (left < cur)
		rquick_sort(data, left, cur - 1, res);
	if (right > cur)
		rquick_sort(data, cur + 1, right, res);
}

stats quick_sort(vector<int>& data)
{
	int left = 0;
	int right = data.size() - 1;
	stats res;
	rquick_sort(data, left, right, res);
	return res;
}

void heap(vector<int>& data, int n, int i, stats& res)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < n && data[l] > data[largest])
	{
		res.comparison_count++;
		largest = l;
	}

	if (r < n && data[r] > data[largest])
	{
		res.comparison_count++;
		largest = r;
	}

	if (largest != i) {
		int tmp = data[largest];
		data[largest] = data[i];
		data[i] = tmp;
		res.copy_count++;
		heap(data, n, largest, res);
	}
}

stats heap_sort(vector<int>& data) //сложность примерно верная
{
	stats res;
	for (int i = data.size() / 2 - 1; i >= 0; i--)
		heap(data, data.size(), i, res);

	for (int i = data.size() - 1; i >= 0; i--) {
		//res.copy_count++;
		int tmp = data[0];
		data[0] = data[i];
		data[i] = tmp;
		heap(data, i, 0, res);
	}
	return res;
}

int random()
{
	return round(rand() % 21);
}

int main()
{
	const int size = 1000;
	const int count = 100;
	stats results[count];
	vector<vector<int>> ch_arr[count];
	for (int i = 0; i < count; i++)
	{
		vector<int> v(size);
		generate(v.begin(), v.end(), random);
		ch_arr->push_back(v);
	}

	for (int i = 0; i < count; i++)
	{
		results[i] = quick_sort(ch_arr->at(i));
	}

	int sum_comparison = 0;
	int sum_copy = 0;
	for (int i = 0; i < count; i++)
	{
		sum_comparison += results[i].comparison_count;
		sum_copy += results[i].copy_count;
	}
	sum_comparison = sum_comparison / count;
	sum_copy = sum_copy / count;
	cout << sum_comparison << ' ' << sum_copy;
}