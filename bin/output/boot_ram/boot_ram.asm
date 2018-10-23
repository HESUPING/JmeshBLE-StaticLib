
========================================================================

** ELF Header Information

    File Name: boot_ram.elf

    Machine class: ELFCLASS32 (32-bit)
    Data encoding: ELFDATA2LSB (Little endian)
    Header version: EV_CURRENT (Current version)
    Operating System ABI: none
    ABI Version: 0
    File Type: ET_EXEC (Executable) (2)
    Machine: EM_ARM (ARM)

    Image Entry point: 0x0012e259
    Flags: EF_ARM_HASENTRY + EF_ARM_ABI_FLOAT_SOFT (0x05000202)

    ARM ELF revision: 5 (ABI version 2)

    Conforms to Soft float procedure-call standard

    Built with
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armasm [4d35a5]
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armcc [4d35ad]
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armlink [4d35a8]

    Header size: 52 bytes (0x34)
    Program header entry size: 32 bytes (0x20)
    Section header entry size: 40 bytes (0x28)

    Program header entries: 1
    Section header entries: 15

    Program header offset: 325256 (0x0004f688)
    Section header offset: 325288 (0x0004f6a8)

    Section header string table index: 14

========================================================================

** Program header #0

    Type          : PT_LOAD (1)
    File Offset   : 52 (0x34)
    Virtual Addr  : 0x0012dff0
    Physical Addr : 0x0012dff0
    Size in file  : 2768 bytes (0xad0)
    Size in memory: 2768 bytes (0xad0)
    Flags         : PF_X + PF_W + PF_R + PF_ARM_ENTRY (0x80000007)
    Alignment     : 4


========================================================================

