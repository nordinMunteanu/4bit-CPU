# 4Bit ALU
INPUTS: A, B, OpCode, Y
OUTPUTS: C, FLAGS

A, B - input variables - they represent the variables used for the ALU Operations. Every operation follows the formula C = A<>B, where <> is the operation to be effectuated. A is always the minuent, or the base of all operations.
Y- flag bit, allows you to chose between addition, substraction, incrememntation, decrementation
OpCode - Operation code, choses between the ALU's operations.

C - the result of the operation
FLAGS - the flags of the ALU, represented as a 4 bit number, where each bit represents one of the following: Carry/Borrow of the subtraction/adition, A<B, A == B, A == 0

Detailed ALU operation codes and FLAG representation in the ALU_opcodes.pdf file in the Documentation folder

The ALU does all operations at once, using multiplexers at the output to output the desired operation.
