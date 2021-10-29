#!/bin/bash
echo "> Generate test matrices and vectors if no test data found."
if [ ! -f data/mat_5x4.txt ]; then
    echo "generate 5x4 matrix..."
    python gen_matrix.py 5 4 > data/mat_5x4.txt
fi

if [ ! -f data/mat_4x1.txt ]; then
    echo "generate 4x1 vector..."
    python gen_matrix.py 4 1 > data/mat_4x1.txt
fi

if [ ! -f data/mat_1000x1000.txt ]; then
    echo "generate 1000x1000 matrix..."
    python gen_matrix.py 1000 1000 > data/mat_1000x1000.txt
fi

if [ ! -f data/mat_1000x1.txt ]; then
    echo "generate 1000x1 vector..."
    python gen_matrix.py 1000 1 > data/mat_1000x1.txt
fi

if [ ! -f data/mat_3000x2000.txt ]; then
    echo "generate 3000x2000 matrix..."
    python gen_matrix.py 3000 2000 > data/mat_3000x2000.txt
fi

if [ ! -f data/mat_2000x1.txt ]; then
    echo "generate 2000x1 vector..."
    python gen_matrix.py 2000 1 > data/mat_2000x1.txt
fi

echo
echo "> Compile source code."
make
echo

echo "> Calculate."
echo "5x1"
echo "* Serial:"
bin/serial.out data/mat_5x4.txt data/mat_4x1.txt
echo "* Parallel:"
bin/parallel.out data/mat_5x4.txt data/mat_4x1.txt
echo "* 2D partitioning:"
bin/parallel2D.out data/mat_5x4.txt data/mat_4x1.txt
echo
echo "1000x1"
echo "* Serial:"
bin/serial.out data/mat_1000x1000.txt data/mat_1000x1.txt
echo "* Parallel:"
bin/parallel.out data/mat_1000x1000.txt data/mat_1000x1.txt
echo "* 2D partitioning:"
bin/parallel2D.out data/mat_1000x1000.txt data/mat_1000x1.txt
echo
echo "3000x1"
echo "* Serial:"
bin/serial.out data/mat_3000x2000.txt data/mat_2000x1.txt
echo "* Parallel:"
bin/parallel.out data/mat_3000x2000.txt data/mat_2000x1.txt
echo "* 2D partitioning:"
bin/parallel2D.out data/mat_3000x2000.txt data/mat_2000x1.txt