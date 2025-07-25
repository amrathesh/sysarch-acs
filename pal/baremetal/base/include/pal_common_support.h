/** @file
 * Copyright (c) 2020-2025, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#ifndef __PAL_COMMON_SUPPORT_H_
#define __PAL_COMMON_SUPPORT_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef uintptr_t addr_t;
typedef char     char8_t;

extern uint32_t g_print_level;
extern uint32_t g_print_mmio;
extern uint32_t g_curr_module;
extern uint32_t g_enable_module;

#define ACS_PRINT_ERR   5      /* Only Errors. use this to de-clutter the terminal and focus only on specifics */
#define ACS_PRINT_WARN  4      /* Only warnings & errors. use this to de-clutter the terminal and focus only on specifics */
#define ACS_PRINT_TEST  3      /* Test description and result descriptions. THIS is DEFAULT */
#define ACS_PRINT_DEBUG 2      /* For Debug statements. contains register dumps etc */
#define ACS_PRINT_INFO  1      /* Print all statements. Do not use unless really needed */

#define MEM_ALIGN_4K       0x1000
#define MEM_ALIGN_8K       0x2000
#define MEM_ALIGN_16K      0x4000
#define MEM_ALIGN_32K      0x8000
#define MEM_ALIGN_64K      0x10000

#ifdef TARGET_BM_BOOT
    #define TRUE 1
    #define FALSE 0
#endif

void pal_mem_free_aligned(void *Buffer);
void *pal_aligned_alloc( uint32_t alignment, uint32_t size );

#define PCIE_EXTRACT_BDF_SEG(bdf)  ((bdf >> 24) & 0xFF)
#define PCIE_EXTRACT_BDF_BUS(bdf)  ((bdf >> 16) & 0xFF)
#define PCIE_EXTRACT_BDF_DEV(bdf)  ((bdf >> 8) & 0xFF)
#define PCIE_EXTRACT_BDF_FUNC(bdf) (bdf & 0xFF)

#define PCIE_CFG_SIZE  4096

#define PCIE_MAX_BUS   256
#define PCIE_MAX_DEV    32
#define PCIE_MAX_FUNC    8

