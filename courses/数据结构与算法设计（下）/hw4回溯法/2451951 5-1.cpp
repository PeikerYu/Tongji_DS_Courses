//单词搜索
// 核心思路：从每个格子出发做 DFS，按 word 的顺序往下匹配。每走一步标记当前格已访问，四个方向递归；走不通就撤销标记回溯。
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (dfs(board, word, 0, i, j))
                    return true;
        return false;
    }

    bool dfs(vector<vector<char>>& board, string& word, int idx, int i, int j) {
        if (idx == word.size()) return true;
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
            return false;
        if (board[i][j] != word[idx]) return false;

        char tmp = board[i][j];
        board[i][j] = '#'; // 标记已用，防止重复走同一格

        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};
        for (int k = 0; k < 4; k++) {
            if (dfs(board, word, idx + 1, i + dx[k], j + dy[k]))
                return true;
        }

        board[i][j] = tmp; // 回溯
        return false;
    }
};
