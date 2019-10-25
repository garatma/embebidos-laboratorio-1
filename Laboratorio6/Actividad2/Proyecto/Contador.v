module contador(
	input reloj, reset,
	output [3:0] cuenta
);

	reg [3:0] cuenta_aux;

	always @(posedge reloj or posedge reset)
	begin
		if (reset)
			cuenta_aux <= 4'd0;
		else
			cuenta_aux <= cuenta_aux + 4'd1;
	end
	assign cuenta = cuenta_aux;

endmodule
