/*
 * @Author: huangjiamin-1 2716673911@qq.com
 * @Date: 2025-10-16 14:54:33
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-10-23 11:43:05
 * @FilePath: /构造函数系列/main_4.cpp
 * @Description: 移动构造函数的一般写法和double free问题
 */
#include <iostream>
#include <memory>
#include <cstring>

class MyObject{
public:
    // 默认构造函数
    MyObject(): _buff_size(0), _buff(nullptr){
        printf("创建默认构造函数 -- %p\n", this);
    }

    // 有参构造函数
    MyObject(char* buff, size_t buff_size): _buff(buff), _buff_size(buff_size) {
        printf("创建有参构造函数1 -- %p, buff:%p size:%ld\n", this, _buff, _buff_size);
    }

    MyObject(size_t buff_size): _buff_size(buff_size), _buff(new char[buff_size]){
        printf("创建有参构造函数2 -- %p, buff:%p size:%ld\n", this, _buff, _buff_size);
    }

    // 拷贝构造函数
    MyObject(const MyObject& other){
        _buff_size = other._buff_size;
        _buff = new char[_buff_size];
        memcpy(_buff, other._buff, _buff_size);
        printf("创建拷贝构造函数 -- %p, buff:%p size:%ld, from %p\n", this, _buff, _buff_size, &other);
    }

    // 移动构造函数
    MyObject(MyObject&& other){
        this->_buff = other._buff; // 指针转移
        this->_buff_size = other._buff_size;
        other._buff = nullptr;
        other._buff_size = 0;
        printf("创建移动构造函数 -- %p, buff:%p size:%ld, from %p\n", this, _buff, _buff_size, &other);
    }

    ~MyObject(){
        printf("析构函数 -- %p, buff:%p size:%ld\n", this, _buff, _buff_size);
        if (nullptr != _buff)
        {
            delete [] _buff;
            _buff = nullptr;
            _buff_size = 0;
        }
    }

private:
    char* _buff;
    size_t _buff_size;
};


int main(int argc, char *argv[])
{
    MyObject a;
    MyObject b(10);
    MyObject c = b;
    // printf("....\n");
    // MyObject& e = a;
    // printf("....\n");
    MyObject d = std::move(b);
    return 0;
}

/* 输出结果
创建默认构造函数 -- 0x7ffc1a5ad340
创建有参构造函数2 -- 0x7ffc1a5ad350, buff:0x55e6307032c0 size:10
创建拷贝构造函数 -- 0x7ffc1a5ad360, buff:0x55e6307032e0 size:10, from 0x7ffc1a5ad350
创建移动构造函数 -- 0x7ffc1a5ad370, buff:0x55e6307032c0 size:10, from 0x7ffc1a5ad350
析构函数 -- 0x7ffc1a5ad370, buff:0x55e6307032c0 size:10
析构函数 -- 0x7ffc1a5ad360, buff:0x55e6307032e0 size:10
析构函数 -- 0x7ffc1a5ad350, buff:(nil) size:0
析构函数 -- 0x7ffc1a5ad340, buff:(nil) size:0
*/
