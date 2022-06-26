
module qsys (
	btn_export,
	clk_clk,
	d7seg_export,
	eeprom_sda_in,
	eeprom_scl_in,
	eeprom_sda_oe,
	eeprom_scl_oe,
	enc_spi_MISO,
	enc_spi_MOSI,
	enc_spi_SCLK,
	enc_spi_SS_n,
	led_export,
	ram_addr,
	ram_ba,
	ram_cas_n,
	ram_cke,
	ram_cs_n,
	ram_dq,
	ram_dqm,
	ram_ras_n,
	ram_we_n,
	reset_reset_n,
	temp_sda_in,
	temp_scl_in,
	temp_sda_oe,
	temp_scl_oe);	

	input	[7:0]	btn_export;
	input		clk_clk;
	output	[15:0]	d7seg_export;
	input		eeprom_sda_in;
	input		eeprom_scl_in;
	output		eeprom_sda_oe;
	output		eeprom_scl_oe;
	input		enc_spi_MISO;
	output		enc_spi_MOSI;
	output		enc_spi_SCLK;
	output		enc_spi_SS_n;
	output	[3:0]	led_export;
	output	[11:0]	ram_addr;
	output	[1:0]	ram_ba;
	output		ram_cas_n;
	output		ram_cke;
	output		ram_cs_n;
	inout	[15:0]	ram_dq;
	output	[1:0]	ram_dqm;
	output		ram_ras_n;
	output		ram_we_n;
	input		reset_reset_n;
	input		temp_sda_in;
	input		temp_scl_in;
	output		temp_sda_oe;
	output		temp_scl_oe;
endmodule
