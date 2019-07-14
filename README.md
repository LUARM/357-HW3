# 357-HW3

Programs: hencode and hdecode
This assignment is to build a file compression tool, hencode, that will use Huffman codes to compress
a given file, and a file decompression tool, hdecode, that will uncompress a file compressed with
hencode.

hencode must:
• take a command line argument that is the name of the file to be compressed; and
• take a second, optional, command line argument that is the name of the outfile. (If this
argument is missing, the output should go to stdout.)
• properly encode its input into a binary Huffman-coded file according to the algorithm below.
hdecode must:
• Take an optional command line argument that is the name of the file to be uncompressed.
If this argument is missing, or if the input file name is “-”, hdecode will take its input from
standard input.
• Take a second, optional, command line argument that is the name of the output file. (If this
argument is missing, the output should go to stdout.)
• Properly decode its input and restore the original data.
