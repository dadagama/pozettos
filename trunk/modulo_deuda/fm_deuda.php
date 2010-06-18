<html>
	<head>
		<link rel="stylesheet" type="text/css" href="../modulo_deuda/deuda.css"/>
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
		
	$_SESSION['modulo'] = "deuda";
	
	require_once("../herramientas/GeneradorHtml2.inc");
	$html = new GeneradorHtml2();
	
	$html->cargarModuloJS($_SESSION['modulo']);

	require_once("../conexiones/ConexionBDMySQL.inc");
	$conexion_bd_bozettos = new ConexionBDMySQL($_SESSION['arregloParametros']);
	$conexion_bd_bozettos->conectar();
	
	//tabla titulo
  	 $td_titulo = $html->tag("td", "class='alineacion_centro'", array("<label>Registro de deudas pendientes</label>"));
  	$tr_titulo = $html->tag("tr", "", array($td_titulo));
	$table_titulo = $html->tag("table","class='tbl_titulo tabla_centrada'", array($tr_titulo));
	
	//tabla historial
        $th_cod = $html->tag("th", "class='fondo_azul alineacion_centro'", array("<label class='label_formulario'>Cod</label>"));
        $th_cliente = $html->tag("th", "class='fondo_azul alineacion_centro'", array("<label class='label_formulario'>Cliente</label>"));
        $th_fecha = $html->tag("th", "class='fondo_azul alineacion_centro'", array("<label class='label_formulario'>Fecha</label>"));
        $th_servicio = $html->tag("th", "class='fondo_azul alineacion_centro'", array("<label class='label_formulario'>Servicio</label>"));
        $th_duracion = $html->tag("th", "class='fondo_azul alineacion_centro'", array("<label class='label_formulario'>Duración</label>"));
        $th_total = $html->tag("th", "class='fondo_azul alineacion_centro'", array("<label class='label_formulario'>Total</label>"));
        $th_pago = $html->tag("th", "class='fondo_azul alineacion_centro'", array("<label class='label_formulario'>Pagó</label>"));
        $th_gratis = $html->tag("th", "class='fondo_azul alineacion_centro'", array("<label class='label_formulario'>Gratis</label>"));
        $th_observacion = $html->tag("th", "class='fondo_azul alineacion_centro'", array("<label class='label_formulario'>Observación</label>"));
    	$tr_encabezados = $html->tag("tr", "", array($th_cod,$th_cliente,$th_fecha,$th_servicio,$th_duracion,$th_total,$th_pago,$th_gratis,$th_observacion));
  	$thead_historial = $html->tag("thead", "", array($tr_encabezados));
    $tbody_historial = $html->tag("tbody", "id='historial_deudas' class='cuerpo_historial'");
  $table_historial = $html->tag("table","id='tbl_historial' class='zona_historial ancho_100p'", array($thead_historial,$tbody_historial));
  
  $contenido_modulo = "";
  if($viene_de_icono)//hizo click en el menu
    echo $table_titulo, $table_historial;
  else//actualizo la pagina f5
  {
    $contenido_modulo .= $table_titulo;
    $contenido_modulo .= $table_historial;
  }
?>
	</body>
</html>