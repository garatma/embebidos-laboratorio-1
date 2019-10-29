
module sopc (
	clk_clk,
	reset_reset_n,
	pio_out_export,
	pio_in_export);	

	input		clk_clk;
	input		reset_reset_n;
	output	[7:0]	pio_out_export;
	input	[7:0]	pio_in_export;
endmodule
