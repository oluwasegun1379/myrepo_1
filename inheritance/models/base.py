#!/usr/bin/python3
""" craeting a class Base to return id value or an increament if none is passed """
class Base:
    """ private instance attribute to take note of increament if the id passed is empty """
    __nb_instance = 0
    def __init__(self, id=0):
        if not id:
            type(self).__nb_instance += 1
            self.id = type(self).__nb_instance
        else:
            self.id = id
