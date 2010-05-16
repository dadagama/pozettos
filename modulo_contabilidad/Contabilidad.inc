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


require_once("../conexiones/ConexionBDMySQL.inc");
require_once("../herramientas/GeneradorHtml.inc");

class Contabilidad
{
	var $_conexionBD;	
	var $_conexionBDAux;
	var $_html;
	var $_fecha_contabilidad;
	
	function __construct($parametrosConexion, $fecha_contabilidad)
	{
		$this->_conexionBD = new ConexionBDMySQL($parametrosConexion);
		$this->_conexionBD->conectar();
		$this->_conexionBDAux = new ConexionBDMySQL($parametrosConexion);
		$this->_conexionBDAux->conectar();
		$this->_html = new GeneradorHtml();
		$this->_fecha_contabilidad = $fecha_contabilidad;
	}

/**********************************
******* ACCIONES GENERICAS  *******
***********************************/
	/*
	function actualizarListaClientes($info_cliente)
	{
		$sql = "SELECT cli_id, concat(cli_id, \" - \", cli_nombre, \" \", cli_apellido) as cli_nombre
						FROM pozettos_cliente
						WHERE cli_id like '$info_cliente'
						OR cli_nombre like '%$info_cliente%'
						OR cli_apellido like '%$info_cliente%'
						OR cli_id = 1
						ORDER BY cli_id ASC";

		$this->_conexionBD->ejecutarSQL($sql);
		
		$opciones_select = "";
		$contador = 0;
		while($info_cliente = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
		{
			$seleccionado = "";
			if($contador == 0)
				$seleccionado = "selected";
			$opciones_select .= "<option value='".$info_cliente['cli_id']."' $seleccionado='$seleccionado'>".$info_cliente['cli_nombre']."</option>";
			$contador++;
		}
		return $opciones_select;
	}
*/	
	function actualizarCampoColor($id, $color_fila, $prefijo)
	{
		if($color_fila == "null")
			$color_fila = "null";
		else
			$color_fila = "'".$color_fila."'";
		
		$tabla = "";
		if($prefijo == "vep")
			$tabla = "pozettos_venta_producto";
		else if($prefijo == "ves")
			$tabla = "pozettos_venta_servicio";

		$sql = "UPDATE $tabla
						SET ".$prefijo."_color_fila = $color_fila
						WHERE ".$prefijo."_id = '$id'";
		$this->_conexionBD->ejecutarSQL($sql);
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return true;
		else
			return false;
	}
/*
	function actualizarEstadoDeuda($prefijo, $id_fila, $estado)
	{
		$tabla = "";
		if($prefijo == "vep")
			$tabla = "pozettos_venta_producto";
		else if($prefijo == "ves")
			$tabla = "pozettos_venta_servicio";
		$reiniciar_color = "";
		//FUNCIONALIDAD COMENTADA SIN APROBAR:
		//Quitar el color de la fila cuando se pague la deuda
		//if($estado)
			//$reiniciar_color = ", ".$prefijo."_color_fila = null";
		$sql = "UPDATE $tabla
						SET ".$prefijo."_pago = '$estado'
						$reiniciar_color
						WHERE ".$prefijo."_id = '$id_fila'";
		$this->_conexionBD->ejecutarSQL($sql);
		return $prefijo;
	}
	
	function eliminarFila($id, $prefijo)
	{
		$tabla = "";
		if($prefijo == "vep")
			$tabla = "pozettos_venta_producto";
		else if($prefijo == "ves")
			$tabla = "pozettos_venta_servicio";
		
		$sql = "DELETE FROM $tabla
						WHERE ".$prefijo."_id = '$id'";
		$this->_conexionBD->ejecutarSQL($sql);
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return $prefijo."_fila_".$id;
		else
			return false;
	}

	function actualizarObservacion($prefijo, $id_fila, $observacion)
	{
		$tabla = "";
		if($prefijo == "vep")
			$tabla = "pozettos_venta_producto";
		else if($prefijo == "ves")
			$tabla = "pozettos_venta_servicio";
			
		$sql = "UPDATE $tabla
						SET ".$prefijo."_observacion = '$observacion'
						WHERE ".$prefijo."_id = '$id_fila'";
		$this->_conexionBD->ejecutarSQL($sql);
		echo $sql;
	}
	*/
/**********************************
******* ACCIONES PRODUCTOS  *******
***********************************/
	/*
	function agregarFilaProducto($vep_cli_id, $vep_pro_id, $vep_total, $vep_fecha_venta)
	{
		if($vep_fecha_venta)
		{
			$campo_vep_fecha_venta = ", vep_fecha_venta";
			$valor_vep_fecha_venta = ", '$vep_fecha_venta'";
		}
		$sql = "INSERT INTO pozettos_venta_producto
						(vep_cli_id, vep_pro_id, vep_total $campo_vep_fecha_venta)
						VALUES
						('$vep_cli_id', '$vep_pro_id', '$vep_total' $valor_vep_fecha_venta)";
		$this->_conexionBD->ejecutarSQL($sql);
		//echo $sql;
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return true;
		else
			return false;
	}
	
	function actualizarHistoricoProductos()
	{
		$sql = "SELECT	vep1.vep_id,
										vep1.vep_cli_id,
										vep1.vep_color_fila, 
										vep1.vep_pago, 
										date_format(vep1.vep_fecha_venta, '%l:%i%p') as vep_fecha_venta,
										vep1.vep_total, 
										vep1.vep_observacion, 
										pro_nombre,
										cli_nombre,
										(	SELECT SUM(vep2.vep_total)
											FROM pozettos_venta_producto AS vep2
											WHERE SUBSTRING( vep2.vep_fecha_venta, 1, 10 ) != '".$this->_fecha_contabilidad."'
											AND vep2.vep_cli_id = vep1.vep_cli_id
											AND vep2.vep_pago = 0
										)AS deuda_producto_vieja,
										(	SELECT SUM(ves3.ves_total)
											FROM pozettos_venta_servicio AS ves3
											WHERE ves3.ves_fecha != '".$this->_fecha_contabilidad."'
											AND ves3.ves_cli_id = vep1.vep_cli_id
											AND ves3.ves_pago = 0
										)AS deuda_servicio_vieja
						FROM 	pozettos_venta_producto AS vep1, pozettos_producto, pozettos_cliente
						WHERE vep1.vep_pro_id = pro_id
						AND vep1.vep_cli_id = cli_id
						AND SUBSTRING(vep_fecha_venta, 1, 10) = '".$this->_fecha_contabilidad."'
						ORDER BY vep_color_fila DESC, vep_fecha_venta DESC";
		$this->_conexionBD->ejecutarSQL($sql);
		$contador = 0;

		while($info_tupla_historico_producto = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
		{
			$vep_color_fila = "";
			if($info_tupla_historico_producto['vep_color_fila'])
				$vep_color_fila = "{background: ".$info_tupla_historico_producto['vep_color_fila'].";}";
			$fondo_default = "";
			if(!$fondo_default && $contador % 2 == 0)
				$fondo_default = "fila_historial_par";
			else if (!$fondo_default)
				$fondo_default = "fila_historial_impar";
			
			$this->_html->tag("tr", array("style"=>$vep_color_fila, "class"=>$fondo_default, "id"=>"vep_fila_".$info_tupla_historico_producto['vep_id'], "name"=>"vep_fila"));
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("input", array("type"=>"image", "src"=>"../imagenes/color.jpg", "id"=>"vep_color_".$info_tupla_historico_producto['vep_id'], "class"=>"boton_color"));
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_izquierda celda_producto"));
					$this->_html->tag("label");
						$this->_html->printText(utf8_encode($info_tupla_historico_producto['pro_nombre']));
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_izquierda celda_producto"));
					$this->_html->tag("label");
						$this->_html->printText($info_tupla_historico_producto['vep_fecha_venta']);
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_derecha celda_producto"));
					$this->_html->tag("label");
						$this->_html->printText($this->_html->colocarPuntoMiles($info_tupla_historico_producto['vep_total']));
					$this->_html->end("label");
				$this->_html->end("td");

				$checked_pago = "";
				$checked_debe = "";
				$clase_celda_pago = "";
				$clase_celda_debe = "";
				if($info_tupla_historico_producto['vep_pago'])
				{
					$checked_pago = "checked";
					$clase_celda_pago = "celda_pago";
				}
				else
				{
					$checked_debe = "checked";
					$clase_celda_debe = "celda_debe";
				}
				
				$this->_html->tag("td", array("id"=>"vep_pago_".$info_tupla_historico_producto['vep_id'], "class"=>"alineacion_centro $clase_celda_pago"));
					$this->_html->tag("input", array($checked_pago=>$checked_pago, "type"=>"radio", "name"=>"vep_rad_pago_".$info_tupla_historico_producto['vep_id'], "onchange"=>"actualizarEstadoDeuda(".$info_tupla_historico_producto['vep_id'].", 1, 'vep');"));
				$this->_html->end("td");
				
				$this->_html->tag("td", array("id"=>"vep_debe_".$info_tupla_historico_producto['vep_id'], "class"=>"alineacion_centro $clase_celda_debe"));
					$this->_html->tag("input", array($checked_debe=>$checked_debe, "type"=>"radio", "name"=>"vep_rad_pago_".$info_tupla_historico_producto['vep_id'], "onchange"=>"actualizarEstadoDeuda(".$info_tupla_historico_producto['vep_id'].", 0, 'vep');"));
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro celda_producto"));
					$this->_html->tag("label", array("title"=>utf8_encode($info_tupla_historico_producto['cli_nombre'])));
						$this->_html->tag("form", array("action"=>"index.php", "method"=>"post"));
							$this->_html->printText($info_tupla_historico_producto['vep_cli_id']);
							$total_deuda = $info_tupla_historico_producto['deuda_producto_vieja'] + $info_tupla_historico_producto['deuda_servicio_vieja'];
							if($total_deuda != "0")
							{
								$this->_html->espacios();
								$this->_html->tag("input", array("type"=>"image", "name"=>"modulo", "value"=>"deuda", "src"=>"../imagenes/deuda.gif", "class"=>"imagen_deuda", "title"=>utf8_encode($info_tupla_historico_producto['cli_nombre']." debe [".$total_deuda."] de otros días")), true);
								$this->_html->tag("input", array("type"=>"hidden", "name"=>"cli_id", "value"=>$info_tupla_historico_producto['vep_cli_id']));
							}
							$this->_html->end("form");
						$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("input", array("id"=>"vep_observacion_".$info_tupla_historico_producto['vep_id'], "type"=>"text", "class"=>"input_observacion_producto celda_producto", "value"=>utf8_encode($info_tupla_historico_producto['vep_observacion']), "onkeyup"=>"actualizarObservacion(event.keyCode, ".$info_tupla_historico_producto['vep_id'].", 'vep');", "onchange"=>"actualizarObservacion(13, ".$info_tupla_historico_producto['vep_id'].", 'vep');"), true);
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("button", array("class"=>"boton_delete", "onclick"=>"eliminarFila(".$info_tupla_historico_producto['vep_id'].",'vep')"));
						$this->_html->tag("img", array("src"=>"../imagenes/delete.png", "class"=>"imagen_delete"), true);
					$this->_html->end("button");
				$this->_html->end("td");
			$this->_html->end("tr");
			$contador++;
		}
	}
*/
/**********************************
******* ACCIONES SERVICIOS  *******
***********************************/

