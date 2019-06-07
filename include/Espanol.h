#ifndef __ESPANOL_H
#define __ESPANOL_H
#endif

/* Cadenas en el archivo FUZZYSET HPP  */

#define IDS_CONJUNTOS_TIPO_0			"Tipo L"
#define IDS_CONJUNTOS_TIPO_1        "Triángulo"
#define IDS_CONJUNTOS_TIPO_2        "Tipo Pi"
#define IDS_CONJUNTOS_TIPO_3        "Tipo Gamma"
#define IDS_CONJUNTOS_TIPO_4        "Tipo Z"
#define IDS_CONJUNTOS_TIPO_5        "Campana"
#define IDS_CONJUNTOS_TIPO_6        "Pi-Campana"
#define IDS_CONJUNTOS_TIPO_7        "Tipo S"
#define IDS_CONJUNTOS_TIPO_8        "Singleton"

/* Cadenas en el archivo FUZNORMS HPP  */

#define IDS_T_NORMA_TIPO_0			"Producto"
#define IDS_T_NORMA_TIPO_1			"Mínimo"
#define IDS_T_NORMA_TIPO_2			"Producto Acotado"
#define IDS_T_NORMA_TIPO_3			"Producto Drástico"
#define IDS_T_NORMA_TIPO_4			"Familia Tp"
#define IDS_T_NORMA_TIPO_5			"Familia Hamacher"
#define IDS_T_NORMA_TIPO_6			""
#define IDS_T_NORMA_TIPO_7			"Familia Frank"
#define IDS_T_NORMA_TIPO_8			"Familia Yager"
#define IDS_T_NORMA_TIPO_9			"Familia Dubois-Prade"
#define IDS_S_NORMA_TIPO_10		  "Máximo"
#define IDS_S_NORMA_TIPO_11	  	"Suma Acotada"
#define IDS_S_NORMA_TIPO_12		  "Suma Drástica"
#define IDS_S_NORMA_TIPO_6			"Familia Sugeno"

/* Cadenas en el archivo FUZIMPLI HPP  */

#define IDS_IMPLICA_TIPO				"Implicación"
#define IDS_IMPLICA_TN_TIPO_0			"Producto"
#define IDS_IMPLICA_TN_TIPO_1			"Mínimo"
#define IDS_IMPLICA_IF_TIPO_2			"Kleen-Dienes"
#define IDS_IMPLICA_IF_TIPO_3			"Lukasiewicz"
#define IDS_IMPLICA_IF_TIPO_4			"Zadeh"
#define IDS_IMPLICA_IF_TIPO_5			"Estocástica"
#define IDS_IMPLICA_IF_TIPO_6			"Goguen"
#define IDS_IMPLICA_IF_TIPO_7			"Gödel"
#define IDS_IMPLICA_IF_TIPO_8			"Aguda"


/* Cadenas en el archivo FUZDEFUZ HPP  */

#define IDS_CONCRESOR_TIPO_0				"Primer Máximo"
#define IDS_CONCRESOR_TIPO_1				"Ultimo Máximo"
#define IDS_CONCRESOR_TIPO_2				"Media de Máximos"
#define IDS_CONCRESOR_TIPO_3				"Centro de Gravedad"
#define IDS_CONCRESOR_TIPO_4				"Altura"

/* Cadenas en el archivo FUZZYAPP HPP  */

#define IDS_FUZZYAPP_CAPTION				"Sistema de Lógica Difusa"


/* Cadenas en el archivo FUZZYVAR CPP  */

#define IDS_VARIABLE_ETIQUETA1			"Conjunto 1"  //¿No sería bueno cambiar "Conjunto" por "Etiqueta"?
#define IDS_VARIABLE_ETIQUETA				"Conjunto "

/* Cadenas en el archivo FUZINPUT CPP  */

#define IDS_UNIVERSO_VARIABLE				"Variable"

/* Cadenas en el archivo VENTMDI  CPP  */

