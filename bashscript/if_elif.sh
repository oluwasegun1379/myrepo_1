#!/bin/bash
echo -n "Enter your name: "
read name
echo "Happy birthday $name, I wish you long life and prosperity"
echo -n "Enter your age: "
read age
#using if, elif and else in bash script
if [ "$age" -lt 18 ]; then
	echo "Happy birthday $name. You are a minor."
elif [ "$age" -ge 18 ] && [ "$age" -le 65 ]; then
	echo "Happy birthday $name. You are an adult."
else
	echo "Happy birthday $Segun. You are a senior"
fi
