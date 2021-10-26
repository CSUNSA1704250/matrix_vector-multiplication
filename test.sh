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

echo
echo "> Compile source code."
make
echo

echo "> Calculate."
echo "* * * * * * * Serial: 5x1"
bin/serial.out data/mat_5x4.txt data/mat_4x1.txt
echo "* * * * * * * Processing1D: 5x1"
bin/parallel.out data/mat_5x4.txt data/mat_4x1.txt
echo "* * * * * * * Processing2D: 5x1"
bin/parallel2D.out data/mat_5x4.txt data/mat_4x1.txt
