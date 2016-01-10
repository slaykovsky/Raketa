#!/usr/bin/env python3

import random
import sys

with open("random", "w") as f:
    for i in range(int(sys.argv[1])):
        line = str(random.randint(2, 10000)) + "\n"
        f.write(line)
