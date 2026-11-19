# Progress

## Current position

**Module 1.1 Sharpen C, session 1 in progress** (started 2026-11-19).

Next session: review Part A notes and the arena allocator in `unit1/1.1-c/`, re-quiz, then 1.1 session 2 (dynamic array and hash map).

Open decision: Module 0 (finish Nand2Tetris) or skip it. Session 1 starts Unit 1 directly; tick Module 0 as skipped if that stands.

## Running notes for the tutor

Weak spots, questions to revisit, and topics to re-quiz.

**Re-quiz next session:**
- What lives in `.rodata` vs `.bss` vs `.data`; why `char *s = "hello"` and `char s[] = "hello"` differ
- Signed overflow is UB, unsigned wraps; why `x + 1 > x` can fold to true
- Two's complement: all-zero bits, `INT_MAX` = `0x7FFFFFFF`, `sizeof(int)` on x86-64 Linux
- What `volatile` does and does not guarantee
- System V integer argument registers (rdi, rsi, rdx, rcx, r8, r9) and the return register (rax)

**Environment:** Windows 11 PC with no WSL installed yet (checked 2026-11-19). Toolchain setup is part of 1.1 session 1.

## Modules

### Module 0
- [ ] Module 0 (optional): Nand2Tetris projects 10 to 12

### Unit 1: Systems programming
- [ ] 1.1 Sharpen C: arena allocator, dynamic array, hash map
- [ ] 1.2 Bits, integers, floating point (Data Lab)
- [ ] 1.3 x86-64 assembly I (Bomb Lab)
- [ ] 1.4 x86-64 assembly II (freestanding NASM)
- [ ] 1.5 Memory hierarchy, linking, ELF (Cache Lab)
- [ ] 1.6 Processes, signals, I/O (Shell Lab)
- [ ] 1.7 Virtual memory and allocation (Malloc Lab)
- [ ] 1.8 Concurrency and networking (Proxy Lab)
- [ ] Capstone 1: M1 Boot
- [ ] Capstone 1: M2 Interrupts
- [ ] Capstone 1: M3 Memory
- [ ] Capstone 1: M4 Tasks
- [ ] Capstone 1: M5 User mode
- [ ] Capstone 1: M6 Files
- [ ] Capstone 1: M7 Shell

### Bridge A
- [ ] Bridge A: Rust

### Unit 2: Languages and compilers
- [ ] 2.1 Tree-walk interpreter in Rust
- [ ] 2.2 clox bytecode VM in C
- [ ] 2.3 Language design and type inference
- [ ] 2.4 Native codegen (Writing a C Compiler ch. 1 to 10)
- [ ] Capstone 2: M1 Design
- [ ] Capstone 2: M2 Front end
- [ ] Capstone 2: M3 IR
- [ ] Capstone 2: M4 VM backend
- [ ] Capstone 2: M5 Native backend
- [ ] Capstone 2: M6 Polish

### Bridge B
- [ ] Bridge B: Modern C++

### Unit 3: Database engines
- [ ] 3.1 Storage layout
- [ ] 3.2 Buffer pool (BusTub P1)
- [ ] 3.3 Indexes (BusTub P2)
- [ ] 3.4 Query execution (BusTub P3)
- [ ] 3.5 Transactions and recovery (BusTub P4)
- [ ] Capstone 3: M1 Storage
- [ ] Capstone 3: M2 Indexes
- [ ] Capstone 3: M3 SQL
- [ ] Capstone 3: M4 Execution
- [ ] Capstone 3: M5 Durability and transactions
- [ ] Capstone 3: M6 Graph queries

## Session log

| Date | Module | Covered | Next step |
|---|---|---|---|
| 2026-11-18 | Planning | Built the curriculum and tracker; diagnostic quiz on C memory layout, UB, `volatile` | Toolchain setup; Module 0 decision; start 1.1 |
| 2026-11-19 | 1.1 | Created this repo. Session 1 "Where things live": process memory map, the four diagnostic rules, System V argument registers. Set practicum: UB exploration + arena allocator | Install WSL2 + toolchain; do Part A and Part B; bring them to session 2 |
