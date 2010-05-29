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
	
	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml();
	
	$html->cargarModuloJS($_SESSION['modulo']);

	require_once("../conexiones/ConexionBDMySQL.inc");
	$conexion_bd_bozettos = new ConexionBDMySQL($_SESSION['arregloParametros']);
	$conexion_bd_bozettos->conectar();
	
	$html->tag("table",array("class"=>"tbl_titulo tabla_centrada "));
		$html->tag("tr");
			$html->tag("td", array("class"=>"alineacion_centro"));
				$html->tag("label");
					$html->printText("Registro de deudas pendientes");
				$html->end("label");
			$html->end("td");
		$html->end("tr");
	$html->end("table");
	
	$html->tag("table",array("class"=>"zona_historial ancho_100p"));
		//ENCABEZADOS HISTORIAL		
		$html->tag("thead");
			$html->tag("tr");
				
				$html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_200"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Cliente");
					$html->end("label");
				$html->end("th");
			
				$html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_80"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Fecha");
					$html->end("label");
				$html->end("th");
			
				$html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_140"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Servicio");
					$html->end("label");
				$html->end("th");
				
				$html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_70"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Duración");
					$html->end("label");
				$html->end("th");
				
				$html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_50"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Total");
					$html->end("label");
				$html->end("th");
				
				$html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_50"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Pagó");
					$html->end("label");
				$html->end("th");
				
				$html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_50"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Gratis");
					$html->end("label");
				$html->end("th");
				
				$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Observación");
					$html->end("label");
				$html->end("th");
			$html->end("tr");
		$html->end("thead");
		
		$html->tag("tbody", array("id"=>"historial_deudas", "class"=>"cuerpo_historial"));
			
		$html->end("tbody");
	$html->end("table");
?>
	</body>
</html>