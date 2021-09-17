library ieee;

use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;



entity digit is
	port (
		num_dig_in: 	in  std_logic_vector(3 downto 0);
		num_dig_out:   out std_logic_vector(7 downto 0)
		--ind1_cs:	out std_logic
	);
end digit;



architecture digit_behav of digit is 
	--signal num:	std_logic_vector(3 downto 0);
	signal int: integer range 0 to 4097;

begin
	int <= to_integer(signed(num_dig_in));
	
	process(int) begin
		case int is
			when 0 =>		num_dig_out <= "11000000"; --ind1_cs <= '0';
			when 1 =>		num_dig_out <= "11111001"; --ind1_cs <= '0';
			when 2 => 		num_dig_out <= "10100100"; --ind1_cs <= '0';
			when 3 => 		num_dig_out <= "10110000"; --ind1_cs <= '0';
			when 4 => 		num_dig_out <= "10011001"; --ind1_cs <= '0';
			when 5 => 		num_dig_out <= "10010010"; --ind1_cs <= '0';
			when 6 => 		num_dig_out <= "10000010"; --ind1_cs <= '0';
			when 7 => 		num_dig_out <= "11111000"; --ind1_cs <= '0';
			when 8 =>		num_dig_out <= "10000000"; --ind1_cs <= '0';
			when 9 => 		num_dig_out <= "10010000"; --ind1_cs <= '0';
			when others => num_dig_out <= "01111111";
		end case;
	end process;
end digit_behav;