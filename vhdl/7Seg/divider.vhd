library ieee;

use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;




entity divider is
	generic(
		 count: integer range 0 to 5000 := 0
	);
	port (
		clock: 	in  std_logic;
		clock_div:  out std_logic
	);
end divider;



architecture divider_behav of divider is 
	--signal cnt: integer range 0 to 5000 := 0;
	signal clk:  std_logic := '0';
	signal cnt: integer range 0 to 5000 := 0;
begin
	
	clock_div <= clk;
	
	process(clock) begin
		if rising_edge(clock) then
			if (cnt = count) then
				clk <= not clk;
				cnt <= 0;
			else
				cnt <= cnt + 1;
			end if;
		end if;
	end process;
end divider_behav;