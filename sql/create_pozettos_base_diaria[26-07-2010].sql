CREATE TABLE pozettos_base_diaria
(
	bas_fecha DATE NOT NULL COMMENT 'Fecha que corresponde al dinero base del dia',
	bas_saldo INTEGER NOT NULL DEFAULT 0 COLLATE utf8_unicode_ci NOT NULL DEFAULT 0 COMMENT 'Total de dinero base del dia',
	bas_vigente TINYINT( 1 ) COLLATE utf8_unicode_ci DEFAULT '1' COMMENT 'Bandera para funciones de control'
) ENGINE = MyISAM COMMENT = 'Almacena la informacion del total de dinero base del dia en la contabilidad';
