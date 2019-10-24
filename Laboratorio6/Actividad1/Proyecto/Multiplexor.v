module multiplexor (
	data0x,
	data1x,
	sel,
	result);

	input [3:0] data0x;
	input [3:0] data1x;
	input sel;
	output[3:0] result;

	assign result = sel ? data1x : data0x;

endmodule
