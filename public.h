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

int findPos(std::vector<int> &array, int begin, int end);
int maxArea(std::vector<int>& height);
int romanToInt(std::string s);
std::string longestCommonPrefix(std::vector<std::string>& strs);

//static const auto speedup = []() {
//	ios::sync_with_stdio(false);
//	cin.tie(nullptr);
//	return nullptr;
//}();