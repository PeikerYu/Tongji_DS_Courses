//利用分治法将计算量从 O(n) 降低到 O(\log n)。核心逻辑是递归地将指数减半，只需要计算一次 x^{n/2} 并取其平方即可。如果 n 是奇数，再额外乘一个 x
class Solution {
public:
    double myPow(double x, int n) {
        if(n<0)
            return 1.0/myPow(x,-n); // 处理负指数情况
        double res;
        if(n==0)
            return 1.0;
        double half=myPow(x,n/2); // 递归计算一半指数的结果
        if(n%2==0)
            res=half*half;
        else
            res=half*half*x; // 如果是奇数，平方后再乘一个x
        return res;

    }
};