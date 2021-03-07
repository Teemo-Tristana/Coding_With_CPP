<<<<<<< HEAD
#ifndef EXAMPLE_H__
#define EXAMPLE_H__

#include <iostream>
#include <memory>
#include <vector>
#include <string>


using namespace std;

// 

class StrBlobPtr;

class StrBlob
{
public:
    friend class StrBlobPtr;
    StrBlobPtr begin() { return StrBlobPtr(*this) ;}
    StrBlobPtr end(){
        auto ret = StrBlobPtr(*this, data->size());
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


class StrBlobPtr{
    public:
        StrBlobPtr():cur(0){}
        StrBlobPtr(StrBlob&a, size_t sz = 0): wptr(a.data), cur(sz){}
        string& deref() const;
        StrBlobPtr& incr();

    private:
        shared_ptr<vector<string>> data;
        shared_ptr<vector<string>>  check(size_t, const string&) const;
        weak_ptr<vector<string>> wptr;
        size_t cur;
};



=======
#ifndef EXAMPLE_H__
#define EXAMPLE_H__

#include <iostream>
#include <memory>
#include <vector>
#include <string>


using namespace std;

// 

class StrBlobPtr;

class StrBlob
{
public:
    friend class StrBlobPtr;
    StrBlobPtr begin() { return StrBlobPtr(*this) ;}
    StrBlobPtr end(){
        auto ret = StrBlobPtr(*this, data->size());
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


class StrBlobPtr{
    public:
        StrBlobPtr():cur(0){}
        StrBlobPtr(StrBlob&a, size_t sz = 0): wptr(a.data), cur(sz){}
        string& deref() const;
        StrBlobPtr& incr();

    private:
        shared_ptr<vector<string>> data;
        shared_ptr<vector<string>>  check(size_t, const string&) const;
        weak_ptr<vector<string>> wptr;
        size_t cur;
};



>>>>>>> 9a5e9bede5efffbf2eb1d5a82ed59e134223b5e5
#endif