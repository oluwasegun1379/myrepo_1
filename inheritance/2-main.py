#!/usr/bin/python3
from models.rectangle import Rectangle
if __name__ == "__main__":
    r1 = Rectangle(10, 2)
    print(r1.id)

    r1 = Rectangle(3, 2, 9)
    print(r1.id)

    r1 = Rectangle(10, 2, 3, 7)
    print(r1.id)

    r1 = Rectangle(10, 2, 10, 45, 15)
    print(r1.id)
