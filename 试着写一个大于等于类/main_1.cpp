/*
 * @Author: huangjiamin-1 2716673911@qq.com
 * @Date: 2025-10-23 15:21:38
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-10-23 15:34:58
 * @FilePath: /C-Knowledge/试着写一个大于等于类/main_1.cpp
 * @Description: 新的比较函数的封装，修改了之前版本中可能存在的BUG
 */
#include <iostream>
#include <memory>

namespace Jimn_Jhn{
    template<typename T>
    class Numerical{
        public:
            Numerical(T data):_data(data){}

            T getData() const {
                return _data;
            }
        private:
            /// @brief 原始数据
            T _data;
    };

    template<typename T>
    class Comparator {
        public:
            /// @brief 封装的构造器
            /// @param num 被封装的数据
            Comparator(const Numerical<T>& num):_data(num.getData()), _isValid(true){}

            // 构造函数：从比较结果构造（继承上一次的有效性）
            Comparator(T data, bool isValid): _data(data), _isValid(isValid) {}

            // 重载<运算符：返回新的临时Comparator，不修改原对象
            Comparator<T> operator<(const Numerical<T>& other) const {
                // 若上一次比较已无效，直接返回无效状态
                if (!_isValid) {
                    return Comparator<T>(other.getData(), false);
                }
                // 否则判断当前数据是否小于other，新状态为“上一次有效 && 当前比较成立”
                bool newValid = _data < other.getData();
                return Comparator<T>(other.getData(), newValid);
            }

            // 布尔转换：返回最终比较结果
            operator bool() const {
                return _isValid;
            }

        private:
            /// @brief 当前数值
            T _data;       
            /// @brief 中间比较结果（true表示当前链式比较仍有效）
            bool _isValid; 
    };

    template<typename T>
    Comparator<T> operator<(const Numerical<T>& left, const Numerical<T>& right){
        return Comparator<T>(left) < right;
    }
};


int main(int argc, char* argv[]) {
    using namespace Jimn_Jhn;

    Numerical<int> A(10);
    Numerical<int> B(20);
    Numerical<int> C(30);
    Numerical<int> D(20);

    // 链式比较：A < B < C < D
    if (A < B < C < D) {
        printf("hello\n");
    } else {
        printf("failed\n"); // 输出failed（因为30 < 20不成立）
    }

    // 验证原对象状态未被修改（可重复使用）
    if (A < B) {
        printf("A < B 成立\n"); // 输出
    }
    if (B < C) {
        printf("B < C 成立\n"); // 输出
    }

    return 0;
}

