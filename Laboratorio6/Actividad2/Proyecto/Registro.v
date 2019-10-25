module registro(reloj, D, Q);

	input [7:0] reloj;
	input [7:0] D;
	output [7:0] Q;
	reg [7:0] Q;

	always @(posedge reloj)
		begin
			Q = D;
		end

endmodule
