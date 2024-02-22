#!/usr/bin/python3
class Parent:
    def __init__(self, money="", properties=""):
        self.money = money
        self.properties = properties

# Creating a child class that inherits from Parent
class Child(Parent):
    def __init__(self, money="", properties="", allowance=""):
        # Call the Parent's __init__ method to initialize inherited attributes
        super().__init__(money, properties)
        self.allowance = allowance

# Taking input for the Parent class
money_inherited = input("Enter the amount of money inherited: ")
properties_inherited = input("Enter the list of properties inherited: ")

# Instantiating the Parent class
parent_instance = Parent(money_inherited, properties_inherited)
print("Parent Money:", parent_instance.money)
print("Parent Properties:", parent_instance.properties)

# Taking input for the Child class
allowance = input("Enter the allowance: ")

# Instantiating the Child class
child_instance = Child(money_inherited, properties_inherited, allowance)
print("Child Money:", child_instance.money)
print("Child Properties:", child_instance.properties)
print("Child Allowance:", child_instance.allowance)
