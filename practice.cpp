#include "public.h"
using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;

int reverse(int x) {
	bool non_negative = true;
	if (x == -2147483647 - 1)
		return 0;
	//对int类型整数的最大值定义为2147483647，最小值为-2147483648(在climits头文件中)
	//因此直接写-2147483648会出现错误，因为2147483648直接量超过了int的范围
	//若输入为-2147483647，那么下面的取相反数运算会溢出，这也是唯一一种输入取相反数会直接导致溢出的情况，因此需要提前处理
	//后续还需要处理取反导致溢出的情况
	if (x < 0) {
		non_negative = false;
		x = -x;
	}
	int result = 0;
	string s;
	double divide = 1.0;
	while (1) {
		int temp = static_cast<int>(x / divide) % 10;
		s += (temp + '0');
		divide *= 10.0;
		if (divide > x)
			break;
	}
	//去掉前导0
	string temp = s;
	for (auto &c : temp) {
		if (c == '0')
			s.erase(s.begin());
		else
			break;
	}
	if (s.size() > 10)
		return 0;
	else if (s.size() == 10 && s > to_string(2147483647) && non_negative)
		return 0;
	else if (s.size() == 10 && s > to_string(2147483648) && !non_negative)
		return 0;
	//转化为整数
	for (int i = 0; i < s.size(); i++)
		result += static_cast<int>((s[i] - '0') * pow(10, s.size() - 1 - i));
	if (non_negative)
		return result;
	else
		return -result;
	
}

string convert(string s, int numRows) {
	//brutal solution，复杂度为O(n)，而且会用到各种if判断，但应该任何算法都不能将复杂度量级降低
	//先确定第一列的元素，其后一个元素的下标随着i = 1, 2, ...依次为(2 * numRows - 2) * i - 当前元素下标
	string result;
	if (numRows == 1)
		return s;
	else {
		for (int i = 0; i < numRows; i++) {
			result += s[i];
			//加入当前元素
			int j = 1;
			int pos = i;
			int temp;
			while ((temp = (2 * numRows - 2) * j - pos) < s.size()) {
				j++;
				if (temp == pos)
					continue;
				else
					pos = temp;
				result += s[pos];
			}
		}
		return result;
	}
}

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