#ifdef TARGET_BM_BOOT
void pal_uart_print(int log, const char *fmt, ...);
void *mem_alloc(size_t alignment, size_t size);
#define print(verbose, string, ...)  if(verbose >= g_print_level) \
                                                   pal_uart_print(verbose, string, ##__VA_ARGS__)
#else
#define print(verbose, string, ...)  if(verbose >= g_print_level) \
                                                   printf(string, ##__VA_ARGS__)
#endif

#define PCIE_CREATE_BDF(Seg, Bus, Dev, Func) ((Seg << 24) | (Bus << 16) | (Dev << 8) | Func)

#define PCIE_SUCCESS            0x00000000  /* Operation completed successfully */
#define PCIE_NO_MAPPING         0x10000001  /* A mapping to a Function does not exist */
#define PCIE_CAP_NOT_FOUND      0x10000010  /* The specified capability was not found */
#define PCIE_UNKNOWN_RESPONSE   0xFFFFFFFF  /* Function not found or UR response from completer */

/* PCI/PCIe express extended capability structure's
   next capability pointer mask and cap ID mask */
#define PCIE_NXT_CAP_PTR_MASK 0x0FFF
#define PCIE_CAP_ID_MASK      0xFFFF
#define PCI_CAP_ID_MASK       0x00FF
#define PCI_NXT_CAP_PTR_MASK  0x00FF
#define CAP_PTR_MASK          0x00FF
#define PCIE_CAP_OFFSET       0x100
#define CAP_PTR_OFFSET        0x34

#define PCI_CAP_PTR_OFFSET    8
#define PCIE_CAP_PTR_OFFSET   20

/* TYPE 0/1 Cmn Cfg reg offsets and mask*/
#define TYPE01_CPR           0x34
#define TYPE01_CPR_MASK      0xff
#define COMMAND_REG_OFFSET   0x04
#define REG_ACC_DATA         0x7

#define BAR_MASK        0xFFFFFFF0
#define BAR64_MASK      0xFFFFFFFFFFFFFFF0

/* Class Code Masks */
#define CC_SUB_MASK     0xFF   /* Sub Class */
#define CC_BASE_MASK    0xFF   /* Base Class */

/* Class Code Shifts */
#define CC_SHIFT        8
#define CC_SUB_SHIFT    16
#define CC_BASE_SHIFT   24

#define HB_BASE_CLASS   0x06
#define HB_SUB_CLASS    0x00

/* Device Type Shift and mask*/
#define PCIE_DEVICE_TYPE_SHIFT  20
#define PCIE_DEVICE_TYPE_MASK   0xf
#define PCI_EXP_DEVCTL          8
#define DEVCTL_SNOOP_BIT        11

/* Bus Number reg shifts */
#define SECBN_SHIFT 8
#define SUBBN_SHIFT 16

/* Bus Number reg masks */
#define SECBN_MASK  0xff
#define SUBBN_MASK  0xff

/* Capability header reg shifts */
#define PCIE_CIDR_SHIFT      0
#define PCIE_NCPR_SHIFT      8
#define PCIE_ECAP_CIDR_SHIFT 0
#define PCIE_ECAP_NCPR_SHIFT 20

/* Capability header reg masks */
#define PCIE_CIDR_MASK       0xff
#define PCIE_NCPR_MASK       0xff
#define PCIE_ECAP_CIDR_MASK  0xffff
#define PCIE_ECAP_NCPR_MASK  0xfff

#define PCIE_ECAP_START      0x100

/* Capability Structure IDs */
#define CID_PCIECS           0x10
#define CID_MSI              0x05
#define CID_MSIX             0x11
#define ECID_PASID           0x001b

/* PCI Express capability struct offsets */
#define CIDR_OFFSET    0x0
#define PCIECR_OFFSET  0x2
#define DCAPR_OFFSET   0x4
#define DCTLR_OFFSET   0x8
#define DCAP2R_OFFSET  0x24
#define DCTL2R_OFFSET  0x28

/* RAS related Offset, shift and mask */
#define RAS_OFFSET     0x10000
#define CTRL_OFFSET    0x08
#define STATUS_OFFSET  0x10

/* PCIe capabilities reg shifts and masks */
#define PCIECR_DPT_SHIFT 4
#define PCIECR_DPT_MASK  0xf

#define PASID_OFFSET         0x04
#define PASID_NUM_SHIFT      8
#define PASID_NUM_MASK       0x1f
#define PER_FLAG_MSI_ENABLED 0x2

/* Device bitmask definitions */
#define RCiEP    (1 << 0b1001)
#define RCEC     (1 << 0b1010)
#define EP       (1 << 0b0000)
#define RP       (1 << 0b0100)
#define UP       (1 << 0b0101)
#define DP       (1 << 0b0110)
#define iEP_EP   (1 << 0b1100)
#define iEP_RP   (1 << 0b1011)

#define CLEAN_AND_INVALIDATE  0x1
#define CLEAN                 0x2
#define INVALIDATE            0x3

#define NOT_IMPLEMENTED       0x4B1D

#define MEM_SIZE_64K              0x10000

#define ATTR_NORMAL_NONCACHEABLE  (0x0ull << 2)
#define ATTR_NORMAL_WB_WA_RA      (0x1ull << 2)
#define ATTR_DEVICE               (0x2ull << 2)
#define ATTR_NORMAL_WB            (0x1ull << 3)

/* Stage 1 Inner and Outer Cacheability attribute encoding without TEX remap */
#define ATTR_S1_NONCACHEABLE   (0x0ull << 2)
#define ATTR_S1_WB_WA_RA       (0x1ull << 2)
#define ATTR_S1_WT_RA          (0x2ull << 2)
#define ATTR_S1_WB_RA          (0x3ull << 2)

/* Stage 2 MemAttr[1:0] encoding for Normal memory */
#define ATTR_S2_INNER_NONCACHEABLE   (0x1ull << 2)
#define ATTR_S2_INNER_WT_CACHEABLE   (0x2ull << 2)
#define ATTR_S2_INNER_WB_CACHEABLE   (0x3ull << 2)

#define ATTR_NS   (0x1ull << 5)
#define ATTR_S    (0x0ull << 5)

#define ATTR_STAGE1_AP_RW    (0x1ull << 6)
#define ATTR_STAGE2_AP_RW    (0x3ull << 6)
#define ATTR_STAGE2_MASK     (0x3ull << 6 | 0x1ull << 4)
#define ATTR_STAGE2_MASK_RO  (0x1ull << 6 | 0x1ull << 4)

#define ATTR_NON_SHARED     (0x0ull << 8)
#define ATTR_OUTER_SHARED   (0x2ull << 8)
#define ATTR_INNER_SHARED   (0x3ull << 8)

#define ATTR_AF     (0x1ull << 10)
#define ATTR_nG     (0x1ull << 11)
#define ATTR_UXN    (0x1ull << 54)
#define ATTR_PXN    (0x1ull << 53)

#define ATTR_PRIV_RW        (0x0ull << 6)
#define ATTR_PRIV_RO        (0x2ull << 6)
#define ATTR_USER_RW        (0x1ull << 6)
#define ATTR_USER_RO        (0x3ull << 6)

#define ATTR_CODE           (ATTR_S1_WB_WA_RA | ATTR_USER_RO | \
                              ATTR_AF | ATTR_INNER_SHARED | ATTR_NS)
#define ATTR_RO_DATA        (ATTR_S1_WB_WA_RA | ATTR_USER_RO | \
                              ATTR_UXN | ATTR_PXN | ATTR_AF | \
                              ATTR_INNER_SHARED | ATTR_NS)
#define ATTR_RW_DATA        (ATTR_S1_WB_WA_RA | \
                              ATTR_USER_RW | ATTR_UXN | ATTR_PXN | ATTR_AF \
                              | ATTR_INNER_SHARED | ATTR_NS)
#define ATTR_DEVICE_RW      (ATTR_DEVICE | ATTR_USER_RW | ATTR_UXN | \
                              ATTR_PXN | ATTR_AF | ATTR_INNER_SHARED | ATTR_NS)
#define ATTR_RW_DATA_NC      (ATTR_S1_NONCACHEABLE | \
                              ATTR_USER_RW | ATTR_UXN | ATTR_PXN | ATTR_AF \
                              | ATTR_INNER_SHARED | ATTR_NS)

typedef struct {
  uint64_t   Arg0;
  uint64_t   Arg1;
  uint64_t   Arg2;
  uint64_t   Arg3;
  uint64_t   Arg4;
  uint64_t   Arg5;
  uint64_t   Arg6;
  uint64_t   Arg7;
} ARM_SMC_ARGS;

typedef struct {
  uint32_t num_of_pe;
} PE_INFO_HDR;

#define MAX_L1_CACHE_RES 2 /* Generally PE Level 1 have a data and a instruction cache */

/**
  @brief  structure instance for PE entry
**/
typedef struct {
  uint32_t   pe_num;                        /* PE Index */
  uint32_t   attr;                          /* PE attributes */
  uint64_t   mpidr;                         /* PE MPIDR */
  uint32_t   pmu_gsiv;                      /* PMU Interrupt ID */
  uint32_t   gmain_gsiv;                    /* GIC Maintenance Interrupt ID */
  uint32_t   acpi_proc_uid;                 /* ACPI Processor UID */
  uint32_t   level_1_res[MAX_L1_CACHE_RES]; /* index of level 1 cache(s) in cache_info_table */
  uint32_t   trbe_interrupt;                /* TRBE Interrupt */
} PE_INFO_ENTRY;