#define IDS_VENTANA_CHILD_ENTRADA		"Entrada 1"
#define IDS_VENTANA_CHILD_SALIDA			"Salida 1"
#define IDS_VENTANA_CHILD_ARCHIVO1		"El archivo no es UNFUZZY 1.0"
#define IDS_VENTANA_CHILD_ARCHIVO2     "Lectura Fallida"
#define IDS_VENTANA_CHILD_ARCHIVO3		"Ha ocurrido un error"
#define IDS_VENTANA_CHILD_ARCHIVO4     "Atención"
#define IDS_VENTANA_CHILD_ARCHIVO5     "Archivos UNFUZZY (*.dif)|*.dif|Todos los Archivos (*.*)|*.*"
#define IDS_VENTANA_CHILD_SALIR1			"¿Desea Salir?"
#define IDS_VENTANA_CHILD_SALIR2       "El archivo ha cambiado"
#define IDS_VENTANA_CHILD_NOIMPL1      "Opción No Implementada"
#define IDS_VENTANA_CHILD_NOIMPL2      "Lo Siento..."
#define IDS_VENTANA_CHILD_NUEVASREGLA1 "Debe definir nuevamente las reglas"
#define IDS_VENTANA_CHILD_NUEVASREGLA2 "Atención"
#define IDS_VENTANA_CHILD_DIBUJO1		"ENTRADAS : "
#define IDS_VENTANA_CHILD_DIBUJO2      "ENTRADAS : ?"
#define IDS_VENTANA_CHILD_DIBUJO3      "SALIDAS : "
#define IDS_VENTANA_CHILD_DIBUJO4      "SALIDAS : ?"
#define IDS_VENTANA_CHILD_DIBUJO5      "REGLAS : "
#define IDS_VENTANA_CHILD_DIBUJO6      "REGLAS : ?"
#define IDS_VENTANA_CHILD_DIBUJO7      "entradas"
#define IDS_VENTANA_CHILD_DIBUJO8      "Motor de"     // Estas dos cadenas forman una sóla "Motor de Inferencia"
#define IDS_VENTANA_CHILD_DIBUJO9      "Inferencia"   // Debe tenerse precaución al traducir "Inference Engine", porque puede quedar "Engine Inference"
#define IDS_VENTANA_CHILD_DIBUJO10     "salidas"
#define IDS_VENTANA_CHILD_DIBUJO11     "reglas"
#define IDS_VENTANA_CHILD_DIBUJO12     "Descripción : "
#define IDS_VENTANA_CLIENT_NUEVO       "Nuevo SLD "

/* Cadenas en el archivo DIALOGOS CPP  */

#define IDS_OK                              "Aceptar"
#define IDS_CANCEL                          "Cancelar"
#define IDS_HELP                            "Ayuda"

#define IDS_DIALOG_ENTRARDATOS_CAPTION		  "Valores de Entrada"
#define IDS_DIALOG_ENTRARDATOS_NOMBRE        "Nombre de la Variable:"
#define IDS_DIALOG_ENTRARDATOS_VALOR         "Valor:"

#define IDS_DIALOG_DESCRIPCION_CAPTION		  "Descripción"
#define IDS_DIALOG_DESCRIPCION_LEYENDA      "Leyenda:"

#define IDS_DIALOG_AUTOENTRADA_CAPTION      "Autodefinición de Universos"
#define IDS_DIALOG_AUTOENTRADA_TITULO1      "UNIVERSO DE ENTRADA - Definición Recta"
#define IDS_DIALOG_AUTOENTRADA_TITULO2      "UNIVERSO DE ENTRADA - Definición Curva"
#define IDS_DIALOG_AUTOENTRADA_TITULO3      "UNIVERSO DE SALIDA - Definición Recta"
#define IDS_DIALOG_AUTOENTRADA_TITULO4      "UNIVERSO DE SALIDA - Definición Curva"
#define IDS_DIALOG_AUTOENTRADA_NUMVAR       "Número de Variables"
#define IDS_DIALOG_AUTOENTRADA_NUMCON       "Número de Conjuntos por Variable"

#define IDS_DIALOG_CALCULAR_CAPTION			  "Calcular Salidas"
#define IDS_DIALOG_CALCULAR_ENTRADAS        "Entradas"
#define IDS_DIALOG_CALCULAR_SALIDAS         "Salidas"
#define IDS_DIALOG_CALCULAR_CALCULAR        "Calcular"

