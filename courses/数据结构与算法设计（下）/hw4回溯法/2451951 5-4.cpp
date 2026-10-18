//复原 IP 地址
// 核心思路：把数字串切成 4 段，每段 1~3 位且数值在 0~255，不能有前导零。用回溯依次确定每一段的起止位置，4 段都合法且用完整个字符串时加入答案。
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        vector<string> seg(4);
        backtrack(s, 0, 0, seg, res);
        return res;
    }

    void backtrack(string& s, int start, int cnt, vector<string>& seg, vector<string>& res) {
        if (cnt == 4) {
            if (start == s.size())
                res.push_back(seg[0] + "." + seg[1] + "." + seg[2] + "." + seg[3]);
            return;
        }

        for (int len = 1; len <= 3 && start + len <= s.size(); len++) {
            string part = s.substr(start, len);
            // 前导零：长度大于 1 且首位是 0，不合法
            if (len > 1 && part[0] == '0') break;
            // 数值超过 255 不合法
            if (stoi(part) > 255) break;

            seg[cnt] = part;
            backtrack(s, start + len, cnt + 1, seg, res);
        }
    }
};
