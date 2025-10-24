
#include <stdio.h>

#include <algorithm>
#include <memory>
#include <vector>

class MyObject
{
public:
    // 默认构造函数
    MyObject() noexcept : index_(0) {
        printf("创建默认构造函数 -- %p\n", this);
    }

    // 有参构造函数
    explicit MyObject(int index) noexcept : index_(index) {
        printf("创建有参构造函数 -- %p, index:%d\n", this, index_);
    }

    // 拷贝构造函数
    MyObject(const MyObject& other) noexcept {
        printf("创建拷贝构造函数 -- %p(index:%d), from %p(index:%d)\n", this, index_, &other, other.index_);
        index_ = other.index_;
    }

    // 移动构造函数
    MyObject(MyObject&& other) noexcept {
        printf("创建移动构造函数 -- %p(index:%d), from %p(index:%d)\n", this, index_, &other, other.index_);
        index_ = other.index_;
        other.index_ = 0;
    }

    // 析构函数
    ~MyObject() {
        printf("析构函数 -- %p\n", this);
    }

    // 拷贝绑定操作
    MyObject& operator=(const MyObject& other) noexcept {
        printf("拷贝绑定操作 -- %p(index:%d), from %p(index:%d)\n", this, index_, &other, other.index_);
        index_ = other.index_;
        return *this;
    }

    // 移动绑定操作
    MyObject& operator=(MyObject&& other) noexcept {
        printf("移动绑定操作 -- %p(index:%d), from %p(index:%d)\n", this, index_, &other, other.index_);
        index_ = other.index_;
        other.index_ = 0;
        return *this;
    }

    void show() const {
        printf("展示信息 -- %p, index:%d\n", this, index_);
    }

    int GetValue() const {
        return index_;
    }

private:
    int index_;
};

void test_unique_ptr(std::unique_ptr<MyObject> ptr) {
    if (!ptr) {
        printf("test_unique_ptr ptr is nullptr\n");
        return;
    }
    ptr->show();
}

void printItemsInfo(std::vector<MyObject>& items , const char* info) {
    std::string text = "";
    for(const auto& item: items) {
        char buff[128] = { 0 };
        snprintf(buff, sizeof(buff), "%p(index:%d) ", &item, item.GetValue());
        text += buff;
    }
    if (text.empty()) {
        printf("%s -- Items is None\n", info);
    } else {
        printf("%s -- Items: %s\n", info, text.c_str());
    }
}

int main()
{
    printf("场景1:\n");
    {
        std::vector<MyObject> items;
        items.push_back(MyObject(1));
    }
    printf("\n场景2:\n");
    {
        std::vector<MyObject> items;
        items.emplace_back(2);
    }
    printf("\n场景3:\n");
    {
        std::vector<MyObject> items;
        items.emplace_back(3);
        items.emplace_back(4);
    }
    printf("\n场景4:\n");
    {
        std::vector<MyObject> items;
        items.reserve(2);
        items.emplace_back(5);
        items.emplace_back(6);
    }
    printf("\n场景5:\n");
    {
        std::vector<MyObject> items(2);
        printf("Items size:%ld capacity:%ld\n", items.size(), items.capacity());
        items.reserve(4);
        printf("Items size:%ld capacity:%ld\n", items.size(), items.capacity());
    }
    printf("\n场景6:\n");
    {
        std::vector<MyObject> items;
        items.reserve(4);
        items.emplace_back(7);
        items.insert(items.begin(), MyObject(8));
        printf("场景6 主操作完成\n");
    }
    printf("\n场景7:\n");
    {
        std::vector<MyObject> items;
        items.reserve(4);
        items.emplace_back(9);
        items.emplace(items.begin(), 10);
        printf("场景7 主操作完成\n");
    }
    printf("\n场景8:\n");
    {
        std::vector<MyObject> items;
        items.reserve(4);
        items.emplace_back(11);
        items.emplace_back(12);
        items.emplace_back(13);
        items.emplace_back(14);
        auto needToRemove = [](const MyObject& o) -> bool {
            return o.GetValue() % 2 == 0;
        };
        printItemsInfo(items, "初始化完成");
        auto itor = items.begin();
        while(itor != items.end()) {
            if (itor->GetValue() % 2 == 0) {
                itor = items.erase(itor);
            } else {
                itor++;
            }
        }
        printItemsInfo(items, "erase后");
    }
    printf("\n场景9:\n");
    {
        std::vector<MyObject> items;
        items.reserve(4);
        items.emplace_back(15);
        items.emplace_back(16);
        items.emplace_back(17);
        items.emplace_back(18);
        auto needToRemove = [](const MyObject& o) -> bool {
            return o.GetValue() % 2 == 0;
        };
        printItemsInfo(items, "初始化完成");
        auto itor = std::remove_if(items.begin(), items.end(), needToRemove);
        printItemsInfo(items, "std::remove_if后");
        items.erase(itor, items.end());
        printItemsInfo(items, "erase后");
    }
}