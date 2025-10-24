/*
 * @Author: huangjiamin-1 2716673911@qq.com
 * @Date: 2025-10-17 11:45:59
 * @LastEditors: huangjiamin-1 2716673911@qq.com
 * @LastEditTime: 2025-10-17 11:50:16
 * @FilePath: /构造函数系列/main_6.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AEfloat
 */
#include <iostream>

int main(int argc, char const *argv[])
{
    float** arr;
    arr = (float**)malloc(4 * sizeof(float*));
    for (int i = 0; i < 4; i++)
    {
        arr[i] = (float*)malloc(sizeof(float) * 4);
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%f, ", arr[i][j]);
        }
    }
    
    for (int i = 0; i < 4; i++)
    {
        free(arr[i]);
    }
    free(arr);
    
    return 0;
}
