/*
 This file is part of Pozzettos.

    Pozzettos is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pozzettos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
    along with Pozzettos.  If not, see <http://www.gnu.org/licenses/>.
*/
DROP TABLE IF EXISTS pozettos_duracion_servicio;
DROP TABLE IF EXISTS pozettos_promocion_horas_gratis;
DROP TABLE IF EXISTS pozettos_permiso_usuario_modulo;
DROP TABLE IF EXISTS pozettos_usuario;
DROP TABLE IF EXISTS pozettos_modulo;
/*DROP TABLE IF EXISTS pozettos_venta_producto;*/
/*DROP TABLE IF EXISTS pozettos_producto;*/
DROP TABLE IF EXISTS pozettos_historico_venta;
DROP TABLE IF EXISTS pozettos_tarifas_servicio;
DROP TABLE IF EXISTS pozettos_categoria_servicios;
DROP TABLE IF EXISTS pozettos_servicio;
DROP TABLE IF EXISTS pozettos_categoria;
/*DROP TABLE IF EXISTS pozettos_jugador;*/
DROP TABLE IF EXISTS pozettos_cliente;
DROP TABLE IF EXISTS pozettos_timer;
DROP TABLE IF EXISTS pozettos_saldo_inicial_titan;

CREATE TABLE pozettos_saldo_inicial_titan
(
	sit_fecha DATE NOT NULL COMMENT 'Fecha que corresponde al saldo inicial',
	sit_saldo INTEGER NOT NULL DEFAULT 0 COLLATE utf8_unicode_ci NOT NULL DEFAULT 0 COMMENT 'saldo inicial diario de titan'
) ENGINE = MyISAM COMMENT = 'Almacena la informacion del saldo inicial de TITAN para cada dia de la contabilidad';


CREATE TABLE pozettos_timer
(
	tim_id CHAR(2) NOT NULL DEFAULT 'a' COMMENT 'identificador del timer',
	tim_dus_minutos TIME COLLATE utf8_unicode_ci NOT NULL COMMENT 'duracion que tendra el timer',
	tim_inicia TIMESTAMP DEFAULT 0 COLLATE utf8_unicode_ci COMMENT 'Momento en que el timer inicia si es incremental',
	tim_finaliza TIMESTAMP DEFAULT 0 COLLATE utf8_unicode_ci COMMENT 'Momento en que el timer finaliza si es decremental',
	tim_pausa TIMESTAMP DEFAULT 0 COLLATE utf8_unicode_ci COMMENT 'Momento en que el timer se pausa',
	tim_es_incremental TINYINT( 1 ) COLLATE utf8_unicode_ci DEFAULT '1' COMMENT 'Bandera que indica si el timer es incremental o no',
	tim_esta_ejecutando TINYINT( 1 ) COLLATE utf8_unicode_ci DEFAULT '1' COMMENT 'Bandera que indica si el timer se esta ejecutando o no'
) ENGINE = MyISAM COMMENT = 'Almacena la informacion de los timers de la contabilidad';

INSERT INTO pozettos_timer VALUES('0','00:00:00','2010-04-01 00:00:00',0,0,1,0);
INSERT INTO pozettos_timer VALUES('1','00:00:00','2010-04-01 00:00:00',0,0,1,0);
INSERT INTO pozettos_timer VALUES('2','00:15:00',0,'2010-04-01 20:00:00',0,0,0);
INSERT INTO pozettos_timer VALUES('3','00:05:00',0,'2010-04-01 20:00:00',0,0,0);
INSERT INTO pozettos_timer VALUES('4','00:00:00',0,0,0,1,0);

/*     ******************************************************************     */
/*     ******************************************************************     */

