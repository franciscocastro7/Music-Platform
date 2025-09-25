# Music Streaming Platform – Data Processing and Query System

👨‍💻 Authors  
* Miguel Rocha Diegues – A107361 – migueldiegues24  
* Francisco Jorge Salgado de Castro – A104433 – franciscocastro7  

---

## 📁 Description

This project implements a modular system in C for analyzing and querying data from a **music streaming platform**, developed in two phases (Laboratórios de Informática III – 2024/2025).  

The system loads datasets about **musics, users, artists, albums and listening history** from CSV files, validates them, stores the information in memory, and supports multiple **queries** over the data.  

### ✅ Main Features
- **Data ingestion & validation** of CSV files (syntactic and logical checks).
- **Queries implemented:**
  - Q1: User/Artist summary  
  - Q2: Top-N artists by discography  
  - Q3: Most popular music genres in an age range  
  - Q4: Artist with most Top-10 appearances  
  - Q5: User recommendation system based on listening habits  
  - Q6: Annual user summary with detailed stats  
- **Three execution modes**:
  - `programa-principal`: batch execution from queries file  
  - `programa-interativo`: interactive CLI mode  
  - `programa-testes`: validation, performance & memory tests  
- **Memory management checked** with Valgrind (no leaks).  
- **Use of modular architecture** with headers (`.h`) and implementations (`.c`).  

---

## 🚀 Compilation

To compile the project:

```bash
make clean && make
```

This will generate the executables:
- `programa-principal`  
- `programa-interativo`  
- `programa-testes`  

---

## ▶️ Execution

1. **Main program (batch mode):**
   ```bash
   ./programa-principal <dataset_path> <queries_file>
   ```
   Example:
   ```bash
   ./programa-principal dataset/ input.txt
   ```

   Results will be written to `resultados/commandX_output.txt`.

2. **Interactive mode:**
   ```bash
   ./programa-interativo
   ```
   Allows execution of queries directly in the terminal.

3. **Testing program:**
   ```bash
   ./programa-testes <dataset_path> <queries_file> <expected_results_path>
   ```
   Example:
   ```bash
   ./programa-testes dataset/ input.txt resultados-esperados/
   ```

---

## 🧪 Automated Tests

The **testing program** evaluates:
- Correctness of query outputs vs expected results.  
- Execution time (per query & overall).  
- Memory usage.  

---

## 🧠 Project Structure

```
Music-Platform/
├── include/              # Header files (.h)
├── src/                  # Source files (.c)
├── resultados/           # Query results + validation error logs
├── dataset/              # CSV input files (not committed to repo)
├── relatorio-fase1.pdf   # Phase 1 report
├── relatorio-fase2.pdf   # Phase 2 report
├── programa-principal    # Main executable (after make)
├── programa-interativo   # Interactive executable (after make)
├── programa-testes       # Testing executable (after make)
└── Makefile
```
