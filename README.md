# Huffman-Codes
A simple header file that allows you to encode and decode messages using an algorithm that creates a set of Huffman codes out of symbol: probabiliity pairs

#### note that the code is located in the "master" branch

## Usage
All that needs to be done is to instantiate an object of type Decoder, given an ifstream initiated with the file of your choice. The file should have the following format:

```c++
a: 0.5
b: 0.3
c: 0.2
...
<symbol>: <probability>
```

Once the decoder has read in this file, one can print the set of Huffman codes that correlate to each symbol

```c++
ifstream is("english.in");
Decoder decoder(is); // instantiate decoder

decoder.endcode(); // finds codes for each symbol given probability

decoder.print() // print symbol, probability, and Huffman code
```

output:
```c++
Printing Data
t: 0.091 CODE: 000
y: 0.0211 CODE: 00100
v: 0.0111 CODE: 001010
k: 0.0069 CODE: 0010111
z: 0.0007 CODE: 001011000
j: 0.001 CODE: 001011001
q: 0.0011 CODE: 001011010
x: 0.0017 CODE: 001011011
f: 0.023 CODE: 00110
m: 0.0261 CODE: 00111
e: 0.1202 CODE: 011
h: 0.0592 CODE: 0101
c: 0.0271 CODE: 01000
u: 0.0288 CODE: 01001
r: 0.0602 CODE: 1000
s: 0.0628 CODE: 1001
n: 0.0695 CODE: 1010
l: 0.0398 CODE: 10111
b: 0.0149 CODE: 101100
p: 0.0182 CODE: 101101
i: 0.0731 CODE: 1100
o: 0.0768 CODE: 1101
a: 0.0812 CODE: 1110
d: 0.0432 CODE: 11111
g: 0.0203 CODE: 111100
w: 0.0209 CODE: 111101
```

Finally, one can decode a message by inserting an insertion stream with a file containing a code

```c++
ifstream is("code.in")
ofstream os("output.out")
decoder.decode(is, os)
```
if the input is:

```c++
010101110111101111101 111101110110001011111111

```
the output is:
```c++
hello world

```
ONLY for this particular instance, given the input included in the repo 'english.in'.

### Sources

probabilities for "english.in" obtained from http://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html

a great reference for how Huffman codes work: https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/