typedef struct {
  PE_INFO_HDR    header;
  PE_INFO_ENTRY  pe_info[];
} PE_INFO_TABLE;

/**
  @brief  Instance of smbios type 4 processor info
**/
typedef struct {
  uint16_t processor_family;
  uint16_t core_count;
} PE_SMBIOS_TYPE4_INFO;

/**
  @brief  Instance of smbios info
**/
typedef struct {
  uint32_t slot_count;
  PE_SMBIOS_TYPE4_INFO type4_info[];
} PE_SMBIOS_PROCESSOR_INFO_TABLE;

void pal_pe_data_cache_ops_by_va(uint64_t addr, uint32_t type);

typedef struct {
  uint32_t   gic_version;
  uint32_t   num_gicd;
  uint32_t   num_gicc_rd;
  uint32_t   num_gicr_rd;
  uint32_t   num_its;
  uint32_t   num_msi_frames;
  uint32_t   num_gich;
}GIC_INFO_HDR;


/* Interrupt Trigger Type */
typedef enum {
  INTR_TRIGGER_INFO_LEVEL_LOW,
  INTR_TRIGGER_INFO_LEVEL_HIGH,
  INTR_TRIGGER_INFO_EDGE_FALLING,
  INTR_TRIGGER_INFO_EDGE_RISING
}INTR_TRIGGER_INFO_TYPE_e;

/**
  @brief  structure instance for GIC entry
**/
typedef struct {
  uint32_t type;
  uint64_t base;
  uint32_t entry_id;  /* This entry_id is used to tell component ID */
  uint64_t length;  /* This length is only used in case of Re-Distributor Range Address length */
  uint32_t flags;
  uint32_t spi_count;
  uint32_t spi_base;
}GIC_INFO_ENTRY;

/**
  @brief  GIC Information Table
**/
typedef struct {
  GIC_INFO_HDR   header;
  GIC_INFO_ENTRY gic_info[];  ///< Array of Information blocks - instantiated for each GIC type
}GIC_INFO_TABLE;

typedef struct {
  uint32_t s_el1_timer_flag;
  uint32_t ns_el1_timer_flag;
  uint32_t el2_timer_flag;
  uint32_t el2_virt_timer_flag;
  uint32_t s_el1_timer_gsiv;
  uint32_t ns_el1_timer_gsiv;
  uint32_t el2_timer_gsiv;
  uint32_t virtual_timer_flag;
  uint32_t virtual_timer_gsiv;
  uint32_t el2_virt_timer_gsiv;
  uint32_t num_platform_timer;
  uint32_t num_watchdog;
  uint32_t sys_timer_status;
}TIMER_INFO_HDR;

#define TIMER_TYPE_SYS_TIMER 0x2001

/**
  @brief  structure instance for TIMER entry
**/
typedef struct {
  uint32_t type;
  uint32_t timer_count;
  uint64_t block_cntl_base;
  uint8_t  frame_num[8];
  uint64_t GtCntBase[8];
  uint64_t GtCntEl0Base[8];
  uint32_t gsiv[8];
  uint32_t virt_gsiv[8];
  uint32_t flags[8];
}TIMER_INFO_GTBLOCK;

typedef struct {
  TIMER_INFO_HDR     header;
  TIMER_INFO_GTBLOCK gt_info[];
}TIMER_INFO_TABLE;

/**
  @brief  Watchdog Info header - Summary of Watchdog subsytem
**/
typedef struct {
  uint32_t num_wd;  ///< number of Watchdogs present in the system
}WD_INFO_HDR;

/**
  @brief  structure instance for Watchdog entry
**/
typedef struct {
  uint64_t wd_ctrl_base;     ///< Watchdog Control Register Frame
  uint64_t wd_refresh_base;  ///< Watchdog Refresh Register Frame
  uint32_t wd_gsiv;          ///< Watchdog Interrupt ID
  uint32_t wd_flags;
}WD_INFO_BLOCK;

/**
  @brief Watchdog Info Table
**/
typedef struct {
  WD_INFO_HDR    header;
  WD_INFO_BLOCK  wd_info[];  ///< Array of Information blocks - instantiated for each WD Controller
}WD_INFO_TABLE;

/**
  @brief PCIe Info Table
**/

#define LEGACY_PCI_IRQ_CNT 4  // Legacy PCI IRQ A, B, C. and D
#define MAX_IRQ_CNT 0xFFFF    // This value is arbitrary and may have to be adjusted

typedef struct {
  uint32_t  irq_list[MAX_IRQ_CNT];
  uint32_t  irq_count;
} PERIFERAL_IRQ_LIST;

typedef struct {
  PERIFERAL_IRQ_LIST  legacy_irq_map[LEGACY_PCI_IRQ_CNT];
} PERIPHERAL_IRQ_MAP;

typedef struct {
  uint64_t   ecam_base;     ///< ECAM Base address
  uint32_t   segment_num;   ///< Segment number of this ECAM
  uint32_t   start_bus_num; ///< Start Bus number for this ecam space
  uint32_t   end_bus_num;   ///< Last Bus number
} PCIE_INFO_BLOCK;

typedef struct {
  uint32_t  num_entries;
  PCIE_INFO_BLOCK block[];
} PCIE_INFO_TABLE;

typedef struct {
  uint64_t   class_code;
  uint32_t   device_id;
  uint32_t   vendor_id;
  uint32_t   bus;
  uint32_t   dev;
  uint32_t   func;
  uint32_t   seg;
  uint32_t   dma_support;
  uint32_t   dma_coherent;
  uint32_t   p2p_support;
  uint32_t   dma_64bit;
  uint32_t   behind_smmu;
  uint32_t   atc_present;
  PERIPHERAL_IRQ_MAP irq_map;
} PCIE_READ_BLOCK;

