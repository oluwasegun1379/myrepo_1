#!/usr/bin/python3
import sys
with open('my second github token.txt', 'r', encoding="UTF8") as f:
    read_data = f.read()
    print(read_data)
    f.close()
