#include "header.h"

/**
 * 在其他数都出现 k 次的数组中找出只出现 1 次 的数
 * 
 * 思路 ：
 *      将数组的每个数转为 k 进制， k 个  k 进制的数相加，得到的结果的每一位都是 0， 所以只出现一次的数才会剩下啦。
*/

// 把 value 转为一个 32 位的 k 进制数
vector<int> NumToKbits(int value, int k)
{
    vector<int> res(32, 0);
    int i = 0;
    while (0 != value)
    {
        res[i++] = value % k;
        value /= k;
    }
    return res;
}

// or 运算
void setExclusiveor(vector<int> &vec, int value, int k)
{
    vector<int> kbits = NumToKbits(value, k);
    for (int i = 0; i < kbits.size(); ++i)
    {
        vec[i] = (vec[i] + kbits[i]) % k;
    }
}

// k 进制转 10 进制
int kbitsTonum(vector<int> &vec, int k)
{
    int num = 0;
    for (int i = vec.size() - 1; i >= 0; --i)
    {
        num = num * k + vec[i];
    }
    return num;
}

// 在其他数都出现 k 次的数组中找出只出现 1 次 的数
int onceNum(vector<int> arr, int k)
{
    vector<int> eo(32, 0);
    for (int i = 0; i < arr.size(); ++i)
    {
        setExclusiveor(eo, arr[i], k);
    }

    int res = kbitsTonum(eo, k);
    return res;
}

int main()
{
    vector<int> nums{1, 1, 3, 2, 3, 1, 3};
    int k = 3;
    cout << "res = " << onceNum(nums, k) << endl;

    return 0;
}