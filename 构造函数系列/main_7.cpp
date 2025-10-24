/*
 * @Author: huangjiamin-1 2716673911@qq.com
 * @Date: 2025-10-23 19:37:26
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-10-23 19:46:18
 * @FilePath: /C-Knowledge/构造函数系列/main_7.cpp
 * @Description: 构造函数中的一些关键字
 */
#include <stdio.h>
#define USE_EXPLICIT_KW (true)
class MyObject
{
public:
#if USE_EXPLICIT_KW
    explicit MyObject(int index): index1_(index), index2_(-1) {
        printf("创建一个参数构造函数 -- %p, index1:%d, index2:%d\n", this, index1_, index2_);
    }

    explicit MyObject(int index1, int index2): index1_(index1), index2_(index2) {
        printf("创建两个参数构造函数 -- %p, index1:%d, index2:%d\n", this, index1_, index2_);
    }
#else
    MyObject(int index): index1_(index), index2_(-1) {
        printf("创建一个参数构造函数 -- %p, index1:%d, index2:%d\n", this, index1_, index2_);
    }

    MyObject(int index1, int index2): index1_(index1), index2_(index2) {
        printf("创建两个参数构造函数 -- %p, index1:%d, index2:%d\n", this, index1_, index2_);
    }
#endif

    ~MyObject() {
        printf("析构函数 -- %p, index1:%d, index2:%d\n", this, index1_, index2_);
    }

    void show() const {
        printf("展示信息 -- %p, index1:%d, index2:%d\n", this, index1_, index2_);
    }

private:
    int index1_;
    int index2_;
};

void f(MyObject o) {
    printf("调用函数f的第一个重载\n");
    o.show();
}

void f(MyObject o, int) {
    printf("调用函数f的第二个重载\n");
    o.show();
}

int main()
{
#if USE_EXPLICIT_KW
    f(MyObject(1));
    f(MyObject(1,2),1); // 只能显示调用
#else
    f(1);
    printf("  ----------  \n");
    f(1, 2);
    printf("  ----------  \n");
    f({1, 2});
#endif
}