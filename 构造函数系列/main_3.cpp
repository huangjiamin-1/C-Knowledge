/*
C++的构造函数主要有以下几种：
1. 默认构造函数: 这个就是没有任何参数的构造函数，这个通常使用比较广泛
2. 有参构造函数: 这个是有参数的构造函数，参数用来初始化，根据参数的类型和个数的不同，这个构造函数可以有多个
3. 复制构造函数: 这是一个特殊的构造函数，参数只有一个，是const修饰的该类的引用类型
4. 移动构造函数: 这也是一个特殊的构造函数，参数只有一个，是该类的右值引用类型
*/
#include <stdio.h>

#include <memory>

class MyObject
{
public:
    // 默认构造函数
    MyObject(): _index(0) {
        printf("创建默认构造函数 -- %p\n", this);
    }

    // 有参构造函数
    MyObject(int index): _index(index) {
        printf("创建有参构造函数 -- %p, index:%d\n", this, _index);
    }

    // 拷贝构造函数
    MyObject(const MyObject& other) {
        printf("创建拷贝构造函数 -- %p, from %p\n", this, &other);
        _index = other._index;
    }

    // 移动构造函数
    MyObject(MyObject&& other) {
        printf("创建移动构造函数 -- %p, from %p\n", this, &other);
        _index = other._index;
        other._index = 0;
    }

    // 不可变移动构造函数
    MyObject(const MyObject&& other) {
        printf("创建不可变移动构造函数 -- %p, from %p\n", this, &other);
        _index = other._index;
    }

    // 析构函数
    ~MyObject() {
        printf("析构函数 -- %p\n", this);
    }

private:
    int _index;
};

int main()
{
    const MyObject a(1);
    MyObject b(2);
    MyObject c = std::move(b);
    MyObject d = std::move(a); // 这里a是const修饰的，所以会调用不可变移动构造函数
    return 0;
}

/*
创建有参构造函数 -- 0x7fff2678e438, index:1
创建有参构造函数 -- 0x7fff2678e43c, index:2
创建移动构造函数 -- 0x7fff2678e440, from 0x7fff2678e43c
创建不可变移动构造函数 -- 0x7fff2678e444, from 0x7fff2678e438
析构函数 -- 0x7fff2678e444
析构函数 -- 0x7fff2678e440
析构函数 -- 0x7fff2678e43c
析构函数 -- 0x7fff2678e438
*/