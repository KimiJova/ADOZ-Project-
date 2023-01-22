/*
 * Discrete-Time FIR Filter (real)
 * -------------------------------
 * Filter Structure  : Direct-Form FIR
 * Filter Length     : 35
 * Stable            : Yes
 * Linear Phase      : Yes (Type 1)
 * Arithmetic        : fixed
 * Numerator         : s16,15 -> [-1 1)
 * Input             : s16,15 -> [-1 1)
 * Type				 : HIGH PASS
 * Fs				 : 48 kHz
 * Fc				 : 12 kHz
 */

#include "tistdtypes.h"

#define HP_LENGTH 35
Int16 highpass_35[35] = {
				  454,
		          366,
		          245,
		           92,
		          -89,
		         -296,
		         -524,
		         -765,
		        -1015,
		        -1265,
		        -1508,
		        -1737,
		        -1945,
		        -2125,
		        -2271,
		        -2379,
		        -2446,
		        30789,
		        -2446,
		        -2379,
		        -2271,
		        -2125,
		        -1945,
		        -1737,
		        -1508,
		        -1265,
		        -1015,
		         -765,
		         -524,
		         -296,
		          -89,
		           92,
		          245,
		          366,
		          454
};

Int16 highpass_77[77] = {
				 -144,
		         -198,
		         -245,
		         -280,
		         -302,
		         -308,
		         -298,
		         -270,
		         -225,
		         -164,
		          -89,
		           -4,
		           87,
		          182,
		          274,
		          359,
		          432,
		          487,
		          520,
		          526,
		          503,
		          449,
		          362,
		          242,
		           91,
		          -88,
		         -293,
		         -518,
		         -757,
		        -1003,
		        -1251,
		        -1491,
		        -1718,
		        -1923,
		        -2101,
		        -2246,
		        -2352,
		        -2418,
		        30443,
		        -2418,
		        -2352,
		        -2246,
		        -2101,
		        -1923,
		        -1718,
		        -1491,
		        -1251,
		        -1003,
		         -757,
		         -518,
		         -293,
		          -88,
		           91,
		          242,
		          362,
		          449,
		          503,
		          526,
		          520,
		          487,
		          432,
		          359,
		          274,
		          182,
		           87,
		           -4,
		          -89,
		         -164,
		         -225,
		         -270,
		         -298,
		         -308,
		         -302,
		         -280,
		         -245,
		         -198,
		         -144
};

Int16 highpass_129[129] = {
        -109,
        -134,
        -152,
        -162,
        -164,
        -157,
        -141,
        -116,
         -84,
         -46,
          -4,
          39,
          83,
         123,
         159,
         188,
         207,
         216,
         213,
         198,
         171,
         134,
          87,
          33,
         -25,
         -85,
        -144,
        -198,
        -245,
        -280,
        -302,
        -308,
        -298,
        -270,
        -225,
        -164,
         -89,
          -4,
          87,
         182,
         274,
         359,
         432,
         487,
         519,
         526,
         503,
         449,
         362,
         242,
          91,
         -88,
        -293,
        -517,
        -756,
       -1003,
       -1250,
       -1490,
       -1717,
       -1922,
       -2100,
       -2244,
       -2351,
       -2417,
       30424,
       -2417,
       -2351,
       -2244,
       -2100,
       -1922,
       -1717,
       -1490,
       -1250,
       -1003,
        -756,
        -517,
        -293,
         -88,
          91,
         242,
         362,
         449,
         503,
         526,
         519,
         487,
         432,
         359,
         274,
         182,
          87,
          -4,
         -89,
        -164,
        -225,
        -270,
        -298,
        -308,
        -302,
        -280,
        -245,
        -198,
        -144,
         -85,
         -25,
          33,
          87,
         134,
         171,
         198,
         213,
         216,
         207,
         188,
         159,
         123,
          83,
          39,
          -4,
         -46,
         -84,
        -116,
        -141,
        -157,
        -164,
        -162,
        -152,
        -134,
        -109
};