CREATE TABLE pozettos_duracion_servicio
(
	dus_minutos TIME COLLATE utf8_unicode_ci NOT NULL COMMENT 'duracion que se presta el servicio',
	dus_texto VARCHAR( 10 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'El texto que representa la duracion en formato hh:mm'
) ENGINE = MyISAM COMMENT = 'Almacena los tiempos que pueden prestar los servicios';

INSERT INTO pozettos_duracion_servicio VALUES('00:00:00','Libre');
INSERT INTO pozettos_duracion_servicio VALUES('00:15:00','00:15');
INSERT INTO pozettos_duracion_servicio VALUES('00:30:00','00:30');
INSERT INTO pozettos_duracion_servicio VALUES('00:45:00','00:45');
INSERT INTO pozettos_duracion_servicio VALUES('01:00:00','01:00');
INSERT INTO pozettos_duracion_servicio VALUES('01:15:00','01:15');
INSERT INTO pozettos_duracion_servicio VALUES('01:30:00','01:30');
INSERT INTO pozettos_duracion_servicio VALUES('01:45:00','01:45');
INSERT INTO pozettos_duracion_servicio VALUES('02:00:00','02:00');
INSERT INTO pozettos_duracion_servicio VALUES('02:15:00','02:15');
INSERT INTO pozettos_duracion_servicio VALUES('02:30:00','02:30');
INSERT INTO pozettos_duracion_servicio VALUES('02:45:00','02:45');
INSERT INTO pozettos_duracion_servicio VALUES('03:00:00','03:00');
INSERT INTO pozettos_duracion_servicio VALUES('03:15:00','03:15');
INSERT INTO pozettos_duracion_servicio VALUES('03:30:00','03:30');
INSERT INTO pozettos_duracion_servicio VALUES('03:45:00','03:45');
INSERT INTO pozettos_duracion_servicio VALUES('04:00:00','04:00');
INSERT INTO pozettos_duracion_servicio VALUES('04:15:00','04:15');
INSERT INTO pozettos_duracion_servicio VALUES('04:30:00','04:30');
INSERT INTO pozettos_duracion_servicio VALUES('04:45:00','04:45');
INSERT INTO pozettos_duracion_servicio VALUES('05:00:00','05:00');
INSERT INTO pozettos_duracion_servicio VALUES('05:15:00','05:15');
INSERT INTO pozettos_duracion_servicio VALUES('05:30:00','05:30');
INSERT INTO pozettos_duracion_servicio VALUES('05:45:00','05:45');
INSERT INTO pozettos_duracion_servicio VALUES('06:00:00','06:00');
INSERT INTO pozettos_duracion_servicio VALUES('06:15:00','06:15');
INSERT INTO pozettos_duracion_servicio VALUES('06:30:00','06:30');
INSERT INTO pozettos_duracion_servicio VALUES('06:45:00','06:45');
INSERT INTO pozettos_duracion_servicio VALUES('07:00:00','07:00');
INSERT INTO pozettos_duracion_servicio VALUES('07:15:00','07:15');
INSERT INTO pozettos_duracion_servicio VALUES('07:30:00','07:30');
INSERT INTO pozettos_duracion_servicio VALUES('07:45:00','07:45');
INSERT INTO pozettos_duracion_servicio VALUES('08:00:00','08:00');

/*     ******************************************************************     */
/*     ******************************************************************     */

CREATE TABLE pozettos_usuario
(
	usu_login VARCHAR( 50 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'login del usuario',
	usu_password VARCHAR( 40 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'contraseña del usuario'
) ENGINE = MyISAM COMMENT = 'Almacena los usuarios que tienen acceso a la aplicación';

INSERT INTO pozettos_usuario VALUES('admin','d033e22ae348aeb5660fc2140aec35850c4da997');

/*     ******************************************************************     */
/*     ******************************************************************     */

CREATE TABLE pozettos_cliente
(
	cli_id INTEGER COLLATE utf8_unicode_ci NOT NULL AUTO_INCREMENT COMMENT 'identificador/código del cliente',
	cli_password VARCHAR( 40 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'contraseña para acceder al perfil del cliente',
	cli_nombre VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre(s) del cliente',
	cli_apellido VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'apellido(s) del cliente',
	cli_url_foto VARCHAR( 500 ) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'c_0.png' COMMENT 'url donde se encuentra alojada la foto del perfil del cliente',
	cli_email VARCHAR( 100 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'direccion de correo electrónico del cliente',
	PRIMARY KEY (cli_id)
) ENGINE = MyISAM COMMENT = 'Almacena la información de los clientes del negocio';

INSERT INTO pozettos_cliente VALUES(1,'','Nadie','','c_1.png','nadie@gmail.com');
/*INSERT INTO pozettos_cliente VALUES(2,'40bd001563085fc35165329ea1ff5c5ecbdbbeef','Darwin David','García Maya','c_2.png','dadagama@gmail.com');
INSERT INTO pozettos_cliente VALUES(3,'','Melissa','García Maya','c_3.png','cristian@gmail.com');
INSERT INTO pozettos_cliente VALUES(4,'','Cristian','García Maya','c_4.png','cristian@gmail.com');
INSERT INTO pozettos_cliente VALUES(5,'','Tomas','García','c_5.png','cristian@gmail.com');
INSERT INTO pozettos_cliente VALUES(6,'','Luz Elena','Maya','c_6.png','cristian@gmail.com');*/


/*     ******************************************************************     */
/*     ******************************************************************     */
/*
CREATE TABLE pozettos_jugador
(
	jug_cli_id INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'referencia al identificador/código del cliente',
	jug_num_retos_ganados INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'cantidad de retos ganados por el jugador',
	jug_num_retos_perdidos INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'cantidad de retos perdidos por el jugador',
	jug_nick VARCHAR( 20 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'alias del jugador',
	jug_url_foto VARCHAR( 500 ) COLLATE utf8_unicode_ci NOT NULL DEFAULT 'j_0.png' COMMENT 'url donde se encuentra alojada la foto del perfil del jugador',
	FOREIGN KEY (jug_cli_id) REFERENCES pozettos_cliente (cli_id) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = MyISAM COMMENT = 'Almacena la información de los jugadores';

INSERT INTO pozettos_jugador VALUES(2,5,1,'DaDaGaMa','j_1.png');
*/
/*     ******************************************************************     */
/*     ******************************************************************     */

CREATE TABLE pozettos_servicio
(
	ser_id INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'identificador/código del producto',
	ser_nombre VARCHAR( 500 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre del producto',
	ser_url_foto VARCHAR( 500 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'url de la foto del producto',
	ser_onclick VARCHAR( 500 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'url de la foto del producto',
	ser_tipo VARCHAR( 500 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'cadena con el tipo de servicio'
) ENGINE = MyISAM COMMENT = 'Almacena la información de los servicios ofrecidos en el negocio';

INSERT INTO pozettos_servicio VALUES(1,'Xbox 1', '../imagenes/x1.png','agregarFilaHistorial(1,\'servicio\');','servicio');
INSERT INTO pozettos_servicio VALUES(2,'Xbox 2', '../imagenes/x2.png','agregarFilaHistorial(2,\'servicio\');','servicio');
INSERT INTO pozettos_servicio VALUES(3,'Xbox 3', '../imagenes/x3.png','agregarFilaHistorial(3,\'servicio\');','servicio');
INSERT INTO pozettos_servicio VALUES(4,'Xbox 4', '../imagenes/x4.png','agregarFilaHistorial(4,\'servicio\');','servicio');
INSERT INTO pozettos_servicio VALUES(5,'Cabina 1', '../imagenes/pc1.png','agregarFilaHistorial(5,\'servicio\');','servicio');
INSERT INTO pozettos_servicio VALUES(6,'Cabina 2', '../imagenes/pc2.png','agregarFilaHistorial(6,\'servicio\');','servicio');
INSERT INTO pozettos_servicio VALUES(7,'Cabina 3', '../imagenes/pc3.png','agregarFilaHistorial(7,\'servicio\');','servicio');
INSERT INTO pozettos_servicio VALUES(8,'Cabina 4', '../imagenes/pc4.png','agregarFilaHistorial(8,\'servicio\');','servicio');
INSERT INTO pozettos_servicio VALUES(9,'Wii 1', '../imagenes/wii.png','agregarFilaHistorial(9,\'servicio\');','servicio');
INSERT INTO pozettos_servicio VALUES(10,'Recarga FULLCARGA', '../imagenes/fullcarga.png','agregarFilaHistorial(10,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(11,'Recarga TIGO', '../imagenes/tigo.png','agregarFilaHistorial(11,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(12,'Minutos Celular', '../imagenes/celular.png','agregarFilaHistorial(12,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(13,'Minuto Inalambrico', '../imagenes/inalambrico.png','agregarFilaHistorial(13,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(14,'Minuto Fijo Local', '../imagenes/fijo.png','agregarFilaHistorial(14,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(15,'Cabina Internacional', '../imagenes/internacional.png','agregarFilaHistorial(15,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(16,'Fotocopia', '../imagenes/fotocopiadora.png','agregarFilaHistorial(16,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(17,'Impresion', '../imagenes/impresora.png','agregarFilaHistorial(17,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(18,'Escaneada', '../imagenes/escaner.png','agregarFilaHistorial(18,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(19,'Papeleria', '../imagenes/papeleria.png','agregarFilaHistorial(19,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(20,'Quemada', '../imagenes/cd.png','agregarFilaHistorial(20,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(21,'Mecato', '../imagenes/mecato.png','agregarFilaHistorial(21,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(22,'Tarjeta YA!', '../imagenes/tarjetaYa.png','agregarFilaHistorial(22,\'producto\');','producto');
INSERT INTO pozettos_servicio VALUES(50,'Otro', '../imagenes/otro.png','agregarFilaHistorial(50,\'producto\');','producto');


/*     ******************************************************************     */
/*     ******************************************************************     */

CREATE TABLE pozettos_categoria
(
	cat_id INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'identificador/codigo de la categoria',
	cat_nombre VARCHAR( 500 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre de la categoria del servicio'
) ENGINE = MyISAM COMMENT = 'Almacena la información de las categorias a las que pueden pertenecer los servicios';

INSERT INTO pozettos_categoria VALUES(1,'Todo');
INSERT INTO pozettos_categoria VALUES(2,'Recargas');
INSERT INTO pozettos_categoria VALUES(3,'Llamadas');
INSERT INTO pozettos_categoria VALUES(4,'Juegos');
INSERT INTO pozettos_categoria VALUES(5,'Cabinas');
INSERT INTO pozettos_categoria VALUES(6,'Otros');

/*     ******************************************************************     */
/*     ******************************************************************     */

CREATE TABLE pozettos_categoria_servicios
(
	cas_ser_id INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'identificador/código del servicio',
	cas_cat_id INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'identificador/código de la categoria'
) ENGINE = MyISAM COMMENT = 'Almacena la información de los servicios ofrecidos en el negocio';

INSERT INTO pozettos_categoria_servicios VALUES(1,1);
INSERT INTO pozettos_categoria_servicios VALUES(2,1);
INSERT INTO pozettos_categoria_servicios VALUES(3,1);
INSERT INTO pozettos_categoria_servicios VALUES(4,1);
INSERT INTO pozettos_categoria_servicios VALUES(5,1);
INSERT INTO pozettos_categoria_servicios VALUES(6,1);
INSERT INTO pozettos_categoria_servicios VALUES(7,1);
INSERT INTO pozettos_categoria_servicios VALUES(8,1);
INSERT INTO pozettos_categoria_servicios VALUES(9,1);
INSERT INTO pozettos_categoria_servicios VALUES(10,1);
INSERT INTO pozettos_categoria_servicios VALUES(11,1);
INSERT INTO pozettos_categoria_servicios VALUES(12,1);
INSERT INTO pozettos_categoria_servicios VALUES(13,1);
INSERT INTO pozettos_categoria_servicios VALUES(14,1);
INSERT INTO pozettos_categoria_servicios VALUES(15,1);
INSERT INTO pozettos_categoria_servicios VALUES(16,1);
INSERT INTO pozettos_categoria_servicios VALUES(17,1);
INSERT INTO pozettos_categoria_servicios VALUES(18,1);
INSERT INTO pozettos_categoria_servicios VALUES(19,1);
INSERT INTO pozettos_categoria_servicios VALUES(10,2);
INSERT INTO pozettos_categoria_servicios VALUES(11,2);
INSERT INTO pozettos_categoria_servicios VALUES(12,3);
INSERT INTO pozettos_categoria_servicios VALUES(13,3);
INSERT INTO pozettos_categoria_servicios VALUES(14,3);
INSERT INTO pozettos_categoria_servicios VALUES(15,3);
INSERT INTO pozettos_categoria_servicios VALUES(1,4);
INSERT INTO pozettos_categoria_servicios VALUES(2,4);
INSERT INTO pozettos_categoria_servicios VALUES(3,4);
INSERT INTO pozettos_categoria_servicios VALUES(4,4);
INSERT INTO pozettos_categoria_servicios VALUES(9,4);
INSERT INTO pozettos_categoria_servicios VALUES(5,5);
INSERT INTO pozettos_categoria_servicios VALUES(6,5);
INSERT INTO pozettos_categoria_servicios VALUES(7,5);
INSERT INTO pozettos_categoria_servicios VALUES(8,5);
INSERT INTO pozettos_categoria_servicios VALUES(16,6);
INSERT INTO pozettos_categoria_servicios VALUES(17,6);
INSERT INTO pozettos_categoria_servicios VALUES(18,6);
INSERT INTO pozettos_categoria_servicios VALUES(19,6);
INSERT INTO pozettos_categoria_servicios VALUES(20,6);
INSERT INTO pozettos_categoria_servicios VALUES(21,6);
INSERT INTO pozettos_categoria_servicios VALUES(22,6);
INSERT INTO pozettos_categoria_servicios VALUES(50,6);


/*     ******************************************************************     */
/*     ******************************************************************     */

CREATE TABLE pozettos_tarifas_servicio
(
	tas_ser_id INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'referencia a identificador/código del servicio',
	tas_dus_minutos TIME COLLATE utf8_unicode_ci NOT NULL COMMENT 'duracion por uso del servicio',
	tas_precio INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'tarifa a cobrar por uso del servicio'
) ENGINE = MyISAM COMMENT = 'Almacena la información de las tarifas de cada servicio por minutos de uso';

/*XBOX 1*/
INSERT INTO pozettos_tarifas_servicio VALUES(1,'00:00:00',0);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'00:15:00',500);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'00:30:00',1000);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'00:45:00',1400);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'01:00:00',1800);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'01:15:00',2300);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'01:30:00',2700);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'01:45:00',3200);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'02:00:00',3600);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'02:15:00',4000);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'02:30:00',4400);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'02:45:00',4800);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'03:00:00',5200);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'03:15:00',5600);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'03:30:00',6000);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'03:45:00',6400);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'04:00:00',6800);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'04:15:00',7200);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'04:30:00',7500);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'04:45:00',7900);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'05:00:00',8200);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'05:15:00',8600);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'05:30:00',8900);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'05:45:00',9300);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'06:00:00',9600);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'06:15:00',9900);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'06:30:00',10200);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'06:45:00',10500);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'07:00:00',10800);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'07:15:00',11100);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'07:30:00',11400);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'07:45:00',11700);
INSERT INTO pozettos_tarifas_servicio VALUES(1,'08:00:00',12000);
/*XBOX 2*/
INSERT INTO pozettos_tarifas_servicio VALUES(2,'00:00:00',0);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'00:15:00',500);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'00:30:00',1000);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'00:45:00',1400);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'01:00:00',1800);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'01:15:00',2300);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'01:30:00',2700);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'01:45:00',3200);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'02:00:00',3600);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'02:15:00',4000);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'02:30:00',4400);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'02:45:00',4800);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'03:00:00',5200);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'03:15:00',5600);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'03:30:00',6000);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'03:45:00',6400);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'04:00:00',6800);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'04:15:00',7200);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'04:30:00',7500);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'04:45:00',7900);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'05:00:00',8200);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'05:15:00',8600);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'05:30:00',8900);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'05:45:00',9300);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'06:00:00',9600);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'06:15:00',9900);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'06:30:00',10200);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'06:45:00',10500);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'07:00:00',10800);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'07:15:00',11100);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'07:30:00',11400);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'07:45:00',11700);
INSERT INTO pozettos_tarifas_servicio VALUES(2,'08:00:00',12000);
/*XBOX 2*/
INSERT INTO pozettos_tarifas_servicio VALUES(3,'00:00:00',0);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'00:15:00',500);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'00:30:00',1000);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'00:45:00',1400);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'01:00:00',1800);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'01:15:00',2300);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'01:30:00',2700);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'01:45:00',3200);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'02:00:00',3600);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'02:15:00',4000);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'02:30:00',4400);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'02:45:00',4800);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'03:00:00',5200);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'03:15:00',5600);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'03:30:00',6000);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'03:45:00',6400);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'04:00:00',6800);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'04:15:00',7200);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'04:30:00',7500);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'04:45:00',7900);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'05:00:00',8200);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'05:15:00',8600);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'05:30:00',8900);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'05:45:00',9300);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'06:00:00',9600);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'06:15:00',9900);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'06:30:00',10200);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'06:45:00',10500);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'07:00:00',10800);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'07:15:00',11100);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'07:30:00',11400);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'07:45:00',11700);
INSERT INTO pozettos_tarifas_servicio VALUES(3,'08:00:00',12000);
/*XBOX 4*/
INSERT INTO pozettos_tarifas_servicio VALUES(4,'00:00:00',0);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'00:15:00',500);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'00:30:00',1000);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'00:45:00',1400);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'01:00:00',1800);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'01:15:00',2300);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'01:30:00',2700);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'01:45:00',3200);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'02:00:00',3600);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'02:15:00',4000);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'02:30:00',4400);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'02:45:00',4800);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'03:00:00',5200);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'03:15:00',5600);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'03:30:00',6000);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'03:45:00',6400);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'04:00:00',6800);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'04:15:00',7200);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'04:30:00',7500);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'04:45:00',7900);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'05:00:00',8200);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'05:15:00',8600);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'05:30:00',8900);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'05:45:00',9300);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'06:00:00',9600);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'06:15:00',9900);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'06:30:00',10200);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'06:45:00',10500);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'07:00:00',10800);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'07:15:00',11100);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'07:30:00',11400);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'07:45:00',11700);
INSERT INTO pozettos_tarifas_servicio VALUES(4,'08:00:00',12000);
/*CABINA 1*/
INSERT INTO pozettos_tarifas_servicio VALUES(5,'00:00:00',0);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'00:15:00',500);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'00:30:00',700);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'00:45:00',1000);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'01:00:00',1300);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'01:15:00',1600);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'01:30:00',1900);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'01:45:00',2200);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'02:00:00',2500);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'02:15:00',2800);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'02:30:00',3100);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'02:45:00',3400);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'03:00:00',3700);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'03:15:00',4000);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'03:30:00',4300);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'03:45:00',4600);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'04:00:00',4900);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'04:15:00',5200);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'04:30:00',5400);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'04:45:00',5700);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'05:00:00',5900);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'05:15:00',6200);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'05:30:00',6400);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'05:45:00',6700);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'06:00:00',6900);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'06:15:00',7200);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'06:30:00',7400);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'06:45:00',7700);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'07:00:00',7900);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'07:15:00',8200);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'07:30:00',8400);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'07:45:00',8700);
INSERT INTO pozettos_tarifas_servicio VALUES(5,'08:00:00',8900);
/*CABINA 2*/
INSERT INTO pozettos_tarifas_servicio VALUES(6,'00:00:00',0);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'00:15:00',500);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'00:30:00',700);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'00:45:00',1000);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'01:00:00',1300);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'01:15:00',1600);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'01:30:00',1900);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'01:45:00',2200);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'02:00:00',2500);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'02:15:00',2800);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'02:30:00',3100);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'02:45:00',3400);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'03:00:00',3700);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'03:15:00',4000);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'03:30:00',4300);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'03:45:00',4600);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'04:00:00',4900);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'04:15:00',5200);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'04:30:00',5400);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'04:45:00',5700);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'05:00:00',5900);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'05:15:00',6200);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'05:30:00',6400);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'05:45:00',6700);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'06:00:00',6900);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'06:15:00',7200);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'06:30:00',7400);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'06:45:00',7700);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'07:00:00',7900);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'07:15:00',8200);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'07:30:00',8400);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'07:45:00',8700);
INSERT INTO pozettos_tarifas_servicio VALUES(6,'08:00:00',8900);
/*CABINA 3*/
INSERT INTO pozettos_tarifas_servicio VALUES(7,'00:00:00',0);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'00:15:00',500);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'00:30:00',700);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'00:45:00',1000);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'01:00:00',1300);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'01:15:00',1600);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'01:30:00',1900);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'01:45:00',2200);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'02:00:00',2500);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'02:15:00',2800);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'02:30:00',3100);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'02:45:00',3400);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'03:00:00',3700);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'03:15:00',4000);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'03:30:00',4300);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'03:45:00',4600);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'04:00:00',4900);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'04:15:00',5200);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'04:30:00',5400);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'04:45:00',5700);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'05:00:00',5900);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'05:15:00',6200);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'05:30:00',6400);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'05:45:00',6700);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'06:00:00',6900);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'06:15:00',7200);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'06:30:00',7400);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'06:45:00',7700);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'07:00:00',7900);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'07:15:00',8200);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'07:30:00',8400);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'07:45:00',8700);
INSERT INTO pozettos_tarifas_servicio VALUES(7,'08:00:00',8900);
/*CABINA 4*/
INSERT INTO pozettos_tarifas_servicio VALUES(8,'00:00:00',0);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'00:15:00',500);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'00:30:00',700);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'00:45:00',1000);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'01:00:00',1300);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'01:15:00',1600);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'01:30:00',1900);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'01:45:00',2200);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'02:00:00',2500);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'02:15:00',2800);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'02:30:00',3100);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'02:45:00',3400);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'03:00:00',3700);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'03:15:00',4000);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'03:30:00',4300);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'03:45:00',4600);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'04:00:00',4900);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'04:15:00',5200);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'04:30:00',5400);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'04:45:00',5700);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'05:00:00',5900);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'05:15:00',6200);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'05:30:00',6400);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'05:45:00',6700);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'06:00:00',6900);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'06:15:00',7200);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'06:30:00',7400);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'06:45:00',7700);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'07:00:00',7900);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'07:15:00',8200);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'07:30:00',8400);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'07:45:00',8700);
INSERT INTO pozettos_tarifas_servicio VALUES(8,'08:00:00',8900);
/*WII 1*/
INSERT INTO pozettos_tarifas_servicio VALUES(9,'00:00:00',0);
INSERT INTO pozettos_tarifas_servicio VALUES(9,'00:15:00',800);
INSERT INTO pozettos_tarifas_servicio VALUES(9,'00:30:00',1500);
INSERT INTO pozettos_tarifas_servicio VALUES(9,'00:45:00',2000);
INSERT INTO pozettos_tarifas_servicio VALUES(9,'01:00:00',2500);
INSERT INTO pozettos_tarifas_servicio VALUES(9,'01:15:00',3100);
INSERT INTO pozettos_tarifas_servicio VALUES(9,'01:30:00',3800);
INSERT INTO pozettos_tarifas_servicio VALUES(9,'01:45:00',4400);
INSERT INTO pozettos_tarifas_servicio VALUES(9,'02:00:00',5000);
INSERT INTO pozettos_tarifas_servicio VALUES(9,'02:15:00',5600);
INSERT INTO pozettos_tarifas_servicio VALUES(9,'02:30:00',6400);
INSERT INTO pozettos_tarifas_servicio VALUES(9,'02:45:00',6800);
INSERT INTO pozettos_tarifas_servicio VALUES(9,'03:00:00',7200);


