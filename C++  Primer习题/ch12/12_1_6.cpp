#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// 12_19

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob
{
public:
    friend class StrBlobPtr;
    StrBlobPtr begin() { return StrBlobPtr(*this); }
    StrBlobPtr end()
    {
        auto ret = StrBlobPtr(*this, data->size());
        return ret;
    }

    
    // 12_22
    friend class ConstStrBlobPtr;
    ConstStrBlobPtr cbegin() {return ConstStrBlobPtr(*this)); }
    ConstStrBlobPtr cend()
    {
        auto ret = ConstStrBlobPtr(*this, data->size());
        return ret;
    }


public:
    using size_type = vector<string>::size_type;

    StrBlob();
    StrBlob(initializer_list<string> il);

    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }

    void push_back(const string &t) { data->push_back(t); }
    void pop_back();

    string &front();
    const string &front() const;
    string &back();
    const string &back() const;

private:
    shared_ptr<vector<string>> data; // data是一个智能指针
    void check(size_type i, const string &msg) const;
};

StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> il) : data(make_shared<vector<string>>(il)) {}

void StrBlob::check(size_type i, const string &msg) const
{
    if (i >= data->size())
    {
        throw out_of_range(msg);
    }
}

string &StrBlob::front()
{
    check(0, "front on empty StrBlob");
    return data->front();
}

const string &StrBlob::front() const
{
    check(0, "front on empty StrBlob const");
    return data->front();
}

string &StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}

const string &StrBlob::back() const
{
    check(0, "front on empty StrBlob const ");
    return data->back();
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}


/*****************************************************************************************/
class StrBlobPtr
{
public:
    StrBlobPtr() : cur(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), cur(sz) {}

    string &deref() const;
    StrBlobPtr &incr();

public:
    bool operator!=(const StrBlobPtr &rhs) const
    {
        return rhs.cur == data->size();
    }

private:
    shared_ptr<vector<string>> data;
    shared_ptr<vector<string>> check(size_t, const string &) const;
    weak_ptr<vector<string>> wptr;
    size_t cur;
};

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const
{
    auto ret = wptr.lock();
    if (!ret)
    {
        throw runtime_error("inbound StrBlobPtr");
    }

    if (i >= ret->size())
    {
        throw out_of_range(msg);
    }

    return ret;
}

// 版本1
string &StrBlobPtr::deref() const
{
    auto pvec = check(cur, "dereference past end");
    return (*pvec)[cur];
}

StrBlobPtr &StrBlobPtr::incr()
{
    check(cur, "incurement past end of StrBlobPtr");
    ++cur;
    return *this;
}

// 12_20
void readFile(string &path)
{
    ifstream ifs(path);
    StrBlob strb;
    string line;
    StrBlobPtr pb, pe;

    if (ifs)
    {
        while (getline(ifs, line))
        {
            strb.push_back(line);
        }
    }

    for (StrBlobPtr pb = strb.begin(); pb != strb.end(); pb.incr())
    {
        cout << pb.deref() << endl;
    }
}

// 12_21
// 版本2
// 版本1更好， 因为版本1的可读性更好
string &StrBlobPtr::deref() const
{
    return (*check(cur, "dereference past end"))[cur];
}

/*****************************************************************************************/
// 12_22
class ConstStrBlobPtr
{
public:
    ConstStrBlobPtr() : cur(0) {}
    ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), cur(sz) {}

    string &deref() const;
    ConstStrBlobPtr &incr();

public:
    bool operator!=(const ConstStrBlobPtr &rhs) const
    {
        return rhs.cur == data->size();
    }

private:
    shared_ptr<vector<string>> data;
    shared_ptr<vector<string>> check(size_t, const string &) const;
    weak_ptr<vector<string>> wptr;
    size_t cur;
};