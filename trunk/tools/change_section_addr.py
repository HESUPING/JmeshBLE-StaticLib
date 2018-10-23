import sys
import re
import os
axf_file = sys.argv[1]
elf_for_gdb_file = sys.argv[2]
if(len(sys.argv)== 4):
    map_file_hdl = open(sys.argv[3])
else:
    map_file_hdl = open('../build/ble-full-bx2400/linkinfo.armcc.txt')
map_file = map_file_hdl.read()

nvds_area_pattern = re.compile('Execution Region NVDS_AREA \(Base: 0x(\w+), Size: 0x(\w+)')
match_nvds = nvds_area_pattern.search(map_file)
if(match_nvds):
    nvds_area_base = int(match_nvds.group(1),16)
    nvds_area_size = int(match_nvds.group(2),16)
else:
    print('NVDS_AREA not found')
    exit(1)
    
lr_ram2_pattern = re.compile('Load Region LR_RAM2 \(Base: 0x(\w+), Size: 0x(\w+)')
match_lr_ram2 = lr_ram2_pattern.search(map_file)
if(match_lr_ram2):
    lr_ram2_base = int(match_lr_ram2.group(1),16)
else:
    print('LR_RAM2 not found')
    exit(1)

cmd = 'arm-none-eabi-objcopy --change-section-address NVDS_AREA=' + str(lr_ram2_base) +' ' + axf_file +' ' + elf_for_gdb_file
rslt=os.system(cmd)
print('arm-none-eabi-objcopy return value: '+str(rslt))
print(axf_file +' NVDS_AREA section address set to '+ str(hex(lr_ram2_base))+' > '+elf_for_gdb_file)