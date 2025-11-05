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
