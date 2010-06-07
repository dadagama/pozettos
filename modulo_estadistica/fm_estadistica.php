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
	
	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml();
	
	$html->cargarModuloJS($_SESSION['modulo']);

	require_once("../conexiones/ConexionBDMySQL.inc");
	$conexion_bd_bozettos = new ConexionBDMySQL($_SESSION['arregloParametros']);
	$conexion_bd_bozettos->conectar();
	
	if($_REQUEST['con_fecha'])
		$_SESSION['fecha_contabilidad'] = $_REQUEST['con_fecha'];
	else
		$_SESSION['fecha_contabilidad'] = date("Y-m-d");

	$html->tag("table",array("class"=>"tbl_titulo tabla_centrada "));
		$html->tag("tr");
			$html->tag("td", array("class"=>"alineacion_centro"));
				$html->tag("label");
					$html->printText("Estadísticas");
				$html->end("label");
			$html->end("td");
		$html->end("tr");
	$html->end("table");
	
	$html->tag("form", array("id"=>"form_opciones", "onsubmit"=>"return false;"));	  
  	$html->tag("table",array("class"=>"zona_opciones tabla_centrada"));
  		//ENCABEZADOS OPCIONES		
  		$html->tag("thead");
  			$html->tag("tr");
  				
  				$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
  					$html->tag("label", array("class"=>"label_formulario"));
  						$html->printText("Categorías");
  					$html->end("label");
  				$html->end("th");
  			
  				$html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_200"));
  					$html->tag("label", array("class"=>"label_formulario"));
  						$html->printText("Alcance");
  					$html->end("label");
  				$html->end("th");
  				
  			$html->end("tr");
  		$html->end("thead");
  		
  		$html->tag("tbody", array("class"=>"cuerpo_opciones"));
  			$html->tag("tr");
  				$html->tag("td", array("id"=>"td_categorias", "rowspan"=>"2"));
  					
  				$html->end("td");
  				
  				$html->tag("td", array("class"=>"alineacion_centro"));
  					$html->printText("<select id='opc_alcance' name='opc_alcance' class='alineacion_centro letra_azul verdana letra_9 negrilla' onchange='actualizarParametros();'>
  															<option value='diario'>Diario</option>
  															<option value='mensual'>Mensual</option>
  															<option value='rango'>Rango de fechas</option>
  														</select>");
  				$html->end("td");
        $html->end("tr");
        
        $html->tag("tr");
  				$html->tag("td");
  					/* DIARIO */
  					$html->tag("table",array("id"=>"tbl_diario", "class"=>"tabla_centrada"));
  						$html->tag("tr");
  							$html->tag("td", array("class"=>"alineacion_derecha"));
  								$html->tag("label", array("class"=>"letra_azul verdana letra_9 negrilla"));
  									$html->printText("Fecha");
  								$html->end("label");
  							$html->end("td");
  							
  							$html->tag("td");
  								$html->tag("input", array("type"=>"text", "name"=>"opc_fecha", "id"=>"opc_fecha", "class"=>"ancho_100 alineacion_centro letra_azul verdana letra_9 negrilla", "value"=>$_SESSION['fecha_contabilidad']), true);
  							$html->end("td");
  						$html->end("tr");
  					$html->end("table");
  					
  					/* MENSUAL */
  					$html->tag("table",array("id"=>"tbl_mensual", "class"=>"tabla_centrada oculto"));
  						$html->tag("tr");
  							$html->tag("td", array("class"=>"alineacion_derecha"));
  								$html->tag("label", array("class"=>"letra_azul verdana letra_9 negrilla"));
  									$html->printText("Mes");
  								$html->end("label");
  							$html->end("td");
  							
  							$html->tag("td");
  								$html->printText("<select id='opc_mes' name='opc_mes' class='ancho_100 alineacion_centro letra_azul verdana letra_9 negrilla'>
  																		<option value='01'>Enero</option>
  																		<option value='02'>Febrero</option>
  																		<option value='03'>Marzo</option>
  																		<option value='04'>Abril</option>
  																		<option value='05'>Mayo</option>
  																		<option value='06'>Junio</option>
  																		<option value='07'>Julio</option>
  																		<option value='08'>Agosto</option>
  																		<option value='09'>Septiembre</option>
  																		<option value='10'>Octubre</option>
  																		<option value='11'>Noviembre</option>
  																		<option value='12'>Diciembre</option>
  																	</select>");
  							$html->end("td");
  						$html->end("tr");
  						
  						$html->tag("tr");
  							$html->tag("td", array("class"=>"alineacion_derecha"));
  								$html->tag("label", array("class"=>"letra_azul verdana letra_9 negrilla"));
  									$html->printText("Año");
  								$html->end("label");
  							$html->end("td");
  							
  							$html->tag("td");
  								$html->printText("<select id='opc_anno' name='opc_anno' class='ancho_100 alineacion_centro letra_azul verdana letra_9 negrilla'>
  																		<option value='2010'>2010</option>
  																		<option value='2011'>2011</option>
  																		<option value='2012'>2012</option>
  																	</select>");
  							$html->end("td");
  						$html->end("tr");
  					$html->end("table");
  					
  					/* RANGO */
  					$html->tag("table",array("id"=>"tbl_rango", "class"=>"tabla_centrada oculto"));
  						$html->tag("tr");
  							$html->tag("td", array("class"=>"alineacion_derecha"));
  								$html->tag("label", array("class"=>"letra_azul verdana letra_9 negrilla"));
  									$html->printText("Fecha Inicial");
  								$html->end("label");
  							$html->end("td");
  							
  							$html->tag("td");
  								$html->tag("input", array("type"=>"text", "name"=>"opc_fecha_inicial", "id"=>"opc_fecha_inicial", "class"=>"ancho_100 alineacion_centro letra_azul verdana letra_9 negrilla", "value"=>$_SESSION['fecha_contabilidad']), true);
  							$html->end("td");
  						$html->end("tr");
  						
  						$html->tag("tr");
  							$html->tag("td", array("class"=>"alineacion_derecha"));
  								$html->tag("label", array("class"=>"letra_azul verdana letra_9 negrilla"));
  									$html->printText("Fecha Final");
  								$html->end("label");
  							$html->end("td");
  							
  							$html->tag("td");
  								$html->tag("input", array("type"=>"text", "name"=>"opc_fecha_final", "id"=>"opc_fecha_final", "class"=>"ancho_100 alineacion_centro letra_azul verdana letra_9 negrilla", "value"=>$_SESSION['fecha_contabilidad']), true);
  							$html->end("td");
  						$html->end("tr");
  					$html->end("table");
  				$html->end("td");
  			$html->end("tr");
  			
  			$html->tag("tr");
  				$html->tag("td", array("colspan"=>"3", "class"=>"alineacion_centro fila_boton_generar"));
  					$html->tag("button", array("onclick"=>"actualizarEstadisticas();", "class"=>"letra_azul verdana letra_9 negrilla"));
  						$html->printText("Generar<br/>Estadísticas");
  					$html->end("button");
  				$html->end("td");
  			$html->end("tr");
  		$html->end("tbody");
  	$html->end("table");
	$html->end("form");
	
	$html->tag("table",array("id"=>"tbl_estadisticas", "class"=>"tabla_centrada"));
	$html->end("table");
?>
	</body>
</html>