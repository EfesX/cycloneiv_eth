library ieee;

use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

use ieee.std_logic_arith.all;


entity bin_to_bcd is
	port (
		bin:			in  std_logic_vector(11 downto 0);
		bcd_dig_1:	out std_logic_vector(3 downto 0);
		bcd_dig_2:	out std_logic_vector(3 downto 0);
		bcd_dig_3:	out std_logic_vector(3 downto 0);
		bcd_dig_4:	out std_logic_vector(3 downto 0)
	);
end bin_to_bcd;


architecture bin_to_bcd_behav of bin_to_bcd is 

begin
	process(bin)
		variable num: 			integer range 0 to 4097;
		variable num_dig: 	integer range 0 to 9;
	begin
		num 			:= conv_integer(bin);
		
		num_dig	 	:= num / 1000;
		bcd_dig_4	<= CONV_STD_LOGIC_VECTOR(num_dig, 4);
		
		num_dig		:= (num rem 1000) / 100;
		bcd_dig_3	<= CONV_STD_LOGIC_VECTOR(num_dig, 4);
		
		num_dig		:= ((num rem 1000) rem 100) / 10;
		bcd_dig_2	<= CONV_STD_LOGIC_VECTOR(num_dig, 4);
		
		num_dig		:= ((num rem 1000) rem 100) rem 10;
		bcd_dig_1	<= CONV_STD_LOGIC_VECTOR(num_dig, 4);
	end process;
end bin_to_bcd_behav;