typedef struct {
  uint32_t num_entries;
  PCIE_READ_BLOCK device[];
} PCIE_READ_TABLE;

typedef enum {
  NON_PREFETCH_MEMORY = 0x0,
  PREFETCH_MEMORY = 0x1
}PCIE_MEM_TYPE_INFO_e;

typedef struct {
  uint32_t bdf;
  uint32_t rp_bdf;
} pcie_device_attr;

typedef struct {
  uint32_t num_entries;
  pcie_device_attr device[];         ///< in the format of Segment/Bus/Dev/Func
} pcie_device_bdf_table;


typedef struct {
  uint32_t    num_usb;   ///< Number of USB  Controllers
  uint32_t    num_sata;  ///< Number of SATA Controllers
  uint32_t    num_uart;  ///< Number of UART Controllers
  uint32_t    num_all;   ///< Number of all PCI Controllers
}PERIPHERAL_INFO_HDR;

typedef enum {
  PERIPHERAL_TYPE_USB = 0x2000,
  PERIPHERAL_TYPE_SATA,
  PERIPHERAL_TYPE_UART,
  PERIPHERAL_TYPE_OTHER,
  PERIPHERAL_TYPE_NONE
}PER_INFO_TYPE_e;

/**
  @brief  Instance of peripheral info
**/
typedef struct {
  PER_INFO_TYPE_e  type;  ///< PER_INFO_TYPE
  uint32_t         bdf;   ///< Bus Device Function
  uint64_t         base0; ///< Base Address of the controller
  uint64_t         base1; ///< Base Address of the controller
  uint32_t         width; ///< Access width
  uint32_t         irq;   ///< IRQ to install an ISR
  uint32_t         flags;
  uint32_t         msi;   ///< MSI Enabled
  uint32_t         msix;  ///< MSIX Enabled
  uint32_t         max_pasids;
  uint32_t         baud_rate;
  uint32_t         interface_type;
  uint32_t         platform_type;
}PERIPHERAL_INFO_BLOCK;

/**
  @brief Peripheral Info Structure
**/
typedef struct {
  PERIPHERAL_INFO_HDR     header;
  PERIPHERAL_INFO_BLOCK   info[]; ///< Array of Information blocks - instantiated for each peripheral
}PERIPHERAL_INFO_TABLE;

typedef struct {
  uint64_t  Address;
  uint8_t   AddressSpaceId;
  uint8_t   RegisterBitWidth;
  uint8_t   RegisterBitOffset;
  uint8_t   AccessSize;
} PLATFORM_OVERRIDE_GENERIC_ADDRESS_STRUCTURE;

typedef struct {
  uint64_t                                     Address;
  PLATFORM_OVERRIDE_GENERIC_ADDRESS_STRUCTURE  BaseAddress;
  uint8_t                                      InterfaceType;
  uint32_t                                     GlobalSystemInterrupt;
  uint8_t                                      BaudRate;
  uint32_t                                     PciFlags;
  uint16_t                                     PciDeviceId;
  uint16_t                                     PciVendorId;
  uint8_t                                      PciBusNumber;
  uint8_t                                      PciDeviceNumber;
  uint8_t                                      PciFunctionNumber;
  uint8_t                                      PciSegment;
} PLATFORM_OVERRIDE_UART_INFO_TABLE;

/**
  @brief MSI(X) controllers info structure
**/

typedef struct {
  uint32_t  vector_upper_addr; ///< Bus Device Function
  uint32_t  vector_lower_addr; ///< Base Address of the controller
  uint32_t  vector_data;       ///< Base Address of the controller
  uint32_t  vector_control;    ///< IRQ to install an ISR
  uint64_t  vector_irq_base;   ///< Base IRQ for the vectors in the block
  uint32_t  vector_n_irqs;     ///< Number of irq vectors in the block
  uint32_t  vector_mapped_irq_base; ///< Mapped IRQ number base for this MSI
}PERIPHERAL_VECTOR_BLOCK;

typedef struct PERIPHERAL_VECTOR_LIST_STRUCT
{
  PERIPHERAL_VECTOR_BLOCK vector;
  struct PERIPHERAL_VECTOR_LIST_STRUCT *next;
}PERIPHERAL_VECTOR_LIST;

uint32_t pal_get_msi_vectors (uint32_t seg, uint32_t bus, uint32_t dev, uint32_t fn, PERIPHERAL_VECTOR_LIST **mvector);

/**
  @brief  Instance of SMMU INFO block
**/
typedef struct {
  uint32_t arch_major_rev;  ///< Version 1 or 2 or 3
  uint64_t base;              ///< SMMU Controller base address
}SMMU_INFO_BLOCK;

typedef struct {
  uint32_t segment;
  uint32_t ats_attr;
  uint32_t cca;             //Cache Coherency Attribute
  uint64_t smmu_base;
}IOVIRT_RC_INFO_BLOCK;

typedef struct {
  uint64_t base;
  uint32_t overflow_gsiv;
  uint32_t node_ref;
  uint64_t smmu_base;
} IOVIRT_PMCG_INFO_BLOCK;

typedef enum {
  IOVIRT_NODE_ITS_GROUP = 0x00,
  IOVIRT_NODE_NAMED_COMPONENT = 0x01,
  IOVIRT_NODE_PCI_ROOT_COMPLEX = 0x02,
  IOVIRT_NODE_SMMU = 0x03,
  IOVIRT_NODE_SMMU_V3 = 0x04,
  IOVIRT_NODE_PMCG = 0x05
}IOVIRT_NODE_TYPE;

