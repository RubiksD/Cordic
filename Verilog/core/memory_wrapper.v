/*
File: memory_wrapper.v
Modules: memory_wrapper
Heirarchy: memory_wrapper

Created : 28/2/2016

*/

/*
Module: memory_wrapper
*/

module memory_wrapper(
	clk,
	cen,
	wr_en,
	addr,
	wdata,
	rdata
);
input wire	                clk;
input wire	                cen;
input wire	                wr_en;
input wire [ADDR_WIDTH-1:0] addr;
input wire [DATA_WIDTH-1:0]	wdata;
output reg [DATA_WIDTH-1:0] rdata;

parameter ADDR_WIDTH = 6;
parameter DATA_WIDTH = 32;

parameter ADDRESSES = 1 << ADDR_WIDTH;

reg [DATA_WIDTH-1:0] mem [0:ADDRESSES-1];

always@(posedge clk)
if(~cen)
begin
	if(wr_en)
	begin
		mem[addr] <= wdata;
	end
	else
	begin
		rdata <= mem[addr];
	end
end
endmodule
