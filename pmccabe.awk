#!/usr/bin/awk -f

BEGIN {
	max_function_points = 10;
	max_function_statements = 50;
	max_function_loc = 50;
}

{
	if ($1 > max_function_points) {
		print $6,"warning:",$7,"is too complex (" $1,"function points)";
	}
	if ($3 > max_function_statements) {
		print $6,"warning:",$7,"has too many statements (" $3 ")";
	}
	if ($5 > max_function_loc) {
		print $6,"warning:",$7,"is too long (" $5,"lines of code)";
	}
}
