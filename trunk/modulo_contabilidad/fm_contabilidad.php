﻿<html>
	<head>
		<link rel="stylesheet" type="text/css" href="../modulo_contabilidad/contabilidad.css"/>
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
		
	$_SESSION['modulo'] = "contabilidad";
	if($_REQUEST['con_fecha'])
		$_SESSION['fecha_contabilidad'] = $_REQUEST['con_fecha'];
	else
		$_SESSION['fecha_contabilidad'] = date("Y-m-d");
	require_once("../herramientas/GeneradorHtml.inc");
	$html = new GeneradorHtml();
	
	require_once("../modulo_contabilidad/Contabilidad.inc");
	$objetoContabilidad = new Contabilidad($_SESSION['arregloParametros'], $_SESSION['fecha_contabilidad']);
	
	$html->cargarHerramientaJS("../herramientas/jquery.vreboton.ColorPicker");
	$html->cargarModuloJS($_SESSION['modulo']);
	
	require_once("../conexiones/ConexionBDMySQL.inc");
	$conexion_bd_bozettos = new ConexionBDMySQL($_SESSION['arregloParametros']);
	$conexion_bd_bozettos->conectar();

	/* TITULO CON LA FECHA DEL DIA */
	$html->tag("table",array("id"=>"tbl_titulo", "class"=>"tabla_centrada"));
		$html->tag("tr");
			$html->tag("td", array("class"=>"alineacion_centro"));
				$html->tag("label");
					$html->printText("CONTABILIDAD");
				$html->end("label");
				$html->br();
				$html->tag("label", array("id"=>"lbl_fecha_contabilidad"));
					$html->printText($html->obtenerFechaTextual($_SESSION['fecha_contabilidad'], true, true, true, true));
					$html->tag("input", array("type"=>"hidden", "id"=>"fecha_contabilidad", "value"=>$_SESSION['fecha_contabilidad']));
				$html->end("label");
			$html->end("td");
			
			$html->tag("td", array("class"=>"ancho_40"));
				$html->tag("input", array("title"=>"Volver al panel de control", "type"=>"image", "src"=>"../imagenes/home.png", "onclick"=>"mostrarPanel();"), true);
			$html->end("td");
			
			$html->tag("td", array("class"=>"ancho_40"));
				$html->tag("input", array("title"=>"Ir a consultar deudas", "type"=>"image", "src"=>"../imagenes/modulo_deuda.jpg"), true);
			$html->end("td");
		$html->end("tr");
	$html->end("table");
	
	/*TABLA PRODUCTOS Y SERVICIOS*/
	$html->tag("table", array("class"=>"tabla_centrada margen_arriba_10"));
		$html->tag("tr");
			$html->tag("td");
				$objetoContabilidad->obtenerTablaServicios();
			$html->end("td");
			
			$html->tag("td", array("class"=>"vertical_arriba"));
				$html->tag("table", array("class"=>"fondo_azul"));
							
							/* TIMER 0 */
							$html->tag("tr");
								
								$html->tag("td");
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText("Xbox 1");
									$html->end("label");
								$html->end("td");
								$html->tag("td");
									$html->tag("input", array("id"=>"tim_duracion_horas_0", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText(":");
									$html->end("label");
									$html->tag("input", array("id"=>"tim_duracion_minutos_0", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText(":");
									$html->end("label");
									$html->tag("input", array("id"=>"tim_duracion_segundos_0", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
								$html->end("td");
								$html->tag("td");
									$html->tag("button", array("id"=>"btn_play_pause_0", "class"=>"boton_timer", "onclick"=>"IniciarCrono(0);"));
										$html->tag("img", array("id"=>"img_play_pause_0", "src"=>"../imagenes/play.jpg", "class"=>"imagen_timer"), true);
									$html->end("button");
								$html->end("td");
								
								$html->tag("td");
									$html->tag("button", array("class"=>"boton_timer", "onclick"=>"InicializarCrono(0);"));
										$html->tag("img", array("src"=>"../imagenes/stop.jpg", "class"=>"imagen_timer"), true);
									$html->end("button");
								$html->end("td");
							$html->end("tr");
							
							/* TIMER 1 */
							$html->tag("tr");
								
								$html->tag("td");
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText("Xbox 2");
									$html->end("label");
								$html->end("td");
								$html->tag("td");
									$html->tag("input", array("id"=>"tim_duracion_horas_1", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText(":");
									$html->end("label");
									$html->tag("input", array("id"=>"tim_duracion_minutos_1", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText(":");
									$html->end("label");
									$html->tag("input", array("id"=>"tim_duracion_segundos_1", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
								$html->end("td");
								
								$html->tag("td");
									$html->tag("button", array("id"=>"btn_play_pause_1", "class"=>"boton_timer", "onclick"=>"IniciarCrono(1);"));
										$html->tag("img", array("id"=>"img_play_pause_1", "src"=>"../imagenes/play.jpg", "class"=>"imagen_timer"), true);
									$html->end("button");
								$html->end("td");
								
								$html->tag("td");
									$html->tag("button", array("class"=>"boton_timer", "onclick"=>"InicializarCrono(1);"));
										$html->tag("img", array("src"=>"../imagenes/stop.jpg", "class"=>"imagen_timer"), true);
									$html->end("button");
								$html->end("td");
							$html->end("tr");
						
							/* TIMER 2 */
							$html->tag("tr");
								
								$html->tag("td");
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText("Play 1");
									$html->end("label");
								$html->end("td");
								$html->tag("td");
									$html->tag("input", array("id"=>"tim_duracion_horas_2", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText(":");
									$html->end("label");
									$html->tag("input", array("id"=>"tim_duracion_minutos_2", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText(":");
									$html->end("label");
									$html->tag("input", array("id"=>"tim_duracion_segundos_2", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
								$html->end("td");
								
								$html->tag("td");
									$html->tag("button", array("id"=>"btn_play_pause_2", "class"=>"boton_timer", "onclick"=>"IniciarCrono(2);"));
										$html->tag("img", array("id"=>"img_play_pause_2", "src"=>"../imagenes/play.jpg", "class"=>"imagen_timer"), true);
									$html->end("button");
								$html->end("td");
								
								$html->tag("td");
									$html->tag("button", array("class"=>"boton_timer", "onclick"=>"InicializarCrono(2);"));
										$html->tag("img", array("src"=>"../imagenes/stop.jpg", "class"=>"imagen_timer"), true);
									$html->end("button");
								$html->end("td");
							$html->end("tr");
							
							/* TIMER 3 */
							$html->tag("tr");
								
								$html->tag("td");
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText("Play 2");
									$html->end("label");
								$html->end("td");
								$html->tag("td");
									$html->tag("input", array("id"=>"tim_duracion_horas_3", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText(":");
									$html->end("label");
									$html->tag("input", array("id"=>"tim_duracion_minutos_3", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText(":");
									$html->end("label");
									$html->tag("input", array("id"=>"tim_duracion_segundos_3", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
								$html->end("td");
								
								$html->tag("td");
									$html->tag("button", array("id"=>"btn_play_pause_3", "class"=>"boton_timer", "onclick"=>"IniciarCrono(3);"));
										$html->tag("img", array("id"=>"img_play_pause_3", "src"=>"../imagenes/play.jpg", "class"=>"imagen_timer"), true);
									$html->end("button");
								$html->end("td");
								
								$html->tag("td");
									$html->tag("button", array("class"=>"boton_timer", "onclick"=>"InicializarCrono(3);"));
										$html->tag("img", array("src"=>"../imagenes/stop.jpg", "class"=>"imagen_timer"), true);
									$html->end("button");
								$html->end("td");
							$html->end("tr");
							
							/* TIMER 4 */
							$html->tag("tr");
					
								$html->tag("td");
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText("Otro");
									$html->end("label");
								$html->end("td");
								
								$html->tag("td");
									$html->tag("input", array("id"=>"tim_duracion_horas_4", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText(":");
									$html->end("label");
									$html->tag("input", array("id"=>"tim_duracion_minutos_4", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
									$html->tag("label", array("class"=>"label_formulario"));
										$html->printText(":");
									$html->end("label");
									$html->tag("input", array("id"=>"tim_duracion_minutos_4", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
								$html->end("td");
								
								$html->tag("td");
									$html->tag("button", array("id"=>"btn_play_pause_4", "class"=>"boton_timer", "onclick"=>"IniciarCrono(4);"));
										$html->tag("img", array("id"=>"img_play_pause_4", "src"=>"../imagenes/play.jpg", "class"=>"imagen_timer"), true);
									$html->end("button");
								$html->end("td");
								
								$html->tag("td");
									$html->tag("button", array("class"=>"boton_timer", "onclick"=>"InicializarCrono(4);"));
										$html->tag("img", array("src"=>"../imagenes/stop.jpg", "class"=>"imagen_timer"), true);
									$html->end("button");
								$html->end("td");
							$html->end("tr");

						$html->end("table");
					$html->end("td");
					
				$html->end("tr");
	$html->end("table");
	
	/* ZONA HISTORIAL */
	// $html->tag("table", array("class"=>"zona_historial"));
		// $html->tag("tr");
			// $html->tag("td", array("class"=>"tabla_servicio"));
	
	
				// $html->tag("table",array("class"=>"tabla_servicio alineacion_centro"));
					// $html->tag("tr");
					
						
						
						// /* CELDA HORA INICIO */
						// $html->tag("td", array("class"=>"celda_interna fondo_verde"));
							// $html->tag("table",array("class"=>"tabla_interna"));
								
								// $html->tag("caption");
									// $html->tag("label", array("class"=>"label_formulario"));
										// $html->printText("Hora Inicio");
									// $html->end("label");
								// $html->end("caption");
								
								// $html->tag("tr");
									// $html->tag("td");
										// $html->tag("select", array("id"=>"ves_hora", "class"=>"select_hora verdana letra_9", "size"=>"9"));
											// $arreglo_horas = array("1"=>"01","2"=>"02","3"=>"03","4"=>"04","5"=>"05","6"=>"06","7"=>"07","8"=>"08","9"=>"09","10"=>"10","11"=>"11","12"=>"12");
											// $html->arregloAOpciones($arreglo_horas);
										// $html->end("select");
									// $html->end("td");
									
									// $html->tag("td");
										// $html->tag("label", array("class"=>"label_formulario"));
										// $html->printText(":");
									// $html->end("label");
									// $html->end("td");
									
									// $html->tag("td");
										// $html->tag("select", array("id"=>"ves_minuto", "class"=>"select_hora verdana letra_9", "size"=>"9"));
											// $arreglo_minutos = array("0"=>"00","5"=>"05","10"=>"10","15"=>"15","20"=>"20","25"=>"25","30"=>"30","35"=>"35","40"=>"40","45"=>"45","50"=>"50","55"=>"55");
											// $html->arregloAOpciones($arreglo_minutos);
										// $html->end("select");
									// $html->end("td");
									
									// $html->tag("td", array("class"=>"alineacion_centro"));
										// $html->tag("select", array("id"=>"ves_meridiano", "class"=>"select_hora verdana letra_9", "size"=>"2"));
											// $arreglo_meridiano = array("am"=>"AM","pm"=>"PM");
											// $html->arregloAOpciones($arreglo_meridiano);
										// $html->end("select");
										
										// $html->br(2);
										
										// $html->tag("button", array("class"=>"boton_hora", "onclick"=>"actualizarHoraInicio();"));
											// $html->tag("img", array("src"=>"../imagenes/clock.png", "class"=>"imagen_hora"), true);
										// $html->end("button");
									// $html->end("td");
								// $html->end("tr");
								
							// $html->end("table");
						// $html->end("td");
						
						// /* CELDA DURACION */
						// $html->tag("td", array("class"=>"celda_interna fondo_verde"));
							// $html->tag("table",array("class"=>"tabla_interna"));
								
								// $html->tag("caption");
									// $html->tag("label", array("class"=>"label_formulario"));
										// $html->printText("Duración");
									// $html->end("label");
								// $html->end("caption");
						
								// $html->tag("tr");
									// $html->tag("td");
										// $html->printSelect($conexion_bd_bozettos, "dus_minutos", "dus_texto", "pozettos_duracion_servicio", "", "00:00:00", array("id"=>"ves_duracion", "class"=>"select_duracion verdana letra_9 alineacion_centro", "size"=>"9", "onchange"=>"actualizarTotalServicio();"));
									// $html->end("td");
								// $html->end("tr");

							// $html->end("table");
						// $html->end("td");
						
					// $html->end("tr");
				// $html->end("table");
			// $html->end("td");
			
			// $html->tag("td",array("class"=>"alineacion_centro"));
			// $html->end("td");
			
		// $html->end("tr");
		
		// $html->tag("tr");
			// $html->tag("td", array("colspan"=>"2"));
				$html->tag("table",array("class"=>"zona_historial ancho_100p"));
				
				//ENCABEZADOS HISTORIAL		
					$html->tag("thead");
						$html->tag("tr");
							$html->tag("th");
							$html->end("th");
						
							$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Servicio");
								$html->end("label");
							$html->end("th");
							
							$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Inicio");
								$html->end("label");
							$html->end("th");
							
							$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Duración");
								$html->end("label");
							$html->end("th");
							
							$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Termina");
								$html->end("label");
							$html->end("th");
							
							$html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_50"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Total");
								$html->end("label");
							$html->end("th");
							
							$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Pagó");
								$html->end("label");
							$html->end("th");
							
							$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Gratis");
								$html->end("label");
							$html->end("th");
							
							$html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_55"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Cliente");
								$html->end("label");
							$html->end("th");
							
							$html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
								$html->tag("label", array("class"=>"label_formulario"));
									$html->printText("Observación");
								$html->end("label");
							$html->end("th");
						
							$html->tag("th");
							$html->end("th");
							
							// $html->tag("th", array("class"=>"ancho_scroll"));
							// $html->end("th");
						$html->end("tr");
					$html->end("thead");
					
					$html->tag("tbody", array("id"=>"historial_ventas", "class"=>"cuerpo_historial"));
						
					$html->end("tbody");
				$html->end("table");
?>
	</body>
</html>