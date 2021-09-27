library ieee;

use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity device is
	port(
		clock : in std_logic := '0';
		reset : in std_logic := '0';
		
		ram_data 	: inout 	std_logic_vector(15 downto 0) := (others => 'Z');
		ram_addr 	: out   	std_logic_vector(11 downto 0) := (others => '0');
		ram_bs		: out		std_logic_vector(1 downto 0) := "00";
		ram_dm		: out		std_logic_vector(1 downto 0) := "00";
		ram_cke		: out 	std_logic := '0';
		ram_clk		: out 	std_logic := '0';
		ram_cs		: out 	std_logic := '0';
		ram_ras		: out 	std_logic := '0';
		ram_cas		: out 	std_logic := '0';
		ram_we		: out 	std_logic := '0';
		
		led : out std_logic_vector(3 downto 0) := "0000";
		btn : in  std_logic_vector(3 downto 0) := "ZZZZ";
		sw : in std_logic_vector(3 downto 0) := "ZZZZ";
		
		dt_dig : out std_logic_vector(3 downto 0) := "0000";
		dt_seg : out std_logic_vector(7 downto 0) := (others => '0');
		
		buzzer : out std_logic := '0';
		
		uart_tx : out std_logic := '0';
		uart_rx : in  std_logic := '0';
		
		scl : inout std_logic := 'Z';
		sda : inout std_logic := 'Z';
		
		i2c_scl : inout std_logic := 'Z';
		i2c_sda : inout std_logic := 'Z';
				
		ir : in std_logic := '0';
		
		vga_hsync : out std_logic := '0';
		vga_vsync : out std_logic := '0';
		vga_r : out std_logic := '0';
		vga_g : out std_logic := '0';
		vga_b : out std_logic := '0';
		
		enc_spi_MISO : in std_logic := '0';
		enc_spi_MOSI : out std_logic := '0';
		enc_spi_SCLK : out std_logic := '0';
		enc_spi_SS_n : out std_logic := '0';
		enc_rst		 : out std_logic := '1';
		enc_irq		 : in  std_logic := '0'

--		sd_miso : in  std_logic := '0';
--		sd_mosi : out std_logic := '0';
--		sd_sck	: out std_logic := '0';
--		sd_cs	: out std_logic := '0'
	);
end entity device;


architecture dev_bhv of device is
    component qsys is
        port (
            clk_clk       : in    std_logic                     := 'X';             -- clk
            reset_reset_n : in    std_logic                     := 'X';             -- reset_n
            ram_addr      : out   std_logic_vector(11 downto 0);                    -- addr
            ram_ba        : out   std_logic_vector(1 downto 0);                     -- ba
            ram_cas_n     : out   std_logic;                                        -- cas_n
            ram_cke       : out   std_logic;                                        -- cke
            ram_cs_n      : out   std_logic;                                        -- cs_n
            ram_dq        : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
            ram_dqm       : out   std_logic_vector(1 downto 0);                     -- dqm
            ram_ras_n     : out   std_logic;                                        -- ras_n
            ram_we_n      : out   std_logic;                                         -- we_n
				
			d7seg_export  : out   std_logic_vector(15 downto 0);                     -- export
				
			led_export    : out   std_logic_vector(3 downto 0);                     -- export
            btn_export    : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- export
				
			enc_spi_MISO  : in    std_logic                     := 'X';             -- MISO
            enc_spi_MOSI  : out   std_logic;                                        -- MOSI
            enc_spi_SCLK  : out   std_logic;                                        -- SCLK
            enc_spi_SS_n  : out   std_logic;                                         -- SS_n

			temp_sda_in   : in    std_logic                     := 'X';             -- sda_in
			temp_scl_in   : in    std_logic                     := 'X';             -- scl_in
			temp_sda_oe   : out   std_logic;                                        -- sda_oe
			temp_scl_oe   : out   std_logic;                                         -- scl_oe

			eeprom_sda_in : in    std_logic                     := 'X';             -- sda_in
			eeprom_scl_in : in    std_logic                     := 'X';             -- scl_in
			eeprom_sda_oe : out   std_logic;                                        -- sda_oe
			eeprom_scl_oe : out   std_logic                                        -- scl_oe
--
--			sdcard_MISO   : in    std_logic                     := 'X';             -- MISO
--			sdcard_MOSI   : out   std_logic;                                        -- MOSI
--			sdcard_SCLK   : out   std_logic;                                        -- SCLK
--			sdcard_SS_n   : out   std_logic                                        -- SS_n
        );
    end component qsys;
	 
	 component disp_7_seg is
		port (
			clock:   in  std_logic;
			num_in: 	in  std_logic_vector(11 downto 0);
			
			num_out: out std_logic_vector(7 downto 0);
			cs:      out std_logic_vector(3 downto 0)
		);
	end component disp_7_seg;
	
	signal s_num_7seg : std_logic_vector(15 downto 0) := (others => '0'); -- 11...0  numbers
																								 -- 15...12 points
																								 
   	signal  s_btn : std_logic_vector(7 downto 0) := (others => '0');
	signal s_led	: std_logic_vector(3 downto 0) := "0000";

	signal s_temp_sda_in   : std_logic                     := 'X';             -- sda_in
	signal s_temp_scl_in   : std_logic                     := 'X';             -- scl_in
	signal s_temp_sda_oe   : std_logic;                                        -- sda_oe
	signal s_temp_scl_oe   : std_logic;                                         -- scl_oe

	signal s_eeprom_sda_in : std_logic                     := 'X';             -- sda_in
	signal s_eeprom_scl_in : std_logic                     := 'X';             -- scl_in
	signal s_eeprom_sda_oe : std_logic;                                        -- sda_oe
	signal s_eeprom_scl_oe : std_logic;                                        -- scl_oe
