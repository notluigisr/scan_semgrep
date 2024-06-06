static void DumpBIH(unsigned char *BIH)
{				
	printf("STR",
	       (int)(BIH[3] << 24) + (BIH[2] << 16) + (BIH[1] << 8) + (BIH[0]));
	printf("STR",
	       (int)(BIH[7] << 24) + (BIH[6] << 16) + (BIH[5] << 8) + (BIH[4]));
	printf("STR",
	       (int)(BIH[11] << 24) + (BIH[10] << 16) + (BIH[9] << 8) +
	       (BIH[8]));
	printf("STR", (int)(BIH[13] << 8) + (BIH[12]));
	printf("STR", (int)(BIH[15] << 8) + (BIH[14]));
	printf("STR",
	       (int)(BIH[19] << 24) + (BIH[18] << 16) + (BIH[17] << 8) +
	       (BIH[16]));
	printf("STR",
	       (int)(BIH[23] << 24) + (BIH[22] << 16) + (BIH[21] << 8) +
	       (BIH[20]));
	printf("STR",
	       (int)(BIH[27] << 24) + (BIH[26] << 16) + (BIH[25] << 8) +
	       (BIH[24]));
	printf("STR",
	       (int)(BIH[31] << 24) + (BIH[30] << 16) + (BIH[29] << 8) +
	       (BIH[28]));
	printf("STR",
	       (int)(BIH[35] << 24) + (BIH[34] << 16) + (BIH[33] << 8) +
	       (BIH[32]));
	printf("STR",
	       (int)(BIH[39] << 24) + (BIH[38] << 16) + (BIH[37] << 8) +
	       (BIH[36]));
}