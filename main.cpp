#include "public.h"

using std::vector;
using std::cout;
using std::endl;

int main() {
	vector<int> nums = { 1, 0, -1, 0, -2, 2 };
	fourSum(nums, 0);
	system("pause");
	return 0;
}