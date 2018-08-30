#include "public.h"
using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;


//bubble sort, 一趟一趟进行
void bubbleSort(vector<int> &array) {
	for(int i = 0; i < array.size() - 1; i++)
		//bubble needs array.size() - 1 times
		for (int j = 0; j < array.size() - 1 - i; j++) {
			//swap until last sorted element
			if (array[j] > array[j + 1]) {
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	cout << "结果为: ";
	for (auto &num : array)
		cout << num << " ";
	cout << endl;
}

//insert sort, 关键在于每一轮前面的元素已经排序完毕
void insertSort(vector<int> &array) {
	for (int i = 1; i < array.size(); i++) 
		for (int j = i; j > 0; j--) {
			//element 0 to i - 1 has been sorted well
			if (array[j] < array[j - 1]) {
				int temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
			}
		}

	cout << "结果为: ";
	for (auto &num : array)
		cout << num << " ";
	cout << endl;
}

//select sort, the simpliest
void selectSort(vector<int> &array) {
	for (int i = 0; i < array.size() - 1; i++) {
		int pos = i;
		//record the position of the (i + 1)st small element
		for (int j = i + 1; j < array.size(); j++) 
			if (array[j] < array[pos])
				pos = j;
		int temp = array[pos];
		array[pos] = array[i];
		array[i] = temp;
	}
	cout << "结果为: ";
	for (auto &num : array)
		cout << num << " ";
	cout << endl;
}

//quick sort
void quickSort(vector<int> &array, int begin, int end) {
	if (begin >= end)
		return;
	//current part has zero or only one element and there is no need to sort

	int pos = findPos(array, begin, end);
	//find the position and divide this part

	quickSort(array, begin, pos - 1);
	quickSort(array, pos + 1, end);
	//recursive call
}

int findPos(vector<int> &array, int begin, int end) {
	int left = begin, right = end - 1, key = array[end];
	while (left < right) {
		while (left < right && array[left] <= key)
			left++;
		while (left < right && array[right] >= key)
			right--;
		int temp = array[left];
		array[left] = array[right];
		array[right] = temp;
	}
	if (array[left] >= key) {
		//处理所有元素都比key小的情况
		int temp = array[left];
		array[left] = key;
		array[end] = temp;
	}
	return left;
}