module demultiplexor(reloj, sel, i, s1, s2, s3, s4, s5, s6, s7, s8);

	input reloj;
	input [2:0] sel;
	input [7:0] i;
	output [7:0] s1; 
	output [7:0] s2; 
	output [7:0] s3; 
	output [7:0] s4; 
	output [7:0] s5; 
	output [7:0] s6; 
	output [7:0] s7; 
	output [7:0] s8;

	reg [7:0] s1;
	reg [7:0] s2;
	reg [7:0] s3;
	reg [7:0] s4;
	reg [7:0] s5;
	reg [7:0] s6;
	reg [7:0] s7;
	reg [7:0] s8;

	always @*
		begin
			s1 = (sel == 3'b000) ? i : 3'b000;
			s2 = (sel == 3'b001) ? i : 3'b000;
			s3 = (sel == 3'b010) ? i : 3'b000;
			s4 = (sel == 3'b011) ? i : 3'b000;
			s5 = (sel == 3'b100) ? i : 3'b000;
			s6 = (sel == 3'b101) ? i : 3'b000;
			s7 = (sel == 3'b110) ? i : 3'b000;
			s8 = (sel == 3'b111) ? i : 3'b000;
		end

endmodule

