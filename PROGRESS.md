# Progress

## Current position

**Module 1.1 Sharpen C, session 2 in progress** (started 2026-11-24). Session 1 practicum (UB exploration, arena) done. Session 2 practicum: dynamic array and hash map in `unit1/1.1-c/containers/`, about two weeks.

Next session (1.1 session 3): re-quiz, review both containers against the session 2 done-when list. If they pass, tick 1.1 and start 1.2.

## Running notes for the tutor

Weak spots, questions to revisit, and topics to re-quiz.

**Re-quiz next session:**
- Hex notation: on 2026-11-24 the learner thought `0x` meant binary. Explained hex (4 bits per digit, last digit = addr mod 16) and `0b`. Next time, give an address in hex and ask for its value mod 8, 16 and 64 without converting to decimal. Recheck before 1.2, which leans on it hard.
- Unsigned negation (`-x` is 2ᴺ − x mod 2ᴺ) and integer promotion of narrow types (`-(unsigned char)1` is int -1). Taught 2026-11-24 when the learner asked; promotion returns in 1.2.
- `realloc` failure handling, stale pointers after a vector grows, tombstones vs empty slots (new in session 2)
- What lives in `.rodata` vs `.bss` vs `.data`; why `char *s = "hello"` and `char s[] = "hello"` differ (answered well 2026-11-24; lower priority)
- Signed overflow is UB, unsigned wraps; why `x + 1 > x` can fold to true. 2026-11-24: concept right, but on `UINT_MAX + 1 > UINT_MAX` they reasoned "0 + 1 < UINT_MAX" instead of "0 > UINT_MAX is false". Ask them to trace an unsigned comparison step by step.
- Two's complement: all-zero bits, `INT_MAX` = `0x7FFFFFFF`, `sizeof(int)` on x86-64 Linux
- What `volatile` does and does not guarantee
- System V integer argument registers (rdi, rsi, rdx, rcx, r8, r9) and the return register (rax)
- Why gcc prints 1 for `x + 1 > x` even at -O0 and UBSan misses it, while clang prints 0 and UBSan flags it (UB = compilers may legitimately disagree; sanitizers only see code that survives folding)
- Alignment is a property of the type being allocated (`alignof(T)`), not of the previous allocation. The learner first thought padding was always `8 - allocated % 8` (also off by one when already aligned). Ask them to work a padding example by hand.
- Why UBSan needs `-fno-sanitize-recover=all` in a test build (answered correctly 2026-11-24; tie it to valgrind's `--error-exitcode` next time)
- Warning vs error: answered correctly 2026-11-24 (it's a warning; a binary is built). Stuck; drop after one more check.
- Off-by-one in alignment padding: on 2026-11-24 they worked three hex examples correctly and wrote the branch-free `(align - addr % align) % align` themselves. `-addr & (align - 1)` was explained; ask them to derive it again in 1.2.
- Tests that pass on NULL: the first arena tests only masked the pointer (`(uintptr_t)p & 7`), so NULL passed. One (`arena_alloc(ar, 16, SIZE_MAX)`) still does. Ask what a test must assert before checking a property of a result.
- Power-of-two check: they wrote a popcount loop. Ask for the one-expression `n && !(n & (n - 1))` and why it works.
- Dangling pointers: gcc replaces `return &local` with NULL (crash); clang returns the real address, and at -O0 `*p` happened to print the correct 0, the most dangerous outcome. Only clang's ASan names the bug (`stack-use-after-return`).

**Part A (done 2026-11-19), optional extras not yet tried:** clang on a (-O2 deletes the write and exits 0) and on b.

**Part B (done 2026-11-24):** `make test` passes under gcc and clang with the full sanitizer flags. Extra edge cases also pass: exact fill, the allocation after a full arena, `SIZE_MAX` and `SIZE_MAX - 1` on a partly full arena, just-over vs exactly-remaining, reset returning the buffer start, and align 0, 3, 12, `SIZE_MAX` and an align larger than the arena. Style points (`static` helpers, the two redundant capacity checks, the `SIZE_MAX`-align test asserting `NULL`) fixed in 6c62013. Stretch (chain blocks) not attempted; offer it again if the dynamic array goes quickly.

**Session 2 containers review, 2026-11-28 (at fc7ff91):** `make test` passes under gcc and clang and `make valgrind` is clean, but the map has bugs the tests don't reach. (A 2026-11-25 Part A review and the lesson's 1.5 → 1.4 threshold fix were committed to the old Windows copy and lost in the move to GitHub; re-applied here.)
- **vec: passes** except one test gap. All five 2026-11-25 blockers are fixed (linking, inverted checks, capacity updated before `realloc`, `main` returning failures, `elem_size` 0). Remaining: the growth test checks only the first step (16 → 24); the done-when asks it to record every capacity change over 1,000,000 pushes. The code satisfies it (×1.5 from 16 never drops below ×1.49).
- **map: not passed.** Probe (scratch, not in the repo) results:
  1. `map_len` never goes down: `map_remove` bumps `dead` but not `length`, and reusing a tombstone doesn't count the new key. Put + remove gives len 1; 200k put/remove churn gives len 175136.
  2. Duplicate keys: `slot_put` takes the first tombstone before checking the rest of the bucket for the same key. Put a, put k (same bucket), remove a, put k → two `k`s, len 2; after removing k it is still found. The done-when's "then insert new keys" step is missing from the tests and would catch it.
  3. The tombstone is a real `""` string, compared with `strcmp`: `map_get("")` finds a removed entry (returned a stale value 7), `map_remove("")` frees the static tombstone (ASan: bad free), and `map_destroy` leaks a real `""` key. Pointer comparison is the fix region (`map_destroy`, `map_get_index`).
  4. `map_grow` re-inserts tombstones (skips only NULL), then sets `dead = 0`, so dead slots survive every grow and `dead` underflows when one is reused.
  5. A full 8-entry bucket makes `map_put` fail for good: no grow-and-retry or probe of the next bucket.
  6. `map_put` doesn't check `malloc`; `map_create` leaks the `Map` when `calloc` fails.
  - Nits: `int hash` in `slot_put` vs `uint64_t` in `map_get_index`; unused `#include "../arena/arena.h"`; clang `-Wnewline-eof` in `lib/`; `test_vec.o`, `test_vec.d` and `compile_commands.json` are still tracked in git (needs `git rm --cached`).
- **Copy vs original, third time:** `MapEntry entry = m->entries[index]` in `map_remove` changed a copy (after `vec_pop`'s `out =` and the `Slot` initializer). Fixed now, but quiz struct copies vs pointers to slots in session 3.
- Out-parameters were weak on 2026-11-25 (thought you can't write through one into caller storage; `realloc` already copies). Re-quiz.

**Background gap:** comfortable with C itself but has no experience with real-world C build systems or automated testing. Taught a Makefile + hand-rolled CHECK-macro tests in the 1.1 supplement (2026-11-19); review the arena's Makefile and tests as closely as its code. Introduce pattern rules and `-MMD -MP` when a practicum grows past a few files, and CMake properly in Bridge B.

**Bit-trick intuition (raised 2026-11-24):** the learner is worried they can't intuit binary tricks (e.g. exponentiation by squaring). Reassured: the tricks are learned folklore built from a few primitives (`x & (x-1)`, `x & -x`, mask = mod by a power of two, `-x = ~x + 1`). In 1.2, have them work 4- or 8-bit examples by hand and derive each trick from those primitives before seeing a solution, and point out when they've derived one themselves.

**Environment:** Debian on WSL2, gcc 14.2 and clang 19.1. Learner codes in `~/learning` there; `origin` is GitHub since 2026-11-28 (see CLAUDE.md). `pull.rebase=true` set in the Debian repo.

## Modules

### Module 0
- [x] ~~Module 0 (optional): Nand2Tetris projects 10 to 12~~ Skipped (decided 2026-11-19)

### Unit 1: Systems programming
- [ ] 1.1 Sharpen C: arena allocator, dynamic array, hash map (Part A UB exploration and Part B arena done)
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
| 2026-11-24 | 1.1 | Reviewed the Part B arena twice. First pass found off-by-one padding (exact fit returned NULL), no power-of-two check (align 0 divided by zero), unchecked `malloc`, and tests that passed on NULL. All fixed; Part B passes its done-when list under gcc and clang | Re-quiz, then 1.1 session 2: dynamic array and hash map |
| 2026-11-24 | 1.1 | Session 2 "Growing Things". Quiz: `.rodata` vs stack array right; hex notation was new (thought `0x` was binary); padding by hand right, wrote the branch-free expression; signed-overflow folding right, slipped tracing `UINT_MAX + 1 > UINT_MAX`; sanitizer-recover and warning vs error right. Taught dynamic arrays, `realloc` traps, open addressing, deletion, pattern rules with `-MMD -MP`, valgrind vs ASan, gdb basics. Added `*.d` to `.gitignore` | Build `unit1/1.1-c/containers/` (vec, then map) with `make test` and `make valgrind`; bring it to session 3 |
| 2026-11-28 | 1.1 | Reviewed both containers (see running notes). vec passes apart from the full growth test; map not passed: `map_len` ignores removes, duplicate keys via tombstone reuse, `""` key collides with the tombstone, tombstones survive grow, full bucket fails the put. Repo moved to GitHub; restored lost tutor changes | Fix the map, add the growth and re-insert tests, bring back for a re-review |
