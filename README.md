
markdown
Kopieren
Bearbeiten
# 🎲 Snakes and Ladders Simulator (MCMC-Based)

This project is a **Snakes and Ladders game simulator** implemented in **C** using **Markov Chain Monte Carlo (MCMC)** methods. It simulates thousands of games on customizable boards and computes various statistics such as the average number of moves to win, shortest winning sequences, and how often snakes and ladders are used.

---

## 📌 Features

- Custom board size (NxM), default: 10x10 (100 squares)
- Configurable snakes and ladders from `.cfg` file
- Support for **uniform** and **non-uniform** dice
- Simulates thousands of games
- Computes:
  - 📈 Average number of moves to win
  - 🏆 Shortest winning path
  - 📊 Frequency of each snake and ladder usage
- Clean modular C code (`.c`/`.h` structure)
- Command-line file input
- Defensive programming: No memory leaks or crashes

---

## 🛠️ Project Structure

.
├── board.c / board.h # Board structure and snake/ladder logic
├── config.c / config.h # Load board config from file
├── dice.c / dice.h # Dice rolling (uniform / weighted)
├── graph.c / graph.h # Optional graph generation (for future extensions)
├── simulator.c / simulator.h # Simulation logic (MCMC)
├── stats.c / stats.h # Statistics collection & reporting
├── main.c # Entry point
├── board1.cfg / board2.cfg # Example board configuration files
├── Makefile (optional) # For easy compilation
└── README.md # This file

yaml
Kopieren
Bearbeiten

---

## 📋 Example Board Config (`board1.cfg`)

Example configuration
BOARD 10 10
LADDER 3 22
LADDER 5 8
SNAKE 17 4
SNAKE 99 7

yaml
Kopieren
Bearbeiten

---

## ▶️ How to Run

### 🔧 Compile

```bash
clang -Wall -Wextra -Werror -o snakes main.c board.c config.c dice.c simulator.c stats.c graph.c
🚀 Execute
bash
Kopieren
Bearbeiten
./snakes board1.cfg
Replace board1.cfg with your own configuration file.

📈 Sample Output
plaintext
Kopieren
Bearbeiten
Board Size: 10x10 (100 squares)
Ladders (2):
  Ladder from 3 to 22
  Ladder from 5 to 8
Snakes (2):
  Snake from 17 to 4
  Snake from 99 to 7

🔁 Simulating 1000 games...
📈 Average number of moves to win: 39.42

🏆 Shortest winning game found in 17 moves:
    Roll sequence: 3 4 5 ...

📊 Snake and Ladder Usage Statistics (across 1000 games):
🐍 Snakes:
  Snake 1: from 17 to 4 — used 58 times (0.06 per game)
  Snake 2: from 99 to 7 — used 0 times (0.00 per game)

🪜 Ladders:
  Ladder 1: from 3 to 22 — used 131 times (0.13 per game)
  Ladder 2: from 5 to 8 — used 67 times (0.07 per game)
📚 Notes
Only plain-text .c and .h files should be committed.

No binaries, object files, or archives should be pushed.

Memory leaks are avoided, and program aborts after max steps to prevent infinite loops.

👨‍💻 Author
Amina Khalifah
