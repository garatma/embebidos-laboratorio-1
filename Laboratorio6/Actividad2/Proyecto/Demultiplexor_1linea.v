module demultiplexor_1linea(sel, i, s1, s2, s3, s4, s5, s6, s7, s8);

	input [2:0] sel;
	input i;
	output s1; 
	output s2; 
	output s3; 
	output s4; 
	output s5; 
	output s6; 
	output s7; 
	output s8;

	reg s1;
	reg s2;
	reg s3;
	reg s4;
	reg s5;
	reg s6;
	reg s7;
	reg s8;

	always @*
	begin
		s1 = (sel == 3'b000) ? i : 1'b0;
		s2 = (sel == 3'b001) ? i : 1'b0;
		s3 = (sel == 3'b010) ? i : 1'b0;
		s4 = (sel == 3'b011) ? i : 1'b0;
		s5 = (sel == 3'b100) ? i : 1'b0;
		s6 = (sel == 3'b101) ? i : 1'b0;
		s7 = (sel == 3'b110) ? i : 1'b0;
		s8 = (sel == 3'b111) ? i : 1'b0;
	end

endmodule

