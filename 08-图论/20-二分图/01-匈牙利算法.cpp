/*----------------------------------------------------------------
 *
 *   文件名称：01-匈牙利算法.cpp
 *   创建日期：2021年03月29日 ---- 18时51分
 *   题    目：hdu2063
 *   算    法：匈牙利算法
 *   描    述：<++>
 *
 ----------------------------------------------------------------*/

#include <cstdio>
#include <cstring>
using namespace std;
int g[510][510];
int match[510];
int reserve_boy[510];     //匹配结果在match[]中
int k, m_girl, n_boy;

//找一个增广路径，即给女孩x找一个配对男孩
bool dfs(int x) {
    for (int i = 1; i<=n_boy; i++)
        if (!reserve_boy[i] && g[x][i]) {
            reserve_boy[i] = 1;      // 预定男孩i，准备分给女孩x
            if (!match[i] || dfs(match[i])) {
                /*
                 * 有两种情况：(1)如果男孩i还没配对，就分给女孩x；
                 *            (2)如果男孩i已经配对，尝试用dfs()更换原配女孩，以腾出位置给女孩x
                 */
                match[i] = x;
                //配对成功；如果原来有配对，更换成功。现在男孩i属于女孩x
                return true;
            }
        }
    return false;      //女孩x没有喜欢的男孩，或者更换不成功
}

int main() {
    while (~scanf("%d",&k) && k) {
        scanf("%d %d", &m_girl, &n_boy);
        memset(g, 0, sizeof(g));
        memset(match, 0, sizeof(match));
        for (int i = 0; i < k; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            g[a][b] = 1;
        }
        int sum = 0;
        for (int i = 1; i <= m_girl; ++i) {         //为每个女孩找配对
            memset(reserve_boy, 0, sizeof(reserve_boy));
            if(dfs(i))
                sum++;
            //第i个女孩配对成功，这个配对后面可能更换，但是保证她能配对
        }
        printf("%d\n",sum);
    }
    return 0;
}
