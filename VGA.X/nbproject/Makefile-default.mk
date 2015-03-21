#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/VGA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/VGA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c gpu.c charset2.c charset3.c charset5.c coreFont.c sinclair.c topaz.c gpu_rcc.c gpu_chr.c spi.c events.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/gpu.o ${OBJECTDIR}/charset2.o ${OBJECTDIR}/charset3.o ${OBJECTDIR}/charset5.o ${OBJECTDIR}/coreFont.o ${OBJECTDIR}/sinclair.o ${OBJECTDIR}/topaz.o ${OBJECTDIR}/gpu_rcc.o ${OBJECTDIR}/gpu_chr.o ${OBJECTDIR}/spi.o ${OBJECTDIR}/events.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/gpu.o.d ${OBJECTDIR}/charset2.o.d ${OBJECTDIR}/charset3.o.d ${OBJECTDIR}/charset5.o.d ${OBJECTDIR}/coreFont.o.d ${OBJECTDIR}/sinclair.o.d ${OBJECTDIR}/topaz.o.d ${OBJECTDIR}/gpu_rcc.o.d ${OBJECTDIR}/gpu_chr.o.d ${OBJECTDIR}/spi.o.d ${OBJECTDIR}/events.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/gpu.o ${OBJECTDIR}/charset2.o ${OBJECTDIR}/charset3.o ${OBJECTDIR}/charset5.o ${OBJECTDIR}/coreFont.o ${OBJECTDIR}/sinclair.o ${OBJECTDIR}/topaz.o ${OBJECTDIR}/gpu_rcc.o ${OBJECTDIR}/gpu_chr.o ${OBJECTDIR}/spi.o ${OBJECTDIR}/events.o

# Source Files
SOURCEFILES=main.c gpu.c charset2.c charset3.c charset5.c coreFont.c sinclair.c topaz.c gpu_rcc.c gpu_chr.c spi.c events.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/VGA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256DA210
MP_LINKER_FILE_OPTION=,--script=p24FJ256DA210.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/gpu.o: gpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/gpu.o.d 
	@${RM} ${OBJECTDIR}/gpu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gpu.c  -o ${OBJECTDIR}/gpu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/gpu.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/gpu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/charset2.o: charset2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/charset2.o.d 
	@${RM} ${OBJECTDIR}/charset2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  charset2.c  -o ${OBJECTDIR}/charset2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/charset2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/charset2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/charset3.o: charset3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/charset3.o.d 
	@${RM} ${OBJECTDIR}/charset3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  charset3.c  -o ${OBJECTDIR}/charset3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/charset3.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/charset3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/charset5.o: charset5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/charset5.o.d 
	@${RM} ${OBJECTDIR}/charset5.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  charset5.c  -o ${OBJECTDIR}/charset5.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/charset5.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/charset5.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/coreFont.o: coreFont.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/coreFont.o.d 
	@${RM} ${OBJECTDIR}/coreFont.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  coreFont.c  -o ${OBJECTDIR}/coreFont.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/coreFont.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/coreFont.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sinclair.o: sinclair.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sinclair.o.d 
	@${RM} ${OBJECTDIR}/sinclair.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sinclair.c  -o ${OBJECTDIR}/sinclair.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sinclair.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sinclair.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/topaz.o: topaz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/topaz.o.d 
	@${RM} ${OBJECTDIR}/topaz.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  topaz.c  -o ${OBJECTDIR}/topaz.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/topaz.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/topaz.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/gpu_rcc.o: gpu_rcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/gpu_rcc.o.d 
	@${RM} ${OBJECTDIR}/gpu_rcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gpu_rcc.c  -o ${OBJECTDIR}/gpu_rcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/gpu_rcc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/gpu_rcc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/gpu_chr.o: gpu_chr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/gpu_chr.o.d 
	@${RM} ${OBJECTDIR}/gpu_chr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gpu_chr.c  -o ${OBJECTDIR}/gpu_chr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/gpu_chr.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/gpu_chr.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/spi.o: spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/spi.o.d 
	@${RM} ${OBJECTDIR}/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  spi.c  -o ${OBJECTDIR}/spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/spi.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/events.o: events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/events.o.d 
	@${RM} ${OBJECTDIR}/events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  events.c  -o ${OBJECTDIR}/events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/events.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/events.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/gpu.o: gpu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/gpu.o.d 
	@${RM} ${OBJECTDIR}/gpu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gpu.c  -o ${OBJECTDIR}/gpu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/gpu.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/gpu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/charset2.o: charset2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/charset2.o.d 
	@${RM} ${OBJECTDIR}/charset2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  charset2.c  -o ${OBJECTDIR}/charset2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/charset2.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/charset2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/charset3.o: charset3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/charset3.o.d 
	@${RM} ${OBJECTDIR}/charset3.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  charset3.c  -o ${OBJECTDIR}/charset3.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/charset3.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/charset3.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/charset5.o: charset5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/charset5.o.d 
	@${RM} ${OBJECTDIR}/charset5.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  charset5.c  -o ${OBJECTDIR}/charset5.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/charset5.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/charset5.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/coreFont.o: coreFont.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/coreFont.o.d 
	@${RM} ${OBJECTDIR}/coreFont.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  coreFont.c  -o ${OBJECTDIR}/coreFont.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/coreFont.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/coreFont.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/sinclair.o: sinclair.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sinclair.o.d 
	@${RM} ${OBJECTDIR}/sinclair.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  sinclair.c  -o ${OBJECTDIR}/sinclair.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sinclair.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/sinclair.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/topaz.o: topaz.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/topaz.o.d 
	@${RM} ${OBJECTDIR}/topaz.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  topaz.c  -o ${OBJECTDIR}/topaz.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/topaz.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/topaz.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/gpu_rcc.o: gpu_rcc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/gpu_rcc.o.d 
	@${RM} ${OBJECTDIR}/gpu_rcc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gpu_rcc.c  -o ${OBJECTDIR}/gpu_rcc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/gpu_rcc.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/gpu_rcc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/gpu_chr.o: gpu_chr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/gpu_chr.o.d 
	@${RM} ${OBJECTDIR}/gpu_chr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  gpu_chr.c  -o ${OBJECTDIR}/gpu_chr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/gpu_chr.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/gpu_chr.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/spi.o: spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/spi.o.d 
	@${RM} ${OBJECTDIR}/spi.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  spi.c  -o ${OBJECTDIR}/spi.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/spi.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/spi.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/events.o: events.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/events.o.d 
	@${RM} ${OBJECTDIR}/events.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  events.c  -o ${OBJECTDIR}/events.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/events.o.d"      -mno-eds-warn  -g -omf=elf -mlarge-data -menable-large-arrays -O3 -funroll-loops -fomit-frame-pointer -msmart-io=1 -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/events.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/VGA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/VGA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -mreserve=data@0x800:0x81B -mreserve=data@0x81C:0x81D -mreserve=data@0x81E:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x827 -mreserve=data@0x82A:0x84F   -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/VGA.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/VGA.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--local-stack,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/VGA.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
