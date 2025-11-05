#include <bits/stdc++.h>
using namespace std;

string getNextPermutation(string str)
{
    int n = str.size();
    int pivotIndex = -1;

    // Step 1: Find pivot (rightmost i such that str[i] < str[i + 1])
    for (int i = n - 2; i >= 0; i--) {
        if (str[i] < str[i + 1]) {
            pivotIndex = i;
            break;
        }
    }

    // Step 2: If no pivot, return smallest permutation
    if (pivotIndex == -1) {
        sort(str.begin(), str.end());
        return str;
    }

    // Step 3: Find rightmost element greater than pivot
    int nextGreaterIndex = -1;
    for (int j = n - 1; j > pivotIndex; j--) {
        if (str[j] > str[pivotIndex]) {
            nextGreaterIndex = j;
            break;
        }
    }

    // Step 4: Swap pivot and next greater
    swap(str[pivotIndex], str[nextGreaterIndex]);

    // Step 5: Reverse the suffix
    reverse(str.begin() + pivotIndex + 1, str.end());

    return str;
}

int main()
{
    string str = "abba";
    cout << getNextPermutation(str) << endl; // Output: baab
    return 0;
}
