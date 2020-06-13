* 位运算

    - 计算n的二进制中1的个数        

``` cpp
        // cpp
            int cnt = 0;
            while (n != 0)
            {
                n = n &(n-1);
                ++cnt;
            }
            return cnt;
    ```
