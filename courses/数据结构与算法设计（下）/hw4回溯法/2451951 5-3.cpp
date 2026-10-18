//分割回文串
// 核心思路：从字符串开头往后切，每次尝试切一段 s[start..i]，若这段是回文就加入当前方案，再从 i+1 继续切；切到末尾时把当前方案存入结果，然后回溯撤销最后一段。
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> path;
        backtrack(s, 0, path, res);
        return res;
    }

    void backtrack(string& s, int start, vector<string>& path, vector<vector<string>>& res) {
        if (start == s.size()) {
            res.push_back(path);
            return;
        }

        for (int i = start; i < s.size(); i++) {
            string sub = s.substr(start, i - start + 1);
            if (!isPalin(sub)) continue;

            path.push_back(sub);
            backtrack(s, i + 1, path, res);
            path.pop_back(); // 回溯
        }
    }

    bool isPalin(string& t) {
        int l = 0, r = t.size() - 1;
        while (l < r) {
            if (t[l] != t[r]) return false;
            l++; r--;
        }
        return true;
    }
};
