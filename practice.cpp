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
	//��int�������������ֵ����Ϊ2147483647����СֵΪ-2147483648(��climitsͷ�ļ���)
	//���ֱ��д-2147483648����ִ�����Ϊ2147483648ֱ����������int�ķ�Χ
	//������Ϊ-2147483647����ô�����ȡ�෴��������������Ҳ��Ψһһ������ȡ�෴����ֱ�ӵ������������������Ҫ��ǰ����
	//��������Ҫ����ȡ��������������
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
	//ȥ��ǰ��0
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
	//ת��Ϊ����
	for (int i = 0; i < s.size(); i++)
		result += static_cast<int>((s[i] - '0') * pow(10, s.size() - 1 - i));
	if (non_negative)
		return result;
	else
		return -result;
	
}

string convert(string s, int numRows) {
	//brutal solution�����Ӷ�ΪO(n)�����һ��õ�����if�жϣ���Ӧ���κ��㷨�����ܽ����Ӷ���������
	//��ȷ����һ�е�Ԫ�أ����һ��Ԫ�ص��±�����i = 1, 2, ...����Ϊ(2 * numRows - 2) * i - ��ǰԪ���±�
	string result;
	if (numRows == 1)
		return s;
	else {
		for (int i = 0; i < numRows; i++) {
			result += s[i];
			//���뵱ǰԪ��
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

//bubble sort, һ��һ�˽���
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
	cout << "���Ϊ: ";
	for (auto &num : array)
		cout << num << " ";
	cout << endl;
}

//insert sort, �ؼ�����ÿһ��ǰ���Ԫ���Ѿ��������
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

	cout << "���Ϊ: ";
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
	cout << "���Ϊ: ";
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
		//��������Ԫ�ض���keyС�����
		int temp = array[left];
		array[left] = key;
		array[end] = temp;
	}
	return left;
}