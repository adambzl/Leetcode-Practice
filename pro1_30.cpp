#include "public.h"
using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;
using std::map;
using std::unordered_map;
using std::exception;


vector<int> twoSum(vector<int>& nums, int target) {
	//����һ����ϣ�������ͬʱ���һ���Ԫ���Ƿ���ڣ������ӶȽ�ΪO(n)
	//stupid program that fucks me
	map<int, int> m;
	vector<int> result;
	auto iter = nums.cbegin();
	for (; iter != nums.cend(); iter++) {
		if (iter != nums.cbegin()) {
			int temp = target - *iter;
			if (m.find(temp) != m.end()) {
				//������ظ�ƥ�䣬��ô�������ֻ���ҵ����һ��ƥ����ֵ�λ��
				result.push_back(m[temp]);
				result.push_back(iter - nums.cbegin());
				return result;
			}
		}
		//��ƥ����ߵ�һ��Ԫ�ص��������map�в�����Ԫ��
		m[*iter] = iter - nums.cbegin();
	}
	return result;
}

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	ListNode *add1 = l1;
	ListNode *add2 = l2;
	ListNode *result = nullptr, *pos = nullptr;
	int temp = 0;
	while (add1 || add2 || temp) {
		if (add1) {
			temp += add1->val;
			add1 = add1->next;
		}
		if (add2) {
			temp += add2->val;
			add2 = add2->next;
		}
		if (!result) {
			result = new ListNode(temp % 10);
			pos = result;
		}
		else {
			pos->next = new ListNode(temp % 10);
			pos = pos->next;
		}
		temp = temp / 10;
	}
	return result;
}