** Section #1

    Name        : EXEC_SECTION
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : SHF_ALLOC + SHF_EXECINSTR (0x00000006)
    Addr        : 0x0012dff0
    File Offset : 52 (0x34)
    Size        : 2764 bytes (0xacc)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 4
    Entry Size  : 0

    $d.realdata
    boot_header_area
    boot_info
        0x0012dff0:    34325842    BX24    DCD    875714626
        0x0012dff4:    0012e000    ....    DCD    1236992
        0x0012dff8:    ffffffff    ....    DCD    4294967295
        0x0012dffc:    0012e259    Y...    DCD    1237593
        0x0012e000:    ffffffff    ....    DCD    4294967295
        0x0012e004:    ffffffff    ....    DCD    4294967295
        0x0012e008:    ffffffff    ....    DCD    4294967295
        0x0012e00c:    ffffffff    ....    DCD    4294967295
        0x0012e010:    00000000    ....    DCD    0
    $t
    .text
    __aeabi_uidiv
    __aeabi_uidivmod
        0x0012e014:    b530        0.      PUSH     {r4,r5,lr}
        0x0012e016:    460b        .F      MOV      r3,r1
        0x0012e018:    4601        .F      MOV      r1,r0
        0x0012e01a:    2000        .       MOVS     r0,#0
        0x0012e01c:    2220         "      MOVS     r2,#0x20
        0x0012e01e:    2401        .$      MOVS     r4,#1
        0x0012e020:    e009        ..      B        0x12e036 ; __aeabi_uidiv + 34
        0x0012e022:    460d        .F      MOV      r5,r1
        0x0012e024:    40d5        .@      LSRS     r5,r5,r2
        0x0012e026:    429d        .B      CMP      r5,r3
        0x0012e028:    d305        ..      BCC      0x12e036 ; __aeabi_uidiv + 34
        0x0012e02a:    461d        .F      MOV      r5,r3
        0x0012e02c:    4095        .@      LSLS     r5,r5,r2
        0x0012e02e:    1b49        I.      SUBS     r1,r1,r5
        0x0012e030:    4625        %F      MOV      r5,r4
        0x0012e032:    4095        .@      LSLS     r5,r5,r2
        0x0012e034:    1940        @.      ADDS     r0,r0,r5
        0x0012e036:    4615        .F      MOV      r5,r2
        0x0012e038:    1e52        R.      SUBS     r2,r2,#1
        0x0012e03a:    2d00        .-      CMP      r5,#0
        0x0012e03c:    dcf1        ..      BGT      0x12e022 ; __aeabi_uidiv + 14
        0x0012e03e:    bd30        0.      POP      {r4,r5,pc}
    i.awo_bootram_init
    awo_bootram_init
        0x0012e040:    b570        p.      PUSH     {r4-r6,lr}
        0x0012e042:    bf00        ..      NOP      
        0x0012e044:    4822        "H      LDR      r0,[pc,#136] ; [0x12e0d0] = 0x20201000
        0x0012e046:    68c0        .h      LDR      r0,[r0,#0xc]
        0x0012e048:    0580        ..      LSLS     r0,r0,#22
        0x0012e04a:    0fc0        ..      LSRS     r0,r0,#31
        0x0012e04c:    2800        .(      CMP      r0,#0
        0x0012e04e:    d000        ..      BEQ      0x12e052 ; awo_bootram_init + 18
        0x0012e050:    bd70        p.      POP      {r4-r6,pc}
        0x0012e052:    2001        .       MOVS     r0,#1
        0x0012e054:    491e        .I      LDR      r1,[pc,#120] ; [0x12e0d0] = 0x20201000
        0x0012e056:    68c9        .h      LDR      r1,[r1,#0xc]
        0x0012e058:    0242        B.      LSLS     r2,r0,#9
        0x0012e05a:    4391        .C      BICS     r1,r1,r2
        0x0012e05c:    0242        B.      LSLS     r2,r0,#9
        0x0012e05e:    0243        C.      LSLS     r3,r0,#9
        0x0012e060:    401a        .@      ANDS     r2,r2,r3
        0x0012e062:    4311        .C      ORRS     r1,r1,r2
        0x0012e064:    4a1a        .J      LDR      r2,[pc,#104] ; [0x12e0d0] = 0x20201000
        0x0012e066:    60d1        .`      STR      r1,[r2,#0xc]
        0x0012e068:    bf00        ..      NOP      
        0x0012e06a:    f000fceb    ....    BL       sysc_awo_dr_16m_rcosc_en_setf ; 0x12ea44
        0x0012e06e:    2000        .       MOVS     r0,#0
        0x0012e070:    f000fcf6    ....    BL       sysc_awo_reg_16m_rcosc_en_setf ; 0x12ea60
        0x0012e074:    2001        .       MOVS     r0,#1
        0x0012e076:    f000f831    ..1.    BL       awo_clk_div_pbus_para_m1 ; 0x12e0dc
        0x0012e07a:    f000f841    ..A.    BL       awo_clk_div_pbus_para_up ; 0x12e100
        0x0012e07e:    2020                MOVS     r0,#0x20
        0x0012e080:    f000f844    ..D.    BL       awo_clkgate_en ; 0x12e10c
        0x0012e084:    4913        .I      LDR      r1,[pc,#76] ; [0x12e0d4] = 0xf4240
        0x0012e086:    4814        .H      LDR      r0,[pc,#80] ; [0x12e0d8] = 0x12eabc
        0x0012e088:    6800        .h      LDR      r0,[r0,#0]
        0x0012e08a:    f7ffffc3    ....    BL       __aeabi_uidiv ; 0x12e014
        0x0012e08e:    b2c5        ..      UXTB     r5,r0
        0x0012e090:    4628        (F      MOV      r0,r5
        0x0012e092:    f000f86f    ..o.    BL       awo_open_pll ; 0x12e174
        0x0012e096:    2400        .$      MOVS     r4,#0
        0x0012e098:    e002        ..      B        0x12e0a0 ; awo_bootram_init + 96
        0x0012e09a:    bf00        ..      NOP      
        0x0012e09c:    1c60        `.      ADDS     r0,r4,#1
        0x0012e09e:    b284        ..      UXTH     r4,r0
        0x0012e0a0:    2c05        .,      CMP      r4,#5
        0x0012e0a2:    dbfa        ..      BLT      0x12e09a ; awo_bootram_init + 90
        0x0012e0a4:    bf00        ..      NOP      
        0x0012e0a6:    bf00        ..      NOP      
        0x0012e0a8:    4809        .H      LDR      r0,[pc,#36] ; [0x12e0d0] = 0x20201000
        0x0012e0aa:    3080        .0      ADDS     r0,r0,#0x80
        0x0012e0ac:    6b00        .k      LDR      r0,[r0,#0x30]
        0x0012e0ae:    2120         !      MOVS     r1,#0x20
        0x0012e0b0:    4008        .@      ANDS     r0,r0,r1
        0x0012e0b2:    2800        .(      CMP      r0,#0
        0x0012e0b4:    d0f7        ..      BEQ      0x12e0a6 ; awo_bootram_init + 102
        0x0012e0b6:    2002        .       MOVS     r0,#2
        0x0012e0b8:    f000f83e    ..>.    BL       awo_hbus1_clksel ; 0x12e138
        0x0012e0bc:    2010        .       MOVS     r0,#0x10
        0x0012e0be:    f000f825    ..%.    BL       awo_clkgate_en ; 0x12e10c
        0x0012e0c2:    2002        .       MOVS     r0,#2
        0x0012e0c4:    f000f82a    ..*.    BL       awo_hbus0_clksel ; 0x12e11c
        0x0012e0c8:    f000f8c0    ....    BL       awo_set_parameter ; 0x12e24c
        0x0012e0cc:    bf00        ..      NOP      
        0x0012e0ce:    e7bf        ..      B        0x12e050 ; awo_bootram_init + 16
    $d
        0x0012e0d0:    20201000    ..      DCD    538972160
        0x0012e0d4:    000f4240    @B..    DCD    1000000
        0x0012e0d8:    0012eabc    ....    DCD    1239740
    $t
    i.awo_clk_div_pbus_para_m1
    awo_clk_div_pbus_para_m1
        0x0012e0dc:    bf00        ..      NOP      
        0x0012e0de:    4907        .I      LDR      r1,[pc,#28] ; [0x12e0fc] = 0x20201000
        0x0012e0e0:    6809        .h      LDR      r1,[r1,#0]
        0x0012e0e2:    220f        ."      MOVS     r2,#0xf
        0x0012e0e4:    0412        ..      LSLS     r2,r2,#16
        0x0012e0e6:    4391        .C      BICS     r1,r1,r2
        0x0012e0e8:    0402        ..      LSLS     r2,r0,#16
        0x0012e0ea:    230f        .#      MOVS     r3,#0xf
        0x0012e0ec:    041b        ..      LSLS     r3,r3,#16
        0x0012e0ee:    401a        .@      ANDS     r2,r2,r3
        0x0012e0f0:    4311        .C      ORRS     r1,r1,r2
        0x0012e0f2:    4a02        .J      LDR      r2,[pc,#8] ; [0x12e0fc] = 0x20201000
        0x0012e0f4:    6011        .`      STR      r1,[r2,#0]
        0x0012e0f6:    bf00        ..      NOP      
        0x0012e0f8:    4770        pG      BX       lr
    $d
        0x0012e0fa:    0000        ..      DCW    0
        0x0012e0fc:    20201000    ..      DCD    538972160
    $t
    i.awo_clk_div_pbus_para_up
    awo_clk_div_pbus_para_up
        0x0012e100:    b510        ..      PUSH     {r4,lr}
        0x0012e102:    2001        .       MOVS     r0,#1
        0x0012e104:    f000fc98    ....    BL       sysc_awo_clkgen_awo_signal_1_set ; 0x12ea38
        0x0012e108:    bd10        ..      POP      {r4,pc}
        0x0012e10a:    0000        ..      MOVS     r0,r0
    i.awo_clkgate_en
    awo_clkgate_en
        0x0012e10c:    bf00        ..      NOP      
        0x0012e10e:    4902        .I      LDR      r1,[pc,#8] ; [0x12e118] = 0x20201000
        0x0012e110:    6048        H`      STR      r0,[r1,#4]
        0x0012e112:    bf00        ..      NOP      
        0x0012e114:    4770        pG      BX       lr
    $d
        0x0012e116:    0000        ..      DCW    0
        0x0012e118:    20201000    ..      DCD    538972160
    $t
    i.awo_hbus0_clksel
    awo_hbus0_clksel
        0x0012e11c:    bf00        ..      NOP      
        0x0012e11e:    4905        .I      LDR      r1,[pc,#20] ; [0x12e134] = 0x20201000
        0x0012e120:    6809        .h      LDR      r1,[r1,#0]
        0x0012e122:    08c9        ..      LSRS     r1,r1,#3
        0x0012e124:    00c9        ..      LSLS     r1,r1,#3
        0x0012e126:    0742        B.      LSLS     r2,r0,#29
        0x0012e128:    0f52        R.      LSRS     r2,r2,#29
        0x0012e12a:    4311        .C      ORRS     r1,r1,r2
        0x0012e12c:    4a01        .J      LDR      r2,[pc,#4] ; [0x12e134] = 0x20201000
        0x0012e12e:    6011        .`      STR      r1,[r2,#0]
        0x0012e130:    bf00        ..      NOP      
        0x0012e132:    4770        pG      BX       lr
    $d
        0x0012e134:    20201000    ..      DCD    538972160
    $t
    i.awo_hbus1_clksel
    awo_hbus1_clksel
        0x0012e138:    bf00        ..      NOP      
        0x0012e13a:    4906        .I      LDR      r1,[pc,#24] ; [0x12e154] = 0x20201000
        0x0012e13c:    6809        .h      LDR      r1,[r1,#0]
        0x0012e13e:    2218        ."      MOVS     r2,#0x18
        0x0012e140:    4391        .C      BICS     r1,r1,r2
        0x0012e142:    00c2        ..      LSLS     r2,r0,#3
        0x0012e144:    2318        .#      MOVS     r3,#0x18
        0x0012e146:    401a        .@      ANDS     r2,r2,r3
        0x0012e148:    4311        .C      ORRS     r1,r1,r2
        0x0012e14a:    4a02        .J      LDR      r2,[pc,#8] ; [0x12e154] = 0x20201000
        0x0012e14c:    6011        .`      STR      r1,[r2,#0]
        0x0012e14e:    bf00        ..      NOP      
        0x0012e150:    4770        pG      BX       lr
    $d
        0x0012e152:    0000        ..      DCW    0
        0x0012e154:    20201000    ..      DCD    538972160
    $t
    i.awo_ldo_setup_time
    awo_ldo_setup_time
        0x0012e158:    bf00        ..      NOP      
        0x0012e15a:    4905        .I      LDR      r1,[pc,#20] ; [0x12e170] = 0x20201000
        0x0012e15c:    6989        .i      LDR      r1,[r1,#0x18]
        0x0012e15e:    0a09        ..      LSRS     r1,r1,#8
        0x0012e160:    0209        ..      LSLS     r1,r1,#8
        0x0012e162:    b2c2        ..      UXTB     r2,r0
        0x0012e164:    4311        .C      ORRS     r1,r1,r2
        0x0012e166:    4a02        .J      LDR      r2,[pc,#8] ; [0x12e170] = 0x20201000
        0x0012e168:    6191        .a      STR      r1,[r2,#0x18]
        0x0012e16a:    bf00        ..      NOP      
        0x0012e16c:    4770        pG      BX       lr
    $d
        0x0012e16e:    0000        ..      DCW    0
        0x0012e170:    20201000    ..      DCD    538972160
    $t
    i.awo_open_pll
    awo_open_pll
        0x0012e174:    b570        p.      PUSH     {r4-r6,lr}
        0x0012e176:    4604        .F      MOV      r4,r0
        0x0012e178:    2c40        @,      CMP      r4,#0x40
        0x0012e17a:    d012        ..      BEQ      0x12e1a2 ; awo_open_pll + 46
        0x0012e17c:    dc06        ..      BGT      0x12e18c ; awo_open_pll + 24
        0x0012e17e:    2c10        .,      CMP      r4,#0x10
        0x0012e180:    d009        ..      BEQ      0x12e196 ; awo_open_pll + 34
        0x0012e182:    2c20         ,      CMP      r4,#0x20
        0x0012e184:    d009        ..      BEQ      0x12e19a ; awo_open_pll + 38
        0x0012e186:    2c30        0,      CMP      r4,#0x30
        0x0012e188:    d111        ..      BNE      0x12e1ae ; awo_open_pll + 58
        0x0012e18a:    e008        ..      B        0x12e19e ; awo_open_pll + 42
        0x0012e18c:    2c50        P,      CMP      r4,#0x50
        0x0012e18e:    d00a        ..      BEQ      0x12e1a6 ; awo_open_pll + 50
        0x0012e190:    2c60        `,      CMP      r4,#0x60
        0x0012e192:    d10c        ..      BNE      0x12e1ae ; awo_open_pll + 58
        0x0012e194:    e009        ..      B        0x12e1aa ; awo_open_pll + 54
        0x0012e196:    2400        .$      MOVS     r4,#0
        0x0012e198:    e00a        ..      B        0x12e1b0 ; awo_open_pll + 60
        0x0012e19a:    2408        .$      MOVS     r4,#8
        0x0012e19c:    e008        ..      B        0x12e1b0 ; awo_open_pll + 60
        0x0012e19e:    2413        .$      MOVS     r4,#0x13
        0x0012e1a0:    e006        ..      B        0x12e1b0 ; awo_open_pll + 60
        0x0012e1a2:    2414        .$      MOVS     r4,#0x14
        0x0012e1a4:    e004        ..      B        0x12e1b0 ; awo_open_pll + 60
        0x0012e1a6:    2415        .$      MOVS     r4,#0x15
        0x0012e1a8:    e002        ..      B        0x12e1b0 ; awo_open_pll + 60
        0x0012e1aa:    2416        .$      MOVS     r4,#0x16
        0x0012e1ac:    e000        ..      B        0x12e1b0 ; awo_open_pll + 60
        0x0012e1ae:    bf00        ..      NOP      
        0x0012e1b0:    bf00        ..      NOP      
        0x0012e1b2:    f000fc65    ..e.    BL       sysc_awo_rf_reg_0_get ; 0x12ea80
        0x0012e1b6:    2101        .!      MOVS     r1,#1
        0x0012e1b8:    0449        I.      LSLS     r1,r1,#17
        0x0012e1ba:    4388        .C      BICS     r0,r0,r1
        0x0012e1bc:    4605        .F      MOV      r5,r0
        0x0012e1be:    4628        (F      MOV      r0,r5
        0x0012e1c0:    f000fc64    ..d.    BL       sysc_awo_rf_reg_0_set ; 0x12ea8c
        0x0012e1c4:    f000fc5c    ..\.    BL       sysc_awo_rf_reg_0_get ; 0x12ea80
        0x0012e1c8:    2101        .!      MOVS     r1,#1
        0x0012e1ca:    0449        I.      LSLS     r1,r1,#17
        0x0012e1cc:    4308        .C      ORRS     r0,r0,r1
        0x0012e1ce:    4605        .F      MOV      r5,r0
        0x0012e1d0:    4628        (F      MOV      r0,r5
        0x0012e1d2:    f000fc5b    ..[.    BL       sysc_awo_rf_reg_0_set ; 0x12ea8c
        0x0012e1d6:    f000fc53    ..S.    BL       sysc_awo_rf_reg_0_get ; 0x12ea80
        0x0012e1da:    2107        .!      MOVS     r1,#7
        0x0012e1dc:    0389        ..      LSLS     r1,r1,#14
        0x0012e1de:    4388        .C      BICS     r0,r0,r1
        0x0012e1e0:    2105        .!      MOVS     r1,#5
        0x0012e1e2:    0389        ..      LSLS     r1,r1,#14
        0x0012e1e4:    1845        E.      ADDS     r5,r0,r1
        0x0012e1e6:    4628        (F      MOV      r0,r5
        0x0012e1e8:    f000fc50    ..P.    BL       sysc_awo_rf_reg_0_set ; 0x12ea8c
        0x0012e1ec:    f000fc48    ..H.    BL       sysc_awo_rf_reg_0_get ; 0x12ea80
        0x0012e1f0:    2107        .!      MOVS     r1,#7
        0x0012e1f2:    02c9        ..      LSLS     r1,r1,#11
        0x0012e1f4:    4388        .C      BICS     r0,r0,r1
        0x0012e1f6:    2101        .!      MOVS     r1,#1
        0x0012e1f8:    0309        ..      LSLS     r1,r1,#12
        0x0012e1fa:    1845        E.      ADDS     r5,r0,r1
        0x0012e1fc:    4628        (F      MOV      r0,r5
        0x0012e1fe:    f000fc45    ..E.    BL       sysc_awo_rf_reg_0_set ; 0x12ea8c
        0x0012e202:    f000fc3d    ..=.    BL       sysc_awo_rf_reg_0_get ; 0x12ea80
        0x0012e206:    2107        .!      MOVS     r1,#7
        0x0012e208:    0209        ..      LSLS     r1,r1,#8
        0x0012e20a:    4388        .C      BICS     r0,r0,r1
        0x0012e20c:    2101        .!      MOVS     r1,#1
        0x0012e20e:    0289        ..      LSLS     r1,r1,#10
        0x0012e210:    1845        E.      ADDS     r5,r0,r1
        0x0012e212:    4628        (F      MOV      r0,r5
        0x0012e214:    f000fc3a    ..:.    BL       sysc_awo_rf_reg_0_set ; 0x12ea8c
        0x0012e218:    f000fc32    ..2.    BL       sysc_awo_rf_reg_0_get ; 0x12ea80
        0x0012e21c:    08c0        ..      LSRS     r0,r0,#3
        0x0012e21e:    00c0        ..      LSLS     r0,r0,#3
        0x0012e220:    1cc5        ..      ADDS     r5,r0,#3
        0x0012e222:    4628        (F      MOV      r0,r5
        0x0012e224:    f000fc32    ..2.    BL       sysc_awo_rf_reg_0_set ; 0x12ea8c
        0x0012e228:    f000fc2a    ..*.    BL       sysc_awo_rf_reg_0_get ; 0x12ea80
        0x0012e22c:    21f8        .!      MOVS     r1,#0xf8
        0x0012e22e:    4388        .C      BICS     r0,r0,r1
        0x0012e230:    00e1        ..      LSLS     r1,r4,#3
        0x0012e232:    4308        .C      ORRS     r0,r0,r1
        0x0012e234:    4606        .F      MOV      r6,r0
        0x0012e236:    f000fc29    ..).    BL       sysc_awo_rf_reg_0_set ; 0x12ea8c
        0x0012e23a:    f000fc21    ..!.    BL       sysc_awo_rf_reg_0_get ; 0x12ea80
        0x0012e23e:    2101        .!      MOVS     r1,#1
        0x0012e240:    0489        ..      LSLS     r1,r1,#18
        0x0012e242:    4308        .C      ORRS     r0,r0,r1
        0x0012e244:    4606        .F      MOV      r6,r0
        0x0012e246:    f000fc21    ..!.    BL       sysc_awo_rf_reg_0_set ; 0x12ea8c
        0x0012e24a:    bd70        p.      POP      {r4-r6,pc}
    i.awo_set_parameter
    awo_set_parameter
        0x0012e24c:    b500        ..      PUSH     {lr}
        0x0012e24e:    20c0        .       MOVS     r0,#0xc0
        0x0012e250:    f7ffff82    ....    BL       awo_ldo_setup_time ; 0x12e158
        0x0012e254:    bd00        ..      POP      {pc}
        0x0012e256:    0000        ..      MOVS     r0,r0
    i.boot_ram_entry
    boot_ram_entry
        0x0012e258:    b570        p.      PUSH     {r4-r6,lr}
        0x0012e25a:    f7fffef1    ....    BL       awo_bootram_init ; 0x12e040
        0x0012e25e:    f000fa27    ..'.    BL       peri_gate ; 0x12e6b0
        0x0012e262:    4823        #H      LDR      r0,[pc,#140] ; [0x12e2f0] = 0x12dff0
        0x0012e264:    69c0        .i      LDR      r0,[r0,#0x1c]
        0x0012e266:    2801        .(      CMP      r0,#1
        0x0012e268:    d017        ..      BEQ      0x12e29a ; boot_ram_entry + 66
        0x0012e26a:    4821        !H      LDR      r0,[pc,#132] ; [0x12e2f0] = 0x12dff0
        0x0012e26c:    6980        .i      LDR      r0,[r0,#0x18]
        0x0012e26e:    2800        .(      CMP      r0,#0
        0x0012e270:    d007        ..      BEQ      0x12e282 ; boot_ram_entry + 42
        0x0012e272:    200f        .       MOVS     r0,#0xf
        0x0012e274:    f000fc16    ....    BL       sysc_cpu_qspi_en_setf ; 0x12eaa4
        0x0012e278:    491d        .I      LDR      r1,[pc,#116] ; [0x12e2f0] = 0x12dff0
        0x0012e27a:    481e        .H      LDR      r0,[pc,#120] ; [0x12e2f4] = 0x12e5d9
        0x0012e27c:    f000fa02    ....    BL       image_read ; 0x12e684
        0x0012e280:    e006        ..      B        0x12e290 ; boot_ram_entry + 56
        0x0012e282:    2003        .       MOVS     r0,#3
        0x0012e284:    f000fc0e    ....    BL       sysc_cpu_qspi_en_setf ; 0x12eaa4
        0x0012e288:    4919        .I      LDR      r1,[pc,#100] ; [0x12e2f0] = 0x12dff0
        0x0012e28a:    481b        .H      LDR      r0,[pc,#108] ; [0x12e2f8] = 0x12e631
        0x0012e28c:    f000f9fa    ....    BL       image_read ; 0x12e684
        0x0012e290:    2401        .$      MOVS     r4,#1
        0x0012e292:    0524        $.      LSLS     r4,r4,#20
        0x0012e294:    f000f8b2    ....    BL       dmac_qspi_gate ; 0x12e3fc
        0x0012e298:    e016        ..      B        0x12e2c8 ; boot_ram_entry + 112
        0x0012e29a:    20ff        .       MOVS     r0,#0xff
        0x0012e29c:    3001        .0      ADDS     r0,#1
        0x0012e29e:    f000fbfb    ....    BL       sysc_cpu_clkg1_set ; 0x12ea98
        0x0012e2a2:    200f        .       MOVS     r0,#0xf
        0x0012e2a4:    f000fbfe    ....    BL       sysc_cpu_qspi_en_setf ; 0x12eaa4
        0x0012e2a8:    4911        .I      LDR      r1,[pc,#68] ; [0x12e2f0] = 0x12dff0
        0x0012e2aa:    6a09        .j      LDR      r1,[r1,#0x20]
        0x0012e2ac:    2900        .)      CMP      r1,#0
        0x0012e2ae:    d002        ..      BEQ      0x12e2b6 ; boot_ram_entry + 94
        0x0012e2b0:    2101        .!      MOVS     r1,#1
        0x0012e2b2:    04c9        ..      LSLS     r1,r1,#19
        0x0012e2b4:    e000        ..      B        0x12e2b8 ; boot_ram_entry + 96
        0x0012e2b6:    2100        .!      MOVS     r1,#0
        0x0012e2b8:    4608        .F      MOV      r0,r1
        0x0012e2ba:    f000f905    ....    BL       flash_cache_init ; 0x12e4c8
        0x0012e2be:    480c        .H      LDR      r0,[pc,#48] ; [0x12e2f0] = 0x12dff0
        0x0012e2c0:    6900        .i      LDR      r0,[r0,#0x10]
        0x0012e2c2:    2101        .!      MOVS     r1,#1
        0x0012e2c4:    05c9        ..      LSLS     r1,r1,#23
        0x0012e2c6:    1844        D.      ADDS     r4,r0,r1
        0x0012e2c8:    6820         h      LDR      r0,[r4,#0]
        0x0012e2ca:    f3808808    ....    MSR      MSP,r0
        0x0012e2ce:    bf00        ..      NOP      
        0x0012e2d0:    1d25        %.      ADDS     r5,r4,#4
        0x0012e2d2:    4a07        .J      LDR      r2,[pc,#28] ; [0x12e2f0] = 0x12dff0
        0x0012e2d4:    6911        .i      LDR      r1,[r2,#0x10]
        0x0012e2d6:    6a12        .j      LDR      r2,[r2,#0x20]
        0x0012e2d8:    2a00        .*      CMP      r2,#0
        0x0012e2da:    d001        ..      BEQ      0x12e2e0 ; boot_ram_entry + 136
        0x0012e2dc:    2200        ."      MOVS     r2,#0
        0x0012e2de:    e001        ..      B        0x12e2e4 ; boot_ram_entry + 140
        0x0012e2e0:    2201        ."      MOVS     r2,#1
        0x0012e2e2:    04d2        ..      LSLS     r2,r2,#19
        0x0012e2e4:    4610        .F      MOV      r0,r2
        0x0012e2e6:    4b05        .K      LDR      r3,[pc,#20] ; [0x12e2fc] = 0x3399
        0x0012e2e8:    4a05        .J      LDR      r2,[pc,#20] ; [0x12e300] = 0xad0
        0x0012e2ea:    682e        .h      LDR      r6,[r5,#0]
        0x0012e2ec:    47b0        .G      BLX      r6
        0x0012e2ee:    bd70        p.      POP      {r4-r6,pc}
    $d
        0x0012e2f0:    0012dff0    ....    DCD    1236976
        0x0012e2f4:    0012e5d9    ....    DCD    1238489
        0x0012e2f8:    0012e631    1...    DCD    1238577
        0x0012e2fc:    00003399    .3..    DCD    13209
        0x0012e300:    00000ad0    ....    DCD    2768
    $t
    i.cache_reg_cache_en_set
    cache_reg_cache_en_set
        0x0012e304:    4901        .I      LDR      r1,[pc,#4] ; [0x12e30c] = 0x20121000
        0x0012e306:    6008        .`      STR      r0,[r1,#0]
        0x0012e308:    4770        pG      BX       lr
    $d
        0x0012e30a:    0000        ..      DCW    0
        0x0012e30c:    20121000    ...     DCD    538054656
    $t
    i.cache_reg_flush_en_set
    cache_reg_flush_en_set
        0x0012e310:    4901        .I      LDR      r1,[pc,#4] ; [0x12e318] = 0x20121000
        0x0012e312:    61c8        .a      STR      r0,[r1,#0x1c]
        0x0012e314:    4770        pG      BX       lr
    $d
        0x0012e316:    0000        ..      DCW    0
        0x0012e318:    20121000    ...     DCD    538054656
    $t
    i.clk_gate_cpu_g1
    clk_gate_cpu_g1
        0x0012e31c:    bf00        ..      NOP      
        0x0012e31e:    490f        .I      LDR      r1,[pc,#60] ; [0x12e35c] = 0x20132000
        0x0012e320:    6148        Ha      STR      r0,[r1,#0x14]
        0x0012e322:    bf00        ..      NOP      
        0x0012e324:    490e        .I      LDR      r1,[pc,#56] ; [0x12e360] = 0xaaaaaaaa
        0x0012e326:    4001        .@      ANDS     r1,r1,r0
        0x0012e328:    2900        .)      CMP      r1,#0
        0x0012e32a:    d007        ..      BEQ      0x12e33c ; clk_gate_cpu_g1 + 32
        0x0012e32c:    bf00        ..      NOP      
        0x0012e32e:    bf00        ..      NOP      
        0x0012e330:    490a        .I      LDR      r1,[pc,#40] ; [0x12e35c] = 0x20132000
        0x0012e332:    6949        Ii      LDR      r1,[r1,#0x14]
        0x0012e334:    4001        .@      ANDS     r1,r1,r0
        0x0012e336:    2900        .)      CMP      r1,#0
        0x0012e338:    d1f9        ..      BNE      0x12e32e ; clk_gate_cpu_g1 + 18
        0x0012e33a:    e00e        ..      B        0x12e35a ; clk_gate_cpu_g1 + 62
        0x0012e33c:    4908        .I      LDR      r1,[pc,#32] ; [0x12e360] = 0xaaaaaaaa
        0x0012e33e:    43c9        .C      MVNS     r1,r1
        0x0012e340:    4001        .@      ANDS     r1,r1,r0
        0x0012e342:    2900        .)      CMP      r1,#0
        0x0012e344:    d008        ..      BEQ      0x12e358 ; clk_gate_cpu_g1 + 60
        0x0012e346:    bf00        ..      NOP      
        0x0012e348:    bf00        ..      NOP      
        0x0012e34a:    4904        .I      LDR      r1,[pc,#16] ; [0x12e35c] = 0x20132000
        0x0012e34c:    6949        Ii      LDR      r1,[r1,#0x14]
        0x0012e34e:    4602        .F      MOV      r2,r0
        0x0012e350:    438a        .C      BICS     r2,r2,r1
        0x0012e352:    2a00        .*      CMP      r2,#0
        0x0012e354:    d1f8        ..      BNE      0x12e348 ; clk_gate_cpu_g1 + 44
        0x0012e356:    e000        ..      B        0x12e35a ; clk_gate_cpu_g1 + 62
        0x0012e358:    bf00        ..      NOP      
        0x0012e35a:    4770        pG      BX       lr
    $d
        0x0012e35c:    20132000    . .     DCD    538124288
        0x0012e360:    aaaaaaaa    ....    DCD    2863311530
    $t
    i.clk_gate_dmac_clr
    clk_gate_dmac_clr
        0x0012e364:    b500        ..      PUSH     {lr}
        0x0012e366:    bf00        ..      NOP      
        0x0012e368:    4803        .H      LDR      r0,[pc,#12] ; [0x12e378] = 0x20120380
        0x0012e36a:    6a00        .j      LDR      r0,[r0,#0x20]
        0x0012e36c:    2800        .(      CMP      r0,#0
        0x0012e36e:    d102        ..      BNE      0x12e376 ; clk_gate_dmac_clr + 18
        0x0012e370:    2080        .       MOVS     r0,#0x80
        0x0012e372:    f7ffffd3    ....    BL       clk_gate_cpu_g1 ; 0x12e31c
        0x0012e376:    bd00        ..      POP      {pc}
    $d
        0x0012e378:    20120380    ...     DCD    538051456
    $t
    i.clk_gate_dmac_set
    clk_gate_dmac_set
        0x0012e37c:    b500        ..      PUSH     {lr}
        0x0012e37e:    2040        @       MOVS     r0,#0x40
        0x0012e380:    f7ffffcc    ....    BL       clk_gate_cpu_g1 ; 0x12e31c
        0x0012e384:    bd00        ..      POP      {pc}
        0x0012e386:    0000        ..      MOVS     r0,r0
    i.dmac_ch0_ctrl_h_pack
    dmac_ch0_ctrl_h_pack
        0x0012e388:    0302        ..      LSLS     r2,r0,#12
        0x0012e38a:    430a        .C      ORRS     r2,r2,r1
        0x0012e38c:    4b01        .K      LDR      r3,[pc,#4] ; [0x12e394] = 0x20120000
        0x0012e38e:    61da        .a      STR      r2,[r3,#0x1c]
        0x0012e390:    4770        pG      BX       lr
    $d
        0x0012e392:    0000        ..      DCW    0
        0x0012e394:    20120000    ...     DCD    538050560
    $t
    i.dmac_ch0_ctrl_l_pack
    dmac_ch0_ctrl_l_pack
        0x0012e398:    b5f0        ..      PUSH     {r4-r7,lr}
        0x0012e39a:    9d06        ..      LDR      r5,[sp,#0x18]
        0x0012e39c:    9c05        ..      LDR      r4,[sp,#0x14]
        0x0012e39e:    0506        ..      LSLS     r6,r0,#20
        0x0012e3a0:    038f        ..      LSLS     r7,r1,#14
        0x0012e3a2:    433e        >C      ORRS     r6,r6,r7
        0x0012e3a4:    02d7        ..      LSLS     r7,r2,#11
        0x0012e3a6:    433e        >C      ORRS     r6,r6,r7
        0x0012e3a8:    025f        _.      LSLS     r7,r3,#9
        0x0012e3aa:    433e        >C      ORRS     r6,r6,r7
        0x0012e3ac:    01e7        ..      LSLS     r7,r4,#7
        0x0012e3ae:    433e        >C      ORRS     r6,r6,r7
        0x0012e3b0:    012f        /.      LSLS     r7,r5,#4
        0x0012e3b2:    433e        >C      ORRS     r6,r6,r7
        0x0012e3b4:    9f07        ..      LDR      r7,[sp,#0x1c]
        0x0012e3b6:    007f        ..      LSLS     r7,r7,#1
        0x0012e3b8:    433e        >C      ORRS     r6,r6,r7
        0x0012e3ba:    9f08        ..      LDR      r7,[sp,#0x20]
        0x0012e3bc:    433e        >C      ORRS     r6,r6,r7
        0x0012e3be:    4f01        .O      LDR      r7,[pc,#4] ; [0x12e3c4] = 0x20120000
        0x0012e3c0:    61be        .a      STR      r6,[r7,#0x18]
        0x0012e3c2:    bdf0        ..      POP      {r4-r7,pc}
    $d
        0x0012e3c4:    20120000    ...     DCD    538050560
    $t
    i.dmac_ch0_dar_l_set
    dmac_ch0_dar_l_set
        0x0012e3c8:    4901        .I      LDR      r1,[pc,#4] ; [0x12e3d0] = 0x20120000
        0x0012e3ca:    6088        .`      STR      r0,[r1,#8]
        0x0012e3cc:    4770        pG      BX       lr
    $d
        0x0012e3ce:    0000        ..      DCW    0
        0x0012e3d0:    20120000    ...     DCD    538050560
    $t
    i.dmac_ch0_sar_l_set
    dmac_ch0_sar_l_set
        0x0012e3d4:    4901        .I      LDR      r1,[pc,#4] ; [0x12e3dc] = 0x20120000
        0x0012e3d6:    6008        .`      STR      r0,[r1,#0]
        0x0012e3d8:    4770        pG      BX       lr
    $d
        0x0012e3da:    0000        ..      DCW    0
        0x0012e3dc:    20120000    ...     DCD    538050560
    $t
    i.dmac_chenreg_l_pack
    dmac_chenreg_l_pack
        0x0012e3e0:    0202        ..      LSLS     r2,r0,#8
        0x0012e3e2:    430a        .C      ORRS     r2,r2,r1
        0x0012e3e4:    4b01        .K      LDR      r3,[pc,#4] ; [0x12e3ec] = 0x20120380
        0x0012e3e6:    621a        .b      STR      r2,[r3,#0x20]
        0x0012e3e8:    4770        pG      BX       lr
    $d
        0x0012e3ea:    0000        ..      DCW    0
        0x0012e3ec:    20120380    ...     DCD    538051456
    $t
    i.dmac_clearblock_l_set
    dmac_clearblock_l_set
        0x0012e3f0:    4901        .I      LDR      r1,[pc,#4] ; [0x12e3f8] = 0x20120340
        0x0012e3f2:    6008        .`      STR      r0,[r1,#0]
        0x0012e3f4:    4770        pG      BX       lr
    $d
        0x0012e3f6:    0000        ..      DCW    0
        0x0012e3f8:    20120340    @..     DCD    538051392
    $t
    i.dmac_qspi_gate
    dmac_qspi_gate
        0x0012e3fc:    b510        ..      PUSH     {r4,lr}
        0x0012e3fe:    2011        .       MOVS     r0,#0x11
        0x0012e400:    01c0        ..      LSLS     r0,r0,#7
        0x0012e402:    f000fb49    ..I.    BL       sysc_cpu_clkg1_set ; 0x12ea98
        0x0012e406:    bd10        ..      POP      {r4,pc}
    i.dmac_transfer_QSPI_RX
    dmac_transfer_QSPI_RX
        0x0012e408:    b57f        ..      PUSH     {r0-r6,lr}
        0x0012e40a:    4606        .F      MOV      r6,r0
        0x0012e40c:    460c        .F      MOV      r4,r1
        0x0012e40e:    4615        .F      MOV      r5,r2
        0x0012e410:    f7ffffb4    ....    BL       clk_gate_dmac_set ; 0x12e37c
        0x0012e414:    4630        0F      MOV      r0,r6
        0x0012e416:    f7ffffdd    ....    BL       dmac_ch0_sar_l_set ; 0x12e3d4
        0x0012e41a:    4620         F      MOV      r0,r4
        0x0012e41c:    f7ffffd4    ....    BL       dmac_ch0_dar_l_set ; 0x12e3c8
        0x0012e420:    2000        .       MOVS     r0,#0
        0x0012e422:    9000        ..      STR      r0,[sp,#0]
        0x0012e424:    9001        ..      STR      r0,[sp,#4]
        0x0012e426:    9002        ..      STR      r0,[sp,#8]
        0x0012e428:    2302        .#      MOVS     r3,#2
        0x0012e42a:    2204        ."      MOVS     r2,#4
        0x0012e42c:    4611        .F      MOV      r1,r2
        0x0012e42e:    9003        ..      STR      r0,[sp,#0xc]
        0x0012e430:    4618        .F      MOV      r0,r3
        0x0012e432:    f7ffffb1    ....    BL       dmac_ch0_ctrl_l_pack ; 0x12e398
        0x0012e436:    b2a9        ..      UXTH     r1,r5
        0x0012e438:    2000        .       MOVS     r0,#0
        0x0012e43a:    f7ffffa5    ....    BL       dmac_ch0_ctrl_h_pack ; 0x12e388
        0x0012e43e:    2101        .!      MOVS     r1,#1
        0x0012e440:    4608        .F      MOV      r0,r1
        0x0012e442:    f7ffffcd    ....    BL       dmac_chenreg_l_pack ; 0x12e3e0
        0x0012e446:    bf00        ..      NOP      
        0x0012e448:    bf00        ..      NOP      
        0x0012e44a:    4806        .H      LDR      r0,[pc,#24] ; [0x12e464] = 0x201202c0
        0x0012e44c:    6880        .h      LDR      r0,[r0,#8]
        0x0012e44e:    07c0        ..      LSLS     r0,r0,#31
        0x0012e450:    0fc0        ..      LSRS     r0,r0,#31
        0x0012e452:    2800        .(      CMP      r0,#0
        0x0012e454:    d0f8        ..      BEQ      0x12e448 ; dmac_transfer_QSPI_RX + 64
        0x0012e456:    2001        .       MOVS     r0,#1
        0x0012e458:    f7ffffca    ....    BL       dmac_clearblock_l_set ; 0x12e3f0
        0x0012e45c:    f7ffff82    ....    BL       clk_gate_dmac_clr ; 0x12e364
        0x0012e460:    bd7f        ..      POP      {r0-r6,pc}
    $d
        0x0012e462:    0000        ..      DCW    0
        0x0012e464:    201202c0    ...     DCD    538051264
    $t
    i.dmac_transfer_QSPI_RX_32Bit
    dmac_transfer_QSPI_RX_32Bit
        0x0012e468:    b57f        ..      PUSH     {r0-r6,lr}
        0x0012e46a:    4606        .F      MOV      r6,r0
        0x0012e46c:    460c        .F      MOV      r4,r1
        0x0012e46e:    4615        .F      MOV      r5,r2
        0x0012e470:    f7ffff84    ....    BL       clk_gate_dmac_set ; 0x12e37c
        0x0012e474:    4630        0F      MOV      r0,r6
        0x0012e476:    f7ffffad    ....    BL       dmac_ch0_sar_l_set ; 0x12e3d4
        0x0012e47a:    4620         F      MOV      r0,r4
        0x0012e47c:    f7ffffa4    ....    BL       dmac_ch0_dar_l_set ; 0x12e3c8
        0x0012e480:    2000        .       MOVS     r0,#0
        0x0012e482:    2102        .!      MOVS     r1,#2
        0x0012e484:    9101        ..      STR      r1,[sp,#4]
        0x0012e486:    9000        ..      STR      r0,[sp,#0]
        0x0012e488:    460b        .F      MOV      r3,r1
        0x0012e48a:    2204        ."      MOVS     r2,#4
        0x0012e48c:    9102        ..      STR      r1,[sp,#8]
        0x0012e48e:    9003        ..      STR      r0,[sp,#0xc]
        0x0012e490:    4611        .F      MOV      r1,r2
        0x0012e492:    2002        .       MOVS     r0,#2
        0x0012e494:    f7ffff80    ....    BL       dmac_ch0_ctrl_l_pack ; 0x12e398
        0x0012e498:    b2a9        ..      UXTH     r1,r5
        0x0012e49a:    2000        .       MOVS     r0,#0
        0x0012e49c:    f7ffff74    ..t.    BL       dmac_ch0_ctrl_h_pack ; 0x12e388
        0x0012e4a0:    2101        .!      MOVS     r1,#1
        0x0012e4a2:    4608        .F      MOV      r0,r1
        0x0012e4a4:    f7ffff9c    ....    BL       dmac_chenreg_l_pack ; 0x12e3e0
        0x0012e4a8:    bf00        ..      NOP      
        0x0012e4aa:    bf00        ..      NOP      
        0x0012e4ac:    4805        .H      LDR      r0,[pc,#20] ; [0x12e4c4] = 0x201202c0
        0x0012e4ae:    6880        .h      LDR      r0,[r0,#8]
        0x0012e4b0:    07c0        ..      LSLS     r0,r0,#31
        0x0012e4b2:    0fc0        ..      LSRS     r0,r0,#31
        0x0012e4b4:    2800        .(      CMP      r0,#0
        0x0012e4b6:    d0f8        ..      BEQ      0x12e4aa ; dmac_transfer_QSPI_RX_32Bit + 66
        0x0012e4b8:    2001        .       MOVS     r0,#1
        0x0012e4ba:    f7ffff99    ....    BL       dmac_clearblock_l_set ; 0x12e3f0
        0x0012e4be:    f7ffff51    ..Q.    BL       clk_gate_dmac_clr ; 0x12e364
        0x0012e4c2:    bd7f        ..      POP      {r0-r6,pc}
    $d
        0x0012e4c4:    201202c0    ...     DCD    538051264
    $t
    i.flash_cache_init
    flash_cache_init
        0x0012e4c8:    b5f0        ..      PUSH     {r4-r7,lr}
        0x0012e4ca:    b085        ..      SUB      sp,sp,#0x14
        0x0012e4cc:    4604        .F      MOV      r4,r0
        0x0012e4ce:    2001        .       MOVS     r0,#1
        0x0012e4d0:    0280        ..      LSLS     r0,r0,#10
        0x0012e4d2:    f7ffff23    ..#.    BL       clk_gate_cpu_g1 ; 0x12e31c
        0x0012e4d6:    2000        .       MOVS     r0,#0
        0x0012e4d8:    f000fa94    ....    BL       qspi_ssi_en_setf ; 0x12ea04
        0x0012e4dc:    2002        .       MOVS     r0,#2
        0x0012e4de:    493b        ;I      LDR      r1,[pc,#236] ; [0x12e5cc] = 0x20300000
        0x0012e4e0:    6949        Ii      LDR      r1,[r1,#0x14]
        0x0012e4e2:    0c09        ..      LSRS     r1,r1,#16
        0x0012e4e4:    0409        ..      LSLS     r1,r1,#16
        0x0012e4e6:    4301        .C      ORRS     r1,r1,r0
        0x0012e4e8:    4a38        8J      LDR      r2,[pc,#224] ; [0x12e5cc] = 0x20300000
        0x0012e4ea:    6151        Qa      STR      r1,[r2,#0x14]
        0x0012e4ec:    bf00        ..      NOP      
        0x0012e4ee:    211f        .!      MOVS     r1,#0x1f
        0x0012e4f0:    2200        ."      MOVS     r2,#0
        0x0012e4f2:    4613        .F      MOV      r3,r2
        0x0012e4f4:    4615        .F      MOV      r5,r2
        0x0012e4f6:    9201        ..      STR      r2,[sp,#4]
        0x0012e4f8:    9202        ..      STR      r2,[sp,#8]
        0x0012e4fa:    9203        ..      STR      r2,[sp,#0xc]
        0x0012e4fc:    9000        ..      STR      r0,[sp,#0]
        0x0012e4fe:    0546        F.      LSLS     r6,r0,#21
        0x0012e500:    040f        ..      LSLS     r7,r1,#16
        0x0012e502:    433e        >C      ORRS     r6,r6,r7
        0x0012e504:    0317        ..      LSLS     r7,r2,#12
        0x0012e506:    433e        >C      ORRS     r6,r6,r7
        0x0012e508:    02df        ..      LSLS     r7,r3,#11
        0x0012e50a:    433e        >C      ORRS     r6,r6,r7
        0x0012e50c:    02af        ..      LSLS     r7,r5,#10
        0x0012e50e:    433e        >C      ORRS     r6,r6,r7
        0x0012e510:    9f00        ..      LDR      r7,[sp,#0]
        0x0012e512:    023f        ?.      LSLS     r7,r7,#8
        0x0012e514:    433e        >C      ORRS     r6,r6,r7
        0x0012e516:    9f01        ..      LDR      r7,[sp,#4]
        0x0012e518:    01ff        ..      LSLS     r7,r7,#7
        0x0012e51a:    433e        >C      ORRS     r6,r6,r7
        0x0012e51c:    9f02        ..      LDR      r7,[sp,#8]
        0x0012e51e:    01bf        ..      LSLS     r7,r7,#6
        0x0012e520:    433e        >C      ORRS     r6,r6,r7
        0x0012e522:    9f03        ..      LDR      r7,[sp,#0xc]
        0x0012e524:    013f        ?.      LSLS     r7,r7,#4
        0x0012e526:    433e        >C      ORRS     r6,r6,r7
        0x0012e528:    4f28        (O      LDR      r7,[pc,#160] ; [0x12e5cc] = 0x20300000
        0x0012e52a:    603e        >`      STR      r6,[r7,#0]
        0x0012e52c:    bf00        ..      NOP      
        0x0012e52e:    2007        .       MOVS     r0,#7
        0x0012e530:    4639        9F      MOV      r1,r7
        0x0012e532:    6048        H`      STR      r0,[r1,#4]
        0x0012e534:    bf00        ..      NOP      
        0x0012e536:    2008        .       MOVS     r0,#8
        0x0012e538:    2102        .!      MOVS     r1,#2
        0x0012e53a:    2206        ."      MOVS     r2,#6
        0x0012e53c:    2300        .#      MOVS     r3,#0
        0x0012e53e:    02c5        ..      LSLS     r5,r0,#11
        0x0012e540:    020e        ..      LSLS     r6,r1,#8
        0x0012e542:    4335        5C      ORRS     r5,r5,r6
        0x0012e544:    0096        ..      LSLS     r6,r2,#2
        0x0012e546:    4335        5C      ORRS     r5,r5,r6
        0x0012e548:    431d        .C      ORRS     r5,r5,r3
        0x0012e54a:    4e20         N      LDR      r6,[pc,#128] ; [0x12e5cc] = 0x20300000
        0x0012e54c:    36c0        .6      ADDS     r6,r6,#0xc0
        0x0012e54e:    6375        uc      STR      r5,[r6,#0x34]
        0x0012e550:    bf00        ..      NOP      
        0x0012e552:    2000        .       MOVS     r0,#0
        0x0012e554:    4639        9F      MOV      r1,r7
        0x0012e556:    62c8        .b      STR      r0,[r1,#0x2c]
        0x0012e558:    bf00        ..      NOP      
        0x0012e55a:    2001        .       MOVS     r0,#1
        0x0012e55c:    6108        .a      STR      r0,[r1,#0x10]
        0x0012e55e:    bf00        ..      NOP      
        0x0012e560:    f000fa50    ..P.    BL       qspi_ssi_en_setf ; 0x12ea04
        0x0012e564:    bf00        ..      NOP      
        0x0012e566:    481a        .H      LDR      r0,[pc,#104] ; [0x12e5d0] = 0x20121000
        0x0012e568:    6044        D`      STR      r4,[r0,#4]
        0x0012e56a:    bf00        ..      NOP      
        0x0012e56c:    4817        .H      LDR      r0,[pc,#92] ; [0x12e5cc] = 0x20300000
        0x0012e56e:    3060        `0      ADDS     r0,r0,#0x60
        0x0012e570:    4917        .I      LDR      r1,[pc,#92] ; [0x12e5d0] = 0x20121000
        0x0012e572:    6088        .`      STR      r0,[r1,#8]
        0x0012e574:    bf00        ..      NOP      
        0x0012e576:    2027        '       MOVS     r0,#0x27
        0x0012e578:    01c0        ..      LSLS     r0,r0,#7
        0x0012e57a:    2100        .!      MOVS     r1,#0
        0x0012e57c:    460a        .F      MOV      r2,r1
        0x0012e57e:    460b        .F      MOV      r3,r1
        0x0012e580:    256b        k%      MOVS     r5,#0x6b
        0x0012e582:    0406        ..      LSLS     r6,r0,#16
        0x0012e584:    028f        ..      LSLS     r7,r1,#10
        0x0012e586:    433e        >C      ORRS     r6,r6,r7
        0x0012e588:    0257        W.      LSLS     r7,r2,#9
        0x0012e58a:    433e        >C      ORRS     r6,r6,r7
        0x0012e58c:    021f        ..      LSLS     r7,r3,#8
        0x0012e58e:    433e        >C      ORRS     r6,r6,r7
        0x0012e590:    432e        .C      ORRS     r6,r6,r5
        0x0012e592:    4f0f        .O      LDR      r7,[pc,#60] ; [0x12e5d0] = 0x20121000
        0x0012e594:    60fe        .`      STR      r6,[r7,#0xc]
        0x0012e596:    bf00        ..      NOP      
        0x0012e598:    2001        .       MOVS     r0,#1
        0x0012e59a:    f7fffeb3    ....    BL       cache_reg_cache_en_set ; 0x12e304
        0x0012e59e:    2001        .       MOVS     r0,#1
        0x0012e5a0:    4639        9F      MOV      r1,r7
        0x0012e5a2:    6188        .a      STR      r0,[r1,#0x18]
        0x0012e5a4:    bf00        ..      NOP      
        0x0012e5a6:    f7fffeb3    ....    BL       cache_reg_flush_en_set ; 0x12e310
        0x0012e5aa:    2001        .       MOVS     r0,#1
        0x0012e5ac:    4909        .I      LDR      r1,[pc,#36] ; [0x12e5d4] = 0x20132040
        0x0012e5ae:    6809        .h      LDR      r1,[r1,#0]
        0x0012e5b0:    4381        .C      BICS     r1,r1,r0
        0x0012e5b2:    4301        .C      ORRS     r1,r1,r0
        0x0012e5b4:    4a07        .J      LDR      r2,[pc,#28] ; [0x12e5d4] = 0x20132040
        0x0012e5b6:    6011        .`      STR      r1,[r2,#0]
        0x0012e5b8:    bf00        ..      NOP      
        0x0012e5ba:    bf00        ..      NOP      
        0x0012e5bc:    bf00        ..      NOP      
        0x0012e5be:    4804        .H      LDR      r0,[pc,#16] ; [0x12e5d0] = 0x20121000
        0x0012e5c0:    69c0        .i      LDR      r0,[r0,#0x1c]
        0x0012e5c2:    2800        .(      CMP      r0,#0
        0x0012e5c4:    d1fa        ..      BNE      0x12e5bc ; flash_cache_init + 244
        0x0012e5c6:    b005        ..      ADD      sp,sp,#0x14
        0x0012e5c8:    bdf0        ..      POP      {r4-r7,pc}
    $d
        0x0012e5ca:    0000        ..      DCW    0
        0x0012e5cc:    20300000    ..0     DCD    540016640
        0x0012e5d0:    20121000    ...     DCD    538054656
        0x0012e5d4:    20132040    @ .     DCD    538124352
    $t
    i.flash_quad_read
    flash_quad_read
        0x0012e5d8:    b5fe        ..      PUSH     {r1-r7,lr}
        0x0012e5da:    4604        .F      MOV      r4,r0
        0x0012e5dc:    460d        .F      MOV      r5,r1
        0x0012e5de:    4616        .F      MOV      r6,r2
        0x0012e5e0:    08af        ..      LSRS     r7,r5,#2
        0x0012e5e2:    07a8        ..      LSLS     r0,r5,#30
        0x0012e5e4:    0f80        ..      LSRS     r0,r0,#30
        0x0012e5e6:    9001        ..      STR      r0,[sp,#4]
        0x0012e5e8:    2008        .       MOVS     r0,#8
        0x0012e5ea:    4623        #F      MOV      r3,r4
        0x0012e5ec:    226b        k"      MOVS     r2,#0x6b
        0x0012e5ee:    4639        9F      MOV      r1,r7
        0x0012e5f0:    9000        ..      STR      r0,[sp,#0]
        0x0012e5f2:    4630        0F      MOV      r0,r6
        0x0012e5f4:    f000f8ac    ....    BL       qspi_flash_quad_read_data ; 0x12e750
        0x0012e5f8:    00b8        ..      LSLS     r0,r7,#2
        0x0012e5fa:    1836        6.      ADDS     r6,r6,r0
        0x0012e5fc:    00b8        ..      LSLS     r0,r7,#2
        0x0012e5fe:    1904        ..      ADDS     r4,r0,r4
        0x0012e600:    9801        ..      LDR      r0,[sp,#4]
        0x0012e602:    2800        .(      CMP      r0,#0
        0x0012e604:    d012        ..      BEQ      0x12e62c ; flash_quad_read + 84
        0x0012e606:    2103        .!      MOVS     r1,#3
        0x0012e608:    4668        hF      MOV      r0,sp
        0x0012e60a:    7001        .p      STRB     r1,[r0,#0]
        0x0012e60c:    0220         .      LSLS     r0,r4,#8
        0x0012e60e:    0e01        ..      LSRS     r1,r0,#24
        0x0012e610:    4668        hF      MOV      r0,sp
        0x0012e612:    7041        Ap      STRB     r1,[r0,#1]
        0x0012e614:    0420         .      LSLS     r0,r4,#16
        0x0012e616:    0e01        ..      LSRS     r1,r0,#24
        0x0012e618:    4668        hF      MOV      r0,sp
        0x0012e61a:    7081        .p      STRB     r1,[r0,#2]
        0x0012e61c:    70c4        .p      STRB     r4,[r0,#3]
        0x0012e61e:    2304        .#      MOVS     r3,#4
        0x0012e620:    466a        jF      MOV      r2,sp
        0x0012e622:    4630        0F      MOV      r0,r6
        0x0012e624:    9901        ..      LDR      r1,[sp,#4]
        0x0012e626:    f000f973    ..s.    BL       qspi_read ; 0x12e910
        0x0012e62a:    bf00        ..      NOP      
        0x0012e62c:    2000        .       MOVS     r0,#0
        0x0012e62e:    bdfe        ..      POP      {r1-r7,pc}
    i.flash_read
    flash_read
        0x0012e630:    b5fe        ..      PUSH     {r1-r7,lr}
        0x0012e632:    4604        .F      MOV      r4,r0
        0x0012e634:    460d        .F      MOV      r5,r1
        0x0012e636:    4616        .F      MOV      r6,r2
        0x0012e638:    08af        ..      LSRS     r7,r5,#2
        0x0012e63a:    07a8        ..      LSLS     r0,r5,#30
        0x0012e63c:    0f80        ..      LSRS     r0,r0,#30
        0x0012e63e:    9001        ..      STR      r0,[sp,#4]
        0x0012e640:    4623        #F      MOV      r3,r4
        0x0012e642:    2203        ."      MOVS     r2,#3
        0x0012e644:    4639        9F      MOV      r1,r7
        0x0012e646:    4630        0F      MOV      r0,r6
        0x0012e648:    f000f8f8    ....    BL       qspi_flash_read_data ; 0x12e83c
        0x0012e64c:    00b8        ..      LSLS     r0,r7,#2
        0x0012e64e:    1836        6.      ADDS     r6,r6,r0
        0x0012e650:    00b8        ..      LSLS     r0,r7,#2
        0x0012e652:    1904        ..      ADDS     r4,r0,r4
        0x0012e654:    9801        ..      LDR      r0,[sp,#4]
        0x0012e656:    2800        .(      CMP      r0,#0
        0x0012e658:    d012        ..      BEQ      0x12e680 ; flash_read + 80
        0x0012e65a:    2103        .!      MOVS     r1,#3
        0x0012e65c:    4668        hF      MOV      r0,sp
        0x0012e65e:    7001        .p      STRB     r1,[r0,#0]
        0x0012e660:    0220         .      LSLS     r0,r4,#8
        0x0012e662:    0e01        ..      LSRS     r1,r0,#24
        0x0012e664:    4668        hF      MOV      r0,sp
        0x0012e666:    7041        Ap      STRB     r1,[r0,#1]
        0x0012e668:    0420         .      LSLS     r0,r4,#16
        0x0012e66a:    0e01        ..      LSRS     r1,r0,#24
        0x0012e66c:    4668        hF      MOV      r0,sp
        0x0012e66e:    7081        .p      STRB     r1,[r0,#2]
        0x0012e670:    70c4        .p      STRB     r4,[r0,#3]
        0x0012e672:    2304        .#      MOVS     r3,#4
        0x0012e674:    466a        jF      MOV      r2,sp
        0x0012e676:    4630        0F      MOV      r0,r6
        0x0012e678:    9901        ..      LDR      r1,[sp,#4]
        0x0012e67a:    f000f949    ..I.    BL       qspi_read ; 0x12e910
        0x0012e67e:    bf00        ..      NOP      
        0x0012e680:    2000        .       MOVS     r0,#0
        0x0012e682:    bdfe        ..      POP      {r1-r7,pc}
    i.image_read
    image_read
        0x0012e684:    b5f8        ..      PUSH     {r3-r7,lr}
        0x0012e686:    4605        .F      MOV      r5,r0
        0x0012e688:    460c        .F      MOV      r4,r1
        0x0012e68a:    6a20         j      LDR      r0,[r4,#0x20]
        0x0012e68c:    2800        .(      CMP      r0,#0
        0x0012e68e:    d002        ..      BEQ      0x12e696 ; image_read + 18
        0x0012e690:    2001        .       MOVS     r0,#1
        0x0012e692:    04c0        ..      LSLS     r0,r0,#19
        0x0012e694:    e000        ..      B        0x12e698 ; image_read + 20
        0x0012e696:    2000        .       MOVS     r0,#0
        0x0012e698:    9000        ..      STR      r0,[sp,#0]
        0x0012e69a:    6921        !i      LDR      r1,[r4,#0x10]
        0x0012e69c:    9800        ..      LDR      r0,[sp,#0]
        0x0012e69e:    180e        ..      ADDS     r6,r1,r0
        0x0012e6a0:    2701        .'      MOVS     r7,#1
        0x0012e6a2:    053f        ?.      LSLS     r7,r7,#20
        0x0012e6a4:    463a        :F      MOV      r2,r7
        0x0012e6a6:    4630        0F      MOV      r0,r6
        0x0012e6a8:    6961        ai      LDR      r1,[r4,#0x14]
        0x0012e6aa:    47a8        .G      BLX      r5
        0x0012e6ac:    bdf8        ..      POP      {r3-r7,pc}
        0x0012e6ae:    0000        ..      MOVS     r0,r0
    i.peri_gate
    peri_gate
        0x0012e6b0:    b510        ..      PUSH     {r4,lr}
        0x0012e6b2:    4807        .H      LDR      r0,[pc,#28] ; [0x12e6d0] = 0x2aaa
        0x0012e6b4:    4907        .I      LDR      r1,[pc,#28] ; [0x12e6d4] = 0x20149000
        0x0012e6b6:    6148        Ha      STR      r0,[r1,#0x14]
        0x0012e6b8:    bf00        ..      NOP      
        0x0012e6ba:    4807        .H      LDR      r0,[pc,#28] ; [0x12e6d8] = 0xaaaaaaa
        0x0012e6bc:    6108        .a      STR      r0,[r1,#0x10]
        0x0012e6be:    bf00        ..      NOP      
        0x0012e6c0:    2080        .       MOVS     r0,#0x80
        0x0012e6c2:    4906        .I      LDR      r1,[pc,#24] ; [0x12e6dc] = 0x20132000
        0x0012e6c4:    6108        .a      STR      r0,[r1,#0x10]
        0x0012e6c6:    bf00        ..      NOP      
        0x0012e6c8:    4805        .H      LDR      r0,[pc,#20] ; [0x12e6e0] = 0xaa220
        0x0012e6ca:    f000f9e5    ....    BL       sysc_cpu_clkg1_set ; 0x12ea98
        0x0012e6ce:    bd10        ..      POP      {r4,pc}
    $d
        0x0012e6d0:    00002aaa    .*..    DCD    10922
        0x0012e6d4:    20149000    ...     DCD    538218496
        0x0012e6d8:    0aaaaaaa    ....    DCD    178956970
        0x0012e6dc:    20132000    . .     DCD    538124288
        0x0012e6e0:    000aa220     ...    DCD    696864
    $t
    i.qspi_ctrlr0_pack
    qspi_ctrlr0_pack
        0x0012e6e4:    b5f0        ..      PUSH     {r4-r7,lr}
        0x0012e6e6:    9d06        ..      LDR      r5,[sp,#0x18]
        0x0012e6e8:    9c05        ..      LDR      r4,[sp,#0x14]
        0x0012e6ea:    0546        F.      LSLS     r6,r0,#21
        0x0012e6ec:    040f        ..      LSLS     r7,r1,#16
        0x0012e6ee:    433e        >C      ORRS     r6,r6,r7
        0x0012e6f0:    0317        ..      LSLS     r7,r2,#12
        0x0012e6f2:    433e        >C      ORRS     r6,r6,r7
        0x0012e6f4:    02df        ..      LSLS     r7,r3,#11
        0x0012e6f6:    433e        >C      ORRS     r6,r6,r7
        0x0012e6f8:    02a7        ..      LSLS     r7,r4,#10
        0x0012e6fa:    433e        >C      ORRS     r6,r6,r7
        0x0012e6fc:    022f        /.      LSLS     r7,r5,#8
        0x0012e6fe:    433e        >C      ORRS     r6,r6,r7
        0x0012e700:    9f07        ..      LDR      r7,[sp,#0x1c]
        0x0012e702:    01ff        ..      LSLS     r7,r7,#7
        0x0012e704:    433e        >C      ORRS     r6,r6,r7
        0x0012e706:    9f08        ..      LDR      r7,[sp,#0x20]
        0x0012e708:    01bf        ..      LSLS     r7,r7,#6
        0x0012e70a:    433e        >C      ORRS     r6,r6,r7
        0x0012e70c:    9f09        ..      LDR      r7,[sp,#0x24]
        0x0012e70e:    013f        ?.      LSLS     r7,r7,#4
        0x0012e710:    433e        >C      ORRS     r6,r6,r7
        0x0012e712:    4f01        .O      LDR      r7,[pc,#4] ; [0x12e718] = 0x20300000
        0x0012e714:    603e        >`      STR      r6,[r7,#0]
        0x0012e716:    bdf0        ..      POP      {r4-r7,pc}
    $d
        0x0012e718:    20300000    ..0     DCD    540016640
    $t
    i.qspi_ctrlr1_pack
    qspi_ctrlr1_pack
        0x0012e71c:    4901        .I      LDR      r1,[pc,#4] ; [0x12e724] = 0x20300000
        0x0012e71e:    6048        H`      STR      r0,[r1,#4]
        0x0012e720:    4770        pG      BX       lr
    $d
        0x0012e722:    0000        ..      DCW    0
        0x0012e724:    20300000    ..0     DCD    540016640
    $t
    i.qspi_dmacr_pack
    qspi_dmacr_pack
        0x0012e728:    0042        B.      LSLS     r2,r0,#1
        0x0012e72a:    430a        .C      ORRS     r2,r2,r1
        0x0012e72c:    4b01        .K      LDR      r3,[pc,#4] ; [0x12e734] = 0x20300040
        0x0012e72e:    60da        .`      STR      r2,[r3,#0xc]
        0x0012e730:    4770        pG      BX       lr
    $d
        0x0012e732:    0000        ..      DCW    0
        0x0012e734:    20300040    @.0     DCD    540016704
    $t
    i.qspi_dmardlr_set
    qspi_dmardlr_set
        0x0012e738:    4901        .I      LDR      r1,[pc,#4] ; [0x12e740] = 0x20300040
        0x0012e73a:    6148        Ha      STR      r0,[r1,#0x14]
        0x0012e73c:    4770        pG      BX       lr
    $d
        0x0012e73e:    0000        ..      DCW    0
        0x0012e740:    20300040    @.0     DCD    540016704
    $t
    i.qspi_dr_set
    qspi_dr_set
        0x0012e744:    4901        .I      LDR      r1,[pc,#4] ; [0x12e74c] = 0x20300040
        0x0012e746:    6208        .b      STR      r0,[r1,#0x20]
        0x0012e748:    4770        pG      BX       lr
    $d
        0x0012e74a:    0000        ..      DCW    0
        0x0012e74c:    20300040    @.0     DCD    540016704
    $t
    i.qspi_flash_quad_read_data
    qspi_flash_quad_read_data
        0x0012e750:    b5ff        ..      PUSH     {r0-r7,lr}
        0x0012e752:    b089        ..      SUB      sp,sp,#0x24
        0x0012e754:    4604        .F      MOV      r4,r0
        0x0012e756:    460d        .F      MOV      r5,r1
        0x0012e758:    9e12        ..      LDR      r6,[sp,#0x48]
        0x0012e75a:    2001        .       MOVS     r0,#1
        0x0012e75c:    0280        ..      LSLS     r0,r0,#10
        0x0012e75e:    f7fffddd    ....    BL       clk_gate_cpu_g1 ; 0x12e31c
        0x0012e762:    4933        3I      LDR      r1,[pc,#204] ; [0x12e830] = 0xfff
        0x0012e764:    4628        (F      MOV      r0,r5
        0x0012e766:    f7fffc55    ..U.    BL       __aeabi_uidiv ; 0x12e014
        0x0012e76a:    b280        ..      UXTH     r0,r0
        0x0012e76c:    9008        ..      STR      r0,[sp,#0x20]
        0x0012e76e:    4930        0I      LDR      r1,[pc,#192] ; [0x12e830] = 0xfff
        0x0012e770:    4628        (F      MOV      r0,r5
        0x0012e772:    f7fffc4f    ..O.    BL       __aeabi_uidiv ; 0x12e014
        0x0012e776:    9107        ..      STR      r1,[sp,#0x1c]
        0x0012e778:    2000        .       MOVS     r0,#0
        0x0012e77a:    f000f937    ..7.    BL       qspi_ssi_en_setf ; 0x12e9ec
        0x0012e77e:    2000        .       MOVS     r0,#0
        0x0012e780:    f000f92e    ....    BL       qspi_ser_set ; 0x12e9e0
        0x0012e784:    2000        .       MOVS     r0,#0
        0x0012e786:    2302        .#      MOVS     r3,#2
        0x0012e788:    9002        ..      STR      r0,[sp,#8]
        0x0012e78a:    9003        ..      STR      r0,[sp,#0xc]
        0x0012e78c:    9004        ..      STR      r0,[sp,#0x10]
        0x0012e78e:    9301        ..      STR      r3,[sp,#4]
        0x0012e790:    9000        ..      STR      r0,[sp,#0]
        0x0012e792:    4603        .F      MOV      r3,r0
        0x0012e794:    4602        .F      MOV      r2,r0
        0x0012e796:    211f        .!      MOVS     r1,#0x1f
        0x0012e798:    2002        .       MOVS     r0,#2
        0x0012e79a:    f7ffffa3    ....    BL       qspi_ctrlr0_pack ; 0x12e6e4
        0x0012e79e:    1e69        i.      SUBS     r1,r5,#1
        0x0012e7a0:    b288        ..      UXTH     r0,r1
        0x0012e7a2:    f7ffffbb    ....    BL       qspi_ctrlr1_pack ; 0x12e71c
        0x0012e7a6:    2002        .       MOVS     r0,#2
        0x0012e7a8:    2106        .!      MOVS     r1,#6
        0x0012e7aa:    2700        .'      MOVS     r7,#0
        0x0012e7ac:    02f2        ..      LSLS     r2,r6,#11
        0x0012e7ae:    0203        ..      LSLS     r3,r0,#8
        0x0012e7b0:    431a        .C      ORRS     r2,r2,r3
        0x0012e7b2:    008b        ..      LSLS     r3,r1,#2
        0x0012e7b4:    431a        .C      ORRS     r2,r2,r3
        0x0012e7b6:    433a        :C      ORRS     r2,r2,r7
        0x0012e7b8:    4b1e        .K      LDR      r3,[pc,#120] ; [0x12e834] = 0x203000c0
        0x0012e7ba:    635a        Zc      STR      r2,[r3,#0x34]
        0x0012e7bc:    bf00        ..      NOP      
        0x0012e7be:    201f        .       MOVS     r0,#0x1f
        0x0012e7c0:    f7ffffba    ....    BL       qspi_dmardlr_set ; 0x12e738
        0x0012e7c4:    2100        .!      MOVS     r1,#0
        0x0012e7c6:    4608        .F      MOV      r0,r1
        0x0012e7c8:    f7ffffae    ....    BL       qspi_dmacr_pack ; 0x12e728
        0x0012e7cc:    2101        .!      MOVS     r1,#1
        0x0012e7ce:    2000        .       MOVS     r0,#0
        0x0012e7d0:    f7ffffaa    ....    BL       qspi_dmacr_pack ; 0x12e728
        0x0012e7d4:    2001        .       MOVS     r0,#1
        0x0012e7d6:    f000f921    ..!.    BL       qspi_ssienr_set ; 0x12ea1c
        0x0012e7da:    980b        ..      LDR      r0,[sp,#0x2c]
        0x0012e7dc:    f7ffffb2    ....    BL       qspi_dr_set ; 0x12e744
        0x0012e7e0:    980c        ..      LDR      r0,[sp,#0x30]
        0x0012e7e2:    f7ffffaf    ....    BL       qspi_dr_set ; 0x12e744
        0x0012e7e6:    2001        .       MOVS     r0,#1
        0x0012e7e8:    f000f8fa    ....    BL       qspi_ser_set ; 0x12e9e0
        0x0012e7ec:    2000        .       MOVS     r0,#0
        0x0012e7ee:    9006        ..      STR      r0,[sp,#0x18]
        0x0012e7f0:    e00b        ..      B        0x12e80a ; qspi_flash_quad_read_data + 186
        0x0012e7f2:    4810        .H      LDR      r0,[pc,#64] ; [0x12e834] = 0x203000c0
        0x0012e7f4:    302c        ,0      ADDS     r0,r0,#0x2c
        0x0012e7f6:    4a0e        .J      LDR      r2,[pc,#56] ; [0x12e830] = 0xfff
        0x0012e7f8:    4621        !F      MOV      r1,r4
        0x0012e7fa:    f7fffe35    ..5.    BL       dmac_transfer_QSPI_RX_32Bit ; 0x12e468
        0x0012e7fe:    480e        .H      LDR      r0,[pc,#56] ; [0x12e838] = 0x3ffc
        0x0012e800:    1824        $.      ADDS     r4,r4,r0
        0x0012e802:    9806        ..      LDR      r0,[sp,#0x18]
        0x0012e804:    1c40        @.      ADDS     r0,r0,#1
        0x0012e806:    b280        ..      UXTH     r0,r0
        0x0012e808:    9006        ..      STR      r0,[sp,#0x18]
        0x0012e80a:    9908        ..      LDR      r1,[sp,#0x20]
        0x0012e80c:    9806        ..      LDR      r0,[sp,#0x18]
        0x0012e80e:    4288        .B      CMP      r0,r1
        0x0012e810:    dbef        ..      BLT      0x12e7f2 ; qspi_flash_quad_read_data + 162
        0x0012e812:    4808        .H      LDR      r0,[pc,#32] ; [0x12e834] = 0x203000c0
        0x0012e814:    302c        ,0      ADDS     r0,r0,#0x2c
        0x0012e816:    4621        !F      MOV      r1,r4
        0x0012e818:    9a07        ..      LDR      r2,[sp,#0x1c]
        0x0012e81a:    f7fffe25    ..%.    BL       dmac_transfer_QSPI_RX_32Bit ; 0x12e468
        0x0012e81e:    2000        .       MOVS     r0,#0
        0x0012e820:    f000f8fc    ....    BL       qspi_ssienr_set ; 0x12ea1c
        0x0012e824:    2001        .       MOVS     r0,#1
        0x0012e826:    02c0        ..      LSLS     r0,r0,#11
        0x0012e828:    f7fffd78    ..x.    BL       clk_gate_cpu_g1 ; 0x12e31c
        0x0012e82c:    b00d        ..      ADD      sp,sp,#0x34
        0x0012e82e:    bdf0        ..      POP      {r4-r7,pc}
    $d
        0x0012e830:    00000fff    ....    DCD    4095
        0x0012e834:    203000c0    ..0     DCD    540016832
        0x0012e838:    00003ffc    .?..    DCD    16380
    $t
    i.qspi_flash_read_data
    qspi_flash_read_data
        0x0012e83c:    b5f0        ..      PUSH     {r4-r7,lr}
        0x0012e83e:    b089        ..      SUB      sp,sp,#0x24
        0x0012e840:    4604        .F      MOV      r4,r0
        0x0012e842:    460d        .F      MOV      r5,r1
        0x0012e844:    4616        .F      MOV      r6,r2
        0x0012e846:    461f        .F      MOV      r7,r3
        0x0012e848:    2001        .       MOVS     r0,#1
        0x0012e84a:    0280        ..      LSLS     r0,r0,#10
        0x0012e84c:    f7fffd66    ..f.    BL       clk_gate_cpu_g1 ; 0x12e31c
        0x0012e850:    492c        ,I      LDR      r1,[pc,#176] ; [0x12e904] = 0xfff
        0x0012e852:    4628        (F      MOV      r0,r5
        0x0012e854:    f7fffbde    ....    BL       __aeabi_uidiv ; 0x12e014
        0x0012e858:    b280        ..      UXTH     r0,r0
        0x0012e85a:    9008        ..      STR      r0,[sp,#0x20]
        0x0012e85c:    4929        )I      LDR      r1,[pc,#164] ; [0x12e904] = 0xfff
        0x0012e85e:    4628        (F      MOV      r0,r5
        0x0012e860:    f7fffbd8    ....    BL       __aeabi_uidiv ; 0x12e014
        0x0012e864:    9107        ..      STR      r1,[sp,#0x1c]
        0x0012e866:    2000        .       MOVS     r0,#0
        0x0012e868:    f000f8c0    ....    BL       qspi_ssi_en_setf ; 0x12e9ec
        0x0012e86c:    2000        .       MOVS     r0,#0
        0x0012e86e:    f000f8b7    ....    BL       qspi_ser_set ; 0x12e9e0
        0x0012e872:    2000        .       MOVS     r0,#0
        0x0012e874:    2303        .#      MOVS     r3,#3
        0x0012e876:    9002        ..      STR      r0,[sp,#8]
        0x0012e878:    9003        ..      STR      r0,[sp,#0xc]
        0x0012e87a:    9004        ..      STR      r0,[sp,#0x10]
        0x0012e87c:    9301        ..      STR      r3,[sp,#4]
        0x0012e87e:    9000        ..      STR      r0,[sp,#0]
        0x0012e880:    4603        .F      MOV      r3,r0
        0x0012e882:    4602        .F      MOV      r2,r0
        0x0012e884:    211f        .!      MOVS     r1,#0x1f
        0x0012e886:    f7ffff2d    ..-.    BL       qspi_ctrlr0_pack ; 0x12e6e4
        0x0012e88a:    1e69        i.      SUBS     r1,r5,#1
        0x0012e88c:    b288        ..      UXTH     r0,r1
        0x0012e88e:    f7ffff45    ..E.    BL       qspi_ctrlr1_pack ; 0x12e71c
        0x0012e892:    201f        .       MOVS     r0,#0x1f
        0x0012e894:    f7ffff50    ..P.    BL       qspi_dmardlr_set ; 0x12e738
        0x0012e898:    2100        .!      MOVS     r1,#0
        0x0012e89a:    4608        .F      MOV      r0,r1
        0x0012e89c:    f7ffff44    ..D.    BL       qspi_dmacr_pack ; 0x12e728
        0x0012e8a0:    2101        .!      MOVS     r1,#1
        0x0012e8a2:    2000        .       MOVS     r0,#0
        0x0012e8a4:    f7ffff40    ..@.    BL       qspi_dmacr_pack ; 0x12e728
        0x0012e8a8:    2001        .       MOVS     r0,#1
        0x0012e8aa:    f000f8b7    ....    BL       qspi_ssienr_set ; 0x12ea1c
        0x0012e8ae:    0239        9.      LSLS     r1,r7,#8
        0x0012e8b0:    0a09        ..      LSRS     r1,r1,#8
        0x0012e8b2:    0632        2.      LSLS     r2,r6,#24
        0x0012e8b4:    4311        .C      ORRS     r1,r1,r2
        0x0012e8b6:    4608        .F      MOV      r0,r1
        0x0012e8b8:    f7ffff44    ..D.    BL       qspi_dr_set ; 0x12e744
        0x0012e8bc:    2001        .       MOVS     r0,#1
        0x0012e8be:    f000f88f    ....    BL       qspi_ser_set ; 0x12e9e0
        0x0012e8c2:    2000        .       MOVS     r0,#0
        0x0012e8c4:    9006        ..      STR      r0,[sp,#0x18]
        0x0012e8c6:    e00a        ..      B        0x12e8de ; qspi_flash_read_data + 162
        0x0012e8c8:    480f        .H      LDR      r0,[pc,#60] ; [0x12e908] = 0x203000ec
        0x0012e8ca:    4a0e        .J      LDR      r2,[pc,#56] ; [0x12e904] = 0xfff
        0x0012e8cc:    4621        !F      MOV      r1,r4
        0x0012e8ce:    f7fffdcb    ....    BL       dmac_transfer_QSPI_RX_32Bit ; 0x12e468
        0x0012e8d2:    480e        .H      LDR      r0,[pc,#56] ; [0x12e90c] = 0x3ffc
        0x0012e8d4:    1824        $.      ADDS     r4,r4,r0
        0x0012e8d6:    9806        ..      LDR      r0,[sp,#0x18]
        0x0012e8d8:    1c40        @.      ADDS     r0,r0,#1
        0x0012e8da:    b280        ..      UXTH     r0,r0
        0x0012e8dc:    9006        ..      STR      r0,[sp,#0x18]
        0x0012e8de:    9908        ..      LDR      r1,[sp,#0x20]
        0x0012e8e0:    9806        ..      LDR      r0,[sp,#0x18]
        0x0012e8e2:    4288        .B      CMP      r0,r1
        0x0012e8e4:    dbf0        ..      BLT      0x12e8c8 ; qspi_flash_read_data + 140
        0x0012e8e6:    4808        .H      LDR      r0,[pc,#32] ; [0x12e908] = 0x203000ec
        0x0012e8e8:    4621        !F      MOV      r1,r4
        0x0012e8ea:    9a07        ..      LDR      r2,[sp,#0x1c]
        0x0012e8ec:    f7fffdbc    ....    BL       dmac_transfer_QSPI_RX_32Bit ; 0x12e468
        0x0012e8f0:    2000        .       MOVS     r0,#0
        0x0012e8f2:    f000f893    ....    BL       qspi_ssienr_set ; 0x12ea1c
        0x0012e8f6:    2001        .       MOVS     r0,#1
        0x0012e8f8:    02c0        ..      LSLS     r0,r0,#11
        0x0012e8fa:    f7fffd0f    ....    BL       clk_gate_cpu_g1 ; 0x12e31c
        0x0012e8fe:    b009        ..      ADD      sp,sp,#0x24
        0x0012e900:    bdf0        ..      POP      {r4-r7,pc}
    $d
        0x0012e902:    0000        ..      DCW    0
        0x0012e904:    00000fff    ....    DCD    4095
        0x0012e908:    203000ec    ..0     DCD    540016876
        0x0012e90c:    00003ffc    .?..    DCD    16380
    $t
    i.qspi_read
    qspi_read
        0x0012e910:    b5ff        ..      PUSH     {r0-r7,lr}
        0x0012e912:    b085        ..      SUB      sp,sp,#0x14
        0x0012e914:    4605        .F      MOV      r5,r0
        0x0012e916:    460c        .F      MOV      r4,r1
        0x0012e918:    4617        .F      MOV      r7,r2
        0x0012e91a:    2001        .       MOVS     r0,#1
        0x0012e91c:    0280        ..      LSLS     r0,r0,#10
        0x0012e91e:    f7fffcfd    ....    BL       clk_gate_cpu_g1 ; 0x12e31c
        0x0012e922:    2000        .       MOVS     r0,#0
        0x0012e924:    f000f862    ..b.    BL       qspi_ssi_en_setf ; 0x12e9ec
        0x0012e928:    2000        .       MOVS     r0,#0
        0x0012e92a:    f000f859    ..Y.    BL       qspi_ser_set ; 0x12e9e0
        0x0012e92e:    2000        .       MOVS     r0,#0
        0x0012e930:    2303        .#      MOVS     r3,#3
        0x0012e932:    9002        ..      STR      r0,[sp,#8]
        0x0012e934:    9003        ..      STR      r0,[sp,#0xc]
        0x0012e936:    9004        ..      STR      r0,[sp,#0x10]
        0x0012e938:    9301        ..      STR      r3,[sp,#4]
        0x0012e93a:    9000        ..      STR      r0,[sp,#0]
        0x0012e93c:    4603        .F      MOV      r3,r0
        0x0012e93e:    4602        .F      MOV      r2,r0
        0x0012e940:    2107        .!      MOVS     r1,#7
        0x0012e942:    f7fffecf    ....    BL       qspi_ctrlr0_pack ; 0x12e6e4
        0x0012e946:    1e61        a.      SUBS     r1,r4,#1
        0x0012e948:    b288        ..      UXTH     r0,r1
        0x0012e94a:    f7fffee7    ....    BL       qspi_ctrlr1_pack ; 0x12e71c
        0x0012e94e:    2001        .       MOVS     r0,#1
        0x0012e950:    f000f864    ..d.    BL       qspi_ssienr_set ; 0x12ea1c
        0x0012e954:    2600        .&      MOVS     r6,#0
        0x0012e956:    e005        ..      B        0x12e964 ; qspi_read + 84
        0x0012e958:    7838        8x      LDRB     r0,[r7,#0]
        0x0012e95a:    1c7f        ..      ADDS     r7,r7,#1
        0x0012e95c:    f7fffef2    ....    BL       qspi_dr_set ; 0x12e744
        0x0012e960:    1c70        p.      ADDS     r0,r6,#1
        0x0012e962:    b286        ..      UXTH     r6,r0
        0x0012e964:    9808        ..      LDR      r0,[sp,#0x20]
        0x0012e966:    4286        .B      CMP      r6,r0
        0x0012e968:    dbf6        ..      BLT      0x12e958 ; qspi_read + 72
        0x0012e96a:    2001        .       MOVS     r0,#1
        0x0012e96c:    f000f838    ..8.    BL       qspi_ser_set ; 0x12e9e0
        0x0012e970:    2c40        @,      CMP      r4,#0x40
        0x0012e972:    d819        ..      BHI      0x12e9a8 ; qspi_read + 152
        0x0012e974:    bf00        ..      NOP      
        0x0012e976:    f000f857    ..W.    BL       qspi_tfe_getf ; 0x12ea28
        0x0012e97a:    2801        .(      CMP      r0,#1
        0x0012e97c:    d1fb        ..      BNE      0x12e976 ; qspi_read + 102
        0x0012e97e:    bf00        ..      NOP      
        0x0012e980:    bf00        ..      NOP      
        0x0012e982:    4816        .H      LDR      r0,[pc,#88] ; [0x12e9dc] = 0x20300000
        0x0012e984:    6a80        .j      LDR      r0,[r0,#0x28]
        0x0012e986:    07c0        ..      LSLS     r0,r0,#31
        0x0012e988:    0fc0        ..      LSRS     r0,r0,#31
        0x0012e98a:    2800        .(      CMP      r0,#0
        0x0012e98c:    d1f8        ..      BNE      0x12e980 ; qspi_read + 112
        0x0012e98e:    2600        .&      MOVS     r6,#0
        0x0012e990:    e007        ..      B        0x12e9a2 ; qspi_read + 146
        0x0012e992:    bf00        ..      NOP      
        0x0012e994:    4811        .H      LDR      r0,[pc,#68] ; [0x12e9dc] = 0x20300000
        0x0012e996:    3040        @0      ADDS     r0,r0,#0x40
        0x0012e998:    6a00        .j      LDR      r0,[r0,#0x20]
        0x0012e99a:    7028        (p      STRB     r0,[r5,#0]
        0x0012e99c:    1c6d        m.      ADDS     r5,r5,#1
        0x0012e99e:    1c70        p.      ADDS     r0,r6,#1
        0x0012e9a0:    b286        ..      UXTH     r6,r0
        0x0012e9a2:    42a6        .B      CMP      r6,r4
        0x0012e9a4:    d3f5        ..      BCC      0x12e992 ; qspi_read + 130
        0x0012e9a6:    e010        ..      B        0x12e9ca ; qspi_read + 186
        0x0012e9a8:    201f        .       MOVS     r0,#0x1f
        0x0012e9aa:    f7fffec5    ....    BL       qspi_dmardlr_set ; 0x12e738
        0x0012e9ae:    2100        .!      MOVS     r1,#0
        0x0012e9b0:    4608        .F      MOV      r0,r1
        0x0012e9b2:    f7fffeb9    ....    BL       qspi_dmacr_pack ; 0x12e728
        0x0012e9b6:    2101        .!      MOVS     r1,#1
        0x0012e9b8:    2000        .       MOVS     r0,#0
        0x0012e9ba:    f7fffeb5    ....    BL       qspi_dmacr_pack ; 0x12e728
        0x0012e9be:    4807        .H      LDR      r0,[pc,#28] ; [0x12e9dc] = 0x20300000
        0x0012e9c0:    3060        `0      ADDS     r0,r0,#0x60
        0x0012e9c2:    4622        "F      MOV      r2,r4
        0x0012e9c4:    4629        )F      MOV      r1,r5
        0x0012e9c6:    f7fffd1f    ....    BL       dmac_transfer_QSPI_RX ; 0x12e408
        0x0012e9ca:    2000        .       MOVS     r0,#0
        0x0012e9cc:    f000f826    ..&.    BL       qspi_ssienr_set ; 0x12ea1c
        0x0012e9d0:    2001        .       MOVS     r0,#1
        0x0012e9d2:    02c0        ..      LSLS     r0,r0,#11
        0x0012e9d4:    f7fffca2    ....    BL       clk_gate_cpu_g1 ; 0x12e31c
        0x0012e9d8:    b009        ..      ADD      sp,sp,#0x24
        0x0012e9da:    bdf0        ..      POP      {r4-r7,pc}
    $d
        0x0012e9dc:    20300000    ..0     DCD    540016640
    $t
    i.qspi_ser_set
    qspi_ser_set
        0x0012e9e0:    4901        .I      LDR      r1,[pc,#4] ; [0x12e9e8] = 0x20300000
        0x0012e9e2:    6108        .a      STR      r0,[r1,#0x10]
        0x0012e9e4:    4770        pG      BX       lr
    $d
        0x0012e9e6:    0000        ..      DCW    0
        0x0012e9e8:    20300000    ..0     DCD    540016640
    $t
    i.qspi_ssi_en_setf
    qspi_ssi_en_setf
        0x0012e9ec:    4904        .I      LDR      r1,[pc,#16] ; [0x12ea00] = 0x20300000
        0x0012e9ee:    6889        .h      LDR      r1,[r1,#8]
        0x0012e9f0:    0849        I.      LSRS     r1,r1,#1
        0x0012e9f2:    0049        I.      LSLS     r1,r1,#1
        0x0012e9f4:    07c2        ..      LSLS     r2,r0,#31
        0x0012e9f6:    0fd2        ..      LSRS     r2,r2,#31
        0x0012e9f8:    4311        .C      ORRS     r1,r1,r2
        0x0012e9fa:    4a01        .J      LDR      r2,[pc,#4] ; [0x12ea00] = 0x20300000
        0x0012e9fc:    6091        .`      STR      r1,[r2,#8]
        0x0012e9fe:    4770        pG      BX       lr
    $d
        0x0012ea00:    20300000    ..0     DCD    540016640
    $t
    i.qspi_ssi_en_setf
    qspi_ssi_en_setf
        0x0012ea04:    4904        .I      LDR      r1,[pc,#16] ; [0x12ea18] = 0x20300000
        0x0012ea06:    6889        .h      LDR      r1,[r1,#8]
        0x0012ea08:    0849        I.      LSRS     r1,r1,#1
        0x0012ea0a:    0049        I.      LSLS     r1,r1,#1
        0x0012ea0c:    07c2        ..      LSLS     r2,r0,#31
        0x0012ea0e:    0fd2        ..      LSRS     r2,r2,#31
        0x0012ea10:    4311        .C      ORRS     r1,r1,r2
        0x0012ea12:    4a01        .J      LDR      r2,[pc,#4] ; [0x12ea18] = 0x20300000
        0x0012ea14:    6091        .`      STR      r1,[r2,#8]
        0x0012ea16:    4770        pG      BX       lr
    $d
        0x0012ea18:    20300000    ..0     DCD    540016640
    $t
    i.qspi_ssienr_set
    qspi_ssienr_set
        0x0012ea1c:    4901        .I      LDR      r1,[pc,#4] ; [0x12ea24] = 0x20300000
        0x0012ea1e:    6088        .`      STR      r0,[r1,#8]
        0x0012ea20:    4770        pG      BX       lr
    $d
        0x0012ea22:    0000        ..      DCW    0
        0x0012ea24:    20300000    ..0     DCD    540016640
    $t
    i.qspi_tfe_getf
    qspi_tfe_getf
        0x0012ea28:    4802        .H      LDR      r0,[pc,#8] ; [0x12ea34] = 0x20300000
        0x0012ea2a:    6a80        .j      LDR      r0,[r0,#0x28]
        0x0012ea2c:    0740        @.      LSLS     r0,r0,#29
        0x0012ea2e:    0fc0        ..      LSRS     r0,r0,#31
        0x0012ea30:    4770        pG      BX       lr
    $d
        0x0012ea32:    0000        ..      DCW    0
        0x0012ea34:    20300000    ..0     DCD    540016640
    $t
    i.sysc_awo_clkgen_awo_signal_1_set
    sysc_awo_clkgen_awo_signal_1_set
        0x0012ea38:    4901        .I      LDR      r1,[pc,#4] ; [0x12ea40] = 0x20201000
        0x0012ea3a:    6388        .c      STR      r0,[r1,#0x38]
        0x0012ea3c:    4770        pG      BX       lr
    $d
        0x0012ea3e:    0000        ..      DCW    0
        0x0012ea40:    20201000    ..      DCD    538972160
    $t
    i.sysc_awo_dr_16m_rcosc_en_setf
    sysc_awo_dr_16m_rcosc_en_setf
        0x0012ea44:    4905        .I      LDR      r1,[pc,#20] ; [0x12ea5c] = 0x20201000
        0x0012ea46:    69c9        .i      LDR      r1,[r1,#0x1c]
        0x0012ea48:    2210        ."      MOVS     r2,#0x10
        0x0012ea4a:    4391        .C      BICS     r1,r1,r2
        0x0012ea4c:    0102        ..      LSLS     r2,r0,#4
        0x0012ea4e:    2310        .#      MOVS     r3,#0x10
        0x0012ea50:    401a        .@      ANDS     r2,r2,r3
        0x0012ea52:    4311        .C      ORRS     r1,r1,r2
        0x0012ea54:    4a01        .J      LDR      r2,[pc,#4] ; [0x12ea5c] = 0x20201000
        0x0012ea56:    61d1        .a      STR      r1,[r2,#0x1c]
        0x0012ea58:    4770        pG      BX       lr
    $d
        0x0012ea5a:    0000        ..      DCW    0
        0x0012ea5c:    20201000    ..      DCD    538972160
    $t
    i.sysc_awo_reg_16m_rcosc_en_setf
    sysc_awo_reg_16m_rcosc_en_setf
        0x0012ea60:    4906        .I      LDR      r1,[pc,#24] ; [0x12ea7c] = 0x20201000
        0x0012ea62:    69c9        .i      LDR      r1,[r1,#0x1c]
        0x0012ea64:    2201        ."      MOVS     r2,#1
        0x0012ea66:    0312        ..      LSLS     r2,r2,#12
        0x0012ea68:    4391        .C      BICS     r1,r1,r2
        0x0012ea6a:    0302        ..      LSLS     r2,r0,#12
        0x0012ea6c:    2301        .#      MOVS     r3,#1
        0x0012ea6e:    031b        ..      LSLS     r3,r3,#12
        0x0012ea70:    401a        .@      ANDS     r2,r2,r3
        0x0012ea72:    4311        .C      ORRS     r1,r1,r2
        0x0012ea74:    4a01        .J      LDR      r2,[pc,#4] ; [0x12ea7c] = 0x20201000
        0x0012ea76:    61d1        .a      STR      r1,[r2,#0x1c]
        0x0012ea78:    4770        pG      BX       lr
    $d
        0x0012ea7a:    0000        ..      DCW    0
        0x0012ea7c:    20201000    ..      DCD    538972160
    $t
    i.sysc_awo_rf_reg_0_get
    sysc_awo_rf_reg_0_get
        0x0012ea80:    4801        .H      LDR      r0,[pc,#4] ; [0x12ea88] = 0x20201040
        0x0012ea82:    6b00        .k      LDR      r0,[r0,#0x30]
        0x0012ea84:    4770        pG      BX       lr
    $d
        0x0012ea86:    0000        ..      DCW    0
        0x0012ea88:    20201040    @.      DCD    538972224
    $t
    i.sysc_awo_rf_reg_0_set
    sysc_awo_rf_reg_0_set
        0x0012ea8c:    4901        .I      LDR      r1,[pc,#4] ; [0x12ea94] = 0x20201040
        0x0012ea8e:    6308        .c      STR      r0,[r1,#0x30]
        0x0012ea90:    4770        pG      BX       lr
    $d
        0x0012ea92:    0000        ..      DCW    0
        0x0012ea94:    20201040    @.      DCD    538972224
    $t
    i.sysc_cpu_clkg1_set
    sysc_cpu_clkg1_set
        0x0012ea98:    4901        .I      LDR      r1,[pc,#4] ; [0x12eaa0] = 0x20132000
        0x0012ea9a:    6148        Ha      STR      r0,[r1,#0x14]
        0x0012ea9c:    4770        pG      BX       lr
    $d
        0x0012ea9e:    0000        ..      DCW    0
        0x0012eaa0:    20132000    . .     DCD    538124288
    $t
    i.sysc_cpu_qspi_en_setf
    sysc_cpu_qspi_en_setf
        0x0012eaa4:    4904        .I      LDR      r1,[pc,#16] ; [0x12eab8] = 0x20132000
        0x0012eaa6:    6a09        .j      LDR      r1,[r1,#0x20]
        0x0012eaa8:    0909        ..      LSRS     r1,r1,#4
        0x0012eaaa:    0109        ..      LSLS     r1,r1,#4
        0x0012eaac:    0702        ..      LSLS     r2,r0,#28
        0x0012eaae:    0f12        ..      LSRS     r2,r2,#28
        0x0012eab0:    4311        .C      ORRS     r1,r1,r2
        0x0012eab2:    4a01        .J      LDR      r2,[pc,#4] ; [0x12eab8] = 0x20132000
        0x0012eab4:    6211        .b      STR      r1,[r2,#0x20]
        0x0012eab6:    4770        pG      BX       lr
    $d
        0x0012eab8:    20132000    . .     DCD    538124288

====================================

** Section #2

    Name        : EXEC_SECTION
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : SHF_ALLOC + SHF_WRITE (0x00000003)
    Addr        : 0x0012eabc
    File Offset : 2816 (0xb00)
    Size        : 4 bytes (0x4)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 4
    Entry Size  : 0

    0x12eabc:   00 d8 b8 05                                        ....


====================================

** Section #3

    Name        : .debug_abbrev
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 2820 (0xb04)
    Size        : 1444 bytes (0x5a4)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #4

    Name        : .debug_frame
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 4264 (0x10a8)
    Size        : 1256 bytes (0x4e8)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #5

    Name        : .debug_info
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 5520 (0x1590)
    Size        : 235852 bytes (0x3994c)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #6

    Name        : .debug_line
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 241372 (0x3aedc)
    Size        : 13076 bytes (0x3314)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #7

    Name        : .debug_loc
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 254448 (0x3e1f0)
    Size        : 3972 bytes (0xf84)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #8

    Name        : .debug_macinfo
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 258420 (0x3f174)
    Size        : 4040 bytes (0xfc8)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #9

    Name        : .debug_pubnames
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 262460 (0x4013c)
    Size        : 1033 bytes (0x409)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #10

    Name        : .symtab
    Type        : SHT_SYMTAB (0x00000002)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 263496 (0x40548)
    Size        : 3376 bytes (0xd30)
    Link        : Section 11 (.strtab)
    Info        : Last local symbol no = 181
    Alignment   : 4
    Entry Size  : 16


====================================

** Section #11

    Name        : .strtab
    Type        : SHT_STRTAB (0x00000003)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 266872 (0x41278)
    Size        : 3284 bytes (0xcd4)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #12

    Name        : .note
    Type        : SHT_NOTE (0x00000007)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 270156 (0x41f4c)
    Size        : 24 bytes (0x18)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 4
    Entry Size  : 0

        Section     Segment
    ====================================

              1           0
              2           0

====================================

** Section #13

    Name        : .comment
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 270180 (0x41f64)
    Size        : 54928 bytes (0xd690)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0

    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armlink [4d35a8]
    armlink --verbose --library_type=microlib --callgraph --map --symbols --xref --cpu=Cortex-M0+ --datacompressor=off --list=../../../../output/boot_ram/boot_ram.map --output=../../../../output/boot_ram/boot_ram.elf --scatter=E:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/bootloader/boot_ram/boot_ram_scatter.txt --entry=boot_ram_entry --info=any,architecture,exceptions,inline,inputs,libraries,merge,pltgot,sizes,stack,summarysizes,summarystack,tailreorder,totals,unused,unusedsymbols,veneers,veneercallers,veneerpools,visibility,weakrefs

    C:\Keil_v5\ARM\ARMCC\bin\..\lib\armlib\h_p.l
    C:\Keil_v5\ARM\ARMCC\bin\..\lib\armlib\m_ps.l
    C:\Keil_v5\ARM\ARMCC\bin\..\lib\armlib\mc_p.l
    C:\Keil_v5\ARM\ARMCC\bin\..\lib\armlib\mf_p.l
    C:\Keil_v5\ARM\ARMCC\bin\..\lib\armlib\vfpsupport.l
    Input Comments:
    
    boot_ram.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armlink [4d35a8]
    armlink --partial --no_add_relocs_to_undefined --no_generate_mapping_symbols --diag_suppress=6642 --cpu=Cortex-M0+ --fpu=SoftVFP --output=CMakeFiles/boot_ram.dir/boot_ram.o --vfemode=force

    Input Comments:
    
    p6780-3
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armasm [4d35a5]
    armasm --debug --diag_suppress=1602,1073 --cpu=Cortex-M0+ --fpu=SoftVFP --apcs=/interwork --no_divide 
    boot_ram.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armcc [4d35ad]
    armcc --c99 --bss_threshold=0 --split_sections --debug -c  --cpu=Cortex-M0+ -O0 -Otime -IE:/KeilProject/SVN/Jmesh/trunk/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/bootloader/boot_ram/.. -IE:/KeilProject/SVN/Jmesh/trunk/modules/ke/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/dbg/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/common/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rwip/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/nvds/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rf/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/ecc_p256/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/h4tl/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/app/api -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/boot/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/compiler/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/ll/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/intc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/led -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/uart -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/reg -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash_cache -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl/awo -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pshare -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/dmac -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/gpio -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pwm -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/wdt -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/timer -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/rtc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/adc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/clk_gen -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/iic -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/patch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/hw_ecc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/qspi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/modem -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/spi_master -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/sleep -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/RTT -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/jmp_table -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/patch_list -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/build/ble-full/reg/fw -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/cmsis_inc -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/include -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/portable/armcc/arm_cm0 -IE:/KeilProject/SVN/Jmesh/trunk/freertos/app -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/oled_iic -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/mems_spi -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/motor -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/temp -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/rgb_led -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/uart_echo -IE:/KeilProject/SVN/Jmesh/trunk/freertos -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llm -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/lld -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/em -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/rwble -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/inc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/basc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/bass/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/disc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/diss/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpbh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpd/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogprh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lanc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lans/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/paspc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/pasps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxm/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxr/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tipc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tips/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota/bxotas/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota -IE:/KeilProject/SVN/Jmesh/trunk/ip/hci/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ahi/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ea/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/em/api -DNDEBUG -D__BOOT_RAM__ -D__MICROLIB
    
    awo_2400.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armlink [4d35a8]
    armlink --partial --no_add_relocs_to_undefined --no_generate_mapping_symbols --diag_suppress=6642 --cpu=Cortex-M0+ --fpu=SoftVFP --output=CMakeFiles/boot_ram.dir/__/__/src/driver/sysctrl/awo/awo_2400.o --vfemode=force

    Input Comments:
    
    p2a08-3
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armasm [4d35a5]
    armasm --debug --diag_suppress=1602,1073 --cpu=Cortex-M0+ --fpu=SoftVFP --apcs=/interwork --no_divide 
    awo_2400.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armcc [4d35ad]
    armcc --c99 --bss_threshold=0 --split_sections --debug -c  --cpu=Cortex-M0+ -O0 -Otime -IE:/KeilProject/SVN/Jmesh/trunk/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/bootloader/boot_ram/.. -IE:/KeilProject/SVN/Jmesh/trunk/modules/ke/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/dbg/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/common/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rwip/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/nvds/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rf/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/ecc_p256/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/h4tl/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/app/api -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/boot/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/compiler/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/ll/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/intc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/led -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/uart -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/reg -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash_cache -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl/awo -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pshare -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/dmac -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/gpio -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pwm -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/wdt -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/timer -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/rtc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/adc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/clk_gen -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/iic -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/patch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/hw_ecc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/qspi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/modem -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/spi_master -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/sleep -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/RTT -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/jmp_table -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/patch_list -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/build/ble-full/reg/fw -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/cmsis_inc -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/include -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/portable/armcc/arm_cm0 -IE:/KeilProject/SVN/Jmesh/trunk/freertos/app -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/oled_iic -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/mems_spi -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/motor -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/temp -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/rgb_led -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/uart_echo -IE:/KeilProject/SVN/Jmesh/trunk/freertos -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llm -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/lld -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/em -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/rwble -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/inc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/basc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/bass/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/disc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/diss/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpbh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpd/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogprh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lanc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lans/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/paspc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/pasps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxm/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxr/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tipc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tips/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota/bxotas/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota -IE:/KeilProject/SVN/Jmesh/trunk/ip/hci/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ahi/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ea/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/em/api -DNDEBUG -D__BOOT_RAM__ -D__MICROLIB
    
    
    
    
    awo_2401.o
    flash.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armcc [4d35ad]
    armcc --c99 --bss_threshold=0 --split_sections --debug -c  --cpu=Cortex-M0+ -O0 -Otime -IE:/KeilProject/SVN/Jmesh/trunk/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/bootloader/boot_ram/.. -IE:/KeilProject/SVN/Jmesh/trunk/modules/ke/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/dbg/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/common/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rwip/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/nvds/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rf/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/ecc_p256/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/h4tl/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/app/api -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/boot/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/compiler/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/ll/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/intc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/led -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/uart -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/reg -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash_cache -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl/awo -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pshare -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/dmac -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/gpio -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pwm -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/wdt -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/timer -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/rtc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/adc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/clk_gen -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/iic -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/patch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/hw_ecc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/qspi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/modem -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/spi_master -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/sleep -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/RTT -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/jmp_table -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/patch_list -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/build/ble-full/reg/fw -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/cmsis_inc -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/include -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/portable/armcc/arm_cm0 -IE:/KeilProject/SVN/Jmesh/trunk/freertos/app -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/oled_iic -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/mems_spi -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/motor -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/temp -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/rgb_led -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/uart_echo -IE:/KeilProject/SVN/Jmesh/trunk/freertos -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llm -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/lld -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/em -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/rwble -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/inc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/basc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/bass/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/disc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/diss/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpbh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpd/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogprh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lanc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lans/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/paspc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/pasps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxm/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxr/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tipc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tips/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota/bxotas/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota -IE:/KeilProject/SVN/Jmesh/trunk/ip/hci/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ahi/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ea/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/em/api -DNDEBUG -D__BOOT_RAM__ -D__MICROLIB
    dma_for_qspi.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armlink [4d35a8]
    armlink --partial --no_add_relocs_to_undefined --no_generate_mapping_symbols --diag_suppress=6642 --cpu=Cortex-M0+ --fpu=SoftVFP --output=CMakeFiles/boot_ram.dir/__/__/src/driver/dmac/dma_for_qspi.o --vfemode=force

    Input Comments:
    
    p2354-3
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armasm [4d35a5]
    armasm --debug --diag_suppress=1602,1073 --cpu=Cortex-M0+ --fpu=SoftVFP --apcs=/interwork --no_divide 
    dma_for_qspi.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armcc [4d35ad]
    armcc --c99 --bss_threshold=0 --split_sections --debug -c  --cpu=Cortex-M0+ -O0 -Otime -IE:/KeilProject/SVN/Jmesh/trunk/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/bootloader/boot_ram/.. -IE:/KeilProject/SVN/Jmesh/trunk/modules/ke/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/dbg/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/common/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rwip/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/nvds/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rf/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/ecc_p256/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/h4tl/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/app/api -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/boot/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/compiler/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/ll/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/intc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/led -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/uart -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/reg -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash_cache -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl/awo -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pshare -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/dmac -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/gpio -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pwm -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/wdt -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/timer -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/rtc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/adc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/clk_gen -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/iic -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/patch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/hw_ecc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/qspi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/modem -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/spi_master -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/sleep -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/RTT -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/jmp_table -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/patch_list -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/build/ble-full/reg/fw -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/cmsis_inc -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/include -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/portable/armcc/arm_cm0 -IE:/KeilProject/SVN/Jmesh/trunk/freertos/app -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/oled_iic -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/mems_spi -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/motor -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/temp -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/rgb_led -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/uart_echo -IE:/KeilProject/SVN/Jmesh/trunk/freertos -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llm -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/lld -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/em -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/rwble -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/inc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/basc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/bass/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/disc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/diss/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpbh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpd/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogprh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lanc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lans/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/paspc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/pasps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxm/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxr/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tipc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tips/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota/bxotas/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota -IE:/KeilProject/SVN/Jmesh/trunk/ip/hci/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ahi/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ea/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/em/api -DNDEBUG -D__BOOT_RAM__ -D__MICROLIB
    
    
    
    qspi.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armlink [4d35a8]
    armlink --partial --no_add_relocs_to_undefined --no_generate_mapping_symbols --diag_suppress=6642 --cpu=Cortex-M0+ --fpu=SoftVFP --output=CMakeFiles/boot_ram.dir/__/__/src/driver/ssi/qspi/qspi.o --vfemode=force

    Input Comments:
    
    p358c-3
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armasm [4d35a5]
    armasm --debug --diag_suppress=1602,1073 --cpu=Cortex-M0+ --fpu=SoftVFP --apcs=/interwork --no_divide 
    qspi.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armcc [4d35ad]
    armcc --c99 --bss_threshold=0 --split_sections --debug -c  --cpu=Cortex-M0+ -O0 -Otime -IE:/KeilProject/SVN/Jmesh/trunk/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/bootloader/boot_ram/.. -IE:/KeilProject/SVN/Jmesh/trunk/modules/ke/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/dbg/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/common/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rwip/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/nvds/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rf/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/ecc_p256/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/h4tl/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/app/api -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/boot/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/compiler/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/ll/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/intc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/led -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/uart -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/reg -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash_cache -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl/awo -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pshare -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/dmac -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/gpio -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pwm -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/wdt -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/timer -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/rtc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/adc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/clk_gen -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/iic -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/patch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/hw_ecc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/qspi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/modem -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/spi_master -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/sleep -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/RTT -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/jmp_table -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/patch_list -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/build/ble-full/reg/fw -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/cmsis_inc -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/include -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/portable/armcc/arm_cm0 -IE:/KeilProject/SVN/Jmesh/trunk/freertos/app -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/oled_iic -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/mems_spi -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/motor -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/temp -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/rgb_led -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/uart_echo -IE:/KeilProject/SVN/Jmesh/trunk/freertos -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llm -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/lld -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/em -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/rwble -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/inc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/basc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/bass/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/disc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/diss/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpbh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpd/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogprh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lanc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lans/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/paspc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/pasps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxm/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxr/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tipc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tips/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota/bxotas/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota -IE:/KeilProject/SVN/Jmesh/trunk/ip/hci/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ahi/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ea/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/em/api -DNDEBUG -D__BOOT_RAM__ -D__MICROLIB
    
    
    
    flash_cache.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armlink [4d35a8]
    armlink --partial --no_add_relocs_to_undefined --no_generate_mapping_symbols --diag_suppress=6642 --cpu=Cortex-M0+ --fpu=SoftVFP --output=CMakeFiles/boot_ram.dir/__/__/src/driver/flash_cache/flash_cache.o --vfemode=force

    Input Comments:
    
    p6644-3
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armasm [4d35a5]
    armasm --debug --diag_suppress=1602,1073 --cpu=Cortex-M0+ --fpu=SoftVFP --apcs=/interwork --no_divide 
    flash_cache.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armcc [4d35ad]
    armcc --c99 --bss_threshold=0 --split_sections --debug -c  --cpu=Cortex-M0+ -O0 -Otime -IE:/KeilProject/SVN/Jmesh/trunk/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/bootloader/boot_ram/.. -IE:/KeilProject/SVN/Jmesh/trunk/modules/ke/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/dbg/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/common/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rwip/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/nvds/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rf/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/ecc_p256/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/h4tl/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/app/api -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/boot/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/compiler/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/ll/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/intc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/led -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/uart -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/reg -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash_cache -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl/awo -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pshare -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/dmac -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/gpio -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pwm -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/wdt -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/timer -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/rtc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/adc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/clk_gen -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/iic -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/patch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/hw_ecc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/qspi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/modem -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/spi_master -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/sleep -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/RTT -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/jmp_table -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/patch_list -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/build/ble-full/reg/fw -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/cmsis_inc -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/include -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/portable/armcc/arm_cm0 -IE:/KeilProject/SVN/Jmesh/trunk/freertos/app -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/oled_iic -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/mems_spi -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/motor -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/temp -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/rgb_led -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/uart_echo -IE:/KeilProject/SVN/Jmesh/trunk/freertos -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llm -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/lld -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/em -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/rwble -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/inc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/basc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/bass/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/disc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/diss/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpbh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpd/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogprh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lanc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lans/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/paspc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/pasps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxm/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxr/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tipc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tips/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota/bxotas/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota -IE:/KeilProject/SVN/Jmesh/trunk/ip/hci/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ahi/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ea/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/em/api -DNDEBUG -D__BOOT_RAM__ -D__MICROLIB
    
    
    clk_gate.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armlink [4d35a8]
    armlink --partial --no_add_relocs_to_undefined --no_generate_mapping_symbols --diag_suppress=6642 --cpu=Cortex-M0+ --fpu=SoftVFP --output=CMakeFiles/boot_ram.dir/__/__/src/driver/sysctrl/clk_gate.o --vfemode=force

    Input Comments:
    
    p4628-3
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armasm [4d35a5]
    armasm --debug --diag_suppress=1602,1073 --cpu=Cortex-M0+ --fpu=SoftVFP --apcs=/interwork --no_divide 
    clk_gate.o
    
    Component: ARM Compiler 5.06 update 1 (build 61) Tool: armcc [4d35ad]
    armcc --c99 --bss_threshold=0 --split_sections --debug -c  --cpu=Cortex-M0+ -O0 -Otime -IE:/KeilProject/SVN/Jmesh/trunk/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/bootloader/boot_ram/.. -IE:/KeilProject/SVN/Jmesh/trunk/modules/ke/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/dbg/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/common/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rwip/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/nvds/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/rf/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/ecc_p256/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/h4tl/api -IE:/KeilProject/SVN/Jmesh/trunk/modules/app/api -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/boot/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/compiler/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/arch/ll/armcc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/intc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/led -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/uart -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/reg -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash_cache -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/flash -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/sysctrl/awo -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pshare -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/dmac -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/gpio -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/pwm -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/wdt -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/timer -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/rtc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/adc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/clk_gen -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/iic -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/patch -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/hw_ecc -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/qspi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/modem -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/driver/ssi/spi_master -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/sleep -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/. -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/bx_debug/log/RTT -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/jmp_table -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/patch_list -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/build/ble-full/reg/fw -IE:/KeilProject/SVN/Jmesh/trunk/plf/bx2400/src/cmsis_inc -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/include -IE:/KeilProject/SVN/Jmesh/trunk/freertos/src/portable/armcc/arm_cm0 -IE:/KeilProject/SVN/Jmesh/trunk/freertos/app -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/oled_iic -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/mems_spi -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/motor -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/temp -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/rgb_led -IE:/KeilProject/SVN/Jmesh/trunk/freertos/peripheral/uart_echo -IE:/KeilProject/SVN/Jmesh/trunk/freertos -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llm -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/llc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/lld -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/em -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/ll/src/rwble -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/hl/inc -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp/anps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/anp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/basc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas/bass/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bas -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp/blps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/blp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp/cpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp/cscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/cscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/disc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis/diss/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/dis -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findl/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find/findt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/find -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp/glps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/glp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpbh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogpd/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp/hogprh/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hogp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp/hrps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/hrp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp/htpt/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/htp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lanc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan/lans/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/lan -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/paspc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp/pasps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/pasp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxm/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox/proxr/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/prox -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscpc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp/rscps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/rscp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scppc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp/scpps/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/scpp -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tipc/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip/tips/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/tip -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota/bxotas/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ble/profiles/bxota -IE:/KeilProject/SVN/Jmesh/trunk/ip/hci/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ahi/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/ea/api -IE:/KeilProject/SVN/Jmesh/trunk/ip/em/api -DNDEBUG -D__BOOT_RAM__ -D__MICROLIB
    
    
    
    
    
    
    

====================================

** Section #14

    Name        : .shstrtab
    Type        : SHT_STRTAB (0x00000003)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 325108 (0x4f5f4)
    Size        : 148 bytes (0x94)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

address     size       variable name                            type
0x0012eabc  0x4        wakeup_pll                               uint32_t

address     size       variable name                            type
0x0012dff0  0x24       boot_info                                const boot_info_t
0x0012dff0  0x10       boot_info.boot_header                    boot_header_t
0x0012dff0  0x4        boot_info.boot_header.bx_flag            uint32_t
0x0012dff4  0x4        boot_info.boot_header.base_addr          pointer to uint8_t
0x0012dff8  0x4        boot_info.boot_header.length             uint32_t
0x0012dffc  0x4        boot_info.boot_header.entry_point        entry_point_t
0x0012e000  0x4        boot_info.image_offset                   uint32_t
0x0012e004  0x4        boot_info.image_size                     uint32_t
0x0012e008  0x4        boot_info.flash_qspi_enabled             uint32_t
0x0012e00c  0x4        boot_info.flash_xip                      uint32_t
0x0012e010  0x4        boot_info.valid_part                     uint32_t

