<html>
	<head>
		<link rel="stylesheet" type="text/css" href="../modulo_cliente/cliente.css"/>
	</head>
	<body>
<?php
/*
 This file is part of Pozettos.

    Pozettos is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pozettos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
    along with Pozettos.  If not, see <http://www.gnu.org/licenses/>.

*/

	session_start();
		
	$_SESSION['modulo'] = "cliente";
	
	require_once("../herramientas/GeneradorHtml2.inc");
	$html2 = new GeneradorHtml2();
  
  $html2->cargarModuloJS($_SESSION['modulo']);
  
  /* TITULO MODULO*/	
	$lbl_titulo = $html2->tag("label", "", array("Clientes Fieles"));
	$td_titulo = $html2->tag("td", "class='alineacion_centro'", array($lbl_titulo));
	$tr_titulo = $html2->tag("tr", "", array($td_titulo));
	$tbl_titulo = $html2->tag("table", "class='tbl_titulo tabla_centrada'", array($tr_titulo));

  /*Nombre*/
  $lbl_nombre = $html2->tag("label", "class='letra_azul verdana letra_9  alineacion_derecha'", array("Nombre"));
  $td_nombre = $html2->tag("td", "class='alineacion_derecha'", array($lbl_nombre));  
  $input_nombre = $html2->tag("input", "id='cli_nombre' type='text' class='letra_azul verdana letra_9'", array(), true);  
  $td_input_nombre = $html2->tag("td", "class='alineacion_derecha'", array($input_nombre)); 
  $tr_nombre = $html2->tag("tr", "", array($td_nombre,$td_input_nombre));  
  /*Apellido*/
  $lbl_apellido = $html2->tag("label", "class='letra_azul verdana letra_9  alineacion_derecha'", array("Apellido"));
  $td_apellido = $html2->tag("td", "class='alineacion_derecha'", array($lbl_apellido));  
  $input_apellido = $html2->tag("input", "id='cli_apellido' type='text' class='letra_azul verdana letra_9'", array(), true);  
  $td_input_apellido = $html2->tag("td", "class='alineacion_derecha'", array($input_apellido));  
  $tr_apellido = $html2->tag("tr", "", array($td_apellido,$td_input_apellido));
  /*Correo*/
  $lbl_correo = $html2->tag("label", "class='letra_azul verdana letra_9  alineacion_derecha'", array("Correo"));
  $td_correo = $html2->tag("td", "class='alineacion_derecha'", array($lbl_correo));  
  $input_correo = $html2->tag("input", "id='cli_email' type='text' class='letra_azul verdana letra_9'", array(), true);  
  $td_input_correo = $html2->tag("td", "class='alineacion_derecha'", array($input_correo));  
  $tr_correo = $html2->tag("tr", "", array($td_correo,$td_input_correo));
  /*Boton*/
  $btn_adicionar = $html2->tag("button", "class='boton_adicionar letra_azul verdana letra_9' onclick='agregarCliente();'", array("Adicionar<br/>Cliente"));
  $td_boton = $html2->tag("td", "colspan='2' class='alineacion_centro'", array($btn_adicionar));
  $tr_boton = $html2->tag("tr", "", array($td_boton));
	/*TABLA NUEVO CLIENTE*/
  $tbl_nuevo_cliente = $html2->tag("table", "", array($tr_nombre,$tr_apellido,$tr_correo,$tr_boton));
  /*FORMULARIO NUEVO CLIENTE*/
  $caption_nuevo_cliente = $html2->tag("legend", "class='letra_azul verdana letra_9'", array("Nuevo Cliente"));
  $form_nuevo_cliente = $html2->tag("fieldset", "class='borde_azul ancho_200 padding_abajo_5 tabla_centrada'", array($caption_nuevo_cliente,$tbl_nuevo_cliente));
  