begin

	led(3 downto 0) <= s_led(3 downto 0);
	--enc_spi_SS_n <= s_led(0);

	ram_clk <= clock;
	--dt_dig  <= s_num_7seg(15 downto 12);
	
	s_btn(3 downto 0) <= btn;
	s_btn(4) <= enc_irq;
	
	enc_rst <= btn(0);

	s_temp_scl_in <= scl; 
	scl  <= '0' when s_temp_scl_oe = '1' else 'Z';
	s_temp_sda_in <= sda; 
	sda  <= '0' when s_temp_sda_oe = '1' else 'Z';

	s_eeprom_scl_in <= i2c_scl; 
	i2c_scl  <= '0' when s_eeprom_scl_oe = '1' else 'Z';
	s_eeprom_sda_in <= i2c_sda; 
	i2c_sda  <= '0' when s_eeprom_sda_oe = '1' else 'Z';

	qsys_unit : qsys
		port map(
            clk_clk                 => clock,
            reset_reset_n           => reset,
            
            ram_addr      => ram_addr,
            ram_ba        => ram_bs,
            ram_cas_n     => ram_cas,
            ram_cke       => ram_cke,
            ram_cs_n      => ram_cs,
            ram_dq        => ram_data,
            ram_dqm       => ram_dm,
            ram_ras_n     => ram_ras,
            ram_we_n      => ram_we,
				
			d7seg_export  => s_num_7seg,
				
			led_export    => s_led,
            btn_export    => s_btn,
				
			enc_spi_MISO  => enc_spi_MISO,
            enc_spi_MOSI  => enc_spi_MOSI,
            enc_spi_SCLK  => enc_spi_SCLK,
            enc_spi_SS_n  => enc_spi_SS_n,

			temp_sda_in   => s_temp_sda_in,
			temp_scl_in   => s_temp_scl_in,
			temp_sda_oe   => s_temp_sda_oe,
			temp_scl_oe   => s_temp_scl_oe,

			eeprom_sda_in => s_eeprom_sda_in,
			eeprom_scl_in => s_eeprom_scl_in,
			eeprom_sda_oe => s_eeprom_sda_oe,
			eeprom_scl_oe => s_eeprom_scl_oe

--			sdcard_MISO   => '0',
--			sdcard_MOSI   => open,
--			sdcard_SCLK   => open,
--			sdcard_SS_n   => open
        );
		  
	disp_7_seg_unit : disp_7_seg		
		port map(
			clock   => clock,
			num_in 	=> s_num_7seg(11 downto 0),
			
			num_out => dt_seg,
			cs      => dt_dig
		);
end architecture;