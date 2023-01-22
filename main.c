//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// * Description:  Main function.
// *
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *
// *
// *
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "ezdsp5535_i2s.h"
#include "WAVheader.h"
#include "fir.h"
#include "iir.h"
#include "high_pass_32th_order.h"
#include "IIR_high_pass_filters.h"

static WAV_HEADER outputWAVhdr;
static WAV_HEADER inputWAVhdr;

#define SAMPLE_RATE 48000L
#define GAIN 0

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

/* TO DO: Define history buffers and Rd/Wr pointers*/
/* Your code here */
	//ZADATAK 2
	Int16 historyL[35] = {0};
	Int16 historyR[35] = {0};
	Int16 historyD[35] = {0};
	Uint16 l=0;
	Uint16 r=0;
	Uint16 d=0;

	//ZADATAK 3
	Int16 historyLX[2]={0};
	Int16 historyRX[2]={0};
	Int16 historyDX[2]={0};
	Int16 historyLY[2]={0};
	Int16 historyRY[2]={0};
	Int16 historyDY[2]={0};

	//ZADATAK 4
	//Cetvri red
	Int16 historyLX2[2][2]={0};
	Int16 historyRX2[2][2]={0};
	Int16 historyDX2[2][2]={0};
	Int16 historyLY2[2][2]={0};
	Int16 historyRY2[2][2]={0};
	Int16 historyDY2[2][2]={0};

	//Sesti red
	Int16 historyLX3[3][2]={0};
	Int16 historyRX3[3][2]={0};
	Int16 historyDX3[3][2]={0};
	Int16 historyLY3[3][2]={0};
	Int16 historyRY3[3][2]={0};
	Int16 historyDY3[3][2]={0};

	//FIR 77
	Int16 historyD77[77]={0};
	Int16 historyR77[77]={0};
	Int16 historyL77[77]={0};
	Uint16 d77=0;
	Uint16 l77=0;
	Uint16 r77=0;

	//FIR 129
	Int16 historyD129[129]={0};
	Int16 historyR129[129]={0};
	Int16 historyL129[129]={0};
	Uint16 d129=0;
	Uint16 l129=0;
	Uint16 r129=0;

	//DIRAK IO
	Int16 dirakov_input[AUDIO_IO_SIZE];
	Int16 dirakov_output[AUDIO_IO_SIZE];

/*
 *
 *  main( )
 *
 */
