#ifndef LTQ_HAL_H
#define LTQ_HAL_H

#define LTQ_PPE(idx)                            KSEG1ADDR(LTQ_PPE_ORG(idx))
#define PP32_DEBUG_REG_ADDR(i, x)               ((volatile unsigned int*)(LTQ_PPE(2) + (((x) + 0x000000 + (i) * 0x00010000) << 2)))
#define CDM_CODE_MEMORY(i, x)                   ((volatile unsigned int*)(LTQ_PPE(2) + (((x) + 0x001000 + (i) * 0x00010000) << 2)))
#define CDM_DATA_MEMORY(i, x)                   ((volatile unsigned int*)(LTQ_PPE(2) + (((x) + 0x004000 + (i) * 0x00010000) << 2)))
#define SB_RAM0_ADDR(idx, x)                    ((volatile unsigned int*)(LTQ_PPE(idx) + (((x) + 0x008000) << 2)))
#define SB_RAM1_ADDR(idx, x)                    ((volatile unsigned int*)(LTQ_PPE(idx) + (((x) + 0x009000) << 2)))
#define SB_RAM2_ADDR(idx, x)                    ((volatile unsigned int*)(LTQ_PPE(idx) + (((x) + 0x00A000) << 2)))
#define SB_RAM3_ADDR(idx, x)                    ((volatile unsigned int*)(LTQ_PPE(idx) + (((x) + 0x00B000) << 2)))
#define PPE_REG_ADDR(idx, x)                    ((volatile unsigned int*)(LTQ_PPE(idx) + (((x) + 0x00D000) << 2)))
#define QSB_CONF_REG_ADDR(x)                    ((volatile unsigned int*)(LTQ_PPE(2) + (((x) + 0x00E000) << 2)))
#define SB_RAM6_ADDR(idx, x)                    ((volatile unsigned int*)(LTQ_PPE(idx) + (((x) + 0x018000) << 2)))


#endif //LTQ_HAL_H
