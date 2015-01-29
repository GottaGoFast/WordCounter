/* These #include statements tell the compiler to include the named header 
 * files. These are similar to imports in Java. When the name of the included
 * file is between angle brackets -- like so: <name.h> -- it is a *system*
 * header file. This means the compiler looks in predefined directories for 
 * this include file. Typically, these files will be in /usr/include/.
 * For example, stdio.h contains the declaration of the printf() function, and
 * stdlib.h contains malloc() and free(). When the name of the included file 
 * is within quotation * marks -- e.g. "name.h" -- it is a *user* header file. 
 * This means the compiler looks in the same directory as the source file you 
 * are compiling. 
 */
#include <stdio.h>
#include <stdlib.h>

/* This is called a function prototype. This lets the compiler know necessary
 * details of a function so it can use it, without yet having knowing the
 * implementation of the function. Specifically, it tells the compiler the 
 * function's return type, function name, and type for each of the 
 * fuction arguments (in this case there are none). You can supply the 
 * argument names in the function prototypes if you want, but it is not 
 * required. An example with arguments:
 * 
 * int average(int x, int y);
 */
void func();

/* main() is the entry point of the program.
 * argc is the argument count, and argv is the argument vector.
 * When you run your compiled program from the command line
 * you can supply arguments. For example:
 *
 * ./lab0 arg1 arg2
 *
 * In this case, argv has 3 items in it -- and thus argc is 3.
 * The program name is the first argument, so it is in argv[0].
 * arg1 is the second argument, so it is in argv[1].
 * arg2 is the third argument, so it is in argv[2].
 * You will be using argv in your program.
 */
int main(int argc, char **argv) {
	/* Here are some debug macros which you might find helpful when 
	 * debugging programs for this course or future projects.
	 */
	printf("line %d: file name is %s\n", __LINE__, __FILE__);
	printf("line %d: function name is %s\n", __LINE__, __func__);
	func();
}

void func() {
	printf("line %d: function name is %s\n", __LINE__, __func__);
}