typedef enum {
  IOVIRT_FLAG_DEVID_OVERLAP_SHIFT,
  IOVIRT_FLAG_STRID_OVERLAP_SHIFT,
  IOVIRT_FLAG_SMMU_CTX_INT_SHIFT,
}IOVIRT_FLAG_SHIFT;

typedef struct {
  uint32_t input_base;
  uint32_t id_count;
  uint32_t output_base;
  uint32_t output_ref;
}ID_MAP;

typedef union {
  uint32_t id[4];
  ID_MAP map;
}NODE_DATA_MAP;

#define MAX_NAMED_COMP_LENGTH 150

typedef struct {
  uint64_t smmu_base;                  /* SMMU base to which component is attached, else NULL */
  uint32_t cca;                        /* Cache Coherency Attribute */
  char name[MAX_NAMED_COMP_LENGTH];    /* Device object name */
} IOVIRT_NAMED_COMP_INFO_BLOCK;

typedef union {
  IOVIRT_NAMED_COMP_INFO_BLOCK named_comp;
  IOVIRT_RC_INFO_BLOCK rc;
  IOVIRT_PMCG_INFO_BLOCK pmcg;
  uint32_t its_count;
  SMMU_INFO_BLOCK smmu;
}NODE_DATA;

typedef struct {
  uint32_t type;
  uint32_t num_data_map;
  NODE_DATA data;
  uint32_t flags;
  NODE_DATA_MAP data_map[];
}IOVIRT_BLOCK;

typedef struct {
  uint32_t num_blocks;
  uint32_t num_smmus;
  uint32_t num_pci_rcs;
  uint32_t num_named_components;
  uint32_t num_its_groups;
  uint32_t num_pmcgs;
  IOVIRT_BLOCK blocks[];
}IOVIRT_INFO_TABLE;

#define IOVIRT_NEXT_BLOCK(b) (IOVIRT_BLOCK *)((uint8_t*)(&b->data_map[0]) + b->num_data_map * sizeof(NODE_DATA_MAP))
#define IOVIRT_CCA_MASK ~((uint32_t)0)
#ifdef TARGET_BM_BOOT
  // Align memory access to nearest 8 byte boundary
  #define BOUND 0x08
  #define ALIGN_MEMORY_ACCESS(b) \
            (IOVIRT_BLOCK *) (((uint64_t)b + BOUND - 1) & (~((uint64_t)BOUND - 1)))
#else
  #define ALIGN_MEMORY_ACCESS(b) (IOVIRT_BLOCK *) (b)
#endif

/* Memory INFO table */
#define MEM_MAP_SUCCESS  0x0
#define MEM_MAP_NO_MEM   0x10000001
#define MEM_MAP_FAILURE  0x2

typedef enum {
  MEMORY_TYPE_DEVICE = 0x1000,
  MEMORY_TYPE_NORMAL,
  MEMORY_TYPE_RESERVED,
  MEMORY_TYPE_NOT_POPULATED,
  MEMORY_TYPE_PERSISTENT,
  MEMORY_TYPE_LAST_ENTRY
}MEM_INFO_TYPE_e;


typedef struct {
  MEM_INFO_TYPE_e type;
  uint64_t        phy_addr;
  uint64_t        virt_addr;
  uint64_t        size;
  uint64_t        flags;  //To Indicate Cacheablility etc..
}MEM_INFO_BLOCK;


typedef struct {
  uint64_t  dram_base;
  uint64_t  dram_size;
  MEM_INFO_BLOCK  info[];
} MEMORY_INFO_TABLE;

typedef struct {
    uint64_t physical_address;
    uint64_t virtual_address;
    uint64_t length;
    uint64_t attributes;
} memory_region_descriptor_t;

/**
  @brief DMA controllers info structure
**/
typedef enum {
  DMA_TYPE_USB  =  0x2000,
  DMA_TYPE_SATA,
  DMA_TYPE_OTHER,
}DMA_INFO_TYPE_e;

typedef struct {
  DMA_INFO_TYPE_e type;
  void            *target;   ///< The actual info stored in these pointers is implementation specific.
  void            *port;
  void            *host;     // It will be used only by PAL. hence void.
  uint32_t        flags;
}DMA_INFO_BLOCK;

typedef struct {
  uint32_t         num_dma_ctrls;
  DMA_INFO_BLOCK   info[];    ///< Array of information blocks - per DMA controller
}DMA_INFO_TABLE;

typedef enum {
    EDMA_NO_SUPPORT   = 0x0,
    EDMA_COHERENT     = 0x1,
    EDMA_NOT_COHERENT = 0x2,
    EDMA_FROM_DEVICE  = 0x3,
    EDMA_TO_DEVICE    = 0x4
} EXERCISER_DMA_ATTR;

typedef enum {
    SNOOP_ATTRIBUTES = 0x1,
    LEGACY_IRQ       = 0x2,
    MSIX_ATTRIBUTES  = 0x3,
    DMA_ATTRIBUTES   = 0x4,
    P2P_ATTRIBUTES   = 0x5,
    PASID_ATTRIBUTES = 0x6,
    CFG_TXN_ATTRIBUTES = 0x7,
    ATS_RES_ATTRIBUTES = 0x8,
    TRANSACTION_TYPE  = 0x9,
    NUM_TRANSACTIONS  = 0xA,
    ADDRESS_ATTRIBUTES = 0xB,
    DATA_ATTRIBUTES = 0xC,
    ERROR_INJECT_TYPE = 0xD,
    ENABLE_POISON_MODE = 0xE,
    ENABLE_RAS_CTRL = 0xF,
    DISABLE_POISON_MODE = 0x10,
    CLEAR_TXN = 0x11
} EXERCISER_PARAM_TYPE;

