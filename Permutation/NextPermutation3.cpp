// TC : O(N) SC : O(1)
// Based on my algorithmic theory of first + pivot + remaining

#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

class Solution
{
public:
    int nextGreaterElement(int n)
    {
        // "12" 1 and 2 so we know that nums[i] < nums[i+1] yes so 1 is pivot
        // after 1 we have everything greater so 1 and next is 2 swap these 2 so
        // we found the string
        string str = to_string(n);
        int pivotIndex = -1;
        for (int i = str.size() - 2; i >= 0; i--)
        {
            if (str[i] < str[i + 1])
            {
                pivotIndex = i;
                break;
            }
        }
        // now we can find char greater than pivot index
        if (pivotIndex == -1)
        {
            return -1;
        }
        int nextGreaterIndex = -1;
        // let's build a pivot index value as well
        for (int j = str.size() - 1; j > pivotIndex; j--)
        {
            if (str[j] > str[pivotIndex])
            {
                nextGreaterIndex = j;
                break;
            }
        }
        swap(str[pivotIndex], str[nextGreaterIndex]);
        /*Reverse the some half of the string convert to num and return*/
        reverse(str.begin() + pivotIndex + 1, str.end());
        long long val = stoll(str);
        if (val > INT_MAX)
            return -1;
        return (int)val;
    }
};

int main()
{
    Solution sol;

    // Test cases
    int testCases[] = {12, 21, 123, 321, 1234, 4321, 54321};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);

    cout << "Testing Next Greater Element:\n";
    cout << "Input\t-> Output\n";
    cout << "-----\t   ------\n";

    for (int i = 0; i < numTests; i++)
    {
        int result = sol.nextGreaterElement(testCases[i]);
        cout << testCases[i] << "\t-> ";
        if (result == -1)
        {
            cout << "No next greater permutation\n";
        }
        else
        {
            cout << result << "\n";
        }
    }

    return 0;
}