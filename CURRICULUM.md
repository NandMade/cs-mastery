# Systems, Compilers & Databases: Personal Curriculum

Created 2026-11-18. Progress lives in [PROGRESS.md](PROGRESS.md), not here.

## How this works

Three units, two language bridges, three capstones. At about 4 hours a week the whole path takes roughly 3 to 3.5 years; at a steady 5 hours, closer to 2.5. Every module ends in working code, so each stage pays off on its own even if you stop there.

**Pacing.** Each week is about 1.5 hours of video or reading and 2.5 hours of building. Week estimates below assume 4 hours. Slower is fine: the tracker records where you are, not where a calendar says you should be.

**Session format.** Open Claude Code in this repo and ask for the next session. It reads `PROGRESS.md`, runs a 3-to-5 question warm-up quiz on earlier material, teaches the next lesson (written to `lessons/`), sets or reviews a practicum, and logs the session. Details in [CLAUDE.md](CLAUDE.md).

**Primary language per unit.** Unit 1 is C and x86-64 assembly. Unit 2 is written in Rust (one C detour for the bytecode VM). Unit 3 is C++. Each bridge ramps the next language up before you need it.

**Dev environment.** An x86-64 Linux toolchain: gcc or clang, gdb, make, nasm, QEMU, and later rustup and CMake. On an Intel or AMD machine, native Linux or WSL2 works. On Apple Silicon, use an x86-64 Linux VM or a small cloud VM, because the assembly units and the OS capstone target x86-64. Everything lives in this one monorepo with a folder per module.

**Grading.** No grades, but every practicum has a done-when line. A module is done when its practicum passes that line, not when the videos are watched.

## Roadmap at a glance

```
Module 0 (opt.) ─► Unit 1: Systems + x86-64 ─► Capstone 1: OS on QEMU
                                                      │
                   Bridge A: Rust ◄───────────────────┘
                        │
                        ▼
                   Unit 2: Languages + compilers ─► Capstone 2: own language, VM + native
                                                      │
                   Bridge B: Modern C++ ◄─────────────┘
                        │
                        ▼
                   Unit 3: Database engines ─► Capstone 3: SQL database + graph queries
```

Each unit's capstone feeds the next: your OS can run programs from your compiler, and your compiler skills build the database's SQL front end. Doing Module 0 first shifts everything about two months later.

## Module 0 (optional): finish The Elements of Computing Systems

Halfway through Nand2Tetris, with a VM translator working. Finishing it is the cheapest warm-up available: projects 9 to 12 preview Units 1 and 2 in miniature. Skip it to start on x86-64 now; nothing later depends on it.

| Part | Work | Est. weeks |
|---|---|---|
| Projects 10 and 11 | Jack syntax analyzer, then code generator to your VM language | 5 |
| Project 12 | Jack OS library: memory allocator, math, screen, I/O | 3 |

Video: the authors' Nand2Tetris Part II course on Coursera (free to audit).

**Done when:** a Jack program compiled by your compiler runs on the VM emulator using your own OS library.

## Unit 1: Systems programming and x86-64 assembly

**Goal:** understand a program from transistor-adjacent detail up to the kernel, then write that kernel. About 30 weeks of foundations plus a 34-week OS capstone (roughly 15 months). Language: C and x86-64 assembly.

