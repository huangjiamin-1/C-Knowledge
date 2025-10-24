/*
 * @Author: huangjiamin-1 2716673911@qq.com
 * @Date: 2025-10-23 13:44:25
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-10-23 15:21:12
 * @FilePath: /C-Knowledge/试着写一个大于等于类/main_0.cpp
 * @Description: 实现一个自定义数据类型 初代版本 由于_flag在过程中进行修改可能导致隐藏Bug
 */
#include <iostream>
#include <memory>

namespace Jimn_Jhn{
    class Bool{
        public:
            Bool(bool flag):_flag(flag){
                printf("create Bool base!\n");
            }

            virtual operator bool() const{
                return _flag;
            }

        protected:
            bool _flag;
    };

    template<typename T>
    class Numerical: public Bool{
        public:
            Numerical(T data):_data(data), Bool(true){
                printf("create Numerical derive\n");
            }

            Numerical<T>& operator<(Numerical<T>& other){
                if (!_flag || _data >= other._data) {
                    other._flag = false;
                };
                return other;   
            }

            virtual operator bool() const override{
                // printf("hhlllpoo\n");
                return _flag;
            }

        private:
            /// @brief 原始数据
            T _data;
    };
};

int main(int argc, char *argv[])
{   
    using namespace Jimn_Jhn;
    Numerical<int> A(10);
    Numerical<int> B(20);
    Numerical<int> C(30);
    Numerical<int> D(20);
    if(A < B < C < D)
        printf("hello\n");
    else
        printf("failed\n");
    
    std::unique_ptr<Bool> b = std::make_unique<Numerical<int>>(10);
    printf("%d\n", b->operator bool());

    return 0;
}
