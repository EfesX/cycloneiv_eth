library ieee;

use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;


entity multiplexer is
	port (
		clock: in std_logic;
		dig_1: in std_logic_vector(7 downto 0);
		dig_2: in std_logic_vector(7 downto 0);
		dig_3: in std_logic_vector(7 downto 0);
		dig_4: in std_logic_vector(7 downto 0);
		
		dig_out: out std_logic_vector(7 downto 0);
		cs:    	out std_logic_vector(3 downto 0)
	);
end multiplexer;


architecture multiplexer_behav of multiplexer is 
	signal count: integer range 1 to 5 := 1;
begin
	process(clock) begin
	if rising_edge(clock) then
		if (count = 5) then count <= 1; 
		else count <= count + 1; end if;
		
		case count is
			when 1 =>		cs <= "1110"; dig_out <= dig_1;
			when 2 => 		cs <= "1101"; dig_out <= dig_2;
			when 3 => 		cs <= "1011"; dig_out <= dig_3;
			when 4 => 		cs <= "0111"; dig_out <= dig_4;
			when others => cs <= "1111";
		end case;
	end if;
	end process;

end multiplexer_behav;