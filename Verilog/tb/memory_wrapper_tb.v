`timescale 1ns/1ps
module memory_wrapper_tb(
);

parameter ADDR_WIDTH = 6;
parameter DATA_WIDTH = 32;

reg clk;
reg cen;
reg wr_en;
reg [ADDR_WIDTH-1:0] addr;
reg [DATA_WIDTH-1:0] wdata;
wire [DATA_WIDTH-1:0] rdata;

reg reset_n;
reg [ADDR_WIDTH:0]counter;


initial
begin
reset_n = 1'b0;
#100 reset_n= 1'b1;
end
initial
begin
$dumpfile("mem_wrapper_dump.vcd");
//$dumpvars(0,memory_wrapper_tb);
$dumpvars;
#3000 $finish;
end

initial
begin
$monitor("At timetime %t, value = %h (%0d)",
              $time, rdata, rdata);
end

initial
begin
clk = 0;
forever #10 clk =~clk;
end

always@(posedge clk or negedge reset_n)
begin
	if(~reset_n)
	begin
		cen <= 1'b1;
		wr_en <= 1'b0;
		addr <= {(ADDR_WIDTH){1'b0}};
		wdata<= {(DATA_WIDTH){1'b0}};
		counter <= {(ADDR_WIDTH+1){1'b0}};
	end
	else
	begin
		cen <= 1'b0;
		wr_en <= ~counter[ADDR_WIDTH];
		addr <= counter[ADDR_WIDTH-1:0];
		counter <= counter + {{(ADDR_WIDTH){1'b0}},{1'b1}};
		wdata <= counter[ADDR_WIDTH-1:0];
	end
end

memory_wrapper mem_wrap_inst(
	.clk  (clk  ) ,
	.cen  (cen  ) ,
	.wr_en(wr_en) ,
	.addr (addr ) ,
	.wdata(wdata) ,
	.rdata(rdata)
);
endmodule