**Core resources.** CS:APP 3rd ed. (Bryant and O'Hallaron) with the CMU 15-213 lecture videos (Fall 2015 and Fall 2017 are the complete public sets) and the self-study labs. OSTEP (free) for OS theory. The xv6 book for how a small real kernel is laid out; MIT's current xv6 targets RISC-V, so read it for design, not for x86 code.

| # | Module | Watch / read | Practicum, done when | Weeks |
|---|---|---|---|---|
| 1.1 | Sharpen C: tooling, UB, sanitizers, debugging | K&R refresh as needed; gdb, valgrind, ASan/UBSan docs | Arena allocator, dynamic array and hash map in C with tests; clean under ASan and UBSan | 3 |
| 1.2 | Bits, integers, floating point | CS:APP ch. 2; 15-213 lectures 2 to 4 | Data Lab passes the checker | 2 |
| 1.3 | x86-64 assembly I: registers, addressing, control flow, System V ABI, stack frames | CS:APP ch. 3; 15-213 lectures 5 to 9 | Bomb Lab: all phases defused using gdb only | 5 |
| 1.4 | x86-64 assembly II: freestanding code, syscalls, no libc | Intel SDM vol. 1 skim; System V ABI doc | NASM programs with no libc: cat, a number printer, and a few asm functions called from C. Attack Lab optional | 3 |
| 1.5 | Memory hierarchy, caches, linking, ELF | CS:APP ch. 6 to 7; lectures 10 to 13 | Cache Lab, plus a small ELF header and section dumper in C | 4 |
| 1.6 | Processes, signals, system I/O | CS:APP ch. 8 and 10; lectures 14 to 16 | Shell Lab: job-control shell passes the trace tests | 4 |
| 1.7 | Virtual memory and dynamic allocation | CS:APP ch. 9; lectures 17 to 20 | Malloc Lab: segregated-list allocator scoring well on the driver | 5 |
| 1.8 | Concurrency and network programming | CS:APP ch. 11 to 12; lectures 21 to 26 | Proxy Lab: concurrent caching HTTP proxy | 4 |

### Capstone 1: a small x86-64 operating system on QEMU

Read the matching OSTEP chapters alongside each milestone. References: OSDev wiki, Intel SDM vol. 3, and *Writing an OS in Rust* for a second perspective. Boot through GRUB with Multiboot2 and write the 32-to-64-bit long-mode transition yourself; it is the best assembly exercise in the whole curriculum.

| Milestone | What you build | Done when | Weeks |
|---|---|---|---|
| M1 Boot | Multiboot2 header, GDT, page tables for identity map, jump to long mode, call C | "Hello" on serial and screen from 64-bit C code in QEMU | 4 |
| M2 Interrupts | IDT, exception handlers, APIC or PIC, timer, PS/2 keyboard | Page fault prints a register dump; keypresses echo | 4 |
| M3 Memory | Physical frame allocator from the boot memory map, 4-level paging API, kernel heap | kmalloc and kfree pass a stress test; higher-half kernel | 5 |
| M4 Tasks | Kernel threads, context switch in asm, round-robin scheduler, locks | Several kernel threads print interleaved under the timer | 5 |
| M5 User mode | Ring 3, TSS, syscall/sysret, per-process address spaces, ELF loader | A user program built with your toolchain calls write and exit | 6 |
| M6 Files | VFS layer, initrd (tar), then a simple disk filesystem over virtio-blk or ATA | Read and write files that survive a reboot | 6 |
| M7 Shell | User-space shell with fork/exec-style spawn, a few utilities | Boot to a prompt, run ls and cat from disk | 4 |

Stretch: SMP bring-up, a virtio-net driver, and later, running programs compiled by your Unit 2 compiler on this OS.

## Bridge A: Rust (5 weeks)

Rust becomes the implementation language for Unit 2, so it gets a focused ramp now, while your C instincts are fresh enough to see what the borrow checker is protecting you from.

| Week | Work | Done when |
|---|---|---|
| 1 to 2 | *The Rust Programming Language* ch. 1 to 10, plus Rustlings | Rustlings exercises through traits and generics pass |
| 3 | Book ch. 13 to 16: closures, iterators, smart pointers, concurrency | Port your Unit 1 hash map to Rust with the same tests |
| 4 to 5 | Unsafe Rust, no_std, FFI with C | A Rust module (a driver or the allocator) linked into your OS, or the first posts of *Writing an OS in Rust* done in a scratch repo |

## Unit 2: Programming languages and compilers

**Goal:** design a language and compile it two ways, to your own bytecode VM and to native x86-64. About 28 weeks of foundations plus a 28-week capstone (roughly 13 months). Language: Rust, with one deliberate detour into C.

**Core resources.** *Crafting Interpreters* (Nystrom, free online). *Writing a C Compiler* (Sandler, No Starch 2024): builds a C subset to x86-64 assembly chapter by chapter, with pseudocode you can write in Rust, and ships a test suite. *Engineering a Compiler* (Cooper and Torczon) as the reference for IR, optimization and register allocation.

| # | Module | Watch / read | Practicum, done when | Weeks |
|---|---|---|---|---|
| 2.1 | Scanning, recursive-descent parsing, ASTs, tree-walk evaluation, closures, classes | *Crafting Interpreters* part II | Lox tree-walk interpreter written in Rust (not Java) passes the book's test suite | 6 |
| 2.2 | Bytecode, stack VMs, hashing, closures as upvalues, mark-sweep GC | *Crafting Interpreters* part III | clox in C passes the test suite; GC stress mode clean under ASan | 8 |
| 2.3 | Language design: semantics, type systems, inference, error design | Selected chapters of *TAPL* (Pierce) or *Essentials of Programming Languages*; targeted lessons | A typechecker for a small typed lambda calculus with Hindley-Milner inference | 4 |
| 2.4 | Native codegen: three-address IR, x86-64 emission, stack frames, System V calling convention | *Writing a C Compiler* part I (ch. 1 to 10) | Your Rust compiler passes the book's tests through ch. 10 | 10 |

### Capstone 2: your own language, two backends

| Milestone | What you build | Done when | Weeks |
|---|---|---|---|
| M1 Design | Language spec: syntax, semantics, type system, memory model, what makes it yours | A 3 to 5 page spec plus 20 example programs with expected output | 3 |
| M2 Front end | Lexer, parser with good error messages, name resolution, typechecker | All examples parse and typecheck; bad programs get located errors | 6 |
| M3 IR | A typed IR shared by both backends, with constant folding and dead-code elimination | IR dump matches hand-checked expectations | 4 |
| M4 VM backend | Bytecode compiler, VM, garbage collector | Example suite runs on the VM | 5 |
| M5 Native backend | x86-64 assembly emission, register allocation (linear scan), a small runtime in C | Same suite produces identical output as native binaries | 7 |
| M6 Polish | Standard library basics, a test runner, benchmarks VM vs native | Benchmark write-up comparing both backends | 3 |

Stretch: compile programs for the Unit 1 OS (your syscall ABI as a target), or a third backend for WebAssembly.

## Bridge B: Modern C++ (5 weeks)

BusTub and the database capstone are in C++, so this bridge targets the subset that matters for systems work: RAII, value semantics, move semantics, smart pointers, templates, and the concurrency library.

| Week | Work | Done when |
|---|---|---|
| 1 to 2 | *A Tour of C++* (Stroustrup, 3rd ed.) plus learncpp.com for gaps | Rewrite your C arena allocator as a RAII class with move-only semantics |
| 3 | Templates, concepts, the STL algorithms, CMake | A generic LRU cache template with tests (reused in the buffer pool) |
| 4 to 5 | std::thread, mutexes, atomics, memory model basics; sanitizers in C++ | BusTub Project 0 (the C++ primer) passes its tests |

## Unit 3: Database engines

**Goal:** build the storage engine, query engine and transaction layer of a relational database, then add graph queries on top. About 20 weeks of foundations plus a 28-week capstone (roughly 11 months). Language: C++ (Rust is a fine alternative for the capstone).

**Core resources.** CMU 15-445/645 (Pavlo): self-learners should use the Fall 2025 lectures on YouTube. Its BusTub projects are the practicums below; follow the Fall 2025 handouts. *Database Internals* (Petrov) for storage and distribution depth. *Build Your Own Database From Scratch* (Smith) and the cstack "Let's Build a Simple Database" tutorial as build-along companions.

| # | Module | Watch / read | Practicum, done when | Weeks |
|---|---|---|---|---|
| 3.1 | Relational model, SQL, storage layout, pages, tuples, files | 15-445 lectures 1 to 5 | Hand-write a slotted-page format in C++ with insert, delete and compaction tests | 3 |
| 3.2 | Buffer pools, replacement policies, disk scheduling | Lectures 6 to 7 | BusTub P1: buffer pool manager passes the tests | 4 |
| 3.3 | Hash tables, B+ trees, index concurrency (latch crabbing) | Lectures 8 to 10 | BusTub P2: index passes tests including the concurrent ones | 5 |
| 3.4 | Sorting, joins, query execution, optimization | Lectures 11 to 15 | BusTub P3: executors and a few optimizer rules | 4 |
| 3.5 | Concurrency control (2PL, MVCC), logging, ARIES recovery | Lectures 16 to 21; the ARIES paper | BusTub P4: transactions pass the tests | 4 |

### Capstone 3: your own SQL database with graph queries

All three units meet here: systems C++ for storage, Unit 2 front-end skills for the SQL parser and planner. For the graph side, aim at SQL/PGQ, the property-graph extension to SQL, so graph queries are a pattern-matching clause inside ordinary SQL.

| Milestone | What you build | Done when | Weeks |
|---|---|---|---|
| M1 Storage | Pager, slotted pages, free list, buffer pool | Tables of 1M rows insert and scan correctly | 4 |
| M2 Indexes | Disk-based B+ tree with range scans | Point and range queries use the index; tree survives restart | 5 |
| M3 SQL | Lexer, parser, binder, catalog for CREATE TABLE, INSERT, SELECT, UPDATE, DELETE, WHERE, joins, GROUP BY | A small SQL test corpus returns correct results | 5 |
| M4 Execution | Logical and physical plans, iterator (Volcano) executors, a rule-based optimizer | EXPLAIN prints plans; index scans chosen when they should be | 4 |
| M5 Durability and transactions | Write-ahead log, crash recovery, MVCC with snapshot isolation | Kill -9 mid-workload loses no committed data; concurrent tests pass | 6 |
| M6 Graph queries | Property-graph definition over node and edge tables, adjacency index, MATCH patterns with variable-length paths compiled to joins or recursive traversal | Shortest-path and friends-of-friends queries return correct results on a sample social graph | 4 |

Stretch: speak a subset of the PostgreSQL wire protocol so psql can connect, or add a cost-based optimizer with statistics.

## Language mastery thread

Each language is mastered by building something hard in it. Mastery means you can read idiomatic production code in it, debug it at the machine level, and know its sharp edges.

| Language | Where it is learned | Proof of mastery | Extra reading |
|---|---|---|---|
| x86-64 assembly | Modules 1.3 and 1.4, OS boot and context switch, compiler backend 2.4 and capstone M5 | Hand-written long-mode boot code and a working register allocator | Intel SDM vols. 1 to 3; System V ABI; Compiler Explorer daily |
| C | All of Unit 1, clox in 2.2, the native runtime in Capstone 2 | An OS kernel and a GC that run clean under sanitizers | *Effective C* (Seacord); *Modern C* (Gustedt) |
| Rust | Bridge A, all of Unit 2 | A two-backend compiler with idiomatic error handling and no needless clones | *Rust for Rustaceans* (Gjengset); the Rustonomicon |
| C++ | Bridge B, all of Unit 3 | A database with correct concurrent indexes and recovery | *Effective Modern C++* (Meyers); *C++ Concurrency in Action* (Williams) |

Standing habit: once a week, take one function you wrote and read the assembly your compiler produced for it.