#define IDS_DIALOG_VARENT_CAPTION           "Variables del Universo de Entrada"
#define IDS_DIALOG_VARENT_NOMVAR            "Nombre de la Variable"
#define IDS_DIALOG_VARENT_DIFUSOR           "Difusor"
#define IDS_DIALOG_VARENT_NOMCONJ           "Nombre del Conjunto"
#define IDS_DIALOG_VARENT_TIPOCONJ          "Tipo de Conjunto"
#define IDS_DIALOG_VARENT_DEFVAR            "Definir Variable"
#define IDS_DIALOG_VARENT_INSVAR            "Insertar Variable"
#define IDS_DIALOG_VARENT_ELIVAR            "Eliminar Variable"
#define IDS_DIALOG_VARENT_DEFDIF            "Definir Difusor"
#define IDS_DIALOG_VARENT_PUNTOS            "Puntos de Evaluación"
#define IDS_DIALOG_VARENT_DEFCON            "Definir Conjuntos"
#define IDS_DIALOG_VARENT_INSCON            "Insertar Conjuntos"
#define IDS_DIALOG_VARENT_ELICON            "Eliminar Conjuntos"
#define IDS_DIALOG_VARENT_AUTODEF           "Autodefinir"
#define IDS_DIALOG_VARENT_VARENT            "Variable de Entrada"
#define IDS_DIALOG_VARENT_ELIMINAR1			  "No puede eliminar todas las variables"
#define IDS_DIALOG_VARENT_ELIMINAR2			  "Error"
#define IDS_DIALOG_VARENT_ELIMINAR3			  "¿Desea Eliminar "
#define IDS_DIALOG_VARENT_ELIMINAR4			  "Atención"
#define IDS_DIALOG_VARENT_ELIMINAR5			  "No puede eliminar todos los conjuntos"
#define IDS_DIALOG_VARENT_CONJENT           "Conjunto de Entrada"
#define IDS_DIALOG_VARENT_PTOS              "Puntos"

#define IDS_DIALOG_DEFINIRVARIABLEENTRADA_CAPTION			"Definición de Variables"
#define IDS_DIALOG_DEFINIRVARIABLEENTRADA_NOMBRE         "Nombre: "
#define IDS_DIALOG_DEFINIRVARIABLEENTRADA_MINIMO         "Valor Mínimo: "
#define IDS_DIALOG_DEFINIRVARIABLEENTRADA_MAXIMO         "Valor Máximo: "
#define IDS_DIALOG_DEFINIRVARIABLEENTRADA_INTERVALOS     "Intervalos de Evaluación: "
#define IDS_DIALOG_DEFINIRVARIABLEENTRADA_SALIR1         "Los valores Mínimo y Máximo son ilógicos"
#define IDS_DIALOG_DEFINIRVARIABLEENTRADA_SALIR2			"Error"


#define IDS_DIALOG_AUTODEFINIRENTRADAS_CAPTION				"Autodefinición de Variables"
#define IDS_DIALOG_AUTODEFINIRENTRADAS_RECTOS            "Definir Conjuntos Rectos"
#define IDS_DIALOG_AUTODEFINIRENTRADAS_CURVOS            "Definir Conjuntos Curvos"
#define IDS_DIALOG_AUTODEFINIRENTRADAS_CONJUNTOS         "Número de Conjuntos"

#define IDS_DIALOG_INSERTARCONJUNTO_CAPTION		"Insertar Conjunto"
#define IDS_DIALOG_INSERTARCONJUNTO_NOMBRE      "Nombre:"
#define IDS_DIALOG_INSERTARCONJUNTO_TIPO        "Tipo de Conjunto"

#define IDS_DEFINIRDIFUSOR_INTERVALOS_CAPTION    "Definición del Difusor"
#define IDS_STATIC_DEFINIRDIFUSOR_INTERVALOS     "Número de Intervalos de Evaluación:"

/* Cadenas en el archivo SETDIALO CPP  */

