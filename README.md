# boogle

# 📖 Boogle – Slang Word Dictionary

A C++ console application for documenting and searching internet slang words, built with a **Trie** (prefix tree) data structure.

> 🎓 **Final project** for the **Data Structures** course.
> The assignment: build an application for a fictional company, *Boogle*, that creates and documents new slang words, using a Trie and **without using regex**.

## ✨ Features

1. **Release a new slang word**: add a new word with its description. If the word already exists, its description is updated.
2. **Search a slang word**: look up a word and show its description.
3. **View slang words by prefix**: list all words that start with a given prefix.
4. **View all slang words**: list every word in the dictionary.
5. **Exit**

All lists are shown in **lexicographical order**.

## ✅ Input Validation

| Input | Rule |
|---|---|
| Slang word | More than 1 character, no spaces |
| Description | More than 1 word |
| Prefix | Not empty |

## 🧠 Concepts Applied

- Trie data structure (insert, update, search, prefix search)
- Recursion (DFS traversal to print words in sorted order)
- Dynamic memory allocation
- String processing and input validation (no regex)

## ▶️ How to Run

```bash
g++ main.cpp -o boogle
./boogle
```

The program clears the screen automatically on Windows, Linux, and macOS.

## 📷 Sample Usage

```
Input a new slang word [Must be more than 1 characters and contains no space]: da
Input a new slang word description [Must be more than 2 words]: The word the
Successfully released new slang word.

Input a prefix to be searched: da
Words starts with "da":
1. da
2. dawg
```

## ⏱️ Complexity

Insert, search, and prefix search run in **O(L)** time, where L is the length of the word. This does not depend on the number of words stored.

## 👤 Author

**Your Name** – [GitHub](https://github.com/USERNAME)
