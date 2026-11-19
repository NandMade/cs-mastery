# Progress

## Current position

**Module 1.1 Sharpen C, session 1 in progress** (started 2026-11-19). Part A done; Part B (arena allocator) next.

Next session: review the arena allocator in `unit1/1.1-c/arena/` against its done-when list, re-quiz, then 1.1 session 2 (dynamic array and hash map).

## Running notes for the tutor

Weak spots, questions to revisit, and topics to re-quiz.

**Re-quiz next session:**
- What lives in `.rodata` vs `.bss` vs `.data`; why `char *s = "hello"` and `char s[] = "hello"` differ
- Signed overflow is UB, unsigned wraps; why `x + 1 > x` can fold to true
- Two's complement: all-zero bits, `INT_MAX` = `0x7FFFFFFF`, `sizeof(int)` on x86-64 Linux
- What `volatile` does and does not guarantee
- System V integer argument registers (rdi, rsi, rdx, rcx, r8, r9) and the return register (rax)
- Why gcc prints 1 for `x + 1 > x` even at -O0 and UBSan misses it, while clang prints 0 and UBSan flags it (UB = compilers may legitimately disagree; sanitizers only see code that survives folding)
- Alignment is a property of the type being allocated (`alignof(T)`), not of the previous allocation. The learner first thought padding was always `8 - allocated % 8` (also off by one when already aligned). Ask them to work a padding example by hand.
- Why UBSan needs `-fno-sanitize-recover=all` in a test build
- Warning vs error: the learner called `-Wreturn-local-addr` a "compiler error" (it's a warning; the binary is still built). Check it has stuck.
- Dangling pointers: gcc replaces `return &local` with NULL (crash); clang returns the real address, and at -O0 `*p` happened to print the correct 0, the most dangerous outcome. Only clang's ASan names the bug (`stack-use-after-return`).

**Part A (done 2026-11-19), optional extras not yet tried:** clang on a (-O2 deletes the write and exits 0) and on b. Minor style to watch in Part B: `int main()` should be `int main(void)` in C17.

**Background gap:** comfortable with C itself but has no experience with real-world C build systems or automated testing. Taught a Makefile + hand-rolled CHECK-macro tests in the 1.1 supplement (2026-11-19); review the arena's Makefile and tests as closely as its code. Introduce pattern rules and `-MMD -MP` when a practicum grows past a few files, and CMake properly in Bridge B.

**Environment:** Debian on WSL2, gcc 14.2 and clang 19.1. Learner codes in `~/learning` there and pushes to the Windows copy (see CLAUDE.md). `pull.rebase=true` set in the Debian repo.

## Modules

### Module 0
- [x] ~~Module 0 (optional): Nand2Tetris projects 10 to 12~~ Skipped (decided 2026-11-19)

### Unit 1: Systems programming
- [ ] 1.1 Sharpen C: arena allocator, dynamic array, hash map (Part A UB exploration done)
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
| 2026-11-19 | 1.1 | Created this repo. Session 1 "Where things live": process memory map, the four diagnostic rules, System V argument registers. Set practicum: UB exploration + arena allocator. Decided to skip Module 0 | Install WSL2 + toolchain; do Part A and Part B; bring them to session 2 |
| 2026-11-19 | 1.1 | Moved to Debian on WSL with a push-to-Windows workflow. Reviewed Part A: a and c done, b never exercised the bug (notes only cover surprises, as the lesson asked) | Finish Part A follow-ups (see running notes); start Part B arena |
| 2026-11-19 | 1.1 | Re-reviewed Part A: `stack.c` now calls `make_counter` and dereferences it; gcc crashes on the NULL it substitutes, UBSan and ASan report it. Part A done | Part B arena allocator; bring it to session 2 |
| 2026-11-19 | 1.1 | Supplement for Part B: what an arena is, alignment as a property of the type (`alignof`), Make basics, hand-rolled C tests, `-fno-sanitize-recover=all` (added to the done-when flags) | Read the supplement, then build the arena with `make test` |
