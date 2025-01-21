# libcrust

[![libcrust-ci](https://github.com/lfazio/libcrust/actions/workflows/ci.yaml/badge.svg)](https://github.com/lfazio/libcrust/actions/workflows/ci.yaml)

C library to define data structure as proposed by Rust:
- Rc: Reference Counters
- Arc: Atomic Reference Counters
- Box: To allocate data on the heap
- Option: to define `Some(...)`/`None` data type
- Result: to define `Ok(...)`/`Err(...)` data type

# Standard build

```sh
meson setup builddir
meson compile -C builddir
```

# Coverage

```sh
meson setup builddir --reconfigure -Db_coverage=true
meson test -C builddir
ninja coverage-html -C builddir
```
