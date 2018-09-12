#include "public.h"
using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;
using std::map;
using std::unordered_map;
using std::exception;
using std::sort;

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

vector<vector<int>> threeSum_my(vector<int>& nums) {
	map<int, unsigned> m_nums;
	vector<vector<int>> result;
	bool mark = false;
	//����map��O(n)���Ӷ�
	for (auto &num : nums) {
		m_nums[num]++;
		if (m_nums[num] == 3) {
			if (num == 0)
				mark = true;
			m_nums[num] = 2;
		}
	}
	if (mark)
		result.push_back({ 0, 0, 0 });
	int target = 0;
	//������ϣ�O(n^2)���Ӷ�
	for (auto iter = m_nums.cbegin(); iter != m_nums.cend(); iter++) {
		//a = b����a != b������ֱ���
		if (iter->second == 2 && iter->first != 0) {
			target = 0 - (iter->first * 2);
			if (m_nums.find(target) != m_nums.cend())
				result.push_back({ iter->first, iter->first, target });
		}
		if (iter->first > 0)
			continue;
		auto temp = iter;
		for (auto jter = ++temp; jter != m_nums.cend(); jter++) {
			target = 0 - iter->first - jter->first;
			auto pos = m_nums.find(target);
			if (pos != m_nums.cend() && pos->first > jter->first)
				result.push_back({ iter->first, jter->first, target });
			//Ϊ�˱����ظ���������Ԫ�ز����ʱ��������Ԫ�ر���λ��ǰ����Ԫ��֮��
			//���ﻹ������map��ֵ��������
		}
	}
	return result;
}

vector<vector<int>> threeSum(vector<int>& nums) {
	//reference best practice from Leetcode
	//�����������һ�㶼������һ�������Ҫ���㷨����
	vector<vector<int>> result;
	if (nums.size() < 3)
		return result;
	sort(nums.begin(), nums.end());
	for (vector<int>::size_type i = 0; i < nums.size() - 1; i++) {
		if (nums[i] > 0)
			break;
		//��Ҫ���Ż���
		if (i != 0 && nums[i] == nums[i - 1])
			continue;
		//����i��ֻ�����һ�γ��ֵ�Ԫ���Ա����ظ�
		auto j = i + 1, k = nums.size() - 1;
		int target = -nums[i];
		while (j < k) {
			int sum = nums[j] + nums[k];
			if (sum < target)
				j++;
			else if (sum > target)
				k--;
			else {
				result.push_back({ nums[i], nums[j], nums[k] });
				j++;
				k--;
				//ȥ��
				while (j < k && nums[j] == nums[j - 1])
					j++;
				while (j < k && nums[k] == nums[k + 1])
					k--;
			}
			//��������Ԫ�غ͵�������е���
		}
	}
	return result;
}

int threeSumClosest(vector<int>& nums, int target) {
	sort(nums.begin(), nums.end());
	int result = 0;
	int diff = INT_MAX, min_diff = INT_MAX;
	for (vector<int>::size_type i = 0; i < nums.size(); i++) {
		int temp = target - nums[i];
		vector<int>::size_type j = i + 1, k = nums.size() - 1;
		while (j < k) {
			int sum = nums[j] + nums[k];
			diff = temp - sum;
			//������ǰ��ƫ��
			min_diff = min_diff <= abs(diff) ? min_diff : abs(diff);
			result = min_diff == abs(diff) ? nums[i] + nums[j] + nums[k] : result;
			if (diff > 0)
				j++;
			else if (diff < 0)
				k--;
			else
				return result;
		}
	}
	return result;
}

void combinations(vector<string> &v, string digits, map<char, vector<string>> &maps) {
	//���ƴ�ӡ�����룬�ݹ鴦��
	if (digits.size() == 1)
		for (auto &s : maps[digits[0]])
			v.push_back(s);
	else {
		string::size_type size = digits.size();
		vector<string> v_temp;
		//��ȡǰ׺���ִ���ƥ����
		combinations(v_temp, digits.substr(0, size - 1), maps);
		for (auto i = 0; i < v_temp.size(); i++)
			for (auto j = 0; j < maps[digits[size - 1]].size(); j++)
				v.push_back(v_temp[i] + maps[digits[size - 1]][j]);
	}
	return;
}

vector<string> letterCombinations(string digits) {
	vector<string> result;
	if (digits.size() == 0)
		return result;
	map<char, vector<string>> maps = { {'2', {"a", "b", "c"}},{'3', {"d", "e", "f"}},
	{'4', {"g", "h", "i"}},{'5', {"j", "k", "l"}},{'6', {"m", "n", "o"}},{'7', {"p", "q", "r", "s"}},
	{'8', {"t", "u", "v"}},{'9', {"w", "x", "y", "z"}} };
	combinations(result, digits, maps);
	return result;
}

vector<vector<int>> fourSum(vector<int>& nums, int target) {
	//i, j���������������м��ս���k, l������������ƥ��
	//i, j, k, l��λ�ö����ݺ͵�������б仯
	//��threeSum���������Ƶģ����Ӷ��������ٵ�O(n^4)��Ϊ��O(n^3)
	vector<vector<int>> result;
	if (nums.size() < 4)
		return result;
	sort(nums.begin(), nums.end());
	vector<int>::size_type i = 0, j, k, l;
	for (; i != nums.size() - 3; i++) {
		if (i != 0 && nums[i] == nums[i - 1])
			continue;
		for (j = nums.size() - 1; j != i + 2; j--) {
			if (j != nums.size() - 1 && nums[j] == nums[j + 1])
				continue;
			k = i + 1;
			l = j - 1;
			int temp = target - nums[i] - nums[j];
			while (k < l) {
				int sum = nums[k] + nums[l];
				if (sum < temp)
					k++;
				else if (sum > temp)
					l--;
				else {
					result.push_back({ nums[i], nums[j], nums[k], nums[l] });
					k++;
					l--;
					while (k < l && nums[k] == nums[k - 1])
						k++;
					while (k < l && nums[l] == nums[l + 1])
						l--;
				}
			}
		}
	}
	//Ŀǰ��ʱֻ�뵽���������һ�ַ�ʽ
	//����i��j��ע��nums[i] + nums[j]�ĺ���target�Ĵ�С��ϵ���������ж��ƶ�i��j
	//���磺target = 1 nums = -5 -4 0 0 0 5 ��ָʾӦ���ƶ�j���������������ȷ������
	return result;
}