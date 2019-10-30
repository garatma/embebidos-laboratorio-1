	component sopc4 is
		port (
			clk_clk        : in  std_logic                    := 'X';             -- clk
			in_aux_export  : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			out_aux_export : out std_logic_vector(7 downto 0);                    -- export
			reset_reset_n  : in  std_logic                    := 'X';             -- reset_n
			in0_export     : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			in1_export     : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			in2_export     : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			in3_export     : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			in4_export     : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			in5_export     : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			in6_export     : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			in7_export     : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			out7_export    : out std_logic_vector(7 downto 0);                    -- export
			out6_export    : out std_logic_vector(7 downto 0);                    -- export
			out5_export    : out std_logic_vector(7 downto 0);                    -- export
			out4_export    : out std_logic_vector(7 downto 0);                    -- export
			out3_export    : out std_logic_vector(7 downto 0);                    -- export
			out2_export    : out std_logic_vector(7 downto 0);                    -- export
			out1_export    : out std_logic_vector(7 downto 0);                    -- export
			out0_export    : out std_logic_vector(7 downto 0)                     -- export
		);
	end component sopc4;

	u0 : component sopc4
		port map (
			clk_clk        => CONNECTED_TO_clk_clk,        --     clk.clk
			in_aux_export  => CONNECTED_TO_in_aux_export,  --  in_aux.export
			out_aux_export => CONNECTED_TO_out_aux_export, -- out_aux.export
			reset_reset_n  => CONNECTED_TO_reset_reset_n,  --   reset.reset_n
			in0_export     => CONNECTED_TO_in0_export,     --     in0.export
			in1_export     => CONNECTED_TO_in1_export,     --     in1.export
			in2_export     => CONNECTED_TO_in2_export,     --     in2.export
			in3_export     => CONNECTED_TO_in3_export,     --     in3.export
			in4_export     => CONNECTED_TO_in4_export,     --     in4.export
			in5_export     => CONNECTED_TO_in5_export,     --     in5.export
			in6_export     => CONNECTED_TO_in6_export,     --     in6.export
			in7_export     => CONNECTED_TO_in7_export,     --     in7.export
			out7_export    => CONNECTED_TO_out7_export,    --    out7.export
			out6_export    => CONNECTED_TO_out6_export,    --    out6.export
			out5_export    => CONNECTED_TO_out5_export,    --    out5.export
			out4_export    => CONNECTED_TO_out4_export,    --    out4.export
			out3_export    => CONNECTED_TO_out3_export,    --    out3.export
			out2_export    => CONNECTED_TO_out2_export,    --    out2.export
			out1_export    => CONNECTED_TO_out1_export,    --    out1.export
			out0_export    => CONNECTED_TO_out0_export     --    out0.export
		);

