module contador(
	input reloj,
	output [3:0] cuenta
);

	reg [3:0] cuenta_aux;

	always @(posedge reloj)
	begin
		cuenta_aux <= cuenta_aux + 4'd1;
	end
	assign cuenta = cuenta_aux;

endmodule
