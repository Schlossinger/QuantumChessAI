# The Parallel Move Algorithm (Pattern Method)

**A New Dimension for Chess AI and Analysis**  
*By Dominik Schloss (Schlossinger)*

---

## 🚀 Introduction

Imagine if chess moves were no longer considered individually, but as **flowing patterns** that spread simultaneously across the entire board.  
That's exactly what the **Parallel Move Algorithm**, also known as the "Pattern Method," enables: An innovative approach that replaces classic move-tree logic with distributed **piece shares**—and thus opens up completely new possibilities for analysis and AI.

---

## 🔬 Basic Principle: Piece Shares Instead of Individual Moves

- **All pieces start with a 100% occupancy share on their field.**
- At each half-move, the share is **distributed** over the board according to the move possibilities—like a wave spreading out.
- **Multiple pieces** (even from different sides) can hold shares on the same square.
- For each of the 64 squares, **up to 32 piece shares** are tracked (all pieces from both sides).
- Additionally, for each square, sums are calculated:
    1. **Sum of white piece shares**
    2. **Sum of black piece shares**
    3. **Total sum of all piece shares**
    4. **"Empty field" share** (100% minus the total sum of all piece shares)

**The sum of all piece shares + the "empty field" share always equals 100% for each square.**

---

## 🧩 Step-by-Step Procedure

1. **Calculate all legal moves** (as in Minimax)
2. **Distribute piece shares proportionally to target squares**
    - e.g., with 4 possible moves: 25% to each target square
3. **Iteration over half-moves:**
    - With each half-move, the shares continue to spread across the board
    - Squares can simultaneously hold shares from multiple pieces and sides
    - The patterns of piece shares influence each other (reinforcement, weakening, "interferences")
4. **Pattern Analysis:**
    - The final distribution of piece shares serves as the basis for evaluating moves
    - Goal: Find the initial move that generates the most favorable patterns over time

---

## 🧮 Practical Example: Opening by White

Let's look at a typical chess opening by White:

At the beginning of the game, all 8 white pawns and the 2 knights can move. Each pawn has exactly two possible moves (from rank 2 to rank 3 or 4), and each knight also has two options.

**Calculation of move possibilities:**
- 8 pawns × 2 moves = **16 moves**
- 2 knights × 2 moves = **4 moves**
- Total: **20 possible moves**

**Distribution of piece shares:**
- Each piece starts with 100% on its square.
- This 100% is evenly distributed across all possible target squares:
    - **Per possible move:** 100% ÷ 20 moves = **5% per move**
- **For each individual piece** with two possible moves:
    - **2 moves × 5% = 10%** are distributed to the two target squares.
    - The **remaining share (90%) stays on the originating square**.

**Result:**
- Each target square receives 5% additional piece share.
- The starting squares initially retain 90% of their original share.
- This creates dynamic patterns that form the basis for further iterations and analysis.

**Mathematical Short Formula:**  
For a piece with \( n \) possible moves and occupancy share \( A \):

- Share per target square: \( \frac{A}{n} \)
- Remaining share on the origin square: \( A - n \times \frac{A}{n} \)

---

## 🎯 Advantages & Potential

- **Fewer redundant calculations** than classic move trees
- **Dynamic evaluation:** Moves are analyzed as pattern developments, not just as single positions
- **Ideally combinable with AI & Machine Learning** (e.g., neural networks, stochastic methods)
- **New visualizations:** Heatmaps, share maps & dynamic pattern analysis

---

## ⚙️ Mathematical Structure

- **64 squares × max. 32 piece shares** = 2048 variables per iteration step
- **Each share is a number from 0%–100%**, sum of all shares per square ≤ 100%
- **Four sums per square:** white, black, total, empty
- **Iterative distribution:** The distribution matrix is updated with each half-move

---

## 📊 Visualizations

*Here you could insert sample heatmaps or diagrams!*  
*(Please add a PNG, SVG, or animated GIF as `/img/heatmap1.png`)*

---

## 🗣️ Call to Action

**Interested in discussion, feedback, improvement, or cooperation?**  
**Comment, share, fork, or write to me—**  
**Together, let's take the chessboard to a new level!**

---