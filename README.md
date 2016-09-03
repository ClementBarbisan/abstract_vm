# abstract_vm

Virtual machine to compute numbers from file or standard input

Test files on ./test_files

Usage - ./avm [file]

Program from standard input must finish by ";;"

• Comments: Comments start with a ’;’ and finish with a newline. A comment can
be either at the start of a line, or after an instruction.

• push v: Pushes the value v at the top of the stack. The value v must have one of
the following form:

◦ int8(n) : Creates an 8-bit integer with value n.

◦ int16(n) : Creates a 16-bit integer with value n.

◦ int32(n) : Creates a 32-bit integer with value n.

◦ float(z) : Creates a float with value z.

◦ double(z) : Creates a double with value z.

• pop: Unstacks the value from the top of the stack.

• dump: Displays each value of the stack.

• assert v: Asserts that the value at the top of the stack is equal to the one passed
as parameter for this instruction. The value v has the same form that those passed as parameters
to the instruction push.

• add: Unstacks the first two values on the stack, adds them together and stacks the
result.

• sub: Unstacks the first two values on the stack, subtracts them, then stacks the
result.

• mul: Unstacks the first two values on the stack, multiplies them, then stacks the
result.

• div: Unstacks the first two values on the stack, divides them, then stacks the result.

• mod: Unstacks the first two values on the stack, calculates the modulus, then
stacks the result.

• print: Asserts that the value at the top of the stack is an 8-bit integer. (If not,
see the instruction assert), then interprets it as an ASCII value and displays the
corresponding character on the standard output.

• exit: Terminate the execution of the current program. Must be present in every program.

