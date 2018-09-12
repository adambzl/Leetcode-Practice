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
	//建立一个哈希表，插入的同时查找互补元素是否存在，将复杂度降为O(n)
	//stupid program that fucks me
	map<int, int> m;
	vector<int> result;
	auto iter = nums.cbegin();
	for (; iter != nums.cend(); iter++) {
		if (iter != nums.cbegin()) {
			int temp = target - *iter;
			if (m.find(temp) != m.end()) {
				//如果有重复匹配，那么这个程序只能找到最后一次匹配出现的位置
				result.push_back(m[temp]);
				result.push_back(iter - nums.cbegin());
				return result;
			}
		}
		//无匹配或者第一个元素的情况则向map中插入新元素
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
	//v中存储着字符串中的每一个字符在当前搜索点上最后一次出现的位置
	int beg = 0, len = 0;
	//beg记录当前子串从哪里开始
	for (int i = 0; i < s.size(); i++) {
		if (v[s[i]] >= beg)
			beg = v[s[i]] + 1;
		//当前字符在之前的搜索路径上出现过
		//如果beg <= 该位置，那么最终提取到的字符串中将包含重复字符，因此beg应该设置为该位置+1
		//由于当前位置之前的最长子串长度都已经考察过了并且记录在len之中，因此这样做不会遗漏
		//***可以理解为在i的每一个位置，向前去找最长无重复字符串***
		v[s[i]] = i;
		//更新该字符最后一次出现的位置为当前搜索点
		if (len < i - beg + 1)
			len = i - beg + 1;
	}
	return len;
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	//假设数组A的长度为m，数组B的长度为n
	//一个事实是中位数将一个有序序列分成了等长的两部分而且右边的总比左边的大
	//假设下标i将任意长度为n的数组C分为两个序列C[0]...C[i - 1]和C[i]...C[n - 1]
	//结合中位数的事实，可以将程序目标设置为
	//找到划分点i和j将两个数组分为左右两部分A[0]...A[i - 1],B[0]...B[j - 1]和A[i]...A[m - 1]和B[j]...B[n - 1]，而且A[i - 1] <= B[j]并且B[j - 1] <= A[i]
	//使得i + j = m - i + n - j（若m + n为偶数)或i + j = m - i + n - j + 1（若m + n为奇数）
	//不论在哪种情况下都有j = (m + n + 1)/2 - i，同时考虑到0 <= i <= m和0 <= j <= n，故必须有n >= m
	//对i搜索即可
	//考虑几种特殊情况：若i = 0或j = n，那么数组A的左半部分划分或数组B的右半部分划分不存在，因此不需要去判断A[i - 1] <= B[j]；对于i = m和j = n的情况类似
	//若i > 0或i < m，由j的表达式一定可以推导出j < n或 j > 0

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
				//总元素数为奇数，返回左半部分元素的最大值
				if (i == 0)
					return B[j - 1];
				else if (j == 0)
					return A[i - 1];
				else
					return A[i - 1] >= B[j - 1] ? A[i - 1] : B[j - 1];
			}
			else {
				//否则，返回左半部分元素的最大值和右半部分元素最小值的平均值
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
			//说明i应该减小，相应地j也随之增大
			//范围的判定是为了防止数组下标越界，考虑临界值不满足条件的情况
			right = i - 1;
		}
		else
			left = i + 1;
	}
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

