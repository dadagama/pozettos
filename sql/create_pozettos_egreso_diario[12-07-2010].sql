CREATE TABLE pozettos_egreso_diario
(
	egd_fecha DATE NOT NULL COMMENT 'Fecha que corresponde al dinero que sale',
	egd_saldo INTEGER NOT NULL DEFAULT 0 COLLATE utf8_unicode_ci NOT NULL DEFAULT 0 COMMENT 'Total de dinero que sale',
	egd_vigente TINYINT( 1 ) COLLATE utf8_unicode_ci DEFAULT '1' COMMENT 'Bandera para funciones de control'
) ENGINE = MyISAM COMMENT = 'Almacena la informacion del total de dinero que sale diariamente en la contabilidad';
