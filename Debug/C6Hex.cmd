Uprava1702.out
--binary
--map=Uprava1702.map
--order=L

--boot
--bootorg=0xB0001000
--bootsection=.boot_load 0xB0000000

--image
--zero
--fill=0xFFFFFFFF

ROMS
{
	FLASH: org = 0xB0000000, len = 0x20000, romwidth = 8, memwidth = 8 files={Uprava1702.bin}
}


/*
--outfile=MT.bin
--memwidth=8
--romwidth=8

*/
