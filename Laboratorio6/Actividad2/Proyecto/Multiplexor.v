module multiplexor (
	input [2:0] sel,
	input [7:0] n1,
	input [7:0] n2,
	input [7:0] n3,
	input [7:0] n4,
	input [7:0] n5,
	input [7:0] n6,
	input [7:0] n7,
	input [7:0] n8,
	output [7:0] salida);

	// reg [7:0] salida;

	always @*
		begin
			case (sel)
				3'b000: salida = n1;
				3'b001: salida = n2;
				3'b010: salida = n3;
				3'b011: salida = n4;
				3'b100: salida = n5;
				3'b101: salida = n6;
				3'b110: salida = n7;
				3'b111: salida = n8;
			endcase
		end

endmodule
