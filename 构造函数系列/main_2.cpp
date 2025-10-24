/*
C++的构造函数主要有以下几种：
1. 默认构造函数: 这个就是没有任何参数的构造函数，这个通常使用比较广泛
2. 有参构造函数: 这个是有参数的构造函数，参数用来初始化，根据参数的类型和个数的不同，这个构造函数可以有多个
3. 复制构造函数: 这是一个特殊的构造函数，参数只有一个，是const修饰的该类的引用类型
4. 移动构造函数: 这也是一个特殊的构造函数，参数只有一个，是该类的右值引用类型
*/
#include <iostream> 
class MyObject{
public:
    // 默认构造函数
    MyObject():_index(0){
        printf("创建默认构造函数 -- %p\n", this);
    }
    // 有参构造函数
    MyObject(int index):_index(index){
        printf("创建有参构造函数 -- %p index: %d\n", this, _index);
    }
    // 拷贝构造函数
    MyObject(const MyObject &other){
        printf("创建不变拷贝构造函数 -- %p, from %p\n", this, &other);
        _index = other._index;
    }
    // 可变拷贝构造函数
    MyObject(MyObject &other){
        printf("创建可变拷贝构造函数 -- %p, from %p\n", this, &other);
        _index = other._index;
        other._index = -1;
    }

    ~MyObject(){
        printf("销毁对象 -- %p\n", this);
    }

    void show() const {
        printf("展示信息 -- %p, index:%d\n", this, _index);
    }

private:
    int _index;
};
int main(int argc, char const *argv[])
{
    // 使用const修饰
    const MyObject a(1); 
    MyObject b(1);
    b.show();
    MyObject c = b; // 可变拷贝构造函数
    b.show();
    c.show();
    MyObject d = a; // 不变拷贝构造函数
    a.show();
    MyObject e = std::move(d);
    return 0;
}

/*  输出结果
创建有参构造函数 -- 0x7ffdf8e265c4 index: 1
创建有参构造函数 -- 0x7ffdf8e265c8 index: 1
展示信息 -- 0x7ffdf8e265c8, index:1
创建可变拷贝构造函数 -- 0x7ffdf8e265cc, from 0x7ffdf8e265c8
展示信息 -- 0x7ffdf8e265c8, index:-1
展示信息 -- 0x7ffdf8e265cc, index:1
创建不变拷贝构造函数 -- 0x7ffdf8e265d0, from 0x7ffdf8e265c4
展示信息 -- 0x7ffdf8e265c4, index:1
创建不变拷贝构造函数 -- 0x7ffdf8e265d4, from 0x7ffdf8e265d0  ## 在没有移动函数时，默认调用拷贝函数
销毁对象 -- 0x7ffdf8e265d4
销毁对象 -- 0x7ffdf8e265d0
销毁对象 -- 0x7ffdf8e265cc
销毁对象 -- 0x7ffdf8e265c8
销毁对象 -- 0x7ffdf8e265c4
*/
