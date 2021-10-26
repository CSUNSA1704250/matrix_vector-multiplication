#
# This small helper script generates a test matrix of the given dimension and
# outputs to stdout so that you can pipe it into files.
# The elements (in range [1, 100]) are separated by spaces.
#
# Synopsis:
#   ./gen_matrix.py 4 4
#

import sys
import random

rows, columns = int(sys.argv[1]), int(sys.argv[2])

for row in range(rows):
    print(" ".join([str(random.randint(1, 10)) for col in range(columns)]))