void main( void )
{
	int i, j;
	Int32 number_of_blocks;
	/* Initialize BSL */
	EZDSP5535_init( );


	/* Initialise hardware interface and I2C for code */
	aic3204_hardware_init();

	aic3204_set_input_filename("../Output1.wav");
	aic3204_set_output_filename("../test.wav");

	/* Initialise the AIC3204 codec */
	aic3204_init();

	aic3204_dma_init();

	aic3204_read_wav_header(&inputWAVhdr);

	// Set up output WAV header
	outputWAVhdr = inputWAVhdr;

	number_of_blocks = inputWAVhdr.data.SubChunk2Size/
				(inputWAVhdr.fmt.NumChannels*inputWAVhdr.fmt.BitsPerSample*AUDIO_IO_SIZE/8);

	aic3204_write_wav_header(&outputWAVhdr);

    /* TO DO: Initialize history buffers to 0 */
    /* Your code here */

	//ZADATAK2
	for(i=0; i<35; i++){
		historyL[i] = 0;
		historyR[i] = 0;
		historyD[i] = 0;
	}

	//ZADATAK 3
	for(i=0; i<AUDIO_IO_SIZE; i++){
		historyLX[i] = 0;
		historyRX[i] = 0;
		historyDX[i] = 0;
		historyLY[i] = 0;
		historyRY[i] = 0;
		historyDY[i] = 0;
	}

	//ZADATAK 4
	//FIR 77 baferi na 0
	for(i=0; i<77; i++){
		historyD77[i] = 0;
		historyR77[i] = 0;
		historyL77[i] = 0;
	}

	//FIR 129 baferi na 0
	for(i=0; i<129; i++){
			historyD129[i] = 0;
			historyR129[i] = 0;
			historyL129[i] = 0;
		}

	//IIR 4. REDA i 6. REDA baferi na 0
	for(j=0; j<AUDIO_IO_SIZE; j++){
		for(i=0; i<AUDIO_IO_SIZE; i++){
			historyLX2[j][i] = 0;
			historyRX2[j][i] = 0;
			historyDX2[j][i] = 0;
			historyLY2[j][i] = 0;
			historyRY2[j][i] = 0;
			historyDY2[j][i] = 0;

			historyLX3[j][i] = 0;
			historyRX3[j][i] = 0;
			historyDX3[j][i] = 0;
			historyLY3[j][i] = 0;
			historyRY3[j][i] = 0;
			historyDY3[j][i] = 0;
		}
	}

	//DIRAKOV IMPULS
	dirakov_input[0] = 32767;
	for(i=1; i<AUDIO_IO_SIZE; i++){
		dirakov_input[i] = 0;
	}

	for(i = 0; i < number_of_blocks; ++i)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		/* TO DO: Invoke filtering routine */
		/* Your code here */

		for(j = 0; j < AUDIO_IO_SIZE; j++)
		{
			//ZADATAK 2
				//FIR 35
				//OutputBufferL[j] = fir_circular(InputBufferL[j], highpass_35, historyL, 35, &l);
				//OutputBufferR[j] = fir_circular(InputBufferR[j], highpass_35, historyR, 35, &r);
				//dirakov_output[j] = fir_circular(dirakov_output[j], highpass_35, historyD, 35, &d);

			//ZADATAK 3
				//IIR 2. REDA
				//dirakov_output[j] = second_order_IIR(dirakov_input[j], IIR_zad2, historyDX, historyDY);
				//OutputBufferL[j] = second_order_IIR(InputBufferL[j], IIR_zad2, historyLX, historyLY);
				//OutputBufferR[j] = second_order_IIR(InputBufferR[j], IIR_zad2, historyRX, historyRY);

			//ZADATAK 4
				//FIR 77
				//OutputBufferL[j] = fir_circular(InputBufferL[j], highpass_77, historyL77, 77, &l77);
				//OutputBufferR[j] = fir_circular(InputBufferR[j], highpass_77, historyR77, 77, &r77);
				//dirakov_output[j] = fir_circular(dirakov_input[j], highpass_77, historyD77, 77, &d77);

				//FIR 129
				//OutputBufferL[j] = fir_circular(InputBufferL[j], highpass_129, historyL129, 129, &l129);
				//OutputBufferR[j] = fir_circular(InputBufferR[j], highpass_129, historyR129, 129, &r129);
				//dirakov_output[j] = fir_circular(dirakov_input[j], highpass_129, historyD129, 77, &d129);

				//IIR 4. REDA za FIR 77
				//dirakov_output[j] = fourth_order_IIR(dirakov_input[j], IIR_zad4_4th_order, historyDX2, historyDY2);
				//OutputBufferL[j] = fourth_order_IIR(InputBufferL[j], IIR_zad4_4th_order, historyLX2, historyLY2);
				//OutputBufferR[j] = fourth_order_IIR(InputBufferR[j], IIR_zad4_4th_order, historyRX2, historyRY2);

				//IIR 6. REDA za FIR 129
				//dirakov_output[j] = sixth_order_IIR(dirakov_input[j], IIR_zad4_6th_order, historyDX3, historyDY3);
				//OutputBufferL[j] = sixth_order_IIR(InputBufferL[j], IIR_zad4_6th_order, historyLX3, historyLY3);
				//OutputBufferR[j] = sixth_order_IIR(InputBufferR[j], IIR_zad4_6th_order, historyRX3, historyRY3);

		}
		aic3204_write_block(OutputBufferL, OutputBufferR);
	}

	/* Disable I2S and put codec into reset */
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

