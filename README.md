# Substring Matching With Suffix Trees

## 📘 Problem Statement  
**Suffix Trees and DNA Matching**

Given a text string **T** and a set of patterns  
**P = {p₁, p₂, …, pᵣ}**,  
we often want to find all occurrences of any pattern in **T**.

This type of problem appears in **molecular biology**, where known DNA or protein substrings are stored in a library.  
When a new DNA sequence **S** is generated, we want to check:

- Whether any known substring occurs in **S**  
- How many times it occurs  
- At which positions  

### 🧮 Notation  
- **n** — total length of all patterns in P  
- **m** — length of the text string T  
- **k** — number of occurrences of patterns in T  

---

## 📂 Contents of This Repository  
This project implements substring matching using multiple approaches:

1. **The Problem Statement**
2. **A Naïve Approach**  
   - Simple brute-force pattern matching, running in average O(mn) time.
3. **Tries**  
   - Tree-based pattern storage  
4. **Compressed Tries**  
   - Space-optimized trie representation  
5. **Ukkonen’s Algorithm**  
   - **Linear-time suffix tree construction (O(m))**  
   - **This is the algorithm used in the final implementation**
6. **Running the Code**
7. **Results and Analysis**
8. **Comparison With Alternative Algorithms**

---

## ⚙️ Implementation Details

This project includes implementations of:

- `naive_algo.cpp` – brute-force pattern matching  
- `extend_part.cpp` – prefix extension & tree operations  
- `string_generator.cpp` – random DNA string generator  
- `Makefile` – easy compilation  
- **`Ukkonen_algo.cpp` (main algorithm used to build the suffix tree)**  

The final suffix tree used for substring search is constructed using **Ukkonen’s Algorithm**, ensuring efficient performance even for large DNA sequences.

---

## ▶️ Running the Code

 Compile using `make`:
   ```bash
    mingw32-make run
``` 


## 📊 Results & Analysis

- **Ukkonen’s algorithm** builds the suffix tree in **O(m)** time.
- Searching for each pattern takes **O(k + |pattern|)** time.
- Performance is significantly faster than the naïve approach for large DNA sequences.



## 📚 Bibliography / References
https://en.wikipedia.org/wiki/Ukkonen%27s_algorithm

https://www.geeksforgeeks.org/dsa/ukkonens-suffix-tree-construction-part-1/​

https://cp-algorithms.com/string/suffix-tree-ukkonen.html​

https://www.baeldung.com/cs/ukkonens-suffix-tree-algorithm​

https://programmerspatch.blogspot.com/2013/02/ukkonens-suffix-tree-algorithm.html​

https://brenden.github.io/ukkonen-animation/​

https://www.youtube.com/watch?v=ALEV0Hc5dDk
