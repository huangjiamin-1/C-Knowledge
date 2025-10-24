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
        printf("创建拷贝构造函数 -- %p, from %p\n", this, &other);
        _index = other._index;
    }
    // 移动构造函数
    MyObject(MyObject &&other){
        printf("创建移动构造函数 -- %p, from %p\n", this, &other);
        _index = other._index;
        other._index = 0;
    }

    ~MyObject(){
        printf("销毁对象 -- %p\n", this);
    }

private:
    int _index;
};
int main(int argc, char const *argv[])
{
    MyObject a;
    MyObject b(1);
    MyObject c(b);
    MyObject d(std::move(b));
    return 0;
}