typedef enum {
    EXERCISER_RESET = 0x1,
    EXERCISER_ON    = 0x2,
    EXERCISER_OFF   = 0x3,
    EXERCISER_ERROR = 0x4
} EXERCISER_STATE;

typedef enum {
    START_DMA     = 0x1,
    GENERATE_MSI  = 0x2,
    GENERATE_L_INTR = 0x3,  //Legacy interrupt
    MEM_READ      = 0x4,
    MEM_WRITE     = 0x5,
    CLEAR_INTR    = 0x6,
    PASID_TLP_START = 0x7,
    PASID_TLP_STOP  = 0x8,
    TXN_NO_SNOOP_ENABLE = 0x9,
    TXN_NO_SNOOP_DISABLE  = 0xa,
    START_TXN_MONITOR    = 0xb,
    STOP_TXN_MONITOR     = 0xc,
    ATS_TXN_REQ          = 0xd,
    INJECT_ERROR         = 0xe
} EXERCISER_OPS;
/**
  @brief  Instance of system pmu info
**/

#define PCIE_INTERRUPT_LINE  0x3c
#define PCIE_INTERRUPT_PIN   0x3d
#define PCIE_INTERRUPT_PIN_SHIFT 0x8
#define PCIE_INTERRUPT_PIN_MASK  0xFF

/* LibC functions declaration */

int32_t pal_mem_compare(void *Src, void *Dest, uint32_t Len);
void *pal_memcpy(void *DestinationBuffer, const void *SourceBuffer, uint32_t Length);
void *pal_strncpy(void *DestinationStr, const void *SourceStr, uint32_t Length);
uint32_t pal_strncmp(const char8_t *str1, const char8_t *str2, uint32_t len);
void pal_mem_set(void *buf, uint32_t size, uint8_t value);

/**
  @brief  Instance of system pmu info
**/
typedef struct {
    uint8_t  type;                /* The component that this PMU block is associated with*/
    uint64_t primary_instance;    /* Primary node instance, specific to the PMU type*/
    uint32_t secondary_instance;  /* Secondary node instance, specific to the PMU type*/
    uint8_t  dual_page_extension; /* Support of the dual-page mode*/
    uint64_t base0;               /* Base address of Page 0 of the PMU*/
    uint64_t base1;               /* Base address of Page 1 of the PMU,
                                   valid only if dual_page_extension is 1*/
    uint32_t coresight_compliant; /* node coresight compliant or not */
} PMU_INFO_BLOCK;

typedef struct {
    uint32_t  pmu_count;          /* Total number of PMU info blocks*/
    PMU_INFO_BLOCK  info[];     /* PMU info blocks for each PMU nodes*/
} PMU_INFO_TABLE;

/*
 * @brief Mpam Resource Node
 */
typedef struct {
    uint8_t    ris_index;
    uint8_t    locator_type;  /* Identifies location of this resource */
    uint64_t   descriptor1;   /* Primary acpi description of location */
    uint32_t   descriptor2;   /* Secondary acpi description of location */
} MPAM_RESOURCE_NODE;

/*
 * @brief Mpam MSC Node
 */

typedef struct {
    uint8_t     intrf_type;     /* type of interface to this MPAM MSC */
    uint32_t    identifier;    /* unique id to reference the node */
    uint64_t    msc_base_addr; /* base addr of mem-mapped reg space or PCC
                                  subspace ID based on interface type. */
    uint32_t    msc_addr_len;  /* MSC mem map size */
    uint32_t    of_intr;       /* Overflow interrupt GSIV in case of wired interrupts. */
    uint32_t    of_intr_flags; /* Overflow interrupt flags */
    uint32_t    err_intr;      /* Error interrupt GSIV in case of wired interrupts. */
    uint32_t    err_intr_flags;/* Error interrupt flags */
    uint32_t    max_nrdy;      /* max time in microseconds that MSC not ready
                                  after config change */
    uint32_t    rsrc_count;    /* number of resource nodes */
    MPAM_RESOURCE_NODE rsrc_node[];   /* Details of resource node */
} MPAM_MSC_NODE;

/*
 * @brief Mpam info table
 */

#define MPAM_NEXT_MSC(msc_entry) \
        (MPAM_MSC_NODE *)((uint8_t *)(&msc_entry->rsrc_node[0]) \
        + msc_entry->rsrc_count * sizeof(MPAM_RESOURCE_NODE))

typedef struct {
    uint32_t          msc_count;  /* Number of MSC node */
    MPAM_MSC_NODE   msc_node[]; /* Details of MSC node */
} MPAM_INFO_TABLE;

/**
  @brief  SRAT node type
**/

typedef enum {
  SRAT_NODE_MEM_AFF  = 0x01,
  SRAT_NODE_GICC_AFF = 0x03
} SRAT_NODE_TYPE_e;

/**
  @brief  SRAT GICC Affinity Structure
**/

typedef struct {
  uint32_t   prox_domain;      /* Proximity domain*/
  uint32_t   proc_uid;         /* ACPI Processor UID */
  uint32_t   flags;            /* Flags*/
  uint32_t   clk_domain;       /* Clock Domain*/
} SRAT_GICC_AFF_ENTRY;

/**
  @brief  SRAT Memory Affinity Structure
**/

typedef struct {
  uint32_t   prox_domain;     /* Proximity domain */
  uint32_t   flags;           /* flags */
  uint64_t   addr_base;       /* mem range address base */
  uint64_t   addr_len;        /* mem range address len */
} SRAT_MEM_AFF_ENTRY;

typedef union {
  SRAT_MEM_AFF_ENTRY mem_aff;
  SRAT_GICC_AFF_ENTRY gicc_aff;
} SRAT_NODE_INFO;

typedef struct {
  uint32_t node_type;         /* Node type*/
  SRAT_NODE_INFO node_data;
} SRAT_INFO_ENTRY;

