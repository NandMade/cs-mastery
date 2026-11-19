# learning

My monorepo for the **Systems, Compilers & Databases** curriculum: three units (systems programming, compilers, database engines), two language bridges (Rust, modern C++), and three capstones (an x86-64 OS, a two-backend compiler, a SQL database with graph queries).

| Path | What's in it |
|---|---|
| [CURRICULUM.md](CURRICULUM.md) | The full plan: modules, resources, practicums, capstone milestones |
| [PROGRESS.md](PROGRESS.md) | Where I am, the module checklist, tutor notes, and the session log |
| [lessons/](lessons/) | One Markdown file per session: mini-lesson, practicum, reading |
| `unit1/`, `bridge-a/`, `unit2/`, `bridge-b/`, `unit3/` | My practicum code, one folder per module (e.g. `unit1/1.1-c/`) |
| `capstone1-os/`, `capstone2-lang/`, `capstone3-db/` | Capstone projects |

## Running a session

Open Claude Code in this folder and say "start the next session". [CLAUDE.md](CLAUDE.md) tells it how to read the tracker, quiz, teach, review the practicum, and log the session.

## Toolchain

x86-64 Linux: native or WSL2 (Ubuntu). See the setup section of [lessons/unit1/1.1-session-1.md](lessons/unit1/1.1-session-1.md).
