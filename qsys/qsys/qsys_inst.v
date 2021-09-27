	qsys u0 (
		.btn_export    (<connected-to-btn_export>),    //     btn.export
		.clk_clk       (<connected-to-clk_clk>),       //     clk.clk
		.d7seg_export  (<connected-to-d7seg_export>),  //   d7seg.export
		.enc_spi_MISO  (<connected-to-enc_spi_MISO>),  // enc_spi.MISO
		.enc_spi_MOSI  (<connected-to-enc_spi_MOSI>),  //        .MOSI
		.enc_spi_SCLK  (<connected-to-enc_spi_SCLK>),  //        .SCLK
		.enc_spi_SS_n  (<connected-to-enc_spi_SS_n>),  //        .SS_n
		.led_export    (<connected-to-led_export>),    //     led.export
		.ram_addr      (<connected-to-ram_addr>),      //     ram.addr
		.ram_ba        (<connected-to-ram_ba>),        //        .ba
		.ram_cas_n     (<connected-to-ram_cas_n>),     //        .cas_n
		.ram_cke       (<connected-to-ram_cke>),       //        .cke
		.ram_cs_n      (<connected-to-ram_cs_n>),      //        .cs_n
		.ram_dq        (<connected-to-ram_dq>),        //        .dq
		.ram_dqm       (<connected-to-ram_dqm>),       //        .dqm
		.ram_ras_n     (<connected-to-ram_ras_n>),     //        .ras_n
		.ram_we_n      (<connected-to-ram_we_n>),      //        .we_n
		.reset_reset_n (<connected-to-reset_reset_n>), //   reset.reset_n
		.temp_sda_in   (<connected-to-temp_sda_in>),   //    temp.sda_in
		.temp_scl_in   (<connected-to-temp_scl_in>),   //        .scl_in
		.temp_sda_oe   (<connected-to-temp_sda_oe>),   //        .sda_oe
		.temp_scl_oe   (<connected-to-temp_scl_oe>),   //        .scl_oe
		.eeprom_sda_in (<connected-to-eeprom_sda_in>), //  eeprom.sda_in
		.eeprom_scl_in (<connected-to-eeprom_scl_in>), //        .scl_in
		.eeprom_sda_oe (<connected-to-eeprom_sda_oe>), //        .sda_oe
		.eeprom_scl_oe (<connected-to-eeprom_scl_oe>)  //        .scl_oe
	);

