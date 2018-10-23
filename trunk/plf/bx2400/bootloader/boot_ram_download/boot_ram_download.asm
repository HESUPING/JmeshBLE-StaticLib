
========================================================================

** ELF Header Information

    File Name: .\Objects\boot_ram_download.axf

    Machine class: ELFCLASS32 (32-bit)
    Data encoding: ELFDATA2LSB (Little endian)
    Header version: EV_CURRENT (Current version)
    Operating System ABI: none
    ABI Version: 0
    File Type: ET_EXEC (Executable) (2)
    Machine: EM_ARM (ARM)

    Image Entry point: 0x0012a089
    Flags: EF_ARM_HASENTRY + EF_ARM_ABI_FLOAT_SOFT (0x05000202)

    ARM ELF revision: 5 (ABI version 2)

    Conforms to Soft float procedure-call standard

    Built with
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armasm [4d35ec]
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armlink [4d35ed]

    Header size: 52 bytes (0x34)
    Program header entry size: 32 bytes (0x20)
    Section header entry size: 40 bytes (0x28)

    Program header entries: 1
    Section header entries: 17

    Program header offset: 147780 (0x00024144)
    Section header offset: 147812 (0x00024164)

    Section header string table index: 16

========================================================================

** Program header #0

    Type          : PT_LOAD (1)
    File Offset   : 52 (0x34)
    Virtual Addr  : 0x00129ff0
    Physical Addr : 0x00129ff0
    Size in file  : 4388 bytes (0x1124)
    Size in memory: 15696 bytes (0x3d50)
    Flags         : PF_X + PF_W + PF_R + PF_ARM_ENTRY (0x80000007)
    Alignment     : 8


========================================================================

** Section #1

    Name        : BOOT_HEADER_SECTION
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : SHF_ALLOC (0x00000002)
    Addr        : 0x00129ff0
    File Offset : 52 (0x34)
    Size        : 16 bytes (0x10)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 4
    Entry Size  : 0

    0x129ff0:   42 58 32 34 00 a0 12 00 ff ff ff ff 9d a0 12 00    BX24............


====================================