/* SRAT info table to store memory ranges information */

typedef struct {
  uint32_t num_of_srat_entries;
  uint32_t num_of_mem_ranges;
  SRAT_INFO_ENTRY  srat_info[];
} SRAT_INFO_TABLE;

/* Cache info table structures and APIs */

#define CACHE_TYPE_SHARED  0x0
#define CACHE_TYPE_PRIVATE 0x1

/*only the fields and flags required by ACS are parsed from ACPI PPTT table*/
/*Cache flags indicate validity of cache info provided by PPTT Table*/
typedef struct {
  uint32_t size_property_valid;
  uint32_t cache_type_valid;
  uint32_t cache_id_valid;
} CACHE_FLAGS;

/* Since most of platform doesn't support cache id field (ACPI 6.4+), ACS uses PPTT offset as key
   to uniquely identify a cache, In future once platforms align with ACPI 6.4+ my_offset member
   might be removed from cache entry*/
typedef struct {
  CACHE_FLAGS flags;        /* Cache flags */
  uint32_t my_offset;         /* Cache PPTT structure offset */
  uint32_t next_level_index;  /* Index of next level cache entry in CACHE_INFO_TABLE */
  uint32_t size;              /* Size of the cache in bytes */
  uint32_t cache_id;          /* Unique, non-zero identifier for this cache */
  uint32_t is_private;        /* Field indicate whether cache is private */
  uint8_t  cache_type;        /* Cache type */
} CACHE_INFO_ENTRY;

typedef struct {
  uint32_t num_of_cache;  /* Total of number of cache info entries */
  CACHE_INFO_ENTRY cache_info[];  /* Array of cache info entries */
} CACHE_INFO_TABLE;

/* RAS Information */

typedef enum {
  NODE_TYPE_PE = 0x0,
  NODE_TYPE_MC = 0x1,
  NODE_TYPE_SMMU = 0x2,
  NODE_TYPE_VDR = 0x3,
  NODE_TYPE_GIC = 0x4,
  NODE_TYPE_LAST_ENTRY
} RAS_NODE_TYPE_e;

typedef struct {
  uint32_t  processor_id;
  uint32_t  resource_type;
  uint32_t  flags;
  uint64_t  affinity;
  uint64_t  res_specific_data;  /* Resource Specific Data */
} RAS_NODE_PE_DATA;

typedef struct {
  uint32_t  proximity_domain;
} RAS_NODE_MC_DATA;

typedef struct {
  uint32_t  intf_type;           /* Interface Type */
  uint32_t  flags;
  uint64_t  base_addr;
  uint32_t  start_rec_index;     /* Start Record Index */
  uint32_t  num_err_rec;
  uint64_t  err_rec_implement;
  uint64_t  err_status_reporting;
  uint64_t  addressing_mode;
} RAS_INTERFACE_INFO;

typedef struct {
  uint32_t  type;
  uint32_t  flag;
  uint32_t  gsiv;
  uint32_t  its_grp_id;
} RAS_INTERRUPT_INFO;

typedef union {
  RAS_NODE_PE_DATA    pe;
  RAS_NODE_MC_DATA    mc;
} RAS_NODE_DATA;

typedef struct {
  RAS_NODE_TYPE_e     type;             /* Node Type PE/GIC/SMMU */
  uint16_t            length;           /* Length of the Node */
  uint64_t            num_intr_entries; /* Number of Interrupt Entry */
  RAS_NODE_DATA       node_data;        /* Node Specific Data */
  RAS_INTERFACE_INFO  intf_info;        /* Node Interface Info */
  RAS_INTERRUPT_INFO  intr_info[2];     /* Node Interrupt Info */
} RAS_NODE_INFO;

typedef struct {
  uint32_t  num_nodes;      /* Number of total RAS Nodes */
  uint32_t  num_pe_node;    /* Number of PE RAS Nodes */
  uint32_t  num_mc_node;    /* Number of Memory Controller Nodes */
  RAS_NODE_INFO  node[];  /* Array of RAS nodes */
} RAS_INFO_TABLE;

typedef enum {
    ERR_UC = 0x1,         /* Uncorrectable Error */
    ERR_DE,               /* Deferred Error */
    ERR_CE,               /* Correctable Error */
    ERR_CRITICAL          /* Critical Error */
} RAS_ERROR_TYPE;

typedef struct {
   RAS_ERROR_TYPE ras_error_type;   /* Error Type */
   uint64_t error_pa;                 /* Error Phy Address */
   uint32_t rec_index;                /* Error Record Index */
   uint32_t node_index;               /* Error Node Index in Info table */
   uint8_t is_pfg_check;              /* Pseudo Fault Check or not */
} RAS_ERR_IN_t;

typedef struct {
   uint32_t intr_id;        /* Interrupt ID */
   uint32_t error_record;   /* Error Record Number */
} RAS_ERR_OUT_t;

void pal_ras_create_info_table(RAS_INFO_TABLE *ras_info_table);
uint32_t pal_ras_setup_error(RAS_ERR_IN_t in_param, RAS_ERR_OUT_t *out_param);
uint32_t pal_ras_inject_error(RAS_ERR_IN_t in_param, RAS_ERR_OUT_t *out_param);
uint32_t pal_ras_check_plat_poison_support(void);

typedef enum {
  RAS2_TYPE_MEMORY = 0   /* RAS2 memory feature type*/
} RAS2_FEAT_TYPE;

typedef struct {
  uint32_t  proximity_domain;      /* Proximity domain of the memory */
  uint32_t  patrol_scrub_support;  /* Patrol srub support flag */
} RAS2_MEM_INFO;

typedef union {
  RAS2_MEM_INFO mem_feat_info;   /* Memory feature specific info */
} RAS2_BLOCK_INFO;

