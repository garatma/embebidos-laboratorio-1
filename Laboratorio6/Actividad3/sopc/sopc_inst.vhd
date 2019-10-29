	component sopc is
		port (
			clk_clk        : in  std_logic                    := 'X';             -- clk
			reset_reset_n  : in  std_logic                    := 'X';             -- reset_n
			pio_out_export : out std_logic_vector(7 downto 0);                    -- export
			pio_in_export  : in  std_logic_vector(7 downto 0) := (others => 'X')  -- export
		);
	end component sopc;

	u0 : component sopc
		port map (
			clk_clk        => CONNECTED_TO_clk_clk,        --     clk.clk
			reset_reset_n  => CONNECTED_TO_reset_reset_n,  --   reset.reset_n
			pio_out_export => CONNECTED_TO_pio_out_export, -- pio_out.export
			pio_in_export  => CONNECTED_TO_pio_in_export   --  pio_in.export
		);

