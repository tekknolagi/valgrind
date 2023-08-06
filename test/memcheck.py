import valgrind
import glob
import os


def currently_reachable_blocks() -> int:
    """
    Return the number of reachable allocations (not: bytes!)
    """
    valgrind.memcheck_do_leak_check()
    _leaked, _dubious, reachable, _suppressed = valgrind.memcheck_count_leak_blocks()
    return reachable


def verify_reachable_blocks(n: int, fuzzy: int = 1000) -> None:
    """
    Return the number of reachable blocks

    Includes fuzz for O(1) misc malloc/free by Python that we are not interested in.
    """
    reachable = currently_reachable_blocks()
    assert n - fuzzy <= reachable <= n + fuzzy, \
        f'assertion failed: {n - fuzzy} <= {reachable} <= {n + fuzzy}'


if __name__ == '__main__':
    n = 100000
    baseline = currently_reachable_blocks()
    r0 = list(range(n))
    verify_reachable_blocks(baseline + n)
    r1 = list(range(100000))
    verify_reachable_blocks(baseline + 2 * n)

