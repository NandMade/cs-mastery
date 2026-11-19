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

x86-64 Linux via WSL2 (Debian). See the setup section of [lessons/unit1/1.1-session-1.md](lessons/unit1/1.1-session-1.md).

## Workflow

Code, build and commit in the Debian clone (`~/learning`), then `git push`: its `origin` is the Windows copy at `C:\Users\DArant\source\repos\learning`, which updates its files on push. Run `git pull` in Debian before starting work to pick up new lessons and tracker updates. Pushes are refused while the Windows copy has uncommitted changes.

Executables have no extension and are ignored in practicum folders, so give every source or notes file an extension (Makefiles excepted).
