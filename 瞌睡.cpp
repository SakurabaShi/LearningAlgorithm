#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n,k;
    cin >> n >> k;
    vector<int> a;
    vector<int> t;
    vector<int> bonus(n);
    vector<int> awake(n);
    for ( int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        a.push_back(x);
    }
    int count = 0;
    int count_r = 0;
    for ( int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        t.push_back(x);
    }
    //遍历数组，若该分钟是醒着的，加入整体醒着知识点累积计数；若该分钟是睡着的，加入整体睡着的知识点累积计数;
    //bouns数组用于保存该点累积的睡着时增加知识点累积计数
    for ( int i = 0; i < n; i++)
    {
        if ( t[i] == 1 )
        {
            count+=a[i];
        }
        if ( t[i] == 0 )
        {
            count_r += a[i];
        }
        bonus[i] = count_r;
    }
    //遍历bonus数组，每个睡着的节点叫醒获得的额外知识点增益等于bouns[k+i-1]-bouns[i-1](在数组不越界的情况下)
    for ( int i = 0; i < n ; i++)
    {
        if ( t[i] == 0 )
        {
            int right = (k+i-1 > n-1)? (n-1):(k+i-1);
            int left = ( i-1 < 0)? 0:(i-1);
            awake[i] = bonus[right] - bonus[left];
        }
    }
    int res = 0;
    for ( int i = 0; i < n; i++)
    {
        res = max(awake[i],res);
    }
    int ans = res+count;
    cout<<ans;
    return 0;
}
