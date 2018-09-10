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

void generate(vector<int> &v, int num, int start, int end) {
	//示例，v的大小为pow(2, n - 2) - 1
	//给定num = 3，输出3
	//给定num = 4，输出3，4，3
	//给定num = 5，输出3，4，3，5，3，4，3
	//给定num = 6，输出3，4，3，5，3，4，3，6，3，4，3，5，3，4，3
	int mid = (start + end) / 2;
	v[mid] = num;
	if (start == end)
		return;
	else {
		//分别处理左半部分和右半部分
		generate(v, num - 1, start, mid - 1);
		generate(v, num - 1, mid + 1, end);
	}
}

void printGray(int N) {
	vector<int> poses(static_cast<int>(pow(2, N) - 1), 0);
	vector<int> pads(static_cast<int>(pow(2, ((N == 1) ? 2 : N) - 2) - 1), 0);
	if (N != 2)
		generate(pads, N, 0, pads.size() - 1);
	//构造字符替换位置
	if (N == 1)
		poses[0] = 1;
	else {
		int i = 0;
		int j = 0;
		while (1) {
			poses[i] = 1;
			poses[i + 1] = 2;
			poses[i + 2] = 1;
			i = i + 3;
			if (i >= poses.size())
				break;
			poses[i] = pads[j];
			i++;
			j++;
		}
	}

	string result(N, '0');
	cout << result << endl;
	for (auto &p : poses) {
		result[p - 1] = (result[p - 1] == '0') ? '1' : '0';
		cout << result << endl;
	}
}

void getGray(vector<string> &v, int N) {
	//递归方式生成格雷码
	if (N == 1) {
		v.push_back("0");
		v.push_back("1");
	}
	else {
		vector<string> v_temp;
		getGray(v_temp, N - 1);
		//N位格雷码由N - 1位格雷码生成
		for (int i = 0; i < v_temp.size(); i++)
			v.push_back("0" + v_temp[i]);
		for (int i = v_temp.size() - 1; i >= 0; i--)
			v.push_back("1" + v_temp[i]);
	}
	return;
}


void clockwisePrint(std::vector<vector<int>> &matrix, int rows, int cols) {
	// write code here
	int row = 0, col = 0;
	int lr = cols, lc = rows - 1;
	//访问元素的个数限制
	//标记当前访问元素
	enum dir { RIGHT, DOWN, LEFT, UP };
	dir d = RIGHT;
	int count = 0;
	int count_in = 0;
	while (1) {
		switch (d) {
		case RIGHT:
			cout << matrix[row][col] << " ";
			count_in++;
			if (count_in == lr) {
				lr--;
				row++;
				count_in = 0;
				d = DOWN;
			}
			else
				col++;
			break;
		case DOWN:
			cout << matrix[row][col] << " ";
			count_in++;
			if (count_in == lc) {
				lc--;
				col--;
				count_in = 0;
				d = LEFT;
			}
			else
				row++;
			break;
		case LEFT:
			cout << matrix[row][col] << " ";
			count_in++;
			if (count_in == lr) {
				lr--;
				row--;
				count_in = 0;
				d = UP;
			}
			else
				col--;
			break;
		case UP:
			cout << matrix[row][col] << " ";
			count_in++;
			if (count_in == lc) {
				lc--;
				col++;
				count_in = 0;
				d = RIGHT;
			}
			else
				row--;
			break;
		}
		count++;
		if (count == rows * cols) {
			cout << endl;
			return;
		}
	}

}