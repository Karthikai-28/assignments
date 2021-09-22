import contextlib
import os
import shutil
import tempfile


@contextlib.contextmanager
def tempdir(cleanup=True):
    tempdir = tempfile.mkdtemp()
    cwd = os.getcwd()
    os.chdir(tempdir)
    try:
        yield tempdir
    finally:
        os.chdir(cwd)
        if cleanup:
            shutil.rmtree(tempdir)
