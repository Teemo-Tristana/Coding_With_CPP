#include "example.h"
// 


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
    return (*pvec)[cur];
}

StrBlobPtr& StrBlobPtr:: incr(){
    check(cur, "incurement past end of StrBlobPtr");
    ++cur;
    return *this;
}
