import sys
import pytest
import time
import os
from utils import test_build

@pytest.mark.skipif(sys.platform == 'darwin', reason="does not run on osx yet")
def test_basic():
	
	assert('Hello container: %d'%i == t.result_queue.get().decode('utf-8'))
