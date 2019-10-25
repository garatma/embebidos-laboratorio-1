module registro(
	input reloj,
	input d,
	output q
);

	always @(posedge reloj)
	