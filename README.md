Keccak-Internal-Permutation-in-C
================================

<b>Implementation of Keccak internal permutation in C</b>

Keccak the cryptographic sponge function family called Keccak, which has been selected by NIST to become the new SHA-3 standard. The sponge function is a generalization of the concept of cryptographic hash function with infinite output and 
can perform quasi all symmetric cryptographic functions, from hashing to pseudo-random number generation to authenticated encryption.

The implementation of only internal permutation in C language is doen here. 

The <u>"Keccak Hash Function"</u> and  <u>"Encryption using the Keccak sponge construction"</u> will be available in other repositories soon.

More information about the psuedo code can be found in,
http://keccak.noekeon.org/

Description about the implementation can be found in,
http://keccak.noekeon.org/Keccak-implementation-3.2.pdf

test vectors provided by the designers for debugging. One of them is used in the file KeccakF1600_driver.c . 
https://github.com/gvanas/KeccakCodePackage/blob/master/TestVectors/KeccakF-1600-IntermediateValues.txt



</br>
================================

<b>Usage</b>
This program is written in a way that tests whether the implementation is correct. However the subject of interest in this repository will just be the .c File and ofcourse the header files which has all the definations.

After clonig the repository, Follow the commands below in same order.
cd <directory created by this>
make 
./KeccakF1600_driver

================================

<b>NOTE:</b> 
<ul><li>Tweak the C code and when you run above commands, the output should be PASS.</li>
<li> Depending on your system's architecture, you might get FAIL. Explaination about the memory usage by this program and architectural dependency is beyond the scope of this work.
<li> Segmentation Faults can be debugged using Valgrind http://valgrind.org/ </li> </ul>