#define IDS_DIALOG_DEFINIRCONJUNTOS_CAPTION0     "Definición de Conjuntos Tipo L"
#define IDS_DIALOG_DEFINIRCONJUNTOS_CAPTION1     "Definición de Conjuntos Tipo Triángulo"
#define IDS_DIALOG_DEFINIRCONJUNTOS_CAPTION2     "Definición de Conjuntos Tipo Pi"
#define IDS_DIALOG_DEFINIRCONJUNTOS_CAPTION3     "Definición de Conjuntos Tipo Gamma"
#define IDS_DIALOG_DEFINIRCONJUNTOS_CAPTION4     "Definición de Conjuntos Tipo Z"
#define IDS_DIALOG_DEFINIRCONJUNTOS_CAPTION5     "Definición de Conjuntos Tipo Campana"
#define IDS_DIALOG_DEFINIRCONJUNTOS_CAPTION6     "Definición de Conjuntos Tipo Pi-Campana"
#define IDS_DIALOG_DEFINIRCONJUNTOS_CAPTION7     "Definición de Conjuntos Tipo S"
#define IDS_DIALOG_DEFINIRCONJUNTOS_CAPTION8     "Definición de Conjuntos Tipo Singleton"
#define IDS_DIALOG_DEFINIRCONJUNTOS_NOMBRE       "Nombre :"
#define IDS_DIALOG_DEFINIRCONJUNTOS_A            "a:"
#define IDS_DIALOG_DEFINIRCONJUNTOS_B            "b:"
#define IDS_DIALOG_DEFINIRCONJUNTOS_C            "c:"
#define IDS_DIALOG_DEFINIRCONJUNTOS_D            "d:"
#define IDS_DIALOG_DEFINIRCONJUNTOS_MINIMO       "Valor mínimo de "
#define IDS_DIALOG_DEFINIRCONJUNTOS_MAXIMO       "Valor máximo de "
#define IDS_DIALOG_DEFINIRCONJUNTOS_1            "Valores no permitidos"
#define IDS_DIALOG_DEFINIRCONJUNTOS_2            "Error"
#define IDS_DIALOG_DEFINIRCONJUNTOS_3            "Los valores son ilógicos"
#define IDS_DIALOG_DEFINIRCONJUNTOS_4            "Error"

/* Cadenas en el archivo DIALOGO2 CPP  */

#define IDS_DIALOG_VARSAL_CAPTION           "Variables del Universo de Salida"
#define IDS_DIALOG_VARENT_NOMVAR            "Nombre de la Variable"
#define IDS_DIALOG_VARSAL_CONCRESOR         "Concresor"
#define IDS_DIALOG_VARSAL_VARSAL            "Variable de Salida"
#define IDS_DIALOG_VARSAL_CONJSAL           "Conjunto de Salida"

/* Cadenas en el archivo ENTRDIAL CPP  */

#define IDS_DIALOG_ENTRENA_CAPTION             "Entrenamiento de Sistemas de Lógica Difusa"
#define IDS_DIALOG_ENTRENA_ALGORITMO           "Algoritmo de Entrenamiento"
#define IDS_DIALOG_ENTRENA_ALGORITMO1          "Universos Fijos"
#define IDS_DIALOG_ENTRENA_ALGORITMO2          "Universos Variables"
#define IDS_DIALOG_ENTRENA_TIPO                "Tipo de Entrenamiento"
#define IDS_DIALOG_ENTRENA_TIPO1               "Nuevo"
#define IDS_DIALOG_ENTRENA_TIPO2               "Actualiza"
#define IDS_DIALOG_ENTRENA_ENTRENAR            "Entrenar"
#define IDS_DIALOG_ENTRENA_LEER                "Leer"
#define IDS_DIALOG_ENTRENA_VALIDAR             "Validar"
#define IDS_DIALOG_ENTRENA_NUMPATRONES  		  "Número de Patrones Enseñados :"
#define IDS_DIALOG_ENTRENA_TERMINA1            "Entrenamiento Concluido"
#define IDS_DIALOG_ENTRENA_TERMINA2				  "Atención"
#define IDS_DIALOG_ENTRENA_CONJBASE				  "Conjunto Base"
#define IDS_DIALOG_ENTRENA_ARCHIVO				  "Archivos de Texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*"
#define IDS_DIALOG_ENTRENA_ARCHIVO1				  "Ha ocurrido un error"
#define IDS_DIALOG_ENTRENA_ARCHIVO2     		  "Atención"
#define IDS_DIALOG_ENTRENA_ARCHIVO3				  "No se pudo abrir el archivo "
#define IDS_DIALOG_ENTRENA_ARCHIVO4				  "Error de Lectura"


/* Cadenas en el archivo GENDIAL  CPP  */

