/*
 * @Author: huangjiamin-1 2716673911@qq.com
 * @Date: 2025-10-23 20:47:52
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-10-24 10:39:37
 * @FilePath: /构造函数系列/main_10.cpp
 * @Description: remove_if函数的使用
 */
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto is_even = [](int n)->bool{
        return n % 2 == 0;
    };

    // 1. 用 remove_if 移动元素，返回新的逻辑末尾
    auto new_end = std::remove_if(nums.begin(), nums.end(), is_even);

    // 此时 nums 的 size 仍为 9，但 [begin, new_end) 包含所有未被移除的元素（奇数）
    for(auto it = nums.begin();it != new_end; it++){
        std::cout << *it << " "; // 输出：1 3 5 7 9
    }

    std::cout << "\n容器实际大小：" << nums.size() << std::endl; // 输出：9

    for(auto it = nums.begin();it != nums.end(); it++){
        std::cout << *it << " "; // 输出：1 3 5 7 9 ...
    }
    std::cout << std::endl;

    nums.erase(new_end, nums.end());

    std::cout << "删除后的元素：";
    for (int n : nums) {
        std::cout << n << " "; // 输出：1 3 5 7 9
    }
    std::cout << "\n容器实际大小：" << nums.size() << std::endl; // 输出：5
}