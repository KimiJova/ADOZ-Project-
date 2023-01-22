/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/* 	 IIR_high_pass_filters.h                                                 */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Header file for IIR low pass filters.                                   */
/*   The order of the coefficients is B0, B1/2, B2, A0, A1/2, A2, where      */
/*   B0, B1/2 and B2 are the numerator coefficients, A0, A1/2 and A2 are     */
/*   the denominator coefficients.                                           */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00	                                                         */
/*   Author  : Dejan Bokan													 */
/*****************************************************************************/

#ifndef IIR_HIGH_PASS_FILTERS_H
#define IIR_HIGH_PASS_FILTERS_H

Int16 IIR_zad2[6] = {32767,  -31650,  32767,
		32767, -30068, 29572
};

Int16 IIR_zad4_4th_order[2][6] = { {32767,  -31650,  32767,
		32767, -30068, 29572
},
		{32767,  -31650,  32767,
				32767, -30068, 29572
		}
};

Int16 IIR_zad4_6th_order[3][6] = { {32767,  -31650,  32767,
		32767, -30068, 29572
},
		{32767,  -31650,  32767,
				32767, -30068, 29572
		},
		{32767,  -31650,  32767,
				32767, -30068, 29572
		}
};
#endif

/*****************************************************************************/
/* End of IIR_high_pass_filters.h                                            */
/*****************************************************************************/