int lengthOfLongestSubstring(string s) {
	vector<int> v(255, -1);
	//v�д洢���ַ����е�ÿһ���ַ��ڵ�ǰ�����������һ�γ��ֵ�λ��
	int beg = 0, len = 0;
	//beg��¼��ǰ�Ӵ������￪ʼ
	for (int i = 0; i < s.size(); i++) {
		if (v[s[i]] >= beg)
			beg = v[s[i]] + 1;
		//��ǰ�ַ���֮ǰ������·���ϳ��ֹ�
		//���beg <= ��λ�ã���ô������ȡ�����ַ����н������ظ��ַ������begӦ������Ϊ��λ��+1
		//���ڵ�ǰλ��֮ǰ����Ӵ����ȶ��Ѿ�������˲��Ҽ�¼��len֮�У����������������©
		//***�������Ϊ��i��ÿһ��λ�ã���ǰȥ������ظ��ַ���***
		v[s[i]] = i;
		//���¸��ַ����һ�γ��ֵ�λ��Ϊ��ǰ������
		if (len < i - beg + 1)
			len = i - beg + 1;
	}
	return len;
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	//��������A�ĳ���Ϊm������B�ĳ���Ϊn
	//һ����ʵ����λ����һ���������зֳ��˵ȳ��������ֶ����ұߵ��ܱ���ߵĴ�
	//�����±�i�����ⳤ��Ϊn������C��Ϊ��������C[0]...C[i - 1]��C[i]...C[n - 1]
	//�����λ������ʵ�����Խ�����Ŀ������Ϊ
	//�ҵ����ֵ�i��j�����������Ϊ����������A[0]...A[i - 1],B[0]...B[j - 1]��A[i]...A[m - 1]��B[j]...B[n - 1]������A[i - 1] <= B[j]����B[j - 1] <= A[i]
	//ʹ��i + j = m - i + n - j����m + nΪż��)��i + j = m - i + n - j + 1����m + nΪ������
	//��������������¶���j = (m + n + 1)/2 - i��ͬʱ���ǵ�0 <= i <= m��0 <= j <= n���ʱ�����n >= m
	//��i��������
	//���Ǽ��������������i = 0��j = n����ô����A����벿�ֻ��ֻ�����B���Ұ벿�ֻ��ֲ����ڣ���˲���Ҫȥ�ж�A[i - 1] <= B[j]������i = m��j = n���������
	//��i > 0��i < m����j�ı��ʽһ�������Ƶ���j < n�� j > 0

	int m = nums1.size() <= nums2.size() ? nums1.size() : nums2.size();
	vector<int> &A = nums1.size() <= nums2.size() ? nums1 : nums2;
	int n = nums1.size() <= nums2.size() ? nums2.size() : nums1.size();
	vector<int> &B = nums1.size() <= nums2.size() ? nums2 : nums1;
	int i, j;
	int left = 0, right = m;
	i = (left + right) / 2;
	while (1) {
		i = (left + right) / 2;
		j = (m + n + 1) / 2 - i;
		if (((i == 0 || j == n) || (A[i - 1] <= B[j])) && ((i == m || j == 0) || (B[j - 1] <= A[i]))) {
			if ((m + n) % 2 != 0) {
				//��Ԫ����Ϊ������������벿��Ԫ�ص����ֵ
				if (i == 0)
					return B[j - 1];
				else if (j == 0)
					return A[i - 1];
				else
					return A[i - 1] >= B[j - 1] ? A[i - 1] : B[j - 1];
			}
			else {
				//���򣬷�����벿��Ԫ�ص����ֵ���Ұ벿��Ԫ����Сֵ��ƽ��ֵ
				int max, min;
				if (i == 0)
					max = B[j - 1];
				else if (j == 0)
					max = A[i - 1];
				else
					max = A[i - 1] >= B[j - 1] ? A[i - 1] : B[j - 1];
				if (i == m)
					min = B[j];
				else if (j == n)
					min = A[i];
				else
					min = A[i] <= B[j] ? A[i] : B[j];
				return (min + max) / 2.0;
			}
		}
		else if (i > 0 && i < m && A[i - 1] > B[j]) {
			//˵��iӦ�ü�С����Ӧ��jҲ��֮����
			//��Χ���ж���Ϊ�˷�ֹ�����±�Խ�磬�����ٽ�ֵ���������������
			right = i - 1;
		}
		else
			left = i + 1;
	}
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

int myAtoi(string str) {
	//pro8���ַ���ת��Ϊ����
	//reference other's code
	string::size_type pos = 0;//��ʶ��ǰ����λ��
	int result = 0;
	bool isMinus = false;
	int temp;//����ָʾ�Ƿ�������
	bool overflow = false;
	if (str[pos] == ' ')
		while (str[pos] == ' ')
			pos++;
	//string�ڲ���ʵ��Ȼ���ÿ��ַ���ʶ������������ﲢû����Խ���ж�
	//��δ����һ���÷�����
	//ȥ��ǰ���ո�
	if (str[pos] == '-') {
		pos++;
		isMinus = true;
	}
	else if (str[pos] == '+')
		pos++;
	while (str[pos] >= '0' && str[pos] <= '9') {
		//ѭ�������������˷������ַ����ֵ����п������
		temp = result;
		result = result * 10 + (str[pos] - '0');
		//��10����ӵĴ�������˴���ǰ��0�����
		if (result / 10 != temp) {
			//�ж������Ƿ����������2147483647�ͻ����
			overflow = true;
			break;
		}
		pos++;
	}
	if (isMinus)
		if (overflow)
			return INT_MIN;
		else
			return result;
	else
		if (overflow)
			return INT_MAX;
		else
			return result;
}

bool isPalindrome(int x) {
	if (x < 0)
		return false;
	//����һ�����ǻ��Ĵ�
	int n = 0;
	for (; static_cast<int>(x / pow(10, n)) != 0; n++);
	//ȷ��������λ��
	for (int i = 0; i < n / 2; i++)
		if(static_cast<int>(x/pow(10, i)) % 10 != static_cast<int>(x / pow(10, n - 1 - i)) % 10)
			return false;
	return true;
}

bool isMatch(string s, string p) {
	//��ǰ��󲻶ϵݹ�����ж�
	if (p.empty()) return s.empty();
	//�ַ���������ʽΪ�յ����

	bool first_match = (!s.empty() &&
		(p.at(0) == s.at(0) || p.at(0) == '.'));
	//first_match��ʶ��һ���ַ��Ƿ�ƥ��

	if (p.size() >= 2 && p.at(1) == '*') {
		return (isMatch(s, p.substr(2)) ||
			(first_match && isMatch(s.substr(1), p)));
	}
	//p�ĵڶ����ַ���*���ҳ��ȴ��ڵ���2
	//.*��char*ƥ��0���ַ���ƥ��1���ַ�
	//���ƥ��0���ַ�����ô�������ж�s��p.substr(2)
	//���ƥ��1���ַ�����ô�ж�first_match��ͬʱ�������������ж�s.substr(1)��p������ע��*����ƥ��0���ַ������p���ýض�


	else
		return first_match && isMatch(s.substr(1), p.substr(1));
		//p�ĵ�2���ַ�����*���߳���Ϊ1�����
		//��ʱ��ֱ�Ӱ�����ͬ�ķ����Ƚ�s.substr(1)��p.substr(1)����
}

int maxArea_my(vector<int>& height) {
	//�㷨˼·
	//�������Һʹ�������ֱ����һ��
	//Ѱ�Ҳ�С�ڶ��Ҿ��뵱ǰԪ����Զ��Ԫ�ؼ������
	//����ǰԪ��С�ڵ���֮ǰ�ѷ���Ԫ�أ���������ǰԪ��
	int max = 0;
	int record = 0;//��¼��ǰ�Ѿ����ʹ������Ԫ��
	//��������
	for (int i = 0; i < height.size(); i++) {
		if (height[i] <= record)
			continue;
		else {
			record = height[i];
			//���������ҵ�һ�����ڵ���height[i]��Ԫ��λ��
			for (int j = height.size() - 1; j >= i; j--) {
				if (height[j] >= height[i]) {
					int temp = height[i] * (j - i);
					max = max > temp ? max : temp;
					break;
				}
			}
		}
	}
	record = 0;
	for (int i = height.size() - 1; i >= 0; i--) {
		if (height[i] <= record)
			continue;
		else {
			record = height[i];
			//���������ҵ�һ�����ڵ���height[i]��Ԫ��λ��
			for (int j = 0; j <= i; j++) {
				if (height[j] >= height[i]) {
					int temp = height[i] * (i - j);
					max = max > temp ? max : temp;
					break;
				}
			}
		}
	}
	return max;
}

int maxArea(vector<int>& height) {
	//reference best practice from leetcode
	int maxArea = 0;
	for (int i = 0, j = height.size(); i != j;) {
		int temp = height[i] <= height[j] ? height[i] : height[j];
		temp = temp * (j - i);
		maxArea = maxArea >= temp ? maxArea : temp;
		if (height[i] > height[j])
			j--;
		else
			i++;
		//���Ԫ��i��jС����ôj�����ƶ�ֻ���������С�����Ӧ���ƶ�i
	}
	return maxArea;
	//�������߶�Ҫ���ǵ����һ�㶼����ͨ��ͬʱ�ƶ�����
}

string intToRoman(int num) {
	string result;
	vector<vector<char>> romans = { {'I', 'V', 'X'}, {'X', 'L', 'C'}, {'C', 'D', 'M'}, {'M', 'M', 'M'} };
	int n = 3;//��ʶ��ǰλ����ǧλ��ʼ
	for (int i = 0; i < 4; i++) {
		int temp = static_cast<int>(num / pow(10, 3 - i)) % 10;
		if (temp < 5) {
			if (temp == 4) {
				result += romans[n][0];
				result += romans[n][1];
			}
			else
				result += string(temp, romans[n][0]);	
		}
		else {
			if (temp == 9) {
				result += romans[n][0];
				result += romans[n][2];
			}
			else {
				result += romans[n][1];
				result += string(temp - 5, romans[n][0]);
			}
		}
		n--;
	}
	return result;
}

int romanToInt(string s) {
	unordered_map<char, int> m = { {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000} };
	int result = 0, temp = 0;
	for (int i = s.size() - 1; i >= 0; i--) {
		if (m[s[i]] < temp)
			result += -m[s[i]];
		else
			result += m[s[i]];
		temp = m[s[i]];
	}
	return result;
}

string longestCommonPrefix(vector<string>& strs) {
	string result;
	string::size_type pos = 0;
	if (!strs.size())
		return result;
	while (pos != strs[0].size()) {
		char temp = strs[0][pos];
		for (auto &str : strs) {
			if (pos == str.size() || str[pos] != temp)
				return result;
		}
		result += temp;
		pos++;
	}
	return result;
}