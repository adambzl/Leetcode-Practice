//各源文件会用到的一些常用头文件
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <climits>
#include <vector>
#include <map>
#include <climits>
#include <cctype>
#include <unordered_map>
#include <exception>
#include <deque>
#include <list>

int findPos(std::vector<int> &array, int begin, int end);
int maxArea(std::vector<int>& height);
int romanToInt(std::string s);
std::string longestCommonPrefix(std::vector<std::string>& strs);
std::vector<std::vector<int>> threeSum(std::vector<int>& nums);
int threeSumClosest(std::vector<int>& nums, int target);
std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target);

//static const auto speedup = []() {
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr);
//	return nullptr;
//}();