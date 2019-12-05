#!/bin/bash

#Author: Justin Drouin
#Assignment 1
#Date: September 28th, 2019
#Program name: Assignment 1 Lexer

rm *.o
rm *.out

echo "Compiling Assignment 1 Lexer"

g++ -std=c++14 main.cpp -o Run.out

echo "Running Assignment 1 Lexer"
./Run.out

echo "Lexer Complete. Output file Generated. Terminating."
