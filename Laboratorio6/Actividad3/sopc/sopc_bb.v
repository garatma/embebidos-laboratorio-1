
module sopc (
	clock_clk,
	reset_reset_n,
	out_export,
	in_export);	

	input		clock_clk;
	input		reset_reset_n;
	output	[7:0]	out_export;
	input	[7:0]	in_export;
endmodule