	function agregarFilaServicio($ves_ser_id, $ves_hora, $ves_minuto, $ves_meridiano, $ves_duracion,  $ves_fecha)
	{
		$valor_ves_fecha = $ves_fecha;

		$sql = "INSERT INTO pozettos_venta_servicio
						(	ves_cli_id, ves_ser_id, ves_hora, 
							ves_meridiano, ves_duracion, ves_total,
							ves_fecha)
						VALUES
						(	'1', '$ves_ser_id', '$ves_hora:$ves_minuto:00', 
							'$ves_meridiano', '$ves_duracion', '0',
							'$valor_ves_fecha')";
		$this->_conexionBD->ejecutarSQL($sql);
		//echo $sql;
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return true;
		else
			return false;
	}

	function actualizarHistorialVentas()
	{
		$sql = "SELECT	ves1.ves_id,
										ves1.ves_cli_id,
										ves1.ves_color_fila,
										ves1.ves_pago,
										CONCAT(time_format(ves1.ves_hora, '%l:%i'), ves_meridiano) as ves_hora,
										dus_texto,
										time_format(ADDTIME(ves1.ves_hora, ves1.ves_duracion),'%l:%i') as ves_hora_termina,
										ves1.ves_total, 
										ves1.ves_observacion, 
										ser_nombre,
										(	SELECT SUM(ves2.ves_total)
											FROM pozettos_venta_servicio AS ves2
											WHERE ves2.ves_fecha != '".$this->_fecha_contabilidad."'
											AND ves2.ves_cli_id = ves1.ves_cli_id
											AND ves2.ves_pago = 0
										)AS deuda_servicio_vieja,
										(	SELECT SUM(vep3.vep_total)
											FROM pozettos_venta_producto AS vep3
											WHERE SUBSTRING( vep3.vep_fecha_venta, 1, 10 ) != '".$this->_fecha_contabilidad."'
											AND vep3.vep_cli_id = ves1.ves_cli_id
											AND vep3.vep_pago = 0
										)AS deuda_producto_vieja
						FROM 	pozettos_venta_servicio AS ves1, pozettos_servicio, pozettos_cliente, pozettos_duracion_servicio
						WHERE ves1.ves_ser_id = ser_id
						AND ves1.ves_cli_id = cli_id
						AND ves1.ves_duracion = dus_minutos
						AND ves_fecha = '".$this->_fecha_contabilidad."'
						ORDER BY ves_color_fila DESC, ves_id DESC";
		$this->_conexionBD->ejecutarSQL($sql);
		$contador = 0;
//echo $sql;
		while($info_tupla_historico = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
		{
			$ves_color_fila = "";
			if($info_tupla_historico['ves_color_fila'])
				$ves_color_fila = "{background: ".$info_tupla_historico['ves_color_fila'].";}";
			$fondo_default = "";
			if(!$fondo_default && $contador % 2 == 0)
				$fondo_default = "fila_historial_par";
			else if (!$fondo_default)
				$fondo_default = "fila_historial_impar";
			
			$this->_html->tag("tr", array("style"=>$ves_color_fila, "class"=>$fondo_default, "id"=>"ves_fila_".$info_tupla_historico['ves_id'], "name"=>"fila_historico"));
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("input", array("type"=>"image", "src"=>"../imagenes/color.jpg", "id"=>"ves_color_".$info_tupla_historico['ves_id'], "class"=>"boton_color"));
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_izquierda"));
					$this->_html->tag("label", array("class"=>"verdana letra_9"));
						$this->_html->printText(utf8_encode($info_tupla_historico['ser_nombre']));
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("label", array("class"=>"verdana letra_9"));
						$this->_html->printText($info_tupla_historico['ves_hora']);
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("label", array("class"=>"verdana letra_9"));
						$this->_html->printText($info_tupla_historico['dus_texto']);
						//$this->_html->printSelect($this->_conexionBDAux, "dus_minutos", "dus_texto", "pozettos_duracion_servicio", "", $info_tupla_historico['ves_duracion'], array("id"=>"ves_duracion_".$info_tupla_historico['ves_id'], "class"=>"select_duracion verdana letra_9 alineacion_centro", "size"=>"1", "onchange"=>"actualizarDuracionYTotalServicio('".$info_tupla_historico['ves_id']."');"));
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("label", array("class"=>"verdana letra_9"));
						$this->_html->printText($info_tupla_historico['ves_hora_termina']);
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_derecha"));
					$this->_html->tag("label", array("class"=>"verdana letra_9"));
						$this->_html->printText($this->_html->colocarPuntoMiles($info_tupla_historico['ves_total']));
					$this->_html->end("label");
				$this->_html->end("td");

				$checked_pago = "";
				$clase_celda_pago = "celda_debe";
				if($info_tupla_historico['ves_pago'])
				{
					$checked_pago = "checked";
					$clase_celda_pago = "celda_pago";
				}
				
				$this->_html->tag("td", array("id"=>"ves_pago_".$info_tupla_historico['ves_id'], "class"=>"alineacion_centro $clase_celda_pago"));
					$this->_html->tag("input", array($checked_pago=>$checked_pago, "type"=>"checkbox", "name"=>"ves_rad_pago_".$info_tupla_historico['ves_id'], "onchange"=>"actualizarEstadoDeuda(".$info_tupla_historico['ves_id'].", 1, 'ves');"));
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("label", array("class"=>"verdana letra_9", "title"=>utf8_encode($info_tupla_historico['cli_nombre'])));
						$this->_html->tag("form", array("action"=>"index.php", "method"=>"post"));
							$this->_html->printText($info_tupla_historico['ves_cli_id']);
							$total_deuda = $info_tupla_historico['deuda_producto_vieja'] + $info_tupla_historico['deuda_servicio_vieja'];
							if($total_deuda != "0")
							{
								$this->_html->espacios();
								$this->_html->tag("input", array("type"=>"image", "name"=>"modulo", "value"=>"deuda", "src"=>"../imagenes/deuda.gif", "class"=>"imagen_deuda", "title"=>utf8_encode($info_tupla_historico['cli_nombre']." debe [".$total_deuda."] de otros días")), true);
								$this->_html->tag("input", array("type"=>"hidden", "name"=>"cli_id", "value"=>$info_tupla_historico['ves_cli_id']));
							}
						$this->_html->end("form");
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("input", array("id"=>"ves_observacion_".$info_tupla_historico['ves_id'], "type"=>"text", "class"=>"input_observacion_producto verdana letra_9", "value"=>utf8_encode($info_tupla_historico['ves_observacion']), "onkeyup"=>"actualizarObservacion(event.keyCode, ".$info_tupla_historico['ves_id'].", 'ves');", "onchange"=>"actualizarObservacion(13, ".$info_tupla_historico['ves_id'].", 'ves');"), true);
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("button", array("class"=>"boton_delete", "onclick"=>"eliminarFila(".$info_tupla_historico['ves_id'].",'ves')"));
						$this->_html->tag("img", array("src"=>"../imagenes/delete.png", "class"=>"imagen_delete"), true);
					$this->_html->end("button");
				$this->_html->end("td");
			$this->_html->end("tr");
			$contador++;
		}
	}
	/*
	function actualizarTotalServicio($servicio, $duracion)
	{
		$sql = "SELECT tas_precio
						FROM pozettos_tarifas_servicio
						WHERE tas_ser_id = '$servicio'
						AND tas_duracion = '$duracion'
						LIMIT 1";

		$this->_conexionBD->ejecutarSQL($sql);
		if($this->_conexionBD->obtenerNumeroFilas())
			return $this->_conexionBD->obtenerFilaComoCadena();
		else
			return "0";
	}
	
	function actualizarDuracionYTotalServicio($id, $duracion)
	{
		$sql = "UPDATE pozettos_venta_servicio as ves1
						SET ves_duracion = '$duracion',
								ves_total = (	SELECT tas_precio
															FROM pozettos_tarifas_servicio
															WHERE tas_ser_id = ves1.ves_ser_id
															AND tas_duracion = '$duracion'
															LIMIT 1)
						WHERE ves_id = '$id'";
								
		$this->_conexionBD->ejecutarSQL($sql);
//echo $sql;
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return true;
		else
			return false;
	}
	*/
/**********************************
******* ACCIONES TIMERS     *******
***********************************/
	/*
	function obtenerInfoTimers()
	{
		$sql = "SELECT tim_id, 
						tim_dus_minutos,
						tim_inicia, 
						tim_finaliza,
						TIMEDIFF(CURRENT_TIMESTAMP , tim_inicia) as tim_lleva, 
						TIMEDIFF(tim_finaliza , CURRENT_TIMESTAMP) as tim_falta, 
						tim_es_incremental, 
						tim_esta_ejecutando
						FROM pozettos_timer";
								
		$this->_conexionBD->ejecutarSQL($sql);
		$arreglo_timers = array();
		
		while($info_timer = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
		{
			$arreglo_timers[] = $info_timer;
		}
		return $arreglo_timers;
	}*/
}
?>
