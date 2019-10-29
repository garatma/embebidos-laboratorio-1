module contador(
	input reloj,
	output [2:0] cuenta
);

	reg [2:0] registro_cuenta;

	always @(posedge reloj)
		begin
			if (registro_cuenta < 3'b111)
				registro_cuenta <= registro_cuenta + 3'b001;
			else
				registro_cuenta = 3'b000;
		end
	assign cuenta = registro_cuenta;

endmodule
