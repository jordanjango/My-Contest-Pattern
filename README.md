# 🧩 Handling Permutation Logics and Intuitions

This document explains the intuition, edge cases, and algorithms behind solving permutation-based lexicographic problems — particularly **Next Permutation** and **Lexicographically Smallest Permutation Greater Than Target**.

---

## 🚀 1. Core Difference Between the Two Problems

| Problem | Input | Goal | Example |
|----------|--------|------|----------|
| **Next Permutation** | One string/array `s` | Find the *next lexicographically greater permutation* of `s` itself | `"bac"` → `"bca"` |
| **Lexicographically Smallest Permutation Greater Than Target** | Two strings: `s` and `target` | Find the *smallest permutation of `s`* that’s *strictly greater* than `target` | `s = "aabc"`, `target = "abac"` → `"abca"` |

👉 **Key intuition:**
- `next_permutation` is a **local operation** — it assumes the string you start from is already one valid permutation and finds the immediate next.
- In the second problem, `target` might not even be one of the permutations of `s`. We have to **search** for the smallest permutation of `s` that beats it lexicographically.

---

## ⚙️ 2. When `next_permutation(target)` Works

You can safely use `next_permutation(target)` **only if:**
1. `s` and `target` contain **exactly the same letters** (same multiset),
2. and `target` is **not already the largest permutation**.

### ✅ Example
```cpp
s = "abb";
target = "bab";
next_permutation(target) -> "bba";
```
`"bba"` is indeed the smallest permutation of `s` greater than `"bab"`.

---

## 🚫 3. When `next_permutation(target)` Breaks

### ❌ Case 1: `target` uses letters not in `s`
```
s = "aabc"
target = "bbaa"
```
`next_permutation(target)` → `"baba"` ❌ (invalid; requires two ‘b’s)  
✅ Correct answer: `"bcaa"`

---

### ❌ Case 2: `target` skips the minimal valid next
```
s = "abcc"
target = "acbb"
```
`next_permutation(target)` → `"bacb"` ❌ (invalid for `s`)  
✅ Correct answer: `"accb"`

---

### ❌ Case 3: `target` already the largest permutation
```
s = "abb"
target = "bba"
```
`next_permutation(target)` → `"abb"` ❌ (wraps to smallest)
✅ Correct answer: `""` (no permutation greater than target)

---

## 🧠 4. Correct Logic for the General Case

When `target` is *not* a permutation of `s`,  
you must **construct** the smallest valid permutation of `s` that’s greater than `target`.

### Idea:
1. Count character frequencies from `s`.
2. Build the result left to right:
   - Match `target`’s prefix as long as possible.
   - At the first position you can, pick the **smallest available char** that’s *greater* than `target[i]`.
   - Fill remaining positions with the **smallest possible letters** (sorted order).

---

## 💻 5. Recursive Implementation (void + pruning)

```cpp
class Solution {
public:
    bool found = false;
    string result = "";

    void dfs(string& target, string& curr, vector<int>& freq, bool pivot, int index) {
        if (found) return;
        if (index == target.size()) {
            if (pivot) { result = curr; found = true; }
            return;
        }

        for (int i = 0; i < 26; i++) {
            if (freq[i] == 0) continue;
            char ch = 'a' + i;

            if (!pivot && ch < target[index]) continue;

            bool nextPivot = pivot || ch > target[index];

            freq[i]--;
            curr.push_back(ch);

            dfs(target, curr, freq, nextPivot, index + 1);

            curr.pop_back();
            freq[i]++;
            if (found) return;
        }
    }

    string lexGreaterPermutation(string s, string target) {
        vector<int> freq(26, 0);
        for (char ch : s) freq[ch - 'a']++;

        string curr = "";
        dfs(target, curr, freq, false, 0);

        return found ? result : "";
    }
};
```

---

## ⚡ 6. Complexity

- Each position tries up to 26 letters.
- With pruning, runtime ≈ **O(26 × n)** (efficient compared to O(n!)).

---

## 🧩 7. Quick Summary

| Scenario | Method | Why |
|-----------|---------|-----|
| `s` and `target` are permutations of each other | ✅ `next_permutation(target)` | They share the same permutation space |
| `target` not a permutation of `s` | 🚫 DFS/Greedy reconstruction | Must construct smallest valid > target |
| `target` already max permutation | 🔁 Return `""` | No greater permutation exists |

---

## 🧭 8. Mental Model

Think of `next_permutation` as **“move one step forward in the same lane”**,  
but the 3720-style problem as **“find the first car (permutation) in your lane (of s) that’s ahead of another car (target)”**.  

If `target` isn’t even in your lane, you can’t just drive forward — you must re-plan the route.

---

## 🧾 9. References

- [Leetcode 31 – Next Permutation](https://leetcode.com/problems/next-permutation/)
- [Leetcode 3720 – Lexicographically Smallest Permutation Greater Than Target (Premium)](https://leetcode.com/problems/lexicographically-smallest-permutation-greater-than-target/)
- Related topics: [Backtracking, Greedy Construction, Lexicographic Ordering]

---

## 🏁 Final Takeaways

- `next_permutation` is **local**, only valid when `target` is already a permutation of `s`.  
- For everything else, use **controlled greedy construction** or **DFS with pruning**.  
- Always validate whether `target` belongs to `s`’s permutation space before deciding the approach.

---
