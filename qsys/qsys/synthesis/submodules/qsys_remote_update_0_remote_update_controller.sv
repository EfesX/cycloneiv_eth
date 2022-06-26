// (C) 2001-2020 Intel Corporation. All rights reserved.
// Your use of Intel Corporation's design tools, logic functions and other 
// software and tools, and its AMPP partner logic functions, and any output 
// files from any of the foregoing (including device programming or simulation 
// files), and any associated documentation or information are expressly subject 
// to the terms and conditions of the Intel Program License Subscription 
// Agreement, Intel FPGA IP License Agreement, or other applicable 
// license agreement, including, without limitation, that your use is for the 
// sole purpose of programming logic devices manufactured by Intel and sold by 
// Intel or its authorized distributors.  Please refer to the applicable 
// agreement for further details.



// $Id: //acds/main/ip/altera_remote_update/altera_remote_update.sv#3 $
// $Revision: #3 $
// $Date: 2014/09/26 $
// $Author: tgngo $

// +----------------------------------------------------------------------
// | Altera Avalon Remote Update Controller
// | This is a controller that allow users to interact with the 
// | Remote Update via Avalon interface
// +----------------------------------------------------------------------
`timescale 1 ps / 1 ps

module qsys_remote_update_0_remote_update_controller
#(
  parameter DEVICE_FAMILY       = "Stratix V",
  parameter IN_DATA_WIDTH       = 32,
  parameter OUT_DATA_WIDTH      = 32,
  parameter CSR_ADDR_WIDTH      = 3
) (
   // +-----------------------------
   // | Clock and Reset
   // +-----------------------------
   input                          clk,
   input                          reset,
   // +-----------------------------
   // | Avalon slave interface
   // +-----------------------------
   input                          avl_csr_write,
   input                          avl_csr_read,
   input [31 : 0]                 avl_csr_wdata,
   output [31 : 0]                avl_csr_rdata,
   output                         avl_csr_readdatavalid,
   output                         avl_csr_waitrequest,
   input [CSR_ADDR_WIDTH - 1 : 0] avl_csr_addr,
   // +-----------------------------
   // | Remote Update interface
   // +-----------------------------
   output [1 : 0]                 ru_read_source,
   output                         ru_read_param,
   output                         ru_write_param,
   output [2 : 0]                 ru_param,
   output                         ru_reconfig,
   output                         ru_reset_timer,
   input                          ru_busy,
   output [IN_DATA_WIDTH - 1 : 0] ru_data_in,
   input [OUT_DATA_WIDTH - 1 : 0] ru_data_out
   );
    
    // +---------------------------------
    // | Internal registers
    // +---------------------------------
    reg [CSR_ADDR_WIDTH - 1 : 0]  csr_addr_reg;    
    reg                           csr_write_reg;
    reg                           csr_read_reg;
    reg [31 : 0]                  csr_wdata_reg;
    reg                           csr_waitrequest_reg;
    
    reg [CSR_ADDR_WIDTH - 1 : 0]  csr_addr;    
    reg                           csr_write;
    reg                           csr_read;
    reg [31 : 0]                  csr_wdata;
    
    reg [CSR_ADDR_WIDTH - 1 : 0]  cmd_addr;    
    reg                           cmd_write;
    reg                           cmd_read;
    reg [31 : 0]                  cmd_wdata;
    wire                          cmd_waitrequest;
    reg                           local_waitrequest;
    wire                          controller_waitrequest;
        
    reg                           use_reg;
    reg                           wait_rise;
    wire                          no_command;
    
    // +------------------------------------------------------------
    // | Command pipeline
    // +------------------------------------------------------------
    assign no_command           = !(cmd_read | cmd_write);
    assign avl_csr_waitrequest  = csr_waitrequest_reg;
    assign wait_rise            = !csr_waitrequest_reg & cmd_waitrequest;
            
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            use_reg             <= '1;
            csr_waitrequest_reg <= '1;
            csr_read_reg        <= '0;
            csr_write_reg       <= '0;
            csr_wdata_reg       <= '0;
            csr_addr_reg        <= '0;
        end
        else begin
            csr_waitrequest_reg <= cmd_waitrequest;
            if (wait_rise) begin
                csr_read_reg  <= avl_csr_read;
                csr_write_reg <= avl_csr_write;
                csr_wdata_reg <= avl_csr_wdata;
                csr_addr_reg  <= avl_csr_addr;
            end
            if (!cmd_waitrequest)
                use_reg <= '0;
            else if (wait_rise) begin
                use_reg <= '1;
            end
        end // else: !if(reset)
    end // always @ (posedge clk or posedge reset)
    
    always_comb begin
        csr_write  = avl_csr_write;
        csr_read   = avl_csr_read;
        csr_wdata  = avl_csr_wdata;
        csr_addr   = avl_csr_addr;
        if (use_reg) begin
            csr_write  = csr_write_reg;
            csr_read   = csr_read_reg;
            csr_wdata  = csr_wdata_reg;
            csr_addr   = csr_addr_reg;
        end
    end // always_comb
    
    //wairequest includes the busy signal from core and a local generated waitrequest
    assign cmd_waitrequest  = (controller_waitrequest | local_waitrequest)  & !no_command;

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            cmd_write <= '0;
            cmd_read  <= '0;
            cmd_wdata <= '0;
            cmd_addr  <= '0;
        end
        else begin
            if (!cmd_waitrequest) begin
                cmd_write <= csr_write;
                cmd_read  <= csr_read;
                cmd_wdata <= csr_wdata;
                cmd_addr  <= csr_addr;
            end
        end // else: !if(reset)
    end // always @ (posedge clk or posedge reset)
    // +------------------------------------------------------------

    // +------------------------------------------------------------
    // | Waitrequest
    // +------------------------------------------------------------
    // | In most cases, the internal waitrequest based on busy signal
    // | from the RU to indicate it is busy or ready to take in new
    // | command.
    // | For some special cases, the busy does not trigger (reset timer, change ctl_nupdt ..)
    // | these are direct signals connect to RU. The local wairequest just acts like a buffer
    // | hold two cycles before it can process new command to make sure the signal has been
    // | completely sent to RU. This is for safety!.

    localparam WAITREQUEST_CYCLES  = 2;
    reg [1:0] wait_latency_counter;
    reg [1:0] next_wait_latency_counter;

    always_comb begin
        if (local_waitrequest) begin
            next_wait_latency_counter      = wait_latency_counter + 1'b1;
            if (next_wait_latency_counter == WAITREQUEST_CYCLES[1:0])
                next_wait_latency_counter = 2'd0;
        end
        else
            next_wait_latency_counter = 2'd0;
    end
    
    always_ff @(posedge clk or posedge reset) begin
        if (reset)
            local_waitrequest <= '0;
        else begin
            wait_latency_counter <= next_wait_latency_counter; 
            if ((cmd_write || cmd_read) && ! cmd_waitrequest)
                local_waitrequest <= 1'b1;
            else begin
                if (wait_latency_counter == 2'b1)
                    local_waitrequest <= 1'b0;
            end
        end // else: !if(reset)
    end // always_ff @

    // +------------------------------------------------------------
    // | Controllers instantiation
    // +------------------------------------------------------------
        avl_controller_cycloneiii_iv #(
            .DEVICE_FAMILY      (DEVICE_FAMILY),
            .IN_DATA_WIDTH      (IN_DATA_WIDTH),
            .OUT_DATA_WIDTH     (OUT_DATA_WIDTH),
            .CSR_ADDR_WIDTH     (CSR_ADDR_WIDTH)
        ) cycloneiii_iv_ctrl (
            .clk                        (clk                    ),
            .reset                      (reset                  ),
            .cmd_write                  (cmd_write              ),
            .cmd_read                   (cmd_read               ),
            .cmd_wdata                  (cmd_wdata              ),
            .cmd_rdata                  (avl_csr_rdata          ),
            .cmd_readdatavalid          (avl_csr_readdatavalid  ),
            .cmd_waitrequest            (controller_waitrequest ),
            .cmd_addr                   (cmd_addr               ),

            .ru_read_param              (ru_read_param          ),
            .ru_write_param             (ru_write_param         ),
            .ru_param                   (ru_param               ),
            .ru_reconfig                (ru_reconfig            ),
            .ru_reset_timer             (ru_reset_timer         ),
            .ru_busy                    (ru_busy                ),
            .ru_read_source             (ru_read_source         ),
            .ru_data_in                 (ru_data_in             ),
            .ru_data_out                (ru_data_out            )
         );  
endmodule

// +------------------------------------------------
// | The avalon controller for V series and Arrria10
// +------------------------------------------------
module avl_controller_v_series_arria10
#(
  parameter DEVICE_FAMILY       = "Stratix V",
  parameter IN_DATA_WIDTH       = 32,
  parameter OUT_DATA_WIDTH      = 32,
  parameter CSR_ADDR_WIDTH      = 3
  
) (
   // +-----------------------------
   // | Clock and Reset
   // +-----------------------------
   input                          clk,
   input                          reset,
   // +-----------------------------
   // | Avalon slave interface
   // +-----------------------------
   input                          cmd_write,
   input                          cmd_read,
   input [31 : 0]                 cmd_wdata,
   output [31 : 0]                cmd_rdata,
   output                         cmd_readdatavalid,
   output                         cmd_waitrequest,
   input [CSR_ADDR_WIDTH - 1 : 0] cmd_addr,
   // +-----------------------------
   // | Remote Update interface
   // +-----------------------------
   output                         ru_read_param,
   output reg                     ru_write_param,
   output [2 : 0]                 ru_param,
   output                         ru_reconfig,
   output                         ru_reset_timer,
   input                          ru_busy,
   output [IN_DATA_WIDTH - 1 : 0] ru_data_in,
   input [OUT_DATA_WIDTH - 1 : 0] ru_data_out
   );

    // +---------------------------------
    // | CSR address offset
    // +---------------------------------
    
    localparam CSR_RECONFIG_TRIGGER_CONDITIONS  = 3'b000;
    localparam CSR_WATCHDOG_TIMEOUT             = 3'b001;
    localparam CSR_WATCHDOG_ENABLE              = 3'b010;
    localparam CSR_PAGE_SELECT                  = 3'b011;
    localparam CSR_CONFIGURATION_MODE           = 3'b100;
    localparam CSR_RESET_TIMER                  = 3'b101;
    localparam CSR_RECONFIG                     = 3'b110;
    localparam CSR_CTL_NUPDT                    = 3'b111;
    localparam HIGH_DATA_W                      = 32 - OUT_DATA_WIDTH;

    // +------------------------------------------------------------
    // | Address decode and internal signals
    // +------------------------------------------------------------
    reg                           local_waitrequest;
    wire                          one_pulse_busy_delay;
    reg [2 : 0]                   ru_param_internal;
    reg                           csr_reset_timer_access;
    reg                           csr_reconfig_access;
    reg                           csr_ctl_nupdt_access;
    reg                           suppress_ru_write;
    
    always_comb begin
        csr_reset_timer_access  = '0;
        csr_reconfig_access     = '0;
        ru_param_internal       = 3'b000;
        suppress_ru_write       = 1'b1;
        if (cmd_addr == CSR_RECONFIG_TRIGGER_CONDITIONS) begin
            ru_param_internal  = 3'b000;
            suppress_ru_write  = 1'b0;
        end
        if (cmd_addr == CSR_WATCHDOG_TIMEOUT) begin
            ru_param_internal  = 3'b010;
            suppress_ru_write = 1'b0;
        end
        if (cmd_addr == CSR_WATCHDOG_ENABLE) begin
            ru_param_internal  = 3'b011;
            suppress_ru_write = 1'b0;
        end
        if (cmd_addr == CSR_PAGE_SELECT) begin
            ru_param_internal  = 3'b100;
            suppress_ru_write = 1'b0;
        end
        if (cmd_addr == CSR_CONFIGURATION_MODE) begin
            ru_param_internal  = 3'b101;
            suppress_ru_write = 1'b0;
        end
        if (cmd_addr == CSR_RESET_TIMER) begin
            csr_reset_timer_access  = 1'b1;
            suppress_ru_write = 1'b1;
        end
        if (cmd_addr == CSR_RECONFIG) begin
            csr_reconfig_access  = 1'b1;
            suppress_ru_write = 1'b1;
        end
    end
    
    // +------------------------------------------------------------
    // | Readdatavalid logic
    // +------------------------------------------------------------
    wire readdata_valid;
    reg  need_response;
    reg  ru_busy_delay;
    
    always_ff @(posedge clk or posedge reset) begin
        if (reset) 
            need_response  <= '0;
        else begin
            if (ru_read_param)
                need_response <= '1;
            if (ru_write_param)
                need_response <= '0;
        end
    end // always_ff @

    always_ff @(posedge clk) begin
        ru_busy_delay <= ru_busy;
    end

    assign one_pulse_busy_delay  = !ru_busy & ru_busy_delay;
    assign readdata_valid        = one_pulse_busy_delay & need_response;
    
    
    // +------------------------------------------------------------
    // | Waitrequest
    // +------------------------------------------------------------
    assign cmd_waitrequest  = (ru_busy | one_pulse_busy_delay);

    // +------------------------------------------------------------
    // | Remote update interface connections
    // +------------------------------------------------------------
    wire csr_reset_timer;
    reg [31 : 0] ru_wdata;
    // Write data to RU block, in most case, it is just direct assign
    // with LSB is wdata[0]
    always_comb begin
        ru_wdata  = cmd_wdata;
    end
    reg reconfig_reg;

    always_ff @(posedge clk or posedge reset) begin
        if (reset)
            reconfig_reg <= '0;
        else begin
            if (csr_reconfig_access && cmd_write && !cmd_waitrequest && (cmd_wdata[0] == 1'b1))
                reconfig_reg <= 1'b1;
        end
    end // always_ff @
    
    always_comb begin
        ru_write_param  = cmd_write & !cmd_waitrequest & !suppress_ru_write;
    end
    
    assign csr_reset_timer  = csr_reset_timer_access && cmd_write && !cmd_waitrequest && (cmd_wdata[0] == 1'b1);
    assign ru_read_param    = cmd_read && !cmd_waitrequest;
    assign ru_data_in       = ru_wdata[IN_DATA_WIDTH - 1 : 0];
    assign ru_param         = ru_param_internal;
    assign ru_reset_timer   = csr_reset_timer;
    assign ru_reconfig      = reconfig_reg;

    // +------------------------------------------------------------
    // | Avalon interface connections
    // +------------------------------------------------------------
    assign cmd_readdatavalid  = readdata_valid;
    assign cmd_rdata          = {{HIGH_DATA_W{1'b0}}, ru_data_out};
    
endmodule


// +------------------------------------------------
// | The avalon controller for Cylone III and IV
// +------------------------------------------------
module avl_controller_cycloneiii_iv
#(
  parameter DEVICE_FAMILY       = "Stratix V",
  parameter IN_DATA_WIDTH       = 32,
  parameter OUT_DATA_WIDTH      = 32,
  parameter CSR_ADDR_WIDTH      = 3
) (
   // +-----------------------------
   // | Clock and Reset
   // +-----------------------------
   input                          clk,
   input                          reset,
   // +-----------------------------
   // | Avalon slave interface
   // +-----------------------------
   input                          cmd_write,
   input                          cmd_read,
   input [31 : 0]                 cmd_wdata,
   output [31 : 0]                cmd_rdata,
   output                         cmd_readdatavalid,
   output                         cmd_waitrequest,
   input [CSR_ADDR_WIDTH - 1 : 0] cmd_addr,
   
   // +-----------------------------
   // | Remote Update interface
   // +-----------------------------
   output                         ru_read_param,
   output reg                     ru_write_param,
   output [2 : 0]                 ru_param,
   output                         ru_reconfig,
   output                         ru_reset_timer,
   input                          ru_busy,
   output [IN_DATA_WIDTH - 1 : 0] ru_data_in,
   input [OUT_DATA_WIDTH - 1 : 0] ru_data_out,
   output [1 : 0]                 ru_read_source
   );

    // +---------------------------------
    // | CSR address offset
    // +---------------------------------
    
    localparam CSR_MASTER_SM_CURRENT_STATE_MODE = 3'b000;
    localparam CSR_FORCE_EARLY_CONF_DONE        = 3'b001;
    localparam CSR_WATCHDOG_TIMEOUT             = 3'b010;
    localparam CSR_WATCHDOG_ENABLE              = 3'b011;
    localparam CSR_BOOT_ADDRESS                 = 3'b100;
    localparam CSR_FORCE_INTERNAL_OSC           = 3'b101;
    localparam CSR_RECONFIG_TRIGGER_CONDITIONS  = 3'b110;
    // The CSR_CONTROL controls reset timer and reconfig operations
    // it uses last two bits to select
    localparam CSR_CONTROL                      = 3'b111;
    localparam HIGH_DATA_W                      = 32 - OUT_DATA_WIDTH;

    // +------------------------------------------------------------
    // | Address decode and internal signals
    // +------------------------------------------------------------

    reg                           local_waitrequest;
    wire                          one_pulse_busy_delay;
    reg [2 : 0]                   ru_param_internal;
    reg                           csr_reset_timer_access;
    reg                           csr_reconfig_access;
    reg                           suppress_ru_write;
    wire [2 : 0]                  cmd_addr_csr;
    
    // For address decode, only need to look at these 3 bits, ignore the last two LSB
    // they are used for read_source
    assign cmd_addr_csr = cmd_addr[CSR_ADDR_WIDTH - 1 : 2];
    always_comb begin
        csr_reset_timer_access  = '0;
        csr_reconfig_access     = '0;
        ru_param_internal       = 3'b000;
        suppress_ru_write       = 1'b1;
        if (cmd_addr_csr == CSR_MASTER_SM_CURRENT_STATE_MODE) begin
            ru_param_internal  = 3'b000;
            suppress_ru_write  = 1'b0;
        end
        if (cmd_addr_csr == CSR_FORCE_EARLY_CONF_DONE) begin
            ru_param_internal  = 3'b001;
            suppress_ru_write  = 1'b0;
        end
        if (cmd_addr_csr == CSR_WATCHDOG_TIMEOUT) begin
            ru_param_internal  = 3'b010;
            suppress_ru_write  = 1'b0;
        end
        if (cmd_addr_csr == CSR_WATCHDOG_ENABLE) begin
            ru_param_internal  = 3'b011;
            suppress_ru_write  = 1'b0;
        end
        if (cmd_addr_csr == CSR_BOOT_ADDRESS) begin
            ru_param_internal  = 3'b100;
            suppress_ru_write  = 1'b0;
        end
        if (cmd_addr_csr == CSR_FORCE_INTERNAL_OSC) begin
            ru_param_internal  = 3'b110;
            suppress_ru_write  = 1'b0;
        end
        if (cmd_addr_csr == CSR_RECONFIG_TRIGGER_CONDITIONS) begin
            ru_param_internal  = 3'b111;
            suppress_ru_write  = 1'b0;
        end
        if (cmd_addr_csr == CSR_CONTROL) begin
            suppress_ru_write  = 1'b1;
            if (cmd_addr[1:0] == 2'b00) // Address offset: 1C
                csr_reset_timer_access  = 1'b1;
            if (cmd_addr[1:0] == 2'b01) // Address offset: 1D
                csr_reconfig_access = 1'b1;
        end
    end
  
    // +------------------------------------------------------------
    // | Readdatavalid logic
    // +------------------------------------------------------------
    wire readdata_valid;
    reg  need_response;
    reg  ru_busy_delay;
    
    always_ff @(posedge clk or posedge reset) begin
        if (reset) 
            need_response  <= '0;
        else begin
            if (ru_read_param)
                need_response <= '1;
            if (ru_write_param)
                need_response <= '0;
        end
    end // always_ff @

    always_ff @(posedge clk) begin
        ru_busy_delay <= ru_busy;
    end

    assign one_pulse_busy_delay  = !ru_busy & ru_busy_delay;
    assign readdata_valid        = one_pulse_busy_delay & need_response;
    
    // +------------------------------------------------------------
    // | Waitrequest
    // +------------------------------------------------------------
    assign cmd_waitrequest  = (ru_busy | one_pulse_busy_delay);
    
    // +------------------------------------------------------------
    // | Remote update interface connections
    // +------------------------------------------------------------
    wire csr_reset_timer;
    reg [31 : 0] ru_wdata;
    // Write data to RU block, in most case, it is just direct assign
    // with LSB is wdata[0]
    always_comb begin
        ru_wdata  = cmd_wdata;
    end
    
    reg reconfig_reg;
    always_ff @(posedge clk or posedge reset) begin
        if (reset)
            reconfig_reg <= '0;
        else begin
            if (csr_reconfig_access && cmd_write && !cmd_waitrequest && (cmd_wdata[0] == 1'b1))
                reconfig_reg <= 1'b1;
        end
    end // always_ff @ 

    always_comb begin
        ru_write_param  = cmd_write & ! cmd_waitrequest & !suppress_ru_write;
    end
    
    assign csr_reset_timer  = csr_reset_timer_access && cmd_write && !cmd_waitrequest && (cmd_wdata[0] == 1'b1);
    assign ru_read_param    = cmd_read && !cmd_waitrequest;
    assign ru_data_in       = ru_wdata[IN_DATA_WIDTH - 1 : 0];
    assign ru_param         = ru_param_internal;
    assign ru_reset_timer   = csr_reset_timer;
    assign ru_reconfig      = reconfig_reg;
    assign ru_read_source   = cmd_addr[1 : 0];
    
    // +------------------------------------------------------------
    // | Avalon interface connections
    // +------------------------------------------------------------
    assign cmd_readdatavalid  = readdata_valid;
    assign cmd_rdata          = {{HIGH_DATA_W{1'b0}}, ru_data_out};
    
endmodule


