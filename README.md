# Prime_Finder_2
A command line multithreaed program to find all primes in a range
# Options
## Range End
The last decimal number found in the command line will be the end of the range.
If it is less than 4, the user will be asked to input an integer greater than 4.
## `-v` or `-d`
The verbose and debug mode are the same. 
Using either will output additional information about the internal state of the program.
## `-s`
Single mode only checks the number inputed, not the range from 2 to the number. 
## `-lq`
Prints out at the end the largest size that the queue was.
## `-p`
Prints out only the prime numbers.
## `-prog##`
Prints out the percent to completion. 
The optional `##` is the amount (expressed as a decimal number) at which it will print.
### `-prog10`
Print at every 10% (0, 10, 20, 30, ... 100)
## `-t`
Show the internal recorded time that it took to finish the main loop.
