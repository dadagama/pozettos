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

	function obtenerTablaServicios()
	{
		$this->_html->tag("table", array("id"=>"tbl_servicios"));
			$this->_html->tag("tr");
				$this->_html->tag("td");
					$this->_html->printSelect($this->_conexionBDAux, "dus_minutos", "dus_texto", "pozettos_duracion_servicio", "", "00:00:00", array("id"=>"hiv_dus_minutos", "class"=>"ancho_80 verdana letra_9 alineacion_centro letra_roja negrilla", "title"=>"Duracion del servicio"));
				$this->_html->end("td");
				
				$sql = "SELECT ser_nombre,ser_url_foto,ser_onclick
								FROM pozettos_servicio
								WHERE ser_tipo='servicio'
								ORDER BY ser_id ASC";
				$this->_conexionBD->ejecutarSQL($sql);
		
				$opciones_select = "";
				$contador = 1;
				while($info_servicio = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
				{
					// if($contador % 10 == 0)
					// {
						// $this->_html->end("tr");
						// $this->_html->tag("tr");
							// $this->_html->tag("td");
							// $this->_html->end("td");
					// }
					$this->_html->tag("td");
						$this->_html->tag("button", array("onclick"=>$info_servicio['ser_onclick'], "title"=>$info_servicio['ser_nombre']));
							$this->_html->tag("img", array("src"=>$info_servicio['ser_url_foto']), true);
						$this->_html->end("button");
					$this->_html->end("td");
					$contador++;
				}
			$this->_html->end("tr");
			
			$this->_html->tag("tr");
				$this->_html->tag("td");
					$this->_html->tag("input", array("id"=>"hiv_total", "class"=>"ancho_80 alineacion_centro letra_roja verdana negrilla", "title"=>"Total a pagar", "type"=>"text"), true);
				$this->_html->end("td");
				
				$sql = "SELECT ser_nombre,ser_url_foto,ser_onclick
								FROM pozettos_servicio
								WHERE ser_tipo='producto'
								ORDER BY ser_id ASC";
				$this->_conexionBD->ejecutarSQL($sql);
		
				$opciones_select = "";
				$contador = 1;
				while($info_servicio = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
				{
					// if($contador % 10 == 0)
					// {
						// $this->_html->end("tr");
						// $this->_html->tag("tr");
							// $this->_html->tag("td");
							// $this->_html->end("td");
					// }
					$this->_html->tag("td");
						$this->_html->tag("button", array("onclick"=>$info_servicio['ser_onclick'], "title"=>$info_servicio['ser_nombre']));
							$this->_html->tag("img", array("src"=>$info_servicio['ser_url_foto']), true);
						$this->_html->end("button");
					$this->_html->end("td");
					$contador++;
				}
			$this->_html->end("tr");			
		$this->_html->end("table");
	}
	
	function cargarSaldoInicialTitan($sit_fecha)
	{
		$sql = "SELECT sit_saldo
						FROM pozettos_saldo_inicial_titan
						WHERE sit_fecha='$sit_fecha'
						LIMIT 1";
		$this->_conexionBD->ejecutarSQL($sql);
		if($this->_conexionBD->obtenerNumeroFilas())
			return $this->_conexionBD->obtenerFilaComoCadena();
		else
		{
			$sql = "INSERT INTO pozettos_saldo_inicial_titan (sit_saldo, sit_fecha)
							VALUES ('0','$sit_fecha')";
			$this->_conexionBD->ejecutarSQL($sql);
			return "0";
		}
	}
	
	function actualizarSaldoTitan($sit_saldo, $sit_fecha)
	{
		if(!$sit_saldo)
			$sit_saldo = "0";
		$sql = "UPDATE pozettos_saldo_inicial_titan
						SET sit_saldo = '$sit_saldo'
						WHERE sit_fecha = '$sit_fecha'";
		//echo $sql;
		$this->_conexionBD->ejecutarSQL($sql);
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return true;
		else
			return false;
	}
	
	function obtenerOptions()
	{
		$arreglo_options = array();
		/*  CLIENTES  */
		$sql = "SELECT cli_id,cli_nombre,cli_apellido
						FROM pozettos_cliente
						ORDER BY cli_id DESC";
		$this->_conexionBD->ejecutarSQL($sql);
		$options_clientes = "";
		while($info_option = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
		{
			$options_clientes .= $this->_html->tag("option", array("value"=>$info_option['cli_id']),false,true);
			$options_clientes .= $this->_html->getText($info_option['cli_id']."&nbsp;->&nbsp;".utf8_encode($info_option['cli_nombre'])." ".utf8_encode($info_option['cli_apellido']));
			$options_clientes .= $this->_html->end("option",true);
		}
		$arreglo_options['options_clientes'] = $options_clientes;
		
		/*  DURACION  */
		$sql = "SELECT dus_minutos,dus_texto
						FROM pozettos_duracion_servicio
						ORDER BY dus_minutos ASC";
		$this->_conexionBD->ejecutarSQL($sql);
		$options_duracion = "";
		while($info_option = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
		{
			$options_duracion .= $this->_html->tag("option", array("value"=>$info_option['dus_minutos']),false,true);
			$options_duracion .= $this->_html->getText($info_option['dus_texto']);
			$options_duracion .= $this->_html->end("option",true);
		}
		$arreglo_options['options_duracion'] = $options_duracion;
		
		/*  HORA  */
		$options_hora = "";
		while($info_option = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
		{
			$options_duracion .= $this->_html->tag("option", array("value"=>$info_option['dus_minutos']),false,true);
			$options_duracion .= $this->_html->getText($info_option['dus_texto']);
			$options_duracion .= $this->_html->end("option",true);
		}
		$arreglo_options['options_duracion'] = $options_duracion;
		
		/* SALDO TITAN */
		$sql = "SELECT sit_saldo
						FROM pozettos_saldo_inicial_titan
						WHERE sit_fecha='". $this->_fecha_contabilidad ."'
						LIMIT 1";
		$this->_conexionBD->ejecutarSQL($sql);
		if($this->_conexionBD->obtenerNumeroFilas())
			$arreglo_options['sit_saldo'] = $this->_conexionBD->obtenerFilaComoCadena();
		else
		{
			$sql = "INSERT INTO pozettos_saldo_inicial_titan (sit_saldo, sit_fecha)
							VALUES ('0','". $this->_fecha_contabilidad ."')";
			$this->_conexionBD->ejecutarSQL($sql);
			$arreglo_options['sit_saldo'] = "0";
		}
		return json_encode($arreglo_options);
	}

	function actualizarValor($hiv_id,$valor_nuevo,$nombre_campo)
	{
		if(!$valor_nuevo)
			$valor_nuevo = "0";
		$sql = "UPDATE pozettos_historico_venta
						SET $nombre_campo = '$valor_nuevo'
						WHERE hiv_id = '$hiv_id'";
		//echo $sql;
		$this->_conexionBD->ejecutarSQL($sql);
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return true;
		else
			return false;
	}
	
	function actualizarDeudaCliente($cli_id)
	{
		$sql = "SELECT SUM(hiv_total)
						FROM pozettos_historico_venta
						WHERE hiv_fecha != '".$this->_fecha_contabilidad."'
						AND hiv_cli_id = '$cli_id'
						AND hiv_pago = 0
						AND hiv_es_tiempo_gratis = 0";
		$this->_conexionBD->ejecutarSQL($sql);
		return $this->_conexionBD->obtenerFilaComoCadena();
	}
	
	function actualizarTotal($hiv_id)
	{
		$sql = "UPDATE pozettos_historico_venta as hiv
						SET hiv.hiv_total = (	SELECT tas_precio
																	FROM pozettos_tarifas_servicio
																	WHERE tas_ser_id = hiv.hiv_ser_id
																	AND tas_dus_minutos = hiv.hiv_dus_minutos
																	LIMIT 1)
						WHERE hiv.hiv_id = '$hiv_id'";
								
		$this->_conexionBD->ejecutarSQL($sql);
		//echo $sql;
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return true;
		else
			return false;
	}
	
	function obtenerJsonHoras($hiv_id)
	{
		$sql = "SELECT 	time_format(hiv_hora, '%l:%i') as hiv_hora,
										time_format(ADDTIME(hiv_hora, hiv_dus_minutos),'%l:%i') as hiv_hora_termina,
										dus_texto,
										hiv_total
						FROM pozettos_historico_venta, pozettos_duracion_servicio
						WHERE hiv_dus_minutos = dus_minutos
						AND hiv_id = '".$hiv_id."'";
		$this->_conexionBD->ejecutarSQL($sql);
		$arreglo_horas = $this->_conexionBD->obtenerFilaComoArregloAsociativo();
		$arreglo_horas['hiv_id'] = $hiv_id;
		return json_encode($arreglo_horas);
	}
	
	function actualizarCampoColor($id, $color_fila)
	{
		if($color_fila == "null")
			$color_fila = "null";
		else
			$color_fila = "'".$color_fila."'";

		$sql = "UPDATE pozettos_historico_venta
						SET hiv_color_fila = $color_fila
						WHERE hiv_id = '$id'";

		$this->_conexionBD->ejecutarSQL($sql);
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return true;
		else
			return false;
	} 

	function actualizarEstadoPago($id_fila, $hiv_chk_pago, $hiv_chk_gratis, $ultimo_clic)
	{
		//echo "==>$hiv_chk_pago, $hiv_chk_gratis, $ultimo_clic";
		$hiv_pago = 0;
		$hiv_es_tiempo_gratis = 0;
		if($ultimo_clic == "pago")
		{
			if($hiv_chk_pago == "true")
			{
				$hiv_es_tiempo_gratis = 0;
				$hiv_pago = 1;
			}
		}
		else if($ultimo_clic == "gratis")
		{
			if($hiv_chk_gratis == "true")
			{
				$hiv_es_tiempo_gratis = 1;
				$hiv_pago = 0;
			}
		}
	
		$reiniciar_color = "";
		$sql = "UPDATE pozettos_historico_venta
						SET hiv_pago = '$hiv_pago',
						hiv_es_tiempo_gratis = '$hiv_es_tiempo_gratis'
						$reiniciar_color
						WHERE hiv_id = '$id_fila'";
		//echo $sql;
		$this->_conexionBD->ejecutarSQL($sql);
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return true;
		else
			return false;
	}
	
	function eliminarFila($id)
	{
		$sql = "DELETE FROM pozettos_historico_venta
						WHERE hiv_id = '$id'";
		$this->_conexionBD->ejecutarSQL($sql);
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return "hiv_fila_".$id;
		else
			return false;
	}
/*
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
******* ACCIONES HISTORIAL  *******
***********************************/

	function agregarFilaHistorial($hiv_ser_id, $hiv_ser_tipo, $hiv_hora, $hiv_minuto, $hiv_meridiano, $hiv_dus_minutos, $hiv_total,  $hiv_fecha)
	{
		$valor_hiv_dus_minutos = "'00:00:00'";
		if($hiv_dus_minutos)
			$valor_hiv_dus_minutos = "'$hiv_dus_minutos'";
		$valor_hiv_total = "0";
		if($hiv_total && $hiv_ser_tipo == "producto")
			$valor_hiv_total = "'$hiv_total'";
		else if($hiv_ser_tipo == "servicio")
			$valor_hiv_total = " (SELECT tas_precio
														FROM pozettos_tarifas_servicio
														WHERE tas_ser_id = '$hiv_ser_id'
														AND tas_dus_minutos = $valor_hiv_dus_minutos
														LIMIT 1) ";
		
		$sql = "INSERT INTO pozettos_historico_venta
						(	hiv_cli_id, hiv_ser_id, hiv_fecha, hiv_hora, hiv_ser_tipo,
							hiv_meridiano, hiv_total, hiv_dus_minutos
							)
						VALUES
						(	'1', '$hiv_ser_id','$hiv_fecha','$hiv_hora:$hiv_minuto:00', '$hiv_ser_tipo',
							'$hiv_meridiano', $valor_hiv_total, $valor_hiv_dus_minutos
							)";
		$this->_conexionBD->ejecutarSQL($sql);
		//echo $sql;
		if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
			return true;
		else
			return false;
	}

	function actualizarHistorialVentas()
	{
		$sql = "SELECT	hiv1.hiv_id,
										hiv1.hiv_cli_id,
										hiv1.hiv_color_fila,
										hiv1.hiv_pago,
										hiv1.hiv_es_tiempo_gratis,
										IF(hiv1.hiv_ser_tipo = 'servicio', time_format(hiv1.hiv_hora, '%l:%i'), null) as hiv_hora,
										IF(hiv1.hiv_ser_tipo = 'servicio', dus_texto, null) as dus_texto,
										IF(hiv1.hiv_ser_tipo = 'servicio', dus_minutos, null) as dus_minutos,
										IF(hiv1.hiv_ser_tipo = 'servicio', time_format(ADDTIME(hiv1.hiv_hora, hiv1.hiv_dus_minutos),'%l:%i'), null) as hiv_hora_termina,
										hiv1.hiv_total, 
										hiv1.hiv_observacion, 
										ser_nombre,
										cli_nombre,
										(	SELECT SUM(hiv2.hiv_total)
											FROM pozettos_historico_venta AS hiv2
											WHERE hiv2.hiv_fecha != '".$this->_fecha_contabilidad."'
											AND hiv2.hiv_cli_id = hiv1.hiv_cli_id
											AND hiv2.hiv_pago = 0
											AND hiv2.hiv_es_tiempo_gratis = 0
										) AS deuda_vieja
						FROM 	pozettos_historico_venta as hiv1, pozettos_servicio, pozettos_cliente, pozettos_duracion_servicio
						WHERE hiv1.hiv_ser_id = ser_id
						AND hiv1.hiv_dus_minutos = dus_minutos
						AND hiv1.hiv_cli_id = cli_id
						AND hiv1.hiv_fecha = '".$this->_fecha_contabilidad."'
						ORDER BY hiv1.hiv_color_fila DESC, hiv1.hiv_id DESC";
		$this->_conexionBD->ejecutarSQL($sql);
		$contador = 0;

		while($info_tupla_historico = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
		{
			$hiv_color_fila = "";
			if($info_tupla_historico['hiv_color_fila'])
				$hiv_color_fila = "{background: ".$info_tupla_historico['hiv_color_fila'].";}";
			$fondo_default = "";
			if(!$fondo_default && $contador % 2 == 0)
				$fondo_default = "fila_historial_par";
			else if (!$fondo_default)
				$fondo_default = "fila_historial_impar";
			
			$this->_html->tag("tr", array("style"=>$hiv_color_fila, "class"=>$fondo_default, "id"=>"hiv_fila_".$info_tupla_historico['hiv_id'], "name"=>"fila_historico"));
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("input", array("title"=>"Colocar un color a la fila", "type"=>"image", "src"=>"../imagenes/color.jpg", "id"=>"hiv_color_".$info_tupla_historico['hiv_id'], "class"=>"boton_color"));
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_izquierda"));
					$this->_html->tag("label", array("class"=>"verdana letra_9", "title"=>"Servicio prestado"));
						$this->_html->printText(utf8_encode($info_tupla_historico['ser_nombre']));
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("label", array("title"=>"Hora en que se empieza a prestar el servicio", "id"=>"hiv_hora_".$info_tupla_historico['hiv_id'], "class"=>"verdana letra_9 cursor_cruz", "ondblclick"=>"editableHoraInicio('hiv_hora_".$info_tupla_historico['hiv_id']."',true);"));
						$this->_html->printText($info_tupla_historico['hiv_hora']);
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("input", array("type"=>"hidden", "value"=>$info_tupla_historico['dus_minutos'], "id"=>"hidden_hiv_dus_minutos_".$info_tupla_historico['hiv_id']));
					$this->_html->tag("label", array("title"=>"Duracion del servicio prestado", "id"=>"hiv_dus_minutos_".$info_tupla_historico['hiv_id'], "class"=>"verdana letra_9 cursor_cruz", "ondblclick"=>"editableDuracion('hiv_dus_minutos_".$info_tupla_historico['hiv_id']."',true);"));
						$this->_html->printText($info_tupla_historico['dus_texto']);
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("label", array("title"=>"Hora en que se termina de prestar el servicio", "id"=>"hiv_hora_termina_".$info_tupla_historico['hiv_id'], "class"=>"verdana letra_9"));
						$this->_html->printText($info_tupla_historico['hiv_hora_termina']);
					$this->_html->end("label");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_derecha"));
					$this->_html->tag("label", array("title"=>"Total a pagar por el servicio", "id"=>"hiv_total_".$info_tupla_historico['hiv_id'], "class"=>"verdana letra_9 cursor_cruz", "ondblclick"=>"editableTotal('hiv_total_".$info_tupla_historico['hiv_id']."',true);"));
						$this->_html->printText($info_tupla_historico['hiv_total']);
					$this->_html->end("label");
				$this->_html->end("td");

				$checked_pago = "";
				$clase_celda_pago = "celda_debe";
				
				if($info_tupla_historico['hiv_pago'])
				{
					$checked_pago = "checked";
					$clase_celda_pago = "celda_pago";
				}
				else if($info_tupla_historico['hiv_es_tiempo_gratis'])
					$clase_celda_pago = "";
				
				$this->_html->tag("td", array("id"=>"hiv_pago_".$info_tupla_historico['hiv_id'], "class"=>"alineacion_centro $clase_celda_pago"));
					$this->_html->tag("input", array("title"=>"Ya pago el total del servicio", $checked_pago=>$checked_pago, "type"=>"checkbox", "id"=>"hiv_chk_pago_".$info_tupla_historico['hiv_id'], "onchange"=>"actualizarEstadoPago(".$info_tupla_historico['hiv_id'].",'pago');"));
				$this->_html->end("td");
				
				$checked_gratis = "";
				$clase_celda_gratis = "";
				if($info_tupla_historico['hiv_es_tiempo_gratis'])
				{
					$checked_gratis = "checked";
					$clase_celda_gratis = "celda_pago";
				}
				
				$this->_html->tag("td", array("id"=>"hiv_pago_".$info_tupla_historico['hiv_id'], "class"=>"alineacion_centro $clase_celda_gratis"));
					$this->_html->tag("input", array("title"=>"No se cobra porque es gratis", $checked_gratis=>$checked_gratis, "type"=>"checkbox", "id"=>"hiv_chk_gratis_".$info_tupla_historico['hiv_id'], "onchange"=>"actualizarEstadoPago(".$info_tupla_historico['hiv_id'].",'gratis');"));
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("label", array("id"=>"cli_fila_".$info_tupla_historico['hiv_id'], "ondblclick"=>"editableCliente('cli_fila_".$info_tupla_historico['hiv_id']."',true);", "class"=>"verdana letra_9 cursor_cruz", "title"=>$info_tupla_historico['hiv_cli_id']." -> ".utf8_encode($info_tupla_historico['cli_nombre'])));
							$this->_html->printText($info_tupla_historico['hiv_cli_id']);
					$this->_html->end("label");
					$this->_html->tag("span", array("id"=>"cli_span_debe_".$info_tupla_historico['hiv_id']));
					if($info_tupla_historico['deuda_vieja'])
						$this->_html->tag("img", array("id"=>"cli_img_debe_".$info_tupla_historico['hiv_id'], "class"=>"imagen_deuda", "src"=>"../imagenes/deuda.gif", "title"=>"Debe ".$info_tupla_historico['deuda_vieja']." de otros dias"));
					$this->_html->end("span");
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("input", array("title"=>"Nota adicional si se necesita", "id"=>"hiv_observacion_".$info_tupla_historico['hiv_id'], "type"=>"text", "class"=>"ancho_90p verdana letra_9", "value"=>utf8_encode($info_tupla_historico['hiv_observacion']), "onchange"=>"actualizarValor('hiv_observacion_".$info_tupla_historico['hiv_id']."','hiv_observacion', 13);", "onkeypress"=>"actualizarValor('hiv_observacion_".$info_tupla_historico['hiv_id']."','hiv_observacion', event.keyCode);"), true);
				$this->_html->end("td");
				
				$this->_html->tag("td", array("class"=>"alineacion_centro"));
					$this->_html->tag("button", array("class"=>"boton_delete", "title"=>"Eliminar fila", "onclick"=>"eliminarFila(".$info_tupla_historico['hiv_id'].")"));
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
