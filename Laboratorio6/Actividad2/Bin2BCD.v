module bin2bcd(
			b7, b6, b5, b4, b3, b2, b1, b0,
	p9, p8, p7, p6, p5, p4, p3, p2, p1, p0
);

	input b7;
	input b6;
	input b5;
	input b4;
	input b3;
	input b2;
	input b1;
	input b0;
	output p9;
	output p8;
	output p7;
	output p6;
	output p5;
	output p4;
	output p3;
	output p2;
	output p1;
	output p0;

	wire c1_3, c1_2, c1_1, c1_0,
		 c2_3, c2_2, c2_1, c2_0,
		 c3_3, c3_2, c3_1, c3_0,
		 c4_3, c4_2, c4_1, c4_0,
		 c6_2, c6_1, c6_0;

	shiftadd c1(.a3(0), .a2(b7), .a1(b6), .a0(b5),
				.s3(c1_3), .s2(c1_2), .s1(c1_1), .s0(c1_0)
	);
	shiftadd c2(.a3(c1_2), .a2(c1_1), .a1(c1_0), .a0(b4),
				.s3(c2_3), .s2(c2_2), .s1(c2_1), .s0(c2_0)
	);
	shiftadd c3(.a3(c2_2), .a2(c2_1), .a1(c2_0), .a0(b3),
				.s3(c3_3), .s2(c3_2), .s1(c3_1), .s0(c3_0)
	);
	shiftadd c4(.a3(c3_2), .a2(c3_1), .a1(c3_0), .a0(b2),
				.s3(c4_3), .s2(c4_2), .s1(c4_1), .s0(c4_0)
	);
	shiftadd c5(.a3(c4_2), .a2(c4_1), .a1(c4_0), .a0(b1),
				.s3(p4), .s2(p3), .s1(p2), .s0(p1)
	);
	shiftadd c6(.a3(0), .a2(c1_3), .a1(c2_3), .a0(c3_3),
				.s3(p9), .s2(c6_2), .s1(c6_1), .s0(c6_0)
	);
	shiftadd c7(.a3(c6_2), .a2(c6_1), .a1(c6_0), .a0(c4_3),
				.s3(p8), .s2(p7), .s1(p6), .s0(p5)
	);

	assign p0 = b0;

endmodule	