#define IDS_DIALOG_GENERARCODIGO_CAPTION            "Generación de Código Fuente"
#define IDS_DIALOG_GENERARCODIGO_GENERAR            "Generar"
#define IDS_DIALOG_GENERARCODIGO_SALVAR             "Salvar"
#define IDS_DIALOG_GENERARCODIGO_C                  "Código C"
#define IDS_DIALOG_GENERARCODIGO_CPP                "Código C++"
#define IDS_DIALOG_GENERARCODIGO_TXT                "Texto"
#define IDS_DIALOG_GENERARCODIGO_CODIGO             "Código Generado :"
#define IDS_DIALOG_GENERARCODIGO_CARACTERES         "Caracteres"
#define IDS_DIALOG_GENERARCODIGO_MISISTEMA			 "MiSistema"
#define IDS_DIALOG_GENERARCODIGO_EXTENSO1				 "Debe salvar la fracción de código generado"
#define IDS_DIALOG_GENERARCODIGO_EXTENSO2				 "Atención: Código muy extenso"
#define IDS_DIALOG_GENERARCODIGO_ARCHIVO				 "Archivo C (*.c)|*.c| Archivos CPP (*.cpp)|*.cpp|Todos los Archivos (*.*)|*.*|Archivos de Texto (*.txt)|*.txt"
#define IDS_DIALOG_GENERARCODIGO_ARCHIVO1				 "Ha ocurrido un error"
#define IDS_DIALOG_GENERARCODIGO_ARCHIVO2     		 "Atención"
#define IDS_DIALOG_GENERARCODIGO_ARCHIVO3				 "No se pudo abrir el archivo "
#define IDS_DIALOG_GENERARCODIGO_ARCHIVO4				 "Error de Lectura"

#define IDS_DIALOG_GENERARTABLA_CAPTION            "Generación de Tabla Entrada-Salida"
#define IDS_DIALOG_GENERARTABLA_GENERAR            "Generar"
#define IDS_DIALOG_GENERARTABLA_SALVAR             "Salvar"
#define IDS_DIALOG_GENERARTABLA_TABLA     	      "Tabla Generada :"
#define IDS_DIALOG_GENERARTABLA_LINEAS		         "Líneas"
#define IDS_DIALOG_GENERARTABLA_EXTENSO1				 "Debe salvar la fracción de Tabla generada"
#define IDS_DIALOG_GENERARTABLA_EXTENSO2				 "Atención: Tabla muy extensa"
#define IDS_DIALOG_GENERARTABLA_ARCHIVO				 "Todos los Archivos (*.*)|*.*|Archivos de Texto (*.txt)|*.txt"
#define IDS_DIALOG_GENERARTABLA_ARCHIVO1				 "Ha ocurrido un error"
#define IDS_DIALOG_GENERARTABLA_ARCHIVO2     		 "Atención"
#define IDS_DIALOG_GENERARTABLA_ARCHIVO3				 "No se pudo abrir el archivo "
#define IDS_DIALOG_GENERARTABLA_ARCHIVO4				 "Error de Lectura"

#define IDS_DIALOG_NOMBRECLASE_CAPTION				"Nombre de la clase generada"
#define IDS_DIALOG_NOMBRECLASE_NOMBRE           "Nombre"


/* Cadenas en el archivo INFDIAL  CPP  */

#define IDS_DIALOG_BASEREGLAS_CAPTION				"Definición de las Reglas de la Máquina de Inferencia"
#define IDS_DIALOG_BASEREGLAS_NUMREGLAS         "Regla Número"
#define IDS_DIALOG_BASEREGLAS_REGLAS            "Total de Reglas"
#define IDS_DIALOG_BASEREGLAS_CERTEZA           "Certeza"
#define IDS_DIALOG_BASEREGLAS_MODIFICADOR       "Modificador Lingüístico del Antecedente"
#define IDS_DIALOG_BASEREGLAS_CONSECUENTE       "Consecuente"
#define IDS_DIALOG_BASEREGLAS_SIGUIENTE         "Siguiente"
#define IDS_DIALOG_BASEREGLAS_ANTERIOR          "Anterior"
#define IDS_DIALOG_BASEREGLAS_IRA               "Nuevo/Ir a..."
#define IDS_DIALOG_BASEREGLAS_ELIMINAR          "Eliminar"
#define IDS_DIALOG_BASEREGLAS_ELIMINARTODAS     "Eliminar Todas"
#define IDS_DIALOG_BASEREGLAS_ELIMINAR_1			"Desea Eliminar la Regla?"
#define IDS_DIALOG_BASEREGLAS_ELIMINAR_2			"Atención"
#define IDS_DIALOG_BASEREGLAS_ELIMINAR_3			"Ya están eliminadas todas las Reglas"
#define IDS_DIALOG_BASEREGLAS_ELIMINAR_4			"Error"
#define IDS_DIALOG_BASEREGLAS_ELIMINAR_5        "Desea eliminar todas las Regla?"
#define IDS_DIALOG_BASEREGLAS_ELIMINAR_6			"Atención"

