# GrammarGuard-C 🛡️

**GrammarGuard-C** is a high-performance, modular system implemented in C for detecting structural risks in Context-Free Grammars (CFGs). Specifically designed for compiler engineers and language designers, it identifies both **Direct** and **Indirect Left Recursion**—the primary cause of infinite loops and stack overflows in top-down parsers like LL(1) and Recursive Descent.

![C](https://img.shields.io/badge/Language-C-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Build](https://img.shields.io/badge/Build-Clang%2FGCC-orange.svg)

---

## 🚀 Key Features

*   **Universal Syntax Support**: Seamlessly parses `->`, `::=`, `:=`, and `=` delimiters without requiring user reformatting.
*   **Dynamic Symbol Identification**: Automatically identifies Non-Terminals based on their position (LHS) rather than case-sensitivity.
*   **Graph-Based Analysis**: Models grammar dependencies using an advanced directed graph structure for mathematically sound detection.
*   **Deep Cycle Detection**: Uses a backtracking DFS to identify complex "hidden" indirect cycles and calculates exact **Recursion Depth**.
*   **Dual Mode Operation**:
    *   **Batch Mode**: Process pre-written `.txt` grammar files.
    *   **Interactive Mode**: A terminal-based "sandbox" for rapid grammar design and hypothesis testing.
*   **Modular Architecture**: Clean separation of concerns between parsing, graph building, and recursion logic.

---

## 📂 Project Structure

```text
├── main.c          # Entry point and I/O orchestration
├── parser.c/h       # Universal grammar parsing and symbol table management
├── graph.c/h        # Dependency graph construction (Adjacency List)
├── recursion.c/h    # DFS-based cycle detection and depth metrics
├── utils.c/h        # Memory management and string utility functions
├── grammar.txt      # Sample textbook grammar
└── universal_grammar.txt # Sample with mixed notation (BNF, EBNF, etc.)
```

---

## 🛠️ Installation & Usage

### 1. Prerequisites
Ensure you have a C compiler installed (`clang` or `gcc`).

### 2. Compilation
```bash
clang main.c parser.c graph.c recursion.c utils.c -o grammar_analyzer
```

### 3. Running Batch Mode
```bash
./grammar_analyzer grammar.txt
```

### 4. Running Interactive Mode
```bash
./grammar_analyzer
```
*In interactive mode, type your rules line-by-line and press `Ctrl+Z` (Windows) or `Ctrl+D` (Linux) to run the analysis.*

---

## 📊 Sample Analysis

### Input:
```text
S -> A
A -> S | b
```

### Output:
```text
--- Left Recursion Risk Detection Report ---

NonTerminal: S
Has_Left_Recursion: 1
Type: Indirect
Recursion_Depth: 2

NonTerminal: A
Has_Left_Recursion: 1
Type: Indirect
Recursion_Depth: 2
```

---

## 🧠 Logic & Algorithms

The system converts raw production rules into a **Directed Dependency Graph** where an edge `A -> B` exists if non-terminal `B` is a starting symbol in any production of `A`. It then performs a **Backtracking Depth-First Search** starting from each node to identify cycles. If a cycle is found, the system measures its length to provide the **Recursion Depth**—a critical metric for determining the complexity of the grammar risk.

---

## 📜 License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👤 Author
**Santhosh R**
*   Department: AIML-A, 3rd Year
*   Reg No: RA2311026050077
