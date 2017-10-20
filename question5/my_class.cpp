#include "my_class.h"

#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

string MyClass::str_repr() const
{
    return str_repr_;
}

#define MEMOIZE 1
#if MEMOIZE
static long int make_change(int amount, std::vector<int> coins, map<string, long int>& memo)
{
    if (amount == 0) {
        return 1;
    } else if (amount < 0 || coins.size() == 0) {
        return 0;
    } else {
        long int ways = 0;
        ostringstream oss;
        oss << coins.size() << "_" << amount;
        string key = oss.str();
        auto it = memo.find(key);
        if (it != memo.end()) {
            ways = it->second;
        } else {
            ways += ::make_change(amount - coins[0], coins, memo);
            coins.erase(coins.begin());
            ways += ::make_change(amount, coins, memo);
            memo.insert(make_pair(key, ways));
        }
        return ways;
    }
}

long int MyClass::make_change(int amount, std::vector<int> coins)
{
    map<string, long int> memo;
    return ::make_change(amount, coins, memo);
}
#else // BOTTOM UP
long int MyClass::make_change(int amount, std::vector<int> coins)
{
    // bottom up approach
    // [1,2,3] => [1] & [1,2] & [2,3]
    //sort(coins.begin(), coins.end());;
    vector<int> per_amount(amount + 1);
    per_amount[0] = 1; //base case
    for(const int coin : coins)
    {
        int test_amount = coin;
        while (test_amount <= amount)
        {
            per_amount[test_amount] += per_amount[test_amount - coin];
            test_amount++;
        }
    }
    return per_amount[amount];
}
#endif

