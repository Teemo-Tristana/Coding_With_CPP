#include "header.h"

/**
 * 在其他都出现偶数次的数组中找到出现奇数次的数
*/

int oneNumber(vector<int>& nums)
{
    int res = 0;
    for(auto n : nums)
        res ^= n;
    return res;
}

pair<int,int>  twoNumber(vector<int>& nums)
{
    int res = 0;    
    for(auto n : nums)
        res ^= n;
    
    int  x = res & (~res + 1);
    int one = 0, two = 0;
    for(auto n : nums )
    {
        if (n & x)
            one ^= n;
        else 
            two ^= n;
    }
    return (one, two);
}