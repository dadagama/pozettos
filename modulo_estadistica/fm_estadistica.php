<html>
	<head>
		<link rel="stylesheet" type="text/css" href="../modulo_estadistica/estadistica.css"/>
		<link rel="stylesheet" type="text/css" href="../estilos/redmond/ui.all.css" />
		<link rel="stylesheet" type="text/css" href="../estilos/redmond/ui.datepicker.css" />
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
		
	$_SESSION['modulo'] = "estadistica";
	
	require_once("../herramientas/GeneradorHtml2.inc");
	$html = new GeneradorHtml2();
	
	$html->cargarModuloJS($_SESSION['modulo']);

	require_once("../conexiones/ConexionBDMySQL.inc");
	$conexion_bd_bozettos = new ConexionBDMySQL($_SESSION['arregloParametros']);
	$conexion_bd_bozettos->conectar();
	
	if($_REQUEST['con_fecha'])
		$_SESSION['fecha_contabilidad'] = $_REQUEST['con_fecha'];
	else
		$_SESSION['fecha_contabilidad'] = date("Y-m-d");

  //titulo modulo
  $label_titulo = $html->tag("label", "",array("Estadísticas"));
  $td_titulo = $html->tag("td", "class='alineacion_centro'", array($label_titulo));
  $tr_titulo = $html->tag("tr", "", array($td_titulo));
  $table_titulo =  $html->tag("table", "class='tbl_titulo tabla_centrada'", array($tr_titulo));

	//thead de opciones
  $th_categoria = $html->tag("th", "class='fondo_azul alineacion_centro ancho_140'", array("<label class='label_formulario'>Categorías</label>"));
  $th_alcance = $html->tag("th", "class='fondo_azul alineacion_centro ancho_200'", array("<label class='label_formulario'>Alcance</label>"));
  $tr_encabezados = $html->tag("tr", "", array($th_categoria,$th_alcance));
  $thead_opciones = $html->tag("thead", "", array($tr_encabezados));
	//tbody de opciones
  $td_categorias = $html->tag("td", "id='td_categorias' rowspan='2'");
  $td_alcance = $html->tag("td", "class='alineacion_izquierda alto_30'", array("
    <label title='Mostrar las estadísticas de un solo día' class='alineacion_izquierda letra_azul verdana letra_9'><input type='radio' checked='checked' onchange='actualizarParametros();' name='opc_alcance' value='diario' />Diario</label><br/>
    <label title='Mostrar las estadísticas del mes' class='alineacion_izquierda letra_azul verdana letra_9'><input type='radio' onchange='actualizarParametros();'  name='opc_alcance' value='mensual'/>Mensual</label><br/>
    <label title='Mostrar las estadísticas entre 2 fechas' class='alineacion_izquierda letra_azul verdana letra_9'><input type='radio' onchange='actualizarParametros();'  name='opc_alcance' value='rango'/>Rango de fechas</label>
  "));
	$tr_alcance = $html->tag("tr", "", array($td_categorias,$td_alcance));

  //table diario
  $td_fecha = $html->tag("td", "class='alineacion_derecha'", array("<label class='letra_azul verdana letra_9'>Fecha</label>"));
  $input_fecha = $html->tag("input", "type='text' name='opc_fecha' id='opc_fecha' class='ancho_100 alineacion_centro letra_azul verdana letra_9' value='".$_SESSION['fecha_contabilidad']."'", "", true);
  $td_input_fecha = $html->tag("td", "", array($input_fecha));
  $tr_fecha = $html->tag("tr", "", array($td_fecha,$td_input_fecha));
  $table_diario = $html->tag("table", "id='tbl_diario' class='tabla_centrada'", array($tr_fecha));
  //table mensual
  $arreglo_fecha = explode("-", $_SESSION['fecha_contabilidad']);
  $arreglo_meses = array("01"=>"Enero","02"=>"Febrero","03"=>"Marzo","04"=>"Abril",
                  "05"=>"Mayo","06"=>"Junio","07"=>"Julio","08"=>"Agosto",
                  "09"=>"Septiembre","10"=>"Octubre","11"=>"Noviembre","12"=>"Diciembre");
  $opciones_mes = "";
  foreach($arreglo_meses AS $num_mes => $nombre_mes)
  {
    $seleccionado_mes = "";
    if($num_mes == $arreglo_fecha[1])
      $seleccionado_mes = "selected='selected'";
    $opciones_mes .= "<option value='$num_mes' $seleccionado_mes>$nombre_mes</option>";
  }
  $td_label_mes = $html->tag("td", "class='alineacion_derecha'", array("<label class='letra_azul verdana letra_9'>Mes</label>"));
  $select_mes = $html->tag("select",
                            "id='opc_mes' name='opc_mes' class='ancho_100 alineacion_izquierda letra_azul verdana letra_9'",
                            array($opciones_mes));
  $td_select_mes = $html->tag("td", "", array($select_mes));
  $tr_mes = $html->tag("tr", "", array($td_label_mes,$td_select_mes));
  $td_label_anno = $html->tag("td", "class='alineacion_derecha'", array("<label class='letra_azul verdana letra_9'>Año</label>"));
  $arreglo_annos = array("2010","2011","2012");
  $opciones_annos = "";
  foreach($arreglo_annos AS $anno)
  {
    $seleccionado_anno = "";
    if($anno == $arreglo_fecha[0])
      $seleccionado_anno = "selected='selected'";
    $opciones_annos .= "<option value='$anno' $seleccionado_anno>$anno</option>";
  }
  $select_anno = $html->tag("select",
                            "id='opc_anno' name='opc_anno' class='ancho_100 alineacion_izquierda letra_azul verdana letra_9'",
                            array($opciones_annos));
  $td_select_anno = $html->tag("td", "", array($select_anno));
  $tr_anno = $html->tag("tr", "", array($td_label_anno,$td_select_anno));
  $table_mensual = $html->tag("table", "id='tbl_mensual' class='tabla_centrada oculto'", array($tr_mes,$tr_anno));
  //table rango
  $td_fecha_inicial = $html->tag("td", "class='alineacion_derecha'", array("<label class='letra_azul verdana letra_9'>Fecha Inicial</label>"));
  $input_fecha_inicial = $html->tag("input", "type='text' name='opc_fecha_inicial' id='opc_fecha_inicial' class='ancho_100 alineacion_centro letra_azul verdana letra_9' value='".$_SESSION['fecha_contabilidad']."'", "", true);
  $td_input_fecha_inicial = $html->tag("td", "", array($input_fecha_inicial));
  $tr_fecha_inicial = $html->tag("tr", "", array($td_fecha_inicial,$td_input_fecha_inicial));
  $td_fecha_final = $html->tag("td", "class='alineacion_derecha'", array("<label class='letra_azul verdana letra_9'>Fecha Final</label>"));
  $input_fecha_final = $html->tag("input", "type='text' name='opc_fecha_final' id='opc_fecha_final' class='ancho_100 alineacion_centro letra_azul verdana letra_9' value='".$_SESSION['fecha_contabilidad']."'", "", true);
  $td_input_fecha_final = $html->tag("td", "", array($input_fecha_final));
  $tr_fecha_final = $html->tag("tr", "", array($td_fecha_final,$td_input_fecha_final));
  $table_rango = $html->tag("table", "id='tbl_rango' class='tabla_centrada oculto'", array($tr_fecha_inicial,$tr_fecha_final));
  //alcance
  $td_alcance_conf = $html->tag("td", "class='alineacion_centro'", array($table_diario, $table_mensual, $table_rango));
	$tr_alcance_conf = $html->tag("tr", "", array($td_alcance_conf));
	//boton
	$button_generar = $html->tag("button", "class='letra_azul verdana letra_9' onclick='actualizarEstadisticas();'", array("Generar<br/>Estadísticas"));
	$button_backup = $html->tag("button", "class='letra_roja verdana letra_9' onclick='generarBackupBD();'", array("Generar<br/>Backup"));
	$td_button_generar = $html->tag("td", "class='alineacion_centro fila_boton_generar' colspan='2'", array($button_generar,$button_backup));
	$tr_button_generar = $html->tag("tr", "", array($td_button_generar));
  $tbody_opciones = $html->tag("tbody", "class='cuerpo_opciones'", array($tr_alcance,$tr_alcance_conf,$tr_button_generar));
	//tabla y form de opciones
	$tabla_opciones = $html->tag("table", "class='zona_opciones tabla_centrada'", array($thead_opciones,$tbody_opciones));
	$form_opciones = $html->tag("form", "id='form_opciones' onsubmit='return false;'", array($tabla_opciones));
  //table estadisticas
  $table_estadisticas = $html->tag("table","id='tbl_estadisticas' class='tabla_centrada'");
  
  $contenido_modulo = "";
  if($viene_de_icono)//hizo click en el menu
    echo $table_titulo, $form_opciones, $table_estadisticas;
  else//actualizo la pagina f5
  {
    $contenido_modulo .= $table_titulo;
    $contenido_modulo .= $form_opciones;
    $contenido_modulo .= $table_estadisticas;
  }
	
?>
	</body>
</html>