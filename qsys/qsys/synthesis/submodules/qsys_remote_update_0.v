// qsys_remote_update_0.v

// This file was auto-generated from altera_remote_update_hw.tcl.  If you edit it your changes
// will probably be lost.
// 
// Generated using ACDS version 20.1 720

`timescale 1 ps / 1 ps
module qsys_remote_update_0 (
		input  wire        avl_csr_write,         // avl_csr.write
		input  wire        avl_csr_read,          //        .read
		input  wire [31:0] avl_csr_writedata,     //        .writedata
		output wire [31:0] avl_csr_readdata,      //        .readdata
		output wire        avl_csr_readdatavalid, //        .readdatavalid
		output wire        avl_csr_waitrequest,   //        .waitrequest
		input  wire [4:0]  avl_csr_address,       //        .address
		input  wire        clock,                 //   clock.clk
		input  wire        reset                  //   reset.reset
	);

	wire         remote_update_controller_read_param_read_param;   // remote_update_controller:ru_read_param -> remote_update_core:read_param
	wire   [2:0] remote_update_controller_param_param;             // remote_update_controller:ru_param -> remote_update_core:param
	wire         remote_update_controller_reconfig_reconfig;       // remote_update_controller:ru_reconfig -> remote_update_core:reconfig
	wire         remote_update_controller_reset_timer_reset_timer; // remote_update_controller:ru_reset_timer -> remote_update_core:reset_timer
	wire         remote_update_core_busy_busy;                     // remote_update_core:busy -> remote_update_controller:ru_busy
	wire  [28:0] remote_update_core_data_out_data_out;             // remote_update_core:data_out -> remote_update_controller:ru_data_out
	wire   [1:0] remote_update_controller_read_source_read_source; // remote_update_controller:ru_read_source -> remote_update_core:read_source

	altera_remote_update_core remote_update_core (
		.read_param  (remote_update_controller_read_param_read_param),   //  read_param.read_param
		.param       (remote_update_controller_param_param),             //       param.param
		.reconfig    (remote_update_controller_reconfig_reconfig),       //    reconfig.reconfig
		.reset_timer (remote_update_controller_reset_timer_reset_timer), // reset_timer.reset_timer
		.clock       (clock),                                            //       clock.clk
		.reset       (reset),                                            //       reset.reset
		.busy        (remote_update_core_busy_busy),                     //        busy.busy
		.data_out    (remote_update_core_data_out_data_out),             //    data_out.data_out
		.read_source (remote_update_controller_read_source_read_source), // read_source.read_source
		.ctl_nupdt   (1'b0)                                              // (terminated)
	);

	qsys_remote_update_0_remote_update_controller #(
		.DEVICE_FAMILY  ("Cyclone IV E"),
		.IN_DATA_WIDTH  (24),
		.OUT_DATA_WIDTH (29),
		.CSR_ADDR_WIDTH (5)
	) remote_update_controller (
		.avl_csr_write         (avl_csr_write),                                    //     avl_csr.write
		.avl_csr_read          (avl_csr_read),                                     //            .read
		.avl_csr_wdata         (avl_csr_writedata),                                //            .writedata
		.avl_csr_rdata         (avl_csr_readdata),                                 //            .readdata
		.avl_csr_readdatavalid (avl_csr_readdatavalid),                            //            .readdatavalid
		.avl_csr_waitrequest   (avl_csr_waitrequest),                              //            .waitrequest
		.avl_csr_addr          (avl_csr_address),                                  //            .address
		.clk                   (clock),                                            //         clk.clk
		.reset                 (reset),                                            //       reset.reset
		.ru_read_param         (remote_update_controller_read_param_read_param),   //  read_param.read_param
		.ru_param              (remote_update_controller_param_param),             //       param.param
		.ru_reconfig           (remote_update_controller_reconfig_reconfig),       //    reconfig.reconfig
		.ru_reset_timer        (remote_update_controller_reset_timer_reset_timer), // reset_timer.reset_timer
		.ru_busy               (remote_update_core_busy_busy),                     //        busy.busy
		.ru_data_out           (remote_update_core_data_out_data_out),             //    data_out.data_out
		.ru_read_source        (remote_update_controller_read_source_read_source)  // read_source.read_source
	);

endmodule