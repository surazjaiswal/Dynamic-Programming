// Problem Statement: 0/1 Knapsack
// You are given a bag of max capacity (W) and two arrays, weight and values
// You are required to find the max profit you can generate by putting items in the bag

#include <bits/stdc++.h>
using namespace std;

// using recurison
int knapsack(vector<int> &wt, vector<int> &val, int W, int n)
{
    // base condition
    // to check base condition always check for least valid input
    // for recursion always try to reduce the number (n) / item
    if (n == 0 || W == 0)
        return 0;

    // recursion case
    // always try to make choice diagram
    // for this case we have two conditions
    // if size of item is less than equall to capacity
    // then we have two choices either to_include it in the bag or not
    if (wt[n - 1] <= W)
    {
        int profit_by_including = val[n - 1] + knapsack(wt, val, W - wt[n - 1], n - 1);
        int profit_by_excluding = knapsack(wt, val, W, n - 1);

        return max(profit_by_including, profit_by_excluding);
    }
    // the other condition is that weight of item is more than capacity of the bag
    // so we will exclude this item
    else
    {
        return knapsack(wt, val, W, n - 1);
    }
}

// recurison with memoization
// here dp will defined by taking the vaiables those are not constant during the recurrsion, i.e W (capacity) and n (number of items)
// int dp[Capacity+1][number_of_items+ 1]
int dp[102][102];
int knapsackWithMem(vector<int> &wt, vector<int> &val, int W, int n)
{
    if (n == 0 || W == 0)
        return 0;

    // here we will have a check condition if current values profit has already been calculated or not
    if (dp[W][n] != -1)
        return dp[W][W];

    if (wt[n - 1] <= W)
    {
        int profit_by_including = val[n - 1] + knapsack(wt, val, W - wt[n - 1], n - 1);
        int profit_by_excluding = knapsack(wt, val, W, n - 1);

        return dp[W][n] = max(profit_by_including, profit_by_excluding);
    }
    else
    {
        return dp[W][n] = knapsack(wt, val, W, n - 1);
    }
}

// Dp Top Down approach
// here, base condition from recursion case will be transformed to dp initialzation condition
// and also making similar transformation for recursion cases

void knapsackDP(vector<int> &wt, vector<int> &val, int W, int n)
{
    int dp[102][102];
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= W; j++)
        {
            // initializing base cases
            if (i == 0 || W == 0)
            {
                // this means either capacity or number of item or both is/are 0
                dp[i][j] = 0;
            }
            else if (wt[i - 1] <= j)
            {
                // this case implies that current item weight is less than equal to current capacity taken
                // so here we have 2 choices, include or exclude current item
                // now taking the maximum from, include current item profit and then check remainning items
                // and exluding current item
                //
                dp[i][j] = max(val[i - 1] + dp[i - 1][j - wt[i - 1]], dp[i - 1][j]);
            }
            else
            {
                // here current item weight exceeds capacity so we cannot include this item in the bag
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << dp[n][W] << endl;
}

int main()
{

    int W = 7;                      // bag capacity
    vector<int> wt = {1, 2, 4, 5};  // item weights
    vector<int> val = {1, 3, 5, 7}; // item values
    int n = wt.size();
    cout << knapsack(wt, val, W, n) << endl;
    memset(dp, -1, sizeof(dp));
    cout << knapsackWithMem(wt, val, W, n) << endl;
    knapsackDP(wt, val, W, n);

    return 0;
}