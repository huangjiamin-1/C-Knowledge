/*
 * @Author: huangjiamin-1 2716673911@qq.com
 * @Date: 2025-10-24 13:37:33
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-10-24 13:51:18
 * @FilePath: /构造函数系列/main_12.cpp
 * @Description: 虚析构函数；
 *               如果不加virtual会导致在多态情况下只释放Base而子类的析构函数无法调用
 */
#include <iostream>

class Base{
    public:
        Base()=default;
        /// @brief 此处如果不加virtual会导致在多态情况下只释放Base而子类的析构函数无法调用
        virtual ~Base(){
            printf("Base %p\n", this);
        }
};

class MyObject: public Base{
    public:
        MyObject(size_t size):_size(size),_data(new int[_size]){
        }

        ~MyObject() override{
            delete [] _data;
            _data = nullptr;
            printf("release MyObject\n");
        }
    
    private:
        int *_data;
        size_t _size;
};

int main(int argc, char *argv[])
{
    Base* myObject = new MyObject(12);
    delete myObject;
    
    return 0;
}