#define IDS_DIALOG_RAPIDA_CAPTION  				"Definición Rápida de la Base de Reglas"
#define IDS_DIALOG_RAPIDA_VARIABLE           "Variable de Salida:"
#define IDS_DIALOG_RAPIDA_DEFINIR            "Definir Conjunto Completo de Reglas"
#define IDS_DIALOG_RAPIDA_CRECIENTE          "Tendencia Creciente"
#define IDS_DIALOG_RAPIDA_DECRECIENTE        "Tendencia Decreciente"
#define IDS_DIALOG_RAPIDA_CONSTANTE          "Tendencia Constante"
#define IDS_DIALOG_RAPIDA_TENDENCIA1         "Variable definida con tendencia Creciente"
#define IDS_DIALOG_RAPIDA_TENDENCIA2         "Operación concluida"
#define IDS_DIALOG_RAPIDA_TENDENCIA3         "Variable definida con tendencia Decreciente"
#define IDS_DIALOG_RAPIDA_TENDENCIA4         "Operación concluida"
#define IDS_DIALOG_RAPIDA_TENDENCIA5         "Variable definida con tendencia Constante"
#define IDS_DIALOG_RAPIDA_TENDENCIA6         "Operación concluida"
#define IDS_DIALOG_RAPIDA_DEFINE1				"Se han definido"
#define IDS_DIALOG_RAPIDA_DEFINE2				"reglas"
#define IDS_DIALOG_RAPIDA_DEFINE3				"Operación concluida"

#define IDS_DIALOG_OPCION_CAPTION            "Opciones matemáticas de la máquina de inferencia"
#define IDS_DIALOG_OPCION_IMPLICACION        "Implicación"
#define IDS_DIALOG_OPCION_COMPOSICION        "Composición Max-*"
#define IDS_DIALOG_OPCION_AND                "AND"
#define IDS_DIALOG_OPCION_UNION              "Unión-Intersección"   // ¿remplazar por "Agregación"?
#define IDS_DIALOG_OPCION_IMPLICA1           "Esta Implicación requiere una Unión y usted ha seleccionado una Intersección"
#define IDS_DIALOG_OPCION_IMPLICA2				"Advertencia"
#define IDS_DIALOG_OPCION_IMPLICA3				"Esta Implicación requiere una Intersección y usted ha seleccionado una Unión"
#define IDS_DIALOG_OPCION_IMPLICA4				"Advertencia"
#define IDS_DIALOG_OPCION_IMPLICA5           "La Implicación requiere una Unión y usted ha seleccionado una Intersección"
#define IDS_DIALOG_OPCION_IMPLICA6				"Advertencia"
#define IDS_DIALOG_OPCION_IMPLICA7           "La Implicación requiere una Intersección y usted ha seleccionado una Unión"
#define IDS_DIALOG_OPCION_IMPLICA8				"Advertencia"
#define IDS_DIALOG_OPCION_PARAMETRO1			"El parámetro se fijó en 1.0"
#define IDS_DIALOG_OPCION_PARAMETRO2			"Atención"


/* Cadenas en el archivo INFDIAL2 CPP  */

#define IDS_DIALOG_IRAREGLA_CAPTION          "Ir a la Regla Seleccionada"
#define IDS_DIALOG_IRAREGLA_ANTECEDENTES     "Antecedentes :"
#define IDS_DIALOG_IRAREGLA_CONJUNTOS        "Conjuntos :"
#define IDS_DIALOG_IRAREGLA_NUMREGLA         "Número de Regla"
#define IDS_DIALOG_IRAREGLA_TOTREGLA         "Total de Reglas"
#define IDS_DIALOG_IRAREGLA_BUSCAR           "Buscar Regla"
#define IDS_DIALOG_IRAREGLA_ADICIONAR1       "Desea adicionar Regla?"
#define IDS_DIALOG_IRAREGLA_ADICIONAR2       "Regla no Encontrada"

#define IDS_DIALOG_PARAMETRO_CAPTION			"Parámetro de la Norma"
#define IDS_DIALOG_PARAMETRO_PARAMETRO       "Parámetro"


