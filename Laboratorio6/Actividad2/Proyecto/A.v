module A(n1, n2, s1, s2);

	input [7:0] n1;
	input [7:0] n2;
	output [7:0] s1;
	output [7:0] s2;

	reg [7:0] s1;
	reg [7:0] s2;

	always @* 
		begin
			if (n1>n2)
				begin
					s1 = n2;
					s2 = n1;
				end
			else
				begin
					s1 = n1;
					s2 = n2;
				end
		end

endmodule
