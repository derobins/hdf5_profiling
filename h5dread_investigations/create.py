import argparse
import h5py
import numpy as np

parser = argparse.ArgumentParser(description='Create a test file for H5Dread() profiling.')
parser.add_argument('-c', action='store_true', help='Create a chunked dataset.')
parser.add_argument('-F', action='store_true', help='Use the latest file format')
parser.add_argument('file', help='The name of the file.')
args = parser.parse_args()

file_params = {'name':args.file}
if (args.F):
    file_params.update( {'libver' : ('latest', 'latest')} )
f = h5py.File(**file_params)

arr = np.arange(100)

dset_params = {'name':"test", 'shape':(100,), 'dtype':'i8', 'data':arr}
if (args.c):
    dset_params.update( {'chunks' : (10,)} )
dset = f.create_dataset(**dset_params)

f.close()
