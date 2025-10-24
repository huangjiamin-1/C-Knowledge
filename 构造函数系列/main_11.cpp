/**
 * 使用构造函数中初始化列表来对类中对象进行初始化，减少类对象的重复构造
 * 对比场景3和4
 */
#include <iostream>

class A
{
public:
    A(): index_(0) {
        printf("Call A() --- this:%p\n", this);
    }
    A(int index): index_(index) {
        printf("Call A(int %d) --- this:%p\n", index, this);
    }
    A(const A& a): index_(a.index_) {
        printf("Call A(const A&)  --- this:%p index_:%d\n", this, index_);
    }
    ~A() {
        printf("Call ~A() --- this:%p index_:%d\n", this, index_);
    }
    A& operator=(const A& b) {
        index_ = b.index_;
        printf("Call A& operator=(const A& b)  --- this:%p from %p\n", this, &b);
        return *this;
    }

private:
    int index_;
};

class B
{
public:
    B(): index_(0) {
        printf("Call B() --- this:%p\n", this);
    }
    B(int index): index_(index) {
        printf("Call B(int %d) --- this:%p\n", index, this);
    }
    B(const B& b): index_(b.index_) {
        printf("Call B(const B&)  --- this:%p index_:%d\n", this, index_);
    }
    ~B() {
        printf("Call ~B() --- this:%p index_:%d\n", this, index_);
    }
    B& operator=(const B& b) {
        index_ = b.index_;
        printf("Call B& operator=(const B& b)  --- this:%p from %p\n", this, &b);
        return *this;
    }

private:
    int index_;
};

class C
{
public:
    C(): index_(0) {
        printf("Call C() --- this:%p\n", this);
    }
    C(int index): index_(index) {
        printf("Call C(int %d) --- this:%p\n", index_, this);
    }
    C(const C& c): index_(c.index_) {
        printf("Call C(const B&)  --- this:%p index_:%d\n", this, index_);
    }
    ~C() {
        printf("Call ~C() --- this:%p index_:%d\n", this, index_);
    }
    C& operator=(const C& c) {
        index_ = c.index_;
        printf("Call C& operator=(const C& c)  --- this:%p from %p\n", this, &c);
        return *this;
    }

private:
    int index_;
};

class D
{
public:
    D() = default;
    D(int index):b_(index) {}
    D(int index1, int index2):
        b_(index1), a_(index2) {}
#if 0
    // D(const char*):b_(-1),a_(-2) {
    //     // b_ = B(-1);
    //     // a_ = A(-2);
    // }
#else
    D(const char*){
        b_ = B(-1);
        a_ = A(-2);
    }
#endif

private:
    A a_ = A(1);
    B b_;
    C c_ = C();
};

class E
{
public:
    E() = default;

private:
    B b_;
    A a_;
};

class F: public E
{
public:
    F() = default;

private:
    C c_;
};

class G1
{
public:
    G1() = default;
    G1(int index): a_(index) {};
private:
    A a_;
};

class G2
{
private:
    B b_;
};

class G: public G2, G1
{
public:
    G() = default;
    G(int index): G1(index), G2() {}
};

int main()
{
    {
        printf("场景 ---- 1\n");
        D d;
    }
    {
        printf("\n场景 ---- 2\n");
        D d(1);
    }
    {
        printf("\n场景 ---- 3\n");
        D d(2, 3);
    }
    {
        printf("\n场景 ---- 4\n");
        D d("test");
    }
    {
        printf("\n场景 ---- 5\n");
        E e;
    }
    {
        printf("\n场景 ---- 6\n");
        F f;
    }
    {
        printf("\n场景 ---- 7\n");
        G g;
    }
    {
        printf("\n场景 ---- 8\n");
        G g(4);
    }
}