int myAtoi(string str) {
	//pro8，字符串转化为整数
	//reference other's code
	string::size_type pos = 0;//标识当前遍历位置
	int result = 0;
	bool isMinus = false;
	int temp;//用于指示是否出现溢出
	bool overflow = false;
	if (str[pos] == ' ')
		while (str[pos] == ' ')
			pos++;
	//string内部其实仍然是用空字符标识结束，因此这里并没有做越界判断
	//这未必是一个好方法！
	//去除前导空格
	if (str[pos] == '-') {
		pos++;
		isMinus = true;
	}
	else if (str[pos] == '+')
		pos++;
	while (str[pos] >= '0' && str[pos] <= '9') {
		//循环的条件处理了非数字字符出现的所有可能情况
		temp = result;
		result = result * 10 + (str[pos] - '0');
		//乘10再相加的处理兼容了带有前导0的情况
		if (result / 10 != temp) {
			//判断数字是否溢出，超过2147483647就会溢出
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
	//负数一定不是回文串
	int n = 0;
	for (; static_cast<int>(x / pow(10, n)) != 0; n++);
	//确定整数的位数
	for (int i = 0; i < n / 2; i++)
		if(static_cast<int>(x/pow(10, i)) % 10 != static_cast<int>(x / pow(10, n - 1 - i)) % 10)
			return false;
	return true;
}

bool isMatch(string s, string p) {
	//从前向后不断递归调用判断
	if (p.empty()) return s.empty();
	//字符或正则表达式为空的情况

	bool first_match = (!s.empty() &&
		(p.at(0) == s.at(0) || p.at(0) == '.'));
	//first_match标识第一个字符是否匹配

	if (p.size() >= 2 && p.at(1) == '*') {
		return (isMatch(s, p.substr(2)) ||
			(first_match && isMatch(s.substr(1), p)));
	}
	//p的第二个字符是*而且长度大于等于2
	//.*或char*匹配0个字符或匹配1个字符
	//如果匹配0个字符，那么接下来判断s和p.substr(2)
	//如果匹配1个字符，那么判断first_match的同时，接下来继续判断s.substr(1)和p；这里注意*可以匹配0个字符，因此p不用截断


	else
		return first_match && isMatch(s.substr(1), p.substr(1));
		//p的第2个字符不是*或者长度为1的情况
		//这时候直接按照相同的方法比较s.substr(1)和p.substr(1)即可
}

int maxArea_my(vector<int>& height) {
	//算法思路
	//从左向右和从右向左分别遍历一次
	//寻找不小于而且距离当前元素最远的元素计算面积
	//若当前元素小于等于之前已访问元素，则跳过当前元素
	int max = 0;
	int record = 0;//记录当前已经访问过的最大元素
	//从左向右
	for (int i = 0; i < height.size(); i++) {
		if (height[i] <= record)
			continue;
		else {
			record = height[i];
			//从右向左找第一个大于等于height[i]的元素位置
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
			//从左向右找第一个大于等于height[i]的元素位置
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
		//如果元素i比j小，那么j向左移动只会让面积更小，因此应该移动i
	}
	return maxArea;
	//左右两边都要考虑的情况一般都可以通过同时移动来简化
}

string intToRoman(int num) {
	string result;
	vector<vector<char>> romans = { {'I', 'V', 'X'}, {'X', 'L', 'C'}, {'C', 'D', 'M'}, {'M', 'M', 'M'} };
	int n = 3;//标识当前位，从千位开始
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
	//建立map，O(n)复杂度
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
	//两两组合，O(n^2)复杂度
	for (auto iter = m_nums.cbegin(); iter != m_nums.cend(); iter++) {
		//a = b或者a != b的情况分别处理
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
			//为了避免重复，当三个元素不相等时，第三个元素必须位于前两个元素之后
			//这里还利用了map键值的有序性
		}
	}
	return result;
}

vector<vector<int>> threeSum(vector<int>& nums) {
	//reference best practice from Leetcode
	//这种组合问题一般都是两边一起操作，要有算法信心
	vector<vector<int>> result;
	if (nums.size() < 3)
		return result;
	sort(nums.begin(), nums.end());
	for (vector<int>::size_type i = 0; i < nums.size() - 1; i++) {
		if (nums[i] > 0)
			break;
		//重要的优化！
		if (i != 0 && nums[i] == nums[i - 1])
			continue;
		//对于i，只考察第一次出现的元素以避免重复
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
				//去重
				while (j < k && nums[j] == nums[j - 1])
					j++;
				while (j < k && nums[k] == nums[k + 1])
					k--;
			}
			//根据三个元素和的情况进行调整
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
			//衡量当前的偏差
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
	//类似打印格雷码，递归处理
	if (digits.size() == 1)
		for (auto &s : maps[digits[0]])
			v.push_back(s);
	else {
		string::size_type size = digits.size();
		vector<string> v_temp;
		//获取前缀数字串的匹配结果
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
	//i, j从区间两侧逐渐向中间收紧，k, l在区间中搜索匹配
	//i, j, k, l的位置都根据和的情况进行变化
	//与threeSum问题是类似的，复杂度相比于穷举的O(n^4)降为了O(n^3)
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
	//目前暂时只想到区间穷举这一种方式
	//调整i或j，注意nums[i] + nums[j]的和与target的大小关系不能用于判断移动i或j
	//例如：target = 1 nums = -5 -4 0 0 0 5 和指示应该移动j但是这样将错过正确的区间
	return result;
}