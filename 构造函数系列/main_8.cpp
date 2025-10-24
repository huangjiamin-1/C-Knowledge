/*
 * @Author: huangjiamin-1 2716673911@qq.com
 * @Date: 2025-10-23 19:47:58
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-10-23 20:10:27
 * @FilePath: /构造函数系列/main_8.cpp
 * @Description: 构造函数调用时机
 */
#include <stdio.h>

#include <algorithm>
#include <memory>
#include <vector>

class MyObject
{
public:
    // 默认构造函数
    MyObject(): index_(0) {
        printf("创建默认构造函数 -- %p\n", this);
    }

    // 有参构造函数
    explicit MyObject(int index): index_(index) {
        printf("创建有参构造函数 -- %p, index:%d\n", this, index_);
    }

    // 拷贝构造函数
    MyObject(const MyObject& other) {
        printf("创建拷贝构造函数 -- %p, from %p\n", this, &other);
        index_ = other.index_;
    }

    // 移动构造函数
    MyObject(MyObject&& other) noexcept {
        printf("创建移动构造函数 -- %p, from %p\n", this, &other);
        index_ = other.index_;
        other.index_ = 0;
    }

    // 析构函数
    ~MyObject() {
        printf("析构函数 -- %p\n", this);
    }

    int GetValue() const {
        return index_;
    }

private:
    int index_;
};

int main(int argc, char *argv[])
{
    std::vector<MyObject> items;
    // items.reserve(5);
    printf("初始化 items 第一阶段\n");
    items.emplace_back(1);
    printf("初始化 items 第二阶段\n");
    items.emplace_back(2);
    printf("初始化 items 完成\n");
    return 0;
}

/**
首先解释一下主函数的逻辑

1. 创建一个容量为0的vector -- items

2. 向items插入第1个元素
这时，items需要扩容 从0到1

3. 向items插入第2个元素
这时，items需要扩容 从1到2扩容用需要把第1个元素移动过来
 */
