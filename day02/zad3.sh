#!/bin/sh
echo "Biggest num:" && sort -n numbers.txt | tail -n 1
echo "Smallest num:" && sort -n numbers.txt | head -n 1
