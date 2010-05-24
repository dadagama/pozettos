﻿<html>
	<head>
		<link rel="stylesheet" type="text/css" href="../modulo_panel/panel.css"/>
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
		
	$_SESSION['modulo'] = "panel";
	
	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml();
	
	$html->cargarModuloJS($_SESSION['modulo']);
	
	/* TITULO*/
	$html->tag("table",array("class"=>"tbl_titulo tabla_centrada borde_azul"));
		$html->tag("tr");
			$html->tag("td", array("class"=>"alineacion_centro"));
				$html->tag("label");
					$html->printText("Pozetto's.Net");
				$html->end("label");
			$html->end("td");
			
			$html->tag("td", array("class"=>"ancho_40"));
				$html->tag("input", array("title"=>"Ir al panel de control", "type"=>"image", "src"=>"../imagenes/home.png", "onclick"=>"mostrarModulo('panel');"), true);
			$html->end("td");
			
			$html->tag("td", array("class"=>"ancho_40"));
				$html->tag("input", array("title"=>"Ir a contabilidad de HOY", "type"=>"image", "src"=>"../imagenes/modulo_contabilidad.png", "onclick"=>"mostrarModulo('contabilidad');"), true);
			$html->end("td");
			
			$html->tag("td", array("class"=>"ancho_40"));
				$html->tag("input", array("title"=>"Ir a Deudas de clientes", "type"=>"image", "src"=>"../imagenes/modulo_deuda.jpg", "onclick"=>"mostrarModulo('deuda');"), true);
			$html->end("td");
			
			$html->tag("td", array("class"=>"ancho_40"));
				$html->tag("input", array("title"=>"Ir a Estadisticas", "type"=>"image", "src"=>"../imagenes/estadistica.gif", "onclick"=>"mostrarModulo('estadistica');"), true);
			$html->end("td");
		$html->end("tr");
	$html->end("table");
	
	$html->tag("table",array("class"=>"tbl_titulo tabla_centrada "));
		$html->tag("tr");
			$html->tag("td", array("class"=>"alineacion_centro"));
				$html->tag("label");
					$html->printText("Panel de Control");
				$html->end("label");
			$html->end("td");
		$html->end("tr");
	$html->end("table");
		
	/*ZONA modulos*/
	$html->tag("table", array("id"=>"tbl_modulos", "class"=>"tabla_centrada"));

		$html->tag("tr");
				$html->tag("td", array("class"=>"alineacion_centro"));
					$html->tag("input", array("class"=>"ancho_80 alineacion_centro letra_9 verdana letra_azul", "maxlength "=>"10","name"=>"con_fecha", "id"=>"con_fecha", "type"=>"text", "value"=>date("Y-m-d")), true);
					$html->br();
					$html->tag("input", array("type"=>"image", "src"=>"../imagenes/modulo_contabilidad.png", "onclick"=>"mostrarContabilidad();"), true);
				$html->end("td");
				
				$html->tag("td", array("class"=>"alineacion_centro"));
					$html->tag("input", array("type"=>"image", "src"=>"../imagenes/modulo_deuda.jpg", "onclick"=>"mostrarDeudores();"), true);
				$html->end("td");
		$html->end("tr");
		
		$html->tag("tr");
			$html->tag("td", array("class"=>"alineacion_centro"));
				$html->tag("label", array("class"=>"letra_9 verdana letra_azul negrilla"));
					$html->printText("Contabilidad diaria");
				$html->end("label");
			$html->end("td");

			$html->tag("td", array("class"=>"alineacion_centro"));
				$html->tag("label", array("class"=>"letra_9 verdana letra_azul negrilla"));
					$html->printText("Consultar deudas");
				$html->end("label");
			$html->end("td");
		$html->end("tr");
		
	$html->end("table");
	
?>
	</body>
</html>