//   /*codigo*/
//   $lbl_codigo = $html2->tag("label", "class='letra_azul verdana letra_9  alineacion_derecha'", array(utf8_encode("Código")));
//   $td_codigo = $html2->tag("td", "class='alineacion_derecha'", array($lbl_codigo));  
//   $input_codigo = $html2->tag("input", "id='cli_id' type='text' class='letra_azul verdana letra_9'", array(), true);  
//   $td_input_codigo = $html2->tag("td", "class='alineacion_derecha'", array($input_codigo));  
//   $tr_codigo = $html2->tag("tr", "", array($td_codigo,$td_input_codigo));
//   /*Boton*/
//   $btn_buscar = $html2->tag("button", "class='boton_adicionar letra_azul verdana letra_9'", array("Buscar<br/>Cliente"));
//   $td_boton = $html2->tag("td", "colspan='2' class='alineacion_centro'", array($btn_buscar));
//   $tr_boton = $html2->tag("tr", "", array($td_boton));
// 	/*TABLA NUEVO CLIENTE*/
//   $tbl_nuevo_cliente = $html2->tag("table", "", array($tr_codigo,$tr_nombre,$tr_apellido,$tr_correo,$tr_boton));
//   /*FORMULARIO BUSCAR CLIENTE*/
//   $caption_buscar_cliente = $html2->tag("legend", "class='letra_azul verdana letra_9'", array("Buscar Cliente"));
//   $form_buscar_cliente = $html2->tag("fieldset", "class='borde_azul ancho_200 padding_abajo_5 tabla_centrada'", array($caption_buscar_cliente,$tbl_nuevo_cliente));
  
  /*codigo*/
  $lbl_cli_codigo = $html2->tag("label", "class='label_formulario verdana letra_9'", array("Cod"));
  $th_cli_codigo = $html2->tag("th", "class='fondo_azul ancho_20'", array($lbl_cli_codigo));  
  /*nombre*/
  $lbl_cli_nombre = $html2->tag("label", "class='label_formulario verdana letra_9'", array("Nombre"));
  $th_cli_nombre = $html2->tag("th", "class='fondo_azul ancho_200'", array($lbl_cli_nombre));  
  /*apellido*/
  $lbl_cli_apellido = $html2->tag("label", "class='label_formulario verdana letra_9'", array("Apellido"));
  $th_cli_apellido = $html2->tag("th", "class='fondo_azul ancho_200'", array($lbl_cli_apellido));  
  /*correo*/
  $lbl_cli_correo = $html2->tag("label", "class='label_formulario verdana letra_9'", array("Correo"));
  $th_cli_correo = $html2->tag("th", "class='fondo_azul ancho_140'", array($lbl_cli_correo));
  /*Tiempo acumulado*/
  $lbl_cli_tiempo_acumulado = $html2->tag("label", "class='label_formulario verdana letra_9'", array("Tiempo</br>acumulado"));
  $th_cli_tiempo_acumulado = $html2->tag("th", "class='fondo_azul ancho_80'", array($lbl_cli_tiempo_acumulado));
  /*horas gratis*/
  $lbl_cli_gratis_internet = $html2->tag("label", "class='label_formulario verdana letra_9'", array("Horas<br/>gratis"));
  $th_cli_gratis_internet = $html2->tag("th", "class='fondo_azul ancho_80'", array($lbl_cli_gratis_internet));
  /*fila encabezados*/
  $tr_encabezados = $html2->tag("tr", "", array($th_cli_codigo,$th_cli_nombre,$th_cli_apellido,$th_cli_correo,$th_cli_tiempo_acumulado,$th_cli_gratis_internet));
  /*thead*/
  $thead_clientes = $html2->tag("thead", "", array($tr_encabezados));
  /*tbody*/
  $tbody_clientes = $html2->tag("tbody", "id='tbody_clientes'");
	/*TABLA CLIENTES*/
  $tbl_clientes = $html2->tag("table", "id='tbl_clientes'", array($thead_clientes,$tbody_clientes));

  
  /*FILA FORMULARIOS*/
  $td_nuevo_cliente = $html2->tag("td", "class='vertical_abajo'", array($form_nuevo_cliente));
//   $td_buscar_cliente = $html2->tag("td", "class='vertical_abajo'", array($form_buscar_cliente));
  $tr_formularios = $html2->tag("tr", "", array($td_nuevo_cliente/*,$td_buscar_cliente*/));
  /*FILA REGISTROS*/
  $td_clientes = $html2->tag("td", "class='vertical_abajo'", array($tbl_clientes));
  $td_info_cliente = $html2->tag("td", "class='vertical_abajo'", array($tbl_info_cliente));
  $tr_registros = $html2->tag("tr", "", array($td_clientes,$td_info_cliente));
  /*TABLA GENERAL*/
  $tbl_general  = $html2->tag("table", "class='tabla_centrada'", array($tr_formularios,$tr_registros));
  
  $html2->printHtml(array($tbl_titulo, $tbl_general));
?>
	</body>
</html>