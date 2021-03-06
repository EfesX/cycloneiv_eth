library ieee;

use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;



entity disp_7_seg is
	port (
		clock:   in  std_logic;
		num_in: 	in  std_logic_vector(11 downto 0);
		
		num_out: out std_logic_vector(7 downto 0);
		cs:      out std_logic_vector(3 downto 0)
	);
end disp_7_seg;



architecture disp_7_seg_struct of disp_7_seg is 

	component bin_to_bcd is
		port (
			bin:			in  std_logic_vector(11 downto 0);
			bcd_dig_1:	out std_logic_vector(3 downto 0);
			bcd_dig_2:	out std_logic_vector(3 downto 0);
			bcd_dig_3:	out std_logic_vector(3 downto 0);
		   bcd_dig_4:	out std_logic_vector(3 downto 0)
		);
	end component;
		
	component digit is
		port (
			num_dig_in: 	in  std_logic_vector(3 downto 0);
			num_dig_out: out std_logic_vector(7 downto 0)
		);
	end component;

	component multiplexer is
		port (
			clock: in std_logic;
			dig_1: in std_logic_vector(7 downto 0);
			dig_2: in std_logic_vector(7 downto 0);
			dig_3: in std_logic_vector(7 downto 0);
		   dig_4: in std_logic_vector(7 downto 0);
			
			dig_out: out std_logic_vector(7 downto 0);
			cs:    	out std_logic_vector(3 downto 0)
		);
	end component;
	
	component divider is
		generic(
			count: integer range 0 to 5000 := 5000
		);
		port (
			clock: 	in  std_logic;
			clock_div:  out std_logic := '0'
		);
	end component;
	
	signal bcd_1: std_logic_vector(3 downto 0);
	signal bcd_2: std_logic_vector(3 downto 0);
	signal bcd_3: std_logic_vector(3 downto 0);
	signal bcd_4: std_logic_vector(3 downto 0);
	
	signal dig_1: std_logic_vector(7 downto 0);
	signal dig_2: std_logic_vector(7 downto 0);
	signal dig_3: std_logic_vector(7 downto 0);
	signal dig_4: std_logic_vector(7 downto 0);
	
	signal clock_div: std_logic;
	
begin
----------------------------------
	bin2bcd: bin_to_bcd 
		port map(
			bin 		 => num_in,
			bcd_dig_1 => bcd_1,
			bcd_dig_2 => bcd_2,
			bcd_dig_3 => bcd_3,
			bcd_dig_4 => bcd_4
		);
-----------------------------------
	digit_1: digit
		port map(
			num_dig_in 	=> bcd_1,
			num_dig_out => dig_1
		);
-----------------------------------
	digit_2: digit
		port map(
			num_dig_in 	=> bcd_2,
			num_dig_out => dig_2
		);
-----------------------------------
	digit_3: digit
		port map(
			num_dig_in 	=> bcd_3,
			num_dig_out => dig_3
		);
-----------------------------------
	digit_4: digit
		port map(
			num_dig_in 	=> bcd_4,
			num_dig_out => dig_4
		);
-----------------------------------
	mult: multiplexer
		port map(
			clock => clock_div,
			dig_1 => dig_1,
			dig_2 => dig_2,
			dig_3 => dig_3,
			dig_4 => dig_4,
			
			dig_out  => num_out,
			cs			=> cs
		);
----------------------------------
	div: divider
		port map(
			clock 	 => clock,
			clock_div => clock_div
		);
----------------------------------

end disp_7_seg_struct;