/*     ******************************************************************     */
/*     ******************************************************************     */

CREATE TABLE pozettos_modulo
(
	mod_id INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'identificador/código del módulo',
	mod_nombre VARCHAR( 500 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nombre del módulo',
	mod_url_foto VARCHAR( 500 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'url donde se encuentra alojada la foto del módulo',
	mod_onclick VARCHAR( 500 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'accion javascript al dar click en el módulo'
) ENGINE = MyISAM COMMENT = 'Almacena la información de los módulos disponibles en la aplicación';

INSERT INTO pozettos_modulo VALUES(1,'Contabilidad diaria','../imagenes/modulo_contabilidad.png','mostrarContabilidad();');
INSERT INTO pozettos_modulo VALUES(2,'Consultar clientes que deben','../imagenes/modulo_deuda.png','mostrarDeudores();');

/*     ******************************************************************     */
/*     ******************************************************************     */

CREATE TABLE pozettos_permiso_usuario_modulo
(
	pum_usu_login VARCHAR( 50 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'referencia a login del usuario',
	pum_mod_id INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'referencia a identificador/código del módulo'
) ENGINE = MyISAM COMMENT = 'Almacena la información de los módulos disponibles en la aplicación';

/*     ******************************************************************     */
/*     ******************************************************************     */
/*
CREATE TABLE pozettos_promocion_horas_gratis
(
	phg_cli_id INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'referencia al identificador/código del cliente',
	phg_tiempo_acumulado_servicio INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'duracion en minutos que el cliente ha usado los servicios',
	phg_tiempo_acumulado_gratis_cobrado INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'duracion en minutos que el cliente ha cobrado en tiempo gratis'
) ENGINE = MyISAM COMMENT = 'Almacena la información de la promoción (horas gratis) por cada cliente';
*/
/*     ******************************************************************     */
/*     ******************************************************************     */

CREATE TABLE pozettos_historico_venta
(
	hiv_id SERIAL NOT NULL AUTO_INCREMENT COMMENT 'consecutivo de la venta',
	hiv_cli_id INTEGER COLLATE utf8_unicode_ci NOT NULL DEFAULT '1' COMMENT 'referencia al identificador/código del cliente',
	hiv_ser_id INTEGER COLLATE utf8_unicode_ci NOT NULL COMMENT 'servicio prestado',
	hiv_ser_tipo VARCHAR( 500 ) COLLATE utf8_unicode_ci NOT NULL COMMENT 'cadena con el tipo de servicio',
	hiv_color_fila VARCHAR( 7 ) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'color que tiene la fila en notacion #FFFFFF',
	hiv_pago TINYINT( 1 ) COLLATE utf8_unicode_ci DEFAULT 0 COMMENT 'Bandera que indica si se pago el servicio',
	hiv_es_tiempo_gratis TINYINT( 1 ) COLLATE utf8_unicode_ci DEFAULT 0 COMMENT 'Bandera que indica si el servicio se cuenta como tiempo gratis cobrado',
	hiv_fecha DATE NOT NULL COMMENT 'Fecha de cuando se anoto el servicio prestado',
	hiv_hora TIME NOT NULL DEFAULT '00:00:00' COMMENT 'La hora cuando se presto el servicio',
	hiv_meridiano CHAR(2) NOT NULL DEFAULT 'NN' COMMENT 'El meridiano en que se presto el servicio (AM/PM)',
	hiv_dus_minutos TIME NOT NULL DEFAULT '00:00:00' COMMENT 'La duracion del servicio prestado',
	hiv_total INTEGER NOT NULL DEFAULT 0 COLLATE utf8_unicode_ci NOT NULL DEFAULT 0 COMMENT 'valor total del servicio vendido',
	hiv_observacion VARCHAR( 200 ) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT 'descripción de la venta'
) ENGINE = MyISAM COMMENT = 'Almacena el histórico de ventas de productos';