/**
 * Algorithm to find the next lexicographical permutation of a given array.
 *
 * Problem: Given an array of integers, rearrange the numbers into the
 * lexicographically next greater permutation. If no such arrangement exists,
 * rearrange it as the lowest possible order (sorted in ascending order).
 *
 * Example:
 * Input:  [1,2,3]
 * Output: [1,3,2]
 *
 * Algorithm:
 * 1. Find the largest index i such that nums[i] < nums[i+1]
 *    - This is the "pivot" point for rearrangement
 *    - If no such index exists, the array is in descending order (last permutation)
 *
 * 2. Find the largest index j such that nums[i] < nums[j]
 *    - This gives us the smallest number greater than nums[i] to swap with
 *
 * 3. Swap nums[i] and nums[j]
 *    - Places the next larger digit at the pivot position
 *
 * 4. Reverse the suffix starting at nums[i+1]
 *    - Ensures the suffix is in ascending order (smallest possible arrangement)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * Based on my algorithmic theory of first + pivot + remaining
 */

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

/**
 * Find the largest index i such that nums[i] < nums[i+1]
 * Returns -1 if no such index exists (array is in descending order)
 */
int findPivotIndex(const vector<int> &nums)
{
    int n = nums.size();
    for (int i = n - 2; i >= 0; i--)
    {
        if (nums[i] < nums[i + 1])
        {
            return i;
        }
    }
    return -1;
}

/**
 * Find the largest index j such that nums[i] < nums[j]
 * Searches from right to left to find the smallest number greater than nums[pivotIndex]
 */
int findNextGreaterIndex(const vector<int> &nums, int pivotIndex)
{
    int n = nums.size();
    for (int j = n - 1; j > pivotIndex; j--)
    {
        if (nums[j] > nums[pivotIndex])
        {
            return j;
        }
    }
    return -1;
}

class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        int pivotIndex = findPivotIndex(nums);

        if (pivotIndex == -1)
        {
            reverse(nums.begin(), nums.end());
            return;
        }

        int nextGreaterIndex = findNextGreaterIndex(nums, pivotIndex);
        swap(nums[pivotIndex], nums[nextGreaterIndex]);
        reverse(nums.begin() + pivotIndex + 1, nums.end());
    }
};

void printVector(const vector<int> &nums)
{
    cout << "[";
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i];
        if (i < nums.size() - 1)
            cout << ",";
    }
    cout << "]";
}

int main()
{
    Solution sol;

    // Test cases
    vector<vector<int>> testCases = {
        {1, 2, 3},
        {3, 2, 1},
        {1, 1, 5},
        {1, 3, 2},
        {2, 3, 1},
        {1, 2, 3, 4},
        {4, 3, 2, 1},
        {1, 5, 1}};

    cout << "Testing Next Permutation Algorithm:\n";
    cout << "===================================\n";

    for (auto nums : testCases)
    {
        cout << "Input:  ";
        printVector(nums);

        sol.nextPermutation(nums);

        cout << " -> Output: ";
        printVector(nums);
        cout << "\n";
    }

    return 0;
}