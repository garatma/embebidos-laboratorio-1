	component sopc is
		port (
			clock_clk     : in  std_logic                    := 'X';             -- clk
			reset_reset_n : in  std_logic                    := 'X';             -- reset_n
			out_export    : out std_logic_vector(7 downto 0);                    -- export
			in_export     : in  std_logic_vector(7 downto 0) := (others => 'X')  -- export
		);
	end component sopc;

	u0 : component sopc
		port map (
			clock_clk     => CONNECTED_TO_clock_clk,     -- clock.clk
			reset_reset_n => CONNECTED_TO_reset_reset_n, -- reset.reset_n
			out_export    => CONNECTED_TO_out_export,    --   out.export
			in_export     => CONNECTED_TO_in_export      --    in.export
		);