** Section #2

    Name        : EXEC_SECTION
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : SHF_ALLOC + SHF_EXECINSTR (0x00000006)
    Addr        : 0x0012a000
    File Offset : 68 (0x44)
    Size        : 4344 bytes (0x10f8)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 4
    Entry Size  : 0

    $d.realdata
    RESET
    __Vectors
        0x0012a000:    0012dd40    @...    DCD    1236288
        0x0012a004:    0012a09d    ....    DCD    1220765
        0x0012a008:    0012a0b1    ....    DCD    1220785
        0x0012a00c:    0012a0b3    ....    DCD    1220787
        0x0012a010:    0012a0b5    ....    DCD    1220789
        0x0012a014:    0012a0b7    ....    DCD    1220791
        0x0012a018:    0012a0b9    ....    DCD    1220793
        0x0012a01c:    00000000    ....    DCD    0
        0x0012a020:    00000000    ....    DCD    0
        0x0012a024:    00000000    ....    DCD    0
        0x0012a028:    00000000    ....    DCD    0
        0x0012a02c:    0012a0bb    ....    DCD    1220795
        0x0012a030:    0012a0bd    ....    DCD    1220797
        0x0012a034:    00000000    ....    DCD    0
        0x0012a038:    0012a0bf    ....    DCD    1220799
        0x0012a03c:    0012a0c1    ....    DCD    1220801
        0x0012a040:    0012a0c3    ....    DCD    1220803
        0x0012a044:    0012a0c3    ....    DCD    1220803
        0x0012a048:    0012a0c3    ....    DCD    1220803
        0x0012a04c:    0012a0c3    ....    DCD    1220803
        0x0012a050:    0012a0c3    ....    DCD    1220803
        0x0012a054:    0012a0c3    ....    DCD    1220803
        0x0012a058:    0012a0c3    ....    DCD    1220803
        0x0012a05c:    0012a0c3    ....    DCD    1220803
        0x0012a060:    0012a0c3    ....    DCD    1220803
        0x0012a064:    0012a0c3    ....    DCD    1220803
        0x0012a068:    0012a0c3    ....    DCD    1220803
        0x0012a06c:    0012a12d    -...    DCD    1220909
        0x0012a070:    0012a0c3    ....    DCD    1220803
        0x0012a074:    0012a0c3    ....    DCD    1220803
        0x0012a078:    0012a0c3    ....    DCD    1220803
        0x0012a07c:    0012a0c3    ....    DCD    1220803
        0x0012a080:    0012a0c3    ....    DCD    1220803
        0x0012a084:    0012a0c3    ....    DCD    1220803
    $t
    .ARM.Collect$$$$00000000
    .ARM.Collect$$$$00000001
    __Vectors_End
    __main
    _main_stk
        0x0012a088:    4803        .H      LDR      r0,__lit__00000000 ; [0x12a098] = 0x12dd40
        0x0012a08a:    4685        .F      MOV      sp,r0
    .ARM.Collect$$$$00000004
    _main_scatterload
        0x0012a08c:    f000f824    ..$.    BL       __scatterload ; 0x12a0d8
    .ARM.Collect$$$$00000008
    .ARM.Collect$$$$0000000A
    .ARM.Collect$$$$0000000B
    __main_after_scatterload
    _main_clock
    _main_cpp_init
    _main_init
        0x0012a090:    4800        .H      LDR      r0,[pc,#0] ; [0x12a094] = 0x12a691
        0x0012a092:    4700        .G      BX       r0
    $d
        0x0012a094:    0012a691    ....    DCD    1222289
    .ARM.Collect$$$$00002712
    __lit__00000000
    .ARM.Collect$$$$0000000D
    .ARM.Collect$$$$0000000F
    __rt_final_cpp
    __rt_final_exit
        0x0012a098:    0012dd40    @...    DCD    1236288
    $t
    .text
    Reset_Handler
        0x0012a09c:    4809        .H      LDR      r0,[pc,#36] ; [0x12a0c4] = 0x12a0fd
        0x0012a09e:    4780        .G      BLX      r0
        0x0012a0a0:    4809        .H      LDR      r0,[pc,#36] ; [0x12a0c8] = 0x12a089
        0x0012a0a2:    4700        .G      BX       r0
    exception_exit
        0x0012a0a4:    4809        .H      LDR      r0,[pc,#36] ; [0x12a0cc] = 0x12a09d
        0x0012a0a6:    9006        ..      STR      r0,[sp,#0x18]
        0x0012a0a8:    4809        .H      LDR      r0,[pc,#36] ; [0x12a0d0] = 0xf1000000
        0x0012a0aa:    9007        ..      STR      r0,[sp,#0x1c]
        0x0012a0ac:    4809        .H      LDR      r0,[pc,#36] ; [0x12a0d4] = 0xfffffff9
        0x0012a0ae:    4700        .G      BX       r0
    NMI_Handler
        0x0012a0b0:    e7fe        ..      B        NMI_Handler ; 0x12a0b0
    HardFault_Handler
        0x0012a0b2:    e7fe        ..      B        HardFault_Handler ; 0x12a0b2
    MemManage_Handler
        0x0012a0b4:    e7fe        ..      B        MemManage_Handler ; 0x12a0b4
    BusFault_Handler
        0x0012a0b6:    e7fe        ..      B        BusFault_Handler ; 0x12a0b6
    UsageFault_Handler
        0x0012a0b8:    e7fe        ..      B        UsageFault_Handler ; 0x12a0b8
    SVC_Handler
        0x0012a0ba:    e7fe        ..      B        SVC_Handler ; 0x12a0ba
    DebugMon_Handler
        0x0012a0bc:    e7fe        ..      B        DebugMon_Handler ; 0x12a0bc
    PendSV_Handler
        0x0012a0be:    e7fe        ..      B        PendSV_Handler ; 0x12a0be
    SysTick_Handler
        0x0012a0c0:    e7fe        ..      B        SysTick_Handler ; 0x12a0c0
    BLE_LP_IRQHandler
    BLE_MAC_IRQHandler
    DMAC_IRQHandler
    ECC_IRQHandler
    EXT_INTR_IRQHandler
    GPIO_IRQHandler
    IIC0_IRQHandler
    IIC1_IRQHandler
    QSPI_IRQHandler
    RTC_IRQHandler
    SFT_IRQHandler
    SPIM0_IRQHandler
    SPIM1_IRQHandler
    SPIS_IRQHandler
    TIMER_IRQHandler
    UART1_IRQHandler
    WDT_IRQHandler
        0x0012a0c2:    e7fe        ..      B        BLE_LP_IRQHandler ; 0x12a0c2
    $d
        0x0012a0c4:    0012a0fd    ....    DCD    1220861
        0x0012a0c8:    0012a089    ....    DCD    1220745
        0x0012a0cc:    0012a09d    ....    DCD    1220765
        0x0012a0d0:    f1000000    ....    DCD    4043309056
        0x0012a0d4:    fffffff9    ....    DCD    4294967289
    $t
    .text
    __scatterload
    __scatterload_rt2
        0x0012a0d8:    4c06        .L      LDR      r4,[pc,#24] ; [0x12a0f4] = 0x12b0e8
        0x0012a0da:    2501        .%      MOVS     r5,#1
        0x0012a0dc:    4e06        .N      LDR      r6,[pc,#24] ; [0x12a0f8] = 0x12b0f8
        0x0012a0de:    e005        ..      B        0x12a0ec ; __scatterload + 20
        0x0012a0e0:    68e3        .h      LDR      r3,[r4,#0xc]
        0x0012a0e2:    cc07        ..      LDM      r4!,{r0-r2}
        0x0012a0e4:    432b        +C      ORRS     r3,r3,r5
        0x0012a0e6:    3c0c        .<      SUBS     r4,r4,#0xc
        0x0012a0e8:    4798        .G      BLX      r3
        0x0012a0ea:    3410        .4      ADDS     r4,r4,#0x10
        0x0012a0ec:    42b4        .B      CMP      r4,r6
        0x0012a0ee:    d3f7        ..      BCC      0x12a0e0 ; __scatterload + 8
        0x0012a0f0:    f7ffffce    ....    BL       __main_after_scatterload ; 0x12a090
    $d
        0x0012a0f4:    0012b0e8    ....    DCD    1224936
        0x0012a0f8:    0012b0f8    ....    DCD    1224952
    $t
    i.SystemInit
    SystemInit
        0x0012a0fc:    b530        0.      PUSH     {r4,r5,lr}
        0x0012a0fe:    bf00        ..      NOP      
        0x0012a100:    bf00        ..      NOP      
        0x0012a102:    bf00        ..      NOP      
        0x0012a104:    f3bf8f5f    .._.    DMB      
        0x0012a108:    bf00        ..      NOP      
        0x0012a10a:    bf00        ..      NOP      
        0x0012a10c:    bf00        ..      NOP      
        0x0012a10e:    2495        .$      MOVS     r4,#0x95
        0x0012a110:    0364        d.      LSLS     r4,r4,#13
        0x0012a112:    4d05        .M      LDR      r5,[pc,#20] ; [0x12a128] = 0xe000ed00
        0x0012a114:    60ac        .`      STR      r4,[r5,#8]
        0x0012a116:    bf00        ..      NOP      
        0x0012a118:    bf00        ..      NOP      
        0x0012a11a:    bf00        ..      NOP      
        0x0012a11c:    f3bf8f4f    ..O.    DSB      
        0x0012a120:    bf00        ..      NOP      
        0x0012a122:    bf00        ..      NOP      
        0x0012a124:    bf00        ..      NOP      
        0x0012a126:    bd30        0.      POP      {r4,r5,pc}
    $d
        0x0012a128:    e000ed00    ....    DCD    3758157056
    $t
    i.UART0_IRQHandler
    UART0_IRQHandler
        0x0012a12c:    b510        ..      PUSH     {r4,lr}
        0x0012a12e:    f000fd29    ..).    BL       uart_isr ; 0x12ab84
        0x0012a132:    bd10        ..      POP      {r4,pc}
    i.__scatterload_copy
    __scatterload_copy
        0x0012a134:    e002        ..      B        0x12a13c ; __scatterload_copy + 8
        0x0012a136:    c808        ..      LDM      r0!,{r3}
        0x0012a138:    1f12        ..      SUBS     r2,r2,#4
        0x0012a13a:    c108        ..      STM      r1!,{r3}
        0x0012a13c:    2a00        .*      CMP      r2,#0
        0x0012a13e:    d1fa        ..      BNE      0x12a136 ; __scatterload_copy + 2
        0x0012a140:    4770        pG      BX       lr
    i.__scatterload_null
    __scatterload_null
        0x0012a142:    4770        pG      BX       lr
    i.__scatterload_zeroinit
    __scatterload_zeroinit
        0x0012a144:    2000        .       MOVS     r0,#0
        0x0012a146:    e001        ..      B        0x12a14c ; __scatterload_zeroinit + 8
        0x0012a148:    c101        ..      STM      r1!,{r0}
        0x0012a14a:    1f12        ..      SUBS     r2,r2,#4
        0x0012a14c:    2a00        .*      CMP      r2,#0
        0x0012a14e:    d1fb        ..      BNE      0x12a148 ; __scatterload_zeroinit + 4
        0x0012a150:    4770        pG      BX       lr
    i.clk_uart0_921600
    clk_uart0_921600
        0x0012a152:    b510        ..      PUSH     {r4,lr}
        0x0012a154:    2001        .       MOVS     r0,#1
        0x0012a156:    0240        @.      LSLS     r0,r0,#9
        0x0012a158:    f000fc2e    ....    BL       sysc_per_clkg0_set ; 0x12a9b8
        0x0012a15c:    2302        .#      MOVS     r3,#2
        0x0012a15e:    2201        ."      MOVS     r2,#1
        0x0012a160:    4619        .F      MOV      r1,r3
        0x0012a162:    200c        .       MOVS     r0,#0xc
        0x0012a164:    f000fbb8    ....    BL       sysc_per_clk_div_param1_pack ; 0x12a8d8
        0x0012a168:    2001        .       MOVS     r0,#1
        0x0012a16a:    f000fbc1    ....    BL       sysc_per_clk_sel_uart0_setf ; 0x12a8f0
        0x0012a16e:    20ff        .       MOVS     r0,#0xff
        0x0012a170:    3001        .0      ADDS     r0,#1
        0x0012a172:    f000fc21    ..!.    BL       sysc_per_clkg0_set ; 0x12a9b8
        0x0012a176:    bd10        ..      POP      {r4,pc}
    i.dmac_block_ts_config
    dmac_block_ts_config
        0x0012a178:    b530        0.      PUSH     {r4,r5,lr}
        0x0012a17a:    4a15        .J      LDR      r2,[pc,#84] ; [0x12a1d0] = 0xfff
        0x0012a17c:    4290        .B      CMP      r0,r2
        0x0012a17e:    d913        ..      BLS      0x12a1a8 ; dmac_block_ts_config + 48
        0x0012a180:    bf00        ..      NOP      
        0x0012a182:    2458        X$      MOVS     r4,#0x58
        0x0012a184:    434c        LC      MULS     r4,r1,r4
        0x0012a186:    4d13        .M      LDR      r5,[pc,#76] ; [0x12a1d4] = 0x20120000
        0x0012a188:    1964        d.      ADDS     r4,r4,r5
        0x0012a18a:    69e2        .i      LDR      r2,[r4,#0x1c]
        0x0012a18c:    0b14        ..      LSRS     r4,r2,#12
        0x0012a18e:    0324        $.      LSLS     r4,r4,#12
        0x0012a190:    4d0f        .M      LDR      r5,[pc,#60] ; [0x12a1d0] = 0xfff
        0x0012a192:    432c        ,C      ORRS     r4,r4,r5
        0x0012a194:    4623        #F      MOV      r3,r4
        0x0012a196:    2458        X$      MOVS     r4,#0x58
        0x0012a198:    434c        LC      MULS     r4,r1,r4
        0x0012a19a:    4d0e        .M      LDR      r5,[pc,#56] ; [0x12a1d4] = 0x20120000
        0x0012a19c:    1964        d.      ADDS     r4,r4,r5
        0x0012a19e:    61e3        .a      STR      r3,[r4,#0x1c]
        0x0012a1a0:    bf00        ..      NOP      
        0x0012a1a2:    4a0b        .J      LDR      r2,[pc,#44] ; [0x12a1d0] = 0xfff
        0x0012a1a4:    1a80        ..      SUBS     r0,r0,r2
        0x0012a1a6:    e012        ..      B        0x12a1ce ; dmac_block_ts_config + 86
        0x0012a1a8:    bf00        ..      NOP      
        0x0012a1aa:    2458        X$      MOVS     r4,#0x58
        0x0012a1ac:    434c        LC      MULS     r4,r1,r4
        0x0012a1ae:    4d09        .M      LDR      r5,[pc,#36] ; [0x12a1d4] = 0x20120000
        0x0012a1b0:    1964        d.      ADDS     r4,r4,r5
        0x0012a1b2:    69e2        .i      LDR      r2,[r4,#0x1c]
        0x0012a1b4:    0504        ..      LSLS     r4,r0,#20
        0x0012a1b6:    0d24        $.      LSRS     r4,r4,#20
        0x0012a1b8:    0b15        ..      LSRS     r5,r2,#12
        0x0012a1ba:    032d        -.      LSLS     r5,r5,#12
        0x0012a1bc:    432c        ,C      ORRS     r4,r4,r5
        0x0012a1be:    4623        #F      MOV      r3,r4
        0x0012a1c0:    2458        X$      MOVS     r4,#0x58
        0x0012a1c2:    434c        LC      MULS     r4,r1,r4
        0x0012a1c4:    4d03        .M      LDR      r5,[pc,#12] ; [0x12a1d4] = 0x20120000
        0x0012a1c6:    1964        d.      ADDS     r4,r4,r5
        0x0012a1c8:    61e3        .a      STR      r3,[r4,#0x1c]
        0x0012a1ca:    bf00        ..      NOP      
        0x0012a1cc:    2000        .       MOVS     r0,#0
        0x0012a1ce:    bd30        0.      POP      {r4,r5,pc}
    $d
        0x0012a1d0:    00000fff    ....    DCD    4095
        0x0012a1d4:    20120000    ...     DCD    538050560
    $t
    i.dmac_init
    dmac_init
        0x0012a1d8:    2001        .       MOVS     r0,#1
        0x0012a1da:    4903        .I      LDR      r1,[pc,#12] ; [0x12a1e8] = 0x20120380
        0x0012a1dc:    6188        .a      STR      r0,[r1,#0x18]
        0x0012a1de:    20ff        .       MOVS     r0,#0xff
        0x0012a1e0:    4901        .I      LDR      r1,[pc,#4] ; [0x12a1e8] = 0x20120380
        0x0012a1e2:    3980        .9      SUBS     r1,r1,#0x80
        0x0012a1e4:    6388        .c      STR      r0,[r1,#0x38]
        0x0012a1e6:    4770        pG      BX       lr
    $d
        0x0012a1e8:    20120380    ...     DCD    538051456
    $t
    i.dmac_start
    dmac_start
        0x0012a1ec:    b5f8        ..      PUSH     {r3-r7,lr}
        0x0012a1ee:    4604        .F      MOV      r4,r0
        0x0012a1f0:    460d        .F      MOV      r5,r1
        0x0012a1f2:    4629        )F      MOV      r1,r5
        0x0012a1f4:    68a0        .h      LDR      r0,[r4,#8]
        0x0012a1f6:    f7ffffbf    ....    BL       dmac_block_ts_config ; 0x12a178
        0x0012a1fa:    9000        ..      STR      r0,[sp,#0]
        0x0012a1fc:    89a0        ..      LDRH     r0,[r4,#0xc]
        0x0012a1fe:    0440        @.      LSLS     r0,r0,#17
        0x0012a200:    0f40        @.      LSRS     r0,r0,#29
        0x0012a202:    2800        .(      CMP      r0,#0
        0x0012a204:    d009        ..      BEQ      0x12a21a ; dmac_start + 46
        0x0012a206:    2801        .(      CMP      r0,#1
        0x0012a208:    d004        ..      BEQ      0x12a214 ; dmac_start + 40
        0x0012a20a:    2802        .(      CMP      r0,#2
        0x0012a20c:    d108        ..      BNE      0x12a220 ; dmac_start + 52
        0x0012a20e:    2602        .&      MOVS     r6,#2
        0x0012a210:    2700        .'      MOVS     r7,#0
        0x0012a212:    e006        ..      B        0x12a222 ; dmac_start + 54
        0x0012a214:    2600        .&      MOVS     r6,#0
        0x0012a216:    2702        .'      MOVS     r7,#2
        0x0012a218:    e003        ..      B        0x12a222 ; dmac_start + 54
        0x0012a21a:    2600        .&      MOVS     r6,#0
        0x0012a21c:    2700        .'      MOVS     r7,#0
        0x0012a21e:    e000        ..      B        0x12a222 ; dmac_start + 54
        0x0012a220:    bf00        ..      NOP      
        0x0012a222:    bf00        ..      NOP      
        0x0012a224:    89a0        ..      LDRH     r0,[r4,#0xc]
        0x0012a226:    0440        @.      LSLS     r0,r0,#17
        0x0012a228:    0f40        @.      LSRS     r0,r0,#29
        0x0012a22a:    0500        ..      LSLS     r0,r0,#20
        0x0012a22c:    2103        .!      MOVS     r1,#3
        0x0012a22e:    0509        ..      LSLS     r1,r1,#20
        0x0012a230:    4008        .@      ANDS     r0,r0,r1
        0x0012a232:    89a1        ..      LDRH     r1,[r4,#0xc]
        0x0012a234:    05c9        ..      LSLS     r1,r1,#23
        0x0012a236:    0f49        I.      LSRS     r1,r1,#29
        0x0012a238:    0389        ..      LSLS     r1,r1,#14
        0x0012a23a:    2207        ."      MOVS     r2,#7
        0x0012a23c:    0392        ..      LSLS     r2,r2,#14
        0x0012a23e:    4011        .@      ANDS     r1,r1,r2
        0x0012a240:    4308        .C      ORRS     r0,r0,r1
        0x0012a242:    89a1        ..      LDRH     r1,[r4,#0xc]
        0x0012a244:    0509        ..      LSLS     r1,r1,#20
        0x0012a246:    0f49        I.      LSRS     r1,r1,#29
        0x0012a248:    02c9        ..      LSLS     r1,r1,#11
        0x0012a24a:    10d2        ..      ASRS     r2,r2,#3
        0x0012a24c:    4011        .@      ANDS     r1,r1,r2
        0x0012a24e:    4308        .C      ORRS     r0,r0,r1
        0x0012a250:    0271        q.      LSLS     r1,r6,#9
        0x0012a252:    2203        ."      MOVS     r2,#3
        0x0012a254:    0252        R.      LSLS     r2,r2,#9
        0x0012a256:    4011        .@      ANDS     r1,r1,r2
        0x0012a258:    4308        .C      ORRS     r0,r0,r1
        0x0012a25a:    01f9        ..      LSLS     r1,r7,#7
        0x0012a25c:    1092        ..      ASRS     r2,r2,#2
        0x0012a25e:    4011        .@      ANDS     r1,r1,r2
        0x0012a260:    4308        .C      ORRS     r0,r0,r1
        0x0012a262:    68e1        .h      LDR      r1,[r4,#0xc]
        0x0012a264:    0109        ..      LSLS     r1,r1,#4
        0x0012a266:    2270        p"      MOVS     r2,#0x70
        0x0012a268:    4011        .@      ANDS     r1,r1,r2
        0x0012a26a:    4308        .C      ORRS     r0,r0,r1
        0x0012a26c:    7b21        !{      LDRB     r1,[r4,#0xc]
        0x0012a26e:    0689        ..      LSLS     r1,r1,#26
        0x0012a270:    0f49        I.      LSRS     r1,r1,#29
        0x0012a272:    0049        I.      LSLS     r1,r1,#1
        0x0012a274:    220e        ."      MOVS     r2,#0xe
        0x0012a276:    4011        .@      ANDS     r1,r1,r2
        0x0012a278:    4308        .C      ORRS     r0,r0,r1
        0x0012a27a:    2158        X!      MOVS     r1,#0x58
        0x0012a27c:    4369        iC      MULS     r1,r5,r1
        0x0012a27e:    4a1b        .J      LDR      r2,[pc,#108] ; [0x12a2ec] = 0x20120000
        0x0012a280:    1889        ..      ADDS     r1,r1,r2
        0x0012a282:    6188        .a      STR      r0,[r1,#0x18]
        0x0012a284:    2100        .!      MOVS     r1,#0
        0x0012a286:    2058        X       MOVS     r0,#0x58
        0x0012a288:    4368        hC      MULS     r0,r5,r0
        0x0012a28a:    1880        ..      ADDS     r0,r0,r2
        0x0012a28c:    6401        .d      STR      r1,[r0,#0x40]
        0x0012a28e:    68e0        .h      LDR      r0,[r4,#0xc]
        0x0012a290:    0240        @.      LSLS     r0,r0,#9
        0x0012a292:    0f00        ..      LSRS     r0,r0,#28
        0x0012a294:    02c0        ..      LSLS     r0,r0,#11
        0x0012a296:    210f        .!      MOVS     r1,#0xf
        0x0012a298:    02c9        ..      LSLS     r1,r1,#11
        0x0012a29a:    4008        .@      ANDS     r0,r0,r1
        0x0012a29c:    68e1        .h      LDR      r1,[r4,#0xc]
        0x0012a29e:    0349        I.      LSLS     r1,r1,#13
        0x0012a2a0:    0f09        ..      LSRS     r1,r1,#28
        0x0012a2a2:    01c9        ..      LSLS     r1,r1,#7
        0x0012a2a4:    220f        ."      MOVS     r2,#0xf
        0x0012a2a6:    01d2        ..      LSLS     r2,r2,#7
        0x0012a2a8:    4011        .@      ANDS     r1,r1,r2
        0x0012a2aa:    4308        .C      ORRS     r0,r0,r1
        0x0012a2ac:    1c80        ..      ADDS     r0,r0,#2
        0x0012a2ae:    2158        X!      MOVS     r1,#0x58
        0x0012a2b0:    4369        iC      MULS     r1,r5,r1
        0x0012a2b2:    4a0e        .J      LDR      r2,[pc,#56] ; [0x12a2ec] = 0x20120000
        0x0012a2b4:    1889        ..      ADDS     r1,r1,r2
        0x0012a2b6:    6448        Hd      STR      r0,[r1,#0x44]
        0x0012a2b8:    2058        X       MOVS     r0,#0x58
        0x0012a2ba:    4368        hC      MULS     r0,r5,r0
        0x0012a2bc:    1880        ..      ADDS     r0,r0,r2
        0x0012a2be:    6821        !h      LDR      r1,[r4,#0]
        0x0012a2c0:    6001        .`      STR      r1,[r0,#0]
        0x0012a2c2:    2058        X       MOVS     r0,#0x58
        0x0012a2c4:    4368        hC      MULS     r0,r5,r0
        0x0012a2c6:    1880        ..      ADDS     r0,r0,r2
        0x0012a2c8:    6861        ah      LDR      r1,[r4,#4]
        0x0012a2ca:    6081        .`      STR      r1,[r0,#8]
        0x0012a2cc:    2001        .       MOVS     r0,#1
        0x0012a2ce:    40a8        .@      LSLS     r0,r0,r5
        0x0012a2d0:    0680        ..      LSLS     r0,r0,#26
        0x0012a2d2:    0e80        ..      LSRS     r0,r0,#26
        0x0012a2d4:    2101        .!      MOVS     r1,#1
        0x0012a2d6:    40a9        .@      LSLS     r1,r1,r5
        0x0012a2d8:    0209        ..      LSLS     r1,r1,#8
        0x0012a2da:    223f        ?"      MOVS     r2,#0x3f
        0x0012a2dc:    0212        ..      LSLS     r2,r2,#8
        0x0012a2de:    4011        .@      ANDS     r1,r1,r2
        0x0012a2e0:    4308        .C      ORRS     r0,r0,r1
        0x0012a2e2:    4903        .I      LDR      r1,[pc,#12] ; [0x12a2f0] = 0x20120380
        0x0012a2e4:    6208        .b      STR      r0,[r1,#0x20]
        0x0012a2e6:    9800        ..      LDR      r0,[sp,#0]
        0x0012a2e8:    bdf8        ..      POP      {r3-r7,pc}
    $d
        0x0012a2ea:    0000        ..      DCW    0
        0x0012a2ec:    20120000    ...     DCD    538050560
        0x0012a2f0:    20120380    ...     DCD    538051456
    $t
    i.dmac_transfer_wait
    dmac_transfer_wait
        0x0012a2f4:    b570        p.      PUSH     {r4-r6,lr}
        0x0012a2f6:    4605        .F      MOV      r5,r0
        0x0012a2f8:    460c        .F      MOV      r4,r1
        0x0012a2fa:    bf00        ..      NOP      
        0x0012a2fc:    4817        .H      LDR      r0,[pc,#92] ; [0x12a35c] = 0x201202c0
        0x0012a2fe:    6800        .h      LDR      r0,[r0,#0]
        0x0012a300:    2101        .!      MOVS     r1,#1
        0x0012a302:    40a1        .@      LSLS     r1,r1,r4
        0x0012a304:    4008        .@      ANDS     r0,r0,r1
        0x0012a306:    2800        .(      CMP      r0,#0
        0x0012a308:    d0f8        ..      BEQ      0x12a2fc ; dmac_transfer_wait + 8
        0x0012a30a:    2001        .       MOVS     r0,#1
        0x0012a30c:    40a0        .@      LSLS     r0,r0,r4
        0x0012a30e:    4913        .I      LDR      r1,[pc,#76] ; [0x12a35c] = 0x201202c0
        0x0012a310:    3140        @1      ADDS     r1,r1,#0x40
        0x0012a312:    6388        .c      STR      r0,[r1,#0x38]
        0x0012a314:    e01f        ..      B        0x12a356 ; dmac_transfer_wait + 98
        0x0012a316:    4621        !F      MOV      r1,r4
        0x0012a318:    4628        (F      MOV      r0,r5
        0x0012a31a:    f7ffff2d    ..-.    BL       dmac_block_ts_config ; 0x12a178
        0x0012a31e:    4605        .F      MOV      r5,r0
        0x0012a320:    2001        .       MOVS     r0,#1
        0x0012a322:    40a0        .@      LSLS     r0,r0,r4
        0x0012a324:    0680        ..      LSLS     r0,r0,#26
        0x0012a326:    0e80        ..      LSRS     r0,r0,#26
        0x0012a328:    2101        .!      MOVS     r1,#1
        0x0012a32a:    40a1        .@      LSLS     r1,r1,r4
        0x0012a32c:    0209        ..      LSLS     r1,r1,#8
        0x0012a32e:    223f        ?"      MOVS     r2,#0x3f
        0x0012a330:    0212        ..      LSLS     r2,r2,#8
        0x0012a332:    4011        .@      ANDS     r1,r1,r2
        0x0012a334:    4308        .C      ORRS     r0,r0,r1
        0x0012a336:    4909        .I      LDR      r1,[pc,#36] ; [0x12a35c] = 0x201202c0
        0x0012a338:    31c0        .1      ADDS     r1,r1,#0xc0
        0x0012a33a:    6208        .b      STR      r0,[r1,#0x20]
        0x0012a33c:    bf00        ..      NOP      
        0x0012a33e:    4807        .H      LDR      r0,[pc,#28] ; [0x12a35c] = 0x201202c0
        0x0012a340:    6800        .h      LDR      r0,[r0,#0]
        0x0012a342:    2101        .!      MOVS     r1,#1
        0x0012a344:    40a1        .@      LSLS     r1,r1,r4
        0x0012a346:    4008        .@      ANDS     r0,r0,r1
        0x0012a348:    2800        .(      CMP      r0,#0
        0x0012a34a:    d0f8        ..      BEQ      0x12a33e ; dmac_transfer_wait + 74
        0x0012a34c:    2001        .       MOVS     r0,#1
        0x0012a34e:    40a0        .@      LSLS     r0,r0,r4
        0x0012a350:    4902        .I      LDR      r1,[pc,#8] ; [0x12a35c] = 0x201202c0
        0x0012a352:    3140        @1      ADDS     r1,r1,#0x40
        0x0012a354:    6388        .c      STR      r0,[r1,#0x38]
        0x0012a356:    2d00        .-      CMP      r5,#0
        0x0012a358:    d1dd        ..      BNE      0x12a316 ; dmac_transfer_wait + 34
        0x0012a35a:    bd70        p.      POP      {r4-r6,pc}
    $d
        0x0012a35c:    201202c0    ...     DCD    538051264
    $t
    i.flash_erase
    flash_erase
        0x0012a360:    b5f8        ..      PUSH     {r3-r7,lr}
        0x0012a362:    4604        .F      MOV      r4,r0
        0x0012a364:    460d        .F      MOV      r5,r1
        0x0012a366:    f000f98b    ....    BL       flash_write_enable ; 0x12a680
        0x0012a36a:    2d03        .-      CMP      r5,#3
        0x0012a36c:    d108        ..      BNE      0x12a380 ; flash_erase + 32
        0x0012a36e:    a022        ".      ADR      r0,{pc}+0x8a ; 0x12a3f8
        0x0012a370:    6800        .h      LDR      r0,[r0,#0]
        0x0012a372:    9000        ..      STR      r0,[sp,#0]
        0x0012a374:    2601        .&      MOVS     r6,#1
        0x0012a376:    4631        1F      MOV      r1,r6
        0x0012a378:    4668        hF      MOV      r0,sp
        0x0012a37a:    f000fa9d    ....    BL       qspi_std_write ; 0x12a8b8
        0x0012a37e:    e036        6.      B        0x12a3ee ; flash_erase + 142
        0x0012a380:    2d02        .-      CMP      r5,#2
        0x0012a382:    d110        ..      BNE      0x12a3a6 ; flash_erase + 70
        0x0012a384:    a01d        ..      ADR      r0,{pc}+0x78 ; 0x12a3fc
        0x0012a386:    6800        .h      LDR      r0,[r0,#0]
        0x0012a388:    9000        ..      STR      r0,[sp,#0]
        0x0012a38a:    0220         .      LSLS     r0,r4,#8
        0x0012a38c:    0e01        ..      LSRS     r1,r0,#24
        0x0012a38e:    4668        hF      MOV      r0,sp
        0x0012a390:    7041        Ap      STRB     r1,[r0,#1]
        0x0012a392:    0420         .      LSLS     r0,r4,#16
        0x0012a394:    0e01        ..      LSRS     r1,r0,#24
        0x0012a396:    4668        hF      MOV      r0,sp
        0x0012a398:    7081        .p      STRB     r1,[r0,#2]
        0x0012a39a:    70c4        .p      STRB     r4,[r0,#3]
        0x0012a39c:    2604        .&      MOVS     r6,#4
        0x0012a39e:    4631        1F      MOV      r1,r6
        0x0012a3a0:    f000fa8a    ....    BL       qspi_std_write ; 0x12a8b8
        0x0012a3a4:    e023        #.      B        0x12a3ee ; flash_erase + 142
        0x0012a3a6:    2d01        .-      CMP      r5,#1
        0x0012a3a8:    d110        ..      BNE      0x12a3cc ; flash_erase + 108
        0x0012a3aa:    a015        ..      ADR      r0,{pc}+0x56 ; 0x12a400
        0x0012a3ac:    6800        .h      LDR      r0,[r0,#0]
        0x0012a3ae:    9000        ..      STR      r0,[sp,#0]
        0x0012a3b0:    0220         .      LSLS     r0,r4,#8
        0x0012a3b2:    0e01        ..      LSRS     r1,r0,#24
        0x0012a3b4:    4668        hF      MOV      r0,sp
        0x0012a3b6:    7041        Ap      STRB     r1,[r0,#1]
        0x0012a3b8:    0420         .      LSLS     r0,r4,#16
        0x0012a3ba:    0e01        ..      LSRS     r1,r0,#24
        0x0012a3bc:    4668        hF      MOV      r0,sp
        0x0012a3be:    7081        .p      STRB     r1,[r0,#2]
        0x0012a3c0:    70c4        .p      STRB     r4,[r0,#3]
        0x0012a3c2:    2604        .&      MOVS     r6,#4
        0x0012a3c4:    4631        1F      MOV      r1,r6
        0x0012a3c6:    f000fa77    ..w.    BL       qspi_std_write ; 0x12a8b8
        0x0012a3ca:    e010        ..      B        0x12a3ee ; flash_erase + 142
        0x0012a3cc:    a00d        ..      ADR      r0,{pc}+0x38 ; 0x12a404
        0x0012a3ce:    6800        .h      LDR      r0,[r0,#0]
        0x0012a3d0:    9000        ..      STR      r0,[sp,#0]
        0x0012a3d2:    0220         .      LSLS     r0,r4,#8
        0x0012a3d4:    0e01        ..      LSRS     r1,r0,#24
        0x0012a3d6:    4668        hF      MOV      r0,sp
        0x0012a3d8:    7041        Ap      STRB     r1,[r0,#1]
        0x0012a3da:    0420         .      LSLS     r0,r4,#16
        0x0012a3dc:    0e01        ..      LSRS     r1,r0,#24
        0x0012a3de:    4668        hF      MOV      r0,sp
        0x0012a3e0:    7081        .p      STRB     r1,[r0,#2]
        0x0012a3e2:    70c4        .p      STRB     r4,[r0,#3]
        0x0012a3e4:    2604        .&      MOVS     r6,#4
        0x0012a3e6:    4631        1F      MOV      r1,r6
        0x0012a3e8:    f000fa66    ..f.    BL       qspi_std_write ; 0x12a8b8
        0x0012a3ec:    bf00        ..      NOP      
        0x0012a3ee:    f000f80b    ....    BL       flash_operation_wait ; 0x12a408
        0x0012a3f2:    2000        .       MOVS     r0,#0
        0x0012a3f4:    bdf8        ..      POP      {r3-r7,pc}
    $d
        0x0012a3f6:    0000        ..      DCW    0
        0x0012a3f8:    00000060    `...    DCD    96
        0x0012a3fc:    000000d8    ....    DCD    216
        0x0012a400:    00000052    R...    DCD    82
        0x0012a404:    00000020     ...    DCD    32
    $t
    i.flash_operation_wait
    flash_operation_wait
        0x0012a408:    b51c        ..      PUSH     {r2-r4,lr}
        0x0012a40a:    2005        .       MOVS     r0,#5
        0x0012a40c:    9000        ..      STR      r0,[sp,#0]
        0x0012a40e:    bf00        ..      NOP      
        0x0012a410:    2301        .#      MOVS     r3,#1
        0x0012a412:    aa01        ..      ADD      r2,sp,#4
        0x0012a414:    4619        .F      MOV      r1,r3
        0x0012a416:    4668        hF      MOV      r0,sp
        0x0012a418:    f000fa0c    ....    BL       qspi_std_read ; 0x12a834
        0x0012a41c:    4668        hF      MOV      r0,sp
        0x0012a41e:    7900        .y      LDRB     r0,[r0,#4]
        0x0012a420:    07c0        ..      LSLS     r0,r0,#31
        0x0012a422:    0fc0        ..      LSRS     r0,r0,#31
        0x0012a424:    2800        .(      CMP      r0,#0
        0x0012a426:    d1f3        ..      BNE      0x12a410 ; flash_operation_wait + 8
        0x0012a428:    4668        hF      MOV      r0,sp
        0x0012a42a:    7900        .y      LDRB     r0,[r0,#4]
        0x0012a42c:    bd1c        ..      POP      {r2-r4,pc}
    i.flash_program
    flash_program
        0x0012a42e:    b5f0        ..      PUSH     {r4-r7,lr}
        0x0012a430:    b085        ..      SUB      sp,sp,#0x14
        0x0012a432:    4604        .F      MOV      r4,r0
        0x0012a434:    460d        .F      MOV      r5,r1
        0x0012a436:    4617        .F      MOV      r7,r2
        0x0012a438:    0a20         .      LSRS     r0,r4,#8
        0x0012a43a:    0200        ..      LSLS     r0,r0,#8
        0x0012a43c:    9004        ..      STR      r0,[sp,#0x10]
        0x0012a43e:    9804        ..      LDR      r0,[sp,#0x10]
        0x0012a440:    42a0        .B      CMP      r0,r4
        0x0012a442:    d014        ..      BEQ      0x12a46e ; flash_program + 64
        0x0012a444:    9804        ..      LDR      r0,[sp,#0x10]
        0x0012a446:    30ff        .0      ADDS     r0,r0,#0xff
        0x0012a448:    3001        .0      ADDS     r0,#1
        0x0012a44a:    1b00        ..      SUBS     r0,r0,r4
        0x0012a44c:    9000        ..      STR      r0,[sp,#0]
        0x0012a44e:    9800        ..      LDR      r0,[sp,#0]
        0x0012a450:    4285        .B      CMP      r5,r0
        0x0012a452:    d201        ..      BCS      0x12a458 ; flash_program + 42
        0x0012a454:    4628        (F      MOV      r0,r5
        0x0012a456:    e000        ..      B        0x12a45a ; flash_program + 44
        0x0012a458:    9800        ..      LDR      r0,[sp,#0]
        0x0012a45a:    4606        .F      MOV      r6,r0
        0x0012a45c:    463a        :F      MOV      r2,r7
        0x0012a45e:    4631        1F      MOV      r1,r6
        0x0012a460:    4620         F      MOV      r0,r4
        0x0012a462:    f000f829    ..).    BL       flash_program_base ; 0x12a4b8
        0x0012a466:    19bf        ..      ADDS     r7,r7,r6
        0x0012a468:    19a4        ..      ADDS     r4,r4,r6
        0x0012a46a:    1bad        ..      SUBS     r5,r5,r6
        0x0012a46c:    bf00        ..      NOP      
        0x0012a46e:    0228        (.      LSLS     r0,r5,#8
        0x0012a470:    0c00        ..      LSRS     r0,r0,#16
        0x0012a472:    9003        ..      STR      r0,[sp,#0xc]
        0x0012a474:    b2e8        ..      UXTB     r0,r5
        0x0012a476:    9002        ..      STR      r0,[sp,#8]
        0x0012a478:    2000        .       MOVS     r0,#0
        0x0012a47a:    9001        ..      STR      r0,[sp,#4]
        0x0012a47c:    e00d        ..      B        0x12a49a ; flash_program + 108
        0x0012a47e:    463a        :F      MOV      r2,r7
        0x0012a480:    21ff        .!      MOVS     r1,#0xff
        0x0012a482:    3101        .1      ADDS     r1,#1
        0x0012a484:    4620         F      MOV      r0,r4
        0x0012a486:    f000f817    ....    BL       flash_program_base ; 0x12a4b8
        0x0012a48a:    34ff        .4      ADDS     r4,r4,#0xff
        0x0012a48c:    3401        .4      ADDS     r4,#1
        0x0012a48e:    37ff        .7      ADDS     r7,r7,#0xff
        0x0012a490:    3701        .7      ADDS     r7,#1
        0x0012a492:    9801        ..      LDR      r0,[sp,#4]
        0x0012a494:    1c40        @.      ADDS     r0,r0,#1
        0x0012a496:    b280        ..      UXTH     r0,r0
        0x0012a498:    9001        ..      STR      r0,[sp,#4]
        0x0012a49a:    9903        ..      LDR      r1,[sp,#0xc]
        0x0012a49c:    9801        ..      LDR      r0,[sp,#4]
        0x0012a49e:    4288        .B      CMP      r0,r1
        0x0012a4a0:    dbed        ..      BLT      0x12a47e ; flash_program + 80
        0x0012a4a2:    9802        ..      LDR      r0,[sp,#8]
        0x0012a4a4:    2800        .(      CMP      r0,#0
        0x0012a4a6:    d004        ..      BEQ      0x12a4b2 ; flash_program + 132
        0x0012a4a8:    463a        :F      MOV      r2,r7
        0x0012a4aa:    4620         F      MOV      r0,r4
        0x0012a4ac:    9902        ..      LDR      r1,[sp,#8]
        0x0012a4ae:    f000f803    ....    BL       flash_program_base ; 0x12a4b8
        0x0012a4b2:    2000        .       MOVS     r0,#0
        0x0012a4b4:    b005        ..      ADD      sp,sp,#0x14
        0x0012a4b6:    bdf0        ..      POP      {r4-r7,pc}
    i.flash_program_base
    flash_program_base
        0x0012a4b8:    b570        p.      PUSH     {r4-r6,lr}
        0x0012a4ba:    4604        .F      MOV      r4,r0
        0x0012a4bc:    460d        .F      MOV      r5,r1
        0x0012a4be:    4616        .F      MOV      r6,r2
        0x0012a4c0:    f000f8de    ....    BL       flash_write_enable ; 0x12a680
        0x0012a4c4:    462b        +F      MOV      r3,r5
        0x0012a4c6:    4632        2F      MOV      r2,r6
        0x0012a4c8:    4621        !F      MOV      r1,r4
        0x0012a4ca:    2002        .       MOVS     r0,#2
        0x0012a4cc:    f000f940    ..@.    BL       qspi_flash_program ; 0x12a750
        0x0012a4d0:    f7ffff9a    ....    BL       flash_operation_wait ; 0x12a408
        0x0012a4d4:    bd70        p.      POP      {r4-r6,pc}
        0x0012a4d6:    0000        ..      MOVS     r0,r0
    i.flash_read
    flash_read
        0x0012a4d8:    b5fe        ..      PUSH     {r1-r7,lr}
        0x0012a4da:    4604        .F      MOV      r4,r0
        0x0012a4dc:    460d        .F      MOV      r5,r1
        0x0012a4de:    4616        .F      MOV      r6,r2
        0x0012a4e0:    0c28        (.      LSRS     r0,r5,#16
        0x0012a4e2:    9002        ..      STR      r0,[sp,#8]
        0x0012a4e4:    b2af        ..      UXTH     r7,r5
        0x0012a4e6:    2000        .       MOVS     r0,#0
        0x0012a4e8:    9001        ..      STR      r0,[sp,#4]
        0x0012a4ea:    e019        ..      B        0x12a520 ; flash_read + 72
        0x0012a4ec:    a019        ..      ADR      r0,{pc}+0x68 ; 0x12a554
        0x0012a4ee:    6800        .h      LDR      r0,[r0,#0]
        0x0012a4f0:    9000        ..      STR      r0,[sp,#0]
        0x0012a4f2:    0220         .      LSLS     r0,r4,#8
        0x0012a4f4:    0e01        ..      LSRS     r1,r0,#24
        0x0012a4f6:    4668        hF      MOV      r0,sp
        0x0012a4f8:    7041        Ap      STRB     r1,[r0,#1]
        0x0012a4fa:    0420         .      LSLS     r0,r4,#16
        0x0012a4fc:    0e01        ..      LSRS     r1,r0,#24
        0x0012a4fe:    4668        hF      MOV      r0,sp
        0x0012a500:    7081        .p      STRB     r1,[r0,#2]
        0x0012a502:    70c4        .p      STRB     r4,[r0,#3]
        0x0012a504:    2301        .#      MOVS     r3,#1
        0x0012a506:    041b        ..      LSLS     r3,r3,#16
        0x0012a508:    4632        2F      MOV      r2,r6
        0x0012a50a:    2104        .!      MOVS     r1,#4
        0x0012a50c:    f000f992    ....    BL       qspi_std_read ; 0x12a834
        0x0012a510:    2001        .       MOVS     r0,#1
        0x0012a512:    0400        ..      LSLS     r0,r0,#16
        0x0012a514:    1824        $.      ADDS     r4,r4,r0
        0x0012a516:    1836        6.      ADDS     r6,r6,r0
        0x0012a518:    9801        ..      LDR      r0,[sp,#4]
        0x0012a51a:    1c40        @.      ADDS     r0,r0,#1
        0x0012a51c:    b280        ..      UXTH     r0,r0
        0x0012a51e:    9001        ..      STR      r0,[sp,#4]
        0x0012a520:    9902        ..      LDR      r1,[sp,#8]
        0x0012a522:    9801        ..      LDR      r0,[sp,#4]
        0x0012a524:    4288        .B      CMP      r0,r1
        0x0012a526:    dbe1        ..      BLT      0x12a4ec ; flash_read + 20
        0x0012a528:    2f00        ./      CMP      r7,#0
        0x0012a52a:    d011        ..      BEQ      0x12a550 ; flash_read + 120
        0x0012a52c:    a009        ..      ADR      r0,{pc}+0x28 ; 0x12a554
        0x0012a52e:    6800        .h      LDR      r0,[r0,#0]
        0x0012a530:    9000        ..      STR      r0,[sp,#0]
        0x0012a532:    0220         .      LSLS     r0,r4,#8
        0x0012a534:    0e01        ..      LSRS     r1,r0,#24
        0x0012a536:    4668        hF      MOV      r0,sp
        0x0012a538:    7041        Ap      STRB     r1,[r0,#1]
        0x0012a53a:    0420         .      LSLS     r0,r4,#16
        0x0012a53c:    0e01        ..      LSRS     r1,r0,#24
        0x0012a53e:    4668        hF      MOV      r0,sp
        0x0012a540:    7081        .p      STRB     r1,[r0,#2]
        0x0012a542:    70c4        .p      STRB     r4,[r0,#3]
        0x0012a544:    463b        ;F      MOV      r3,r7
        0x0012a546:    4632        2F      MOV      r2,r6
        0x0012a548:    2104        .!      MOVS     r1,#4
        0x0012a54a:    f000f973    ..s.    BL       qspi_std_read ; 0x12a834
        0x0012a54e:    bf00        ..      NOP      
        0x0012a550:    2000        .       MOVS     r0,#0
        0x0012a552:    bdfe        ..      POP      {r1-r7,pc}
    $d
        0x0012a554:    00000003    ....    DCD    3
    $t
    i.flash_status_read
    flash_status_read
        0x0012a558:    b51c        ..      PUSH     {r2-r4,lr}
        0x0012a55a:    4604        .F      MOV      r4,r0
        0x0012a55c:    2000        .       MOVS     r0,#0
        0x0012a55e:    9000        ..      STR      r0,[sp,#0]
        0x0012a560:    2c00        .,      CMP      r4,#0
        0x0012a562:    d004        ..      BEQ      0x12a56e ; flash_status_read + 22
        0x0012a564:    2c01        .,      CMP      r4,#1
        0x0012a566:    d00b        ..      BEQ      0x12a580 ; flash_status_read + 40
        0x0012a568:    2c02        .,      CMP      r4,#2
        0x0012a56a:    d11b        ..      BNE      0x12a5a4 ; flash_status_read + 76
        0x0012a56c:    e011        ..      B        0x12a592 ; flash_status_read + 58
        0x0012a56e:    2005        .       MOVS     r0,#5
        0x0012a570:    9000        ..      STR      r0,[sp,#0]
        0x0012a572:    2301        .#      MOVS     r3,#1
        0x0012a574:    aa01        ..      ADD      r2,sp,#4
        0x0012a576:    4619        .F      MOV      r1,r3
        0x0012a578:    4668        hF      MOV      r0,sp
        0x0012a57a:    f000f95b    ..[.    BL       qspi_std_read ; 0x12a834
        0x0012a57e:    e012        ..      B        0x12a5a6 ; flash_status_read + 78
        0x0012a580:    2035        5       MOVS     r0,#0x35
        0x0012a582:    9000        ..      STR      r0,[sp,#0]
        0x0012a584:    2301        .#      MOVS     r3,#1
        0x0012a586:    aa01        ..      ADD      r2,sp,#4
        0x0012a588:    4619        .F      MOV      r1,r3
        0x0012a58a:    4668        hF      MOV      r0,sp
        0x0012a58c:    f000f952    ..R.    BL       qspi_std_read ; 0x12a834
        0x0012a590:    e009        ..      B        0x12a5a6 ; flash_status_read + 78
        0x0012a592:    2015        .       MOVS     r0,#0x15
        0x0012a594:    9000        ..      STR      r0,[sp,#0]
        0x0012a596:    2301        .#      MOVS     r3,#1
        0x0012a598:    aa01        ..      ADD      r2,sp,#4
        0x0012a59a:    4619        .F      MOV      r1,r3
        0x0012a59c:    4668        hF      MOV      r0,sp
        0x0012a59e:    f000f949    ..I.    BL       qspi_std_read ; 0x12a834
        0x0012a5a2:    e000        ..      B        0x12a5a6 ; flash_status_read + 78
        0x0012a5a4:    bf00        ..      NOP      
        0x0012a5a6:    bf00        ..      NOP      
        0x0012a5a8:    4668        hF      MOV      r0,sp
        0x0012a5aa:    7900        .y      LDRB     r0,[r0,#4]
        0x0012a5ac:    bd1c        ..      POP      {r2-r4,pc}
        0x0012a5ae:    0000        ..      MOVS     r0,r0
    i.flash_status_write
    flash_status_write
        0x0012a5b0:    b5f8        ..      PUSH     {r3-r7,lr}
        0x0012a5b2:    4604        .F      MOV      r4,r0
        0x0012a5b4:    460d        .F      MOV      r5,r1
        0x0012a5b6:    a020         .      ADR      r0,{pc}+0x82 ; 0x12a638
        0x0012a5b8:    6800        .h      LDR      r0,[r0,#0]
        0x0012a5ba:    9000        ..      STR      r0,[sp,#0]
        0x0012a5bc:    4668        hF      MOV      r0,sp
        0x0012a5be:    7045        Ep      STRB     r5,[r0,#1]
        0x0012a5c0:    2600        .&      MOVS     r6,#0
        0x0012a5c2:    2c00        .,      CMP      r4,#0
        0x0012a5c4:    d004        ..      BEQ      0x12a5d0 ; flash_status_write + 32
        0x0012a5c6:    2c01        .,      CMP      r4,#1
        0x0012a5c8:    d012        ..      BEQ      0x12a5f0 ; flash_status_write + 64
        0x0012a5ca:    2c02        .,      CMP      r4,#2
        0x0012a5cc:    d130        0.      BNE      0x12a630 ; flash_status_write + 128
        0x0012a5ce:    e01f        ..      B        0x12a610 ; flash_status_write + 96
        0x0012a5d0:    f000f856    ..V.    BL       flash_write_enable ; 0x12a680
        0x0012a5d4:    2001        .       MOVS     r0,#1
        0x0012a5d6:    4669        iF      MOV      r1,sp
        0x0012a5d8:    7008        .p      STRB     r0,[r1,#0]
        0x0012a5da:    2102        .!      MOVS     r1,#2
        0x0012a5dc:    4668        hF      MOV      r0,sp
        0x0012a5de:    f000f96b    ..k.    BL       qspi_std_write ; 0x12a8b8
        0x0012a5e2:    f7ffff11    ....    BL       flash_operation_wait ; 0x12a408
        0x0012a5e6:    4620         F      MOV      r0,r4
        0x0012a5e8:    f7ffffb6    ....    BL       flash_status_read ; 0x12a558
        0x0012a5ec:    4606        .F      MOV      r6,r0
        0x0012a5ee:    e020         .      B        0x12a632 ; flash_status_write + 130
        0x0012a5f0:    f000f846    ..F.    BL       flash_write_enable ; 0x12a680
        0x0012a5f4:    2031        1       MOVS     r0,#0x31
        0x0012a5f6:    4669        iF      MOV      r1,sp
        0x0012a5f8:    7008        .p      STRB     r0,[r1,#0]
        0x0012a5fa:    2102        .!      MOVS     r1,#2
        0x0012a5fc:    4668        hF      MOV      r0,sp
        0x0012a5fe:    f000f95b    ..[.    BL       qspi_std_write ; 0x12a8b8
        0x0012a602:    f7ffff01    ....    BL       flash_operation_wait ; 0x12a408
        0x0012a606:    4620         F      MOV      r0,r4
        0x0012a608:    f7ffffa6    ....    BL       flash_status_read ; 0x12a558
        0x0012a60c:    4606        .F      MOV      r6,r0
        0x0012a60e:    e010        ..      B        0x12a632 ; flash_status_write + 130
        0x0012a610:    f000f836    ..6.    BL       flash_write_enable ; 0x12a680
        0x0012a614:    2011        .       MOVS     r0,#0x11
        0x0012a616:    4669        iF      MOV      r1,sp
        0x0012a618:    7008        .p      STRB     r0,[r1,#0]
        0x0012a61a:    2102        .!      MOVS     r1,#2
        0x0012a61c:    4668        hF      MOV      r0,sp
        0x0012a61e:    f000f94b    ..K.    BL       qspi_std_write ; 0x12a8b8
        0x0012a622:    f7fffef1    ....    BL       flash_operation_wait ; 0x12a408
        0x0012a626:    4620         F      MOV      r0,r4
        0x0012a628:    f7ffff96    ....    BL       flash_status_read ; 0x12a558
        0x0012a62c:    4606        .F      MOV      r6,r0
        0x0012a62e:    e000        ..      B        0x12a632 ; flash_status_write + 130
        0x0012a630:    bf00        ..      NOP      
        0x0012a632:    bf00        ..      NOP      
        0x0012a634:    4630        0F      MOV      r0,r6
        0x0012a636:    bdf8        ..      POP      {r3-r7,pc}
    $d
        0x0012a638:    00000031    1...    DCD    49
    $t
    i.flash_status_write_2bytes
    flash_status_write_2bytes
        0x0012a63c:    b5f8        ..      PUSH     {r3-r7,lr}
        0x0012a63e:    4604        .F      MOV      r4,r0
        0x0012a640:    460d        .F      MOV      r5,r1
        0x0012a642:    a00e        ..      ADR      r0,{pc}+0x3a ; 0x12a67c
        0x0012a644:    6800        .h      LDR      r0,[r0,#0]
        0x0012a646:    9000        ..      STR      r0,[sp,#0]
        0x0012a648:    4668        hF      MOV      r0,sp
        0x0012a64a:    7044        Dp      STRB     r4,[r0,#1]
        0x0012a64c:    7085        .p      STRB     r5,[r0,#2]
        0x0012a64e:    2600        .&      MOVS     r6,#0
        0x0012a650:    f000f816    ....    BL       flash_write_enable ; 0x12a680
        0x0012a654:    2103        .!      MOVS     r1,#3
        0x0012a656:    4668        hF      MOV      r0,sp
        0x0012a658:    f000f92e    ....    BL       qspi_std_write ; 0x12a8b8
        0x0012a65c:    f7fffed4    ....    BL       flash_operation_wait ; 0x12a408
        0x0012a660:    2000        .       MOVS     r0,#0
        0x0012a662:    f7ffff79    ..y.    BL       flash_status_read ; 0x12a558
        0x0012a666:    4606        .F      MOV      r6,r0
        0x0012a668:    2001        .       MOVS     r0,#1
        0x0012a66a:    f7ffff75    ..u.    BL       flash_status_read ; 0x12a558
        0x0012a66e:    0200        ..      LSLS     r0,r0,#8
        0x0012a670:    21ff        .!      MOVS     r1,#0xff
        0x0012a672:    0209        ..      LSLS     r1,r1,#8
        0x0012a674:    4008        .@      ANDS     r0,r0,r1
        0x0012a676:    4306        .C      ORRS     r6,r6,r0
        0x0012a678:    4630        0F      MOV      r0,r6
        0x0012a67a:    bdf8        ..      POP      {r3-r7,pc}
    $d
        0x0012a67c:    00000001    ....    DCD    1
    $t
    i.flash_write_enable
    flash_write_enable
        0x0012a680:    b508        ..      PUSH     {r3,lr}
        0x0012a682:    2006        .       MOVS     r0,#6
        0x0012a684:    9000        ..      STR      r0,[sp,#0]
        0x0012a686:    2101        .!      MOVS     r1,#1
        0x0012a688:    4668        hF      MOV      r0,sp
        0x0012a68a:    f000f915    ....    BL       qspi_std_write ; 0x12a8b8
        0x0012a68e:    bd08        ..      POP      {r3,pc}
    i.main
    main
        0x0012a690:    2022        "       MOVS     r0,#0x22
        0x0012a692:    4913        .I      LDR      r1,[pc,#76] ; [0x12a6e0] = 0x130100
        0x0012a694:    6008        .`      STR      r0,[r1,#0]
        0x0012a696:    f000f82b    ..+.    BL       open_pinshare ; 0x12a6f0
        0x0012a69a:    f7fffd9d    ....    BL       dmac_init ; 0x12a1d8
        0x0012a69e:    2101        .!      MOVS     r1,#1
        0x0012a6a0:    2002        .       MOVS     r0,#2
        0x0012a6a2:    f000f875    ..u.    BL       qspi_init ; 0x12a790
        0x0012a6a6:    f000f99b    ....    BL       uart_download_init ; 0x12a9e0
        0x0012a6aa:    f000fcab    ....    BL       uart_sync_to_pc ; 0x12b004
        0x0012a6ae:    bf00        ..      NOP      
        0x0012a6b0:    480c        .H      LDR      r0,[pc,#48] ; [0x12a6e4] = 0x12b0fa
        0x0012a6b2:    7800        .x      LDRB     r0,[r0,#0]
        0x0012a6b4:    2800        .(      CMP      r0,#0
        0x0012a6b6:    d0fb        ..      BEQ      0x12a6b0 ; main + 32
        0x0012a6b8:    f000f9b8    ....    BL       uart_download_start ; 0x12aa2c
        0x0012a6bc:    bf00        ..      NOP      
        0x0012a6be:    480a        .H      LDR      r0,[pc,#40] ; [0x12a6e8] = 0x12b0f8
        0x0012a6c0:    7800        .x      LDRB     r0,[r0,#0]
        0x0012a6c2:    2800        .(      CMP      r0,#0
        0x0012a6c4:    d0fb        ..      BEQ      0x12a6be ; main + 46
        0x0012a6c6:    bf00        ..      NOP      
        0x0012a6c8:    4808        .H      LDR      r0,[pc,#32] ; [0x12a6ec] = 0x12b0f9
        0x0012a6ca:    7800        .x      LDRB     r0,[r0,#0]
        0x0012a6cc:    2800        .(      CMP      r0,#0
        0x0012a6ce:    d0fb        ..      BEQ      0x12a6c8 ; main + 56
        0x0012a6d0:    4806        .H      LDR      r0,[pc,#24] ; [0x12a6ec] = 0x12b0f9
        0x0012a6d2:    7800        .x      LDRB     r0,[r0,#0]
        0x0012a6d4:    2801        .(      CMP      r0,#1
        0x0012a6d6:    d001        ..      BEQ      0x12a6dc ; main + 76
        0x0012a6d8:    bf00        ..      NOP      
        0x0012a6da:    e7fe        ..      B        0x12a6da ; main + 74
        0x0012a6dc:    bf00        ..      NOP      
        0x0012a6de:    e7fe        ..      B        0x12a6de ; main + 78
    $d
        0x0012a6e0:    00130100    ....    DCD    1245440
        0x0012a6e4:    0012b0fa    ....    DCD    1224954
        0x0012a6e8:    0012b0f8    ....    DCD    1224952
        0x0012a6ec:    0012b0f9    ....    DCD    1224953
    $t
    i.open_pinshare
    open_pinshare
        0x0012a6f0:    2003        .       MOVS     r0,#3
        0x0012a6f2:    4916        .I      LDR      r1,[pc,#88] ; [0x12a74c] = 0x20132000
        0x0012a6f4:    6a09        .j      LDR      r1,[r1,#0x20]
        0x0012a6f6:    0909        ..      LSRS     r1,r1,#4
        0x0012a6f8:    0109        ..      LSLS     r1,r1,#4
        0x0012a6fa:    4301        .C      ORRS     r1,r1,r0
        0x0012a6fc:    4a13        .J      LDR      r2,[pc,#76] ; [0x12a74c] = 0x20132000
        0x0012a6fe:    6211        .b      STR      r1,[r2,#0x20]
        0x0012a700:    bf00        ..      NOP      
        0x0012a702:    2000        .       MOVS     r0,#0
        0x0012a704:    4611        .F      MOV      r1,r2
        0x0012a706:    6b49        Ik      LDR      r1,[r1,#0x34]
        0x0012a708:    220f        ."      MOVS     r2,#0xf
        0x0012a70a:    0212        ..      LSLS     r2,r2,#8
        0x0012a70c:    4391        .C      BICS     r1,r1,r2
        0x0012a70e:    0202        ..      LSLS     r2,r0,#8
        0x0012a710:    230f        .#      MOVS     r3,#0xf
        0x0012a712:    021b        ..      LSLS     r3,r3,#8
        0x0012a714:    401a        .@      ANDS     r2,r2,r3
        0x0012a716:    4311        .C      ORRS     r1,r1,r2
        0x0012a718:    4a0c        .J      LDR      r2,[pc,#48] ; [0x12a74c] = 0x20132000
        0x0012a71a:    6351        Qc      STR      r1,[r2,#0x34]
        0x0012a71c:    bf00        ..      NOP      
        0x0012a71e:    2001        .       MOVS     r0,#1
        0x0012a720:    4611        .F      MOV      r1,r2
        0x0012a722:    6b49        Ik      LDR      r1,[r1,#0x34]
        0x0012a724:    011a        ..      LSLS     r2,r3,#4
        0x0012a726:    4391        .C      BICS     r1,r1,r2
        0x0012a728:    0302        ..      LSLS     r2,r0,#12
        0x0012a72a:    011b        ..      LSLS     r3,r3,#4
        0x0012a72c:    401a        .@      ANDS     r2,r2,r3
        0x0012a72e:    4311        .C      ORRS     r1,r1,r2
        0x0012a730:    4a06        .J      LDR      r2,[pc,#24] ; [0x12a74c] = 0x20132000
        0x0012a732:    6351        Qc      STR      r1,[r2,#0x34]
        0x0012a734:    bf00        ..      NOP      
        0x0012a736:    2003        .       MOVS     r0,#3
        0x0012a738:    0280        ..      LSLS     r0,r0,#10
        0x0012a73a:    4611        .F      MOV      r1,r2
        0x0012a73c:    6a49        Ij      LDR      r1,[r1,#0x24]
        0x0012a73e:    0d89        ..      LSRS     r1,r1,#22
        0x0012a740:    0589        ..      LSLS     r1,r1,#22
        0x0012a742:    4301        .C      ORRS     r1,r1,r0
        0x0012a744:    6251        Qb      STR      r1,[r2,#0x24]
        0x0012a746:    bf00        ..      NOP      
        0x0012a748:    4770        pG      BX       lr
    $d
        0x0012a74a:    0000        ..      DCW    0
        0x0012a74c:    20132000    . .     DCD    538124288
    $t
    i.qspi_flash_program
    qspi_flash_program
        0x0012a750:    b5f8        ..      PUSH     {r3-r7,lr}
        0x0012a752:    4605        .F      MOV      r5,r0
        0x0012a754:    460c        .F      MOV      r4,r1
        0x0012a756:    4616        .F      MOV      r6,r2
        0x0012a758:    461f        .F      MOV      r7,r3
        0x0012a75a:    2140        @!      MOVS     r1,#0x40
        0x0012a75c:    480b        .H      LDR      r0,[pc,#44] ; [0x12a78c] = 0x20300000
        0x0012a75e:    f000f82b    ..+.    BL       qspi_std_byte_write_dma_config ; 0x12a7b8
        0x0012a762:    480a        .H      LDR      r0,[pc,#40] ; [0x12a78c] = 0x20300000
        0x0012a764:    3040        @0      ADDS     r0,r0,#0x40
        0x0012a766:    6205        .b      STR      r5,[r0,#0x20]
        0x0012a768:    0220         .      LSLS     r0,r4,#8
        0x0012a76a:    0e00        ..      LSRS     r0,r0,#24
        0x0012a76c:    4907        .I      LDR      r1,[pc,#28] ; [0x12a78c] = 0x20300000
        0x0012a76e:    3140        @1      ADDS     r1,r1,#0x40
        0x0012a770:    6208        .b      STR      r0,[r1,#0x20]
        0x0012a772:    0420         .      LSLS     r0,r4,#16
        0x0012a774:    0e00        ..      LSRS     r0,r0,#24
        0x0012a776:    6208        .b      STR      r0,[r1,#0x20]
        0x0012a778:    b2e0        ..      UXTB     r0,r4
        0x0012a77a:    6208        .b      STR      r0,[r1,#0x20]
        0x0012a77c:    463b        ;F      MOV      r3,r7
        0x0012a77e:    4632        2F      MOV      r2,r6
        0x0012a780:    2101        .!      MOVS     r1,#1
        0x0012a782:    4802        .H      LDR      r0,[pc,#8] ; [0x12a78c] = 0x20300000
        0x0012a784:    f000f826    ..&.    BL       qspi_std_byte_write_dma_start ; 0x12a7d4
        0x0012a788:    bdf8        ..      POP      {r3-r7,pc}
    $d
        0x0012a78a:    0000        ..      DCW    0
        0x0012a78c:    20300000    ..0     DCD    540016640
    $t
    i.qspi_init
    qspi_init
        0x0012a790:    2200        ."      MOVS     r2,#0
        0x0012a792:    4b07        .K      LDR      r3,[pc,#28] ; [0x12a7b0] = 0x20300000
        0x0012a794:    609a        .`      STR      r2,[r3,#8]
        0x0012a796:    461a        .F      MOV      r2,r3
        0x0012a798:    6150        Pa      STR      r0,[r2,#0x14]
        0x0012a79a:    4a05        .J      LDR      r2,[pc,#20] ; [0x12a7b0] = 0x20300000
        0x0012a79c:    32c0        .2      ADDS     r2,r2,#0xc0
        0x0012a79e:    6311        .c      STR      r1,[r2,#0x30]
        0x0012a7a0:    4a04        .J      LDR      r2,[pc,#16] ; [0x12a7b4] = 0x4218
        0x0012a7a2:    4b03        .K      LDR      r3,[pc,#12] ; [0x12a7b0] = 0x20300000
        0x0012a7a4:    33c0        .3      ADDS     r3,r3,#0xc0
        0x0012a7a6:    635a        Zc      STR      r2,[r3,#0x34]
        0x0012a7a8:    2200        ."      MOVS     r2,#0
        0x0012a7aa:    4b01        .K      LDR      r3,[pc,#4] ; [0x12a7b0] = 0x20300000
        0x0012a7ac:    611a        .a      STR      r2,[r3,#0x10]
        0x0012a7ae:    4770        pG      BX       lr
    $d
        0x0012a7b0:    20300000    ..0     DCD    540016640
        0x0012a7b4:    00004218    .B..    DCD    16920
    $t
    i.qspi_std_byte_write_dma_config
    qspi_std_byte_write_dma_config
        0x0012a7b8:    4a05        .J      LDR      r2,[pc,#20] ; [0x12a7d0] = 0x70100
        0x0012a7ba:    6002        .`      STR      r2,[r0,#0]
        0x0012a7bc:    1f0a        ..      SUBS     r2,r1,#4
        0x0012a7be:    6502        .e      STR      r2,[r0,#0x50]
        0x0012a7c0:    2200        ."      MOVS     r2,#0
        0x0012a7c2:    64c2        .d      STR      r2,[r0,#0x4c]
        0x0012a7c4:    2202        ."      MOVS     r2,#2
        0x0012a7c6:    64c2        .d      STR      r2,[r0,#0x4c]
        0x0012a7c8:    2201        ."      MOVS     r2,#1
        0x0012a7ca:    6082        .`      STR      r2,[r0,#8]
        0x0012a7cc:    4770        pG      BX       lr
    $d
        0x0012a7ce:    0000        ..      DCW    0
        0x0012a7d0:    00070100    ....    DCD    459008
    $t
    i.qspi_std_byte_write_dma_start
    qspi_std_byte_write_dma_start
        0x0012a7d4:    b5f0        ..      PUSH     {r4-r7,lr}
        0x0012a7d6:    b085        ..      SUB      sp,sp,#0x14
        0x0012a7d8:    4604        .F      MOV      r4,r0
        0x0012a7da:    460d        .F      MOV      r5,r1
        0x0012a7dc:    4616        .F      MOV      r6,r2
        0x0012a7de:    461f        .F      MOV      r7,r3
        0x0012a7e0:    4813        .H      LDR      r0,[pc,#76] ; [0x12a830] = 0x12b0b8
        0x0012a7e2:    4601        .F      MOV      r1,r0
        0x0012a7e4:    c90e        ..      LDM      r1,{r1-r3}
        0x0012a7e6:    68c0        .h      LDR      r0,[r0,#0xc]
        0x0012a7e8:    9303        ..      STR      r3,[sp,#0xc]
        0x0012a7ea:    9202        ..      STR      r2,[sp,#8]
        0x0012a7ec:    9101        ..      STR      r1,[sp,#4]
        0x0012a7ee:    9004        ..      STR      r0,[sp,#0x10]
        0x0012a7f0:    9601        ..      STR      r6,[sp,#4]
        0x0012a7f2:    4620         F      MOV      r0,r4
        0x0012a7f4:    3060        `0      ADDS     r0,r0,#0x60
        0x0012a7f6:    9002        ..      STR      r0,[sp,#8]
        0x0012a7f8:    9703        ..      STR      r7,[sp,#0xc]
        0x0012a7fa:    2100        .!      MOVS     r1,#0
        0x0012a7fc:    a801        ..      ADD      r0,sp,#4
        0x0012a7fe:    f7fffcf5    ....    BL       dmac_start ; 0x12a1ec
        0x0012a802:    9000        ..      STR      r0,[sp,#0]
        0x0012a804:    6125        %a      STR      r5,[r4,#0x10]
        0x0012a806:    2100        .!      MOVS     r1,#0
        0x0012a808:    9800        ..      LDR      r0,[sp,#0]
        0x0012a80a:    f7fffd73    ..s.    BL       dmac_transfer_wait ; 0x12a2f4
        0x0012a80e:    bf00        ..      NOP      
        0x0012a810:    6aa0        .j      LDR      r0,[r4,#0x28]
        0x0012a812:    2104        .!      MOVS     r1,#4
        0x0012a814:    4008        .@      ANDS     r0,r0,r1
        0x0012a816:    0880        ..      LSRS     r0,r0,#2
        0x0012a818:    2800        .(      CMP      r0,#0
        0x0012a81a:    d0f9        ..      BEQ      0x12a810 ; qspi_std_byte_write_dma_start + 60
        0x0012a81c:    bf00        ..      NOP      
        0x0012a81e:    6aa0        .j      LDR      r0,[r4,#0x28]
        0x0012a820:    07c0        ..      LSLS     r0,r0,#31
        0x0012a822:    0fc0        ..      LSRS     r0,r0,#31
        0x0012a824:    2800        .(      CMP      r0,#0
        0x0012a826:    d1fa        ..      BNE      0x12a81e ; qspi_std_byte_write_dma_start + 74
        0x0012a828:    60a0        .`      STR      r0,[r4,#8]
        0x0012a82a:    6120         a      STR      r0,[r4,#0x10]
        0x0012a82c:    b005        ..      ADD      sp,sp,#0x14
        0x0012a82e:    bdf0        ..      POP      {r4-r7,pc}
    $d
        0x0012a830:    0012b0b8    ....    DCD    1224888
    $t
    i.qspi_std_read
    qspi_std_read
        0x0012a834:    b5ff        ..      PUSH     {r0-r7,lr}
        0x0012a836:    b085        ..      SUB      sp,sp,#0x14
        0x0012a838:    4606        .F      MOV      r6,r0
        0x0012a83a:    460f        .F      MOV      r7,r1
        0x0012a83c:    461c        .F      MOV      r4,r3
        0x0012a83e:    481b        .H      LDR      r0,[pc,#108] ; [0x12a8ac] = 0x70300
        0x0012a840:    491b        .I      LDR      r1,[pc,#108] ; [0x12a8b0] = 0x20300000
        0x0012a842:    6008        .`      STR      r0,[r1,#0]
        0x0012a844:    1e60        `.      SUBS     r0,r4,#1
        0x0012a846:    6048        H`      STR      r0,[r1,#4]
        0x0012a848:    2007        .       MOVS     r0,#7
        0x0012a84a:    4919        .I      LDR      r1,[pc,#100] ; [0x12a8b0] = 0x20300000
        0x0012a84c:    3140        @1      ADDS     r1,r1,#0x40
        0x0012a84e:    6148        Ha      STR      r0,[r1,#0x14]
        0x0012a850:    2000        .       MOVS     r0,#0
        0x0012a852:    60c8        .`      STR      r0,[r1,#0xc]
        0x0012a854:    2001        .       MOVS     r0,#1
        0x0012a856:    60c8        .`      STR      r0,[r1,#0xc]
        0x0012a858:    4915        .I      LDR      r1,[pc,#84] ; [0x12a8b0] = 0x20300000
        0x0012a85a:    6088        .`      STR      r0,[r1,#8]
        0x0012a85c:    2500        .%      MOVS     r5,#0
        0x0012a85e:    e005        ..      B        0x12a86c ; qspi_std_read + 56
        0x0012a860:    5d70        p]      LDRB     r0,[r6,r5]
        0x0012a862:    4913        .I      LDR      r1,[pc,#76] ; [0x12a8b0] = 0x20300000
        0x0012a864:    3140        @1      ADDS     r1,r1,#0x40
        0x0012a866:    6208        .b      STR      r0,[r1,#0x20]
        0x0012a868:    1c68        h.      ADDS     r0,r5,#1
        0x0012a86a:    b2c5        ..      UXTB     r5,r0
        0x0012a86c:    42bd        .B      CMP      r5,r7
        0x0012a86e:    dbf7        ..      BLT      0x12a860 ; qspi_std_read + 44
        0x0012a870:    4810        .H      LDR      r0,[pc,#64] ; [0x12a8b4] = 0x12b0c8
        0x0012a872:    4601        .F      MOV      r1,r0
        0x0012a874:    c90e        ..      LDM      r1,{r1-r3}
        0x0012a876:    68c0        .h      LDR      r0,[r0,#0xc]
        0x0012a878:    9303        ..      STR      r3,[sp,#0xc]
        0x0012a87a:    9202        ..      STR      r2,[sp,#8]
        0x0012a87c:    9101        ..      STR      r1,[sp,#4]
        0x0012a87e:    9004        ..      STR      r0,[sp,#0x10]
        0x0012a880:    9807        ..      LDR      r0,[sp,#0x1c]
        0x0012a882:    9002        ..      STR      r0,[sp,#8]
        0x0012a884:    9403        ..      STR      r4,[sp,#0xc]
        0x0012a886:    2100        .!      MOVS     r1,#0
        0x0012a888:    a801        ..      ADD      r0,sp,#4
        0x0012a88a:    f7fffcaf    ....    BL       dmac_start ; 0x12a1ec
        0x0012a88e:    9000        ..      STR      r0,[sp,#0]
        0x0012a890:    2001        .       MOVS     r0,#1
        0x0012a892:    4907        .I      LDR      r1,[pc,#28] ; [0x12a8b0] = 0x20300000
        0x0012a894:    6108        .a      STR      r0,[r1,#0x10]
        0x0012a896:    2100        .!      MOVS     r1,#0
        0x0012a898:    9800        ..      LDR      r0,[sp,#0]
        0x0012a89a:    f7fffd2b    ..+.    BL       dmac_transfer_wait ; 0x12a2f4
        0x0012a89e:    2000        .       MOVS     r0,#0
        0x0012a8a0:    4903        .I      LDR      r1,[pc,#12] ; [0x12a8b0] = 0x20300000
        0x0012a8a2:    6088        .`      STR      r0,[r1,#8]
        0x0012a8a4:    6108        .a      STR      r0,[r1,#0x10]
        0x0012a8a6:    b009        ..      ADD      sp,sp,#0x24
        0x0012a8a8:    bdf0        ..      POP      {r4-r7,pc}
    $d
        0x0012a8aa:    0000        ..      DCW    0
        0x0012a8ac:    00070300    ....    DCD    459520
        0x0012a8b0:    20300000    ..0     DCD    540016640
        0x0012a8b4:    0012b0c8    ....    DCD    1224904
    $t
    i.qspi_std_write
    qspi_std_write
        0x0012a8b8:    b570        p.      PUSH     {r4-r6,lr}
        0x0012a8ba:    4604        .F      MOV      r4,r0
        0x0012a8bc:    460d        .F      MOV      r5,r1
        0x0012a8be:    2140        @!      MOVS     r1,#0x40
        0x0012a8c0:    4804        .H      LDR      r0,[pc,#16] ; [0x12a8d4] = 0x20300000
        0x0012a8c2:    f7ffff79    ..y.    BL       qspi_std_byte_write_dma_config ; 0x12a7b8
        0x0012a8c6:    462b        +F      MOV      r3,r5
        0x0012a8c8:    4622        "F      MOV      r2,r4
        0x0012a8ca:    2101        .!      MOVS     r1,#1
        0x0012a8cc:    4801        .H      LDR      r0,[pc,#4] ; [0x12a8d4] = 0x20300000
        0x0012a8ce:    f7ffff81    ....    BL       qspi_std_byte_write_dma_start ; 0x12a7d4
        0x0012a8d2:    bd70        p.      POP      {r4-r6,pc}
    $d
        0x0012a8d4:    20300000    ..0     DCD    540016640
    $t
    i.sysc_per_clk_div_param1_pack
    sysc_per_clk_div_param1_pack
        0x0012a8d8:    b530        0.      PUSH     {r4,r5,lr}
        0x0012a8da:    0604        ..      LSLS     r4,r0,#24
        0x0012a8dc:    040d        ..      LSLS     r5,r1,#16
        0x0012a8de:    432c        ,C      ORRS     r4,r4,r5
        0x0012a8e0:    0215        ..      LSLS     r5,r2,#8
        0x0012a8e2:    432c        ,C      ORRS     r4,r4,r5
        0x0012a8e4:    431c        .C      ORRS     r4,r4,r3
        0x0012a8e6:    4d01        .M      LDR      r5,[pc,#4] ; [0x12a8ec] = 0x20149000
        0x0012a8e8:    60ac        .`      STR      r4,[r5,#8]
        0x0012a8ea:    bd30        0.      POP      {r4,r5,pc}
    $d
        0x0012a8ec:    20149000    ...     DCD    538218496
    $t
    i.sysc_per_clk_sel_uart0_setf
    sysc_per_clk_sel_uart0_setf
        0x0012a8f0:    4906        .I      LDR      r1,[pc,#24] ; [0x12a90c] = 0x20149000
        0x0012a8f2:    6809        .h      LDR      r1,[r1,#0]
        0x0012a8f4:    2203        ."      MOVS     r2,#3
        0x0012a8f6:    0212        ..      LSLS     r2,r2,#8
        0x0012a8f8:    4391        .C      BICS     r1,r1,r2
        0x0012a8fa:    0202        ..      LSLS     r2,r0,#8
        0x0012a8fc:    2303        .#      MOVS     r3,#3
        0x0012a8fe:    021b        ..      LSLS     r3,r3,#8
        0x0012a900:    401a        .@      ANDS     r2,r2,r3
        0x0012a902:    4311        .C      ORRS     r1,r1,r2
        0x0012a904:    4a01        .J      LDR      r2,[pc,#4] ; [0x12a90c] = 0x20149000
        0x0012a906:    6011        .`      STR      r1,[r2,#0]
        0x0012a908:    4770        pG      BX       lr
    $d
        0x0012a90a:    0000        ..      DCW    0
        0x0012a90c:    20149000    ...     DCD    538218496
    $t
    i.sysc_per_clkg0_pack
    sysc_per_clkg0_pack
        0x0012a910:    b5f0        ..      PUSH     {r4-r7,lr}
        0x0012a912:    9d06        ..      LDR      r5,[sp,#0x18]
        0x0012a914:    9c05        ..      LDR      r4,[sp,#0x14]
        0x0012a916:    06c6        ..      LSLS     r6,r0,#27
        0x0012a918:    068f        ..      LSLS     r7,r1,#26
        0x0012a91a:    433e        >C      ORRS     r6,r6,r7
        0x0012a91c:    0657        W.      LSLS     r7,r2,#25
        0x0012a91e:    433e        >C      ORRS     r6,r6,r7
        0x0012a920:    061f        ..      LSLS     r7,r3,#24
        0x0012a922:    433e        >C      ORRS     r6,r6,r7
        0x0012a924:    05e7        ..      LSLS     r7,r4,#23
        0x0012a926:    433e        >C      ORRS     r6,r6,r7
        0x0012a928:    05af        ..      LSLS     r7,r5,#22
        0x0012a92a:    433e        >C      ORRS     r6,r6,r7
        0x0012a92c:    9f07        ..      LDR      r7,[sp,#0x1c]
        0x0012a92e:    057f        ..      LSLS     r7,r7,#21
        0x0012a930:    433e        >C      ORRS     r6,r6,r7
        0x0012a932:    9f08        ..      LDR      r7,[sp,#0x20]
        0x0012a934:    053f        ?.      LSLS     r7,r7,#20
        0x0012a936:    433e        >C      ORRS     r6,r6,r7
        0x0012a938:    9f09        ..      LDR      r7,[sp,#0x24]
        0x0012a93a:    04ff        ..      LSLS     r7,r7,#19
        0x0012a93c:    433e        >C      ORRS     r6,r6,r7
        0x0012a93e:    9f0a        ..      LDR      r7,[sp,#0x28]
        0x0012a940:    04bf        ..      LSLS     r7,r7,#18
        0x0012a942:    433e        >C      ORRS     r6,r6,r7
        0x0012a944:    9f0b        ..      LDR      r7,[sp,#0x2c]
        0x0012a946:    047f        ..      LSLS     r7,r7,#17
        0x0012a948:    433e        >C      ORRS     r6,r6,r7
        0x0012a94a:    9f0c        ..      LDR      r7,[sp,#0x30]
        0x0012a94c:    043f        ?.      LSLS     r7,r7,#16
        0x0012a94e:    433e        >C      ORRS     r6,r6,r7
        0x0012a950:    9f0d        ..      LDR      r7,[sp,#0x34]
        0x0012a952:    03ff        ..      LSLS     r7,r7,#15
        0x0012a954:    433e        >C      ORRS     r6,r6,r7
        0x0012a956:    9f0e        ..      LDR      r7,[sp,#0x38]
        0x0012a958:    03bf        ..      LSLS     r7,r7,#14
        0x0012a95a:    433e        >C      ORRS     r6,r6,r7
        0x0012a95c:    9f0f        ..      LDR      r7,[sp,#0x3c]
        0x0012a95e:    037f        ..      LSLS     r7,r7,#13
        0x0012a960:    433e        >C      ORRS     r6,r6,r7
        0x0012a962:    9f10        ..      LDR      r7,[sp,#0x40]
        0x0012a964:    033f        ?.      LSLS     r7,r7,#12
        0x0012a966:    433e        >C      ORRS     r6,r6,r7
        0x0012a968:    9f11        ..      LDR      r7,[sp,#0x44]
        0x0012a96a:    02ff        ..      LSLS     r7,r7,#11
        0x0012a96c:    433e        >C      ORRS     r6,r6,r7
        0x0012a96e:    9f12        ..      LDR      r7,[sp,#0x48]
        0x0012a970:    02bf        ..      LSLS     r7,r7,#10
        0x0012a972:    433e        >C      ORRS     r6,r6,r7
        0x0012a974:    9f13        ..      LDR      r7,[sp,#0x4c]
        0x0012a976:    027f        ..      LSLS     r7,r7,#9
        0x0012a978:    433e        >C      ORRS     r6,r6,r7
        0x0012a97a:    9f14        ..      LDR      r7,[sp,#0x50]
        0x0012a97c:    023f        ?.      LSLS     r7,r7,#8
        0x0012a97e:    433e        >C      ORRS     r6,r6,r7
        0x0012a980:    9f15        ..      LDR      r7,[sp,#0x54]
        0x0012a982:    01ff        ..      LSLS     r7,r7,#7
        0x0012a984:    433e        >C      ORRS     r6,r6,r7
        0x0012a986:    9f16        ..      LDR      r7,[sp,#0x58]
        0x0012a988:    01bf        ..      LSLS     r7,r7,#6
        0x0012a98a:    433e        >C      ORRS     r6,r6,r7
        0x0012a98c:    9f17        ..      LDR      r7,[sp,#0x5c]
        0x0012a98e:    017f        ..      LSLS     r7,r7,#5
        0x0012a990:    433e        >C      ORRS     r6,r6,r7
        0x0012a992:    9f18        ..      LDR      r7,[sp,#0x60]
        0x0012a994:    013f        ?.      LSLS     r7,r7,#4
        0x0012a996:    433e        >C      ORRS     r6,r6,r7
        0x0012a998:    9f19        ..      LDR      r7,[sp,#0x64]
        0x0012a99a:    00ff        ..      LSLS     r7,r7,#3
        0x0012a99c:    433e        >C      ORRS     r6,r6,r7
        0x0012a99e:    9f1a        ..      LDR      r7,[sp,#0x68]
        0x0012a9a0:    00bf        ..      LSLS     r7,r7,#2
        0x0012a9a2:    433e        >C      ORRS     r6,r6,r7
        0x0012a9a4:    9f1b        ..      LDR      r7,[sp,#0x6c]
        0x0012a9a6:    007f        ..      LSLS     r7,r7,#1
        0x0012a9a8:    433e        >C      ORRS     r6,r6,r7
        0x0012a9aa:    9f1c        ..      LDR      r7,[sp,#0x70]
        0x0012a9ac:    433e        >C      ORRS     r6,r6,r7
        0x0012a9ae:    4f01        .O      LDR      r7,[pc,#4] ; [0x12a9b4] = 0x20149000
        0x0012a9b0:    613e        >a      STR      r6,[r7,#0x10]
        0x0012a9b2:    bdf0        ..      POP      {r4-r7,pc}
    $d
        0x0012a9b4:    20149000    ...     DCD    538218496
    $t
    i.sysc_per_clkg0_set
    sysc_per_clkg0_set
        0x0012a9b8:    4901        .I      LDR      r1,[pc,#4] ; [0x12a9c0] = 0x20149000
        0x0012a9ba:    6108        .a      STR      r0,[r1,#0x10]
        0x0012a9bc:    4770        pG      BX       lr
    $d
        0x0012a9be:    0000        ..      DCW    0
        0x0012a9c0:    20149000    ...     DCD    538218496
    $t
    i.uart_dlab_setf
    uart_dlab_setf
        0x0012a9c4:    4905        .I      LDR      r1,[pc,#20] ; [0x12a9dc] = 0x20143000
        0x0012a9c6:    68c9        .h      LDR      r1,[r1,#0xc]
        0x0012a9c8:    2280        ."      MOVS     r2,#0x80
        0x0012a9ca:    4391        .C      BICS     r1,r1,r2
        0x0012a9cc:    01c2        ..      LSLS     r2,r0,#7
        0x0012a9ce:    2380        .#      MOVS     r3,#0x80
        0x0012a9d0:    401a        .@      ANDS     r2,r2,r3
        0x0012a9d2:    4311        .C      ORRS     r1,r1,r2
        0x0012a9d4:    4a01        .J      LDR      r2,[pc,#4] ; [0x12a9dc] = 0x20143000
        0x0012a9d6:    60d1        .`      STR      r1,[r2,#0xc]
        0x0012a9d8:    4770        pG      BX       lr
    $d
        0x0012a9da:    0000        ..      DCW    0
        0x0012a9dc:    20143000    .0.     DCD    538193920
    $t
    i.uart_download_init
    uart_download_init
        0x0012a9e0:    b510        ..      PUSH     {r4,lr}
        0x0012a9e2:    4808        .H      LDR      r0,[pc,#32] ; [0x12aa04] = 0x12aa15
        0x0012a9e4:    4908        .I      LDR      r1,[pc,#32] ; [0x12aa08] = 0x12b0fc
        0x0012a9e6:    6048        H`      STR      r0,[r1,#4]
        0x0012a9e8:    4808        .H      LDR      r0,[pc,#32] ; [0x12aa0c] = 0x12aa5d
        0x0012a9ea:    6008        .`      STR      r0,[r1,#0]
        0x0012a9ec:    f7fffbb1    ....    BL       clk_uart0_921600 ; 0x12a152
        0x0012a9f0:    2001        .       MOVS     r0,#1
        0x0012a9f2:    f000f859    ..Y.    BL       uart_init ; 0x12aaa8
        0x0012a9f6:    200b        .       MOVS     r0,#0xb
        0x0012a9f8:    2101        .!      MOVS     r1,#1
        0x0012a9fa:    4081        .@      LSLS     r1,r1,r0
        0x0012a9fc:    4a04        .J      LDR      r2,[pc,#16] ; [0x12aa10] = 0xe000e100
        0x0012a9fe:    6011        .`      STR      r1,[r2,#0]
        0x0012aa00:    bf00        ..      NOP      
        0x0012aa02:    bd10        ..      POP      {r4,pc}
    $d
        0x0012aa04:    0012aa15    ....    DCD    1223189
        0x0012aa08:    0012b0fc    ....    DCD    1224956
        0x0012aa0c:    0012aa5d    ]...    DCD    1223261
        0x0012aa10:    e000e100    ....    DCD    3758153984
    $t
    i.uart_download_read
    uart_download_read
        0x0012aa14:    b570        p.      PUSH     {r4-r6,lr}
        0x0012aa16:    4604        .F      MOV      r4,r0
        0x0012aa18:    460d        .F      MOV      r5,r1
        0x0012aa1a:    4616        .F      MOV      r6,r2
        0x0012aa1c:    2300        .#      MOVS     r3,#0
        0x0012aa1e:    4632        2F      MOV      r2,r6
        0x0012aa20:    4629        )F      MOV      r1,r5
        0x0012aa22:    4620         F      MOV      r0,r4
        0x0012aa24:    f000f8d6    ....    BL       uart_read ; 0x12abd4
        0x0012aa28:    bd70        p.      POP      {r4-r6,pc}
        0x0012aa2a:    0000        ..      MOVS     r0,r0
    i.uart_download_start
    uart_download_start
        0x0012aa2c:    b510        ..      PUSH     {r4,lr}
        0x0012aa2e:    4806        .H      LDR      r0,[pc,#24] ; [0x12aa48] = 0x12b0fc
        0x0012aa30:    4a06        .J      LDR      r2,[pc,#24] ; [0x12aa4c] = 0x12b091
        0x0012aa32:    2105        .!      MOVS     r1,#5
        0x0012aa34:    6803        .h      LDR      r3,[r0,#0]
        0x0012aa36:    4806        .H      LDR      r0,[pc,#24] ; [0x12aa50] = 0x12b104
        0x0012aa38:    4798        .G      BLX      r3
        0x0012aa3a:    4803        .H      LDR      r0,[pc,#12] ; [0x12aa48] = 0x12b0fc
        0x0012aa3c:    4a05        .J      LDR      r2,[pc,#20] ; [0x12aa54] = 0x12acf5
        0x0012aa3e:    2108        .!      MOVS     r1,#8
        0x0012aa40:    6843        Ch      LDR      r3,[r0,#4]
        0x0012aa42:    4805        .H      LDR      r0,[pc,#20] ; [0x12aa58] = 0x12b514
        0x0012aa44:    4798        .G      BLX      r3
        0x0012aa46:    bd10        ..      POP      {r4,pc}
    $d
        0x0012aa48:    0012b0fc    ....    DCD    1224956
        0x0012aa4c:    0012b091    ....    DCD    1224849
        0x0012aa50:    0012b104    ....    DCD    1224964
        0x0012aa54:    0012acf5    ....    DCD    1223925
        0x0012aa58:    0012b514    ....    DCD    1226004
    $t
    i.uart_download_write
    uart_download_write
        0x0012aa5c:    b570        p.      PUSH     {r4-r6,lr}
        0x0012aa5e:    4604        .F      MOV      r4,r0
        0x0012aa60:    460d        .F      MOV      r5,r1
        0x0012aa62:    4616        .F      MOV      r6,r2
        0x0012aa64:    2300        .#      MOVS     r3,#0
        0x0012aa66:    4632        2F      MOV      r2,r6
        0x0012aa68:    4629        )F      MOV      r1,r5
        0x0012aa6a:    4620         F      MOV      r0,r4
        0x0012aa6c:    f000fb12    ....    BL       uart_write ; 0x12b094
        0x0012aa70:    bd70        p.      POP      {r4-r6,pc}
        0x0012aa72:    0000        ..      MOVS     r0,r0
    i.uart_erbfi_setf
    uart_erbfi_setf
        0x0012aa74:    4904        .I      LDR      r1,[pc,#16] ; [0x12aa88] = 0x20143000
        0x0012aa76:    6849        Ih      LDR      r1,[r1,#4]
        0x0012aa78:    0849        I.      LSRS     r1,r1,#1
        0x0012aa7a:    0049        I.      LSLS     r1,r1,#1
        0x0012aa7c:    07c2        ..      LSLS     r2,r0,#31
        0x0012aa7e:    0fd2        ..      LSRS     r2,r2,#31
        0x0012aa80:    4311        .C      ORRS     r1,r1,r2
        0x0012aa82:    4a01        .J      LDR      r2,[pc,#4] ; [0x12aa88] = 0x20143000
        0x0012aa84:    6051        Q`      STR      r1,[r2,#4]
        0x0012aa86:    4770        pG      BX       lr
    $d
        0x0012aa88:    20143000    .0.     DCD    538193920
    $t
    i.uart_etbei_setf
    uart_etbei_setf
        0x0012aa8c:    4905        .I      LDR      r1,[pc,#20] ; [0x12aaa4] = 0x20143000
        0x0012aa8e:    6849        Ih      LDR      r1,[r1,#4]
        0x0012aa90:    2202        ."      MOVS     r2,#2
        0x0012aa92:    4391        .C      BICS     r1,r1,r2
        0x0012aa94:    0042        B.      LSLS     r2,r0,#1
        0x0012aa96:    2302        .#      MOVS     r3,#2
        0x0012aa98:    401a        .@      ANDS     r2,r2,r3
        0x0012aa9a:    4311        .C      ORRS     r1,r1,r2
        0x0012aa9c:    4a01        .J      LDR      r2,[pc,#4] ; [0x12aaa4] = 0x20143000
        0x0012aa9e:    6051        Q`      STR      r1,[r2,#4]
        0x0012aaa0:    4770        pG      BX       lr
    $d
        0x0012aaa2:    0000        ..      DCW    0
        0x0012aaa4:    20143000    .0.     DCD    538193920
    $t
    i.uart_init
    uart_init
        0x0012aaa8:    b5f1        ..      PUSH     {r0,r4-r7,lr}
        0x0012aaaa:    b098        ..      SUB      sp,sp,#0x60
        0x0012aaac:    2000        .       MOVS     r0,#0
        0x0012aaae:    9014        ..      STR      r0,[sp,#0x50]
        0x0012aab0:    9015        ..      STR      r0,[sp,#0x54]
        0x0012aab2:    9016        ..      STR      r0,[sp,#0x58]
        0x0012aab4:    9017        ..      STR      r0,[sp,#0x5c]
        0x0012aab6:    9010        ..      STR      r0,[sp,#0x40]
        0x0012aab8:    9011        ..      STR      r0,[sp,#0x44]
        0x0012aaba:    9012        ..      STR      r0,[sp,#0x48]
        0x0012aabc:    9013        ..      STR      r0,[sp,#0x4c]
        0x0012aabe:    2001        .       MOVS     r0,#1
        0x0012aac0:    2100        .!      MOVS     r1,#0
        0x0012aac2:    910c        ..      STR      r1,[sp,#0x30]
        0x0012aac4:    900d        ..      STR      r0,[sp,#0x34]
        0x0012aac6:    910e        ..      STR      r1,[sp,#0x38]
        0x0012aac8:    9108        ..      STR      r1,[sp,#0x20]
        0x0012aaca:    9109        ..      STR      r1,[sp,#0x24]
        0x0012aacc:    910a        ..      STR      r1,[sp,#0x28]
        0x0012aace:    910b        ..      STR      r1,[sp,#0x2c]
        0x0012aad0:    9104        ..      STR      r1,[sp,#0x10]
        0x0012aad2:    9105        ..      STR      r1,[sp,#0x14]
        0x0012aad4:    9106        ..      STR      r1,[sp,#0x18]
        0x0012aad6:    9107        ..      STR      r1,[sp,#0x1c]
        0x0012aad8:    900f        ..      STR      r0,[sp,#0x3c]
        0x0012aada:    2000        .       MOVS     r0,#0
        0x0012aadc:    9000        ..      STR      r0,[sp,#0]
        0x0012aade:    9001        ..      STR      r0,[sp,#4]
        0x0012aae0:    9002        ..      STR      r0,[sp,#8]
        0x0012aae2:    4603        .F      MOV      r3,r0
        0x0012aae4:    4602        .F      MOV      r2,r0
        0x0012aae6:    4601        .F      MOV      r1,r0
        0x0012aae8:    9003        ..      STR      r0,[sp,#0xc]
        0x0012aaea:    f7ffff11    ....    BL       sysc_per_clkg0_pack ; 0x12a910
        0x0012aaee:    9818        ..      LDR      r0,[sp,#0x60]
        0x0012aaf0:    f000fa76    ..v.    BL       uart_set_baudrate ; 0x12afe0
        0x0012aaf4:    2000        .       MOVS     r0,#0
        0x0012aaf6:    4921        !I      LDR      r1,[pc,#132] ; [0x12ab7c] = 0x20143000
        0x0012aaf8:    68c9        .h      LDR      r1,[r1,#0xc]
        0x0012aafa:    2208        ."      MOVS     r2,#8
        0x0012aafc:    4391        .C      BICS     r1,r1,r2
        0x0012aafe:    00c2        ..      LSLS     r2,r0,#3
        0x0012ab00:    2308        .#      MOVS     r3,#8
        0x0012ab02:    401a        .@      ANDS     r2,r2,r3
        0x0012ab04:    4311        .C      ORRS     r1,r1,r2
        0x0012ab06:    4a1d        .J      LDR      r2,[pc,#116] ; [0x12ab7c] = 0x20143000
        0x0012ab08:    60d1        .`      STR      r1,[r2,#0xc]
        0x0012ab0a:    bf00        ..      NOP      
        0x0012ab0c:    bf00        ..      NOP      
        0x0012ab0e:    4611        .F      MOV      r1,r2
        0x0012ab10:    68c9        .h      LDR      r1,[r1,#0xc]
        0x0012ab12:    2204        ."      MOVS     r2,#4
        0x0012ab14:    4391        .C      BICS     r1,r1,r2
        0x0012ab16:    0082        ..      LSLS     r2,r0,#2
        0x0012ab18:    2304        .#      MOVS     r3,#4
        0x0012ab1a:    401a        .@      ANDS     r2,r2,r3
        0x0012ab1c:    4311        .C      ORRS     r1,r1,r2
        0x0012ab1e:    4a17        .J      LDR      r2,[pc,#92] ; [0x12ab7c] = 0x20143000
        0x0012ab20:    60d1        .`      STR      r1,[r2,#0xc]
        0x0012ab22:    bf00        ..      NOP      
        0x0012ab24:    2003        .       MOVS     r0,#3
        0x0012ab26:    4611        .F      MOV      r1,r2
        0x0012ab28:    68c9        .h      LDR      r1,[r1,#0xc]
        0x0012ab2a:    4381        .C      BICS     r1,r1,r0
        0x0012ab2c:    4301        .C      ORRS     r1,r1,r0
        0x0012ab2e:    60d1        .`      STR      r1,[r2,#0xc]
        0x0012ab30:    bf00        ..      NOP      
        0x0012ab32:    2000        .       MOVS     r0,#0
        0x0012ab34:    4601        .F      MOV      r1,r0
        0x0012ab36:    2201        ."      MOVS     r2,#1
        0x0012ab38:    4603        .F      MOV      r3,r0
        0x0012ab3a:    4604        .F      MOV      r4,r0
        0x0012ab3c:    01c5        ..      LSLS     r5,r0,#7
        0x0012ab3e:    00ce        ..      LSLS     r6,r1,#3
        0x0012ab40:    4335        5C      ORRS     r5,r5,r6
        0x0012ab42:    0096        ..      LSLS     r6,r2,#2
        0x0012ab44:    4335        5C      ORRS     r5,r5,r6
        0x0012ab46:    005e        ^.      LSLS     r6,r3,#1
        0x0012ab48:    4335        5C      ORRS     r5,r5,r6
        0x0012ab4a:    4325        %C      ORRS     r5,r5,r4
        0x0012ab4c:    4e0b        .N      LDR      r6,[pc,#44] ; [0x12ab7c] = 0x20143000
        0x0012ab4e:    6075        u`      STR      r5,[r6,#4]
        0x0012ab50:    bf00        ..      NOP      
        0x0012ab52:    4602        .F      MOV      r2,r0
        0x0012ab54:    2501        .%      MOVS     r5,#1
        0x0012ab56:    0186        ..      LSLS     r6,r0,#6
        0x0012ab58:    010f        ..      LSLS     r7,r1,#4
        0x0012ab5a:    433e        >C      ORRS     r6,r6,r7
        0x0012ab5c:    00d7        ..      LSLS     r7,r2,#3
        0x0012ab5e:    433e        >C      ORRS     r6,r6,r7
        0x0012ab60:    009f        ..      LSLS     r7,r3,#2
        0x0012ab62:    433e        >C      ORRS     r6,r6,r7
        0x0012ab64:    0067        g.      LSLS     r7,r4,#1
        0x0012ab66:    433e        >C      ORRS     r6,r6,r7
        0x0012ab68:    432e        .C      ORRS     r6,r6,r5
        0x0012ab6a:    4f04        .O      LDR      r7,[pc,#16] ; [0x12ab7c] = 0x20143000
        0x0012ab6c:    60be        .`      STR      r6,[r7,#8]
        0x0012ab6e:    bf00        ..      NOP      
        0x0012ab70:    2100        .!      MOVS     r1,#0
        0x0012ab72:    4803        .H      LDR      r0,[pc,#12] ; [0x12ab80] = 0x12bd3c
        0x0012ab74:    7001        .p      STRB     r1,[r0,#0]
        0x0012ab76:    b019        ..      ADD      sp,sp,#0x64
        0x0012ab78:    bdf0        ..      POP      {r4-r7,pc}
    $d
        0x0012ab7a:    0000        ..      DCW    0
        0x0012ab7c:    20143000    .0.     DCD    538193920
        0x0012ab80:    0012bd3c    <...    DCD    1228092
    $t
    i.uart_isr
    uart_isr
        0x0012ab84:    b510        ..      PUSH     {r4,lr}
        0x0012ab86:    e01f        ..      B        0x12abc8 ; uart_isr + 68
        0x0012ab88:    bf00        ..      NOP      
        0x0012ab8a:    4811        .H      LDR      r0,[pc,#68] ; [0x12abd0] = 0x20143000
        0x0012ab8c:    6880        .h      LDR      r0,[r0,#8]
        0x0012ab8e:    0704        ..      LSLS     r4,r0,#28
        0x0012ab90:    0f24        $.      LSRS     r4,r4,#28
        0x0012ab92:    bf00        ..      NOP      
        0x0012ab94:    2c01        .,      CMP      r4,#1
        0x0012ab96:    d100        ..      BNE      0x12ab9a ; uart_isr + 22
        0x0012ab98:    e017        ..      B        0x12abca ; uart_isr + 70
        0x0012ab9a:    2c02        .,      CMP      r4,#2
        0x0012ab9c:    d00c        ..      BEQ      0x12abb8 ; uart_isr + 52
        0x0012ab9e:    2c04        .,      CMP      r4,#4
        0x0012aba0:    d007        ..      BEQ      0x12abb2 ; uart_isr + 46
        0x0012aba2:    2c06        .,      CMP      r4,#6
        0x0012aba4:    d002        ..      BEQ      0x12abac ; uart_isr + 40
        0x0012aba6:    2c0c        .,      CMP      r4,#0xc
        0x0012aba8:    d10c        ..      BNE      0x12abc4 ; uart_isr + 64
        0x0012abaa:    e008        ..      B        0x12abbe ; uart_isr + 58
        0x0012abac:    f000f874    ..t.    BL       uart_rec_error_isr ; 0x12ac98
        0x0012abb0:    e009        ..      B        0x12abc6 ; uart_isr + 66
        0x0012abb2:    f000f82d    ..-.    BL       uart_rec_data_avail_isr ; 0x12ac10
        0x0012abb6:    e006        ..      B        0x12abc6 ; uart_isr + 66
        0x0012abb8:    f000fa32    ..2.    BL       uart_thr_empty_isr ; 0x12b020
        0x0012abbc:    e003        ..      B        0x12abc6 ; uart_isr + 66
        0x0012abbe:    f000f827    ..'.    BL       uart_rec_data_avail_isr ; 0x12ac10
        0x0012abc2:    e000        ..      B        0x12abc6 ; uart_isr + 66
        0x0012abc4:    bf00        ..      NOP      
        0x0012abc6:    bf00        ..      NOP      
        0x0012abc8:    e7de        ..      B        0x12ab88 ; uart_isr + 4
        0x0012abca:    bf00        ..      NOP      
        0x0012abcc:    bd10        ..      POP      {r4,pc}
    $d
        0x0012abce:    0000        ..      DCW    0
        0x0012abd0:    20143000    .0.     DCD    538193920
    $t
    i.uart_read
    uart_read
        0x0012abd4:    b5f8        ..      PUSH     {r3-r7,lr}
        0x0012abd6:    4604        .F      MOV      r4,r0
        0x0012abd8:    460d        .F      MOV      r5,r1
        0x0012abda:    4616        .F      MOV      r6,r2
        0x0012abdc:    461f        .F      MOV      r7,r3
        0x0012abde:    4804        .H      LDR      r0,[pc,#16] ; [0x12abf0] = 0x12bd1c
        0x0012abe0:    6105        .a      STR      r5,[r0,#0x10]
        0x0012abe2:    6144        Da      STR      r4,[r0,#0x14]
        0x0012abe4:    6186        .a      STR      r6,[r0,#0x18]
        0x0012abe6:    61c7        .a      STR      r7,[r0,#0x1c]
        0x0012abe8:    2001        .       MOVS     r0,#1
        0x0012abea:    f7ffff43    ..C.    BL       uart_erbfi_setf ; 0x12aa74
        0x0012abee:    bdf8        ..      POP      {r3-r7,pc}
    $d
        0x0012abf0:    0012bd1c    ....    DCD    1228060
    $t
    i.uart_read32_register
    uart_read32_register
        0x0012abf4:    b530        0.      PUSH     {r4,r5,lr}
        0x0012abf6:    4603        .F      MOV      r3,r0
        0x0012abf8:    2000        .       MOVS     r0,#0
        0x0012abfa:    e005        ..      B        0x12ac08 ; uart_read32_register + 20
        0x0012abfc:    680c        .h      LDR      r4,[r1,#0]
        0x0012abfe:    0085        ..      LSLS     r5,r0,#2
        0x0012ac00:    515c        \Q      STR      r4,[r3,r5]
        0x0012ac02:    1d09        ..      ADDS     r1,r1,#4
        0x0012ac04:    1c44        D.      ADDS     r4,r0,#1
        0x0012ac06:    b2a0        ..      UXTH     r0,r4
        0x0012ac08:    4290        .B      CMP      r0,r2
        0x0012ac0a:    dbf7        ..      BLT      0x12abfc ; uart_read32_register + 8
        0x0012ac0c:    bd30        0.      POP      {r4,r5,pc}
        0x0012ac0e:    0000        ..      MOVS     r0,r0
    i.uart_rec_data_avail_isr
    uart_rec_data_avail_isr
        0x0012ac10:    b570        p.      PUSH     {r4-r6,lr}
        0x0012ac12:    2400        .$      MOVS     r4,#0
        0x0012ac14:    2500        .%      MOVS     r5,#0
        0x0012ac16:    e032        2.      B        0x12ac7e ; uart_rec_data_avail_isr + 110
        0x0012ac18:    bf00        ..      NOP      
        0x0012ac1a:    481d        .H      LDR      r0,[pc,#116] ; [0x12ac90] = 0x20143000
        0x0012ac1c:    6800        .h      LDR      r0,[r0,#0]
        0x0012ac1e:    b2c1        ..      UXTB     r1,r0
        0x0012ac20:    481c        .H      LDR      r0,[pc,#112] ; [0x12ac94] = 0x12bd1c
        0x0012ac22:    6940        @i      LDR      r0,[r0,#0x14]
        0x0012ac24:    7001        .p      STRB     r1,[r0,#0]
        0x0012ac26:    481b        .H      LDR      r0,[pc,#108] ; [0x12ac94] = 0x12bd1c
        0x0012ac28:    6900        .i      LDR      r0,[r0,#0x10]
        0x0012ac2a:    1e40        @.      SUBS     r0,r0,#1
        0x0012ac2c:    4919        .I      LDR      r1,[pc,#100] ; [0x12ac94] = 0x12bd1c
        0x0012ac2e:    6108        .a      STR      r0,[r1,#0x10]
        0x0012ac30:    4608        .F      MOV      r0,r1
        0x0012ac32:    6940        @i      LDR      r0,[r0,#0x14]
        0x0012ac34:    1c40        @.      ADDS     r0,r0,#1
        0x0012ac36:    6148        Ha      STR      r0,[r1,#0x14]
        0x0012ac38:    4608        .F      MOV      r0,r1
        0x0012ac3a:    6900        .i      LDR      r0,[r0,#0x10]
        0x0012ac3c:    2800        .(      CMP      r0,#0
        0x0012ac3e:    d11e        ..      BNE      0x12ac7e ; uart_rec_data_avail_isr + 110
        0x0012ac40:    2100        .!      MOVS     r1,#0
        0x0012ac42:    4814        .H      LDR      r0,[pc,#80] ; [0x12ac94] = 0x12bd1c
        0x0012ac44:    6141        Aa      STR      r1,[r0,#0x14]
        0x0012ac46:    2000        .       MOVS     r0,#0
        0x0012ac48:    f7ffff14    ....    BL       uart_erbfi_setf ; 0x12aa74
        0x0012ac4c:    4811        .H      LDR      r0,[pc,#68] ; [0x12ac94] = 0x12bd1c
        0x0012ac4e:    6984        .i      LDR      r4,[r0,#0x18]
        0x0012ac50:    69c5        .i      LDR      r5,[r0,#0x1c]
        0x0012ac52:    2c00        .,      CMP      r4,#0
        0x0012ac54:    d011        ..      BEQ      0x12ac7a ; uart_rec_data_avail_isr + 106
        0x0012ac56:    2100        .!      MOVS     r1,#0
        0x0012ac58:    6181        .a      STR      r1,[r0,#0x18]
        0x0012ac5a:    61c1        .a      STR      r1,[r0,#0x1c]
        0x0012ac5c:    3020         0      ADDS     r0,r0,#0x20
        0x0012ac5e:    7800        .x      LDRB     r0,[r0,#0]
        0x0012ac60:    2800        .(      CMP      r0,#0
        0x0012ac62:    d102        ..      BNE      0x12ac6a ; uart_rec_data_avail_isr + 90
        0x0012ac64:    4628        (F      MOV      r0,r5
        0x0012ac66:    47a0        .G      BLX      r4
        0x0012ac68:    e008        ..      B        0x12ac7c ; uart_rec_data_avail_isr + 108
        0x0012ac6a:    2100        .!      MOVS     r1,#0
        0x0012ac6c:    4809        .H      LDR      r0,[pc,#36] ; [0x12ac94] = 0x12bd1c
        0x0012ac6e:    3020         0      ADDS     r0,r0,#0x20
        0x0012ac70:    7001        .p      STRB     r1,[r0,#0]
        0x0012ac72:    2101        .!      MOVS     r1,#1
        0x0012ac74:    4628        (F      MOV      r0,r5
        0x0012ac76:    47a0        .G      BLX      r4
        0x0012ac78:    e000        ..      B        0x12ac7c ; uart_rec_data_avail_isr + 108
        0x0012ac7a:    bf00        ..      NOP      
        0x0012ac7c:    e006        ..      B        0x12ac8c ; uart_rec_data_avail_isr + 124
        0x0012ac7e:    bf00        ..      NOP      
        0x0012ac80:    4803        .H      LDR      r0,[pc,#12] ; [0x12ac90] = 0x20143000
        0x0012ac82:    6940        @i      LDR      r0,[r0,#0x14]
        0x0012ac84:    07c0        ..      LSLS     r0,r0,#31
        0x0012ac86:    0fc0        ..      LSRS     r0,r0,#31
        0x0012ac88:    2800        .(      CMP      r0,#0
        0x0012ac8a:    d1c5        ..      BNE      0x12ac18 ; uart_rec_data_avail_isr + 8
        0x0012ac8c:    bf00        ..      NOP      
        0x0012ac8e:    bd70        p.      POP      {r4-r6,pc}
    $d
        0x0012ac90:    20143000    .0.     DCD    538193920
        0x0012ac94:    0012bd1c    ....    DCD    1228060
    $t
    i.uart_rec_error_isr
    uart_rec_error_isr
        0x0012ac98:    b570        p.      PUSH     {r4-r6,lr}
        0x0012ac9a:    2400        .$      MOVS     r4,#0
        0x0012ac9c:    2600        .&      MOVS     r6,#0
        0x0012ac9e:    bf00        ..      NOP      
        0x0012aca0:    4812        .H      LDR      r0,[pc,#72] ; [0x12acec] = 0x20143000
        0x0012aca2:    6940        @i      LDR      r0,[r0,#0x14]
        0x0012aca4:    b2c5        ..      UXTB     r5,r0
        0x0012aca6:    07a8        ..      LSLS     r0,r5,#30
        0x0012aca8:    0fc0        ..      LSRS     r0,r0,#31
        0x0012acaa:    2800        .(      CMP      r0,#0
        0x0012acac:    d014        ..      BEQ      0x12acd8 ; uart_rec_error_isr + 64
        0x0012acae:    e003        ..      B        0x12acb8 ; uart_rec_error_isr + 32
        0x0012acb0:    bf00        ..      NOP      
        0x0012acb2:    480e        .H      LDR      r0,[pc,#56] ; [0x12acec] = 0x20143000
        0x0012acb4:    6800        .h      LDR      r0,[r0,#0]
        0x0012acb6:    bf00        ..      NOP      
        0x0012acb8:    bf00        ..      NOP      
        0x0012acba:    480c        .H      LDR      r0,[pc,#48] ; [0x12acec] = 0x20143000
        0x0012acbc:    6940        @i      LDR      r0,[r0,#0x14]
        0x0012acbe:    07c0        ..      LSLS     r0,r0,#31
        0x0012acc0:    0fc0        ..      LSRS     r0,r0,#31
        0x0012acc2:    2800        .(      CMP      r0,#0
        0x0012acc4:    d1f4        ..      BNE      0x12acb0 ; uart_rec_error_isr + 24
        0x0012acc6:    2c00        .,      CMP      r4,#0
        0x0012acc8:    d006        ..      BEQ      0x12acd8 ; uart_rec_error_isr + 64
        0x0012acca:    2100        .!      MOVS     r1,#0
        0x0012accc:    4808        .H      LDR      r0,[pc,#32] ; [0x12acf0] = 0x12bd1c
        0x0012acce:    6181        .a      STR      r1,[r0,#0x18]
        0x0012acd0:    61c1        .a      STR      r1,[r0,#0x1c]
        0x0012acd2:    2101        .!      MOVS     r1,#1
        0x0012acd4:    4630        0F      MOV      r0,r6
        0x0012acd6:    47a0        .G      BLX      r4
        0x0012acd8:    0728        (.      LSLS     r0,r5,#28
        0x0012acda:    0fc0        ..      LSRS     r0,r0,#31
        0x0012acdc:    2800        .(      CMP      r0,#0
        0x0012acde:    d003        ..      BEQ      0x12ace8 ; uart_rec_error_isr + 80
        0x0012ace0:    2101        .!      MOVS     r1,#1
        0x0012ace2:    4803        .H      LDR      r0,[pc,#12] ; [0x12acf0] = 0x12bd1c
        0x0012ace4:    3020         0      ADDS     r0,r0,#0x20
        0x0012ace6:    7001        .p      STRB     r1,[r0,#0]
        0x0012ace8:    bd70        p.      POP      {r4-r6,pc}
    $d
        0x0012acea:    0000        ..      DCW    0
        0x0012acec:    20143000    .0.     DCD    538193920
        0x0012acf0:    0012bd1c    ....    DCD    1228060
    $t
    i.uart_rx_header_finish
    uart_rx_header_finish
        0x0012acf4:    b510        ..      PUSH     {r4,lr}
        0x0012acf6:    4804        .H      LDR      r0,[pc,#16] ; [0x12ad08] = 0x12b514
        0x0012acf8:    8841        A.      LDRH     r1,[r0,#2]
        0x0012acfa:    4804        .H      LDR      r0,[pc,#16] ; [0x12ad0c] = 0x12b0fc
        0x0012acfc:    4a04        .J      LDR      r2,[pc,#16] ; [0x12ad10] = 0x12ad15
        0x0012acfe:    6843        Ch      LDR      r3,[r0,#4]
        0x0012ad00:    4801        .H      LDR      r0,[pc,#4] ; [0x12ad08] = 0x12b514
        0x0012ad02:    3008        .0      ADDS     r0,r0,#8
        0x0012ad04:    4798        .G      BLX      r3
        0x0012ad06:    bd10        ..      POP      {r4,pc}
    $d
        0x0012ad08:    0012b514    ....    DCD    1226004
        0x0012ad0c:    0012b0fc    ....    DCD    1224956
        0x0012ad10:    0012ad15    ....    DCD    1223957
    $t
    i.uart_rx_payload_finish
    uart_rx_payload_finish
        0x0012ad14:    b5fe        ..      PUSH     {r1-r7,lr}
        0x0012ad16:    48a9        .H      LDR      r0,[pc,#676] ; [0x12afbc] = 0x12b514
        0x0012ad18:    7800        .x      LDRB     r0,[r0,#0]
        0x0012ad1a:    28ad        .(      CMP      r0,#0xad
        0x0012ad1c:    d006        ..      BEQ      0x12ad2c ; uart_rx_payload_finish + 24
        0x0012ad1e:    48a8        .H      LDR      r0,[pc,#672] ; [0x12afc0] = 0x12b0fc
        0x0012ad20:    4aa8        .J      LDR      r2,[pc,#672] ; [0x12afc4] = 0x12b091
        0x0012ad22:    2105        .!      MOVS     r1,#5
        0x0012ad24:    6803        .h      LDR      r3,[r0,#0]
        0x0012ad26:    48a8        .H      LDR      r0,[pc,#672] ; [0x12afc8] = 0x12b10e
        0x0012ad28:    4798        .G      BLX      r3
        0x0012ad2a:    e13f        ?.      B        0x12afac ; uart_rx_payload_finish + 664
        0x0012ad2c:    48a3        .H      LDR      r0,[pc,#652] ; [0x12afbc] = 0x12b514
        0x0012ad2e:    7840        @x      LDRB     r0,[r0,#1]
        0x0012ad30:    0740        @.      LSLS     r0,r0,#29
        0x0012ad32:    0fc0        ..      LSRS     r0,r0,#31
        0x0012ad34:    2800        .(      CMP      r0,#0
        0x0012ad36:    d17d        }.      BNE      0x12ae34 ; uart_rx_payload_finish + 288
        0x0012ad38:    48a0        .H      LDR      r0,[pc,#640] ; [0x12afbc] = 0x12b514
        0x0012ad3a:    7840        @x      LDRB     r0,[r0,#1]
        0x0012ad3c:    08c0        ..      LSRS     r0,r0,#3
        0x0012ad3e:    2801        .(      CMP      r0,#1
        0x0012ad40:    d133        3.      BNE      0x12adaa ; uart_rx_payload_finish + 150
        0x0012ad42:    489e        .H      LDR      r0,[pc,#632] ; [0x12afbc] = 0x12b514
        0x0012ad44:    8840        @.      LDRH     r0,[r0,#2]
        0x0012ad46:    2802        .(      CMP      r0,#2
        0x0012ad48:    d12f        /.      BNE      0x12adaa ; uart_rx_payload_finish + 150
        0x0012ad4a:    489c        .H      LDR      r0,[pc,#624] ; [0x12afbc] = 0x12b514
        0x0012ad4c:    7a00        .z      LDRB     r0,[r0,#8]
        0x0012ad4e:    2846        F(      CMP      r0,#0x46
        0x0012ad50:    d107        ..      BNE      0x12ad62 ; uart_rx_payload_finish + 78
        0x0012ad52:    489a        .H      LDR      r0,[pc,#616] ; [0x12afbc] = 0x12b514
        0x0012ad54:    7a40        @z      LDRB     r0,[r0,#9]
        0x0012ad56:    2844        D(      CMP      r0,#0x44
        0x0012ad58:    d103        ..      BNE      0x12ad62 ; uart_rx_payload_finish + 78
        0x0012ad5a:    2001        .       MOVS     r0,#1
        0x0012ad5c:    499b        .I      LDR      r1,[pc,#620] ; [0x12afcc] = 0x12b0f8
        0x0012ad5e:    7008        .p      STRB     r0,[r1,#0]
        0x0012ad60:    e124        $.      B        0x12afac ; uart_rx_payload_finish + 664
        0x0012ad62:    4896        .H      LDR      r0,[pc,#600] ; [0x12afbc] = 0x12b514
        0x0012ad64:    7a00        .z      LDRB     r0,[r0,#8]
        0x0012ad66:    2843        C(      CMP      r0,#0x43
        0x0012ad68:    d107        ..      BNE      0x12ad7a ; uart_rx_payload_finish + 102
        0x0012ad6a:    4894        .H      LDR      r0,[pc,#592] ; [0x12afbc] = 0x12b514
        0x0012ad6c:    7a40        @z      LDRB     r0,[r0,#9]
        0x0012ad6e:    2846        F(      CMP      r0,#0x46
        0x0012ad70:    d103        ..      BNE      0x12ad7a ; uart_rx_payload_finish + 102
        0x0012ad72:    20ff        .       MOVS     r0,#0xff
        0x0012ad74:    4996        .I      LDR      r1,[pc,#600] ; [0x12afd0] = 0x12b0f9
        0x0012ad76:    7008        .p      STRB     r0,[r1,#0]
        0x0012ad78:    bdfe        ..      POP      {r1-r7,pc}
        0x0012ad7a:    4890        .H      LDR      r0,[pc,#576] ; [0x12afbc] = 0x12b514
        0x0012ad7c:    7a00        .z      LDRB     r0,[r0,#8]
        0x0012ad7e:    2843        C(      CMP      r0,#0x43
        0x0012ad80:    d107        ..      BNE      0x12ad92 ; uart_rx_payload_finish + 126
        0x0012ad82:    488e        .H      LDR      r0,[pc,#568] ; [0x12afbc] = 0x12b514
        0x0012ad84:    7a40        @z      LDRB     r0,[r0,#9]
        0x0012ad86:    2850        P(      CMP      r0,#0x50
        0x0012ad88:    d103        ..      BNE      0x12ad92 ; uart_rx_payload_finish + 126
        0x0012ad8a:    2001        .       MOVS     r0,#1
        0x0012ad8c:    4990        .I      LDR      r1,[pc,#576] ; [0x12afd0] = 0x12b0f9
        0x0012ad8e:    7008        .p      STRB     r0,[r1,#0]
        0x0012ad90:    e7f2        ..      B        0x12ad78 ; uart_rx_payload_finish + 100
        0x0012ad92:    488a        .H      LDR      r0,[pc,#552] ; [0x12afbc] = 0x12b514
        0x0012ad94:    7a00        .z      LDRB     r0,[r0,#8]
        0x0012ad96:    2850        P(      CMP      r0,#0x50
        0x0012ad98:    d1c7        ..      BNE      0x12ad2a ; uart_rx_payload_finish + 22
        0x0012ad9a:    4888        .H      LDR      r0,[pc,#544] ; [0x12afbc] = 0x12b514
        0x0012ad9c:    7a40        @z      LDRB     r0,[r0,#9]
        0x0012ad9e:    2852        R(      CMP      r0,#0x52
        0x0012ada0:    d1c3        ..      BNE      0x12ad2a ; uart_rx_payload_finish + 22
        0x0012ada2:    2001        .       MOVS     r0,#1
        0x0012ada4:    498b        .I      LDR      r1,[pc,#556] ; [0x12afd4] = 0x12b0fa
        0x0012ada6:    7008        .p      STRB     r0,[r1,#0]
        0x0012ada8:    e7e6        ..      B        0x12ad78 ; uart_rx_payload_finish + 100
        0x0012adaa:    4884        .H      LDR      r0,[pc,#528] ; [0x12afbc] = 0x12b514
        0x0012adac:    7840        @x      LDRB     r0,[r0,#1]
        0x0012adae:    08c0        ..      LSRS     r0,r0,#3
        0x0012adb0:    2802        .(      CMP      r0,#2
        0x0012adb2:    d112        ..      BNE      0x12adda ; uart_rx_payload_finish + 198
        0x0012adb4:    4881        .H      LDR      r0,[pc,#516] ; [0x12afbc] = 0x12b514
        0x0012adb6:    8840        @.      LDRH     r0,[r0,#2]
        0x0012adb8:    2802        .(      CMP      r0,#2
        0x0012adba:    d10e        ..      BNE      0x12adda ; uart_rx_payload_finish + 198
        0x0012adbc:    2000        .       MOVS     r0,#0
        0x0012adbe:    9001        ..      STR      r0,[sp,#4]
        0x0012adc0:    487e        ~H      LDR      r0,[pc,#504] ; [0x12afbc] = 0x12b514
        0x0012adc2:    7a07        .z      LDRB     r7,[r0,#8]
        0x0012adc4:    4638        8F      MOV      r0,r7
        0x0012adc6:    f7fffbc7    ....    BL       flash_status_read ; 0x12a558
        0x0012adca:    9001        ..      STR      r0,[sp,#4]
        0x0012adcc:    487c        |H      LDR      r0,[pc,#496] ; [0x12afc0] = 0x12b0fc
        0x0012adce:    4a7d        }J      LDR      r2,[pc,#500] ; [0x12afc4] = 0x12b091
        0x0012add0:    2101        .!      MOVS     r1,#1
        0x0012add2:    6803        .h      LDR      r3,[r0,#0]
        0x0012add4:    a801        ..      ADD      r0,sp,#4
        0x0012add6:    4798        .G      BLX      r3
        0x0012add8:    e0e8        ..      B        0x12afac ; uart_rx_payload_finish + 664
        0x0012adda:    4878        xH      LDR      r0,[pc,#480] ; [0x12afbc] = 0x12b514
        0x0012addc:    7840        @x      LDRB     r0,[r0,#1]
        0x0012adde:    08c0        ..      LSRS     r0,r0,#3
        0x0012ade0:    2805        .(      CMP      r0,#5
        0x0012ade2:    d115        ..      BNE      0x12ae10 ; uart_rx_payload_finish + 252
        0x0012ade4:    4875        uH      LDR      r0,[pc,#468] ; [0x12afbc] = 0x12b514
        0x0012ade6:    8840        @.      LDRH     r0,[r0,#2]
        0x0012ade8:    2802        .(      CMP      r0,#2
        0x0012adea:    d111        ..      BNE      0x12ae10 ; uart_rx_payload_finish + 252
        0x0012adec:    2000        .       MOVS     r0,#0
        0x0012adee:    9001        ..      STR      r0,[sp,#4]
        0x0012adf0:    4872        rH      LDR      r0,[pc,#456] ; [0x12afbc] = 0x12b514
        0x0012adf2:    7a07        .z      LDRB     r7,[r0,#8]
        0x0012adf4:    7a40        @z      LDRB     r0,[r0,#9]
        0x0012adf6:    9000        ..      STR      r0,[sp,#0]
        0x0012adf8:    4638        8F      MOV      r0,r7
        0x0012adfa:    9900        ..      LDR      r1,[sp,#0]
        0x0012adfc:    f7fffbd8    ....    BL       flash_status_write ; 0x12a5b0
        0x0012ae00:    9001        ..      STR      r0,[sp,#4]
        0x0012ae02:    486f        oH      LDR      r0,[pc,#444] ; [0x12afc0] = 0x12b0fc
        0x0012ae04:    4a6f        oJ      LDR      r2,[pc,#444] ; [0x12afc4] = 0x12b091
        0x0012ae06:    2101        .!      MOVS     r1,#1
        0x0012ae08:    6803        .h      LDR      r3,[r0,#0]
        0x0012ae0a:    a801        ..      ADD      r0,sp,#4
        0x0012ae0c:    4798        .G      BLX      r3
        0x0012ae0e:    e0cd        ..      B        0x12afac ; uart_rx_payload_finish + 664
        0x0012ae10:    486a        jH      LDR      r0,[pc,#424] ; [0x12afbc] = 0x12b514
        0x0012ae12:    7840        @x      LDRB     r0,[r0,#1]
        0x0012ae14:    08c0        ..      LSRS     r0,r0,#3
        0x0012ae16:    2806        .(      CMP      r0,#6
        0x0012ae18:    d117        ..      BNE      0x12ae4a ; uart_rx_payload_finish + 310
        0x0012ae1a:    4868        hH      LDR      r0,[pc,#416] ; [0x12afbc] = 0x12b514
        0x0012ae1c:    8840        @.      LDRH     r0,[r0,#2]
        0x0012ae1e:    2802        .(      CMP      r0,#2
        0x0012ae20:    d113        ..      BNE      0x12ae4a ; uart_rx_payload_finish + 310
        0x0012ae22:    2000        .       MOVS     r0,#0
        0x0012ae24:    9001        ..      STR      r0,[sp,#4]
        0x0012ae26:    4865        eH      LDR      r0,[pc,#404] ; [0x12afbc] = 0x12b514
        0x0012ae28:    7a07        .z      LDRB     r7,[r0,#8]
        0x0012ae2a:    7a40        @z      LDRB     r0,[r0,#9]
        0x0012ae2c:    9000        ..      STR      r0,[sp,#0]
        0x0012ae2e:    4638        8F      MOV      r0,r7
        0x0012ae30:    9900        ..      LDR      r1,[sp,#0]
        0x0012ae32:    e000        ..      B        0x12ae36 ; uart_rx_payload_finish + 290
        0x0012ae34:    e050        P.      B        0x12aed8 ; uart_rx_payload_finish + 452
        0x0012ae36:    f7fffc01    ....    BL       flash_status_write_2bytes ; 0x12a63c
        0x0012ae3a:    9001        ..      STR      r0,[sp,#4]
        0x0012ae3c:    4860        `H      LDR      r0,[pc,#384] ; [0x12afc0] = 0x12b0fc
        0x0012ae3e:    4a61        aJ      LDR      r2,[pc,#388] ; [0x12afc4] = 0x12b091
        0x0012ae40:    2102        .!      MOVS     r1,#2
        0x0012ae42:    6803        .h      LDR      r3,[r0,#0]
        0x0012ae44:    a801        ..      ADD      r0,sp,#4
        0x0012ae46:    4798        .G      BLX      r3
        0x0012ae48:    e0b0        ..      B        0x12afac ; uart_rx_payload_finish + 664
        0x0012ae4a:    485c        \H      LDR      r0,[pc,#368] ; [0x12afbc] = 0x12b514
        0x0012ae4c:    7840        @x      LDRB     r0,[r0,#1]
        0x0012ae4e:    08c0        ..      LSRS     r0,r0,#3
        0x0012ae50:    2803        .(      CMP      r0,#3
        0x0012ae52:    d115        ..      BNE      0x12ae80 ; uart_rx_payload_finish + 364
        0x0012ae54:    4859        YH      LDR      r0,[pc,#356] ; [0x12afbc] = 0x12b514
        0x0012ae56:    8840        @.      LDRH     r0,[r0,#2]
        0x0012ae58:    2802        .(      CMP      r0,#2
        0x0012ae5a:    d111        ..      BNE      0x12ae80 ; uart_rx_payload_finish + 364
        0x0012ae5c:    4857        WH      LDR      r0,[pc,#348] ; [0x12afbc] = 0x12b514
        0x0012ae5e:    7a04        .z      LDRB     r4,[r0,#8]
        0x0012ae60:    4601        .F      MOV      r1,r0
        0x0012ae62:    7a49        Iz      LDRB     r1,[r1,#9]
        0x0012ae64:    0209        ..      LSLS     r1,r1,#8
        0x0012ae66:    430c        .C      ORRS     r4,r4,r1
        0x0012ae68:    4622        "F      MOV      r2,r4
        0x0012ae6a:    6841        Ah      LDR      r1,[r0,#4]
        0x0012ae6c:    485a        ZH      LDR      r0,[pc,#360] ; [0x12afd8] = 0x12b114
        0x0012ae6e:    f7fffec1    ....    BL       uart_read32_register ; 0x12abf4
        0x0012ae72:    00a1        ..      LSLS     r1,r4,#2
        0x0012ae74:    4852        RH      LDR      r0,[pc,#328] ; [0x12afc0] = 0x12b0fc
        0x0012ae76:    4a53        SJ      LDR      r2,[pc,#332] ; [0x12afc4] = 0x12b091
        0x0012ae78:    6803        .h      LDR      r3,[r0,#0]
        0x0012ae7a:    4857        WH      LDR      r0,[pc,#348] ; [0x12afd8] = 0x12b114
        0x0012ae7c:    4798        .G      BLX      r3
        0x0012ae7e:    e095        ..      B        0x12afac ; uart_rx_payload_finish + 664
        0x0012ae80:    484e        NH      LDR      r0,[pc,#312] ; [0x12afbc] = 0x12b514
        0x0012ae82:    7840        @x      LDRB     r0,[r0,#1]
        0x0012ae84:    08c0        ..      LSRS     r0,r0,#3
        0x0012ae86:    2804        .(      CMP      r0,#4
        0x0012ae88:    d11f        ..      BNE      0x12aeca ; uart_rx_payload_finish + 438
        0x0012ae8a:    484c        LH      LDR      r0,[pc,#304] ; [0x12afbc] = 0x12b514
        0x0012ae8c:    8840        @.      LDRH     r0,[r0,#2]
        0x0012ae8e:    2804        .(      CMP      r0,#4
        0x0012ae90:    d11b        ..      BNE      0x12aeca ; uart_rx_payload_finish + 438
        0x0012ae92:    484a        JH      LDR      r0,[pc,#296] ; [0x12afbc] = 0x12b514
        0x0012ae94:    7a00        .z      LDRB     r0,[r0,#8]
        0x0012ae96:    4949        II      LDR      r1,[pc,#292] ; [0x12afbc] = 0x12b514
        0x0012ae98:    7a49        Iz      LDRB     r1,[r1,#9]
        0x0012ae9a:    0209        ..      LSLS     r1,r1,#8
        0x0012ae9c:    4308        .C      ORRS     r0,r0,r1
        0x0012ae9e:    4947        GI      LDR      r1,[pc,#284] ; [0x12afbc] = 0x12b514
        0x0012aea0:    7a89        .z      LDRB     r1,[r1,#0xa]
        0x0012aea2:    0409        ..      LSLS     r1,r1,#16
        0x0012aea4:    4308        .C      ORRS     r0,r0,r1
        0x0012aea6:    4945        EI      LDR      r1,[pc,#276] ; [0x12afbc] = 0x12b514
        0x0012aea8:    7ac9        .z      LDRB     r1,[r1,#0xb]
        0x0012aeaa:    0609        ..      LSLS     r1,r1,#24
        0x0012aeac:    4308        .C      ORRS     r0,r0,r1
        0x0012aeae:    4607        .F      MOV      r7,r0
        0x0012aeb0:    4942        BI      LDR      r1,[pc,#264] ; [0x12afbc] = 0x12b514
        0x0012aeb2:    6848        Hh      LDR      r0,[r1,#4]
        0x0012aeb4:    4639        9F      MOV      r1,r7
        0x0012aeb6:    f000f8fd    ....    BL       uart_write_register ; 0x12b0b4
        0x0012aeba:    4841        AH      LDR      r0,[pc,#260] ; [0x12afc0] = 0x12b0fc
        0x0012aebc:    4a41        AJ      LDR      r2,[pc,#260] ; [0x12afc4] = 0x12b091
        0x0012aebe:    2105        .!      MOVS     r1,#5
        0x0012aec0:    6803        .h      LDR      r3,[r0,#0]
        0x0012aec2:    4841        AH      LDR      r0,[pc,#260] ; [0x12afc8] = 0x12b10e
        0x0012aec4:    1f40        @.      SUBS     r0,r0,#5
        0x0012aec6:    4798        .G      BLX      r3
        0x0012aec8:    e070        p.      B        0x12afac ; uart_rx_payload_finish + 664
        0x0012aeca:    483d        =H      LDR      r0,[pc,#244] ; [0x12afc0] = 0x12b0fc
        0x0012aecc:    4a3d        =J      LDR      r2,[pc,#244] ; [0x12afc4] = 0x12b091
        0x0012aece:    2105        .!      MOVS     r1,#5
        0x0012aed0:    6803        .h      LDR      r3,[r0,#0]
        0x0012aed2:    483d        =H      LDR      r0,[pc,#244] ; [0x12afc8] = 0x12b10e
        0x0012aed4:    4798        .G      BLX      r3
        0x0012aed6:    e069        i.      B        0x12afac ; uart_rx_payload_finish + 664
        0x0012aed8:    4838        8H      LDR      r0,[pc,#224] ; [0x12afbc] = 0x12b514
        0x0012aeda:    7840        @x      LDRB     r0,[r0,#1]
        0x0012aedc:    0740        @.      LSLS     r0,r0,#29
        0x0012aede:    0fc0        ..      LSRS     r0,r0,#31
        0x0012aee0:    2800        .(      CMP      r0,#0
        0x0012aee2:    d063        c.      BEQ      0x12afac ; uart_rx_payload_finish + 664
        0x0012aee4:    4835        5H      LDR      r0,[pc,#212] ; [0x12afbc] = 0x12b514
        0x0012aee6:    7840        @x      LDRB     r0,[r0,#1]
        0x0012aee8:    0780        ..      LSLS     r0,r0,#30
        0x0012aeea:    0f80        ..      LSRS     r0,r0,#30
        0x0012aeec:    2800        .(      CMP      r0,#0
        0x0012aeee:    d004        ..      BEQ      0x12aefa ; uart_rx_payload_finish + 486
        0x0012aef0:    2801        .(      CMP      r0,#1
        0x0012aef2:    d017        ..      BEQ      0x12af24 ; uart_rx_payload_finish + 528
        0x0012aef4:    2802        .(      CMP      r0,#2
        0x0012aef6:    d151        Q.      BNE      0x12af9c ; uart_rx_payload_finish + 648
        0x0012aef8:    e040        @.      B        0x12af7c ; uart_rx_payload_finish + 616
        0x0012aefa:    4830        0H      LDR      r0,[pc,#192] ; [0x12afbc] = 0x12b514
        0x0012aefc:    7a04        .z      LDRB     r4,[r0,#8]
        0x0012aefe:    4601        .F      MOV      r1,r0
        0x0012af00:    7a49        Iz      LDRB     r1,[r1,#9]
        0x0012af02:    0209        ..      LSLS     r1,r1,#8
        0x0012af04:    430c        .C      ORRS     r4,r4,r1
        0x0012af06:    4601        .F      MOV      r1,r0
        0x0012af08:    460a        .F      MOV      r2,r1
        0x0012af0a:    3208        .2      ADDS     r2,r2,#8
        0x0012af0c:    6848        Hh      LDR      r0,[r1,#4]
        0x0012af0e:    4621        !F      MOV      r1,r4
        0x0012af10:    f7fffae2    ....    BL       flash_read ; 0x12a4d8
        0x0012af14:    482a        *H      LDR      r0,[pc,#168] ; [0x12afc0] = 0x12b0fc
        0x0012af16:    4a2b        +J      LDR      r2,[pc,#172] ; [0x12afc4] = 0x12b091
        0x0012af18:    4621        !F      MOV      r1,r4
        0x0012af1a:    6803        .h      LDR      r3,[r0,#0]
        0x0012af1c:    4827        'H      LDR      r0,[pc,#156] ; [0x12afbc] = 0x12b514
        0x0012af1e:    3008        .0      ADDS     r0,r0,#8
        0x0012af20:    4798        .G      BLX      r3
        0x0012af22:    e042        B.      B        0x12afaa ; uart_rx_payload_finish + 662
        0x0012af24:    2600        .&      MOVS     r6,#0
        0x0012af26:    e01d        ..      B        0x12af64 ; uart_rx_payload_finish + 592
        0x0012af28:    4824        $H      LDR      r0,[pc,#144] ; [0x12afbc] = 0x12b514
        0x0012af2a:    8840        @.      LDRH     r0,[r0,#2]
        0x0012af2c:    21ff        .!      MOVS     r1,#0xff
        0x0012af2e:    3101        .1      ADDS     r1,#1
        0x0012af30:    4288        .B      CMP      r0,r1
        0x0012af32:    dd01        ..      BLE      0x12af38 ; uart_rx_payload_finish + 548
        0x0012af34:    4608        .F      MOV      r0,r1
        0x0012af36:    e001        ..      B        0x12af3c ; uart_rx_payload_finish + 552
        0x0012af38:    4820         H      LDR      r0,[pc,#128] ; [0x12afbc] = 0x12b514
        0x0012af3a:    8840        @.      LDRH     r0,[r0,#2]
        0x0012af3c:    4605        .F      MOV      r5,r0
        0x0012af3e:    491f        .I      LDR      r1,[pc,#124] ; [0x12afbc] = 0x12b514
        0x0012af40:    3108        .1      ADDS     r1,r1,#8
        0x0012af42:    198a        ..      ADDS     r2,r1,r6
        0x0012af44:    3908        .9      SUBS     r1,r1,#8
        0x0012af46:    6848        Hh      LDR      r0,[r1,#4]
        0x0012af48:    4629        )F      MOV      r1,r5
        0x0012af4a:    f7fffa70    ..p.    BL       flash_program ; 0x12a42e
        0x0012af4e:    1970        p.      ADDS     r0,r6,r5
        0x0012af50:    b286        ..      UXTH     r6,r0
        0x0012af52:    481a        .H      LDR      r0,[pc,#104] ; [0x12afbc] = 0x12b514
        0x0012af54:    8840        @.      LDRH     r0,[r0,#2]
        0x0012af56:    1b40        @.      SUBS     r0,r0,r5
        0x0012af58:    4918        .I      LDR      r1,[pc,#96] ; [0x12afbc] = 0x12b514
        0x0012af5a:    8048        H.      STRH     r0,[r1,#2]
        0x0012af5c:    4608        .F      MOV      r0,r1
        0x0012af5e:    6840        @h      LDR      r0,[r0,#4]
        0x0012af60:    1940        @.      ADDS     r0,r0,r5
        0x0012af62:    6048        H`      STR      r0,[r1,#4]
        0x0012af64:    4815        .H      LDR      r0,[pc,#84] ; [0x12afbc] = 0x12b514
        0x0012af66:    8840        @.      LDRH     r0,[r0,#2]
        0x0012af68:    2800        .(      CMP      r0,#0
        0x0012af6a:    d1dd        ..      BNE      0x12af28 ; uart_rx_payload_finish + 532
        0x0012af6c:    4814        .H      LDR      r0,[pc,#80] ; [0x12afc0] = 0x12b0fc
        0x0012af6e:    4a15        .J      LDR      r2,[pc,#84] ; [0x12afc4] = 0x12b091
        0x0012af70:    2105        .!      MOVS     r1,#5
        0x0012af72:    6803        .h      LDR      r3,[r0,#0]
        0x0012af74:    4814        .H      LDR      r0,[pc,#80] ; [0x12afc8] = 0x12b10e
        0x0012af76:    1f40        @.      SUBS     r0,r0,#5
        0x0012af78:    4798        .G      BLX      r3
        0x0012af7a:    e016        ..      B        0x12afaa ; uart_rx_payload_finish + 662
        0x0012af7c:    480f        .H      LDR      r0,[pc,#60] ; [0x12afbc] = 0x12b514
        0x0012af7e:    7a07        .z      LDRB     r7,[r0,#8]
        0x0012af80:    6840        @h      LDR      r0,[r0,#4]
        0x0012af82:    9001        ..      STR      r0,[sp,#4]
        0x0012af84:    4639        9F      MOV      r1,r7
        0x0012af86:    9801        ..      LDR      r0,[sp,#4]
        0x0012af88:    f7fff9ea    ....    BL       flash_erase ; 0x12a360
        0x0012af8c:    480c        .H      LDR      r0,[pc,#48] ; [0x12afc0] = 0x12b0fc
        0x0012af8e:    4a0d        .J      LDR      r2,[pc,#52] ; [0x12afc4] = 0x12b091
        0x0012af90:    2105        .!      MOVS     r1,#5
        0x0012af92:    6803        .h      LDR      r3,[r0,#0]
        0x0012af94:    480c        .H      LDR      r0,[pc,#48] ; [0x12afc8] = 0x12b10e
        0x0012af96:    1f40        @.      SUBS     r0,r0,#5
        0x0012af98:    4798        .G      BLX      r3
        0x0012af9a:    e006        ..      B        0x12afaa ; uart_rx_payload_finish + 662
        0x0012af9c:    4808        .H      LDR      r0,[pc,#32] ; [0x12afc0] = 0x12b0fc
        0x0012af9e:    4a09        .J      LDR      r2,[pc,#36] ; [0x12afc4] = 0x12b091
        0x0012afa0:    2105        .!      MOVS     r1,#5
        0x0012afa2:    6803        .h      LDR      r3,[r0,#0]
        0x0012afa4:    4808        .H      LDR      r0,[pc,#32] ; [0x12afc8] = 0x12b10e
        0x0012afa6:    4798        .G      BLX      r3
        0x0012afa8:    bf00        ..      NOP      
        0x0012afaa:    bf00        ..      NOP      
        0x0012afac:    4804        .H      LDR      r0,[pc,#16] ; [0x12afc0] = 0x12b0fc
        0x0012afae:    4a0b        .J      LDR      r2,[pc,#44] ; [0x12afdc] = 0x12acf5
        0x0012afb0:    2108        .!      MOVS     r1,#8
        0x0012afb2:    6843        Ch      LDR      r3,[r0,#4]
        0x0012afb4:    4801        .H      LDR      r0,[pc,#4] ; [0x12afbc] = 0x12b514
        0x0012afb6:    4798        .G      BLX      r3
        0x0012afb8:    bf00        ..      NOP      
        0x0012afba:    e6dd        ..      B        0x12ad78 ; uart_rx_payload_finish + 100
    $d
        0x0012afbc:    0012b514    ....    DCD    1226004
        0x0012afc0:    0012b0fc    ....    DCD    1224956
        0x0012afc4:    0012b091    ....    DCD    1224849
        0x0012afc8:    0012b10e    ....    DCD    1224974
        0x0012afcc:    0012b0f8    ....    DCD    1224952
        0x0012afd0:    0012b0f9    ....    DCD    1224953
        0x0012afd4:    0012b0fa    ....    DCD    1224954
        0x0012afd8:    0012b114    ....    DCD    1224980
        0x0012afdc:    0012acf5    ....    DCD    1223925
    $t
    i.uart_set_baudrate
    uart_set_baudrate
        0x0012afe0:    b510        ..      PUSH     {r4,lr}
        0x0012afe2:    4604        .F      MOV      r4,r0
        0x0012afe4:    2001        .       MOVS     r0,#1
        0x0012afe6:    f7fffced    ....    BL       uart_dlab_setf ; 0x12a9c4
        0x0012afea:    b2e0        ..      UXTB     r0,r4
        0x0012afec:    4904        .I      LDR      r1,[pc,#16] ; [0x12b000] = 0x20143000
        0x0012afee:    6008        .`      STR      r0,[r1,#0]
        0x0012aff0:    bf00        ..      NOP      
        0x0012aff2:    1220         .      ASRS     r0,r4,#8
        0x0012aff4:    6048        H`      STR      r0,[r1,#4]
        0x0012aff6:    bf00        ..      NOP      
        0x0012aff8:    2000        .       MOVS     r0,#0
        0x0012affa:    f7fffce3    ....    BL       uart_dlab_setf ; 0x12a9c4
        0x0012affe:    bd10        ..      POP      {r4,pc}
    $d
        0x0012b000:    20143000    .0.     DCD    538193920
    $t
    i.uart_sync_to_pc
    uart_sync_to_pc
        0x0012b004:    b510        ..      PUSH     {r4,lr}
        0x0012b006:    4803        .H      LDR      r0,[pc,#12] ; [0x12b014] = 0x12b0fc
        0x0012b008:    4a03        .J      LDR      r2,[pc,#12] ; [0x12b018] = 0x12acf5
        0x0012b00a:    2108        .!      MOVS     r1,#8
        0x0012b00c:    6843        Ch      LDR      r3,[r0,#4]
        0x0012b00e:    4803        .H      LDR      r0,[pc,#12] ; [0x12b01c] = 0x12b514
        0x0012b010:    4798        .G      BLX      r3
        0x0012b012:    bd10        ..      POP      {r4,pc}
    $d
        0x0012b014:    0012b0fc    ....    DCD    1224956
        0x0012b018:    0012acf5    ....    DCD    1223925
        0x0012b01c:    0012b514    ....    DCD    1226004
    $t
    i.uart_thr_empty_isr
    uart_thr_empty_isr
        0x0012b020:    b570        p.      PUSH     {r4-r6,lr}
        0x0012b022:    2400        .$      MOVS     r4,#0
        0x0012b024:    2500        .%      MOVS     r5,#0
        0x0012b026:    e024        $.      B        0x12b072 ; uart_thr_empty_isr + 82
        0x0012b028:    4917        .I      LDR      r1,[pc,#92] ; [0x12b088] = 0x12bd1c
        0x0012b02a:    6849        Ih      LDR      r1,[r1,#4]
        0x0012b02c:    7808        .x      LDRB     r0,[r1,#0]
        0x0012b02e:    4917        .I      LDR      r1,[pc,#92] ; [0x12b08c] = 0x20143000
        0x0012b030:    6008        .`      STR      r0,[r1,#0]
        0x0012b032:    bf00        ..      NOP      
        0x0012b034:    4814        .H      LDR      r0,[pc,#80] ; [0x12b088] = 0x12bd1c
        0x0012b036:    6800        .h      LDR      r0,[r0,#0]
        0x0012b038:    1e40        @.      SUBS     r0,r0,#1
        0x0012b03a:    4913        .I      LDR      r1,[pc,#76] ; [0x12b088] = 0x12bd1c
        0x0012b03c:    6008        .`      STR      r0,[r1,#0]
        0x0012b03e:    4608        .F      MOV      r0,r1
        0x0012b040:    6840        @h      LDR      r0,[r0,#4]
        0x0012b042:    1c40        @.      ADDS     r0,r0,#1
        0x0012b044:    6048        H`      STR      r0,[r1,#4]
        0x0012b046:    4608        .F      MOV      r0,r1
        0x0012b048:    6800        .h      LDR      r0,[r0,#0]
        0x0012b04a:    2800        .(      CMP      r0,#0
        0x0012b04c:    d111        ..      BNE      0x12b072 ; uart_thr_empty_isr + 82
        0x0012b04e:    6048        H`      STR      r0,[r1,#4]
        0x0012b050:    f7fffd1c    ....    BL       uart_etbei_setf ; 0x12aa8c
        0x0012b054:    480c        .H      LDR      r0,[pc,#48] ; [0x12b088] = 0x12bd1c
        0x0012b056:    6884        .h      LDR      r4,[r0,#8]
        0x0012b058:    68c5        .h      LDR      r5,[r0,#0xc]
        0x0012b05a:    2c00        .,      CMP      r4,#0
        0x0012b05c:    d007        ..      BEQ      0x12b06e ; uart_thr_empty_isr + 78
        0x0012b05e:    2000        .       MOVS     r0,#0
        0x0012b060:    4909        .I      LDR      r1,[pc,#36] ; [0x12b088] = 0x12bd1c
        0x0012b062:    6088        .`      STR      r0,[r1,#8]
        0x0012b064:    60c8        .`      STR      r0,[r1,#0xc]
        0x0012b066:    2100        .!      MOVS     r1,#0
        0x0012b068:    4628        (F      MOV      r0,r5
        0x0012b06a:    47a0        .G      BLX      r4
        0x0012b06c:    e000        ..      B        0x12b070 ; uart_thr_empty_isr + 80
        0x0012b06e:    bf00        ..      NOP      
        0x0012b070:    e007        ..      B        0x12b082 ; uart_thr_empty_isr + 98
        0x0012b072:    bf00        ..      NOP      
        0x0012b074:    4805        .H      LDR      r0,[pc,#20] ; [0x12b08c] = 0x20143000
        0x0012b076:    3040        @0      ADDS     r0,r0,#0x40
        0x0012b078:    6bc0        .k      LDR      r0,[r0,#0x3c]
        0x0012b07a:    0780        ..      LSLS     r0,r0,#30
        0x0012b07c:    0fc0        ..      LSRS     r0,r0,#31
        0x0012b07e:    2800        .(      CMP      r0,#0
        0x0012b080:    d1d2        ..      BNE      0x12b028 ; uart_thr_empty_isr + 8
        0x0012b082:    bf00        ..      NOP      
        0x0012b084:    bd70        p.      POP      {r4-r6,pc}
    $d
        0x0012b086:    0000        ..      DCW    0
        0x0012b088:    0012bd1c    ....    DCD    1228060
        0x0012b08c:    20143000    .0.     DCD    538193920
    $t
    i.uart_tx_finish
    uart_tx_finish
        0x0012b090:    4770        pG      BX       lr
        0x0012b092:    0000        ..      MOVS     r0,r0
    i.uart_write
    uart_write
        0x0012b094:    b5f8        ..      PUSH     {r3-r7,lr}
        0x0012b096:    4604        .F      MOV      r4,r0
        0x0012b098:    460d        .F      MOV      r5,r1
        0x0012b09a:    4616        .F      MOV      r6,r2
        0x0012b09c:    461f        .F      MOV      r7,r3
        0x0012b09e:    4804        .H      LDR      r0,[pc,#16] ; [0x12b0b0] = 0x12bd1c
        0x0012b0a0:    6005        .`      STR      r5,[r0,#0]
        0x0012b0a2:    6044        D`      STR      r4,[r0,#4]
        0x0012b0a4:    6086        .`      STR      r6,[r0,#8]
        0x0012b0a6:    60c7        .`      STR      r7,[r0,#0xc]
        0x0012b0a8:    2001        .       MOVS     r0,#1
        0x0012b0aa:    f7fffcef    ....    BL       uart_etbei_setf ; 0x12aa8c
        0x0012b0ae:    bdf8        ..      POP      {r3-r7,pc}
    $d
        0x0012b0b0:    0012bd1c    ....    DCD    1228060
    $t
    i.uart_write_register
    uart_write_register
        0x0012b0b4:    6001        .`      STR      r1,[r0,#0]
        0x0012b0b6:    4770        pG      BX       lr
    $d.realdata
    .constdata
        0x0012b0b8:    00000000    ....    DCD    0
        0x0012b0bc:    00000000    ....    DCD    0
        0x0012b0c0:    00000000    ....    DCD    0
        0x0012b0c4:    00009240    @...    DCD    37440
        0x0012b0c8:    20300060    `.0     DCD    540016736
        0x0012b0cc:    00000000    ....    DCD    0
        0x0012b0d0:    00000000    ....    DCD    0
        0x0012b0d4:    0000a480    ....    DCD    42112
        0x0012b0d8:    203000ec    ..0     DCD    540016876
        0x0012b0dc:    00000000    ....    DCD    0
        0x0012b0e0:    00000000    ....    DCD    0
        0x0012b0e4:    0000a482    ....    DCD    42114
    Region$$Table$$Base
        0x0012b0e8:    0012b114    ....    DCD    1224980
        0x0012b0ec:    0012b114    ....    DCD    1224980
        0x0012b0f0:    00002c2c    ,,..    DCD    11308
        0x0012b0f4:    0012a144    D...    DCD    1220932
    Region$$Table$$Limit

====================================

** Section #3

    Name        : EXEC_SECTION
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : SHF_ALLOC + SHF_WRITE (0x00000003)
    Addr        : 0x0012b0f8
    File Offset : 4412 (0x113c)
    Size        : 28 bytes (0x1c)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 4
    Entry Size  : 0

    0x12b0f8:   00 00 00 00 00 00 00 00 00 00 00 00 42 58 53 0d    ............BXS.
    0x12b108:   0a 42 58 41 0d 0a 42 58 4e 0d 0a 00                .BXA..BXN...


====================================

** Section #4

    Name        : EXEC_SECTION
    Type        : SHT_NOBITS (0x00000008)
    Flags       : SHF_ALLOC + SHF_WRITE (0x00000003)
    Addr        : 0x0012b114
    File Offset : 4440 (0x1158)
    Size        : 11308 bytes (0x2c2c)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 8
    Entry Size  : 0


====================================

** Section #5

    Name        : .debug_abbrev
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 4440 (0x1158)
    Size        : 1476 bytes (0x5c4)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #6

    Name        : .debug_frame
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 5916 (0x171c)
    Size        : 1856 bytes (0x740)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #7

    Name        : .debug_info
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 7772 (0x1e5c)
    Size        : 93708 bytes (0x16e0c)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #8

    Name        : .debug_line
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 101480 (0x18c68)
    Size        : 9308 bytes (0x245c)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #9

    Name        : .debug_loc
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 110788 (0x1b0c4)
    Size        : 4940 bytes (0x134c)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #10

    Name        : .debug_macinfo
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 115728 (0x1c410)
    Size        : 8680 bytes (0x21e8)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #11

    Name        : .debug_pubnames
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 124408 (0x1e5f8)
    Size        : 1463 bytes (0x5b7)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #12

    Name        : .symtab
    Type        : SHT_SYMTAB (0x00000002)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 125872 (0x1ebb0)
    Size        : 4848 bytes (0x12f0)
    Link        : Section 13 (.strtab)
    Info        : Last local symbol no = 213
    Alignment   : 4
    Entry Size  : 16


====================================

** Section #13

    Name        : .strtab
    Type        : SHT_STRTAB (0x00000003)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 130720 (0x1fea0)
    Size        : 3664 bytes (0xe50)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #14

    Name        : .note
    Type        : SHT_NOTE (0x00000007)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 134384 (0x20cf0)
    Size        : 32 bytes (0x20)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 4
    Entry Size  : 0

        Section     Segment
    ====================================

              1           0
              2           0
              3           0
              4           0

====================================

** Section #15

    Name        : .comment
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 134416 (0x20d10)
    Size        : 13196 bytes (0x338c)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0

    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armlink [4d35ed]
    ArmLink --strict --library_type=microlib --callgraph --load_addr_map_info --map --symbols --xref --diag_suppress=9931 --cpu=Cortex-M0+ --list=.\Listings\boot_ram_download.map --output=.\Objects\boot_ram_download.axf --scatter=.\boot_ram_scatter.txt --info=summarysizes,sizes,totals,unused,veneers

    E:\installsoft\Keil\mdk525\ARM\ARMCC\Bin\..\lib\armlib\h_p.l
    E:\installsoft\Keil\mdk525\ARM\ARMCC\Bin\..\lib\armlib\m_ps.l
    E:\installsoft\Keil\mdk525\ARM\ARMCC\Bin\..\lib\armlib\mc_p.l
    E:\installsoft\Keil\mdk525\ARM\ARMCC\Bin\..\lib\armlib\mf_p.l
    E:\installsoft\Keil\mdk525\ARM\ARMCC\Bin\..\lib\armlib\vfpsupport.l
    Input Comments:
    
    boot_ram.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armlink [4d35ed]
    armlink --partial --no_add_relocs_to_undefined --no_generate_mapping_symbols --diag_suppress=9931,9931,6642 --cpu=Cortex-M0+ --fpu=SoftVFP --output=.\objects\boot_ram.o --vfemode=force

    Input Comments:
    
    p38c8-3
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armasm [4d35ec]
    armasm --debug --diag_suppress=9931,9931,1602,1073 --cpu=Cortex-M0+ --fpu=SoftVFP --apcs=/interwork/interwork --no_divide 
    boot_ram.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]
    ArmCC --c99 --split_sections --debug -c -o.\objects\boot_ram.o --depend=.\objects\boot_ram.d --cpu=Cortex-M0+ --apcs=interwork -O0 -Otime --diag_suppress=9931 -I.\uart -I.\qspi -I.\flash -I.\dmac -I.\uart_awo -I.\clkg -I..\..\bootloader -IC:\Keil_v5\ARM\Pack\ARM\CMSIS\4.5.0\CMSIS\Include -I.\clkg -I.\dmac -I.\flash -I.\qspi -I.\uart -I.\uart_awo -I.\user_file -I.\log -I.\log\RTT -I..\..\..\..\ip\ble\ll -I.\arch -I.\arch\boot -I.\arch\boot\armcc -I.\arch\boot\armgcc -I.\arch\compiler -I.\arch\compiler\armcc -I.\arch\compiler\armgcc -I.\arch\compiler\iar -I.\arch\ll -I.\arch\ll\armcc -I.\arch\ll\armgcc -I.\rwip\api -I.\sleep -I.\nvds\api -I.\reg\fw -I.\common\api -I..\boot_ram -I.\ -I..\..\..\..\ -I.\RTE\_Target_1 -IE:\installsoft\Keil\mdk525\ARM\PACK\ARM\CMSIS\5.3.0\Device\ARM\ARMCM0plus\Include -IE:\installsoft\Keil\mdk525\ARM\CMSIS\Include -D__MICROLIB -D__UVISION_VERSION=525 -DARMCM0P -DNDEBUG -DHW_BX_VERSION=2400 --omf_browse=.\objects\boot_ram.crf boot_ram.c
    
    
    
    
    
    uart_download.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armlink [4d35ed]
    armlink --partial --no_add_relocs_to_undefined --no_generate_mapping_symbols --diag_suppress=9931,9931,6642 --cpu=Cortex-M0+ --fpu=SoftVFP --output=.\objects\uart_download.o --vfemode=force

    Input Comments:
    
    p4fc0-3
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armasm [4d35ec]
    armasm --debug --diag_suppress=9931,9931,1602,1073 --cpu=Cortex-M0+ --fpu=SoftVFP --apcs=/interwork/interwork --no_divide 
    uart_download.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]
    ArmCC --c99 --split_sections --debug -c -o.\objects\uart_download.o --depend=.\objects\uart_download.d --cpu=Cortex-M0+ --apcs=interwork -O0 -Otime --diag_suppress=9931 -I..\..\bootloader -IC:\Keil_v5\ARM\Pack\ARM\CMSIS\4.5.0\CMSIS\Include -I.\clkg -I.\dmac -I.\flash -I.\qspi -I.\uart -I.\uart_awo -I.\user_file -I.\log -I.\log\RTT -I..\..\..\..\ip\ble\ll -I.\arch -I.\arch\boot -I.\arch\boot\armcc -I.\arch\boot\armgcc -I.\arch\compiler -I.\arch\compiler\armcc -I.\arch\compiler\armgcc -I.\arch\compiler\iar -I.\arch\ll -I.\arch\ll\armcc -I.\arch\ll\armgcc -I.\rwip\api -I.\sleep -I.\nvds\api -I.\reg\fw -I.\common\api -I..\boot_ram -I.\ -I..\..\..\..\ -I.\RTE\_Target_1 -IE:\installsoft\Keil\mdk525\ARM\PACK\ARM\CMSIS\5.3.0\Device\ARM\ARMCM0plus\Include -IE:\installsoft\Keil\mdk525\ARM\CMSIS\Include -D__MICROLIB -D__UVISION_VERSION=525 -DARMCM0P -DNDEBUG -DHW_BX_VERSION=2400 --omf_browse=.\objects\uart_download.crf uart_download.c
    
    
    startup_uart_download.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armasm [4d35ec]
    ArmAsm --debug --xref --diag_suppress=9931 --cpu=Cortex-M0+ --apcs=interwork --depend=.\objects\startup_uart_download.d  -I.\RTE\_Target_1 -IE:\installsoft\Keil\mdk525\ARM\PACK\ARM\CMSIS\5.3.0\Device\ARM\ARMCM0plus\Include -IE:
    
    
    uart.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armlink [4d35ed]
    armlink --partial --no_add_relocs_to_undefined --no_generate_mapping_symbols --diag_suppress=9931,9931,6642 --cpu=Cortex-M0+ --fpu=SoftVFP --output=.\objects\uart.o --vfemode=force

    Input Comments:
    
    p518-3
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armasm [4d35ec]
    armasm --debug --diag_suppress=9931,9931,1602,1073 --cpu=Cortex-M0+ --fpu=SoftVFP --apcs=/interwork/interwork --no_divide 
    uart.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]
    ArmCC --c99 --split_sections --debug -c -o.\objects\uart.o --depend=.\objects\uart.d --cpu=Cortex-M0+ --apcs=interwork -O0 -Otime --diag_suppress=9931 -I..\..\bootloader -IC:\Keil_v5\ARM\Pack\ARM\CMSIS\4.5.0\CMSIS\Include -I.\clkg -I.\dmac -I.\flash -I.\qspi -I.\uart -I.\uart_awo -I.\user_file -I.\log -I.\log\RTT -I..\..\..\..\ip\ble\ll -I.\arch -I.\arch\boot -I.\arch\boot\armcc -I.\arch\boot\armgcc -I.\arch\compiler -I.\arch\compiler\armcc -I.\arch\compiler\armgcc -I.\arch\compiler\iar -I.\arch\ll -I.\arch\ll\armcc -I.\arch\ll\armgcc -I.\rwip\api -I.\sleep -I.\nvds\api -I.\reg\fw -I.\common\api -I..\boot_ram -I.\ -I..\..\..\..\ -I.\RTE\_Target_1 -IE:\installsoft\Keil\mdk525\ARM\PACK\ARM\CMSIS\5.3.0\Device\ARM\ARMCM0plus\Include -IE:\installsoft\Keil\mdk525\ARM\CMSIS\Include -D__MICROLIB -D__UVISION_VERSION=525 -DARMCM0P -DNDEBUG -DHW_BX_VERSION=2400 --omf_browse=.\objects\uart.crf uart\uart.c
    
    
    
    
    pshare_rom.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armlink [4d35ed]
    armlink --partial --no_add_relocs_to_undefined --no_generate_mapping_symbols --diag_suppress=9931,9931,6642 --cpu=Cortex-M0+ --fpu=SoftVFP --output=.\objects\pshare_rom.o --vfemode=force

    Input Comments:
    
    p3a94-3
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armasm [4d35ec]
    armasm --debug --diag_suppress=9931,9931,1602,1073 --cpu=Cortex-M0+ --fpu=SoftVFP --apcs=/interwork/interwork --no_divide 
    pshare_rom.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]
    ArmCC --c99 --split_sections --debug -c -o.\objects\pshare_rom.o --depend=.\objects\pshare_rom.d --cpu=Cortex-M0+ --apcs=interwork -O0 -Otime --diag_suppress=9931 -I..\..\bootloader -IC:\Keil_v5\ARM\Pack\ARM\CMSIS\4.5.0\CMSIS\Include -I.\clkg -I.\dmac -I.\flash -I.\qspi -I.\uart -I.\uart_awo -I.\user_file -I.\log -I.\log\RTT -I..\..\..\..\ip\ble\ll -I.\arch -I.\arch\boot -I.\arch\boot\armcc -I.\arch\boot\armgcc -I.\arch\compiler -I.\arch\compiler\armcc -I.\arch\compiler\armgcc -I.\arch\compiler\iar -I.\arch\ll -I.\arch\ll\armcc -I.\arch\ll\armgcc -I.\rwip\api -I.\sleep -I.\nvds\api -I.\reg\fw -I.\common\api -I..\boot_ram -I.\ -I..\..\..\..\ -I.\RTE\_Target_1 -IE:\installsoft\Keil\mdk525\ARM\PACK\ARM\CMSIS\5.3.0\Device\ARM\ARMCM0plus\Include -IE:\installsoft\Keil\mdk525\ARM\CMSIS\Include -D__MICROLIB -D__UVISION_VERSION=525 -DARMCM0P -DNDEBUG -DHW_BX_VERSION=2400 --omf_browse=.\objects\pshare_rom.crf pshare_rom.c
    
    
    
    
    segger_rtt.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]
    ArmCC --c99 --split_sections --debug -c -o.\objects\segger_rtt.o --depend=.\objects\segger_rtt.d --cpu=Cortex-M0+ --apcs=interwork -O0 -Otime --diag_suppress=9931 -I..\..\bootloader -IC:\Keil_v5\ARM\Pack\ARM\CMSIS\4.5.0\CMSIS\Include -I.\clkg -I.\dmac -I.\flash -I.\qspi -I.\uart -I.\uart_awo -I.\user_file -I.\log -I.\log\RTT -I..\..\..\..\ip\ble\ll -I.\arch -I.\arch\boot -I.\arch\boot\armcc -I.\arch\boot\armgcc -I.\arch\compiler -I.\arch\compiler\armcc -I.\arch\compiler\armgcc -I.\arch\compiler\iar -I.\arch\ll -I.\arch\ll\armcc -I.\arch\ll\armgcc -I.\rwip\api -I.\sleep -I.\nvds\api -I.\reg\fw -I.\common\api -I..\boot_ram -I.\ -I..\..\..\..\ -I.\RTE\_Target_1 -IE:\installsoft\Keil\mdk525\ARM\PACK\ARM\CMSIS\5.3.0\Device\ARM\ARMCM0plus\Include -IE:\installsoft\Keil\mdk525\ARM\CMSIS\Include -D__MICROLIB -D__UVISION_VERSION=525 -DARMCM0P -DNDEBUG -DHW_BX_VERSION=2400 --omf_browse=.\objects\segger_rtt.crf log\RTT\SEGGER_RTT.c
    
    segger_rtt_printf.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]
    ArmCC --c99 --split_sections --debug -c -o.\objects\segger_rtt_printf.o --depend=.\objects\segger_rtt_printf.d --cpu=Cortex-M0+ --apcs=interwork -O0 -Otime --diag_suppress=9931 -I..\..\bootloader -IC:\Keil_v5\ARM\Pack\ARM\CMSIS\4.5.0\CMSIS\Include -I.\clkg -I.\dmac -I.\flash -I.\qspi -I.\uart -I.\uart_awo -I.\user_file -I.\log -I.\log\RTT -I..\..\..\..\ip\ble\ll -I.\arch -I.\arch\boot -I.\arch\boot\armcc -I.\arch\boot\armgcc -I.\arch\compiler -I.\arch\compiler\armcc -I.\arch\compiler\armgcc -I.\arch\compiler\iar -I.\arch\ll -I.\arch\ll\armcc -I.\arch\ll\armgcc -I.\rwip\api -I.\sleep -I.\nvds\api -I.\reg\fw -I.\common\api -I..\boot_ram -I.\ -I..\..\..\..\ -I.\RTE\_Target_1 -IE:\installsoft\Keil\mdk525\ARM\PACK\ARM\CMSIS\5.3.0\Device\ARM\ARMCM0plus\Include -IE:\installsoft\Keil\mdk525\ARM\CMSIS\Include -D__MICROLIB -D__UVISION_VERSION=525 -DARMCM0P -DNDEBUG -DHW_BX_VERSION=2400 --omf_browse=.\objects\segger_rtt_printf.crf log\RTT\SEGGER_RTT_printf.c
    
    dma_for_qspi.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armlink [4d35ed]
    armlink --partial --no_add_relocs_to_undefined --no_generate_mapping_symbols --diag_suppress=9931,9931,6642 --cpu=Cortex-M0+ --fpu=SoftVFP --output=.\objects\dma_for_qspi.o --vfemode=force

    Input Comments:
    
    p42fc-3
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armasm [4d35ec]
    armasm --debug --diag_suppress=9931,9931,1602,1073 --cpu=Cortex-M0+ --fpu=SoftVFP --apcs=/interwork/interwork --no_divide 
    dma_for_qspi.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]
    ArmCC --c99 --split_sections --debug -c -o.\objects\dma_for_qspi.o --depend=.\objects\dma_for_qspi.d --cpu=Cortex-M0+ --apcs=interwork -O0 -Otime --diag_suppress=9931 -I..\..\bootloader -IC:\Keil_v5\ARM\Pack\ARM\CMSIS\4.5.0\CMSIS\Include -I.\clkg -I.\dmac -I.\flash -I.\qspi -I.\uart -I.\uart_awo -I.\user_file -I.\log -I.\log\RTT -I..\..\..\..\ip\ble\ll -I.\arch -I.\arch\boot -I.\arch\boot\armcc -I.\arch\boot\armgcc -I.\arch\compiler -I.\arch\compiler\armcc -I.\arch\compiler\armgcc -I.\arch\compiler\iar -I.\arch\ll -I.\arch\ll\armcc -I.\arch\ll\armgcc -I.\rwip\api -I.\sleep -I.\nvds\api -I.\reg\fw -I.\common\api -I..\boot_ram -I.\ -I..\..\..\..\ -I.\RTE\_Target_1 -IE:\installsoft\Keil\mdk525\ARM\PACK\ARM\CMSIS\5.3.0\Device\ARM\ARMCM0plus\Include -IE:\installsoft\Keil\mdk525\ARM\CMSIS\Include -D__MICROLIB -D__UVISION_VERSION=525 -DARMCM0P -DNDEBUG -DHW_BX_VERSION=2400 --omf_browse=.\objects\dma_for_qspi.crf ..\boot_ram\dma_for_qspi.c
    
    
    
    
    flash.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]
    ArmCC --c99 --split_sections --debug -c -o.\objects\flash.o --depend=.\objects\flash.d --cpu=Cortex-M0+ --apcs=interwork -O0 -Otime --diag_suppress=9931 -I..\..\bootloader -IC:\Keil_v5\ARM\Pack\ARM\CMSIS\4.5.0\CMSIS\Include -I.\clkg -I.\dmac -I.\flash -I.\qspi -I.\uart -I.\uart_awo -I.\user_file -I.\log -I.\log\RTT -I..\..\..\..\ip\ble\ll -I.\arch -I.\arch\boot -I.\arch\boot\armcc -I.\arch\boot\armgcc -I.\arch\compiler -I.\arch\compiler\armcc -I.\arch\compiler\armgcc -I.\arch\compiler\iar -I.\arch\ll -I.\arch\ll\armcc -I.\arch\ll\armgcc -I.\rwip\api -I.\sleep -I.\nvds\api -I.\reg\fw -I.\common\api -I..\boot_ram -I.\ -I..\..\..\..\ -I.\RTE\_Target_1 -IE:\installsoft\Keil\mdk525\ARM\PACK\ARM\CMSIS\5.3.0\Device\ARM\ARMCM0plus\Include -IE:\installsoft\Keil\mdk525\ARM\CMSIS\Include -D__MICROLIB -D__UVISION_VERSION=525 -DARMCM0P -DNDEBUG -DHW_BX_VERSION=2400 --omf_browse=.\objects\flash.crf ..\boot_ram\flash.c
    
    qspi.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armlink [4d35ed]
    armlink --partial --no_add_relocs_to_undefined --no_generate_mapping_symbols --diag_suppress=9931,9931,6642 --cpu=Cortex-M0+ --fpu=SoftVFP --output=.\objects\qspi.o --vfemode=force

    Input Comments:
    
    p490c-3
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: armasm [4d35ec]
    armasm --debug --diag_suppress=9931,9931,1602,1073 --cpu=Cortex-M0+ --fpu=SoftVFP --apcs=/interwork/interwork --no_divide 
    qspi.o
    
    Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]
    ArmCC --c99 --split_sections --debug -c -o.\objects\qspi.o --depend=.\objects\qspi.d --cpu=Cortex-M0+ --apcs=interwork -O0 -Otime --diag_suppress=9931 -I..\..\bootloader -IC:\Keil_v5\ARM\Pack\ARM\CMSIS\4.5.0\CMSIS\Include -I.\clkg -I.\dmac -I.\flash -I.\qspi -I.\uart -I.\uart_awo -I.\user_file -I.\log -I.\log\RTT -I..\..\..\..\ip\ble\ll -I.\arch -I.\arch\boot -I.\arch\boot\armcc -I.\arch\boot\armgcc -I.\arch\compiler -I.\arch\compiler\armcc -I.\arch\compiler\armgcc -I.\arch\compiler\iar -I.\arch\ll -I.\arch\ll\armcc -I.\arch\ll\armgcc -I.\rwip\api -I.\sleep -I.\nvds\api -I.\reg\fw -I.\common\api -I..\boot_ram -I.\ -I..\..\..\..\ -I.\RTE\_Target_1 -IE:\installsoft\Keil\mdk525\ARM\PACK\ARM\CMSIS\5.3.0\Device\ARM\ARMCM0plus\Include -IE:\installsoft\Keil\mdk525\ARM\CMSIS\Include -D__MICROLIB -D__UVISION_VERSION=525 -DARMCM0P -DNDEBUG -DHW_BX_VERSION=2400 --omf_browse=.\objects\qspi.crf ..\boot_ram\qspi.c
    
    
    
    
    
    
    

====================================

** Section #16

    Name        : .shstrtab
    Type        : SHT_STRTAB (0x00000003)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 147612 (0x2409c)
    Size        : 168 bytes (0xa8)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

address     size       variable name                            type
0x0012bd1c  0x24       uart_env                                 uart_env_tag
0x0012bd1c  0x10       uart_env.tx                              uart_txrxchannel
0x0012bd1c  0x4        uart_env.tx.size                         uint32_t
0x0012bd20  0x4        uart_env.tx.bufptr                       pointer to uint8_t
0x0012bd24  0x4        uart_env.tx.callback                     pointer to function 
0x0012bd28  0x4        uart_env.tx.dummy                        pointer to unknown Type 
0x0012bd2c  0x10       uart_env.rx                              uart_txrxchannel
0x0012bd2c  0x4        uart_env.rx.size                         uint32_t
0x0012bd30  0x4        uart_env.rx.bufptr                       pointer to uint8_t
0x0012bd34  0x4        uart_env.rx.callback                     pointer to function 
0x0012bd38  0x4        uart_env.rx.dummy                        pointer to unknown Type 
0x0012bd3c  0x1        uart_env.errordetect                     _Bool

address     size       variable name                            type
0x0012b114  0x400      bx2400_reg_val                           array[256] of uint32_t

address     size       variable name                            type
0x0012b104  0xf        uart2pc                                  array[3] of array[5] of uint8_t

address     size       variable name                            type
0x0012b514  0x808      uart_buff                                Data_From_Host_t
0x0012b514  0x8        uart_buff.header                         Uart_Ramrun_Header_t
0x0012b514  0x1        uart_buff.header.header_flag             uint8_t
0x0012b515  0x1        uart_buff.header.cmd                     anonymous
0x0012b515  0x1(6:2)   uart_buff.header.cmd.r_w                 uint8_t
0x0012b515  0x1(5:1)   uart_buff.header.cmd.section             uint8_t
0x0012b515  0x1(0:5)   uart_buff.header.cmd.op                  uint8_t
0x0012b516  0x2        uart_buff.header.length                  uint16_t
0x0012b518  0x4        uart_buff.header.addr                    uint32_t
0x0012b51c  0x800      uart_buff.data                           array[2048] of uint8_t

address     size       variable name                            type
0x0012b0fc  0x8        uart_itf                                 anonymous
0x0012b0fc  0x4        uart_itf.tx_func                         write_fn_t
0x0012b100  0x4        uart_itf.rx_func                         read_fn_t

address     size       variable name                            type
0x00129ff0  0x10       boot_header                              const boot_header_t
0x00129ff0  0x4        boot_header.bx_flag                      array[4] of uint8_t
0x00129ff4  0x4        boot_header.base_addr                    pointer to uint8_t
0x00129ff8  0x4        boot_header.length                       uint32_t
0x00129ffc  0x4        boot_header.entry_point                  entry_point_t

address     size       variable name                            type
0x0012b0f9  0x1        check_result                             uint8_t

address     size       variable name                            type
0x0012b0fa  0x1        uart_baud_changed                        uint8_t

address     size       variable name                            type
0x0012b0f8  0x1        wait_download_finish                     uint8_t

