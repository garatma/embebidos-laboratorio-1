module B(n1, n2, n3, n4,
	     n5, n6, n7, n8,
		 s1, s2, s3, s4,
	 	 s5, s6, s7, s8);

	// --------------- parámetros ------------------
	
	input [7:0] n1;
	input [7:0] n2;
	input [7:0] n3;
	input [7:0] n4;
	input [7:0] n5;
	input [7:0] n6;
	input [7:0] n7;
	input [7:0] n8;
	output [7:0] s1;
	output [7:0] s2;
	output [7:0] s3;
	output [7:0] s4;
	output [7:0] s5;
	output [7:0] s6;
	output [7:0] s7;
	output [7:0] s8;

	// --------------------- wires -----------------
	
	wire [7:0] a1_1;
	wire [7:0] a1_2;

	wire [7:0] a2_1;
	wire [7:0] a2_2;

	wire [7:0] a3_1;
	wire [7:0] a3_2;

	wire [7:0] a4_1;
	wire [7:0] a4_2;

	wire [7:0] b1_1;
	wire [7:0] b1_2;
	wire [7:0] b1_3;
	wire [7:0] b1_4;

	wire [7:0] b2_1;
	wire [7:0] b2_2;
	wire [7:0] b2_3;
	wire [7:0] b2_4;

	// -------------------- código ------------------

	B b1(
		 .n1(n1),
		 .n2(n2),
		 .n3(n3),
		 .n4(n4),
		 .s1(b1_1),
		 .s2(b1_2),
		 .s3(b1_3),
		 .s4(b1_4)
		);
	B b2(
		 .n1(n5),
		 .n2(n6),
		 .n3(n7),
		 .n4(n8),
		 .s1(b2_1),
		 .s2(b2_2),
		 .s3(b2_3),
		 .s4(b2_4)
		);

	A a1(
		.n1(b1_1),
		.n2(b2_4),
		.s1(a1_1),
		.s2(a1_2)
		);
	A a2(
		.n1(b1_2),
		.n2(b2_3),
		.s1(a2_1),
		.s2(a2_2)
		);
	A a3(
		.n1(b1_3),
		.n2(b2_2),
		.s1(a3_1),
		.s2(a3_2)
		);
	A a4(
		.n1(b1_4),
		.n2(b2_1),
		.s1(a4_1),
		.s2(a4_2)
		);
	D d1(
		 .n1(a1_1),
		 .n2(a2_1),
		 .n3(a3_1),
		 .n4(a4_1),
		 .s1(s1),
		 .s2(s2),
		 .s3(s3),
		 .s4(s4)
		);
	D d1(
		 .n1(a4_2),
		 .n2(a3_2),
		 .n3(a2_2),
		 .n4(a1_2),
		 .s1(s5),
		 .s2(s6),
		 .s3(s7),
		 .s4(s8)
	 	);

endmodule
