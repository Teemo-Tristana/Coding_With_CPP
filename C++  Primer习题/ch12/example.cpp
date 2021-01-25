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

StrBlob::StrBlob() : data(make_shared<vector<string>>()){}

StrBlob::StrBlob(initializer_list<string> il):data(make_shared<vector<string>>(il)){}

void StrBlob::check(size_type i, const string& msg) const{
    if (i >= data->size()){
        throw out_of_range(msg);
    }
}

string& StrBlob::front(){
    check(0, "front on empty StrBlob");
    return data->front();
}

const string& StrBlob::front() const {
    check(0, "front on empty StrBlob const");
    return data->front();

}

string& StrBlob::back(){
    check(0, "back on empty StrBlob");
    return data->back();
}

const string& StrBlob::back() const{
     check(0, "front on empty StrBlob const ");
    return data->back();
}

void StrBlob::pop_back(){
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

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

shared_ptr<vector<string>> StrBlobPtr::check(size_t i, const string &msg) const {
    auto ret = wptr.lock();
    if (!ret){
        throw runtime_error("inbound StrBlobPtr");
    }

    if (i >= ret->size()){
        throw out_of_range(msg);
    }

    return ret;
}



string& StrBlobPtr::deref() const {
    auto pvec= check(cur, "dereference past end");
    return (*pvec)(cur);
}

StrBlobPtr& StrBlobPtr:: incr(){
    check(cur, "incurement past end of StrBlobPtr");
    ++cur;
    return *this;
}
