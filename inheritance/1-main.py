#!/usr/bin/python3
from models.base import Base
if __name__ == "__main__":
    r1 = Base()
    print(r1.id)

    r2 = Base(12)
    print(r2.id)

    r2 = Base(25)
    print(r2.id)

    r2 = Base()
    print(r2.id)
    
    r2 = Base()
    print(r2.id)
