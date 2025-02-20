all: ml_dsa_44_riscv.ec ml_dsa_44_arm-m4.ec


ml_dsa_44_riscv.ec:
	jasmin2ec --arch riscv ../library_export_risc-v.jazz -o ml_dsa_44-riscv.ec


ml_dsa_44_arm-m4.ec:
	jasmin2ec --arch arm-m4 ../library_export_arm-m4.jazz -o ml_dsa_44-arm-m4.ec
