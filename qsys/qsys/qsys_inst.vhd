	component qsys is
		port (
			btn_export    : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- export
			clk_clk       : in    std_logic                     := 'X';             -- clk
			d7seg_export  : out   std_logic_vector(15 downto 0);                    -- export
			eeprom_sda_in : in    std_logic                     := 'X';             -- sda_in
			eeprom_scl_in : in    std_logic                     := 'X';             -- scl_in
			eeprom_sda_oe : out   std_logic;                                        -- sda_oe
			eeprom_scl_oe : out   std_logic;                                        -- scl_oe
			enc_spi_MISO  : in    std_logic                     := 'X';             -- MISO
			enc_spi_MOSI  : out   std_logic;                                        -- MOSI
			enc_spi_SCLK  : out   std_logic;                                        -- SCLK
			enc_spi_SS_n  : out   std_logic;                                        -- SS_n
			led_export    : out   std_logic_vector(3 downto 0);                     -- export
			ram_addr      : out   std_logic_vector(11 downto 0);                    -- addr
			ram_ba        : out   std_logic_vector(1 downto 0);                     -- ba
			ram_cas_n     : out   std_logic;                                        -- cas_n
			ram_cke       : out   std_logic;                                        -- cke
			ram_cs_n      : out   std_logic;                                        -- cs_n
			ram_dq        : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			ram_dqm       : out   std_logic_vector(1 downto 0);                     -- dqm
			ram_ras_n     : out   std_logic;                                        -- ras_n
			ram_we_n      : out   std_logic;                                        -- we_n
			reset_reset_n : in    std_logic                     := 'X';             -- reset_n
			temp_sda_in   : in    std_logic                     := 'X';             -- sda_in
			temp_scl_in   : in    std_logic                     := 'X';             -- scl_in
			temp_sda_oe   : out   std_logic;                                        -- sda_oe
			temp_scl_oe   : out   std_logic                                         -- scl_oe
		);
	end component qsys;

	u0 : component qsys
		port map (
			btn_export    => CONNECTED_TO_btn_export,    --     btn.export
			clk_clk       => CONNECTED_TO_clk_clk,       --     clk.clk
			d7seg_export  => CONNECTED_TO_d7seg_export,  --   d7seg.export
			eeprom_sda_in => CONNECTED_TO_eeprom_sda_in, --  eeprom.sda_in
			eeprom_scl_in => CONNECTED_TO_eeprom_scl_in, --        .scl_in
			eeprom_sda_oe => CONNECTED_TO_eeprom_sda_oe, --        .sda_oe
			eeprom_scl_oe => CONNECTED_TO_eeprom_scl_oe, --        .scl_oe
			enc_spi_MISO  => CONNECTED_TO_enc_spi_MISO,  -- enc_spi.MISO
			enc_spi_MOSI  => CONNECTED_TO_enc_spi_MOSI,  --        .MOSI
			enc_spi_SCLK  => CONNECTED_TO_enc_spi_SCLK,  --        .SCLK
			enc_spi_SS_n  => CONNECTED_TO_enc_spi_SS_n,  --        .SS_n
			led_export    => CONNECTED_TO_led_export,    --     led.export
			ram_addr      => CONNECTED_TO_ram_addr,      --     ram.addr
			ram_ba        => CONNECTED_TO_ram_ba,        --        .ba
			ram_cas_n     => CONNECTED_TO_ram_cas_n,     --        .cas_n
			ram_cke       => CONNECTED_TO_ram_cke,       --        .cke
			ram_cs_n      => CONNECTED_TO_ram_cs_n,      --        .cs_n
			ram_dq        => CONNECTED_TO_ram_dq,        --        .dq
			ram_dqm       => CONNECTED_TO_ram_dqm,       --        .dqm
			ram_ras_n     => CONNECTED_TO_ram_ras_n,     --        .ras_n
			ram_we_n      => CONNECTED_TO_ram_we_n,      --        .we_n
			reset_reset_n => CONNECTED_TO_reset_reset_n, --   reset.reset_n
			temp_sda_in   => CONNECTED_TO_temp_sda_in,   --    temp.sda_in
			temp_scl_in   => CONNECTED_TO_temp_scl_in,   --        .scl_in
			temp_sda_oe   => CONNECTED_TO_temp_sda_oe,   --        .sda_oe
			temp_scl_oe   => CONNECTED_TO_temp_scl_oe    --        .scl_oe
		);

