module B(n1, n2, n3, n4, s1, s2, s3, s4);

	// --------------- parámetros ------------------
	
	input [1:0] n1;
	input [1:0] n2;
	input [1:0] n3;
	input [1:0] n4;
	output [1:0] s1;
	output [1:0] s2;
	output [1:0] s3;
	output [1:0] s4;

	// --------------------- wires -----------------
	
	wire [1:0] a1m;
	wire [1:0] a1M;

	wire [1:0] a2m;
	wire [1:0] a2M;

	wire [1:0] a3m;
	wire [1:0] a3M;

	wire [1:0] a4m;
	wire [1:0] a4M;

	// -------------------- código ------------------

	A a1(
		.n1(n1),
		.n2(n2),
		.s1(a1m),
		.s2(a1M)
		);
	A a2(
		.n1(n3),
		.n2(n4),
		.s1(a2m),
		.s2(a2M)
		);
	A a3(
		.n1(a1M),
		.n2(a2m),
		.s1(a3m),
		.s2(a3M)
		);
	A a4(
		.n1(a1m),
		.n2(a2M),
		.s1(a4m),
		.s2(a4M)
		);
	A a5(
		.n1(a4m),
		.n2(a3m),
		.s1(s1),
		.s2(s2)
		);
	A a6(
		.n1(a3M),
		.n2(a4M),
		.s1(s3),
		.s2(s4)
		);

endmodule
