module D(n1, n2, n3, n4, s1, s2, s3, s4);

	// --------------- parámetros ------------------
	
	input [7:0] n1;
	input [7:0] n2;
	input [7:0] n3;
	input [7:0] n4;
	output [7:0] s1;
	output [7:0] s2;
	output [7:0] s3;
	output [7:0] s4;

	// --------------------- wires -----------------
	
	wire [7:0] a1_1;
	wire [7:0] a1_2;

	wire [7:0] a2_1;
	wire [7:0] a2_2;

	// -------------------- código ------------------

	A a1(
		.n1(n1),
		.n2(n3),
		.s1(a1_1),
		.s2(a1_2)
		);
	A a2(
		.n1(n2),
		.n2(n4),
		.s1(a2_1),
		.s2(a2_2)
		);
	A a3(
		.n1(a1_1),
		.n2(a2_1),
		.s1(s1),
		.s2(s2)
		);
	A a4(
		.n1(a1_2),
		.n2(a2_2),
		.s1(s3),
		.s2(s4)
		);

endmodule
