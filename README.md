# `valgrind`

## Usage

Run `python3 -m pip install valgrind`.

In `benchmark.py` put:

```python
import valgrind

if __name__ == "__main__":
  some_startup_code()
  valgrind.callgrind_start_instrumentation()
  some_expensive_function()
  valgrind.callgrind_stop_instrumentation()
  valgrind.callgrind_dump_stats("myprofile")
```

Run `valgrind --tool=callgrind --instr-atstart=no python3 benchmark.py`.

See profile in `myprofile` file. Consider opening with KCachegrind or
QCachegrind.
