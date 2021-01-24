#include <memory>
#include <string>
#include <iostream>

using namespace std;

// C++ 中 struct 默认是 public 的
struct destination
{
    destination(const string &ip, const string &port) : m_ip(ip), m_port(port) {}

    string m_ip;
    string m_port;
};

struct connection
{
    connection(const string &ip, const string &port) : m_ip(ip), m_port(port) {}

    string m_ip;
    string m_port;
};

connection connect(destination *pdes)
{
    shared_ptr<connection> spConn(new connection(pdes->m_ip, pdes->m_port));
    cout << "create a connection " << spConn.use_count() << " to" << pdes->m_ip << " : " << pdes->m_port << endl;

    return *spConn;
}

void disconnect(connection pConn)
{
    cout << "close the connection " << pConn.m_ip << " : " << pConn.m_port << endl;
}

void end_connection(connection *p)
{
    disconnect(*p);
}

void test(int* t);
void f(destination &d)
{
    // 获取一个连接
    connection c = connect(&d);

    // 当 p 被销毁或 f 异常退出时， 不会对保存的指针执行 delete ，而是调用 end_connection() 函数
    // end_connection 是删除器，来替代 delete ，确保 资源在 f 正常或异常情况下都可以释放资源
    shared_ptr<connection> p(&c, end_connection);

    int x;
    shared_ptr<int> t(&x, test);
}

void test_12_14()
{
    destination d("172.0.0.1", "8080");
    f(d);
}

// 12_15
// 用 lambda 函数替换 end_connection
void f(destination &d)
{
    connection c = connect(&d);

    // 用 lambda 函数替换 end_connection 函数
    shared_ptr<connection> p(&c, [](connection *p) { disconnect(*p); });
}