/* Cadenas en el archivo TRANSFE  CPP  */

#define IDS_DIALOG_TRANSFE_CAPTION     "Función de Transferencia"
#define IDS_DIALOG_TRANSFE_ENTRADAS    "Entrada que Varía"
#define IDS_DIALOG_TRANSFE_SALIDAS     "Salida a Analizar"
#define IDS_DIALOG_TRANSFE_FIJAS       "Entradas Fijas"
#define IDS_DIALOG_TRANSFE_LIMPIAR     "Limpiar"
#define IDS_DIALOG_TRANSFE_CALCULAR    "Calcular"
#define IDS_DIALOG_TRANSFE_VARIANDO		"variando"

#define IDS_DIALOG_PASOAPASO_CAPTION       "Análisis Paso a Paso"
#define IDS_DIALOG_PASOAPASO_ENTRADAS      "Valores de Entrada"
#define IDS_DIALOG_PASOAPASO_DIFUSOR       "Difusor"
#define IDS_DIALOG_PASOAPASO_REGLAS        "Reglas Activadas"
#define IDS_DIALOG_PASOAPASO_REGLA         "Regla Individual"
#define IDS_DIALOG_PASOAPASO_UNION         "Agregación"
#define IDS_DIALOG_PASOAPASO_SALIDA        "Salida"
#define IDS_DIALOG_PASOAPASO_INICIO        "Inicio"
#define IDS_DIALOG_PASOAPASO_SIGUIENTE     "Siguiente"
#define IDS_DIALOG_PASOAPASO_TODOS         "Todos"
#define IDS_DIALOG_PASOAPASO_PASO0         "Paso: 0/5"
#define IDS_DIALOG_PASOAPASO_PASO1         "Paso: 1/5"
#define IDS_DIALOG_PASOAPASO_PASO2         "Paso: 2/5"
#define IDS_DIALOG_PASOAPASO_PASO3         "Paso: 3/5"
#define IDS_DIALOG_PASOAPASO_PASO4         "Paso: 4/5"
#define IDS_DIALOG_PASOAPASO_PASO5         "Paso: 5/5"
#define IDS_DIALOG_PASOAPASO_REGLANUMERO   "Regla"
#define IDS_IF                             "IF"
#define IDS_ES                             "es"
#define IDS_MUY                            "muy"
#define IDS_POCO                           "poco"
#define IDS_AND                            "AND"
#define IDS_THEN                           "THEN"

// Texto generado

#define IDS_TEXTO_DESCRIBE				"Descripción del Sistema de Lógica Difusa "
#define IDS_TEXTO_NUMENT				"Número de Entradas"
#define IDS_TEXTO_NUMSAL				"Número de Salidas"
#define IDS_TEXTO_NUMREG				"Número de Reglas"
#define IDS_TEXTO_OPEAND				"Operador AND"
#define IDS_TEXTO_OPECOM				"Operador Composición"
#define IDS_TEXTO_OPEIMP				"Operador Implicación"
#define IDS_TEXTO_OPEUNI				"Operador Unión-Intersección"
#define IDS_TEXTO_ENTRADAS				"ENTRADAS"
#define IDS_TEXTO_VARENTNUM			"Variable de Entrada Número"
#define IDS_TEXTO_VARNOM				"Nombre de la Variable"
#define IDS_TEXTO_VALMIN				"Valor Mínimo"
#define IDS_TEXTO_VALMAX				"Valor Máximo"
#define IDS_TEXTO_NUMCONJ				"Número de Conjuntos"
#define IDS_TEXTO_TIPODIF				"Tipo de Difusor"
#define IDS_TEXTO_PARADIF				"Parámetros del Difusor:"
#define IDS_TEXTO_CONJNUM				"Conjunto Número"
#define IDS_TEXTO_CONJNOM				"Nombre del Conjunto"
#define IDS_TEXTO_TIPOCONJ				"Tipo de Conjunto"
#define IDS_TEXTO_PARAME				"Parámetros"
#define IDS_TEXTO_SALIDAS				"SALIDAS"
#define IDS_TEXTO_VARSALNUM			"Variable de Salida Número"

#define IDS_TEXTO_TIPOCONC				"Tipo de Concresor"

#define IDS_TEXTO_REGLAS				"REGLAS"

#define IDS_TEXTO_INTERVALOS        "Numero de Intervalos de Evaluación"
