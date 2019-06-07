#ifndef __IDIOMAS_H
#define __IDIOMAS_H
#endif

#include<string.h>

/* En estas líneas se selecciona el idioma:
 sólo debe quedar habilitada una linea*/

#define __IDIOMA_ESPANOL
//#define __IDIOMA_INGLES
//#define __IDIOMA_ITALIANO
//#define __IDIOMA_CHECO
//#define __IDIOMA_RUSO

/* Ahora se llama el archivo con las cadenas de caracteres adecuadas*/

#ifdef __IDIOMA_ESPANOL
	#ifndef __ESPANOL_H
	#include "Espanol.h"
	#endif
#endif
/*
#ifdef __IDIOMA_INGLES
	#ifndef __INGLES_H
	#include "ingles.h"
	#endif
#endif

#ifdef __IDIOMA_ITALIANO
	#ifndef __ITALIANO_H
	#include "italiano.h"
	#endif
#endif

#ifdef __IDIOMA_CHECO
	#ifndef __CHECO_H
	#include "checo.h"
	#endif
#endif

#ifdef __IDIOMA_RUSO
	#ifndef __RUSO_H
	#include "ruso.h"
	#endif
#endif
*/
