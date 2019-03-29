import sys
import pytest
import time
import os
from utils import build_tree

@pytest.mark.skipif(sys.platform == 'darwin', reason="does not run on osx yet")
def test_build_small():
	try:
		time = build_tree(4, 100)
		success = True
	except Exception as e:
		print("Failed basic: "+e.message)
		success = False

	assert(success == True)

@pytest.mark.skipif(sys.platform == 'darwin', reason="does not run on osx yet")
def test_build_t_values():	
	t_values = [2**i for i in range(2, 12)]
	try:
		for t in t_values:
			time = build_tree(t, 1000)
		success = True
	except:
		print("Failed t: "+e.message)
		success = False
	
	assert(success == True)


@pytest.mark.skipif(sys.platform == 'darwin', reason="does not run on osx yet")
def test_build_records():
	record_sizes = [10*i for i in range(1, 6)]
	
	try:
		for s in record_sizes:
			time = build_tree(1024, s)
		success = True
	except:
		print("Failed records: "+e.message)
		success = False
	
	assert(success == True)
