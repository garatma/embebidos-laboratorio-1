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

	always @(posedge reloj)
		begin
			case (sel)
				3'b000: 
					begin
						s1 = i;
						s2 = 0;
						s3 = 0;
						s4 = 0;
						s5 = 0;
						s6 = 0;
						s7 = 0;
						s8 = 0;
					end
				3'b001:
					begin
						s1 = 0;
						s2 = i;
						s3 = 0;
						s4 = 0;
						s5 = 0;
						s6 = 0;
						s7 = 0;
						s8 = 0;
					end
				3'b010:
					begin
						s1 = 0;
						s2 = 0;
						s3 = i;
						s4 = 0;
						s5 = 0;
						s6 = 0;
						s7 = 0;
						s8 = 0;
					end
				3'b011:
					begin
						s1 = 0;
						s2 = 0;
						s3 = 0;
						s4 = i;
						s5 = 0;
						s6 = 0;
						s7 = 0;
						s8 = 0;
					end
				3'b100:
					begin
						s1 = 0;
						s2 = 0;
						s3 = 0;
						s4 = 0;
						s5 = i;
						s6 = 0;
						s7 = 0;
						s8 = 0;
					end
				3'b101:
					begin
						s1 = 0;
						s2 = 0;
						s3 = 0;
						s4 = 0;
						s5 = 0;
						s6 = i;
						s7 = 0;
						s8 = 0;
					end
				3'b110:
					begin
						s1 = 0;
						s2 = 0;
						s3 = 0;
						s4 = 0;
						s5 = 0;
						s6 = 0;
						s7 = i;
						s8 = 0;
					end
				3'b111:
					begin
						s1 = 0;
						s2 = 0;
						s3 = 0;
						s4 = 0;
						s5 = 0;
						s6 = 0;
						s7 = 0;
						s8 = i;
					end
			endcase
		end

endmodule

