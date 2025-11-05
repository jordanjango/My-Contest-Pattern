#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    bool found = false;
    string result = "";

    void getLexGreaterPerm(string &target, string &curr, vector<int> &freq, bool pivot, int index)
    {
        if (found)
            return; // stop once result found

        if (index == target.size())
        {
            if (pivot)
            {
                result = curr;
                found = true;
            }
            return;
        }

        for (int i = 0; i < 26; i++)
        {
            if (freq[i] == 0)
                continue;

            char ch = 'a' + i;

            // must stay >= target[index] if we haven't crossed yet
            if (!pivot && ch < target[index])
                continue;

            bool nextPivot = pivot || ch > target[index];

            freq[i]--;
            curr.push_back(ch);

            getLexGreaterPerm(target, curr, freq, nextPivot, index + 1);

            curr.pop_back();
            freq[i]++;

            if (found)
                return; // stop further recursion
        }
    }

    string lexGreaterPermutation(string s, string target)
    {
        vector<int> freq(26, 0);
        for (char ch : s)
            freq[ch - 'a']++;

        string curr = "";
        getLexGreaterPerm(target, curr, freq, false, 0);

        return result;
    }
};

int main()
{
    Solution sol;

    // Test cases for lexicographically greater permutation
    vector<pair<string, string>> testCases = {
        {"abc", "abc"}, // s="abc", target="abc" -> "acb"
        {"abc", "acb"}, // s="abc", target="acb" -> "bac"
        {"abc", "bca"}, // s="abc", target="bca" -> "cab"
        {"abc", "cab"}, // s="abc", target="cab" -> "cba"
        {"abc", "cba"}, // s="abc", target="cba" -> "" (no greater)
        {"aab", "aab"}, // s="aab", target="aab" -> "aba"
        {"aab", "aba"}, // s="aab", target="aba" -> "baa"
        {"xyz", "xyz"}  // s="xyz", target="xyz" -> "xzy"
    };

    cout << "Testing Lexicographically Greater Permutation (DFS Pattern):\n";
    cout << "============================================================\n";
    cout << "Format: s=\"source\", target=\"target\" -> result\n\n";

    for (auto &test : testCases)
    {
        // Reset solution state for each test
        sol.found = false;
        sol.result = "";

        string s = test.first;
        string target = test.second;
        string result = sol.lexGreaterPermutation(s, target);

        cout << "s=\"" << s << "\", target=\"" << target << "\" -> ";
        if (result.empty())
        {
            cout << "\"\" (no greater permutation exists)\n";
        }
        else
        {
            cout << "\"" << result << "\"\n";
        }
    }

    return 0;
}
