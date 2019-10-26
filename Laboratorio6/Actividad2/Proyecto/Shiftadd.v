module shiftadd(a3, a2, a1, a0, s3, s2, s1, s0);

	input a3;
	input a2;
	input a1;
	input a0;
	output s3;
	output s2;
	output s1;
	output s0;

	assign s3 = a3 | a2&(a1|a0);
	assign s2 = a3&a0 | a2&(~a1)&(~a0);
	assign s1 = a1&(a0|~(a2)) | a3&(~a0);
	assign s0 = a3&(~a0) | (~a3)&(~a2)&a0 | a2&a1&(~a0);

endmodule	