typedef struct {
  RAS2_FEAT_TYPE type;                     /* RAS2 feature type*/
  RAS2_BLOCK_INFO block_info;     /* RAS2 block info */
} RAS2_BLOCK;

typedef struct {
  uint32_t num_all_block;        /* Number of RAS2 feature blocks */
  uint32_t num_of_mem_block;     /* Number of memory feature blocks */
  RAS2_BLOCK blocks[];
} RAS2_INFO_TABLE;

void pal_ras2_create_info_table(RAS2_INFO_TABLE *ras2_info_table);

/* HMAT info table structures and APIs*/

#define HMAT_MEM_HIERARCHY_MEMORY   0x00
#define HMAT_DATA_TYPE_ACCESS_BW    0x03
#define HMAT_DATA_TYPE_READ_BW      0x04
#define HMAT_DATA_TYPE_WRITE_BW     0x05
#define HMAT_BW_ENTRY_UNREACHABLE   0xFFFF
#define HMAT_BASE_UNIT_48BIT        0xFFFFFFFFFFFFULL
typedef struct {
  uint32_t mem_prox_domain;             /* Proximity domain of the memory region*/
  uint64_t write_bw;                    /* Maximum write bandwidth */
  uint64_t read_bw;                     /* Maximum read bandwidth */
} HMAT_BW_ENTRY;

typedef struct {
  uint32_t num_of_mem_prox_domain;      /* Number of Memory Proximity Domains */
  HMAT_BW_ENTRY bw_info[];            /* Array of bandwidth info based on proximity domain */
} HMAT_INFO_TABLE;

void pal_hmat_create_info_table(HMAT_INFO_TABLE *HmatTable);

/* Platform Communication Channel (PCC) info table */
#ifndef GAS_STRUCT
#define GAS_STRUCT
typedef struct {
  uint8_t   addr_space_id;
  uint8_t   reg_bit_width;
  uint8_t   reg_bit_offset;
  uint8_t   access_size;
  uint64_t  addr;
} GENERIC_ADDRESS_STRUCTURE;
#endif

typedef struct {
  uint64_t                         base_addr;               /* base addr of shared mem-region */
  GENERIC_ADDRESS_STRUCTURE        doorbell_reg;            /* doorbell register */
  uint64_t                         doorbell_preserve;       /* doorbell register preserve mask */
  uint64_t                         doorbell_write;          /* doorbell register set mask */
  uint32_t                         min_req_turnaround_usec; /* minimum request turnaround time */
  GENERIC_ADDRESS_STRUCTURE        cmd_complete_chk_reg;    /* command complete check register */
  uint64_t                         cmd_complete_chk_mask;   /* command complete check mask */
  GENERIC_ADDRESS_STRUCTURE        cmd_complete_update_reg; /* command complete update register */
  uint64_t                         cmd_complete_update_preserve;
                                                            /* command complete update preserve */
  uint64_t                         cmd_complete_update_set; /* command complete update set mask */
} PCC_SUBSPACE_TYPE_3;

typedef union {
  PCC_SUBSPACE_TYPE_3 pcc_ss_type_3;
} PCC_TYPE_SPECIFIC_INFO;

typedef struct {
  uint32_t                 subspace_idx;    /* PCC subspace index in PCCT ACPI table */
  uint32_t                 subspace_type;   /* type of PCC subspace */
  PCC_TYPE_SPECIFIC_INFO   type_spec_info;  /* PCC subspace type specific info */
} PCC_INFO;

typedef struct {
  uint32_t  subspace_cnt; /* number of PCC subspace info stored */
  PCC_INFO  pcc_info[];   /* array of PCC info blocks */
} PCC_INFO_TABLE;


typedef struct {
  uint32_t reserved : 4;        /* Bits [31:28] Reserved must be zero */
  uint32_t token : 10;          /* Bits [27:18] Token Caller-defined value */
  uint32_t protocol_id : 8;     /* Bits [17:10] Protocol ID */
  uint32_t message_type : 2;    /* Bits [09:08] Message Type */
  uint32_t message_id : 8;      /* Bits [07:00] Message ID */
} SCMI_PROTOCOL_MESSAGE_HEADER;

typedef struct {
  uint32_t msc_id;            /* Identifier of the MSC */
  uint32_t flags;             /* Reserved, must be zero */
  uint32_t offset;            /* MPAM register offset to read from */
} PCC_MPAM_MSC_READ_CMD_PARA;

typedef struct {
  int32_t  status;             /* command response status code */
  uint32_t val;                /* value read from the register */
} PCC_MPAM_MSC_READ_RESP_PARA;

typedef struct {
  uint32_t msc_id;            /* Identifier of the MSC */
  uint32_t flags;             /* Reserved, must be zero */
  uint32_t val;               /* value to be written to the register */
  uint32_t offset;            /* MPAM register offset to write */
} PCC_MPAM_MSC_WRITE_CMD_PARA;

typedef struct {
  int32_t  status;             /* command response status code */
} PCC_MPAM_MSC_WRITE_RESP_PARA;

#define MPAM_FB_PROTOCOL_ID    0x1A
#define MPAM_MSG_TYPE_CMD      0x0
#define MPAM_MSC_READ_CMD_ID   0x4
#define MPAM_MSC_WRITE_CMD_ID  0x5
#define MPAM_PCC_CMD_SUCCESS   0x0
#define MPAM_PCC_SAFE_RETURN   0x0
#define RETURN_FAILURE         0xFFFFFFFF
#define PCC_TY3_CMD_OFFSET     12
#define PCC_TY3_COMM_SPACE     16
#define PCCT_SUBSPACE_TYPE_3_EXTENDED_PCC 0x03

void pal_pcc_create_info_table(PCC_INFO_TABLE *PccInfoTable);

#endif
