
module sopc4 (
	clk_clk,
	in_aux_export,
	out_aux_export,
	reset_reset_n,
	in0_export,
	in1_export,
	in2_export,
	in3_export,
	in4_export,
	in5_export,
	in6_export,
	in7_export,
	out7_export,
	out6_export,
	out5_export,
	out4_export,
	out3_export,
	out2_export,
	out1_export,
	out0_export);	

	input		clk_clk;
	input	[7:0]	in_aux_export;
	output	[7:0]	out_aux_export;
	input		reset_reset_n;
	input	[7:0]	in0_export;
	input	[7:0]	in1_export;
	input	[7:0]	in2_export;
	input	[7:0]	in3_export;
	input	[7:0]	in4_export;
	input	[7:0]	in5_export;
	input	[7:0]	in6_export;
	input	[7:0]	in7_export;
	output	[7:0]	out7_export;
	output	[7:0]	out6_export;
	output	[7:0]	out5_export;
	output	[7:0]	out4_export;
	output	[7:0]	out3_export;
	output	[7:0]	out2_export;
	output	[7:0]	out1_export;
	output	[7:0]	out0_export;
endmodule
