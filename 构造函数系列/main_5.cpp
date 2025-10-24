/*
 * @Author: huangjiamin-1 2716673911@qq.com
 * @Date: 2025-10-16 14:54:33
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-10-16 16:41:33
 * @FilePath: /构造函数系列/main_4.cpp
 * @Description: operator=(const xxx& ) 与 operator=(xxx &&) 的正确使用
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

    // 拷贝绑定操作
    MyObject& operator=(const MyObject& other){
        if (_buff)
        {
            delete [] _buff;
            _buff = nullptr;
            _buff_size = 0;
        }

        this->_buff_size = other._buff_size;
        this->_buff = new char[_buff_size];
        memcpy(this->_buff, other._buff, _buff_size);
        printf("拷贝绑定操作 -- %p, buff:%p size:%ld, from %p\n", this, _buff, _buff_size, &other);
        return *this;
    }

    // 移动绑定操作
    MyObject& operator=(MyObject&& other){
        if (_buff)
        {
            delete [] _buff;
            _buff = nullptr;
            _buff_size = 0;
        }

        this->_buff = other._buff;
        this->_buff_size = other._buff_size;
        other._buff = nullptr; // 注释会double free
        other._buff_size = 0;
        printf("移动绑定操作 -- %p, buff:%p size:%ld, from %p\n", this, _buff, _buff_size, &other);
        return *this;
    }

private:
    char* _buff;
    size_t _buff_size;
};


int main(int argc, char *argv[])
{
    MyObject a(10);
    MyObject b;
    MyObject c;
    b = a;
    c = std::move(a);
    return 0;
}

/* 输出结果
创建有参构造函数2 -- 0x7ffd847157d0, buff:0x55bb2943aeb0 size:10
创建默认构造函数 -- 0x7ffd847157e0
创建默认构造函数 -- 0x7ffd847157f0
拷贝绑定操作 -- 0x7ffd847157e0, buff:0x55bb2943b2e0 size:10, from 0x7ffd847157d0
移动绑定操作 -- 0x7ffd847157f0, buff:0x55bb2943aeb0 size:10, from 0x7ffd847157d0
析构函数 -- 0x7ffd847157f0, buff:0x55bb2943aeb0 size:10
析构函数 -- 0x7ffd847157e0, buff:0x55bb2943b2e0 size:10
析构函数 -- 0x7ffd847157d0, buff:(nil) size:0
*/
