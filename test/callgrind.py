import valgrind
import glob
import os


def fibonacci(n: int) -> int:
    """
    Dummy expensive function to test
    """
    if n <= 1:
        return n
    return fibonacci(n - 1) + fibonacci(n - 2)


def clean_outputfiles() -> None:
    for f in glob.glob('test/callgrind.out.*'):
        os.remove(f)


def verify_dumped_stats_file() -> None:
    """
    Verify the callgrind dumped stats
    """
    pid = os.getpid()
    filename = f'test/callgrind.out.{pid}.1'
    assert os.path.exists(filename), filename


if __name__ == '__main__':
    clean_outputfiles()
    valgrind.memcheck_do_leak_check()
    fibonacci(10)
    valgrind.callgrind_stop_instrumentation()
    valgrind.callgrind_dump_stats('created by callgrind.py')
    verify_dumped_stats_file()
