<html>
	<head>
		<title>Pozetto's.NET</title>
		<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
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
	
	$html->cargarHerramientaJS("../herramientas/jquery.vreboton.ColorPicker");
	$html->cargarModuloJS($_SESSION['modulo']);

/********************************************************************
  LA CONEXIÓN SE HACE EN EL MODULO PRINCIPAL, SE DEBE QUITAR DE AQUI
********************************************************************/	
	require_once("../conexiones/ConexionBDMySQL.inc");
	$_SESSION['arregloParametros'] = array(	"con_servidor" => "localhost",
																					"con_usuario" => "root",
																					"con_password" => "root",
																					"con_nombre_bd" => "pozettos");
	$conexion_bd_bozettos = new ConexionBDMySQL($_SESSION['arregloParametros']);
	$conexion_bd_bozettos->conectar();
	
	/* TITULO CON LA FECHA DEL DIA */
	$html->tag("table",array("class"=>"tbl_titulo alineacion_centro"));
		$html->tag("tr");
			$html->tag("td", array("class"=>"ancho_40"));
				$html->tag("form", array("action"=>"index.php", "method"=>"post"));
					$html->tag("input", array("class"=>"img_titulo", "title"=>"Ir al panel de control", "name"=>"modulo", "type"=>"image", "src"=>"../imagenes/home.png", "value"=>"login"), true);
				$html->end("form");
			$html->end("td");
			
			$html->tag("td", array("class"=>"ancho_40"));
				$html->tag("form", array("action"=>"index.php", "method"=>"post"));
					$html->tag("input", array("class"=>"img_titulo", "title"=>"Ir a contabilidad de hoy", "name"=>"modulo", "type"=>"image", "src"=>"../imagenes/modulo_contabilidad.png", "value"=>"contabilidad"), true);
				$html->end("form");
			$html->end("td");
			
			$html->tag("td", array("class"=>"alineacion_centro"));
				$html->tag("label", array("class"=>"lbl_titulo"));
					$html->printText("DEUDAS POR CLIENTE");
				$html->end("label");
			$html->end("td");
		$html->end("tr");
	$html->end("table");
	
	
	/*ZONA CLIENTE*/
	$html->tag("table", array("class"=>"zona_productos"));
		$html->tag("tr");
			$html->tag("td");
	
				/*  TABLA CLIENTE */
				$html->tag("table",array("class"=>"tabla_cliente alineacion_centro"));
					$html->tag("tr");

						// CELDA TOTAL CLIENTE
						$html->tag("td", array("class"=>"celda_interna fondo_azul"));
							$html->tag("table",array("class"=>"tabla_interna"));
								
								$html->tag("caption");
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText("Cliente");
									$html->end("label");
								$html->end("caption");
									
								$html->tag("tr");
									$html->tag("td", array("class"=>"alineacion_centro"));
										$html->tag("label", array("class"=>"label_formulario"));
											$html->printText("Buscar");
										$html->end("label");
									$html->end("td");
									
									$html->tag("td", array("class"=>"alineacion_centro"));
										$html->tag("input", array("id"=>"buscar_cliente", "type"=>"text", "class"=>"input_cliente", "maxlength"=>"100", "onkeyup"=>"actualizarListaClientes(event.keyCode);"));
									$html->end("td");
								$html->end("tr");
									
								$html->tag("tr");
									$html->tag("td", array("class"=>"alineacion_centro", "colspan"=>"2"));
										$html->printSelect($conexion_bd_bozettos, "cli_id", "concat(cli_id, \" - \", cli_nombre, \" \", cli_apellido)", "pozettos_cliente", "", $_POST['cli_id'], array("id"=>"vep_cli_id", "class"=>"select_cliente alineacion_izquierda", "size"=>"7", "onchange"=>"actualizarHistoricoProductos(); actualizarHistoricoServicios();"));
									$html->end("td");
								$html->end("tr");						
	
							$html->end("table");
						$html->end("td");
							
					$html->end("tr");
				$html->end("table");
			$html->end("td");
			
			$html->tag("td");
			
				$html->tag("table",array("class"=>"tabla_historial_producto"));
					//ENCABEZADOS HISTORIAL		
					$html->tag("thead");
						$html->tag("tr");
							
							$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Fecha");
								$html->end("label");
							$html->end("th");
						
							$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Producto");
								$html->end("label");
							$html->end("th");
							
							$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Hora");
								$html->end("label");
							$html->end("th");

							$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Total");
								$html->end("label");
							$html->end("th");

							$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Observación");
								$html->end("label");
							$html->end("th");
						
							$html->tag("th");
							$html->end("th");
							
							$html->tag("th", array("class"=>"ancho_scroll"));
							$html->end("th");
							
						$html->end("tr");
					$html->end("thead");
					
					
					$html->tag("tbody", array("id"=>"vep_historial", "class"=>"cuerpo_historial_producto"));
						
						/*  HISTORICO PRODUCTOS */
						
					$html->end("tbody");
				$html->end("table");
			
			$html->end("td");
			
		$html->end("tr");
	$html->end("table");
	
	
	/* ZONA SERVICIOS */
	$html->tag("table",array("class"=>"tabla_historial_servicio"));
	
	//ENCABEZADOS HISTORIAL		
		$html->tag("thead");
			$html->tag("tr");
			
				$html->tag("th", array("class"=>"fondo_verde alineacion_centro"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Fecha");
					$html->end("label");
				$html->end("th");
			
				$html->tag("th", array("class"=>"fondo_verde alineacion_centro"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Servicio");
					$html->end("label");
				$html->end("th");
				
				$html->tag("th", array("class"=>"fondo_verde alineacion_centro"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Hora Inicio");
					$html->end("label");
				$html->end("th");
				
				$html->tag("th", array("class"=>"fondo_verde alineacion_centro"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Duración");
					$html->end("label");
				$html->end("th");

				$html->tag("th", array("class"=>"fondo_verde alineacion_centro"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Total");
					$html->end("label");
				$html->end("th");
				
				$html->tag("th", array("class"=>"fondo_verde alineacion_centro"));
					$html->tag("label", array("class"=>"label_formulario"));
						$html->printText("Observación");
					$html->end("label");
				$html->end("th");
				
				$html->tag("th");
				$html->end("th");
				
				$html->tag("th", array("class"=>"ancho_scroll"));
				$html->end("th");
			$html->end("tr");
		$html->end("thead");
		
		
		$html->tag("tbody", array("id"=>"ves_historial", "class"=>"cuerpo_historial_servicio"));
		$html->end("tbody");
	$html->end("table");
?>
	</body>
</html>